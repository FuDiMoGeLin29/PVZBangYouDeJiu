#pragma once

template <class _T, class _S>
_T AutoTo(_S theSource)
{
	return reinterpret_cast<_T>(theSource);
}

template <unsigned int theTargetOffset>
class ImitateClass
{
private:
	unsigned char mNone[theTargetOffset];
	void* mGet;
public:
	template <class _T>
	_T Get()
	{
		return AutoTo<_T>(mGet);
	}
};

void Asm_Fstp();