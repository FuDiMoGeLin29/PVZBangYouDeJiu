#pragma once
#include "Font.h"
#include "Image.h"
#include "ResourceManager.h"




namespace Sexy
{
	extern Image*& IMAGE_REANIM_CORNPULT_BUTTER_SPLAT;
	extern Font*& FONT_BRIANNETOD16;
	extern Image*& IMAGE_REANIM_ZOMBIE_CATAPULT_BASKETBALL;
	extern Image*& IMAGE_REANIM_ZOMBIE_CONE1;
	extern Image*& IMAGE_BLANK;
	extern Image*& IMAGE_REANIM_ZOMBIE_CONE2;
	extern Image*& IMAGE_REANIM_ZOMBIE_CONE3;
	extern Image*& IMAGE_REANIM_ZOMBIE_BUCKET1;
	extern Image*& IMAGE_REANIM_ZOMBIE_BUCKET2;
	extern Image*& IMAGE_REANIM_ZOMBIE_BUCKET3;
	extern int&		    SOUND_BUTTONCLICK;                                      //0x6A7594
	extern int& SOUND_TAP;		//0x6A7980
	extern Font*& FONT_DWARVENTODCRAFT12;
	extern int& SOUND_GRAVEBUTTON;
	extern int& SOUND_BLOVER;
	extern int& SOUND_DIAMOND;
	extern Image*& IMAGE_ALMANAC_CLOSEBUTTON;
	extern Image*& IMAGE_ALMANAC_CLOSEBUTTONHIGHLIGHT;
	extern Image*& IMAGE_ALMANAC_INDEXBUTTON;                              //0x6A73FC
	extern Image*& IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT;                     //0x6A73F4
	extern Image*& IMAGE_CHALLENGE_BACKGROUND;                             //0x6A780C
	extern Image*& IMAGE_ZEN_NEXTGARDEN;                                   //0x6A75B4

	bool ExtractDelayLoad_ChallengeScreenResources(ResourceManager* theManager);
}
