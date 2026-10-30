#include "LawnCommon.h"

Sexy::Checkbox* MakeNewCheckbox(int theId, Sexy::CheckboxListener* theListener, bool theDefault)
{
    uintptr_t func = 0x456860;
    Sexy::Checkbox* result;
    _asm
    {
        push theDefault;
        push theListener;
        push theId;
        call func;
        add esp, 0xC;
        mov result, eax;
    }
    return result;
}
