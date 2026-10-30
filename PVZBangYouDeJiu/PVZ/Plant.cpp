#include "Plant.h"
#include "LawnApp.h"
#include "Board.h"
#include "Coin.h"
#include <stdint.h>

PlantDefinition* gPlantDefs = (PlantDefinition*)0x69F2B0;

Plant::Plant()
{
	uintptr_t func = 0x401B20;

	_asm
	{
		mov eax, this;
		call func;
	}
}

void Plant::PlantInitialize(int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType)
{
	uintptr_t func = 0x45DB60;

	_asm
	{
		push theImitaterType;
		push theSeedType;
		mov eax, theGridY;
		mov ecx, theGridX;
		push this;
		call func;
	}
}

void Plant::Update()
{
	uintptr_t func = 0x463E40;

	_asm
	{
		mov eax, this;
		call func;
	}
}

void Plant::Draw(Sexy::Graphics* g)
{
	uintptr_t func = 0x465A90;

	_asm
	{
		push g;
		push this;
		call func;
	}
}

void Plant::DoSpecial()
{
	uintptr_t func = 0x4666A0;

	_asm
	{
		push this;
		call func;
	}
}

void Plant::Fire(Zombie* theTargetZombie, int theRow, PlantWeapon thePlantWeapon)
{
	uintptr_t func = 0x466E00;
	_asm
	{
		push thePlantWeapon;
		push theRow;
		push theTargetZombie;
		push this;
		call func;
	}
}

Zombie* Plant::FindTargetZombie(int theRow, PlantWeapon thePlantWeapon)
{
	uintptr_t func = 0x4675C0;
	Zombie* result = nullptr;

	_asm
	{
		mov ecx, thePlantWeapon
		push theRow
		push this
		call func
		mov result, eax
	}
	return result;
}

void Plant::Die()
{
	uintptr_t func = 0x4679B0;

	_asm
	{
		push this;
		call func;
	}
}

int Plant::GetCost(SeedType theSeedType, SeedType theImitaterType)
{
	uintptr_t func = 0x467B00;
	int result;

	_asm
	{
		mov eax, theSeedType;
		mov edx, theImitaterType;
		call func;
		mov result, eax;
	}
	return result;
}

std_string_PVZ Plant::GetNameString(SeedType theSeedType, SeedType theImitaterType)
{
	std_string_PVZ result;
	std_string_PVZ* pResult = &result;
	uintptr_t func = 0x467C00;
	_asm
	{
		push theImitaterType;
		push theSeedType;
		push pResult;
		call func;
		add esp, 0xC;
	}
	return result;
}

bool Plant::IsFlying(SeedType theSeedtype)
{
	return theSeedtype == SEED_INSTANT_COFFEE;
}

void Plant::Squish()
{
	uintptr_t func = 0x462B80;

	_asm
	{
		push this;
		call func;
	}
}

int Plant::GetDamageRangeFlags(PlantWeapon thePlantWeapon)
{
	uintptr_t func = 0x45EB10;
	int result;
	_asm
	{
		push thePlantWeapon;
		mov eax, this;
		call func;
		mov result, eax;
	}
	return result;
}

Sexy::Rect Plant::GetPlantRect()
{
	uintptr_t func = 0x467EF0;
	Sexy::Rect result;
	Sexy::Rect* pResult = &result;
	_asm
	{
		mov eax, pResult;
		mov ecx, this;
		call func;
	}
	return result;
}

Sexy::Rect Plant::OriginalGetPlantRect()
{
	Sexy::Rect aRect;
	if (mSeedType == SEED_TALLNUT)
	{
		aRect = Sexy::Rect(mX + 10, mY, mWidth, mHeight);
	}
	else if (mSeedType == SEED_PUMPKINSHELL)
	{
		aRect = Sexy::Rect(mX, mY, mWidth - 20, mHeight);
	}
	else if (mSeedType == SEED_COBCANNON)
	{
		aRect = Sexy::Rect(mX, mY, 140, 80);
	}
	else
	{
		aRect = Sexy::Rect(mX + 10, mY, mWidth - 20, mHeight);
	}

	return aRect;
}

bool Plant::NotOnGround()
{
	uintptr_t func = 0x463EF0;
	bool result;

	_asm
	{
		mov eax, this;
		call func;
		mov result, al;
	}
	return result;
}

bool Plant::OriginalNotOnGround()
{
	if (mSeedType == SEED_SQUASH)
	{
		if (mState == STATE_SQUASH_RISING || mState == STATE_SQUASH_FALLING || mState == STATE_SQUASH_DONE_FALLING)
			return true;
	}

	return mSquished || mOnBungeeState == RISING_WITH_BUNGEE || mDead;
}

void Plant::GetPeaHeadOffset(int& theOffsetX, int& theOffsetY)
{
	uintptr_t func = 0x465380;

	_asm
	{
		push theOffsetY;
		push theOffsetX;
		mov eax, this;
		call func;
	}
}

void Plant::PlayBodyReanim(const char* theTrackName, ReanimLoopType theLoopType, int theBlendTime, float theAnimRate)
{
	uintptr_t func = 0x45FD90;

	_asm
	{
		push theAnimRate;
		mov ecx, theBlendTime;
		push theLoopType;
		push theTrackName;
		mov eax, this;
		call func;
	}
}

MagnetItem* Plant::GetFreeMagnetItem()
{
	uintptr_t func = 0x4615D0;
	MagnetItem* result;

	_asm
	{
		mov edx, this;
		call func;
		mov result, eax;
	}
	return result;
}

void Plant::StarFruitFire()
{
	uintptr_t func = 0x45F720;

	_asm
	{
		mov esi, this;
		call func;
	}
}

