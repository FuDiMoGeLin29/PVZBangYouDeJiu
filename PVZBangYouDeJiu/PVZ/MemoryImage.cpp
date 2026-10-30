#include "MemoryImage.h"
#include "../PtrAPI.h"

void Sexy::MemoryImage::SetBits(unsigned long* theBits, int theWidth, int theHeight, bool commitBits)
{
	uintptr_t func = ReadPtr(uintptr_t, ReadPtr(uintptr_t, this) + 0x74);

	_asm
	{
		push commitBits;;
		push theHeight;
		push theWidth;
		push theBits;
		mov ecx, this;
		call func;
	}
}
