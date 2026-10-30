#include "Common.h"
#include <stdint.h>

float RandRangeFloat(float theMin, float theMax)
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
