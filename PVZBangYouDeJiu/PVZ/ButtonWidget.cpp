#include "ButtonWidget.h"

bool Sexy::ButtonWidget::IsMouseOver()
{
	return mIsOver && !mDisabled && !mBtnNoDraw;
}

Sexy::ButtonWidget::ButtonWidget(int theId, ButtonListener* theButtonListener)
{
	uintptr_t func = 0x53F200;

	_asm
	{
		push theButtonListener;
		push theId;
		push this;
        call func;
	}
}
