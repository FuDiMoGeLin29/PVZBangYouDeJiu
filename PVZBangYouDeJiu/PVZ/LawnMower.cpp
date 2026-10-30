#include "LawnMower.h"

void LawnMower::LawnMowerInitialize(int theRow)
{
	uintptr_t func = 0x458000;

	_asm
	{
		mov eax, theRow;
		push this;
		call func;
	}
}
