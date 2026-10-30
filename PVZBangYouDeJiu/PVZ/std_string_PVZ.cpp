#include "std_string_PVZ.h"

std_string_PVZ::std_string_PVZ()
{
	uintptr_t func = 0x404400;

	_asm
	{
		mov ecx, this;
		call func;
	}
}


std_string_PVZ::std_string_PVZ(const char* _Ptr)
{
	uintptr_t func = 0x404450;

	_asm
	{
		push _Ptr;
		mov ecx, this;
		xor eax, eax;
		mov[ecx + 0x04], al;
		mov[ecx + 0x14], eax;
		mov[ecx + 0x18], 0x0F;
		call func;
	}
}

//std_string_PVZ::std_string_PVZ(const std::string& str)
//{
//	std_string_PVZ(str.c_str());
//}

std_string_PVZ::~std_string_PVZ()
{
	uintptr_t func = 0x404420;

	_asm
	{
		mov ecx, this;
		call func;
	}
}

void std_string_PVZ::append(const char* _Ptr, unsigned int _Count)
{
	uintptr_t func = 0x41E3E0;

	_asm
	{
		push _Count;
		push _Ptr;
		mov ecx, this;
		call func;
	}
}

void std_string_PVZ::append(const char* _Ptr)
{
	append(_Ptr, strlen(_Ptr));
}

const char* std_string_PVZ::c_str() const
{
	uintptr_t func = 0x4042D0;
	const char* result;
	_asm
	{
		mov ecx, this;
		call func;
		mov result, eax;
	}
    return result;
}

_NODISCARD bool operator<(
	const std_string_PVZ& _Left, const std_string_PVZ& _Right) noexcept
{
	return std::string(_Left.c_str(), _Left._Mysize) < std::string(_Right.c_str(), _Left._Mysize);
}