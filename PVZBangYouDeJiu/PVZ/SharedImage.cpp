#include "SharedImage.h"

Sexy::SharedImageRef::SharedImageRef()
{
	uintptr_t func = 0x59A8B0;
	_asm
	{
		mov eax, this;
		call func;
	}
}

Sexy::SharedImageRef::~SharedImageRef()
{
	uintptr_t func = 0x59A8C0;
	_asm
	{
		mov esi, this;
		call func;
	}
}
