#include "ResourceManager.h"
#include "../PtrAPI.h"

Sexy::SharedImageRef Sexy::ResourceManager::GetImageThrow(const std_string_PVZ& theId)
{
	uintptr_t func = ReadPtr(uintptr_t, ReadPtr(uintptr_t, this) + 0x40);
	Sexy::SharedImageRef result;
	Sexy::SharedImageRef* pImage = &result;
	_asm
	{
		push theId;
		push pImage;
		mov ecx, this;
		call func;
	}
	return result;
}

bool Sexy::ResourceManager::ParseResourcesFile(const std_string_PVZ& theFilename)
{
	uintptr_t func = 0x5B6A20;
	bool result;

	_asm
	{
		mov ecx, theFilename;
		push this;
        call func;
        mov result, al;
	}
    return result;
}
