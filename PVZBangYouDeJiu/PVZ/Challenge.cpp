#include "Board.h"
#include "Cutscene.h"
#include "Challenge.h"
#include "LawnApp.h"
#include "Resources.h"
#include "CursorObject.h"
#include "GameButton.h"
#include "ReanimationLawn.h"

using namespace Sexy;

static constexpr int		BEGHOULED_WINNING_SCORE		= 75;
static constexpr int		SLOT_MACHINE_WINNING_SCORE	= 2000;
static constexpr int		ZOMBIQUARIUM_WINNING_SCORE	= 1000;
static constexpr int		I_ZOMBIE_WINNING_SCORE		= 5;
static constexpr int		MAX_PORTALS					= 4;
static constexpr int		MAX_SQUIRRELS				= 7;
static constexpr int		MAX_SCARY_POTS				= 54;
static constexpr int		STORM_FLASH_TIME			= 150;

int gZombieWaves[NUM_LEVELS] = {  //0x6A34E8
	4,  6,  8,  10, 8,  10, 20, 10, 20, 20,
	10, 20, 10, 20, 10, 10, 20, 10, 20, 20,
	10, 20, 20, 30, 20, 20, 30, 20, 30, 30,
	10, 20, 10, 20, 20, 10, 20, 10, 20, 20,
	10, 20, 20, 30, 20, 20, 30, 20, 30, 30,
};

ZombieAllowedLevels gZombieAllowedLevels[NUM_ZOMBIE_TYPES] = {  //0x6A35B0
	{ ZOMBIE_NORMAL,
		{
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		}
	},
	{ ZOMBIE_FLAG, 
		{
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		}
	},
	{ ZOMBIE_TRAFFIC_CONE,
		{
			0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
			0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		}
	},
	{ ZOMBIE_POLEVAULTER,
		{
			0, 0, 0, 0, 0, 1, 1, 0, 1, 1,
			0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
			0, 0, 0, 1, 0, 0, 0, 0, 1, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		}
	},
	{ ZOMBIE_PAIL,
		{
			0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
			0, 1, 0, 0, 1, 0, 0, 0, 0, 0,
			0, 1, 0, 1, 0, 0, 1, 0, 1, 1,
			0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
			0, 1, 0, 0, 1, 0, 0, 0, 1, 1,
		}
	},
	{ ZOMBIE_NEWSPAPER,
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 0, 0, 1, 0, 0, 0, 0, 0,
			0, 1, 0, 1, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		}
	},
	{ ZOMBIE_DOOR,
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 1, 1, 0, 0, 1, 0, 1, 1,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		}
	},
	{ ZOMBIE_FOOTBALL,
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 1, 1, 0, 0, 1,
			0, 1, 0, 0, 1, 0, 0, 0, 0, 0,
			0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
		}
	},
	{ ZOMBIE_DANCER,
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		}
	},
	{ ZOMBIE_BACKUP_DANCER,
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		}
	},
	{ ZOMBIE_DUCKY_TUBE, { 0 } },
	{ ZOMBIE_SNORKEL,
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 1, 1, 1, 0, 1, 0, 0, 1,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		}
	},
	{ ZOMBIE_ZAMBONI,
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 1, 1, 0, 1, 1,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		}
	},
	{ ZOMBIE_BOBSLED,
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 1, 1, 0, 1, 1,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		}
	},
	{ ZOMBIE_DOLPHIN_RIDER,
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
			0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		}
	},
	{ ZOMBIE_JACK_IN_THE_BOX,
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 0, 0, 0, 0, 1, 0, 0, 1,
			0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		}
	},
	{ ZOMBIE_BALLOON,
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 1, 1, 0, 0, 0, 0, 1, 1,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		}
	},
	{ ZOMBIE_DIGGER,
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 1, 1, 0, 0, 1,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		}
	},
	{ ZOMBIE_POGO,
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
			0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
		}
	},
	{ ZOMBIE_YETI, {0} },
	{ ZOMBIE_BUNGEE,
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 0, 0, 0, 0, 1, 0, 1, 1,
		}
	},
	{ ZOMBIE_LADDER,
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 1, 1, 1, 0, 1, 0, 1, 1,
		}
	},
	{ ZOMBIE_CATAPULT,
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 1, 1, 0, 1, 1,
		}
	},
	{ ZOMBIE_GARGANTUAR,
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
		}
	},
	{ ZOMBIE_IMP,
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
		}
	},
	{ ZOMBIE_BOSS, {0} },
	{ ZOMBIE_PEA_HEAD, {0} },
	{ ZOMBIE_WALLNUT_HEAD, {0} },
	{ ZOMBIE_JALAPENO_HEAD, {0} },
	{ ZOMBIE_GATLING_HEAD, {0} },
	{ ZOMBIE_SQUASH_HEAD, {0} },
	{ ZOMBIE_TALLNUT_HEAD, {0} },
	{ ZOMBIE_REDEYE_GARGANTUAR, {0} },
};

