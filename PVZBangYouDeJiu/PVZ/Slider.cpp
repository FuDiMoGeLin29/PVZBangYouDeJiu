#include "Slider.h"

Sexy::Slider::Slider(int theId, SliderListener* theListener)
{
	uintptr_t func = 0x53A510;
	_asm
	{
		push theListener;
		push theId;
		mov esi, this;
		call func;
	}
}
