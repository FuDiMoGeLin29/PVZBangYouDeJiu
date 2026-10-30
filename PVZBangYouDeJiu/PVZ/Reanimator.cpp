#include "Reanimator.h"
#include <stdint.h>

ReanimationParams*& gReanimationParamArray = *(ReanimationParams**)0x6A9EF0;
int& gReanimationParamArraySize = *(int*)0x6A9EEC;

void Reanimation::SetImageOverride(const char* theTrackName, Sexy::Image* theImage)
{
	uintptr_t func = 0x473490;

	_asm
	{
		push theImage;
		mov eax, theTrackName;
		mov ecx, this;
		call func;
	}
}

void Reanimation::SetFramesForLayer(const char* theTrackName)
{
	uintptr_t func = 0x473280;

	_asm
	{
		push theTrackName;
		mov ecx, this;
		call func;
	}
}

void Reanimation::ReanimationDie()
{
	uintptr_t func = 0x4733F0;

	_asm
	{
		mov ecx, this;
		call func;
	}
}

bool Reanimation::IsAnimPlaying(const char* theTrackName)
{
	uintptr_t func = 0x4745B0;
	bool result = false;

	_asm
	{
		mov edx, theTrackName
		mov esi, this;
		call func;
		mov result, al;
	}
	return result;
}

void Reanimation::PlayReanim(const char* theTrackName, ReanimLoopType theLoopType, int theBlendTime, float theAnimRate)
{
	uintptr_t func = 0x473BF0;

	_asm
	{
		push theAnimRate;
		push theLoopType;
		mov eax, theBlendTime;
		push theTrackName;
		mov esi, this;
		call func;
	}
}

//ÖØÐ´¶¯»­¾ØÕó²Ù×÷
void Reanimation::SetPosition(float theX, float theY)
{
	mOverlayMatrix.m02 = theX;
	mOverlayMatrix.m12 = theY;
}

void Reanimation::OverrideScale(float theScaleX, float theScaleY)
{
	mOverlayMatrix.m00 = theScaleX;
	mOverlayMatrix.m11 = theScaleY;
}

void Reanimation::OverrideScaleByMultiplier(float theScaleXMultiplier, float theScaleYMultiplier)
{
	OverrideScale(mOverlayMatrix.m00 * theScaleXMultiplier, mOverlayMatrix.m11 * theScaleYMultiplier);
}

int Reanimation::FindTrackIndex(const char* theTrackName)
{
	uintptr_t func = 0x472F30;
	int result;

	_asm
	{
		push theTrackName
		mov ebx, this;
		call func;
		mov result, eax;
	}
	return result;
}

void Reanimation::AssignRenderGroupToTrack(const char* theTrackName, int theRenderGroup)
{
	uintptr_t func = 0x4739E0;

	_asm
	{
		push theRenderGroup;
		push theTrackName;
		mov ebx, this;
		call func;
	}
}

void Reanimation::AssignRenderGroupToPrefix(const char* theTrackName, int theRenderGroup)
{
	uintptr_t func = 0x473A40;

	_asm
	{
		push theRenderGroup;
		push theTrackName;
		push this;
		call func;
	}
}

ReanimatorTrackInstance* Reanimation::GetTrackInstanceByName(const char* theTrackName)
{
	return &mTrackInstances[FindTrackIndex(theTrackName)];
}

bool Reanimation::ShouldTriggerTimedEvent(float theEventTime)
{
	uintptr_t func = 0x473B70;
	bool result = false;

	_asm
	{
		push theEventTime;
		mov ecx, this;
		call func;
		mov result, al;
	}
	return result;
}

void Reanimation::GetTrackMatrix(int theTrackIndex, Sexy::SexyTransform2D& theMatrix)
{
	uintptr_t func = 0x472C00;

	_asm
	{
		push theMatrix;
		mov eax, theTrackIndex;
		push this;
		call func
	}
}

bool Reanimation::TrackExists(const char* theTrackName)
{
    bool result;
	uintptr_t func = 0x4732C0;

	_asm
	{
		push theTrackName;
		mov ebx, this;
		call func;
		mov result, al;
	}
	return result;
}

Reanimation* ReanimationHolder::AllocReanimation(float theX, float theY, int theRenderOrder, ReanimationType theReanimationType)
{
    Reanimation* result;
	uintptr_t func = 0x473590;

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
