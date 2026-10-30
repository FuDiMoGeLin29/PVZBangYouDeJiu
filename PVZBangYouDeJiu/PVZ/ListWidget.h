#ifndef __LISTWIDGET_H__
#define __LISTWIDGET_H__

#include "ScrollListener.h"
#include "Widget.h"

namespace Sexy 
{

typedef UnknownClass<0x10> SexyStringVector;
typedef UnknownClass<0x10> ColorVector;

class ScrollbarWidget;
class ListListener;
class Font;

class ListWidget : public Widget, public ScrollListener 
{
public:
	enum 
	{
		JUSTIFY_LEFT			=0,
		JUSTIFY_CENTER,
		JUSTIFY_RIGHT
	};

	enum 
	{
		COLOR_BKG				=0,
		COLOR_OUTLINE,
		COLOR_TEXT,
		COLOR_HILITE,
		COLOR_SELECT,
		COLOR_SELECT_TEXT,
	};

public:
	int							mId;	
	Font*						mFont;
	ScrollbarWidget*			mScrollbar;
	int							mJustify;

	SexyStringVector			mLines;
	ColorVector					mLineColors;
	double						mPosition;	
	double						mPageSize;
	int							mHiliteIdx;
	int							mSelectIdx;
	ListListener*				mListListener;		
	ListWidget*					mParent;
	ListWidget*					mChild;
	bool						mSortFromChild;		
	bool						mDrawOutline;
	int							mMaxNumericPlaces;
	int							mItemHeight;

	bool						mDrawSelectWhenHilited;
	bool						mDoFingerWhenHilited;

	//void						SetHilite(int theHiliteIdx, bool notifyListener = false);

public:
	ListWidget(int theId, Font *theFont, ListListener *theListListener);
	virtual ~ListWidget();

	virtual void				RemovedFromManager(WidgetManager *theManager);
	virtual void				Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void				SetColor(int theIdx, const Color& theColor);
	virtual void				OrderInManagerChanged();
	virtual void				Draw(Graphics *g);
	virtual void				MouseMove(int x, int y);
	virtual void				MouseWheel(int theDelta);
	virtual void				MouseDown(int x, int y, int theClickCount);
	virtual void				MouseDown(int x, int y, int theBtnNum, int theClickCount);
	virtual void				MouseLeave();




	virtual SexyString			GetSortKey(int theIdx);
	virtual void				Sort(bool ascending);
	virtual SexyString			GetStringAt(int theIdx);
	virtual int					AddLine(const SexyString& theLine, bool alphabetical);
	virtual void				SetLine(int theIdx, const SexyString& theString);
	virtual int					GetLineCount();
	virtual int					GetLineIdx(const SexyString& theLine);
	virtual void				SetLineColor(int theIdx, const Color& theColor);
	virtual void				SetLineColor(const SexyString& theLine, const Color& theColor);
	virtual void				RemoveLine(int theIdx);
	virtual void				RemoveAll();
	virtual int					GetOptimalWidth();
	virtual int					GetOptimalHeight();
	virtual void				SetSelect(int theSelectIdx);


	virtual void				ScrollPosition(int theId, double thePosition);
};

}

#endif // __LISTWIDGET_H__
