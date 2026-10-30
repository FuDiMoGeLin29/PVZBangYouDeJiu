#pragma once
#include <Windows.h>
//#include <iostream>
#include <array>

template<typename T>
void WriteMemoryType(DWORD address, const T& val)
{
	DWORD oldProtect;
	VirtualProtect((LPVOID)address, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)address, &val, sizeof(T));
	VirtualProtect((LPVOID)address, sizeof(T), oldProtect, &oldProtect);
}

template<typename T>
T ReadMemoryType(DWORD address)
{
	T result = T();
	memcpy(&result, (void*)address, sizeof(T));
	return result;
}

template<typename T, size_t _Size>
void WriteMemoryArray(DWORD address, const T(&buffer)[_Size])
{
	DWORD oldProtect;
	VirtualProtect((LPVOID)address, sizeof(T) * _Size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)address, &buffer, sizeof(T) * _Size);
	VirtualProtect((LPVOID)address, sizeof(T) * _Size, oldProtect, &oldProtect);
}

template<typename T, size_t _Size>
void ReadMemoryArray(DWORD address, T(&buffer)[_Size])
{
	memcpy(&buffer, (void*)address, sizeof(T) * _Size);
}