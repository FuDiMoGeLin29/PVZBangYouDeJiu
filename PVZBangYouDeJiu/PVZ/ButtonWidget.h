#ifndef __BUTTONWIDGET_H__
#define __BUTTONWIDGET_H__

#include "Widget.h"
#include "std_string_PVZ.h"

namespace Sexy
{

class Image;
class ButtonListener;

class ButtonWidget : public Widget
{
public:
	enum {
		BUTTON_LABEL_LEFT	= -1,
		BUTTON_LABEL_CENTER,
		BUTTON_LABEL_RIGHT
	};
	enum
	{
		COLOR_LABEL,
		COLOR_LABEL_HILITE,
		COLOR_DARK_OUTLINE,
		COLOR_LIGHT_OUTLINE,
		COLOR_MEDIUM_OUTLINE,
		COLOR_BKG,
		NUM_COLORS
	};

	int						mId;
	std_string_PVZ				mLabel;
	int						mLabelJustify;
	Font*					mFont;
	Image*					mButtonImage;
	Image*					mOverImage;
	Image*					mDownImage;	
	Image*					mDisabledImage;
	Rect					mNormalRect;
	Rect					mOverRect;
	Rect					mDownRect;
	Rect					mDisabledRect;

	bool					mInverted;
	bool					mBtnNoDraw;
	bool					mFrameNoDraw;
	ButtonListener*			mButtonListener;

	double					mOverAlpha;
	double					mOverAlphaSpeed;
	double					mOverAlphaFadeInSpeed;

	//bool					HaveButtonImage(Image *theImage, const Rect &theRect);
	//virtual void			DrawButtonImage(Graphics *g, Image *theImage, const Rect &theRect, int x, int y);
	bool IsMouseOver();
	

public:
	ButtonWidget() {};
	virtual ~ButtonWidget();

	// ÐÂÔöÐéº¯Êý
	virtual void DrawButtonImage(Sexy::Graphics*, Sexy::Image*, const Sexy::TRect<int>*, int, int);
	virtual void SetFont(Sexy::Font*);
	virtual bool IsButtonDown();

	ButtonWidget(int theId, ButtonListener* theButtonListener);
	virtual void			Draw(Graphics* g);
	virtual void			SetDisabled(bool isDisabled);
	virtual void			MouseEnter();
	virtual void			MouseLeave();
	virtual void			MouseMove(int theX, int theY);
	virtual void			MouseDown(int theX, int theY, int theClickCount);
	virtual void			MouseDown(int theX, int theY, int theBtnNum, int theClickCount);
	virtual void			MouseUp(int theX, int theY);
	virtual void			MouseUp(int theX, int theY, int theClickCount);
	virtual void			MouseUp(int theX, int theY, int theBtnNum, int theClickCount);
	virtual void			Update();
};

}

#endif //__BUTTONWIDGET_H__