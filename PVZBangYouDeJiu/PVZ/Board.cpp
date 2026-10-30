#include "LawnApp.h"
#include "Board.h"
#include <stdint.h>

Coin* Board::AddCoin(int theX, int theY, CoinType theCoinType, CoinMotion theCoinMotion)
{
	uintptr_t func = 0x40CB10;
	Coin* result;
	_asm
	{
		push theCoinMotion;
		push theCoinType;
		push theY;
		push theX;
		mov ecx, this;
		call func;
		mov result, eax;
	}
	return result;
}

Plant* Board::AddPlant(int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType)
{
	uintptr_t func = 0x40D120;
	Plant* result;
	_asm
	{
		push theImitaterType;
		push theSeedType;
		mov eax, theGridY;
		push theGridX;
		push this;
		call func;
		mov result, eax;
	}
	return result;
}

bool Board::IteratePlants(Plant*& thePlant)
{
	uintptr_t func = 0x41C950;
	bool result;
	_asm
	{
		mov esi, thePlant;
		mov edx, this;
		call func;
		mov result, al;
	}
	return result;
}

bool Board::IterateZombies(Zombie*& theZombie)
{
	uintptr_t func = 0x41C8F0;
	bool result;
	_asm
	{
		mov esi, theZombie;
		mov edx, this;
		call func;
		mov result, al;
	}
	return result;
}

bool Board::IterateProjectiles(Projectile*& theProjectile)
{
	uintptr_t func = 0x41C9B0;
	bool result;
	_asm
	{
		mov esi, theProjectile;
		mov edx, this;
		call func;
		mov result, al;
	}
	return result;
}

bool Board::IterateReanimations(Reanimation*& theReanimation)
{
	uintptr_t func = 0x41CB90;
	bool result;
	_asm
	{
		mov esi, theReanimation;
		mov eax, this;
		call func;
		mov result, al;
	}
	return result;
}

Zombie* Board::ZombieTryToGet(ZombieID theZombieID)
{
	uintptr_t func = 0x41C7F0;
	Zombie* result;
	_asm
	{
		mov ecx, theZombieID;
		mov edx, this;
		call func;
		mov result, eax;
	}
	return result;
}

Plant* Board::PlantTryToGet(PlantID thePlantID)
{
	uintptr_t func = 0x41DF00;
	Plant* result;
	DataArray<Plant>& PlantsData = this->mPlants;

	_asm
	{
		mov ecx, thePlantID;
		mov edx, PlantsData;
		call func;
		mov result, eax;
	}
	return result;
}

Projectile* Board::AddProjectile(int theX, int theY, int theRenderOrder, int theRow, ProjectileType theProjectileType)
{
	uintptr_t func = 0x40D620;

	_asm
	{
		push theProjectileType;
		push theRow;
		push theRenderOrder;
		push theY;
		push theX;
		mov eax, this;
		call func;
	}
}

void Board::KillAllZombiesInRadius(int theRow, int theX, int theY, int theRadius, int theRowRange, bool theBurn, int theDamageRangeFlags)
{
	uintptr_t func = 0x41D8A0;

	_asm
	{
		push theDamageRangeFlags;
		push theBurn;
		push theRowRange;
		push theRadius;
		push theY;
		push theX;
		push theRow;
		push this;
		call func;
	}
}

int Board::PixelToGridX(int theX, int theY)
{
	uintptr_t func = 0x41C4C0;
	int result;
	_asm
	{
		mov edi, theY;
		mov eax, theX;
		mov ecx, this;
		call func;
		mov result, eax;
	}
	return result;
}

int Board::PixelToGridY(int theX, int theY)
{
	uintptr_t func = 0x41C550;
	int result;
	_asm
	{
		mov ecx, theY;
		mov eax, theX;
		mov edx, this;
		call func;
		mov result, eax;
	}
	return result;
}

Zombie* Board::AddZombieInRow(ZombieType theZombieType, int theRow, int theFromWave)
{
	uintptr_t func = 0x40DDC0;
	Zombie* result;

	_asm
	{
		mov ebx, theFromWave;
		push theRow;
		push theZombieType;
		mov eax, this;
		call func;
		mov result, eax;
	}
	return result;
}

ZombieID Board::ZombieGetID(Zombie* theZombie)
{
	return (ZombieID)((DataArray<Zombie>*)&mZombies)->DataArrayGetID(theZombie);
}

PlantID Board::PlantGetID(Plant* thePlant)
{
	return (PlantID)((DataArray<Plant>*)&mPlants)->DataArrayGetID(thePlant);
}

void Board::GetPlantsOnLawn(int theGridX, int theGridY, PlantsOnLawn* thePlantOnLawn)
{
	uintptr_t func = 0x40D2A0;

	_asm
	{
		push theGridY;
		push theGridX;
		mov ebx, thePlantOnLawn;
		mov edx, this;
		call func;
	}
}

float Board::GetPosYBasedOnRow(float thePosX, int theRow)
{
	uintptr_t func = 0x41C6C0;
	float result;
	_asm
	{
		mov ecx, theRow;
		push thePosX;
		mov eax, this;
		call func;
		fstp result;
	}
	return result;
}

int Board::GridToPixelX(int theGridX, int theGridY)
{
	uintptr_t func = 0x41C680;
	int result;
	_asm
	{
		mov esi, theGridY;
		mov eax, theGridX;
		mov ecx, this;
		call func;
		mov result, eax;
	}
	return result;
}

