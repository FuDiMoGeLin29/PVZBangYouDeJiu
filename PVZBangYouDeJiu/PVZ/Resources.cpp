#include "Resources.h"

namespace Sexy
{
	Image*& IMAGE_REANIM_CORNPULT_BUTTER_SPLAT = *(Image**)0x6A78C8;
	Font*& FONT_BRIANNETOD16 = *(Font**)0x6A7224;
	Image*& IMAGE_REANIM_ZOMBIE_CATAPULT_BASKETBALL = *(Image**)0x6A72F8;
	Image*& IMAGE_REANIM_ZOMBIE_CONE1 = *(Image**)0x6A7504;
	Image*& IMAGE_BLANK = *(Image**)0x6A77BC;
	Image*& IMAGE_REANIM_ZOMBIE_CONE2 = *(Image**)0x6A73E4;
	Image*& IMAGE_REANIM_ZOMBIE_CONE3 = *(Image**)0x6A77D4;
	Image*& IMAGE_REANIM_ZOMBIE_BUCKET1 = *(Image**)0x6A73B8;
	Image*& IMAGE_REANIM_ZOMBIE_BUCKET2 = *(Image**)0x6A7AF8;
	Image*& IMAGE_REANIM_ZOMBIE_BUCKET3 = *(Image**)0x6A7330;
	Font*& FONT_DWARVENTODCRAFT12 = *(Font**)0x6A7630;

	extern int& SOUND_BUTTONCLICK = *(int*)0x6A7594;
	int& SOUND_TAP = *(int*)0x6A7980;
	int& SOUND_GRAVEBUTTON = *(int*)0x6A76A0;
	int& SOUND_BLOVER = *(int*)0x6A7970;
	int& SOUND_DIAMOND = *(int*)0x6A7708;
	Image*& IMAGE_ALMANAC_CLOSEBUTTON = *(Image**)0x6A7660;
	Image*& IMAGE_ALMANAC_CLOSEBUTTONHIGHLIGHT = *(Image**)0x6A75A4;
	Image*& IMAGE_ALMANAC_INDEXBUTTON = *(Image**)0x6A73FC;
	Image*& IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT = *(Image**)0x6A73F4;
	Image*& IMAGE_CHALLENGE_BACKGROUND = *(Image**)0x6A780C;
	Image*& IMAGE_ZEN_NEXTGARDEN = *(Image**)0x6A75B4;                                   //0x6A75B4

	bool ExtractDelayLoad_ChallengeScreenResources(ResourceManager* theManager)
	{
		uintptr_t func = 0x475BD0;

		_asm
		{
			mov ecx, theManager;
			call func;
		}
	}
}