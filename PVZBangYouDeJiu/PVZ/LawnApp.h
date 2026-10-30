#pragma once
#include <stdint.h>
#include "TodCommon.h"
#include "TodFoley.h"
#include "Reanimator.h"
#include "std_string_PVZ.h"
#include <Windows.h>
#include "TodParticle.h"
//#include "../ConsoleInterface.h"
#include "Common.h"
#include "SexyApp.h"
//class TodParticleSystem;

class Board;
class GameSelector;
class ChallengeDefinition;
class SeedChooserScreen;
class AwardScreen;
class CreditScreen;
class PoolEffect;
class ZenGarden;
class PottedPlant;
class EffectSystem;
class ReanimatorCache;
class ProfileMgr;
class PlayerInfo;
class Music;
class TitleScreen;
class PopDRMComm;
class ChallengeScreen;
class StoreScreen;
class AlmanacDialog;
class TypingCheck;
namespace Sexy
{
	class Dialog;
	class Graphics;
	class ButtonWidget;
};
enum AwardType;
enum ChallengePage;

class TodFoley;
class ButtonList
{
public:
	uint8_t data[0xC];
};
class ImageList
{
public:
	uint8_t data[0xC];
};

class LevelStats
{
public:
	int								mUnusedLawnMowers;

public:
	LevelStats() { Reset(); }
	inline void						Reset() { mUnusedLawnMowers = 0; }
};

enum GameScenes
{
	SCENE_LOADING,
	SCENE_MENU,
	SCENE_LEVEL_INTRO,
	SCENE_PLAYING,
	SCENE_ZOMBIES_WON,
	SCENE_AWARD,
	SCENE_CREDIT,
	SCENE_CHALLENGE
};

enum BoardResult
{
	BOARDRESULT_NONE,
	BOARDRESULT_WON,
	BOARDRESULT_LOST,
	BOARDRESULT_RESTART,
	BOARDRESULT_QUIT,
	BOARDRESULT_QUIT_APP,
	BOARDRESULT_CHEAT
};

enum CrazyDaveState
{
	CRAZY_DAVE_OFF,
	CRAZY_DAVE_ENTERING,
	CRAZY_DAVE_LEAVING,
	CRAZY_DAVE_IDLING,
	CRAZY_DAVE_TALKING,
	CRAZY_DAVE_HANDING_TALKING,
	CRAZY_DAVE_HANDING_IDLING
};

enum TrialType
{
	TRIALTYPE_NONE,
	TRIALTYPE_STAGELOCKED
};

