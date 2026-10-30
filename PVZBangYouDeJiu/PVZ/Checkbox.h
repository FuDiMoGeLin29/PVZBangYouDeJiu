#ifndef __CHECKBOX_H__
#define __CHECKBOX_H__

#include "Widget.h"

namespace Sexy
{

class CheckboxListener;
class Image;

class Checkbox : public Widget
{	
protected:
	CheckboxListener*		mListener;

public:
	int						mId;

	bool					mChecked;

	Image*					mUncheckedImage;
	Image*					mCheckedImage;

	Rect					mCheckedRect;
	Rect					mUncheckedRect;

	Color					mOutlineColor;	// These are only used if no image is specified
	Color					mBkgColor;
	Color					mCheckColor;

public:
	virtual ~Checkbox();

	virtual void SetChecked(bool checked, bool tellListener);
	virtual bool IsChecked();

public:
	Checkbox(int theId, CheckboxListener* theCheckboxListener);
	Checkbox(Image* theUncheckedImage, Image* theCheckedImage, int theId, CheckboxListener* theCheckboxListener);
public:
	virtual void Draw(Graphics* g);
	virtual void MouseDown(int button, int x, int y);
	virtual void MouseDown(int button, int x, int y, int clickCount);
};

}

#endif //__CHECKBOX_H__