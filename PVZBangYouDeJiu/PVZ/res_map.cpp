#include "res_map.h"
#include <stdint.h>

int* res_map_int_int::op_find(int& _Keyval)
{
    uintptr_t func = 0x47FD90;
    int* result;
    _asm
    {
        mov ebx, _Keyval;
        call func;
        mov result, eax;
    }
    return result;
}
