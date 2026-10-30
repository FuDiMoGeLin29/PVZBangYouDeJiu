#include "LawnApp.h"
#include "EffectSystem.h"
#include <stdint.h>
#include "../PtrAPI.h"
//#include "../PVZMessageSystem/PVZMessageSystem.h"
//#include "../ConsoleInterface.h"

ReanimationParams* gLawnReanimationArray = (ReanimationParams*)0x6A1340;

ReanimationID LawnApp::ReanimationGetID(Reanimation* theReanimation)
{
	ReanimationID result = (ReanimationID)((unsigned int*)theReanimation)[(sizeof(Reanimation) + 4) / 4 - 1];
	//(ReanimationID)mEffectSystem->mReanimationHolder->mReanimations.DataArrayGetID(theReanimation)
	return result;
}

Reanimation* LawnApp::ReanimationTryToGet(ReanimationID theReanimationID)
{
	uintptr_t func = 0x453CB0;
	Reanimation* result;

	_asm
	{
		mov ecx, theReanimationID;
		mov eax, this;
		call func;
		mov result, eax;
	}
	return result;
}

Reanimation* LawnApp::AddReanimation(float theX, float theY, int theRenderOrder, ReanimationType theReanimationType)
{
	uintptr_t func = 0x453C30;
	Reanimation* result;

	_asm
	{
		mov ebx, theReanimationType;
		push theRenderOrder;
		push theY;
		push theX;
		mov eax, this;
		call func;
		mov result, eax;
	}
	return result;
}

TodParticleSystem* LawnApp::AddTodParticle(float theX, float theY, int theRenderOrder, ParticleEffect theEffect)
{
	uintptr_t func = 0x453C80;
	TodParticleSystem* result;

	_asm
	{
		push theY;
		push theX;
		mov eax, theEffect;
		mov ecx, theRenderOrder;
		mov edx, this;
		call func;
		mov result, eax;
	}
	return result;
}

void LawnApp::PlayFoley(FoleyType theFoleyType)
{
	uintptr_t func = 0x453630;

	_asm
	{
		mov esi, theFoleyType;
		mov eax, this;
		call func;
	}
}

//void LawnApp::PlaySample(int theSoundNum)
//{
//	uintptr_t func = ReadPtr(uintptr_t, ReadPtr(uintptr_t, this) + 0xD8);
//	_asm
//	{
//		push theSoundNum;
//		mov ecx, this;
//		call func;
//	}
//}

void LawnApp::SetCursor(int theCursorNum)
{
	uintptr_t func = 0x5548C0;
	_asm
	{
		mov eax, theCursorNum;
		mov ecx, this;
		call func;
	}
}

void LawnApp::PlayFoleyPitch(FoleyType theFoleyType, float thePitch)
{
	uintptr_t func = 0x453650;

	_asm
	{
		push thePitch;
		mov eax, theFoleyType;
		mov ecx, this;
		call func;
	}
}

void LawnApp::DoBackToMain()
{
	uintptr_t func = 0x44FEB0;

	_asm
	{
		mov eax, this;
		call func;
	}
}

bool LawnApp::IsWallnutBowlingLevel()
{
	uintptr_t func = 0x453840;
	bool result = false;

	_asm
	{
		mov ecx, this;
		call func;
		mov result, al;
	}
	return result;
}

bool LawnApp::HasFinishedAdventure()
{
	uintptr_t func = 0x454170;
	bool result;
	_asm
	{
		mov eax, this;
		call func;
        mov result, al;
	}
	return result;
}
bool LawnApp::IsFirstTimeAdventureMode()
{
	uintptr_t func = 0x454190;
	bool result;

	_asm
	{
		mov eax, this;
		call func;
		mov result, al;
	}
	return result;
}

void LawnApp::KillGameSelector()
{
	uintptr_t func = 0x44F9E0;

	_asm
	{
		mov esi, this;
		call func;
	}
}

int LawnApp::LawnMessageBox(int theDialogId, const SexyChar* theHeaderName, const SexyChar* theLinesName, const SexyChar* theButton1Name, const SexyChar* theButton2Name, int theButtonMode)
{
	uintptr_t func = 0x4504B0;
	int result;
	_asm
	{
		push theButtonMode;
		push theButton2Name;
		push theButton1Name;
		push theLinesName;
		push theHeaderName;
		push theDialogId;
		push this;
		call func;
		mov result, eax;
	}
	return result;
}
