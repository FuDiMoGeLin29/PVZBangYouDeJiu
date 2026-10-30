#include "WidgetContainer.h"

Sexy::WidgetContainer::WidgetContainer()
{
	uintptr_t func = 0x536F00;

	_asm
	{
		mov esi, this;
		call func;
	}
}

//Sexy::WidgetContainer::~WidgetContainer()
//{
//	uintptr_t func = 0x536F80;
//
//	_asm
//	{
//		mov ecx, this;
//		call func;
//	}
//}
