#pragma once
#include "Plant.h"
#include "Zombie.h"
#include "Projectile.h"
#include "Coin.h"
#include "LawnMower.h"
#include "GridItem.h"
#include "LawnCommon.h"
#include "DataArray.h"
#include "Rect.h"
#include "ButtonListener.h"

class CursorObject;
class CursorPreview;
class GameButton;
class MessageWidget;
class SeedBank;
class ToolTipWidget;
class CutScene;
class Challenge;
class Reanimation;
class DataSync;
class TodParticleSystem;
namespace Sexy
{
	class ButtonWidget;
	class MTRand;
}
enum MessageStyle;
enum BoardResult;
enum CursorType;
enum ParticleEffect;

class Coin;
class GridItem;
class LawnMower;

constexpr int	MAX_ZOMBIES_IN_WAVE = 50;
constexpr int	MAX_ZOMBIE_WAVES = 100;
constexpr int	MAX_GRAVE_STONES = MAX_GRID_SIZE_X * MAX_GRID_SIZE_Y;
constexpr int	MAX_POOL_GRID_SIZE = 10;
constexpr int	MAX_RENDER_ITEMS = 2048;
constexpr int	PROGRESS_METER_COUNTER = 150;

constexpr int	WIDE_BOARD_WIDTH = 800;
constexpr int	BOARD_OFFSET = 220;
constexpr int	BOARD_EDGE = -100;
constexpr int	BOARD_IMAGE_WIDTH_OFFSET = 1180;
constexpr int   BOARD_ICE_START = 800;
constexpr int   LAWN_XMIN = 40;
constexpr int   LAWN_YMIN = 80;
constexpr int   HIGH_GROUND_HEIGHT = 30;

/* #################################################################################################### */

struct LawnFPoint
{
	float							x;
	float							y;
};

/* #################################################################################################### */

enum GameObjectType
{
	OBJECT_TYPE_NONE,
	OBJECT_TYPE_PLANT,
	OBJECT_TYPE_PROJECTILE,
	OBJECT_TYPE_COIN,
	OBJECT_TYPE_SEEDPACKET,
	OBJECT_TYPE_SHOVEL,
	OBJECT_TYPE_WATERING_CAN,
	OBJECT_TYPE_FERTILIZER,
	OBJECT_TYPE_BUG_SPRAY,
	OBJECT_TYPE_PHONOGRAPH,
	OBJECT_TYPE_CHOCOLATE,
	OBJECT_TYPE_GLOVE,
	OBJECT_TYPE_MONEY_SIGN,
	OBJECT_TYPE_WHEELBARROW,
	OBJECT_TYPE_TREE_FOOD,
	OBJECT_TYPE_NEXT_GARDEN,
	OBJECT_TYPE_MENU_BUTTON,
	OBJECT_TYPE_STORE_BUTTON,
	OBJECT_TYPE_SLOT_MACHINE_HANDLE,
	OBJECT_TYPE_SCARY_POT,
	OBJECT_TYPE_STINKY,
	OBJECT_TYPE_TREE_OF_WISDOM
};

class HitResult
{
public:
	void* mObject;
	GameObjectType					mObjectType;
};

/* #################################################################################################### */

enum RenderObjectType
{
	RENDER_ITEM_COIN,
	RENDER_ITEM_PROJECTILE,
	RENDER_ITEM_ZOMBIE,
	RENDER_ITEM_ZOMBIE_SHADOW,
	RENDER_ITEM_ZOMBIE_BUNGEE_TARGET,
	RENDER_ITEM_PLANT,
	RENDER_ITEM_PLANT_OVERLAY,
	RENDER_ITEM_PLANT_MAGNET_ITEMS,
	RENDER_ITEM_CURSOR_PREVIEW,
	RENDER_ITEM_PARTICLE,
	RENDER_ITEM_REANIMATION,
	RENDER_ITEM_ICE,
	RENDER_ITEM_TOP_UI,
	RENDER_ITEM_FOG,
	RENDER_ITEM_STORM,
	RENDER_ITEM_BOTTOM_UI,
	RENDER_ITEM_BACKDROP,
	RENDER_ITEM_DOOR_MASK,
	RENDER_ITEM_COIN_BANK,
	RENDER_ITEM_PROJECTILE_SHADOW,
	RENDER_ITEM_MOWER,
	RENDER_ITEM_SCREEN_FADE,
	RENDER_ITEM_BOSS_PART,
	RENDER_ITEM_GRID_ITEM,
	RENDER_ITEM_GRID_ITEM_OVERLAY
};

