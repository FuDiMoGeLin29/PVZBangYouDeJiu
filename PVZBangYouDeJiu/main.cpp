#include "main.h"
#include "HookAsm/HookAsm.h"
#include "PVZ/PVZ.h"
#include <corecrt_math_defines.h>
#include <cmath>
#include <cstdio>
#include <dshow.h>
#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "uuid.lib")

namespace Main
{
	using namespace HookAsm;

	void GetXYScale(float& xScale, float& yScale)
	{
		ULONGLONG tick = GetTickCount64();
		float theta1 = (float)(tick % 500) / 500.f * M_PI * 2.f;
		float theta2 = (float)((tick + 250) % 500) / 500.f * M_PI * 2.f;
		xScale = 1.f + sin(theta1) * 0.25f;
		yScale = 1.f + sin(theta2) * 0.25f;
	}

	// ================================================================================================
	// Q 弹效果辅助工具
	// ------------------------------------------------------------------------------------------------
	// 1. QPushGfx / QPopGfx：在指定 Graphics 上以某点为中心叠加一次缩放，用完立刻还原。
	//    注意 mScaleOrig 是「绝对坐标」（SetScale 内部会加上当时的 mTransX），所以传入的 pivot 也要是绝对坐标。
	// 2. QScaleReanimMatrix / QRestoreReanimMatrix：缩放动画（Reanimation）的叠加矩阵 mOverlayMatrix。
	//    动画只认矩阵、不认 Graphics 的 mScaleX，所以必须单独处理。
	// 3. 每个 Hook 内部都用 FXSAVE/FXRSTOR 包住，避免回调里的浮点运算弄脏游戏原来的 FPU/XMM 状态。
	// ================================================================================================
	namespace
	{
		// ============================================================================================
		// 运行时钩子开关（二分排除用）：
		// 所有钩子按注册顺序编号，读 %TEMP%\pvz_hooks.txt：
		//   不存在 / 空 → 全部启用；"none" → 全部禁用；"a b" → 禁用 [a,b] 区间
		// 每秒重读，改完不用重编译。
		// ============================================================================================
		int gQHookCounter = 0;

#define Q_SKIP_MY_HOOKS 0
#define QGATE(n) if (Q_SKIP_MY_HOOKS || !QHookEnabled(n)) return;
		int gQDisableStart = -1;
		int gQDisableEnd = -1;
		DWORD gQHookFileTick = 0;

		inline void QRefreshHookMask()
		{
			DWORD aNow = GetTickCount();
			if (gQHookFileTick != 0 && aNow - gQHookFileTick < 1000)
				return;
			gQHookFileTick = aNow;

			char aPath[MAX_PATH] = { 0 };
			if (GetTempPathA(MAX_PATH, aPath) == 0)
				return;
			strcat_s(aPath, "pvz_hooks.txt");

			FILE* aFile = nullptr;
			if (fopen_s(&aFile, aPath, "r") != 0 || aFile == nullptr)
				return;

			char aBuf[64] = { 0 };
			fgets(aBuf, sizeof(aBuf), aFile);
			fclose(aFile);

			if (strstr(aBuf, "none") != nullptr)
			{
				gQDisableStart = 0;
				gQDisableEnd = 0x7FFFFFFF;
			}
			else
			{
				int aStart = -1, aEnd = -1;
				if (sscanf_s(aBuf, "%d %d", &aStart, &aEnd) == 2)
				{
					gQDisableStart = aStart;
					gQDisableEnd = aEnd;
				}
			}
		}

		inline bool QHookEnabled(int theIndex)
		{
			QRefreshHookMask();
			if (gQDisableStart < 0)
				return true;
			return !(theIndex >= gQDisableStart && theIndex <= gQDisableEnd);
		}



		constexpr int Q_MAX_GFX_DEPTH = 16;

		// 手写保存/恢复（不碰游戏自己的 Graphics 状态栈）：
		// 之前改成调用游戏 PushState/PopState，任何一处 Push/Pop 不配对都会污染游戏的栈，
		// 导致后面所有绘制带着错乱的缩放/原点。这里只保存我们实际会改的 6 个字段。
		struct QGfxState
		{
			Sexy::Graphics* mGraphics;
			float mScaleX;
			float mScaleY;
			float mOrigX;
			float mOrigY;
			float mTransX;
			float mTransY;
		};

		QGfxState gQGfxStack[Q_MAX_GFX_DEPTH];
		int gQGfxDepth = 0;

		// 调试：记录最后一个改共享 Graphics 缩放的位置，便于定位泄漏源
		const char* gQLastWriter = "(none)";

		inline void QPushGfx(Sexy::Graphics* g, float kx, float ky, float pivotX, float pivotY)
		{
			if (g == nullptr || gQGfxDepth >= Q_MAX_GFX_DEPTH)
				return;

			QGfxState& aState = gQGfxStack[gQGfxDepth++];
			aState.mGraphics = g;
			aState.mScaleX = g->mScaleX;
			aState.mScaleY = g->mScaleY;
			aState.mOrigX = g->mScaleOrigX;
			aState.mOrigY = g->mScaleOrigY;
			aState.mTransX = g->mTransX;
			aState.mTransY = g->mTransY;

			g->mScaleX = aState.mScaleX * kx;
			g->mScaleY = aState.mScaleY * ky;
			g->mScaleOrigX = pivotX;
			g->mScaleOrigY = pivotY;
		}

		inline void QPopGfx()
		{
			if (gQGfxDepth <= 0)
				return;

			QGfxState& aState = gQGfxStack[--gQGfxDepth];
			aState.mGraphics->mScaleX = aState.mScaleX;
			aState.mGraphics->mScaleY = aState.mScaleY;
			aState.mGraphics->mScaleOrigX = aState.mOrigX;
			aState.mGraphics->mScaleOrigY = aState.mOrigY;
			aState.mGraphics->mTransX = aState.mTransX;
			aState.mGraphics->mTransY = aState.mTransY;
		}
		struct QReanimState
		{
			Reanimation* mReanim = nullptr;
			float m00 = 0.f;
			float m01 = 0.f;
			float m02 = 0.f;
			float m10 = 0.f;
			float m11 = 0.f;
			float m12 = 0.f;
		};

		// 以「动画原点 + (pivotOffsetX, pivotOffsetY)」为基准做 X / Y 方向拉伸。
		// pivotOffset 就是 (1 - k) * (基准点 - 动画原点)，单位是屏幕像素；
		// 想要「图像底部中心为基准」时，把基准点取成原点正下方半个图像高度即可。
		inline void QScaleReanimMatrix(QReanimState& theState, Reanimation* theReanim, float kx, float ky,
			float pivotOffsetX, float pivotOffsetY)
		{
			theState.mReanim = theReanim;
			if (theReanim == nullptr)
				return;

			Sexy::SexyTransform2D& aMatrix = theReanim->mOverlayMatrix;
			theState.m00 = aMatrix.m00;
			theState.m01 = aMatrix.m01;
			theState.m02 = aMatrix.m02;
			theState.m10 = aMatrix.m10;
			theState.m11 = aMatrix.m11;
			theState.m12 = aMatrix.m12;
			aMatrix.m00 *= kx;
			aMatrix.m01 *= kx;
			aMatrix.m02 += pivotOffsetX;
			aMatrix.m10 *= ky;
			aMatrix.m11 *= ky;
			aMatrix.m12 += pivotOffsetY;
		}

		inline void QRestoreReanimMatrix(QReanimState& theState)
		{
			if (theState.mReanim == nullptr)
				return;

			Sexy::SexyTransform2D& aMatrix = theState.mReanim->mOverlayMatrix;
			aMatrix.m00 = theState.m00;
			aMatrix.m01 = theState.m01;
			aMatrix.m02 = theState.m02;
			aMatrix.m10 = theState.m10;
			aMatrix.m11 = theState.m11;
			aMatrix.m12 = theState.m12;
			theState.mReanim = nullptr;
		}

		// 金币（阳光 / 金银币 / 钻石）的贴图动画，绘制前压入、绘制后还原
		QReanimState gQCoinReanim;
		// 场地物品的贴图动画，绘制前压入、绘制后还原
		QReanimState gQGridItemReanim;

		// 选卡界面正在整屏缩放时，记下它的 Graphics，卡牌就不用再单独叠一次缩放，
		// 只要让位置跟着整屏一起缩放即可（否则卡牌会被缩放两次）。
		bool gQSeedPacketScaled = false;
		// 种子卡专用保存栈（DrawSeedPacket 会嵌套调用，不能用单一标志配对）
		struct QSeedPacketGfxState { Sexy::Graphics* g; float sx, sy, ox, oy, tx, ty; };
		QSeedPacketGfxState gQSeedPacketGfx[8];
		int gQSeedPacketGfxDepth = 0;
		int gQSeedPushCount = 0;
		int gQSeedPopCount = 0;


		// Board::GridToPixelX / GridToPixelY 的调用包装（原函数用 eax / ecx / ebx / esi 传参，
		// 这里用 naked 函数保证不破坏调用方的寄存器）
		int __declspec(naked) QBoardGridToPixelX(Board* theBoard, int theGridX, int theGridY)
		{
			_asm
			{
				push ebp
				mov ebp, esp
				push esi
				mov esi, [ebp + 10h]
				mov eax, [ebp + 0Ch]
				mov ecx, [ebp + 08h]
				mov edx, 41C680h
				call edx
				pop esi
				pop ebp
				ret
			}
		}

		int __declspec(naked) QBoardGridToPixelY(Board* theBoard, int theGridX, int theGridY)
		{
			_asm
			{
				push ebp
				mov ebp, esp
				push ebx
				mov eax, [ebp + 10h]
				mov ecx, [ebp + 0Ch]
				mov ebx, [ebp + 08h]
				mov edx, 41C740h
				call edx
				pop ebx
				pop ebp
				ret
			}
		}

		// ============================ 通用控件（Widget）Q 弹辅助 ============================
		// WidgetContainer 的布局（见 WidgetContainer.h）：
		//   +0x0C mWidgets.size()，+0x30 mX，+0x34 mY，+0x38 mWidth，+0x3C mHeight
		// gLawnApp 位于 0x6A9EC0，LawnApp::mBoard 位于 +0x768。

		// 这些控件跳过不弹：
		//   1. 游戏场地（整块草坪跟着弹会很怪）
		//   2. 满屏界面（背景铺满整屏，缩放会露出黑边，例如主菜单背景、选卡界面背景、小游戏选关背景）
		inline bool QSkipWidget(void* theWidget)
		{
			if (theWidget == nullptr)
				return true;

			LawnApp* aApp = *(LawnApp**)0x6A9EC0;
			if (aApp != nullptr && (void*)aApp->mBoard == theWidget)
				return true;

			int aWidth = *(int*)((char*)theWidget + 0x38);
			int aHeight = *(int*)((char*)theWidget + 0x3C);
			if (aWidth >= 800 && aHeight >= 600)
				return true;

			return false;
		}

