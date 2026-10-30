#include "Image.h"
#include <stdint.h>
#include "../PtrAPI.h"

int Sexy::Image::GetWidth()
{
    uintptr_t func = 0x588A10;
    int result;
    _asm
    {
        mov eax, this;
        call func;
        mov result, eax;
    }
    return result;
}

int Sexy::Image::GetHeight()
{
    uintptr_t func = 0x588A20;
    int result;
    _asm
    {
        mov eax, this;
        call func;
        mov result, eax;
    }
    return result;
}

int Sexy::Image::GetCelWidth()
{
    uintptr_t func = 0x588A40;
    int result;
    _asm
    {
        mov ecx, this;
        call func;
        mov result, eax;
    }
    return result;
}

int Sexy::Image::GetCelHeight()
{
    uintptr_t func = 0x588A30;
    int result;
    _asm
    {
        mov ecx, this;
        call func;
        mov result, eax;
    }
    return result;
}

void Sexy::Image::BltMirror(Image* theImage, int theX, int theY, const Sexy::Rect& theSrcRect, const Sexy::Color& theColor, int theDrawMode)
{
    uintptr_t func = ReadPtr(uintptr_t, ReadPtr(uintptr_t, this) + 0x3C);

    _asm
    {
        push theDrawMode;
        push theColor;
        push theSrcRect;
        push theY;
        push theX;
        push theImage;
        mov ecx, this;
        call func;
    }
}
