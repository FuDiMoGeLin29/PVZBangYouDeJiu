#pragma once
#include "Color.h"
#include "TodList.h"
#include "Image.h"
#include "DataArray.h"
#include "SexyVector.h"
#include "Definition.h"
enum ParticleSystemID { PARTICLESYSTEMID_NULL };

enum ParticleEffect
{
	PARTICLE_NONE = -1,
	PARTICLE_MELONSPLASH,
	PARTICLE_WINTERMELON,
	PARTICLE_FUMECLOUD,
	PARTICLE_POPCORNSPLASH,
	PARTICLE_POWIE,
	PARTICLE_JACKEXPLODE,
	PARTICLE_ZOMBIE_HEAD,
	PARTICLE_ZOMBIE_ARM,
	PARTICLE_ZOMBIE_TRAFFIC_CONE,
	PARTICLE_ZOMBIE_PAIL,
	PARTICLE_ZOMBIE_HELMET,
	PARTICLE_ZOMBIE_FLAG,
	PARTICLE_ZOMBIE_DOOR,
	PARTICLE_ZOMBIE_NEWSPAPER,
	PARTICLE_ZOMBIE_HEADLIGHT,
	PARTICLE_POW,
	PARTICLE_ZOMBIE_POGO,
	PARTICLE_ZOMBIE_NEWSPAPER_HEAD,
	PARTICLE_ZOMBIE_BALLOON_HEAD,
	PARTICLE_SOD_ROLL,
	PARTICLE_GRAVE_STONE_RISE,
	PARTICLE_PLANTING,
	PARTICLE_PLANTING_POOL,
	PARTICLE_ZOMBIE_RISE,
	PARTICLE_GRAVE_BUSTER,
	PARTICLE_GRAVE_BUSTER_DIE,
	PARTICLE_POOL_SPLASH,
	PARTICLE_ICE_SPARKLE,
	PARTICLE_SEED_PACKET,
	PARTICLE_TALL_NUT_BLOCK,
	PARTICLE_DOOM,
	PARTICLE_DIGGER_RISE,
	PARTICLE_DIGGER_TUNNEL,
	PARTICLE_DANCER_RISE,
	PARTICLE_POOL_SPARKLY,
	PARTICLE_WALLNUT_EAT_SMALL,
	PARTICLE_WALLNUT_EAT_LARGE,
	PARTICLE_PEA_SPLAT,
	PARTICLE_BUTTER_SPLAT,
	PARTICLE_CABBAGE_SPLAT,
	PARTICLE_PUFF_SPLAT,
	PARTICLE_STAR_SPLAT,
	PARTICLE_ICE_TRAP,
	PARTICLE_SNOWPEA_SPLAT,
	PARTICLE_SNOWPEA_PUFF,
	PARTICLE_SNOWPEA_TRAIL,
	PARTICLE_LANTERN_SHINE,
	PARTICLE_SEED_PACKET_PICKUP,
	PARTICLE_POTATO_MINE,
	PARTICLE_POTATO_MINE_RISE,
	PARTICLE_PUFFSHROOM_TRAIL,
	PARTICLE_PUFFSHROOM_MUZZLE,
	PARTICLE_SEED_PACKET_FLASH,
	PARTICLE_WHACK_A_ZOMBIE_RISE,
	PARTICLE_ZOMBIE_LADDER,
	PARTICLE_UMBRELLA_REFLECT,
	PARTICLE_SEED_PACKET_PICK,
	PARTICLE_ICE_TRAP_ZOMBIE,
	PARTICLE_ICE_TRAP_RELEASE,
	PARTICLE_ZAMBONI_SMOKE,
	PARTICLE_GLOOMCLOUD,
	PARTICLE_ZOMBIE_POGO_HEAD,
	PARTICLE_ZAMBONI_TIRE,
	PARTICLE_ZAMBONI_EXPLOSION,
	PARTICLE_ZAMBONI_EXPLOSION2,
	PARTICLE_CATAPULT_EXPLOSION,
	PARTICLE_MOWER_CLOUD,
	PARTICLE_BOSS_ICE_BALL,
	PARTICLE_BLASTMARK,
	PARTICLE_COIN_PICKUP_ARROW,
	PARTICLE_PRESENT_PICKUP,
	PARTICLE_IMITATER_MORPH,
	PARTICLE_MOWERED_ZOMBIE_HEAD,
	PARTICLE_MOWERED_ZOMBIE_ARM,
	PARTICLE_ZOMBIE_HEAD_POOL,
	PARTICLE_ZOMBIE_BOSS_FIREBALL,
	PARTICLE_FIREBALL_DEATH,
	PARTICLE_ICEBALL_DEATH,
	PARTICLE_ICEBALL_TRAIL,
	PARTICLE_FIREBALL_TRAIL,
	PARTICLE_BOSS_EXPLOSION,
	PARTICLE_SCREEN_FLASH,
	PARTICLE_TROPHY_SPARKLE,
	PARTICLE_PORTAL_CIRCLE,
	PARTICLE_PORTAL_SQUARE,
	PARTICLE_POTTED_PLANT_GLOW,
	PARTICLE_POTTED_WATER_PLANT_GLOW,
	PARTICLE_POTTED_ZEN_GLOW,
	PARTICLE_MIND_CONTROL,
	PARTICLE_VASE_SHATTER,
	PARTICLE_VASE_SHATTER_LEAF,
	PARTICLE_VASE_SHATTER_ZOMBIE,
	PARTICLE_AWARD_PICKUP_ARROW,
	PARTICLE_ZOMBIE_SEAWEED,
	PARTICLE_ZOMBIE_MUSTACHE,
	PARTICLE_ZOMBIE_SUNGLASS,
	PARTICLE_ZOMBIE_PINATA,
	PARTICLE_DUST_SQUASH,
	PARTICLE_DUST_FOOT,
	PARTICLE_ZOMBIE_DAISIES,
	PARTICLE_CREDIT_STROBE,
	PARTICLE_CREDITS_RAYSWIPE,
	PARTICLE_CREDITS_ZOMBIEHEADWIPE,
	PARTICLE_STARBURST,
	PARTICLE_CREDITS_FOG,
	PARTICLE_PERSENT_PICK_UP_ARROW,
	NUM_PARTICLES
};