		// 控件放大（k > 1）时会超出自己的 mClipRect 被裁掉，这里把裁剪矩形按缩放后的包围盒扩一下。
		// 说明：mClipRect 是绝对坐标；控件本地坐标是 (0,0)-(w,h)，基准点是底边中点 (w/2,h)。
		// 叶子控件这张 Graphics 是临时副本，改了不会外泄；容器控件是在 PushState 之后改的，
		// 随后的 PopState 会自动还原。
		inline void QExpandClipForWidget(Sexy::Graphics* g, int theWidth, int theHeight, float kx, float ky)
		{
			if (g == nullptr || (kx <= 1.0f && ky <= 1.0f))
				return;

			float aHalfWidth = theWidth * 0.5f;

			float aLeft = aHalfWidth * (1.0f - kx) + g->mTransX;
			float aRight = aHalfWidth * (1.0f + kx) + g->mTransX;
			float aTop = theHeight * (1.0f - ky) + g->mTransY;
			float aBottom = (float)theHeight + g->mTransY;

			int aX0 = g->mClipRect.mX;
			int aY0 = g->mClipRect.mY;
			int aX1 = g->mClipRect.mX + g->mClipRect.mWidth;
			int aY1 = g->mClipRect.mY + g->mClipRect.mHeight;

			if ((int)aLeft < aX0) aX0 = (int)aLeft;
			if ((int)aTop < aY0) aY0 = (int)aTop;
			if ((int)aRight > aX1) aX1 = (int)aRight;
			if ((int)aBottom > aY1) aY1 = (int)aBottom;

			if (aX0 < 0) aX0 = 0;
			if (aY0 < 0) aY0 = 0;
			if (aX1 > 800) aX1 = 800;
			if (aY1 > 600) aY1 = 600;

			g->mClipRect.mX = aX0;
			g->mClipRect.mY = aY0;
			g->mClipRect.mWidth = aX1 - aX0;
			g->mClipRect.mHeight = aY1 - aY0;
		}

		// 直接覆写（而不是乘上去），避免父控件 → 子控件重复叠加缩放。
		// 基准点取控件自身的底边中点；调用时 g 已经平移到控件左上角，所以本地坐标就是 (0,0)-(mWidth,mHeight)。
		inline void QSetWidgetScale(Sexy::Graphics* g, void* theWidget)
		{
			gQLastWriter = "QSetWidgetScale";
			if (g == nullptr || theWidget == nullptr)
				return;

			float xScale, yScale;
			GetXYScale(xScale, yScale);
			int aWidth = *(int*)((char*)theWidget + 0x38);
			int aHeight = *(int*)((char*)theWidget + 0x3C);

			// 退化控件（宽或高为 0）会算出 (400,0) 这种基准点，把后面所有绘制都往屏幕顶部中心拉
			if (aWidth <= 0 || aHeight <= 0)
				return;

			g->mScaleX = xScale;
			g->mScaleY = yScale;
			g->mScaleOrigX = aWidth * 0.5f + g->mTransX;
			g->mScaleOrigY = (float)aHeight + g->mTransY;

			QExpandClipForWidget(g, aWidth, aHeight, xScale, yScale);
		}

		// ==================== 不走控件系统的“格子按钮”（铲子 / 禅境花园工具） ====================
		// Board::DrawZenButtons（0x418500）和 Board::DrawShovel（0x418B70）都是直接
		// g->DrawImage 画「IMAGE_SHOVELBANK 底图 + 图标 + 数量文字」的一格按钮，不经过 Widget。
		// 做法：在画底图之前，把缩放基准设成这一格的「底边中点」；同一格后续的图标会沿用这个
		// Graphics 缩放；下一格画底图时再覆盖成新格子；函数出口统一还原。
		Sexy::Graphics* gQButtonG = nullptr;
		float gQButtonScaleX = 1.0f;
		float gQButtonScaleY = 1.0f;
		float gQButtonOrigX = 0.0f;
		float gQButtonOrigY = 0.0f;

		inline void QSetButtonScale(Sexy::Graphics* g, Sexy::Image* theButtonImage, int theX, int theY)
		{
			if (g == nullptr || theButtonImage == nullptr)
				return;

			if (gQButtonG != g)
			{
				gQButtonG = g;
				gQButtonScaleX = g->mScaleX;
				gQButtonScaleY = g->mScaleY;
				gQButtonOrigX = g->mScaleOrigX;
				gQButtonOrigY = g->mScaleOrigY;
			}

			float xScale, yScale;
			GetXYScale(xScale, yScale);
			float aWidth = (float)theButtonImage->GetCelWidth();
			float aHeight = (float)theButtonImage->GetCelHeight();

			g->mScaleX = xScale;
			g->mScaleY = yScale;
			g->mScaleOrigX = theX + aWidth * 0.5f + g->mTransX;
			g->mScaleOrigY = theY + aHeight + g->mTransY;
		}

		inline void QRestoreButtonScale()
		{
			if (gQButtonG == nullptr)
				return;

			gQButtonG->mScaleX = gQButtonScaleX;
			gQButtonG->mScaleY = gQButtonScaleY;
			gQButtonG->mScaleOrigX = gQButtonOrigX;
			gQButtonG->mScaleOrigY = gQButtonOrigY;
			gQButtonG = nullptr;
		}

		// 小游戏 / 生存 / 解密选关按钮（ChallengeScreen::DrawButton）用的状态
		Sexy::Graphics* gQChallengeG = nullptr;
		float gQChallengeScaleX = 1.0f;
		float gQChallengeScaleY = 1.0f;
		float gQChallengeOrigX = 0.0f;
		float gQChallengeOrigY = 0.0f;

		// 主菜单的向日葵奖杯（GameSelector::Draw 里的 TodDrawImageCelF）
		Sexy::Graphics* gQTrophyG = nullptr;
		float gQTrophyScaleX = 1.0f;
		float gQTrophyScaleY = 1.0f;
		float gQTrophyOrigX = 0.0f;
		float gQTrophyOrigY = 0.0f;

		// 奖杯是通过 TodDrawImageCelF -> Graphics::DrawImageF 画的，而 DrawImageF 只做 1:1 平移、
		// 不读 mScaleX。所以这里在“正在画奖杯”时把 DrawImageF 拦下来，改走
		// Graphics::DrawImage(Image*, const Rect& dest, const Rect& src)（StretchBlt）按缩放后的矩形绘制。
		bool gQTrophyPending = false;
		void* gQDrawImageFOrig = nullptr;

		void __cdecl QDrawTrophyScaled(Sexy::Graphics* g, Sexy::Image* theImage, float theX, float theY, const Sexy::Rect* theSrc)
		{
			if (g == nullptr || theImage == nullptr || theSrc == nullptr)
				return;

			float kx = g->mScaleX;
			float ky = g->mScaleY;
			float ox = g->mScaleOrigX;
			float oy = g->mScaleOrigY;
			float tx = g->mTransX;
			float ty = g->mTransY;

			// DrawImageF 内部是 (theX + mTransX) 直接贴图；这里以 (ox,oy) 为中心做缩放，
			// 再把 mTransX 减回去（因为接下来调用的 DrawImage(dest, src) 会自己再加一次）
			float ax = theX + tx;
			float ay = theY + ty;
			float dx = ox + (ax - ox) * kx - tx;
			float dy = oy + (ay - oy) * ky - ty;

			Sexy::Rect aDest((int)dx, (int)dy,
				(int)(theSrc->mWidth * kx), (int)(theSrc->mHeight * ky));
			g->DrawImage(theImage, aDest, *theSrc);
		}

		void __declspec(naked) QDrawImageFHook()
		{
			_asm
			{
				cmp byte ptr [gQTrophyPending], 0
				jne doScaled
				jmp dword ptr [gQDrawImageFOrig]
			doScaled:
				push ebp
				mov ebp, esp
				push [ebp + 14h]
				push [ebp + 10h]
				push [ebp + 0Ch]
				push [ebp + 08h]
				push eax
				call QDrawTrophyScaled
				add esp, 14h
				pop ebp
				ret 10h
			}
		}

		// GameButton::Draw 用的状态（主菜单/商店等手动绘制的石质按钮）
		Sexy::Graphics* gQGameButtonG = nullptr;
		float gQGameButtonScaleX = 1.0f;
		float gQGameButtonScaleY = 1.0f;
		float gQGameButtonOrigX = 0.0f;
		float gQGameButtonOrigY = 0.0f;

		// 面板（选卡界面背景 / 种子槽底图）整体的缩放状态
		bool gQPanelActive = false;

		// 标题界面（TitleScreen）Logo / 读条泥土 / 读条草地
		Sexy::Graphics* gQTitleG = nullptr;
		float gQTitleScaleX = 1.0f;
		float gQTitleScaleY = 1.0f;
		float gQTitleOrigX = 0.0f;
		float gQTitleOrigY = 0.0f;

		inline void QPushTitleScale(Sexy::Graphics* g, Sexy::Image* theImage, int theX, int theY)
		{
			if (g == nullptr || theImage == nullptr)
				return;

			float xScale, yScale;
			GetXYScale(xScale, yScale);
			float aWidth = (float)theImage->GetCelWidth();
			float aHeight = (float)theImage->GetCelHeight();

			gQTitleG = g;
			gQTitleScaleX = g->mScaleX;
			gQTitleScaleY = g->mScaleY;
			gQTitleOrigX = g->mScaleOrigX;
			gQTitleOrigY = g->mScaleOrigY;

			g->mScaleX = xScale;
			g->mScaleY = yScale;
			g->mScaleOrigX = theX + aWidth * 0.5f + g->mTransX;
			g->mScaleOrigY = theY + aHeight + g->mTransY;
		}

		inline void QPopTitleScale()
		{
			if (gQTitleG == nullptr)
				return;
			gQTitleG->mScaleX = gQTitleScaleX;
			gQTitleG->mScaleY = gQTitleScaleY;
			gQTitleG->mScaleOrigX = gQTitleOrigX;
			gQTitleG->mScaleOrigY = gQTitleOrigY;
			gQTitleG = nullptr;
		}

		// 主菜单场景（GameSelector 的“前景”渲染组）用的状态
		Reanimation* gQSelectorReanim = nullptr;		float gQSelectorM00 = 0.0f;
		float gQSelectorM01 = 0.0f;
		float gQSelectorM02 = 0.0f;
		float gQSelectorM10 = 0.0f;
		float gQSelectorM11 = 0.0f;
		float gQSelectorM12 = 0.0f;

		// 以屏幕底部中点 (400, 600) 为基准，把动画的叠加矩阵整体缩放
		inline void QScaleSelectorMatrix(Reanimation* theReanim, float kx, float ky)
		{
			if (theReanim == nullptr)
				return;

			Sexy::SexyTransform2D& aMatrix = theReanim->mOverlayMatrix;
			gQSelectorReanim = theReanim;
			gQSelectorM00 = aMatrix.m00;
			gQSelectorM01 = aMatrix.m01;
			gQSelectorM02 = aMatrix.m02;
			gQSelectorM10 = aMatrix.m10;
			gQSelectorM11 = aMatrix.m11;
			gQSelectorM12 = aMatrix.m12;

			aMatrix.m00 *= kx;
			aMatrix.m01 *= kx;
			aMatrix.m02 = 400.0f + (aMatrix.m02 - 400.0f) * kx;
			aMatrix.m10 *= ky;
			aMatrix.m11 *= ky;
			aMatrix.m12 = 600.0f + (aMatrix.m12 - 600.0f) * ky;
		}

		inline void QRestoreSelectorMatrix()
		{
			if (gQSelectorReanim == nullptr)
				return;
			Sexy::SexyTransform2D& aMatrix = gQSelectorReanim->mOverlayMatrix;
			aMatrix.m00 = gQSelectorM00;
			aMatrix.m01 = gQSelectorM01;
			aMatrix.m02 = gQSelectorM02;
			aMatrix.m10 = gQSelectorM10;
			aMatrix.m11 = gQSelectorM11;
			aMatrix.m12 = gQSelectorM12;
			gQSelectorReanim = nullptr;
		}

