#include "Buffer.h"

const unsigned char* Sexy::Buffer::GetDataPtr() const
{
    uintptr_t func = 0x5D6990;

    _asm
    {
        mov esi, this;
        call func;
    }
}