class RenderItem
{
public:
	RenderObjectType				mRenderObjectType;
	int								mZPos;
	union
	{
		GameObject* mGameObject;
		Plant* mPlant;
		Zombie* mZombie;
		Coin* mCoin;
		Projectile* mProjectile;
		CursorPreview* mCursorPreview;
		TodParticleSystem* mParticleSytem;
		Reanimation* mReanimation;
		GridItem* mGridItem;
		LawnMower* mMower;
		BossPart					mBossPart;
		int							mBoardGridY;
	};
};
//bool RenderItemSortFunc(const RenderItem& theItem1, const RenderItem& theItem2);

/* #################################################################################################### */

struct ZombiePicker
{
	int								mZombieCount;
	int								mZombiePoints;
	int								mZombieTypeCount[NUM_ZOMBIE_TYPES];
	int								mAllWavesZombieTypeCount[NUM_ZOMBIE_TYPES];
};

//void								ZombiePickerInitForWave(ZombiePicker* theZombiePicker);
//void								ZombiePickerInit(ZombiePicker* theZombiePicker);

/* #################################################################################################### */

enum PlantingReason
{
	PLANTING_OK,
	PLANTING_NOT_HERE,
	PLANTING_ONLY_ON_GRAVES,
	PLANTING_ONLY_IN_POOL,
	PLANTING_ONLY_ON_GROUND,
	PLANTING_NEEDS_POT,
	PLANTING_NOT_ON_ART,
	PLANTING_NOT_PASSED_LINE,
	PLANTING_NEEDS_UPGRADE,
	PLANTING_NOT_ON_GRAVE,
	PLANTING_NOT_ON_CRATER,
	PLANTING_NOT_ON_WATER,
	PLANTING_NEEDS_GROUND,
	PLANTING_NEEDS_SLEEPING
};

enum PlantPriority
{
	TOPPLANT_EATING_ORDER,
	TOPPLANT_DIGGING_ORDER,
	TOPPLANT_BUNGEE_ORDER,
	TOPPLANT_CATAPULT_ORDER,
	TOPPLANT_ZEN_TOOL_ORDER,
	TOPPLANT_ANY,
	TOPPLANT_ONLY_NORMAL_POSITION,
	TOPPLANT_ONLY_FLYING,
	TOPPLANT_ONLY_PUMPKIN,
	TOPPLANT_ONLY_UNDER_PLANT
};

struct PlantsOnLawn
{
	Plant* mUnderPlant;
	Plant* mPumpkinPlant;
	Plant* mFlyingPlant;
	Plant* mNormalPlant;
};

/* #################################################################################################### */

struct BungeeDropGrid
{
	TodWeightedGridArray			mGridArray[MAX_GRID_SIZE_X * MAX_GRID_SIZE_Y];
	int								mGridArrayCount;
};

/* #################################################################################################### */

enum InGameButtons
{
	GAME_MENU_BUTTON,
	GAME_STORE_BUTTON
};

