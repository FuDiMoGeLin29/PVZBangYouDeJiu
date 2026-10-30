#ifndef __SLIDER_H__
#define __SLIDER_H__

#include "Widget.h"

namespace Sexy
{

class SliderListener;

class Slider : public Widget
{
public:		
	SliderListener*			mListener;
	double					mVal;
	int						mId;
	Image*					mTrackImage;
	Image*					mThumbImage;

	bool					mDragging;
	int						mRelX;
	int						mRelY;

	bool					mHorizontal;

public:
	Slider(int theId, SliderListener* theListener);

	// ÐÂÔöÐéº¯Êý
	virtual void SetValue(long double value) = 0;
	virtual bool HasTransparencies() = 0;

	//virtual void			SetValue(double theValue);

	//virtual bool			HasTransparencies();
	//virtual void			Draw(Graphics* g);	

	//virtual void			MouseMove(int x, int y);
	//virtual void			MouseDown(int x, int y, int theClickCount);
	//virtual void			MouseDrag(int x, int y);
	//virtual void			MouseUp(int x, int y);
	//virtual void			MouseLeave();
};

}

#endif //__SLIDER_H__