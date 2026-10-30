#include "SeedPacket.h"

void SeedPacket::WasPlanted()
{
	uintptr_t func = 0x488EC0;

	_asm
	{
		mov eax, this;
		call func;
	}
}