		// 以动画自身的原点为基准缩放：只改线性部分，不动平移项。
		// 对叶子/花这种“原点就在底部”的动画，这就是绕自己底部中点缩放。
		inline void QScaleReanimAboutOrigin(Reanimation* theReanim, float kx, float ky)
		{
			if (theReanim == nullptr)
				return;

			Sexy::SexyTransform2D& aMatrix = theReanim->mOverlayMatrix;
			gQSelectorReanim = theReanim;
			gQSelectorM00 = aMatrix.m00;
			gQSelectorM01 = aMatrix.m01;
			gQSelectorM02 = aMatrix.m02;
			gQSelectorM10 = aMatrix.m10;
			gQSelectorM11 = aMatrix.m11;
			gQSelectorM12 = aMatrix.m12;

			aMatrix.m00 *= kx;
			aMatrix.m01 *= kx;
			aMatrix.m10 *= ky;
			aMatrix.m11 *= ky;
		}

		// 主菜单 anim_grass 轨道（只让这条会动的草弹）
		Reanimation* gQGrassReanim = nullptr;
		int gQGrassTrackIndex = -1;
		bool gQGrassActive = false;

		// Reanimation::FindTrackIndex(const char* theTrackName, ebx = Reanimation* this)  @0x472F30
		inline int QFindTrackIndex(Reanimation* theReanim, const char* theName)
		{
			if (theReanim == nullptr || theName == nullptr)
				return -1;

			int aResult = -1;
			_asm
			{
				push ebx
				mov ebx, theReanim
				push theName
				mov eax, 472F30h
				call eax
				add esp, 4
				mov aResult, eax
				pop ebx
			}
			return aResult;
		}

		// ============================================================================================
		// BGM 替换
		// --------------------------------------------------------------------------------------------
		// 1. MP3 以资源形式（bgm.rc，id=1，RCDATA）嵌进 DLL；
		// 2. 启动时释放到 %TEMP%\pvz_bgm.mp3，用 DirectShow 播放；
		// 3. 后台线程轮询进度，快结束时 Seek 回 0 实现无缝循环；
		// 4. 钩 Music::PlayMusic（0x45ADB0，callee 不清理参数，直接 retn）让它变成空函数，
		//    这样游戏自己的 BGM 不会播放/切换，我们的 BGM 也就不会被打断或重置。
		// ============================================================================================
		void* gQPlayMusicOrig = nullptr;
		unsigned int gQBGMStream = 0;
		const void* gQBGMData = nullptr;
		unsigned int gQBGMSize = 0;

		void QBGMLog(const char* theText)
		{
			// 日志已关闭（调试期用）
			(void)theText;
		}

		void __declspec(naked) QNoopPlayMusic()
		{
			_asm { ret }
		}

		// Music::PlayFromOffset 结尾是 retn 14h（被调用者清理 0x14 字节参数）
		void __declspec(naked) QNoopPlayFromOffset()
		{
			_asm { ret 14h }
		}

		void* gQPlayFromOffsetOrig = nullptr;

		// BASS 层拦截：只允许播放我们自己的流，游戏的音乐一律拒绝
		typedef int(__stdcall* QBASS_ChannelPlayFn)(unsigned int handle, int restart);
		void* gQBassChannelPlayOrig = nullptr;
		bool gQBassPlayHookInstalled = false;

		int __stdcall QBassChannelPlayHook(unsigned int theHandle, int theRestart)
		{
			if (gQBGMStream != 0 && theHandle == gQBGMStream)
				return ((QBASS_ChannelPlayFn)gQBassChannelPlayOrig)(theHandle, theRestart);
			return 0;	// 游戏自己的音乐：不播
		}

		// BASS 2.3：StreamCreateFile 的 offset/length 是 32 位；2.4 起才是 64 位
		typedef void* (__stdcall* QBASS_StreamCreateFile23)(int mem, const void* file, unsigned int offset, unsigned int length, unsigned int flags);
		typedef void* (__stdcall* QBASS_StreamCreateFile24)(int mem, const void* file, unsigned long long offset, unsigned long long length, unsigned int flags);
		typedef int(__stdcall* QBASS_ChannelPlay)(unsigned int handle, int restart);
		typedef int(__stdcall* QBASS_ChannelSetAttribute)(unsigned int handle, unsigned int attrib, float value);
		typedef int(__stdcall* QBASS_ChannelSetAttributes)(unsigned int handle, int freq, int volume, int pan);
		typedef unsigned int(__stdcall* QBASS_GetVersion)(void);
		typedef int(__stdcall* QBASS_ErrorGetCode)(void);

		void QTryStartBGM()
		{
			if (gQBGMStream != 0 || gQBGMData == nullptr || gQBGMSize == 0)
				return;

			static bool sLogged = false;
			char aBuf[256];

			HMODULE aBass = GetModuleHandleA("bass.dll");
			if (aBass == nullptr)
				aBass = LoadLibraryA("bass.dll");
			if (aBass == nullptr)
			{
				if (!sLogged) { QBGMLog("BASS: bass.dll not found"); sLogged = true; }
				return;
			}

			QBASS_StreamCreateFile23 aCreate23 = (QBASS_StreamCreateFile23)GetProcAddress(aBass, "BASS_StreamCreateFile");
			QBASS_StreamCreateFile24 aCreate24 = (QBASS_StreamCreateFile24)GetProcAddress(aBass, "BASS_StreamCreateFile");
			QBASS_ChannelPlay aPlay = (QBASS_ChannelPlay)GetProcAddress(aBass, "BASS_ChannelPlay");
			QBASS_ChannelSetAttribute aSetAttr = (QBASS_ChannelSetAttribute)GetProcAddress(aBass, "BASS_ChannelSetAttribute");
			QBASS_ChannelSetAttributes aSetAttrs = (QBASS_ChannelSetAttributes)GetProcAddress(aBass, "BASS_ChannelSetAttributes");
			QBASS_GetVersion aGetVer = (QBASS_GetVersion)GetProcAddress(aBass, "BASS_GetVersion");
			QBASS_ErrorGetCode aErr = (QBASS_ErrorGetCode)GetProcAddress(aBass, "BASS_ErrorGetCode");

			unsigned int aVersion = (aGetVer != nullptr) ? aGetVer() : 0;
			// HIWORD = 主版本，LOWORD = 次版本；2.4 起 offset/length 为 64 位
			bool aV24 = (aVersion >> 16) == 2 && (aVersion & 0xFFFF) >= 4;

			if (!sLogged)
			{
				sprintf_s(aBuf, "BASS: ver=%08X mod=%p create=%p play=%p setAttr=%p v24=%d",
					aVersion, aBass, aCreate23, aPlay, aSetAttr, (int)aV24);
				QBGMLog(aBuf);
				sLogged = true;
			}

			if (aCreate23 == nullptr || aPlay == nullptr)
				return;

			if (!gQBassPlayHookInstalled)
			{
				gQBassPlayHookInstalled = true;
				gQBassChannelPlayOrig = (void*)aPlay;
				HookFunctionBegin((LPVOID)&QBassChannelPlayHook, (LPVOID*)&gQBassChannelPlayOrig);
				sprintf_s(aBuf, "BASS: ChannelPlay hook installed orig=%p", gQBassChannelPlayOrig);
				QBGMLog(aBuf);


			}

			// mem=TRUE 直接用内存里的 MP3；BASS_SAMPLE_LOOP = 4（原生循环）
			unsigned int aStream;
			if (aV24)
				aStream = (unsigned int)(unsigned long)aCreate24(1, gQBGMData, 0, gQBGMSize, 4);
			else
				aStream = (unsigned int)(unsigned long)aCreate23(1, gQBGMData, 0, gQBGMSize, 4);
			if (aStream == 0)
			{
				if (aErr != nullptr)
				{
					static int sLastErr = -12345;
					int aCode = aErr();
					if (aCode != sLastErr)
					{
						sprintf_s(aBuf, "BASS: StreamCreateFile failed, code=%d", aCode);
						QBGMLog(aBuf);
						sLastErr = aCode;
					}
				}
				return;		// BASS 还没初始化，等下一轮重试
			}

			if (aSetAttr != nullptr)
				aSetAttr(aStream, 2 /*BASS_ATTRIB_VOL*/, 0.8f);
			else if (aSetAttrs != nullptr)
				aSetAttrs(aStream, -1, 80 /*0..100*/, -1);

			gQBGMStream = aStream;
			if (gQBassChannelPlayOrig != nullptr)
				((QBASS_ChannelPlayFn)gQBassChannelPlayOrig)(aStream, 0);
			else
				aPlay(aStream, 0);
			QBGMLog("BASS stream started");
		}

		// 主动停掉游戏自己的音乐（Music::StopAllMusic @0x45ABB0，this 在 esi）
		void QStopGameMusic()
		{
			LawnApp* aApp = *(LawnApp**)0x6A9EC0;
			if (aApp == nullptr)
				return;
			Music* aMusic = *(Music**)((char*)aApp + 0x83C);
			if (aMusic == nullptr)
				return;

			_asm
			{
				push esi
				mov esi, aMusic
				mov eax, 45ABB0h
				call eax
				pop esi
			}
		}

		DWORD WINAPI QBGMThread(LPVOID theParam)
		{
			int aTick = 0;
			for (;;)
			{
				QTryStartBGM();
				// 每 2 秒主动停一次游戏音乐，防止它在钩子生效前已开始、或从别的路径重新开始
				if ((aTick++ % 2) == 0)
					QStopGameMusic();
				Sleep(1000);
			}
			return 0;
		}

		void QStartBGM()
		{
			QBGMLog("QStartBGM: enter");

			HMODULE aModule = nullptr;
			GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCSTR)&QStartBGM, &aModule);
			if (aModule == nullptr)
			{
				QBGMLog("QStartBGM: GetModuleHandleEx failed");
				return;
			}

			HRSRC aRes = FindResourceA(aModule, MAKEINTRESOURCEA(1), (LPCSTR)RT_RCDATA);
			if (aRes == nullptr)
			{
				QBGMLog("QStartBGM: FindResource failed");
				return;
			}

			DWORD aSize = SizeofResource(aModule, aRes);
			void* aData = LockResource(LoadResource(aModule, aRes));
			char aBuf[128];
			sprintf_s(aBuf, "QStartBGM: resource size=%lu data=%p", aSize, aData);
			QBGMLog(aBuf);
			if (aSize == 0 || aData == nullptr)
				return;

			gQBGMData = aData;
			gQBGMSize = aSize;

