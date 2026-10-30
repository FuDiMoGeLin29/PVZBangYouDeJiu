#include "PakInterface.h"
#include <stdint.h>

bool PakInterface::AddPakFile(const std_string_PVZ& theFileName)
{
	uintptr_t func = 0x5D7D90;
	bool result;

	_asm
	{
		mov ecx, theFileName;
		call func;
		mov result, al;
	}
    return result;
}
