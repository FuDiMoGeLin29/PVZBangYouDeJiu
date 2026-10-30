#pragma once
#include <stdint.h>

class Plant;
class Zombie;
class LawnApp;
class GameButton;
class Reanimation;
enum SeedType;
enum ZombieType;

enum AlmanacPage
{
	ALMANAC_PAGE_INDEX,
	ALMANAC_PAGE_PLANTS,
	ALMANAC_PAGE_ZOMBIES
};

class AlmanacDialog
{
private:
	enum
	{
		ALMANAC_BUTTON_CLOSE = 0,
		ALMANAC_BUTTON_PLANT = 1,
		ALMANAC_BUTTON_ZOMBIE = 2,
		ALMANAC_BUTTON_INDEX = 3
	};

public:
	uint8_t data[0x16C];

public:
	LawnApp* mApp;						//+0x16C
	GameButton* mCloseButton;				//+0x170
	GameButton* mIndexButton;				//+0x174
	GameButton* mPlantButton;				//+0x178
	GameButton* mZombieButton;				//+0x17C
	AlmanacPage					mOpenPage;					//+0x180
	Reanimation* mReanim[4];					//+0x184
	SeedType					mSelectedSeed;				//+0x194
	ZombieType					mSelectedZombie;			//+0x198
	Plant* mPlant;						//+0x19C
	Zombie* mZombie;					//+0x1A0
	Zombie* mZombiePerfTest[400];		//+0x1A4
};