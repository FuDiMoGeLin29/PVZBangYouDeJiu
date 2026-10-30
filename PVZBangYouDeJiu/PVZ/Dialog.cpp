#include "Dialog.h"

void Sexy::Dialog::EnsureFonts()
{
	uintptr_t func = 0x5405F0;

	_asm
	{
		push this;
		call func;
	}
}

Sexy::Dialog::Dialog(int theId, bool isModal, const SexyString& theDialogHeader, const SexyString& theDialogLines, const SexyString& theDialogFooter, int theButtonMode)
{
	uintptr_t func = 0x53FE40;

	_asm
	{
		push theButtonMode;
		push theDialogFooter;
		push theDialogLines;
		push theDialogHeader;
		push isModal;
		push theId;
		push this;
		call func;
	}
}

//Sexy::Dialog::~Dialog()
//{
//	uintptr_t func = 0x540380;
//
//	_asm
//	{
//		mov ecx, this;
//		call func;
//	}
//}