enum GameMode
{
	GAMEMODE_ADVENTURE,
	GAMEMODE_SURVIVAL_NORMAL_STAGE_1,
	GAMEMODE_SURVIVAL_NORMAL_STAGE_2,
	GAMEMODE_SURVIVAL_NORMAL_STAGE_3,
	GAMEMODE_SURVIVAL_NORMAL_STAGE_4,
	GAMEMODE_SURVIVAL_NORMAL_STAGE_5,
	GAMEMODE_SURVIVAL_HARD_STAGE_1,
	GAMEMODE_SURVIVAL_HARD_STAGE_2,
	GAMEMODE_SURVIVAL_HARD_STAGE_3,
	GAMEMODE_SURVIVAL_HARD_STAGE_4,
	GAMEMODE_SURVIVAL_HARD_STAGE_5,
	GAMEMODE_SURVIVAL_ENDLESS_STAGE_1,
	GAMEMODE_SURVIVAL_ENDLESS_STAGE_2,
	GAMEMODE_SURVIVAL_ENDLESS_STAGE_3,
	GAMEMODE_SURVIVAL_ENDLESS_STAGE_4,
	GAMEMODE_SURVIVAL_ENDLESS_STAGE_5,
	GAMEMODE_CHALLENGE_WAR_AND_PEAS,
	GAMEMODE_CHALLENGE_WALLNUT_BOWLING,
	GAMEMODE_CHALLENGE_SLOT_MACHINE,
	GAMEMODE_CHALLENGE_RAINING_SEEDS,
	GAMEMODE_CHALLENGE_BEGHOULED,
	GAMEMODE_CHALLENGE_INVISIGHOUL,
	GAMEMODE_CHALLENGE_SEEING_STARS,
	GAMEMODE_CHALLENGE_ZOMBIQUARIUM,
	GAMEMODE_CHALLENGE_BEGHOULED_TWIST,
	GAMEMODE_CHALLENGE_LITTLE_TROUBLE,
	GAMEMODE_CHALLENGE_PORTAL_COMBAT,
	GAMEMODE_CHALLENGE_COLUMN,
	GAMEMODE_CHALLENGE_BOBSLED_BONANZA,
	GAMEMODE_CHALLENGE_SPEED,
	GAMEMODE_CHALLENGE_WHACK_A_ZOMBIE,
	GAMEMODE_CHALLENGE_LAST_STAND,
	GAMEMODE_CHALLENGE_WAR_AND_PEAS_2,
	GAMEMODE_CHALLENGE_WALLNUT_BOWLING_2,
	GAMEMODE_CHALLENGE_POGO_PARTY,
	GAMEMODE_CHALLENGE_FINAL_BOSS,
	GAMEMODE_CHALLENGE_ART_CHALLENGE_WALLNUT,
	GAMEMODE_CHALLENGE_SUNNY_DAY,
	GAMEMODE_CHALLENGE_RESODDED,
	GAMEMODE_CHALLENGE_BIG_TIME,
	GAMEMODE_CHALLENGE_ART_CHALLENGE_SUNFLOWER,
	GAMEMODE_CHALLENGE_AIR_RAID,
	GAMEMODE_CHALLENGE_ICE,
	GAMEMODE_CHALLENGE_ZEN_GARDEN,
	GAMEMODE_CHALLENGE_HIGH_GRAVITY,
	GAMEMODE_CHALLENGE_GRAVE_DANGER,
	GAMEMODE_CHALLENGE_SHOVEL,
	GAMEMODE_CHALLENGE_STORMY_NIGHT,
	GAMEMODE_CHALLENGE_BUNGEE_BLITZ,
	GAMEMODE_CHALLENGE_SQUIRREL,
	GAMEMODE_TREE_OF_WISDOM,
	GAMEMODE_SCARY_POTTER_1,
	GAMEMODE_SCARY_POTTER_2,
	GAMEMODE_SCARY_POTTER_3,
	GAMEMODE_SCARY_POTTER_4,
	GAMEMODE_SCARY_POTTER_5,
	GAMEMODE_SCARY_POTTER_6,
	GAMEMODE_SCARY_POTTER_7,
	GAMEMODE_SCARY_POTTER_8,
	GAMEMODE_SCARY_POTTER_9,
	GAMEMODE_SCARY_POTTER_ENDLESS,
	GAMEMODE_PUZZLE_I_ZOMBIE_1,
	GAMEMODE_PUZZLE_I_ZOMBIE_2,
	GAMEMODE_PUZZLE_I_ZOMBIE_3,
	GAMEMODE_PUZZLE_I_ZOMBIE_4,
	GAMEMODE_PUZZLE_I_ZOMBIE_5,
	GAMEMODE_PUZZLE_I_ZOMBIE_6,
	GAMEMODE_PUZZLE_I_ZOMBIE_7,
	GAMEMODE_PUZZLE_I_ZOMBIE_8,
	GAMEMODE_PUZZLE_I_ZOMBIE_9,
	GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS,
	GAMEMODE_UPSELL,
	GAMEMODE_INTRO,
	NUM_GAME_MODES
};

