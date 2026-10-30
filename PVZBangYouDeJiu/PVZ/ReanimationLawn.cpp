#include "ReanimationLawn.h"
#include "../HookAsm/HookAsm.h"
#include <stdint.h>
using namespace HookAsm;

void ReanimatorCache::DrawReanimatorFrame(Sexy::Graphics* g, float thePosX, float thePosY, ReanimationType theReanimationType, const char* theTrackName, DrawVariation theDrawVariation)
{
	uintptr_t func = 0x46F100;

	FXSAVE_Area fxsave_area = Asm_Fxsave();
	_asm
	{
		push theDrawVariation;
		mov ecx, theTrackName;
		mov edx, theReanimationType;
		push thePosY;
		push thePosX;
		push g;
		call func;
	}
	Asm_Fxrstor(fxsave_area);
}

Sexy::MemoryImage* ReanimatorCache::MakeBlankMemoryImage(int theWidth, int theHeight)
{
	uintptr_t func = 0x46F280;

	_asm
	{
		mov ebx, theHeight;
		mov ecx, theWidth;
		call func;
	}
}

Sexy::MemoryImage* ReanimatorCache::MakeCachedPlantFrame(SeedType theSeedType, DrawVariation theDrawVariation)
{
	uintptr_t func = 0x46F550;
    Sexy::MemoryImage* result;
	_asm
	{
		push theDrawVariation;
		mov ecx, theSeedType;
		call func;
        mov result, eax;
	}
    return result;
}

Sexy::MemoryImage* ReanimatorCache::MakeCachedMowerFrame(LawnMowerType theMowerType)
{
	uintptr_t func = 0x46F330;
	Sexy::MemoryImage* result;
	_asm
	{
		push theMowerType;
		call func;
		mov result, eax;
	}
	return result;
}
