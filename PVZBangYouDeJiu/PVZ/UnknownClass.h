#pragma once
#include <stdint.h>

template <size_t _Size>
class alignas(4) UnknownClass {
public:
    uint8_t data[_Size];
};