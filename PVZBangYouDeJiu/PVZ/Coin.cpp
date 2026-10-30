#include "Coin.h"
#include <stdint.h>

void Coin::Collect()
{
	uintptr_t func = 0x432060;

	_asm
	{
		mov ecx, this;
		call func;
	}
}

int Coin::GetCoinValue(CoinType theCoinType)
{
	uintptr_t func = 0x4329D0;
	int result;

	_asm
	{
		mov eax, theCoinType;
		call func;
		mov result, eax;
	}

	return result;
}

bool Coin::IsMoney()
{
	uintptr_t func = 0x430970;
	bool result;

	_asm
	{
		mov eax, this;
		call func;
		mov result, al;
	}

	return result;
}

bool Coin::IsSun()
{
	uintptr_t func = 0x430990;
	bool result;

	_asm
	{
		mov eax, this;
		call func;
		mov result, al;
	}

	return result;
}

bool Coin::IsLevelAward()
{
	uintptr_t func = 0x432F80;
	bool result;

	_asm
	{
		mov eax, this;
		call func;
		mov result,al;
	}

	return result;
}
