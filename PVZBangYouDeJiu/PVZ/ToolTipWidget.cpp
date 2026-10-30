#include "ToolTipWidget.h"
#include <stdint.h>

void ToolTipWidget::SetLabel(const SexyString& theLabel)
{
	uintptr_t func = 0x51A8D0;
	_asm
	{
		mov edx, theLabel;
		mov esi, this;
        call func;
	}
}

void ToolTipWidget::SetTitle(const SexyString& theTitle)
{
	uintptr_t func = 0x51A950;
	_asm
	{
		mov edx, theTitle;
		mov esi, this;
		call func;
	}
}
