#include "Widget.h"
#include "../PtrAPI.h"

Sexy::Widget::Widget()
{
	uintptr_t func = 0x5396F0;

	_asm
	{
		push this;
		call func;
	}
}

//Sexy::Widget::~Widget()
//{
//	uintptr_t func = 0x5397A0;
//
//	_asm
//	{
//		mov ecx, this;
//		call func;
//	}
//}