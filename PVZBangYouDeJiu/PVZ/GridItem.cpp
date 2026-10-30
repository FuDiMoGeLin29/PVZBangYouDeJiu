#include "GridItem.h"
#include <stdint.h>

void GridItem::GridItemDie()
{
	uintptr_t func = 0x44D000;

	_asm
	{
		mov esi, this;
		call func;
	}
}