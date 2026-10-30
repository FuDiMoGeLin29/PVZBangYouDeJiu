#include "SaveGame.h"

void SaveGameContext::SyncBytes(void* theDest, int theReadSize)
{
	uintptr_t func = 0x4813D0;
	_asm
	{
		mov esi, theReadSize;
		mov eax, theDest;
		mov ecx, this;
		call func;
	}
}

void SaveGameContext::SyncInt(int& theInt)
{
	uintptr_t func = 0x481470;
	int* thePtr = &theInt;
	_asm
	{
		mov esi, thePtr;
		mov eax, this;
		call func;
	}
}
