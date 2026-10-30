#include "AsmExtra.h"

void Asm_Fstp()
{
	_asm
	{
		fstp st(0);
	}
}