enum AdviceType
{
	ADVICE_NONE = -1,
	ADVICE_CLICK_ON_SUN,
	ADVICE_CLICKED_ON_SUN,
	ADVICE_CLICKED_ON_COIN,
	ADVICE_SEED_REFRESH,
	ADVICE_CANT_AFFORD_PLANT,
	ADVICE_PLANT_GRAVEBUSTERS_ON_GRAVES,
	ADVICE_PLANT_LILYPAD_ON_WATER,
	ADVICE_PLANT_TANGLEKELP_ON_WATER,
	ADVICE_PLANT_SEASHROOM_ON_WATER,
	ADVICE_PLANT_POTATOE_MINE_ON_LILY,
	ADVICE_PLANT_WRONG_ART_TYPE,
	ADVICE_PLANT_NEED_POT,
	ADVICE_PLANT_NOT_ON_GRAVE,
	ADVICE_PLANT_NOT_ON_CRATER,
	ADVICE_CANT_PLANT_THERE,
	ADVICE_PLANT_NOT_ON_WATER,
	ADVICE_PLANTING_NEEDS_GROUND,
	ADVICE_BEGHOULED_DRAG_TO_MATCH_3,
	ADVICE_BEGHOULED_MATCH_3,
	ADVICE_BEGHOULED_MATCH_4,
	ADVICE_BEGHOULED_SAVE_SUN,
	ADVICE_BEGHOULED_USE_CRATER_1,
	ADVICE_BEGHOULED_USE_CRATER_2,
	ADVICE_PLANT_NOT_PASSED_LINE,
	ADVICE_PLANT_ONLY_ON_REPEATERS,
	ADVICE_PLANT_ONLY_ON_MELONPULT,
	ADVICE_PLANT_ONLY_ON_SUNFLOWER,
	ADVICE_PLANT_ONLY_ON_SPIKEWEED,
	ADVICE_PLANT_ONLY_ON_KERNELPULT,
	ADVICE_PLANT_ONLY_ON_MAGNETSHROOM,
	ADVICE_PLANT_ONLY_ON_FUMESHROOM,
	ADVICE_PLANT_ONLY_ON_LILYPAD,
	ADVICE_PLANT_NEEDS_REPEATER,
	ADVICE_PLANT_NEEDS_MELONPULT,
	ADVICE_PLANT_NEEDS_SUNFLOWER,
	ADVICE_PLANT_NEEDS_SPIKEWEED,
	ADVICE_PLANT_NEEDS_KERNELPULT,
	ADVICE_PLANT_NEEDS_MAGNETSHROOM,
	ADVICE_PLANT_NEEDS_FUMESHROOM,
	ADVICE_PLANT_NEEDS_LILYPAD,
	ADVICE_SLOT_MACHINE_PULL,
	ADVICE_HUGE_WAVE,
	ADVICE_SHOVEL_REFRESH,
	ADVICE_PORTAL_RELOCATING,
	ADVICE_SLOT_MACHINE_COLLECT_SUN,
	ADVICE_DESTORY_POTS_TO_FINISIH_LEVEL,
	ADVICE_USE_SHOVEL_ON_POTS,
	ADVICE_ALMOST_THERE,
	ADVICE_ZOMBIQUARIUM_CLICK_TROPHY,
	ADVICE_ZOMBIQUARIUM_COLLECT_SUN,
	ADVICE_ZOMBIQUARIUM_CLICK_TO_FEED,
	ADVICE_ZOMBIQUARIUM_BUY_SNORKEL,
	ADVICE_I_ZOMBIE_PLANTS_NOT_REAL,
	ADVICE_I_ZOMBIE_NOT_PASSED_LINE,
	ADVICE_I_ZOMBIE_LEFT_OF_LINE,
	ADVICE_SLOT_MACHINE_SPIN_AGAIN,
	ADVICE_I_ZOMBIE_EAT_ALL_BRAINS,
	ADVICE_PEASHOOTER_DIED,
	ADVICE_STINKY_SLEEPING,
	ADVICE_BEGHOULED_NO_MOVES,
	ADVICE_PLANT_SUNFLOWER5,
	ADVICE_PLANTING_NEED_SLEEPING,
	ADVICE_CLICK_TO_CONTINUE,
	ADVICE_SURVIVE_FLAGS,
	ADVICE_UNLOCKED_MODE,
	ADVICE_NEED_WHEELBARROW,
	NUM_ADVICE_TYPES
};

enum BackgroundType
{
	BACKGROUND_1_DAY,
	BACKGROUND_2_NIGHT,
	BACKGROUND_3_POOL,
	BACKGROUND_4_FOG,
	BACKGROUND_5_ROOF,
	BACKGROUND_6_BOSS,
	BACKGROUND_MUSHROOM_GARDEN,
	BACKGROUND_GREENHOUSE,
	BACKGROUND_ZOMBIQUARIUM,
	BACKGROUND_TREEOFWISDOM
};

enum DebugTextMode
{
	DEBUG_TEXT_NONE,
	DEBUG_TEXT_ZOMBIE_SPAWN,
	DEBUG_TEXT_MUSIC,
	DEBUG_TEXT_MEMORY,
	DEBUG_TEXT_COLLISION
};

