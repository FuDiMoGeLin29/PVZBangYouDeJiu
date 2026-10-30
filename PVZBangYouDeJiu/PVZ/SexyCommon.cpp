#include "SexyCommon.h"
#include <stdint.h>

int Sexy::Rand(int range)
{
	uintptr_t func = 0x5AF400;
	int result;
	_asm
	{
		mov eax, range;
		call func;
		mov result, eax;
	}
	return result;
}

float Sexy::Rand(float range)
{
	uintptr_t func = 0x5AF410;
	float result;
	_asm
	{
		push range;
		call func;
		add esp, 0x4;
		fstp result;
	}
	return result;
}

float Sexy::RandRangeFloat(float theMin, float theMax)
{
	uintptr_t func = 0x511CB0;
	float result;

	_asm
	{
		push theMax;
		push theMin;
		call func;
		add esp, 0x8;
		fstp result;
	}
	return result;

}