#include "Checkbox.h"

Sexy::Checkbox::Checkbox(int theId, CheckboxListener* theCheckboxListener)
{
	uintptr_t func = 0x53EF50;

	_asm
	{
		push theCheckboxListener;
		push theId;
		mov esi, this;
		call func;
	}
}

Sexy::Checkbox::Checkbox(Image* theUncheckedImage, Image* theCheckedImage, int theId, CheckboxListener* theCheckboxListener)
{
	uintptr_t func = 0x53EF50;

	_asm
	{
		push theCheckboxListener;
		push theId;
		mov esi, this;
		call func;
	}
	mUncheckedImage = theUncheckedImage;
	mCheckedImage = theCheckedImage;
}
