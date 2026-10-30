#include "SexyAppBase.h"

namespace Sexy
{ 

	bool SexyAppBase::RegistryWriteInteger(const std_string_PVZ& theValueName, int theValue)
	{
		uintptr_t func = 0x549900;
		bool result = false;

		_asm
		{
			push theValue;
			mov ebx, theValueName;
			mov ecx, this;
			call func;
			mov result, al;
		}
		return result;
	}

	bool SexyAppBase::RegistryWriteBoolean(const std_string_PVZ& theValueName, bool theValue)
	{
		uintptr_t func = 0x549920;
		bool result = false;

		_asm
		{
			push theValue;
			mov ebx, theValueName;
			mov edx, this;
			call func;
			mov result, al;
		}
		return result;
	}

	bool SexyAppBase::RegistryReadInteger(const std_string_PVZ& theValueName, int* theValue)
	{
		uintptr_t func = 0x54A3F0;
		bool result = false;

		_asm
		{
			push theValue;
			push theValueName;
			mov edx, this;
			call func;
			mov result, al;
		}
		return result;
	}

	bool SexyAppBase::RegistryReadBoolean(const std_string_PVZ& theValueName, bool* theValue)
	{
		uintptr_t func = 0x54A440;
		bool result = false;

		_asm
		{
			push theValue;
			mov ecx, theValueName;
			mov edx, this;
			call func;
			mov result, al;
		}
		return result;
	}
	void SexyAppBase::ClearUpdateBacklog()
	{
		uintptr_t func = 0x5456A0;

		_asm
		{
			mov esi, this;
			call func;
		}
	}

	void SexyAppBase::RehupFocus()
	{
		uintptr_t func = 0x54EB80;

		_asm
		{
			mov esi, this;
			call func;
		}
	}

	void SexyAppBase::ClearKeysDown()
	{
		uintptr_t func = 0x54EC20;

		_asm
		{
			mov ecx, this;
			call func;
		}
	}

	bool SexyAppBase::ProcessDeferredMessages(bool singleMessage)
	{
		uintptr_t func = 0x54FD70;
		bool result;

		_asm
		{
			push this;
			call func;
			mov result, al;
		}
		return result;
	}

	void SexyAppBase::UpdateFTimeAcc()
	{
		uintptr_t func = 0x5519F0;

		_asm
		{
			mov esi, this;
			call func;
		}
	}

	void SexyAppBase::LoadingThreadProcStub(void* theArg)
	{
		uintptr_t func = 0x551350;
		_asm
		{
			push theArg;
			call func;
		}
	}

	void SexyAppBase::CursorThreadProc()
	{
		uintptr_t func = 0x551400;

		_asm
		{
			mov esi, this;
			call func;
		}
	}

	void SexyAppBase::CursorThreadProcStub(void* theArg)
	{
		uintptr_t func = 0x551520;

		_asm
		{
			push theArg;
			call func;
		}
	}

	void SexyAppBase::StartCursorThread()
	{
		uintptr_t func = 0x551540;

		_asm
		{
			mov esi, this;
			call func;
		}
	}

	void SexyAppBase::WaitForLoadingThread()
	{
		uintptr_t func = 0x546750;

		_asm
		{
			mov esi, this;
			call func;
		}
	}

	void SexyAppBase::ProcessSafeDeleteList()
	{
		uintptr_t func = 0x5518F0;

		_asm
		{
			mov ecx, this;
			call func;
		}
	}

	void SexyAppBase::RestoreScreenResolution()
	{
		uintptr_t func = 0x54B930;

		_asm
		{
			mov edi, this;
            call func;
		}
	}

	void SexyAppBase::DoExit(int theCode)
	{
		uintptr_t func = 0x54B970;

		_asm
		{
            push theCode;
            mov edi, this;
            call func;
		}
	}

	void SexyAppBase::TakeScreenshot()
	{
		uintptr_t func = 0x546780;

		_asm
		{
			push this;
			call func;
		}
	}

	void SexyAppBase::DumpProgramInfo()
	{
		uintptr_t func = 0x546C40;
		_asm
		{
			push this;
			call func;
		}
	}

	void SexyAppBase::ShowMemoryUsage()
	{
		uintptr_t func = 0x54F0E0;

		_asm
		{
			mov ecx, this;
			call func;
		}
	}

	bool SexyAppBase::RegistryRead(const std_string_PVZ& theValueName, ulong* theType, uchar* theValue, ulong* theLength)
	{
		uintptr_t func = 0x549F50;
		bool result;
		_asm
		{
			push theLength;
			push theValue;
			mov eax, theType;
			mov ecx, theValueName;
			mov edx, this;
			call func;
            mov result, al;
		}
        return result;
	}

	bool SexyAppBase::RegistryReadKey(const std_string_PVZ& theValueName, ulong* theType, uchar* theValue, ulong* theLength, HKEY theMainKey)
	{
		uintptr_t func = 0x549F70;
		bool result;
		_asm
		{
			push theMainKey;
			mov edx, theLength;
			mov ecx, theValue;
			push theType;
			push theValueName;
			push this;
			call func;
            mov result, al;
		}
        return result;
	}

	bool SexyAppBase::RegistryWrite(const std_string_PVZ& theValueName, ulong theType, const uchar* theValue, ulong theLength)
	{
		uintptr_t func = 0x5494F0;
		bool result;

		_asm
		{
			push theLength;
			push theValue;
			push theType;
			mov ebx, theValueName;
			push this;
			call func;
			mov result, al;
		}
        return result;
	}

	void SexyAppBase::ProcessDemo()
	{
		uintptr_t func = 0x54ED70;

		_asm
		{
			push this;
			call func;
		}
	}


}