enum ParticleEmitterID { PARTICLEEMITTERID_NULL };

enum EmitterType
{
	EMITTER_CIRCLE,
	EMITTER_BOX,
	EMITTER_BOX_PATH,
	EMITTER_CIRCLE_PATH,
	EMITTER_CIRCLE_EVEN_SPACING
};

class FloatParameterTrackNode;

class ParticleField;

class TodEmitterDefinition
{
public:
	Sexy::Image* mImage;
	int                         mImageCol;
	int                         mImageRow;
	int                         mImageFrames;
	int                         mAnimated;
	int                         mParticleFlags;
	EmitterType                 mEmitterType;
	const char* mName;
	const char* mOnDuration;
	FloatParameterTrack         mSystemDuration;
	FloatParameterTrack         mCrossFadeDuration;
	FloatParameterTrack         mSpawnRate;
	FloatParameterTrack         mSpawnMinActive;
	FloatParameterTrack         mSpawnMaxActive;
	FloatParameterTrack         mSpawnMaxLaunched;
	FloatParameterTrack         mEmitterRadius;
	FloatParameterTrack         mEmitterOffsetX;
	FloatParameterTrack         mEmitterOffsetY;
	FloatParameterTrack         mEmitterBoxX;
	FloatParameterTrack         mEmitterBoxY;
	FloatParameterTrack         mEmitterSkewX;
	FloatParameterTrack         mEmitterSkewY;
	FloatParameterTrack         mEmitterPath;
	FloatParameterTrack         mParticleDuration;
	FloatParameterTrack         mLaunchSpeed;
	FloatParameterTrack         mLaunchAngle;
	FloatParameterTrack         mSystemRed;
	FloatParameterTrack         mSystemGreen;
	FloatParameterTrack         mSystemBlue;
	FloatParameterTrack         mSystemAlpha;
	FloatParameterTrack         mSystemBrightness;
	ParticleField* mParticleFields;
	int                         mParticleFieldCount;
	ParticleField* mSystemFields;
	int                         mSystemFieldCount;
	FloatParameterTrack         mParticleRed;
	FloatParameterTrack         mParticleGreen;
	FloatParameterTrack         mParticleBlue;
	FloatParameterTrack         mParticleAlpha;
	FloatParameterTrack         mParticleBrightness;
	FloatParameterTrack         mParticleSpinAngle;
	FloatParameterTrack         mParticleSpinSpeed;
	FloatParameterTrack         mParticleScale;
	FloatParameterTrack         mParticleStretch;
	FloatParameterTrack         mCollisionReflect;
	FloatParameterTrack         mCollisionSpin;
	FloatParameterTrack         mClipTop;
	FloatParameterTrack         mClipBottom;
	FloatParameterTrack         mClipLeft;
	FloatParameterTrack         mClipRight;
	FloatParameterTrack         mAnimationRate;
};

class TodParticleDefinition
{
public:
	TodEmitterDefinition* mEmitterDefs;
	int                         mEmitterDefCount;
};

class TodParticleSystem;

enum ParticleSystemTracks
{
	TRACK_SPAWN_RATE,
	TRACK_SPAWN_MIN_ACTIVE,
	TRACK_SPAWN_MAX_ACTIVE,
	TRACK_SPAWN_MAX_LAUNCHED,
	TRACK_EMITTER_PATH,
	TRACK_SYSTEM_RED,
	TRACK_SYSTEM_GREEN,
	TRACK_SYSTEM_BLUE,
	TRACK_SYSTEM_ALPHA,
	TRACK_SYSTEM_BRIGHTNESS,
	NUM_SYSTEM_TRACKS
};

