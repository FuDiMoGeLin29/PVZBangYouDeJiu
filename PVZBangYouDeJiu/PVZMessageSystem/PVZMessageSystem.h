#pragma once
#include "../HookAsm/HookAsm.h"
#include <vector>
#include <functional>

using namespace HookAsm;

class PVZMessageSystem
{
public:
	static void Attach();
	static void Post(bool isInBoard, ULONGLONG delayTime, std::function<void()> func);
private:
	static std::vector<std::function<void()>> messages;
	static std::vector<bool> messagesIsInBoard;
	static std::vector<ULONGLONG> messagesPostTime;
	static std::vector<ULONGLONG> messagesDelayTime;
	static void _stdcall LawnApp_UpdateApp_Hook(Register& reg);
};