enum GridSquareType
{
	GRIDSQUARE_NONE,
	GRIDSQUARE_GRASS,
	GRIDSQUARE_DIRT,
	GRIDSQUARE_POOL,
	GRIDSQUARE_HIGH_GROUND
};

enum PlantRowType
{
	PLANTROW_DIRT,
	PLANTROW_NORMAL,
	PLANTROW_POOL,
	PLANTROW_HIGH_GROUND
};

enum TutorialState
{
	TUTORIAL_OFF,
	TUTORIAL_LEVEL_1_PICK_UP_PEASHOOTER,
	TUTORIAL_LEVEL_1_PLANT_PEASHOOTER,
	TUTORIAL_LEVEL_1_REFRESH_PEASHOOTER,
	TUTORIAL_LEVEL_1_COMPLETED,
	TUTORIAL_LEVEL_2_PICK_UP_SUNFLOWER,
	TUTORIAL_LEVEL_2_PLANT_SUNFLOWER,
	TUTORIAL_LEVEL_2_REFRESH_SUNFLOWER,
	TUTORIAL_LEVEL_2_COMPLETED,
	TUTORIAL_MORESUN_PICK_UP_SUNFLOWER,
	TUTORIAL_MORESUN_PLANT_SUNFLOWER,
	TUTORIAL_MORESUN_REFRESH_SUNFLOWER,
	TUTORIAL_MORESUN_COMPLETED,
	TUTORIAL_SLOT_MACHINE_PULL,
	TUTORIAL_SLOT_MACHINE_COMPLETED,
	TUTORIAL_SHOVEL_PICKUP,
	TUTORIAL_SHOVEL_DIG,
	TUTORIAL_SHOVEL_KEEP_DIGGING,
	TUTORIAL_SHOVEL_COMPLETED,
	TUTORIAL_ZOMBIQUARIUM_BUY_SNORKEL,
	TUTORIAL_ZOMBIQUARIUM_BOUGHT_SNORKEL,
	TUTORIAL_ZOMBIQUARIUM_CLICK_TROPHY,
	TUTORIAL_ZEN_GARDEN_PICKUP_WATER,
	TUTORIAL_ZEN_GARDEN_WATER_PLANT,
	TUTORIAL_ZEN_GARDEN_KEEP_WATERING,
	TUTORIAL_ZEN_GARDEN_VISIT_STORE,
	TUTORIAL_ZEN_GARDEN_FERTILIZE_PLANTS,
	TUTORIAL_ZEN_GARDEN_COMPLETED,
	TUTORIAL_WHACK_A_ZOMBIE_BEFORE_PICK_SEED,
	TUTORIAL_WHACK_A_ZOMBIE_PICK_SEED,
	TUTORIAL_WHACK_A_ZOMBIE_COMPLETED
};

