#include "WidgetManager.h"
#include "../PtrAPI.h"

Sexy::WidgetManager::WidgetManager(SexyAppBase* theApplet)
{
	uintptr_t func = 0x5384A0;

	_asm
	{
		push theApplet;
		push this;
		call func;
	}
}

Sexy::WidgetManager::~WidgetManager()
{
	uintptr_t func = 0x538610;

	_asm
	{
		push this;
        call func;
	}
}
