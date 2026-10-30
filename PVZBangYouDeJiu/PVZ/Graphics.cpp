#include "Graphics.h"
#include "../HookAsm/HookAsm.h"
#include<stdint.h>
using namespace Sexy;
using namespace HookAsm;

Sexy::Graphics::Graphics(const Graphics& theGraphics)
{
	uintptr_t func = 0x5869B0;

	_asm
	{
		push theGraphics;
		mov edi, this;
		call func;
	}
}

void Sexy::Graphics::Translate(int theTransX, int theTransY)
{
	uintptr_t func = 0x5878B0;

	_asm
	{
		push theTransY;
		push theTransX;
		mov eax, this;
		call func;
	}
}

void Sexy::Graphics::SetScale(float theScaleX, float theScaleY, float theOrigX, float theOrigY)
{
	uintptr_t func = 0x5878D0;

	_asm
	{
		push theOrigY;
		push theOrigX;
		push theScaleY;
		push theScaleX;
		mov eax, this;
		call func;
	}
}

void Sexy::Graphics::SetColorizeImages(bool colorizeImages)
{
	uintptr_t func = 0x586D10;

	_asm
	{
		mov cl, colorizeImages;
		mov eax, this;
		call func;
	}
}

bool Sexy::Graphics::GetColorizeImages()
{
	uintptr_t func = 0x586D20;
	bool result;
	_asm
	{
		mov eax, this;
		call func;
		mov result, al;
	}
	return result;
}

void Sexy::Graphics::SetColor(const Color& theColor)
{
	uintptr_t func = 0x586CC0;
	_asm
	{
		mov eax, theColor;
		mov ecx, this;
		call func;
	}
}

Color& Sexy::Graphics::GetColor()
{
	// TODO: 在此处插入 return 语句
	uintptr_t func = 0x586CE0;
	_asm
	{
		mov eax, this;
		call func;
	}
}

void Sexy::Graphics::DrawImage(Image* theImage, int theX, int theY)
{
	uintptr_t func = 0x587150;

	FXSAVE_Area fxsave_area = Asm_Fxsave();
	_asm
	{
		push ebx;
		push theY;
		push theX;
		mov eax, this;
		mov ebx, theImage;
		call func;
		pop ebx;
	}
	Asm_Fxrstor(fxsave_area);
}

void Sexy::Graphics::DrawImage(Image* theImage, int theX, int theY, const Rect& theSrcRect)
{
	uintptr_t func = 0x587270;

	_asm
	{
		push theY;
		push theX;
		push theImage;
		mov eax, theSrcRect;
		mov ecx, this;
		call func;
	}
}

void Sexy::Graphics::DrawImage(Image* theImage, int theX, int theY, int theStretchedWidth, int theStretchedHeight)
{
	uintptr_t func = 0x587520;

	_asm
	{
		push theStretchedHeight;
		push theStretchedWidth;
		push theY;
		push theX;
		mov edi, theImage;
		mov eax, this;
		call func;
	}
}

void Sexy::Graphics::DrawImage(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect)
{
	uintptr_t func = 0x5875B0;

	_asm
	{
		push theSrcRect;
		mov eax, theDestRect;
		push theImage;
		mov ecx, this;
		call func;
	}
}

void Sexy::Graphics::DrawImageMirror(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, bool mirror)
{
	uintptr_t func = 0x587490;

	_asm
	{
        push mirror;
		push theSrcRect;
		mov edi, theDestRect;
		mov eax, this;
		mov ebx, theImage;
		call func;
	}
}

void Graphics::DrawImageMirror(Image* theImage, int theX, int theY, bool mirror)
{
	DrawImageMirror(theImage, theX, theY, Rect(0, 0, theImage->GetWidth(), theImage->GetHeight()), mirror);
}

void Graphics::DrawImageMirror(Image* theImage, int theX, int theY, const Rect& theSrcRect, bool mirror)
{
	if (!mirror)
	{
		DrawImage(theImage, theX, theY, theSrcRect);
		return;
	}

	theX += mTransX;
	theY += mTransY;

	if ((theSrcRect.mX + theSrcRect.mWidth > theImage->GetWidth()) ||
		(theSrcRect.mY + theSrcRect.mHeight > theImage->GetHeight()))
		return;

	Rect aDestRect = Rect(theX, theY, theSrcRect.mWidth, theSrcRect.mHeight).Intersection(mClipRect);

	int aTotalClip = theSrcRect.mWidth - aDestRect.mWidth;
	int aLeftClip = aDestRect.mX - theX;
	int aRightClip = aTotalClip - aLeftClip;

	Rect aSrcRect(theSrcRect.mX + aRightClip, theSrcRect.mY + aDestRect.mY - theY, aDestRect.mWidth, aDestRect.mHeight);

	if ((aSrcRect.mWidth > 0) && (aSrcRect.mHeight > 0))
		mDestImage->BltMirror(theImage, aDestRect.mX, aDestRect.mY, aSrcRect, mColorizeImages ? mColor : Color::White, mDrawMode);
}

void Sexy::Graphics::DrawRect(int theX, int theY, int theWidth, int theHeight)
{
	uintptr_t func = 0x586DE0;

	FXSAVE_Area fxsave_area = Asm_Fxsave();
	_asm
	{
		push theHeight;
		push theWidth;
		push theY;
		push theX;
		mov eax, this;
		call func;
	}
	Asm_Fxrstor(fxsave_area);
}

void Sexy::Graphics::FillRect(int theX, int theY, int theWidth, int theHeight)
{
	uintptr_t func = 0x586D50;

	FXSAVE_Area fxsave_area = Asm_Fxsave();
	_asm
	{
		push theHeight;
		push theWidth;
		push theY;
		push theX;
		mov eax, this;
		call func;
	}
	Asm_Fxrstor(fxsave_area);
}

void Sexy::Graphics::PushState()
{
	uintptr_t func = 0x586B40;

	_asm
	{
		push this;
		call func;
	}
}

void Sexy::Graphics::PopState()
{
	uintptr_t func = 0x586BD0;

	_asm
	{
		mov edi, this;
		call func;
	}
}

void Sexy::Graphics::DrawTrianglesTex(Image* theTexture, const TriVertex theVertices[][3], int theNumTriangles)
{
	uintptr_t func = 0x587710;

	_asm
	{
		push theNumTriangles;
		push theVertices;
		push theTexture;
		mov eax, this;
		call func;
	}
}

void Sexy::Graphics::SetDrawMode(int theDrawMode)
{
	uintptr_t func = 0x586CF0;

	_asm
	{
		mov ecx, theDrawMode;
        mov eax, this;
		call func;
	}
}

int Sexy::Graphics::GetDrawMode()
{
	int result;
	uintptr_t func = 0x586D00;

	_asm
	{
		mov eax, this;
        call func;
        mov result, eax;
	}
    return result;
}
