#include "TodDebug.h"
#include "TodCommon.h"
#include "TodStringFile.h"

using namespace Sexy;

bool TodStringListReadItems(const SexyChar* theFileText)
{
	uintptr_t func = 0x519080;
	bool result;
	_asm
	{
		push theFileText;
        call func;
        add esp, 4;
        mov result, al;
	}
    return result;
}

SexyString TodStringTranslate(const SexyString& theString)
{
	uintptr_t func = 0x519520;
	SexyString result;
	SexyString* resultPtr = &result;
	_asm
	{
		mov edx, theString;
		mov edi, resultPtr;
		call func;
	}
	return result;
}

void TodDrawStringWrapped(Sexy::Graphics* g, const SexyString& theText, const Sexy::Rect& theRect, Sexy::Font* theFont, const Sexy::Color& theColor, DrawStringJustification theJustification)
{
	uintptr_t func = 0x51A040;

	_asm
	{
		push theJustification;
		mov esi,theColor;
		push theFont;
		mov ebx,theRect;
		mov edx,theText;
		push g;
        call func;
        add esp, 0xC;
	}
}
