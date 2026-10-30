#include "DialogButton.h"

Sexy::DialogButton::DialogButton(int theId, ButtonListener* theListener)
{
	uintptr_t func = 0x541080;
	_asm
	{
		push theListener;
		mov ecx, theId;
		push this;
		call func;
	}
}

Sexy::DialogButton::DialogButton(Image* theComponentImage, int theId, ButtonListener* theListener)
{
	uintptr_t func = 0x541080;
	_asm
	{
		push theListener;
		mov ecx, theId;
		push this;
        call func;
	}
	mComponentImage = theComponentImage;
}
