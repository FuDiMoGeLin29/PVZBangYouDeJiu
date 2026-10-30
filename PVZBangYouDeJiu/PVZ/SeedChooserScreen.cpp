#include "SeedChooserScreen.h"

bool SeedChooserScreen::DisplayRepickWarningDialog(const char* theMessage)
{
    uintptr_t func = 0x485340;
    bool result;

    _asm
    {
        mov eax, theMessage;
        mov ecx, this;
        call func;
        mov result, al;
    }
    return result;
}

bool SeedChooserScreen::PickedPlantType(SeedType theSeedType)
{
    uintptr_t func = 0x486CE0;
    bool result;

    _asm
    {
        mov edi, theSeedType;
        mov ecx, this;
        call func;
        mov result, al;
    }
    return result;
}