int Board::GridToPixelY(int theGridX, int theGridY)
{
	uintptr_t func = 0x41C740;
	int result;
	_asm
	{
		mov eax, theGridY;
		mov ecx, theGridX;
		mov ebx, this;
		call func;
		mov result, eax;
	}
	return result;
}

GridItem* Board::GetGriditemAt(GridItemType theGridItemType, int theGridX, int theGridY)
{
	uintptr_t func = 0x408E40;
	GridItem* result = nullptr;

	_asm
	{
		mov edi, theGridY;
		mov ebx, theGridX;
		push theGridItemType;
		mov edx, this;
		call func;
		mov result, eax;
	}
	return result;
}

void Board::ShakeBoard(int theShakeAmountX, int theShakeAmountY)
{
	mShakeCounter = 12;
	mShakeAmountX = theShakeAmountX;
	mShakeAmountY = theShakeAmountY;
}

int Board::MakeRenderOrder(RenderLayer theRenderLayer, int theRow, int theLayerOffset)
{
	return theRow * (int)RenderLayer::RENDER_LAYER_ROW_OFFSET + theRenderLayer + theLayerOffset;
}

bool Board::StageHasPool()
{
	return (this->mBackground == BACKGROUND_3_POOL || this->mBackground == BACKGROUND_4_FOG);
}

Plant* Board::NewPlant(int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType)
{
	uintptr_t func = 0x40CE20;
	Plant* result;
	_asm
	{
		push theImitaterType;
		push theSeedType;
		push theGridY;
		push theGridX;
		mov eax, this;
		call func;
		mov result, eax;
	}
	return result;
}

void Board::PickUpTool(GameObjectType theGameObjectType)
{
	uintptr_t func = 0x411C10;

	_asm
	{
		mov edx, theGameObjectType;
		mov ebx, this;
		call func;
	}
}

void Board::ClearCursor()
{
	uintptr_t func = 0x412330;

	_asm
	{
		mov edi, this;
		call func;
	}
}

Plant* Board::FindUmbrellaPlant(int theGridX, int theGridY)
{
	uintptr_t func = 0x41D3D0;
	Plant* result;
	_asm
	{
		mov edi, theGridY;
		mov ebx, theGridX;
		mov edx, this;
		call func;
		mov result, eax;
	}
	return result;
}

Plant* Board::GetFlowerPotAt(int theGridX, int theGridY)
{
	uintptr_t func = 0x40D220;
	Plant* result;
	_asm
	{
		mov ebx, theGridY;
		push theGridX;
		mov edx, this;
		call func;
		mov result, eax;
	}
	return result;
}

int GetRectOverlap(const Sexy::Rect& rect1, const Sexy::Rect& rect2)
{
	uintptr_t func = 0x41C820;
	int result;
	_asm
	{
		mov ecx, rect2;
		mov edi, rect1;
		call func;
		mov result, eax;
	}
	return result;
}

bool GetCircleRectOverlap(int theCircleX, int theCircleY, int theRadius, const Sexy::Rect& theRect)
{
	uintptr_t func = 0x41C850;
	bool result;
	_asm
	{
		mov eax, theRect;
		push theRadius;
		mov edx, theCircleY;
		mov ecx, theCircleX;
		call func;
		add esp, 0x4;
		mov result, al;
	}
	return result;
}

void Board::Draw(Sexy::Graphics* g)
{
	uintptr_t func = 0x41ACF0;

	_asm
	{
		push g;
		mov ecx, this;
		call func;
	}
}

void Board::DrawUIBottom(Sexy::Graphics* g)
{
	uintptr_t func = 0x41A0A0;

	_asm
	{
		mov edi, g;
		push this;
		call func;
	}
}

void Board::DrawUICoinBank(Sexy::Graphics* g)
{
	uintptr_t func = 0x41A2A0;

	_asm
	{
		mov edi, g;
		push this;
		call func;
	}
}

void Board::DrawUITop(Sexy::Graphics* g)
{
	uintptr_t func = 0x41AA40;

	_asm
	{
		push g;
		push this;
		call func;
	}
}

void Board::DrawBackdrop(Sexy::Graphics* g)
{
	uintptr_t func = 0x416290;

	_asm
	{
		push g;
		push this;
		call func;
	}
}

void Board::Update()
{
    uintptr_t func = 0x415D40;

	_asm
	{
		mov ecx, this;
		call func;
	}
}

void Board::LoadBackgroundImages()
{
	uintptr_t func = 0x40A160;

	_asm
	{
		mov esi, this;
		call func;
	}
}

GridItem* Board::AddACrater(int theGridX, int theGridY)
{
	uintptr_t func = 0x408F80;
	GridItem* result;

	_asm
	{
		mov edi, theGridY;
		push theGridX;
		mov eax, this;
		call func;
		mov result, eax;
	}
	return result;
}

bool Board::TakeSunMoney(int theAmount)
{
	uintptr_t func = 0x41BA60;
	bool result;
	_asm
	{
		mov ebx, theAmount;
		mov edi, this;
		call func;
		mov result, al;
	}
	return result;

}

bool Board::CanTakeSunMoney(int theAmount)
{
	uintptr_t func = 0x41BAB0;
	bool result;
	_asm
	{
		push theAmount;
		mov edx, this;
		call func;
		mov result, al;
	}
	return result;
}
