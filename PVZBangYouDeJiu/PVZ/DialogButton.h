#ifndef __DIALOGBUTTON_H__
#define __DIALOGBUTTON_H__

#include "ButtonWidget.h"

namespace Sexy
{

class DialogButton : public ButtonWidget
{
public:	
	Image*					mComponentImage;
	int						mTranslateX, mTranslateY;
	int						mTextOffsetX, mTextOffsetY;

public:
	DialogButton() : mComponentImage(0), mTranslateX(0), mTranslateY(0), mTextOffsetX(0), mTextOffsetY(0) {};
	DialogButton(int theId, ButtonListener* theListener);
	DialogButton(Image* theComponentImage, int theId, ButtonListener* theListener);

	virtual void			Draw(Graphics* g);
};

}

#endif //__DIALOGBUTTON_H__