class LawnApp : public Sexy::SexyApp
{

public:
	Board* mBoard;											//+0x768
	TitleScreen* mTitleScreen;									//+0x76C
	GameSelector* mGameSelector;									//+0x770
	SeedChooserScreen* mSeedChooserScreen;								//+0x774
	AwardScreen* mAwardScreen;									//+0x778
	CreditScreen* mCreditScreen;									//+0x77C
	ChallengeScreen* mChallengeScreen;								//+0x780
	TodFoley* mSoundSystem;									//+0x784
	ButtonList						mControlButtonList;								//+0x788
	ImageList						mCreatedImageList;								//+0x794
	std_string_PVZ					mReferId;										//+0x7A0
	std_string_PVZ					mRegisterLink;									//+0x7BC
	std_string_PVZ					mMod;											//+0x7D8
	bool							mRegisterResourcesLoaded;						//+0x7F4
	bool							mTodCheatKeys;									//+0x7F5
	GameMode						mGameMode;										//+0x7F8
	GameScenes						mGameScene;										//+0x7FC
	bool							mLoadingZombiesThreadCompleted;					//+0x800
	bool							mFirstTimeGameSelector;							//+0x801
	int								mGamesPlayed;									//+0x804
	int								mMaxExecutions;									//+0x808
	int								mMaxPlays;										//+0x80C
	int								mMaxTime;										//+0x810
	bool							mEasyPlantingCheat;								//+0x814
	PoolEffect* mPoolEffect;									//+0x818
	ZenGarden* mZenGarden;										//+0x81C
	EffectSystem* mEffectSystem;									//+0x820
	ReanimatorCache* mReanimatorCache;								//+0x824
	ProfileMgr* mProfileMgr;									//+0x828
	PlayerInfo* mPlayerInfo;									//+0x82C
	LevelStats* mLastLevelStats;								//+0x830
	bool							mCloseRequest;									//+0x834
	int								mAppCounter;									//+0x838
	Music* mMusic;											//+0x83C
	ReanimationID					mCrazyDaveReanimID;								//+0x840
	CrazyDaveState					mCrazyDaveState;								//+0x844
	int								mCrazyDaveBlinkCounter;							//+0x848
	ReanimationID					mCrazyDaveBlinkReanimID;						//+0x84C
	int								mCrazyDaveMessageIndex;							//+0x850
	SexyString						mCrazyDaveMessageText;							//+0x854
	int								mAppRandSeed;									//+0x870
	HICON							mBigArrowCursor;								//+0x874
	PopDRMComm* mDRM;											//+0x878
	int								mSessionID;										//+0x87C
	int								mPlayTimeActiveSession;							//+0x880
	int								mPlayTimeInactiveSession;						//+0x884
	BoardResult						mBoardResult;									//+0x888
	bool							mSawYeti;										//+0x88C
	TypingCheck* mKonamiCheck;									//+0x890
	TypingCheck* mMustacheCheck;									//+0x894
	TypingCheck* mMoustacheCheck;								//+0x898
	TypingCheck* mSuperMowerCheck;								//+0x89C
	TypingCheck* mSuperMowerCheck2;								//+0x8A0
	TypingCheck* mFutureCheck;									//+0x8A4
	TypingCheck* mPinataCheck;									//+0x8A8
	TypingCheck* mDanceCheck;									//+0x8AC
	TypingCheck* mDaisyCheck;									//+0x8B0
	TypingCheck* mSukhbirCheck;									//+0x8B4
	bool							mMustacheMode;									//+0x8B8
	bool							mSuperMowerMode;								//+0x8B9
	bool							mFutureMode;									//+0x8BA
	bool							mPinataMode;									//+0x8BB
	bool							mDanceMode;										//+0x8BC
	bool							mDaisyMode;										//+0x8BD
	bool							mSukhbirMode;									//+0x8BE
	TrialType						mTrialType;										//+0x8C0
	bool							mDebugTrialLocked;								//+0x8C4
	bool							mMuteSoundsForCutscene;							//+0x8C5

public:
	// LawnApp 自身新增的纯虚函数
	virtual void LoadingCompleted() = 0;
	virtual void ShowResourceError(bool doExit) = 0;

public:
	ReanimationID					ReanimationGetID(Reanimation* theReanimation);
	Reanimation*					ReanimationTryToGet(ReanimationID theReanimationID);
	Reanimation*					AddReanimation(float theX, float theY, int theRenderOrder, ReanimationType theReanimationType);
	TodParticleSystem*				AddTodParticle(float theX, float theY, int theRenderOrder, ParticleEffect theEffect);
	void							PlayFoley(FoleyType theFoleyType);
	//void							PlaySample(int theSoundNum); //SexyAppBase
	void							SetCursor(int theCursorNum);
	void							PlayFoleyPitch(FoleyType theFoleyType, float thePitch);
	void							DoBackToMain();
	bool							IsWallnutBowlingLevel();
	bool							HasFinishedAdventure();
	bool							IsFirstTimeAdventureMode();
	void 							KillGameSelector();
	int								LawnMessageBox(int theDialogId, const SexyChar* theHeaderName, const SexyChar* theLinesName, const SexyChar* theButton1Name, const SexyChar* theButton2Name, int theButtonMode);

};

//extern FoleyParams					gLawnFoleyParamArray[(int)FoleyType::NUM_FOLEY];			//0x69FAD0
//extern ParticleParams				gLawnParticleArray[(int)ParticleEffect::NUM_PARTICLES];		//0x6A0FF0
extern ReanimationParams*			gLawnReanimationArray;	//0x6A1340
//extern ReanimationParams			gLawnReanimationArray[(int)ReanimationType::NUM_REANIMS];	//0x6A1340
//extern TrailParams					gLawnTrailArray[(int)TrailType::NUM_TRAILS];				//0x6A19F4

//extern int							gLawnStringFormatCount;
//extern TodStringListFormat			gLawnStringFormats[12];  //0x6A5010