SeedType gArtChallengeWallnut[MAX_GRID_SIZE_Y][ART_CHALLEGE_SIZE_X] = {  //0x6A3260
	{SEED_NONE,     SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_WALLNUT,   SEED_WALLNUT,   SEED_WALLNUT,   SEED_NONE,      SEED_NONE},
	{SEED_NONE,     SEED_NONE,      SEED_NONE,      SEED_WALLNUT,   SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_WALLNUT,   SEED_NONE},
	{SEED_NONE,     SEED_NONE,      SEED_NONE,      SEED_WALLNUT,   SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_WALLNUT,   SEED_NONE},
	{SEED_NONE,     SEED_NONE,      SEED_NONE,      SEED_WALLNUT,   SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_WALLNUT,   SEED_NONE},
	{SEED_NONE,     SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_WALLNUT,   SEED_WALLNUT,   SEED_WALLNUT,   SEED_NONE,      SEED_NONE},
	{SEED_NONE,     SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE}
};

SeedType gArtChallengeSunFlower[MAX_GRID_SIZE_Y][ART_CHALLEGE_SIZE_X] = {  //0x6A3338
	{SEED_NONE,     SEED_NONE,      SEED_STARFRUIT, SEED_STARFRUIT, SEED_STARFRUIT, SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE},
	{SEED_NONE,     SEED_STARFRUIT, SEED_WALLNUT,   SEED_WALLNUT,   SEED_WALLNUT,   SEED_STARFRUIT, SEED_NONE,      SEED_NONE,      SEED_NONE},
	{SEED_NONE,     SEED_NONE,      SEED_STARFRUIT, SEED_STARFRUIT, SEED_STARFRUIT, SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE},
	{SEED_NONE,     SEED_NONE,      SEED_NONE,      SEED_UMBRELLA,  SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE},
	{SEED_NONE,     SEED_NONE,      SEED_UMBRELLA,  SEED_UMBRELLA,  SEED_UMBRELLA,  SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE},
	{SEED_NONE,     SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE}
};

SeedType gArtChallengeStarFruit[MAX_GRID_SIZE_Y][ART_CHALLEGE_SIZE_X] = {  //0x6A3410
	{SEED_NONE,     SEED_NONE,      SEED_NONE,      SEED_STARFRUIT, SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE},
	{SEED_NONE,     SEED_NONE,      SEED_NONE,      SEED_STARFRUIT, SEED_STARFRUIT, SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE},
	{SEED_NONE,     SEED_STARFRUIT, SEED_STARFRUIT, SEED_STARFRUIT, SEED_STARFRUIT, SEED_STARFRUIT, SEED_STARFRUIT, SEED_NONE,      SEED_NONE},
	{SEED_NONE,     SEED_NONE,      SEED_NONE,      SEED_STARFRUIT, SEED_STARFRUIT, SEED_STARFRUIT, SEED_NONE,      SEED_NONE,      SEED_NONE},
	{SEED_NONE,     SEED_NONE,      SEED_NONE,      SEED_STARFRUIT, SEED_NONE,      SEED_NONE,      SEED_STARFRUIT, SEED_NONE,      SEED_NONE},
	{SEED_NONE,     SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE,      SEED_NONE}
};

void Challenge::IZombieSetupPlant(Plant* thePlant)
{
	uintptr_t func = 0x42A530;

	_asm
	{
		push thePlant;
		mov eax, this;
		call func;
	}
}