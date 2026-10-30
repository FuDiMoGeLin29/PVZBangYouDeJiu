#include "TodCommon.h"
#include "../HookAsm/HookAsm.h"
#include <stdint.h>
using namespace Sexy;
using namespace HookAsm;

void TodDrawImageScaledF(Graphics* g, Image* theImage, float thePosX, float thePosY, float theScaleX, float theScaleY)
{
	uintptr_t func = 0x512950;
	FXSAVE_Area fxsave_area = Asm_Fxsave();
	_asm
	{
		push theScaleY;
		push theScaleX;
		push thePosY;
		push thePosX;
		mov eax, theImage;
		mov ecx, g;
		call func;
		add esp, 0x10;
	}
	Asm_Fxrstor(fxsave_area);
}

void TodDrawString(Sexy::Graphics* g, const std_string_PVZ& theText, int thePosX, int thePosY, Sexy::Font* theFont, const Sexy::Color& theColor, DrawStringJustification theJustification)
{
	uintptr_t func = 0x511CE0;
	int cR = theColor.mRed;
	int cG = theColor.mGreen;
	int cB = theColor.mBlue;
	int cA = theColor.mAlpha;

	FXSAVE_Area fxsave_area = Asm_Fxsave();
	_asm
	{
		push ebx;
		push cA;
		push cB;
		push cG;
		push cR;
		push theJustification;
		push thePosY;
		mov ecx, thePosX;
		mov edx, theText;
		push g;
		mov ebx, theFont;
		call func;
		add esp, 0x1C;
		pop ebx;
	}
	Asm_Fxrstor(fxsave_area);
}

bool TodLoadResources(const std_string_PVZ& theGroup)
{
	uintptr_t func = 0x513120;
	_asm
	{
		push theGroup;
		call func;
		add esp, 4;
	}
}

int TodAnimateCurve(int theTimeStart, int theTimeEnd, int theTimeAge, int thePositionStart, int thePositionEnd, TodCurves theCurve)
{
	uintptr_t func = 0x511C40;
	int result;

	_asm
	{
		push theCurve;
		push thePositionEnd;
		push thePositionStart;
		mov eax, theTimeAge;
		mov ecx, theTimeEnd;
		mov edx, theTimeStart;
		call func;
		add esp, 0xC;
		mov result, eax;
	}
	return result;
}

void TodBltMatrix(Sexy::Graphics* g, Sexy::Image* theImage, const Sexy::SexyMatrix3& theTransform, const Sexy::Rect& theClipRect, const Sexy::Color& theColor, int theDrawMode, const Sexy::Rect& theSrcRect)
{
	uintptr_t func = 0x512650;

	_asm
	{
		mov ebx,theSrcRect;
		push theDrawMode;
		push theColor;
		push theClipRect;
		push theTransform;
		mov eax, theImage;
		mov esi, g;
		call func;
		add esp, 0x10;
	}
}