bool Plant::IsOnBoard()
{
	return mBoard != nullptr && IsInPlay();
}

bool Plant::IsInPlay()
{
	uintptr_t func = 0x4638F0;
	bool result;

	_asm
	{
		mov eax, this;
		call func;
		mov result, al;
	}
	return result;
}

void Plant::GoldMagnetFindTargets()
{
	uintptr_t func = 0x4624B0;

	_asm
	{
		mov eax, this;
		call func;
	}
}

//void Plant::UpdateLilypad()
//{
//	PlantsOnLawn Plants;
//	int thsTotalCost = 0;
//	this->mBoard->GetPlantsOnLawn(this->mPlantCol, mRow, &Plants);
//	if (Plants.mNormalPlant)
//	{
//		thsTotalCost += GetCost(Plants.mNormalPlant->mSeedType, Plants.mNormalPlant->mImitaterType);
//	}
//	if (Plants.mPumpkinPlant)
//	{
//		thsTotalCost += GetCost(Plants.mPumpkinPlant->mSeedType, Plants.mPumpkinPlant->mImitaterType);
//	}
//	if (Plants.mFlyingPlant)
//	{
//		thsTotalCost += GetCost(Plants.mFlyingPlant->mSeedType, Plants.mFlyingPlant->mImitaterType);
//	}
//	thsTotalCost /= 25;
//
//	Reanimation* aReanim = this->mApp->ReanimationTryToGet(this->mBodyReanimID);
//	if (aReanim)
//	{
//		ReanimatorTrackInstance* aReanimatorTrackInstance = aReanim->GetTrackInstanceByName("Lilypad_Light");
//		aReanimatorTrackInstance->mTrackColor.mAlpha = min(255 / 10 * thsTotalCost, 255);
//	}
//
//	if (mState == STATE_NOTREADY && mStateCountdown == 0)
//	{
//		if (mState == STATE_LILYPAD_INVULNERABLE)
//		{
//			mState = STATE_NOTREADY;
//		}
//		mStateCountdown = 600;
//		Zombie* aZombie = nullptr;
//		while (this->mBoard->IterateZombies(aZombie))
//		{
//			int aRowDeviation = aZombie->mRow - this->mRow;
//			if (aZombie->mZombieType == ZOMBIE_BOSS)
//			{
//				aRowDeviation = 0;
//			}
//			if (!(aRowDeviation < -1 || aRowDeviation>1) && aZombie->IsOntheGridX(this->mPlantCol - 1, 2) && aZombie->EffectedByDamage(this->GetDamageRangeFlags()))
//			{
//				if (thsTotalCost != 0)
//				{
//					aZombie->TakeDamage(3 * thsTotalCost, 0U);
//					mApp->PlayFoley(FOLEY_SPLAT);
//				}
//			}
//		}
//	}
//}
//
//void Plant::UpdateGarlic()
//{
//	Projectile* aProjectile = nullptr;
//	while (this->mBoard->IterateProjectiles(aProjectile))
//	{
//		if (((ProjectileExtra*)aProjectile)->mLastGarlic != this->mBoard->PlantGetID((PlantExtra*)this))
//		{
//			if (this->mRow == aProjectile->mRow)
//			{
//				Sexy::Rect aPlantRect = this->OriginalGetPlantRect();
//				Sexy::Rect aProjectileRect = aProjectile->GetProjectileRect();
//				aPlantRect.mX = aPlantRect.mX + aPlantRect.mWidth / 2 - 20;
//				aPlantRect.mY = aPlantRect.mY + aPlantRect.mHeight / 2 - 20;
//				aPlantRect.mWidth = aPlantRect.mHeight = 40;
//				if (GetCircleRectOverlap(aProjectileRect.mX + aProjectileRect.mWidth / 2, aProjectileRect.mY + aProjectileRect.mHeight / 2, 1, aPlantRect))
//				{
//					if (aProjectile->mPosZ == 0.0 && aProjectile->mVelZ == 0.0 && aProjectile->mAccZ == 0.0)
//					{
//						if (aProjectile->mVelX == 0.0 && aProjectile->mVelY == 0.0)
//						{
//							aProjectile->mVelX = (aProjectile->mMotionType != MOTION_BACKWARDS) ? 3.33 : -3.33;
//						}
//						aProjectile->mMotionType = MOTION_STAR;
//						std::swap(aProjectile->mVelX, aProjectile->mVelY);
//						aProjectile->mVelY = -aProjectile->mVelY;
//						((ProjectileExtra*)aProjectile)->mLastGarlic = this->mBoard->PlantGetID((PlantExtra*)this);
//					}
//				}
//			}
//		}
//	}
//}
//
//bool Plant::IsAt(int theGridX, int theGridY)
//{
//	if (theGridX < 0 || theGridX >= MAX_GRID_SIZE_X || theGridY < 0 || theGridY >= MAX_GRID_SIZE_Y)
//		return false;
//
//	return (mRow == theGridY && mPlantCol == theGridX) || ((mSeedType == SEED_SPIKEWEED || mSeedType == SEED_SPIKEROCK) && mRow == theGridY) || (mSeedType == SEED_COBCANNON && mRow == theGridY && !(mPlantCol < theGridX - 1 || mPlantCol > theGridX));
//}
//
//void Plant::UpdateGloomShroom()
//{
//	if (mStateCountdown == 0 && mState != PlantState::STATE_DOINGSPECIAL)
//	{
//		mState = PlantState::STATE_DOINGSPECIAL;
//		mDisappearCountdown = 100;
//		PlayBodyReanim("anim_shooting", ReanimLoopType::REANIM_LOOP, 20, 14.0f * 6.0f);
//		mShootingCounter = 100;
//	}
//}
