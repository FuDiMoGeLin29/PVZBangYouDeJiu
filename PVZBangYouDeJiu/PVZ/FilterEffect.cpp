#include "FilterEffect.h"

Sexy::Image* FilterEffectGetImage(Sexy::Image* theImage, FilterEffect theFilterEffect)
{
    Sexy::Image* result;
    uintptr_t func = 0x447340;

    _asm
    {
        mov eax, theFilterEffect;
        push theImage;
        call func;
        add esp, 0x4;
        mov result, eax;
    }
    return result;
}
