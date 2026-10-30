#include "Board.h"
#include "Zombie.h"
#include "Lawncommon.h"
#include <stdint.h>
#include "../HookAsm/HookAsm.h"
using namespace HookAsm;

void Zombie::ZombieInitialize(int theRow, ZombieType theType, bool theVariant, Zombie* theParentZombie, int theFromWave)

{
	uintptr_t func = 0x522580;

	_asm
	{
		push theFromWave;
		push theParentZombie;
		push theVariant;
		push theType;
		mov eax, theRow;
		push this;
		call func;
	}
}

void Zombie::DieNoLoot()
{
	uintptr_t func = 0x530510;

	_asm
	{
		mov ecx, this;
		call func;
	}
}

void Zombie::DieWithLoot()
{
	uintptr_t func = 0x5302F0;

	_asm
	{
		mov ecx, this;
		call func;
	}
}

void Zombie::TakeDamage(int theDamage, unsigned int theDamageFlags)
{
	uintptr_t func = 0x5317C0;
	_asm
	{
		mov eax, theDamageFlags;
		push theDamage;
		mov esi, this;
		call func;
	}
}

float Zombie::GetPosYBasedOnRow(int theRow)
{
	uintptr_t func = 0x531880;
	float result;

	_asm
	{
		push theRow;
		mov eax, this;
		call func;
		fstp result;
	}
	return result;
}

bool Zombie::EffectedByDamage(unsigned int theDamageRangeFlags)
{
	uintptr_t func = 0x531A80;
	bool result;

	_asm
	{
		push theDamageRangeFlags;
		mov esi, this;
		call func;
		mov result, al;
	}
	return result;
}

void Zombie::PickRandomSpeed()
{
	uintptr_t func = 0x524A70;

	_asm
	{
		mov eax, this;
		call func;
	}
}

void Zombie::GetDrawPos(ZombieDrawPosition& theDrawPos)
{
	uintptr_t func = 0x52D9E0;

	_asm
	{
		mov esi, theDrawPos;
		mov ecx, this;
		call func;
	}
}

bool Zombie::IsOnHighGround()
{
	uintptr_t func = 0x52F9C0;
	bool result;

	_asm
	{
		push this;
		call func;
		mov result, al;
	}
	return result;
}

void Zombie::StartZombieSound()
{
	uintptr_t func = 0x530770;

	_asm
	{
		mov esi, this;
		call func;
	}
}

void Zombie::StopZombieSound()
{
	uintptr_t func = 0x530850;

	_asm
	{
		push this;
		call func;
	}
}

Sexy::Rect Zombie::GetZombieRect()
{
	uintptr_t func = 0x5320B0;
	Sexy::Rect result;
	Sexy::Rect* pResult = &result;
	_asm
	{
		mov edi, pResult;
		mov ebx, this;
		call func;
	}
	return result;
}

void Zombie::OverrideParticleScale(TodParticleSystem* aParticle)
{
	uintptr_t func = 0x5297F0;

	_asm
	{
		mov edx, aParticle;
		mov eax, this;
		call func;
	}
}

void Zombie::PoolSplash(bool theInToPoolSound)
{
	uintptr_t func = 0x52F6D0;
	_asm
	{
		push theInToPoolSound;
		mov eax, this;
		call func;
	}
}

void Zombie::HitIceTrap()
{
	uintptr_t func = 0x5323C0;

	_asm
	{
		mov eax, this;
		call func;
	}
}

void Zombie::StartEating()
{
	uintptr_t func = 0x52F250;
	_asm
	{
		mov eax, this;
		call func;
	}
}

void Zombie::StopEating()
{
	uintptr_t func = 0x52F440;

	_asm
	{
		mov edi, this;
		call func;
	}
}

void Zombie::UpdateAnimSpeed()
{
	uintptr_t func = 0x52F050;

	_asm
	{
		mov esi, this;
		call func;
	}
}

void Zombie::ReanimShowPrefix(const char* theTrackPrefix, int theRenderGroup)
{
	uintptr_t func = 0x5331C0;

	_asm
	{
		push theRenderGroup;
		push theTrackPrefix;
		mov eax, this;
		call func;
	}
}

void Zombie::GetTrackPosition(const char* theTrackName, float& thePosX, float& thePosY)
{
	uintptr_t func = 0x5345F0;

	FXSAVE_Area fxsave_area = Asm_Fxsave();
	_asm
	{
		mov edi, thePosY;
		push thePosX;
		push theTrackName;
		mov esi, this;
		call func;
	}
	Asm_Fxrstor(fxsave_area);
}

void Zombie::StartMindControlled()
{
	uintptr_t func = 0x52FA60;

	_asm
	{
		mov esi, this;
		call func;
	}
}

bool Zombie::IsFlying()
{
	uintptr_t func = 0x534680;
	bool result;

	_asm
	{
		mov eax, this;
		call func;
		mov result, al;
	}
	return result;
}

void Zombie::ApplyBurn()
{
	uintptr_t func = 0x532B70;

	_asm
	{
		mov ecx, this;
		call func;
	}
}

void Zombie::PlayZombieReanim(const char* theTrackName, ReanimLoopType theLoopType, int theBlendTime, float theAnimRate)
{
	uintptr_t func = 0x528B00;

	_asm
	{
		push theAnimRate;
		push theBlendTime;
		push theLoopType;
		push theTrackName;
		mov edi, this;
		call func;
	}
}

