#include "TodParticle.h"
#include <stdint.h>

void TodParticleSystem::OverrideScale(float theScale)
{
	uintptr_t func = 0x518630;

	_asm
	{
		push theScale;
		mov edx, this;
		call func;
	}
}

void TodParticleSystem::OverrideColor(const char* theEmitterName, const Sexy::Color& theColor)
{
	uintptr_t func = 0x518560;

	_asm
	{
		push theColor;
		mov ebx, theEmitterName;
		push this;
		call func;
	}
}

void TodParticleSystem::OverrideImage(const char* theEmitterName, Sexy::Image* theImage)
{
	for (TodListNode<ParticleEmitterID>* aNode = mEmitterList.mHead; aNode != nullptr; aNode = aNode->mNext)
	{
		TodParticleEmitter* aEmitter = mParticleHolder->mEmitters.DataArrayGet((unsigned int)aNode->mValue);
		if (theEmitterName == nullptr || _stricmp(theEmitterName, aEmitter->mEmitterDef->mName) == 0)
			aEmitter->mImageOverride = theImage;
	}
}

TodParticleSystem* TodParticleHolder::AllocParticleSystem(float theX, float theY, int theRenderOrder, ParticleEffect theParticleEffect)
{
	uintptr_t func = 0x518A70;

	_asm
	{
		push theParticleEffect;
		push theRenderOrder;
		push theY;
		push theX;
		mov esi, this;
		call func;
	}
}
