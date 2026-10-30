#include "ListWidget.h"

Sexy::ListWidget::ListWidget(int theId, Font* theFont, ListListener* theListListener)
{
	uintptr_t func = 0x53AC70;

	_asm
	{
		push theListListener;
		push this;
		call func;
	}
	mId = theId;
	if (theFont != NULL)
		mItemHeight = theFont->GetHeight();
	mFont = theFont;
}