enum ParticleID { PARTICLEID_NULL };

#define MAX_PARTICLE_FIELDS 4

class TodParticleEmitter
{
public:
	TodEmitterDefinition* mEmitterDef;													//+0x0
	TodParticleSystem* mParticleSystem;												//+0x4
	TodList<ParticleID>				mParticleList;													//+0x8
	float							mSpawnAccum;													//+0x18
	Sexy::SexyVector2				mSystemCenter;													//+0x1C
	int								mParticlesSpawned;												//+0x24
	int								mSystemAge;														//+0x28
	int								mSystemDuration;												//+0x2C
	float							mSystemTimeValue;												//+0x30
	float							mSystemLastTimeValue;											//+0x34
	bool							mDead;															//+0x38
	Sexy::Color						mColorOverride;													//+0x3C
	bool							mExtraAdditiveDrawOverride;										//+0x4C
	float							mScaleOverride;													//+0x50
	Sexy::Image* mImageOverride;													//+0x54
	ParticleEmitterID				mCrossFadeEmitterID;											//+0x58
	int								mEmitterCrossFadeCountDown;										//+0x5C
	int								mFrameOverride;													//+0x60
	float							mTrackInterp[ParticleSystemTracks::NUM_SYSTEM_TRACKS];			//+0x64
	float							mSystemFieldInterp[MAX_PARTICLE_FIELDS][2];						//+0x8C

public:
	//void							TodEmitterInitialize(float theX, float theY, TodParticleSystem* theSystem, TodEmitterDefinition* theEmitterDef);
	//void							Update();
	//void							Draw(Sexy::Graphics* g);
	//void							SystemMove(float theX, float theY);
	//static bool						GetRenderParams(TodParticle* theParticle, ParticleRenderParams* theParams);
	//void							DrawParticle(Sexy::Graphics* g, TodParticle* theParticle, TodTriangleGroup* theTriangleGroup);
	//void							UpdateSpawning();
	//bool							UpdateParticle(TodParticle* theParticle);
	//TodParticle* SpawnParticle(int theIndex, int theSpawnCount);
	//bool							CrossFadeParticle(TodParticle* theParticle, TodParticleEmitter* theToEmitter);
	//void							CrossFadeEmitter(TodParticleEmitter* theToEmitter);
	//bool							CrossFadeParticleToName(TodParticle* theParticle, const char* theEmitterName);
	//void							DeleteAll();
	//void							UpdateParticleField(TodParticle* theParticle, ParticleField* theParticleField, float theParticleTimeValue, int theFieldIndex);
	//void							UpdateSystemField(ParticleField* theParticleField, float theParticleTimeValue, int theFieldIndex);
	//float				            SystemTrackEvaluate(FloatParameterTrack& theTrack, ParticleSystemTracks theSystemTrack);
	//static float		            ParticleTrackEvaluate(FloatParameterTrack& theTrack, TodParticle* theParticle, ParticleTracks theParticleTrack);
	//void							DeleteParticle(TodParticle* theParticle);
	//void							DeleteNonCrossFading();
};

class TodParticleEmitter;
class TodParticle;

class TodParticleHolder
{
public:
	DataArray<TodParticleSystem>	mParticleSystems;
	DataArray<TodParticleEmitter>	mEmitters;
	DataArray<TodParticle>			mParticles;
	TodAllocator					mParticleListNodeAllocator;
	TodAllocator					mEmitterListNodeAllocator;

public:
	//~TodParticleHolder();

	//void							InitializeHolder();
	//void							DisposeHolder();
	//TodParticleSystem* AllocParticleSystemFromDef(float theX, float theY, int theRenderOrder, TodParticleDefinition* theDefinition, ParticleEffect theParticleEffect);
	TodParticleSystem* AllocParticleSystem(float theX, float theY, int theRenderOrder, ParticleEffect theParticleEffect);
	//bool					        IsOverLoaded();
};

class TodParticleSystem
{
public:
	ParticleEffect					mEffectType;					//+0x0
	TodParticleDefinition* mParticleDef;					//+0x4
	TodParticleHolder* mParticleHolder;				//+0x8
	TodList<ParticleEmitterID>		mEmitterList;					//+0xC
	bool							mDead;							//+0x1C
	bool							mIsAttachment;					//+0x1D
	int								mRenderOrder;					//+0x20
	bool							mDontUpdate;					//+0x24
public:
	void OverrideScale(float theScale);
	void OverrideColor(const char* theEmitterName, const Sexy::Color& theColor);
	void OverrideImage(const char* theEmitterName, Sexy::Image* theImage);
};