			CreateThread(nullptr, 0, QBGMThread, nullptr, 0, nullptr);
		}
		inline void QPushPanelScale(Sexy::Graphics* g, float pivotX, float pivotY)
		{
			if (g == nullptr)
				return;

			float xScale, yScale;
			GetXYScale(xScale, yScale);
			gQLastWriter = "QPushGfx:panel";
			QPushGfx(g, xScale, yScale, pivotX, pivotY);
			gQPanelActive = true;
		}

		inline void QPopPanelScale()
		{
			if (!gQPanelActive)
				return;
			QPopGfx();
			gQPanelActive = false;
		}

		// 关卡内左下角的金钱槽（Board::DrawUICoinBank 里的 IMAGE_COINBANK + 金额）
		Sexy::Graphics* gQCoinBankG = nullptr;
		float gQCoinBankScaleX = 1.0f;
		float gQCoinBankScaleY = 1.0f;
		float gQCoinBankOrigX = 0.0f;
		float gQCoinBankOrigY = 0.0f;

		inline void QPushCoinBankScale(Sexy::Graphics* g, Sexy::Image* theImage, int theX, int theY)
		{
			if (g == nullptr || theImage == nullptr)
				return;

			float xScale, yScale;
			GetXYScale(xScale, yScale);
			float aWidth = (float)theImage->GetCelWidth();
			float aHeight = (float)theImage->GetCelHeight();

			gQCoinBankG = g;
			gQCoinBankScaleX = g->mScaleX;
			gQCoinBankScaleY = g->mScaleY;
			gQCoinBankOrigX = g->mScaleOrigX;
			gQCoinBankOrigY = g->mScaleOrigY;

			g->mScaleX = xScale;
			g->mScaleY = yScale;
			g->mScaleOrigX = theX + aWidth * 0.5f + g->mTransX;
			g->mScaleOrigY = theY + aHeight + g->mTransY;
		}

		inline void QPopCoinBankScale()
		{
			if (gQCoinBankG == nullptr)
				return;
			gQCoinBankG->mScaleX = gQCoinBankScaleX;
			gQCoinBankG->mScaleY = gQCoinBankScaleY;
			gQCoinBankG->mScaleOrigX = gQCoinBankOrigX;
			gQCoinBankG->mScaleOrigY = gQCoinBankOrigY;
			gQCoinBankG = nullptr;
		}
	}

		// 主菜单三组动画（前景组 / 叶子 / 花）：各用独立保存，避免互相覆盖
		struct QReanimScaleState
		{
			Reanimation* r;
			float m00, m01, m02, m10, m11, m12;
		};
		QReanimScaleState gQFgState = { nullptr, 0, 0, 0, 0, 0, 0 };
		QReanimScaleState gQLeafState = { nullptr, 0, 0, 0, 0, 0, 0 };
		QReanimScaleState gQFlowerState = { nullptr, 0, 0, 0, 0, 0, 0 };
		QReanimScaleState gQCoinAttachState = { nullptr, 0, 0, 0, 0, 0, 0 };
		// 图鉴僵尸格子：整格的缩放保存
		Sexy::Graphics* gQAlmanacG = nullptr;
		float gQAlmanacSX = 1.0f, gQAlmanacSY = 1.0f, gQAlmanacOX = 0.0f, gQAlmanacOY = 0.0f;

		// 植物/僵尸等“每帧改动画矩阵”的钩子用的原始矩阵缓存（避免累乘漂移）
		struct QReanimOrig
		{
			Reanimation* r;
			float m00, m01, m02, m10, m11, m12;
		};
		QReanimOrig gQOrigCache[256];
		int gQOrigCount = 0;

		inline QReanimOrig* QGetOrig(Reanimation* r)
		{
			for (int i = 0; i < gQOrigCount; i++)
			{
				if (gQOrigCache[i].r == r)
					return &gQOrigCache[i];
			}
			if (gQOrigCount >= 256)
				return nullptr;
			QReanimOrig& e = gQOrigCache[gQOrigCount++];
			e.r = r;
			e.m00 = r->mOverlayMatrix.m00; e.m01 = r->mOverlayMatrix.m01; e.m02 = r->mOverlayMatrix.m02;
			e.m10 = r->mOverlayMatrix.m10; e.m11 = r->mOverlayMatrix.m11; e.m12 = r->mOverlayMatrix.m12;
			return &e;
		}
		// 禅境花园植物覆盖层（水滴/气泡）的缩放保存
		Sexy::Graphics* gQZenOverlayG = nullptr;
		float gQZenOverlaySX = 1.0f, gQZenOverlaySY = 1.0f, gQZenOverlayOX = 0.0f, gQZenOverlayOY = 0.0f;

		// 幂等版本：第一次记录原始矩阵，之后每次都用「原始矩阵 × 缩放」重算，
		// 所以不需要在绘制结束后还原（避免了往可能已失效的动画指针写数据）。
		inline void QScaleReanimState(QReanimScaleState& st, Reanimation* r, float kx, float ky, bool aboutOrigin)
		{
			if (r == nullptr)
				return;
			Sexy::SexyTransform2D& m = r->mOverlayMatrix;
			if (st.r != r)
			{
				st.r = r;
				st.m00 = m.m00; st.m01 = m.m01; st.m02 = m.m02;
				st.m10 = m.m10; st.m11 = m.m11; st.m12 = m.m12;
			}

			m.m00 = st.m00 * kx;
			m.m01 = st.m01 * kx;
			m.m02 = st.m02;
			m.m10 = st.m10 * ky;
			m.m11 = st.m11 * ky;
			m.m12 = st.m12;
			if (!aboutOrigin)
			{
				m.m02 = 400.0f + (st.m02 - 400.0f) * kx;
				m.m12 = 600.0f + (st.m12 - 600.0f) * ky;
			}
		}

		inline void QRestoreReanimState(QReanimScaleState& st)
		{
			if (st.r == nullptr)
				return;
			Sexy::SexyTransform2D& m = st.r->mOverlayMatrix;
			m.m00 = st.m00; m.m01 = st.m01; m.m02 = st.m02;
			m.m10 = st.m10; m.m11 = st.m11; m.m12 = st.m12;
			st.r = nullptr;
		}
		// 绘制期缩放：成对保存/还原（绘制前施加，调用返回后立刻还原）
		struct QDrawSave
		{
			Reanimation* r;
			float m00, m01, m02, m10, m11, m12;
			bool used;
		};
		QDrawSave gQDrawSave[8];
		int gQDrawDepth = 0;

		inline void QDrawScaleBegin(Reanimation* r, float kx, float ky, float ox, float oy)
		{
			if (r == nullptr || gQDrawDepth >= 8)
				return;
			QDrawSave& s = gQDrawSave[gQDrawDepth++];
			s.r = r; s.used = true;
			s.m00 = r->mOverlayMatrix.m00; s.m01 = r->mOverlayMatrix.m01; s.m02 = r->mOverlayMatrix.m02;
			s.m10 = r->mOverlayMatrix.m10; s.m11 = r->mOverlayMatrix.m11; s.m12 = r->mOverlayMatrix.m12;
			r->mOverlayMatrix.m00 *= kx;
			r->mOverlayMatrix.m11 *= ky;
			r->mOverlayMatrix.m02 -= ox * (kx - 1.f);
			r->mOverlayMatrix.m12 -= oy * (ky - 1.f);
		}

		inline void QDrawScaleEnd()
		{
			if (gQDrawDepth <= 0)
				return;
			QDrawSave& s = gQDrawSave[--gQDrawDepth];
			if (!s.used || s.r == nullptr)
				return;
			s.r->mOverlayMatrix.m00 = s.m00; s.r->mOverlayMatrix.m01 = s.m01; s.r->mOverlayMatrix.m02 = s.m02;
			s.r->mOverlayMatrix.m10 = s.m10; s.r->mOverlayMatrix.m11 = s.m11; s.r->mOverlayMatrix.m12 = s.m12;
			s.used = false;
		}
	void init_hook()
	{
		//这里写初始化Hook的代码
		//例如：HookBegin((LPVOID)0x114514,Hookcallback);
		/*HookBegin((LPVOID)0x465A90, [](Register& reg) { QGATE(__COUNTER__);
			ULONGLONG tick = GetTickCount64();
			Plant* plant = *(Plant**)(reg.esp + 0x4);
			Sexy::Graphics* g = *(Sexy::Graphics**)(reg.esp + 0x8);
			g->mScaleX *= 0.5f + (float)(tick % 500) / 500.f;
			g->mScaleY *= 0.5f + (float)((tick + 250) % 500) / 500.f;

			});*/
		HookBegin((LPVOID)0x463E2C, [](Register& reg) {
			Plant* plant = (Plant*)reg.ebx;
			Reanimation* reanim = (Reanimation*)reg.ebp;
			float xScale, yScale;
			GetXYScale(xScale, yScale);
			reanim->mOverlayMatrix.m00 *= xScale;
			reanim->mOverlayMatrix.m11 *= yScale;
			reanim->mOverlayMatrix.Translate(-40 * (xScale - 1.f), -70 * (yScale - 1.f));
			});
		HookBegin((LPVOID)0x0052C5F7, [](Register& reg) {
			Zombie* zombie = (Zombie*)reg.edi;
			Sexy::SexyTransform2D& matrix = *(Sexy::SexyTransform2D*)reg.ebx;
			float xScale, yScale;
			GetXYScale(xScale, yScale);
			matrix.m00 *= xScale;
			matrix.m11 *= yScale;
			matrix.Translate(-30 * (xScale - 1.f), -120 * (yScale - 1.f));
			});
		HookBegin((LPVOID)0x00458C74, [](Register& reg) {
			Sexy::Graphics* g = (Sexy::Graphics*)(reg.esp + 0x1C);
			LawnMower* lawnMowver = (LawnMower*)reg.ebx;
			LawnApp* app = lawnMowver->mApp;
			Reanimation* reanim = app->ReanimationTryToGet(lawnMowver->mReanimID);
			float xScale, yScale;
			GetXYScale(xScale, yScale);
			reanim->mOverlayMatrix.m00 = xScale;
			reanim->mOverlayMatrix.m11 = yScale;
			g->mScaleX = xScale;
			g->mScaleY = yScale;
			g->mScaleOrigX = 0.0f;
			g->mScaleOrigY = 0.0f;
			g->Translate(-50 * (xScale - 1.f), -50 * (yScale - 1.f));
			});

		// ============================================================================================
		// 金币（Coin）
		// --------------------------------------------------------------------------------------------
		// 阳光、银币、金币、钻石的主体都是挂在 Coin 身上的贴图动画（Attachment -> Reanimation）。
		// Coin::Draw 里画附件之前（0x4319C3，ebp = Coin*），把该动画的叠加矩阵按 X / Y 缩放；
		// 附件画完（0x4319C8）立刻还原，避免矩阵逐帧累积。
		// ============================================================================================
		HookBegin((LPVOID)0x4319C3, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			Coin* aCoin = (Coin*)reg.ebp;
			float xScale, yScale;
			GetXYScale(xScale, yScale);
			gQCoinReanim.mReanim = nullptr;
			if (aCoin != nullptr && aCoin->mAttachmentID != 0)
			{
				Reanimation* aReanim = FindReanimAttachment(aCoin->mAttachmentID);
				QScaleReanimMatrix(gQCoinReanim, aReanim, xScale, yScale, 0.0f, 0.0f);
			}
			Asm_Fxrstor(aFpu);
			});

		HookBegin((LPVOID)0x4319C8, [](Register& reg) { QGATE(__COUNTER__);
			QRestoreReanimMatrix(gQCoinReanim);
			});

		

		// 关卡奖励、场景物品等用 TodDrawImageCelCenterScaledF 绘制的贴图（0x431D61 调用前）：
		// 该函数以「贴图中心」为锚点缩放，所以直接把栈上的 theScaleX / theScaleY 乘上系数即可。
		// 参数布局：[esp]=thePosX, [esp+4]=thePosY, [esp+8]=theCelCol, [esp+0xC]=theScaleX, [esp+0x10]=theScaleY
		HookBegin((LPVOID)0x431D61, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			Sexy::Image* aImage = (Sexy::Image*)reg.ecx;
			float xScale, yScale;
			GetXYScale(xScale, yScale);
			float* aScale = (float*)(reg.esp + 0xC);
			float* aPosY = (float*)(reg.esp + 0x4);
			// 这个函数把贴图中心固定在 (thePosX + celW/2, thePosY + celH/2)，
			// 想让「底边」不动，就把中心往下/往上补回来：Δ = celH * 原缩放 * (1 - k) / 2
			// 该函数以贴图中心为锚点，位置即中心，不需要位移补偿
			aScale[0] *= xScale;
			aScale[1] *= yScale;
			Asm_Fxrstor(aFpu);
			});

		// 银币 / 金币飞行时的光圈（0x431A92 调用 TodDrawImageCenterScaledF 前）：
		// 参数布局：[esp]=thePosX, [esp+4]=thePosY, [esp+8]=theScaleX, [esp+0xC]=theScaleY
		HookBegin((LPVOID)0x431A92, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			Sexy::Image* aImage = (Sexy::Image*)reg.eax;
			float xScale, yScale;
			GetXYScale(xScale, yScale);
			float* aScale = (float*)(reg.esp + 0x8);
			// 这个函数是以 (posX,posY) 为【中心】绘制，缩放中心就是它本身，不需要位移补偿
			aScale[0] *= xScale;
			aScale[1] *= yScale;
			Asm_Fxrstor(aFpu);
			});

		// ============================================================================================
		// 子弹（Projectile）
		// --------------------------------------------------------------------------------------------
		// 子弹不走 Graphics 的缩放，而是直接给一整块目标矩形 / 矩阵，这里按「子弹贴图中心」改参数。
		// ============================================================================================
		// 路径一：不旋转的子弹（豌豆、孢子等）走 Graphics::DrawImageMirror，
		// 目标矩形指针在 edi 上，内容是 {x, y, w, h}，此时为贴图的本地坐标 (0, 0, celW, celH)。
		HookBegin((LPVOID)0x46E786, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			float xScale, yScale;
			GetXYScale(xScale, yScale);
			int* aRect = (int*)reg.edi;
			int aWidth = aRect[2];
			int aHeight = aRect[3];
			// 横向：保持中心不动；纵向：保持底边不动
			aRect[0] = (int)(aWidth * (1.0f - xScale) * 0.5f);
			aRect[1] = (int)(aHeight * (1.0f - yScale));
			aRect[2] = (int)(aWidth * xScale);
			aRect[3] = (int)(aHeight * yScale);
			Asm_Fxrstor(aFpu);
			});

		// 路径二：带旋转的子弹（卷心菜、西瓜、玉米粒等）走 TodBltMatrix，
		// 0x46E7FB 处 TodScaleRotateTransformMatrix 刚构造完矩阵，矩阵位于 [esp+0x58]，
		// 内存布局 m00,m01,m02,m10,m11,m12；平移量就是贴图中心，所以只乘行向量即可。
		HookBegin((LPVOID)0x46E7FB, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			float xScale, yScale;
			GetXYScale(xScale, yScale);
			int aCelWidth = (int)reg.edi;
			int aCelHeight = (int)reg.ebx;
			float* aMatrix = (float*)(reg.esp + 0x58);
			// 矩阵平移量是贴图中心，先算出贴图在竖直方向上的半高（考虑旋转后的轴对齐范围），
			// 再把平移量补到「底边」上，这样缩放时底边不动
			float aHalfHeight = (fabsf(aMatrix[3]) * aCelWidth + fabsf(aMatrix[4]) * aCelHeight) * 0.5f;
			aMatrix[0] *= xScale;	// m00
			aMatrix[1] *= xScale;	// m01
			aMatrix[3] *= yScale;	// m10
			aMatrix[4] *= yScale;	// m11
			aMatrix[5] += (1.0f - yScale) * aHalfHeight;	// m12
			Asm_Fxrstor(aFpu);
			});

		// ============================================================================================
		// 场地物品（GridItem）
		// --------------------------------------------------------------------------------------------
		// 弹坑、梯子、花瓶、臭鼬、传送门等都是 Reanimation，在 GridItem::DrawGridItem 里统一绘制：
		// 0x44D18D 调用 Reanimation::DrawRenderGroup 前（ecx = Reanimation*）缩放叠加矩阵，
		// 0x44D192 画完立刻还原。
		// ============================================================================================
		HookBegin((LPVOID)0x44D18D, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			float xScale, yScale;
			GetXYScale(xScale, yScale);
			// 场地物品动画的原点一般就落在格子底部，直接以原点为基准即可
			QScaleReanimMatrix(gQGridItemReanim, (Reanimation*)reg.ecx, xScale, yScale, 0.0f, 0.0f);
			Asm_Fxrstor(aFpu);
			});
		HookBegin((LPVOID)0x44D192, [](Register& reg) { QGATE(__COUNTER__);
			QRestoreReanimMatrix(gQGridItemReanim);
			});

		// 墓碑是纯贴图绘制（DrawGraveStone），不会走上面的动画分支，
		// 所以在 0x44D159 调用 DrawGraveStone 之前，以「所在格子的底边中点」压入 Graphics 缩放，
		// 0x44D160 画完还原。格子底边中点由 Board::GridToPixelX / GridToPixelY 算出来。
		HookBegin((LPVOID)0x44D159, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			GridItem* aGridItem = (GridItem*)reg.edi;
			Sexy::Graphics* g = (Sexy::Graphics*)reg.ebx;
			float xScale, yScale;
			GetXYScale(xScale, yScale);

			int aPixelX = 0;
			int aPixelY = 0;
			Board* aBoard = aGridItem->mBoard;
			if (aBoard != nullptr)
			{
				aPixelX = QBoardGridToPixelX(aBoard, aGridItem->mGridX, aGridItem->mGridY);
				aPixelY = QBoardGridToPixelY(aBoard, aGridItem->mGridX, aGridItem->mGridY);
			}

			gQLastWriter = "QPushGfx:gravestone";
			QPushGfx(g, xScale, yScale, aPixelX + 40.0f, aPixelY + 80.0f);
			Asm_Fxrstor(aFpu);
			});
		HookBegin((LPVOID)0x44D160, [](Register& reg) { QGATE(__COUNTER__);
			QPopGfx();
			});

		// ============================================================================================
		// 种子卡（SeedBank 里的每一张卡）
		// --------------------------------------------------------------------------------------------
		// 卡牌由 DrawSeedPacket 统一绘制，而且它本身就支持 g->mScaleX / g->mScaleY
		// （原版就是靠这个来放大正在拖动的卡牌），所以这里只要：
		//   1. 进入函数前把 x / y 偏移一下，让缩放以「卡片底边中点」为基准；
		//   2. 把缩放比例乘到 Graphics 上；
		//   3. 函数出口（0x488215，唯一退出点之前）还原 Graphics，避免影响后面的绘制。
		// 参数布局：[esp+4]=g, [esp+8]=x, [esp+0xC]=y
		// ============================================================================================
		HookBegin((LPVOID)0x4876F0, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			Sexy::Graphics* g = *(Sexy::Graphics**)(reg.esp + 0x4);
			float* aPosX = (float*)(reg.esp + 0x8);
			float* aPosY = (float*)(reg.esp + 0xC);
			float xScale, yScale;
			GetXYScale(xScale, yScale);

			// 基准点：卡片底边中点 (x + 宽/2, y + 高)
			// 种子槽、选卡界面、金币奖励里的卡牌都走这里，因此每张卡都是单独弹的
			float aHalfWidth = SEED_PACKET_WIDTH * 0.5f;
			float aBottomX = *aPosX + aHalfWidth + g->mTransX;		// 绝对坐标
			float aBottomY = *aPosY + (float)SEED_PACKET_HEIGHT + g->mTransY;
			*aPosX += aHalfWidth * (1.0f - xScale);
			*aPosY += SEED_PACKET_HEIGHT * (1.0f - yScale);

			gQLastWriter = "QPushGfx:seedpacket";
			gQSeedPushCount++;
			// 专用栈保存（不用共享的 QPushGfx 栈，避免嵌套/漏 Pop 互相影响）
			if (gQSeedPacketGfxDepth < 8)
			{
				QSeedPacketGfxState& aSaved = gQSeedPacketGfx[gQSeedPacketGfxDepth++];
				aSaved.g = g;
				aSaved.sx = g->mScaleX;
				aSaved.sy = g->mScaleY;
				aSaved.ox = g->mScaleOrigX;
				aSaved.oy = g->mScaleOrigY;
				aSaved.tx = g->mTransX;
				aSaved.ty = g->mTransY;
			}
			g->mScaleX *= xScale;
			g->mScaleY *= yScale;
			g->mScaleOrigX = aBottomX;
			g->mScaleOrigY = aBottomY;

			// 关键：把 Graphics 的平移“烘焙”进 x / y，并把平移清零。
			// DrawSeedPacket 在 g->mScaleX != 1 时，价格文字会改走 TodDrawStringMatrix
			// （纯绝对矩阵，不加 g->mTransX），而卡牌本身走的是 x + mTransX；
			// 不烘焙的话价格会和卡牌错位（选卡界面滑入、局内卡槽都会偏到左边）。
			*aPosX += g->mTransX;
			*aPosY += g->mTransY;
			g->mTransX = 0.0f;
			g->mTransY = 0.0f;
			Asm_Fxrstor(aFpu);
			});
		// 出口还原：0x488215 是 ret 之前的最后一条 add esp, 0E4h
		HookBegin((LPVOID)0x488215, [](Register& reg) { QGATE(__COUNTER__);
			gQSeedPopCount++;
			if (gQSeedPacketGfxDepth <= 0)
				return;
			QSeedPacketGfxState& aSaved = gQSeedPacketGfx[--gQSeedPacketGfxDepth];
			if (aSaved.g == nullptr)
				return;
			aSaved.g->mScaleX = aSaved.sx;
			aSaved.g->mScaleY = aSaved.sy;
			aSaved.g->mScaleOrigX = aSaved.ox;
			aSaved.g->mScaleOrigY = aSaved.oy;
			aSaved.g->mTransX = aSaved.tx;
			aSaved.g->mTransY = aSaved.ty;
			});

		// ============================================================================================
		// 出怪进度条（Board::DrawProgressMeter）
		// --------------------------------------------------------------------------------------------
		// 逐元素：只让「进度条底图」自己弹，文字/旗帜不参与，避免它们绕进度条的基准点乱动。
		// 填充条是 DrawImage(dest, src) 不认 Graphics 缩放，单独按同一基准点改目标矩形。
		//   0x41754F：底图（ebp = Graphics*，ecx = IMAGE_FLAGMETER），画完 0x417554 立刻还原
		//   0x4175D2：填充条，eax = &目标矩形 {x, y, w, h}，edi = IMAGE_FLAGMETER
		// ============================================================================================
		HookBegin((LPVOID)0x41754F, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			Sexy::Graphics* g = (Sexy::Graphics*)reg.ebp;
			Sexy::Image* aImage = (Sexy::Image*)reg.ecx;
			float xScale, yScale;
			GetXYScale(xScale, yScale);
			// 基准点：进度条底边中点
			float aCenterX = 593.0f + aImage->GetCelWidth() * 0.5f;
			float aCenterY = 575.0f + aImage->GetCelHeight();
			gQLastWriter = "QPushGfx:meter";
			QPushGfx(g, xScale, yScale, aCenterX, aCenterY);
			Asm_Fxrstor(aFpu);
			});
		HookBegin((LPVOID)0x4175D2, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			Sexy::Image* aImage = (Sexy::Image*)reg.edi;
			float xScale, yScale;
			GetXYScale(xScale, yScale);
			float aCenterX = 593.0f + aImage->GetCelWidth() * 0.5f;
			float aCenterY = 575.0f + aImage->GetCelHeight();
			int* aRect = (int*)reg.eax;
			aRect[0] = (int)(aCenterX + (aRect[0] - aCenterX) * xScale);
			aRect[1] = (int)(aCenterY + (aRect[1] - aCenterY) * yScale);
			aRect[2] = (int)(aRect[2] * xScale);
			aRect[3] = (int)(aRect[3] * yScale);
			Asm_Fxrstor(aFpu);
			});
		// 旗帜（0x417A2C / 0x417A45 两处 DrawImageCel）：与进度条用同一个基准点一起缩放
		HookBegin((LPVOID)0x417A2C, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			Sexy::Graphics* g = (Sexy::Graphics*)reg.ebp;
			Sexy::Image* aImage = (Sexy::Image*)reg.ecx;
			if (g != nullptr && aImage != nullptr)
			{
				float xScale, yScale;
				GetXYScale(xScale, yScale);
				float aCenterX = 593.0f + aImage->GetCelWidth() * 0.5f;
				float aCenterY = 575.0f + aImage->GetCelHeight();
				g->mScaleX = xScale;
				g->mScaleY = yScale;
				g->mScaleOrigX = aCenterX;
				g->mScaleOrigY = aCenterY;
			}
			Asm_Fxrstor(aFpu);
			});

		HookBegin((LPVOID)0x417A31, [](Register& reg) { QGATE(__COUNTER__);
			Sexy::Graphics* g = (Sexy::Graphics*)reg.ebp;
			if (g != nullptr)
			{
				g->mScaleX = 1.0f;
				g->mScaleY = 1.0f;
				g->mScaleOrigX = 0.0f;
				g->mScaleOrigY = 0.0f;
			}
			});

		HookBegin((LPVOID)0x417A45, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			Sexy::Graphics* g = (Sexy::Graphics*)reg.ebp;
			Sexy::Image* aImage = (Sexy::Image*)reg.ecx;
			if (g != nullptr && aImage != nullptr)
			{
				float xScale, yScale;
				GetXYScale(xScale, yScale);
				float aCenterX = 593.0f + aImage->GetCelWidth() * 0.5f;
				float aCenterY = 575.0f + aImage->GetCelHeight();
				g->mScaleX = xScale;
				g->mScaleY = yScale;
				g->mScaleOrigX = aCenterX;
				g->mScaleOrigY = aCenterY;
			}
			Asm_Fxrstor(aFpu);
			});

		HookBegin((LPVOID)0x417A4A, [](Register& reg) { QGATE(__COUNTER__);
			Sexy::Graphics* g = (Sexy::Graphics*)reg.ebp;
			if (g != nullptr)
			{
				g->mScaleX = 1.0f;
				g->mScaleY = 1.0f;
				g->mScaleOrigX = 0.0f;
				g->mScaleOrigY = 0.0f;
			}
			});

		HookBegin((LPVOID)0x417554, [](Register& reg) { QGATE(__COUNTER__);
			// 不还原成“之前的值”，强制归位：进度条后面的旗帜/文字不该继承任何残留缩放
			QPopGfx();
			Sexy::Graphics* g = (Sexy::Graphics*)reg.ebp;
			if (g != nullptr)
			{
				g->mScaleX = 1.0f;
				g->mScaleY = 1.0f;
				g->mScaleOrigX = 0.0f;
				g->mScaleOrigY = 0.0f;
			}
			});

		// ============================================================================================
		// 通用 UI 控件（主菜单、小游戏选关、图鉴、商店、对话框、各种按钮……）
		// --------------------------------------------------------------------------------------------
		// 所有控件最终都走 Sexy::WidgetContainer::DrawAll（0x538240）：
		//   · 叶子控件：直接 Draw(g)
		//   · 容器控件自身：PushState -> Draw(g) -> PopState（PopState 会自动还原缩放）
		//   · 子控件：复制一份 Graphics、平移到子控件位置后递归 DrawAll
		// 注意：钩子点都选在「几条普通 MOV」上（每条 5 字节整），不跨越 call/含 SIB 的指令，
		// 避免被 HookBegin 搬运时出现指令长度/重定位问题。
		// ============================================================================================
		// 叶子控件：0x53830B = mov edx,[edi] ; mov eax,[ebp+arg_4]；edi = 控件，g 在 [ebp+arg_4]
		HookBegin((LPVOID)0x53830B, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			void* aWidget = (void*)reg.edi;
			if (!QSkipWidget(aWidget))
			{
				Sexy::Graphics* g = *(Sexy::Graphics**)(reg.ebp + 0xC);
				QSetWidgetScale(g, aWidget);
			}
			Asm_Fxrstor(aFpu);
			});

		// 容器控件自身：0x538357 = mov edx,[edi] ; mov eax,[edx+68h]；edi = 控件，esi = g
		HookBegin((LPVOID)0x538357, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			void* aWidget = (void*)reg.edi;
			if (!QSkipWidget(aWidget))
			{
				Sexy::Graphics* g = (Sexy::Graphics*)reg.esi;
				QSetWidgetScale(g, aWidget);
			}
			Asm_Fxrstor(aFpu);
			});

		// 子控件：0x5383E8 = mov edx,[esi] ; mov edx,[edx+6Ch]；esi = 子控件，edi = &aClipG
		HookBegin((LPVOID)0x5383E8, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			void* aWidget = (void*)reg.esi;
			if (!QSkipWidget(aWidget))
			{
				Sexy::Graphics* g = (Sexy::Graphics*)reg.edi;
				QSetWidgetScale(g, aWidget);
			}
			Asm_Fxrstor(aFpu);
			});

		// ============================================================================================
		// 禅境花园工具条 / 普通关铲子（不走控件系统的格子按钮）
		// --------------------------------------------------------------------------------------------
		// DrawZenButtons（0x418500）每格先画 IMAGE_SHOVELBANK 底图（0x4185E6），再画图标和数量；
		// 下一格箭头在 0x4185BC；函数出口 0x418B4B 还原。
		// DrawShovel（0x418B70）的铲子格在 0x418BC5，函数出口 0x418C5B 还原。
		// 这两个调用点参数都是：[esp]=x，[esp+4]=y，ebx=底图，g 在 eax/ebp。
		// ============================================================================================
		HookBegin((LPVOID)0x4185E6, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			QSetButtonScale((Sexy::Graphics*)reg.ebp, (Sexy::Image*)reg.ebx,
				*(int*)(reg.esp), *(int*)(reg.esp + 0x4));
			Asm_Fxrstor(aFpu);
			});

		HookBegin((LPVOID)0x4185BC, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			QSetButtonScale((Sexy::Graphics*)reg.eax, (Sexy::Image*)reg.ebx,
				*(int*)(reg.esp), *(int*)(reg.esp + 0x4));
			Asm_Fxrstor(aFpu);
			});

		HookBegin((LPVOID)0x418B4B, [](Register& reg) { QGATE(__COUNTER__);
			QRestoreButtonScale();
			});

		HookBegin((LPVOID)0x418BC5, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			QSetButtonScale((Sexy::Graphics*)reg.eax, (Sexy::Image*)reg.ebx,
				*(int*)(reg.esp), *(int*)(reg.esp + 0x4));
			Asm_Fxrstor(aFpu);
			});

		HookBegin((LPVOID)0x418C5B, [](Register& reg) { QGATE(__COUNTER__);
			QRestoreButtonScale();
			});

		// ============================================================================================
		// 小游戏 / 生存 / 解密选关界面（ChallengeScreen::DrawButton）
		// --------------------------------------------------------------------------------------------
		// 这个界面里的关卡按钮是 mBtnNoDraw 的“假控件”，真正的画面由 ChallengeScreen::Draw
		// 循环调用 DrawButton(g, index) 手动绘制，所以控件级钩子覆盖不到。
		//   DrawButton 入口 0x42E920：[esp+4]=ChallengeScreen*，[esp+8]=Graphics*，[esp+0xC]=index
		//   按钮控件 = this->mChallengeButtons[index]（+0xA0 + index*4），矩形在 +0x30/+0x34/+0x38/+0x3C
		//   函数出口 0x42F142 还原（所有分支都汇到这里）
		// 图片和按钮上的文字都走 g->DrawImage（字形也吃 mScaleX），所以会一起弹。
		// ============================================================================================
		HookBegin((LPVOID)0x42E920, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			void* aThis = *(void**)(reg.esp + 0x4);
			Sexy::Graphics* g = *(Sexy::Graphics**)(reg.esp + 0x8);
			int aIndex = *(int*)(reg.esp + 0xC);
			void* aButton = nullptr;
			if (aThis != nullptr && aIndex >= 0 && aIndex < 64)
				aButton = *(void**)((char*)aThis + 0xA0 + aIndex * 4);

			gQChallengeG = nullptr;
			if (g != nullptr && aButton != nullptr)
			{
				float xScale, yScale;
				GetXYScale(xScale, yScale);
				int aWidth = *(int*)((char*)aButton + 0x38);
				int aHeight = *(int*)((char*)aButton + 0x3C);
				int aPosX = *(int*)((char*)aButton + 0x30);
				int aPosY = *(int*)((char*)aButton + 0x34);

				gQChallengeG = g;
				gQChallengeScaleX = g->mScaleX;
				gQChallengeScaleY = g->mScaleY;
				gQChallengeOrigX = g->mScaleOrigX;
				gQChallengeOrigY = g->mScaleOrigY;

				g->mScaleX = xScale;
				g->mScaleY = yScale;
				g->mScaleOrigX = aPosX + aWidth * 0.5f + g->mTransX;
				g->mScaleOrigY = aPosY + aHeight + g->mTransY;
			}
			Asm_Fxrstor(aFpu);
			});

		HookBegin((LPVOID)0x42F142, [](Register& reg) { QGATE(__COUNTER__);
			if (gQChallengeG == nullptr)
				return;
			gQChallengeG->mScaleX = gQChallengeScaleX;
			gQChallengeG->mScaleY = gQChallengeScaleY;
			gQChallengeG->mScaleOrigX = gQChallengeOrigX;
			gQChallengeG->mScaleOrigY = gQChallengeOrigY;
			gQChallengeG = nullptr;
			});

		// ============================================================================================
		// 主菜单左下角的向日葵奖杯（GameSelector::Draw 里单独画的贴图）
		// --------------------------------------------------------------------------------------------
		// 0x44AAEE = call TodDrawImageCelF(IMAGE_SUNFLOWER_TROPHY, ...)，实际栈布局：
		//   [esp]=g，[esp+4]=thePosX（+10 的那个），[esp+8]=thePosY（+390 的那个），[esp+0xC]=theCelCol，ecx=贴图
		// 0x44AAF3 画完后还原。
		// ============================================================================================
		HookBegin((LPVOID)0x44AAEE, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			Sexy::Graphics* g = *(Sexy::Graphics**)(reg.esp);
			Sexy::Image* aImage = (Sexy::Image*)reg.ecx;
			float* aPosX = (float*)(reg.esp + 0x4);
			float* aPosY = (float*)(reg.esp + 0x8);
			gQTrophyG = nullptr;
			if (g != nullptr && aImage != nullptr)
			{
				float xScale, yScale;
				GetXYScale(xScale, yScale);
				float aWidth = (float)aImage->GetCelWidth();
				float aHeight = (float)aImage->GetCelHeight();

				gQTrophyG = g;
				gQTrophyScaleX = g->mScaleX;
				gQTrophyScaleY = g->mScaleY;
				gQTrophyOrigX = g->mScaleOrigX;
				gQTrophyOrigY = g->mScaleOrigY;

				g->mScaleX = xScale;
				g->mScaleY = yScale;
				g->mScaleOrigX = *aPosX + aWidth * 0.5f + g->mTransX;
				g->mScaleOrigY = *aPosY + aHeight + g->mTransY;
				gQTrophyPending = true;
			}
			Asm_Fxrstor(aFpu);
			});

		HookBegin((LPVOID)0x44AAF3, [](Register& reg) { QGATE(__COUNTER__);
			gQTrophyPending = false;
			if (gQTrophyG == nullptr)
				return;
			gQTrophyG->mScaleX = gQTrophyScaleX;
			gQTrophyG->mScaleY = gQTrophyScaleY;
			gQTrophyG->mScaleOrigX = gQTrophyOrigX;
			gQTrophyG->mScaleOrigY = gQTrophyOrigY;
			gQTrophyG = nullptr;
			});

		// ============================================================================================
		// GameButton::Draw（禅境花园右上角「主菜单」「商店」、主菜单的「点击开始」等都是这种按钮）
		// --------------------------------------------------------------------------------------------
		// GameButton 不是 Widget（布局见 GameButton.h：mX +0x8、mY +0xC、mWidth +0x10、mHeight +0x14），
		// Draw 内部会把自己的坐标加到 g->mTransX 上再画，所以基准点用「g->mTransX + mX + 宽/2, … + 高」。
		//   0x447EC0 入口：esi = GameButton*，[esp+4] = Graphics*
		//   0x4482EF 出口（所有分支都汇到这里）还原
		// ============================================================================================
		HookBegin((LPVOID)0x447EC0, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			void* aButton = (void*)reg.esi;
			Sexy::Graphics* g = *(Sexy::Graphics**)(reg.esp + 0x4);
			gQGameButtonG = nullptr;
			if (aButton != nullptr && g != nullptr)
			{
				float xScale, yScale;
				GetXYScale(xScale, yScale);
				int aWidth = *(int*)((char*)aButton + 0x10);
				int aHeight = *(int*)((char*)aButton + 0x14);
				int aPosX = *(int*)((char*)aButton + 0x8);
				int aPosY = *(int*)((char*)aButton + 0xC);

				gQGameButtonG = g;
				gQGameButtonScaleX = g->mScaleX;
				gQGameButtonScaleY = g->mScaleY;
				gQGameButtonOrigX = g->mScaleOrigX;
				gQGameButtonOrigY = g->mScaleOrigY;

				g->mScaleX = xScale;
				g->mScaleY = yScale;
				g->mScaleOrigX = aPosX + aWidth * 0.5f + g->mTransX;
				g->mScaleOrigY = aPosY + aHeight + g->mTransY;
			}
			Asm_Fxrstor(aFpu);
			});

		HookBegin((LPVOID)0x4482EF, [](Register& reg) { QGATE(__COUNTER__);
			if (gQGameButtonG == nullptr)
				return;
			gQGameButtonG->mScaleX = gQGameButtonScaleX;
			gQGameButtonG->mScaleY = gQGameButtonScaleY;
			gQGameButtonG->mScaleOrigX = gQGameButtonOrigX;
			gQGameButtonG->mScaleOrigY = gQGameButtonOrigY;
			gQGameButtonG = nullptr;
			});
		// GameButton::Draw 的另一个出口（早期返回 0x447F57 之后是 retn 4 @0x447F68），
		// 原来只有 0x4482EF 一个还原点，走这条路就会漏还原、污染后面的绘制。
		HookBegin((LPVOID)0x447F57, [](Register& reg) { QGATE(__COUNTER__);
			if (gQGameButtonG == nullptr)
				return;
			gQGameButtonG->mScaleX = gQGameButtonScaleX;
			gQGameButtonG->mScaleY = gQGameButtonScaleY;
			gQGameButtonG->mScaleOrigX = gQGameButtonOrigX;
			gQGameButtonG->mScaleOrigY = gQGameButtonOrigY;
			gQGameButtonG = nullptr;
			});

		// ============================================================================================
		// 面板：选卡界面背景 + 种子槽底图
		// --------------------------------------------------------------------------------------------
		// 面板和卡牌各自弹：面板以自己的底边中点为基准，卡牌仍以各自底边中点为准（互不影响）。
		// 做法是在“画面板”的那几条绘制之前压入缩放，画完立刻还原，再继续画卡牌。
		//   选卡背景：0x48472F = DrawImage(IMAGE_SEEDCHOOSER_BACKGROUND, 0, 87)，之后 0x484734 还原
		//   种子槽  ：0x48973A（ebx = IMAGE_SEEDBANK，ebp = Graphics*），循环画卡前 0x489781 还原
		//             （种子槽里的阳光框属于槽本身，跟着槽一起弹是对的；
		//               关卡左下角的钱袋是另一处 IMAGE_COINBANK，单独在 0x41A37E 处理）
		// ============================================================================================
		HookBegin((LPVOID)0x48472F, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			Sexy::Graphics* g = (Sexy::Graphics*)reg.eax;
			Sexy::Image* aImage = (Sexy::Image*)reg.ebx;
			int aPosX = *(int*)(reg.esp);
			int aPosY = *(int*)(reg.esp + 0x4);
			if (g != nullptr && aImage != nullptr)
			{
				float aWidth = (float)aImage->GetCelWidth();
				float aHeight = (float)aImage->GetCelHeight();
				QPushPanelScale(g, aPosX + aWidth * 0.5f + g->mTransX, aPosY + aHeight + g->mTransY);
			}
			Asm_Fxrstor(aFpu);
			});

		HookBegin((LPVOID)0x484734, [](Register& reg) { QGATE(__COUNTER__);
			QPopPanelScale();
			});

		HookBegin((LPVOID)0x48973A, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			Sexy::Graphics* g = (Sexy::Graphics*)reg.ebp;
			Sexy::Image* aImage = (Sexy::Image*)reg.ebx;
			if (g != nullptr && aImage != nullptr)
			{
				float aWidth = (float)aImage->GetCelWidth();
				float aHeight = (float)aImage->GetCelHeight();
				QPushPanelScale(g, aWidth * 0.5f + g->mTransX, aHeight + g->mTransY);
			}
			Asm_Fxrstor(aFpu);
			});

		HookBegin((LPVOID)0x489781, [](Register& reg) { QGATE(__COUNTER__);
			QPopPanelScale();
			});

		// ============================================================================================
		// 标题界面（TitleScreen）：Logo、读条泥土、读条草地
		// --------------------------------------------------------------------------------------------
		// 三个都是普通 DrawImage(x, y)，各自以「贴图底边中点」弹，画完立刻还原：
		//   0x48DA47  IMAGE_PVZ_LOGO          → 0x48DA4C 还原
		//   0x48DA6D  IMAGE_LOADBAR_DIRT      → 0x48DA72 还原
		//   0x48DA99  IMAGE_LOADBAR_GRASS     → 0x48DA9E 还原
		// 调用点寄存器：ebx = 贴图，eax = Graphics*，[esp] = x，[esp+4] = y
		// ============================================================================================
		HookBegin((LPVOID)0x48DA47, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			QPushTitleScale((Sexy::Graphics*)reg.eax, (Sexy::Image*)reg.ebx,
				*(int*)(reg.esp), *(int*)(reg.esp + 0x4));
			Asm_Fxrstor(aFpu);
			});
		HookBegin((LPVOID)0x48DA4C, [](Register& reg) { QGATE(__COUNTER__);
			QPopTitleScale();
			});

		HookBegin((LPVOID)0x48DA6D, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			QPushTitleScale((Sexy::Graphics*)reg.eax, (Sexy::Image*)reg.ebx,
				*(int*)(reg.esp), *(int*)(reg.esp + 0x4));
			Asm_Fxrstor(aFpu);
			});
		HookBegin((LPVOID)0x48DA72, [](Register& reg) { QGATE(__COUNTER__);
			QPopTitleScale();
			});

		HookBegin((LPVOID)0x48DA99, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			QPushTitleScale((Sexy::Graphics*)reg.eax, (Sexy::Image*)reg.ebx,
				*(int*)(reg.esp), *(int*)(reg.esp + 0x4));
			Asm_Fxrstor(aFpu);
			});
		HookBegin((LPVOID)0x48DA9E, [](Register& reg) { QGATE(__COUNTER__);
			QPopTitleScale();
			});

		// ============================================================================================
		// 主菜单场景（GameSelector 的“前景”渲染组）
		// --------------------------------------------------------------------------------------------
		// 0x44A73B = DrawRenderGroup(前景组)：墓碑、木牌、地面装饰都在这组，按屏幕底部中点缩放，
		// 0x44A740 画完立刻还原。组 1（天空/房子）不缩放。
		// 另外单独尝试只缩放 anim_grass 轨道（见下面），没命中时不影响任何东西。
		// ============================================================================================
		
		

		

		// ============================================================================================
		// 主菜单的叶子 / 花（GameSelector::DrawOverlay）
		// --------------------------------------------------------------------------------------------
		//   0x44AF4A  mLeafReanimID（[this+0x110]）的动画绘制 → 0x44AF4F 还原
		//   0x44AF81  mFlowerReanimID[3]（[this+0x104]，循环 3 次）→ 0x44AF86 还原
		// ecx = Reanimation*，同样以屏幕底部中点 (400,600) 缩放。
		// ============================================================================================
		HookBegin((LPVOID)0x44AF4A, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			float xScale, yScale;
			GetXYScale(xScale, yScale);
			// 叶子这个动画的原点缩放会把它缩出画面，改回屏幕底部中点
			QScaleReanimState(gQLeafState, (Reanimation*)reg.ecx, xScale, yScale, false);
			Asm_Fxrstor(aFpu);
			});

		

		HookBegin((LPVOID)0x44AF4F, [](Register& reg) { QGATE(__COUNTER__);
			QRestoreReanimState(gQLeafState);
			});
		

		

		

		// 主菜单那条会动的草：只缩放 anim_grass 这一条轨道（组级缩放碰不到它）。
		// 做法：钩 Reanimation::DrawRenderGroup 里的逐轨道调用点（0x472E9A，ebx = Reanimation*、edi = ReanimTrack*），
		// 用 Reanimation::FindTrackIndex（0x472F30）取 "anim_grass" 的索引做比较，命中才缩放，
		// 调用返回后（0x472E9F）还原。轨道基址 = [Reanimation+0x58]，每条 0x60 字节。
		// ============================================================================================
		

		

		// 奖杯：拦 Graphics::DrawImageF（0x5876B0），"正在画奖杯"时改走缩放绘制。
		gQDrawImageFOrig = (void*)0x5876B0;
		HookFunctionBegin((LPVOID)&QDrawImageFHook, (LPVOID*)&gQDrawImageFOrig);

		// ============================================================================================
		// 关卡内左下角的金钱槽（Board::DrawUICoinBank）
		// --------------------------------------------------------------------------------------------
		// 0x41A37E = DrawImage(IMAGE_COINBANK, x, y)：ebx = 贴图，eax = g，[esp] = x，[esp+4] = y
		// 以槽的底边中点为基准缩放；金额文字随后绘制，会跟着槽一起动（同一块 UI，视觉上是整体的）。
		// 0x41A3FB = 金额文字画完之后立刻还原（不能等到函数出口 0x41A418，
		//            否则同一函数里后面画的东西会被带上金钱槽的基准点）。
		// ============================================================================================
		HookBegin((LPVOID)0x41A37E, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			QPushCoinBankScale((Sexy::Graphics*)reg.eax, (Sexy::Image*)reg.ebx,
				*(int*)(reg.esp), *(int*)(reg.esp + 0x4));
			Asm_Fxrstor(aFpu);
			});

		HookBegin((LPVOID)0x41A3FB, [](Register& reg) { QGATE(__COUNTER__);
			QPopCoinBankScale();
			});

		// ============================================================================================
		// ============================================================================================

		// ============================================================================================
		// 每帧兜底：Board::Draw 开头把共享 Graphics 的缩放复位。
		// 0x41AD43 处 edi = Graphics*（arg_0），0x41AD4E 是下一条 call，此时 edi 已就绪。
		// 这样任何钩子漏还原的缩放最多影响当帧，不会累积成“基准点整体错乱”。
		// ============================================================================================
		HookBegin((LPVOID)0x41AD4E, [](Register& reg) { QGATE(__COUNTER__);

			Sexy::Graphics* g = (Sexy::Graphics*)reg.edi;
			if (g != nullptr)
			{
				g->mScaleX = 1.0f;
				g->mScaleY = 1.0f;
				g->mScaleOrigX = 0.0f;
				g->mScaleOrigY = 0.0f;
			}
			});

		// ============================================================================================
		// 戴夫的商店：每个商品格子（StoreScreen::DrawItem @0x48B170）
		// 已售出的商品走的是另一条分支（只画图标），所以之前不弹。
		// 入口 [esp+4]=StoreItem、[esp+8]=spotIndex、[esp+0xC]=Graphics*；
		// 共同出口 0x48B4A3（正常/售罄两条路都汇到这里）还原。
		// 格子位置：第一排 (422 + 74*i, 206)，第二排起 (372 + 74*(i-4), 310)，格宽 74。
		// ============================================================================================
		

		

		// ============================================================================================
		// 戴夫的商店：商品格子（StoreScreen::DrawItem @0x48B170）
		// 签名（函数表）：DrawItem(StoreItem, int spotIndex, Graphics* g, StoreScreen* this)
		//   入口：[esp+4]=StoreItem、[esp+8]=spotIndex、[esp+0xC]=Graphics*
		//   出口：0x48B4A3（正常/售罄两条分支的汇合点）
		// 为防止野指针崩溃，先用 IsBadReadPtr 校验 g 是否可读。
		// ============================================================================================
		

		

		// ============================================================================================
		// 戴夫的商店：商品图标（StoreScreen::DrawItemIcon @0x48AC50）
		// 签名（函数表）：DrawItemIcon(bool theIsForHighlight, ecx = StoreItem, edx = theSpotIndex,
		//                              edi = Graphics* g, StoreScreen* this)
		//   入口：edi = Graphics*，edx = 格子序号
		//   出口：0x48B15C（唯一 retn 之前的公共收尾）还原
		// 格子位置：第一排 (422 + 74*i, 206)，第二排起 (372 + 74*(i-4), 310)，格宽 74
		// ============================================================================================
		HookBegin((LPVOID)0x48AC50, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			Sexy::Graphics* g = (Sexy::Graphics*)reg.edi;
			int aSpot = (int)reg.edx;
			bool aBad = (g == nullptr) || IsBadReadPtr(g, sizeof(void*) * 8);
			if (aSpot < 0) aSpot = 0;
if (aBad)
			{
				Asm_Fxrstor(aFpu);
				return;
			}
			int aPosX, aPosY;
			if (aSpot < 4) { aPosX = 422 + 74 * aSpot; aPosY = 206; }
			else { aPosX = 372 + 74 * (aSpot - 4); aPosY = 310; }
			float xScale, yScale;
			GetXYScale(xScale, yScale);
			QPushGfx(g, xScale, yScale, aPosX + 37.0f, aPosY + 74.0f);
			Asm_Fxrstor(aFpu);
			});

		HookBegin((LPVOID)0x48B15C, [](Register& reg) { QGATE(__COUNTER__);
			QPopGfx();
			});

		// ============================================================================================
		// 商店里的盆栽商品（ZenGarden::DrawPottedPlantIcon @0x51D0E0）
		// 它把 theScale（0.7）作为参数传给 DrawPottedPlant，不走 Graphics 缩放。
		// 0x51D0EA 处 fstp 把 0.7 写到 [esp]（栈顶），这里直接乘上我们的系数即可。
		// ============================================================================================
		

		// ============================================================================================
		// 禅境花园植物的需求提示（水滴 / 气泡）：ZenGarden::DrawPlantOverlay
		//   0x521F6D = DrawImage(IMAGE_PLANTSPEECHBUBBLE, 50, 0)，之后 0x521FC1 画 IMAGE_WATERDROP
		// 它们会继承前面元素泄漏的缩放，导致水滴乱飘。这里在画气泡之前把缩放强制归 1/0。
		// 覆盖层本身不需要缩放，所以不需要还原。
		// ============================================================================================
		

		// ============================================================================================
		// 商店盆栽商品：ZenGarden::DrawPottedPlant（0x51D110）
		// 它用参数 theScale（=0.7）绘制，不读 Graphics 缩放。
		// 在入口扫描栈上参数，只修改值恰好是 0.7f 的那个 float，避免误伤其它数据。
		// ============================================================================================
		

		// ============================================================================================
		// 禅境花园植物需求提示（水滴/气泡）：ZenGarden::DrawPlantOverlay（0x521F30）
		// 进入覆盖层前保存缩放并归位（0x521F6D = 气泡 DrawImage），覆盖层返回后还原（0x41702B）。
		// 该函数有 3 个 retn，所以还原点放在调用方返回处，而不是函数内部。
		// ============================================================================================
		

		

		// ============================================================================================
		// 植物绘制期缩放（Plant::Draw @0x465A90 里的两处 DrawRenderGroup，ecx = 植物动画）
		//   0x465D98 / 0x465E96：调用前 ecx = esi = Reanimation*
		// 用幂等缓存：第一次记录原始矩阵，之后每帧用「原始矩阵 × 缩放」重算。
		// 这样暂停时（UpdateReanim 不跑）植物依然会弹，且不会累乘。
		// ============================================================================================
		

		

		// ============================================================================================
		// 僵尸绘制期缩放（sub_52D020 里的 4 处 DrawRenderGroup，ecx = ebx = 僵尸动画）
		// 用幂等缓存，暂停时（不跑 UpdateReanim）僵尸也会弹。
		// ============================================================================================
		
		
		
		
		
		
		
		
		
		
		
		
		HookBegin((LPVOID)0x52D44F, [](Register& reg) { QGATE(__COUNTER__);
			QDrawScaleEnd();
			});
		HookBegin((LPVOID)0x52D49C, [](Register& reg) { QGATE(__COUNTER__);
			QDrawScaleEnd();
			});
		HookBegin((LPVOID)0x52D649, [](Register& reg) { QGATE(__COUNTER__);
			QDrawScaleEnd();
			});
		HookBegin((LPVOID)0x52D6B6, [](Register& reg) { QGATE(__COUNTER__);
			QDrawScaleEnd();
			});
		// ============================================================================================
		// 图鉴僵尸页的格子按钮（AlmanacDialog::DrawZombies @0x402C00）
		// 每格：0x402DC5 / 0x402DFB 画僵尸图标（[esp]=x, [esp+4]=y）→ 0x4031D0 画框 → 0x40321F 高亮
		// 循环尾 0x403248 还原。格 85x80，基准点 (x+42, y+80)。
		// ============================================================================================
		

		

		

		HookBegin((LPVOID)0x402DC5, [](Register& reg) { QGATE(__COUNTER__);
			Sexy::Graphics* g = (Sexy::Graphics*)reg.eax;
			int aX = *(int*)(reg.esp);
			int aY = *(int*)(reg.esp + 0x4);
			if (g != nullptr && gQAlmanacG == nullptr)
			{
				float xScale, yScale;
				GetXYScale(xScale, yScale);
				gQAlmanacG = g;
				gQAlmanacSX = g->mScaleX; gQAlmanacSY = g->mScaleY;
				gQAlmanacOX = g->mScaleOrigX; gQAlmanacOY = g->mScaleOrigY;
				g->mScaleX = xScale; g->mScaleY = yScale;
				g->mScaleOrigX = aX + 42.0f;
				g->mScaleOrigY = aY + 80.0f;
			}
			});

		HookBegin((LPVOID)0x402DFB, [](Register& reg) { QGATE(__COUNTER__);
			Sexy::Graphics* g = (Sexy::Graphics*)reg.eax;
			int aX = *(int*)(reg.esp);
			int aY = *(int*)(reg.esp + 0x4);
			if (g != nullptr && gQAlmanacG == nullptr)
			{
				float xScale, yScale;
				GetXYScale(xScale, yScale);
				gQAlmanacG = g;
				gQAlmanacSX = g->mScaleX; gQAlmanacSY = g->mScaleY;
				gQAlmanacOX = g->mScaleOrigX; gQAlmanacOY = g->mScaleOrigY;
				g->mScaleX = xScale; g->mScaleY = yScale;
				g->mScaleOrigX = aX + 42.0f;
				g->mScaleOrigY = aY + 80.0f;
			}
			});
		HookBegin((LPVOID)0x403248, [](Register& reg) { QGATE(__COUNTER__);
			if (gQAlmanacG == nullptr)
				return;
			gQAlmanacG->mScaleX = gQAlmanacSX; gQAlmanacG->mScaleY = gQAlmanacSY;
			gQAlmanacG->mScaleOrigX = gQAlmanacOX; gQAlmanacG->mScaleOrigY = gQAlmanacOY;
			gQAlmanacG = nullptr;
			});

		// ============================================================================================
		// 图鉴里缓存的僵尸画像（ReanimatorCache::DrawCachedZombie @0x470170）
		// 内部调用 TodDrawImageScaledF（0x512950，左上锚点、自带缩放参数），不吃 Graphics 缩放。
		// 调用点 0x4701B2 的栈参数：[esp]=thePosX, [esp+4]=thePosY, [esp+8]=theScaleX, [esp+0xC]=theScaleY，
		// eax = Image*。这里按「底边中点」调整位置并乘上缩放系数。
		// ============================================================================================
		HookBegin((LPVOID)0x4701B2, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			Sexy::Image* aImage = (Sexy::Image*)reg.eax;
			if (aImage != nullptr)
			{
				float* aPosX = (float*)(reg.esp);
				float* aPosY = (float*)(reg.esp + 0x4);
				float* aScaleX = (float*)(reg.esp + 0x8);
				float* aScaleY = (float*)(reg.esp + 0xC);
				float xScale, yScale;
				GetXYScale(xScale, yScale);
				float aW = aImage->GetCelWidth() * (*aScaleX);
				float aH = aImage->GetCelHeight() * (*aScaleY);
				*aPosX += aW * (1.0f - xScale) * 0.5f;
				*aPosY += aH * (1.0f - yScale);
				*aScaleX *= xScale;
				*aScaleY *= yScale;
			}
			Asm_Fxrstor(aFpu);
			});

		HookBegin((LPVOID)0x4031A4, [](Register& reg) { QGATE(__COUNTER__);
			FXSAVE_Area aFpu = Asm_Fxsave();
			Sexy::Image* aImage = (Sexy::Image*)reg.eax;
			if (aImage != nullptr)
			{
				float* aPosX = (float*)(reg.esp);
				float* aPosY = (float*)(reg.esp + 0x4);
				float* aScaleX = (float*)(reg.esp + 0x8);
				float* aScaleY = (float*)(reg.esp + 0xC);
				float xScale, yScale;
				GetXYScale(xScale, yScale);
				float aW = aImage->GetCelWidth() * (*aScaleX);
				float aH = aImage->GetCelHeight() * (*aScaleY);
				*aPosX += aW * (1.0f - xScale) * 0.5f;
				*aPosY += aH * (1.0f - yScale);
				*aScaleX *= xScale;
				*aScaleY *= yScale;
			}
			Asm_Fxrstor(aFpu);
			});
		// BGM：把游戏自己的音乐播放全部变成空函数（换成 DLL 里嵌入的那首 BASS 流）
		HookFunctionBegin((LPVOID)&QNoopPlayMusic, (LPVOID*)&gQPlayMusicOrig);
		HookFunctionBegin((LPVOID)&QNoopPlayFromOffset, (LPVOID*)&gQPlayFromOffsetOrig);

	}

	void run()
	{
		//这里写运行的代码
		QStartBGM();
	}

	void dll_exit()
	{
		//这里写退出Hook的代码

	}
}