class Board : public Sexy::Widget, public Sexy::ButtonListener
{
//public:
//	uint8_t data[0x8C];
public:
	LawnApp* mApp;													//+0x8C
	DataArray<Zombie>				mZombies;												//+0x90
	DataArray<Plant>				mPlants;												//+0xAC
	DataArray<Projectile>			mProjectiles;											//+0xC8
	DataArray<Coin>					mCoins;													//+0xE4
	DataArray<LawnMower>			mLawnMowers;											//+0x100
	DataArray<GridItem>				mGridItems;												//+0x11C
	CursorObject* mCursorObject;											//+0x138
	CursorPreview* mCursorPreview;											//+0x13C
	MessageWidget* mAdvice;												//+0x140
	SeedBank* mSeedBank;												//+0x144
	GameButton* mMenuButton;											//+0x148
	GameButton* mStoreButton;											//+0x14C
	bool							mIgnoreMouseUp;											//+0x150
	ToolTipWidget* mToolTip;												//+0x154
	Sexy::Font* mDebugFont;												//+0x158
	CutScene* mCutScene;												//+0x15C
	Challenge* mChallenge;												//+0x160
	bool							mPaused;												//+0x164
	GridSquareType					mGridSquareType[MAX_GRID_SIZE_X][MAX_GRID_SIZE_Y];		//+0x168
	int								mGridCelLook[MAX_GRID_SIZE_X][MAX_GRID_SIZE_Y];			//+0x240
	int								mGridCelOffset[MAX_GRID_SIZE_X][MAX_GRID_SIZE_Y][2];	//+0x318
	int								mGridCelFog[MAX_GRID_SIZE_X][MAX_GRID_SIZE_Y + 1];		//+0x4C8
	bool							mEnableGraveStones;										//+0x5C4
	int								mSpecialGraveStoneX;									//+0x5C8
	int								mSpecialGraveStoneY;									//+0x5CC
	float							mFogOffset;												//+0x5D0
	int								mFogBlownCountDown;										//+0x5D4
	PlantRowType					mPlantRow[MAX_GRID_SIZE_Y];								//+0x5D8
	int								mWaveRowGotLawnMowered[MAX_GRID_SIZE_Y];				//+0x5F0
	int								mBonusLawnMowersRemaining;								//+0x608
	int								mIceMinX[MAX_GRID_SIZE_Y];								//+0x60C
	int								mIceTimer[MAX_GRID_SIZE_Y];								//+0x624
	ParticleSystemID				mIceParticleID[MAX_GRID_SIZE_Y];						//+0x63C
	TodSmoothArray					mRowPickingArray[MAX_GRID_SIZE_Y];						//+0x654
	ZombieType						mZombiesInWave[MAX_ZOMBIE_WAVES][MAX_ZOMBIES_IN_WAVE];	//+0x6B4
	bool							mZombieAllowed[100];									//+0x54D4
	int								mSunCountDown;											//+0x5538
	int								mNumSunsFallen;											//+0x553C
	int								mShakeCounter;											//+0x5540
	int								mShakeAmountX;											//+0x5544
	int								mShakeAmountY;											//+0x5548
	BackgroundType					mBackground;											//+0x554C
	int								mLevel;													//+0x5550
	int								mSodPosition;											//+0x5554
	int								mPrevMouseX;											//+0x5558
	int								mPrevMouseY;											//+0x555C
	int								mSunMoney;												//+0x5560
	int								mNumWaves;												//+0x5564
	int								mMainCounter;											//+0x5568
	int								mEffectCounter;											//+0x556C
	int								mDrawCount;												//+0x5570
	int								mRiseFromGraveCounter;									//+0x5574
	int								mOutOfMoneyCounter;										//+0x5578
	int								mCurrentWave;											//+0x557C
	int								mTotalSpawnedWaves;										//+0x5580
	TutorialState					mTutorialState;											//+0x5584
	ParticleSystemID				mTutorialParticleID;									//+0x5588
	int								mTutorialTimer;											//+0x558C
	int								mLastBungeeWave;										//+0x5590
	int								mZombieHealthToNextWave;								//+0x5594
	int								mZombieHealthWaveStart;									//+0x5598
	int								mZombieCountDown;										//+0x559C
	int								mZombieCountDownStart;									//+0x55A0
	int								mHugeWaveCountDown;										//+0x55A4
	bool							mHelpDisplayed[NUM_ADVICE_TYPES];						//+0x55A8
	AdviceType						mHelpIndex;												//+0x55EC
	bool							mFinalBossKilled;										//+0x55F0
	bool							mShowShovel;											//+0x55F1
	int								mCoinBankFadeCount;										//+0x55F4
	DebugTextMode					mDebugTextMode;											//+0x55F8
	bool							mLevelComplete;											//+0x55FC
	int								mBoardFadeOutCounter;									//+0x5600
	int								mNextSurvivalStageCounter;								//+0x5604
	int								mScoreNextMowerCounter;									//+0x5608
	bool							mLevelAwardSpawned;										//+0x560C
	int								mProgressMeterWidth;									//+0x5610
	int								mFlagRaiseCounter;										//+0x5614
	int								mIceTrapCounter;										//+0x5618
	int								mBoardRandSeed;											//+0x561C
	ParticleSystemID				mPoolSparklyParticleID;									//+0x5620
	ReanimationID					mFwooshID[MAX_GRID_SIZE_Y][12];							//+0x5624
	int								mFwooshCountDown;										//+0x5744
	int								mTimeStopCounter;										//+0x5748
	bool							mDroppedFirstCoin;										//+0x574C
	int								mFinalWaveSoundCounter;									//+0x5750
	int								mCobCannonCursorDelayCounter;							//+0x5754
	int								mCobCannonMouseX;										//+0x5758
	int								mCobCannonMouseY;										//+0x575C
	bool							mKilledYeti;											//+0x5760
	bool							mMustacheMode;											//+0x5761
	bool							mSuperMowerMode;										//+0x5762
	bool							mFutureMode;											//+0x5763
	bool							mPinataMode;											//+0x5764
	bool							mDanceMode;												//+0x5765
	bool							mDaisyMode;												//+0x5766
	bool							mSukhbirMode;											//+0x5767
	BoardResult						mPrevBoardResult;										//+0x5768
	int								mTriggeredLawnMowers;									//+0x576C
	int								mPlayTimeActiveLevel;									//+0x5770
	int								mPlayTimeInactiveLevel;									//+0x5774
	int								mMaxSunPlants;											//+0x5778
	int								mStartDrawTime;											//+0x577C
	int								mIntervalDrawTime;										//+0x5780
	int								mIntervalDrawCountStart;								//+0x5784
	float							mMinFPS;												//+0x5788
	int								mPreloadTime;											//+0x578C
	int								mGameID;												//+0x5790
	int								mGravesCleared;											//+0x5794
	int								mPlantsEaten;											//+0x5798
	int								mPlantsShoveled;										//+0x579C
	int								mCoinsCollected;										//+0x57A0
	int								mDiamondsCollected;										//+0x57A4
	int								mPottedPlantsCollected;									//+0x57A8
	int								mChocolateCollected;									//+0x57AC

public:
	Coin* AddCoin(int theX, int theY, CoinType theCoinType, CoinMotion theCoinMotion);
	Plant* AddPlant(int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType = SEED_NONE);
	bool IteratePlants(Plant*& thePlant);
	bool IterateZombies(Zombie*& theZombie);
	bool IterateProjectiles(Projectile*& theProjectile);
	bool IterateReanimations(Reanimation*& theReanimation);
	Zombie* ZombieTryToGet(ZombieID theZombieID);
	Plant* PlantTryToGet(PlantID thePlantID);
	Projectile* AddProjectile(int theX, int theY, int theRenderOrder, int theRow, ProjectileType theProjectileType);
	void KillAllZombiesInRadius(int theRow, int theX, int theY, int theRadius, int theRowRange, bool theBurn, int theDamageRangeFlags);
	int	PixelToGridX(int theX, int theY);
	int	PixelToGridY(int theX, int theY);
	Zombie* AddZombieInRow(ZombieType theZombieType, int theRow, int theFromWave);
	ZombieID						ZombieGetID(Zombie* theZombie);
	PlantID						    PlantGetID(Plant* thePlant);
	void GetPlantsOnLawn(int theGridX, int theGridY, PlantsOnLawn* thePlantOnLawn);
	float GetPosYBasedOnRow(float thePosX, int theRow);
	int GridToPixelX(int theGridX, int theGridY);
	int GridToPixelY(int theGridX, int theGridY);
	void ShakeBoard(int theShakeAmountX, int theShakeAmountY);
	static int MakeRenderOrder(RenderLayer theRenderLayer, int theRow, int theLayerOffset);
	GridItem* GetGriditemAt(GridItemType theGridItemType, int theGridX, int theGridY);
	bool StageHasPool();
	Plant* NewPlant(int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType);
	void PickUpTool(GameObjectType theGameObjectType);
	void ClearCursor();
	Plant* FindUmbrellaPlant(int theGridX, int theGridY);
	Plant* GetFlowerPotAt(int theGridX, int theGridY);
	void Draw(Sexy::Graphics* g);
	void DrawUIBottom(Sexy::Graphics* g);
	void DrawUICoinBank(Sexy::Graphics* g);
	void DrawUITop(Sexy::Graphics* g);
	void DrawBackdrop(Sexy::Graphics* g);
	void Update();
	void LoadBackgroundImages();
	GridItem* AddACrater(int theGridX, int theGridY);
	bool							TakeSunMoney(int theAmount);
	bool							CanTakeSunMoney(int theAmount);
};

int GetRectOverlap(const Sexy::Rect& rect1, const Sexy::Rect& rect2);
bool GetCircleRectOverlap(int theCircleX, int theCircleY, int theRadius, const Sexy::Rect& theRect);