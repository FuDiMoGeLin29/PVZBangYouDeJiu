#pragma once
#include "Graphics.h"
#include "Image.h"
#include <stdint.h>
#include "std_string_PVZ.h"

struct TodWeightedGridArray
{
	int					mX;
	int					mY;
	int					mWeight;
};

class TodSmoothArray
{
public:
	int					mItem;
	float				mWeight;
	float				mLastPicked;
	float				mSecondLastPicked;
};

enum DrawStringJustification
{
	DS_ALIGN_LEFT,
	DS_ALIGN_RIGHT,
	DS_ALIGN_CENTER,
	DS_ALIGN_LEFT_VERTICAL_MIDDLE,
	DS_ALIGN_RIGHT_VERTICAL_MIDDLE,
	DS_ALIGN_CENTER_VERTICAL_MIDDLE
};

enum TodCurves
{
    CURVE_CONSTANT,             // 常函数曲线
    CURVE_LINEAR,               // 线性曲线
    CURVE_EASE_IN,              // 二次曲线（缓入）
    CURVE_EASE_OUT,             // 二次曲线（缓出）
    CURVE_EASE_IN_OUT,          // 缓入缓出曲线
    CURVE_EASE_IN_OUT_WEAK,     // 缓入缓出曲线（效果减弱）
    CURVE_FAST_IN_OUT,          // 快入快出曲线
    CURVE_FAST_IN_OUT_WEAK,     // 快入快出曲线（效果减弱）
    CURVE_WEAK_FAST_IN_OUT,     // 【废弃】弱快入快出曲线
    CURVE_BOUNCE,               // 弹跳效果曲线
    CURVE_BOUNCE_FAST_MIDDLE,   // 弹跳效果曲线（尖形）
    CURVE_BOUNCE_SLOW_MIDDLE,   // 弹跳效果曲线（罩形）
    CURVE_SIN_WAVE,             // 正弦曲线
    CURVE_EASE_SIN_WAVE         // 缓入缓出的正弦曲线
};

void TodDrawImageScaledF(Sexy::Graphics* g, Sexy::Image* theImage, float thePosX, float thePosY, float theScaleX, float theScaleY);

inline void	SetBit(uint32_t& theNum, int theIdx, bool theValue = true) { if (theValue) theNum |= 1 << theIdx; else theNum &= ~(1 << theIdx); }
inline bool				TestBit(uint32_t theNum, int theIdx) { return theNum & (1 << theIdx); }

void TodDrawString(Sexy::Graphics* g, const std_string_PVZ& theText, int thePosX, int thePosY, Sexy::Font* theFont, const Sexy::Color& theColor, DrawStringJustification theJustification);

bool TodLoadResources(const std_string_PVZ& theGroup);

int TodAnimateCurve(int theTimeStart, int theTimeEnd, int theTimeAge, int thePositionStart, int thePositionEnd, TodCurves theCurve);

void TodBltMatrix(Sexy::Graphics* g, Sexy::Image* theImage, const Sexy::SexyMatrix3& theTransform, const Sexy::Rect& theClipRect, const Sexy::Color& theColor, int theDrawMode, const Sexy::Rect& theSrcRect);