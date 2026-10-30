#pragma once
#include "Widget.h"
#include "ButtonListener.h"

namespace Sexy
{
	class DialogButton;
}

enum SelectorAnimState
{
	SELECTOR_OPEN,
	SELECTOR_NEW_USER,
	SELECTOR_SHOW_SIGN,
	SELECTOR_IDLE
};

class GameSelector : public Sexy::Widget, public Sexy::ButtonListener
{
public:
	LawnApp* mApp;
	Sexy::DialogButton* mAdventureButton;
	Sexy::DialogButton* mMinigameButton;
	Sexy::DialogButton* mPuzzleButton;
	Sexy::DialogButton* mOptionsButton;
	Sexy::DialogButton* mQuitButton;
	Sexy::DialogButton* mHelpButton;
	Sexy::DialogButton* mStoreButton;
	Sexy::DialogButton* mAlmanacButton;
	Sexy::DialogButton* mZenGardenButton;
	Sexy::DialogButton* mSurvivalButton;
	Sexy::DialogButton* mChangeUserButton;
	Sexy::Widget* mOverlayWidget;
	bool mStartingGame;
	int mStartingGameCounter;
	bool mMinigamesLocked;
	bool mPuzzleLocked;
	bool mSurvivalLocked;
	bool mShowStartButton;
	ParticleSystemID mTrophyParticleID;
	ReanimationID mSelectorReanimID;
	ReanimationID mCloudReanimID[6];
	int mCloudCounter[6];
	ReanimationID mFlowerReanimID[3];
	ReanimationID mLeafReanimID;
	ReanimationID mHandReanimID;
	int mLeafCounter;
	SelectorAnimState mSelectorState;
	int mLevel;
	bool mLoading;
	ToolTipWidget* mToolTip;
};