void Zombie::StartWalkAnim(int theBlendTime)
{
	uintptr_t func = 0x52F2E0;

	_asm
	{
		mov esi, theBlendTime;
		mov eax, this;
		call func;
	}
}

Reanimation* Zombie::AddAttachedReanim(int thePosX, int thePosY, ReanimationType theReanimType)
{
	uintptr_t func = 0x5322C0;
	Reanimation* result = nullptr;

	_asm
	{
		push thePosY;
		push thePosX;
		mov edx, theReanimType;
		mov esi, this;
		call func;
		mov result, eax;
	}
	return result;
}

void Zombie::DragUnder()
{
	mZombieHeight = ZombieHeight::HEIGHT_DRAGGED_UNDER;
	StopEating();
	ReanimReenableClipping();
}

bool Zombie::IsOnBoard()
{
	uintptr_t func = 0x52AE40;
	bool result;

	_asm
	{
		mov eax, this;
		call func;
		mov result, al;
	}
	return result;
}

void Zombie::ApplyButter()
{
	uintptr_t func = 0x5326D0;

	_asm
	{
		mov eax, this;
		call func;
	}
}

float Zombie::ZombieTargetLeadX(float theTime)
{
	uintptr_t func = 0x52A580;
	float result;
	_asm
	{
		push theTime;
		mov eax, this;
		call func;
		fstp result;
	}
	return result;
}

int Zombie::GetBobsledPosition()
{
	uintptr_t func = 0x5346A0;
	int result;
	_asm
	{
		mov ecx, this;
		call func;
		mov result, eax;
	}
	return result;
}

bool Zombie::IsBobsledTeamWithSled()
{
	return GetBobsledPosition() != -1;
}

bool Zombie::CanBeFrozen()
{
	uintptr_t func = 0x531A10;
	bool result;
	_asm
	{
		mov eax, this;
		call func;
		mov result, al;
	}
	return result;
}

void Zombie::SetAnimRate(float theAnimRate)
{
	uintptr_t func = 0x52EFD0;

	_asm
	{
		push theAnimRate;
		mov eax, this;
		call func;
	}
}

bool Zombie::IsDeadOrDying()
{
	uintptr_t func = 0x534700;
	bool result;
	_asm
	{
		mov eax, this;
		call func;
		mov result, al;
	}
	return result;
}

void Zombie::ReanimReenableClipping()
{
	uintptr_t func = 0x524310;

	_asm
	{
		mov eax, this
		call func;
	}
}

void Zombie::BossDestroyIceballInRow(int theRow)
{
	uintptr_t func = 0x535630;
	if (mFireballRow != theRow)
	{
		return;
	}

	_asm
	{
		mov eax, this;
		call func
	}
}

void Zombie::RemoveColdEffects()
{
	uintptr_t func = 0x532B40;

	_asm
	{
		mov eax, this;
		call func;
	}
}

bool Zombie::IsTangleKelpTarget()
{

	if (!mBoard)
	{
		return false;
	}

	uintptr_t func = 0x5324B0;
	bool result;
	_asm
	{
		mov edi, this;
		call func;
		mov result, al;
	}
	return result;
}

void Zombie::RemoveButter()
{
	uintptr_t func = 0x532570;

	_asm
	{
		mov eax, this;
		call func;
	}
}

void Zombie::BalloonPropellerHatSpin(bool theSpinning)
{
	uintptr_t func = 0x532510;

	_asm
	{
		push theSpinning;
		mov eax, this;
		call func;
	}
}

bool Zombie::IsImmobilized()
{
	uintptr_t func = 0x52EEF0;
	bool result;
	_asm
	{
		mov eax, this;
		call func;
		mov result, al;
	}
	return result;
}

bool Zombie::IsZombotany(ZombieType theZombieType)
{
	return
		theZombieType == ZombieType::ZOMBIE_PEA_HEAD ||
		theZombieType == ZombieType::ZOMBIE_WALLNUT_HEAD ||
		theZombieType == ZombieType::ZOMBIE_TALLNUT_HEAD ||
		theZombieType == ZombieType::ZOMBIE_JALAPENO_HEAD ||
		theZombieType == ZombieType::ZOMBIE_GATLING_HEAD ||
		theZombieType == ZombieType::ZOMBIE_SQUASH_HEAD;
}

bool Zombie::IsOntheGridX(int theGridX, int theGridXExWidth)
{
	/*if (theGridX<0 || theGridX>MAX_GRID_SIZE_X)
	{
		return false;
	}*/
	if (this->mZombieType == ZOMBIE_BUNGEE)
	{
		return this->mTargetCol >= theGridX && this->mTargetCol <= theGridX + theGridXExWidth;
	}
	Sexy::Rect GridXRect(mBoard->GridToPixelX(theGridX, mRow), 0, theGridXExWidth * LAWN_GRIDXWIDTH + LAWN_GRIDXWIDTH, 0);
	Sexy::Rect ZombieRect = this->GetZombieRect();
	return (GetRectOverlap(GridXRect, ZombieRect) > 0);
}

ZombieDefinition& GetZombieDefinition(ZombieType theZombieType)
{
	// TODO: 在此处插入 return 语句
	return *(ZombieDefinition*)(0x69DA80 + sizeof(ZombieDefinition) * theZombieType);
}
