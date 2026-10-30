#include "PVZMessageSystem.h"
#include "../PVZ/PVZ.h"

std::vector<std::function<void()>> PVZMessageSystem::messages;
std::vector<bool> PVZMessageSystem::messagesIsInBoard;
std::vector<ULONGLONG> PVZMessageSystem::messagesPostTime;
std::vector<ULONGLONG> PVZMessageSystem::messagesDelayTime;

void _stdcall PVZMessageSystem::LawnApp_UpdateApp_Hook(Register& reg)
{
	LawnApp* lawnApp = (LawnApp*)reg.ecx;
	for (size_t i = 0; i < messages.size(); i++)
	{
		if (messagesIsInBoard[i])
		{
			if (lawnApp->mBoard && (GetTickCount64() - messagesPostTime[i]) >= messagesDelayTime[i])
			{
				(messages[i])();
				messages.erase(messages.begin() + i);
				i--;
			}
			else
			{
				messages.erase(messages.begin() + i);
				i--;
			}
		}
		else
		{
			if ((GetTickCount64() - messagesPostTime[i]) >= messagesDelayTime[i])
			{
				(messages[i])();
				messages.erase(messages.begin() + i);
				i--;
			}
		}
	}
}

void PVZMessageSystem::Attach()
{
	HookBegin((LPVOID)0x453A50, LawnApp_UpdateApp_Hook);
}

void PVZMessageSystem::Post(bool isInBoard, ULONGLONG delayTime, std::function<void()> func)
{
	messagesIsInBoard.push_back(isInBoard);
	messagesPostTime.push_back(GetTickCount64());
	messagesDelayTime.push_back(delayTime);
	messages.push_back(func);
}
