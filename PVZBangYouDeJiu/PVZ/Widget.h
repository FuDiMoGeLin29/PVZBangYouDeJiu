#ifndef __WIDGET_H__
#define __WIDGET_H__

#include "Common.h"
#include "Color.h"
#include "Insets.h"
#include "Graphics.h"
#include "KeyCodes.h"
#include <stdint.h>
#include "UnknownClass.h"
#include "WidgetContainer.h"

namespace Sexy
{

class WidgetManager;

class WidgetContainer;

//typedef std::vector<Color> ColorVector;

typedef UnknownClass<0x10> ColorVector;

class Widget : public WidgetContainer
{
public:
	bool mVisible; // 0x54
	bool mMouseVisible; // 0x55
	bool mDisabled; // 0x56
	bool mHasFocus; // 0x57
	bool mIsDown; // 0x58
	bool mIsOver; // 0x59
	bool mHasTransparencies; // 0x5a
	ColorVector mColors; // 0x5c
	Insets mMouseInsets; // 0x6c
	bool mDoFinger; // 0x7c
	bool mWantsFocus; // 0x7d
	Widget* mTabPrev; // 0x80
	Widget* mTabNext; // 0x84

	//static bool				mWriteColoredString;  // controls whether ^color^ works in calls to WriteString
	
	//void					WidgetRemovedHelper();

public:
	Widget();
	virtual ~Widget();

	// ---------- 新增虚函数（按虚表顺序）----------
	virtual void OrderInManagerChanged();
	virtual void SetVisible(bool isVisible);
	virtual void SetColors(int theColors[][3], int theNumColors);
	virtual void SetColors(int theColors[][4], int theNumColors);
	virtual void SetColor(int theIdx, const Color& theColor);
	virtual const Color& GetColor(int theIdx) const;
	virtual Color GetColor(int theIdx, const Color& theDefaultColor);
	virtual void SetDisabled(bool isDisabled);
	virtual void ShowFinger(bool on);
	virtual void Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void Resize(const Rect& theRect);
	virtual void Move(int theNewX, int theNewY);
	virtual bool WantsFocus();
	virtual void DrawOverlay(Graphics* g);
	virtual void DrawOverlay(Graphics* g, int thePriority);
	virtual void GotFocus();
	virtual void LostFocus();
	virtual void KeyChar(SexyChar theChar);
	virtual void KeyDown(KeyCode theKey);
	virtual void KeyUp(KeyCode theKey);
	virtual void MouseEnter();
	virtual void MouseLeave();
	virtual void MouseMove(int x, int y);
	virtual void MouseDown(int x, int y, int theCliclCount);
	virtual void MouseDown(int x, int y,int theBtnNumber , int theClickCount);
	virtual void MouseUp(int x, int y);           // 参数个数保留，具体含义参考原表
	virtual void MouseUp(int x, int y, int theClickCount);
	virtual void MouseUp(int x, int y, int theBtnNumber, int theClickCount);
	virtual void MouseDrag(int x, int y);
	virtual void MouseWheel(int theDelta);
	virtual bool IsPointVisible(int x, int y);
	virtual Rect WriteCenteredLine(Graphics* g, int anOffset, const SexyString& theLine);
	virtual Rect WriteCenteredLine(Graphics* g, int anOffset, const SexyString& theLine, Color color1, Color color2, const Point& offset);
	virtual int WriteString(Graphics* g, const SexyString& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
	virtual int WriteWordWrapped(Graphics* g, const Rect& theRect, const SexyString& theLine, int theLineSpacing, int theJustification);
	virtual int GetWordWrappedHeight(Graphics* g, int theWidth, const SexyString& theLine, int aLineSpacing);
	virtual int GetNumDigits(int theNumber);
	virtual void WriteNumberFromStrip(Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing);
	virtual bool Contains(int theX, int theY);
	virtual Rect GetInsetRect();
	//void					DeferOverlay(int thePriority = 0);	

	////////// Layout functions
	//int						Left()							{ return mX; } 
	//int						Top()							{ return mY; }
	//int						Right()							{ return mX + mWidth; }
	//int						Bottom()						{ return mY + mHeight; }
	//int						Width()							{ return mWidth; }
	//int						Height()						{ return mHeight; }

	//void					Layout(int theLayoutFlags, Widget *theRelativeWidget, int theLeftPad = 0, int theTopPad = 0, int theWidthPad = 0, int theHeightPad = 0);
	virtual void AddedToManager(WidgetManager* manager);
	virtual void RemovedFromManager(WidgetManager* manager);
	virtual void Update();
	virtual void Draw(Graphics* g);
};

/////// Layout flags used in Widget::Layout method
enum LayoutFlags
{
	LAY_SameWidth		=		0x0001,
	LAY_SameHeight		=		0x0002,

	LAY_SetLeft			=		0x0010,
	LAY_SetTop			=		0x0020,
	LAY_SetWidth		=		0x0040,
	LAY_SetHeight		=		0x0080,

	LAY_Above			=		0x0100,
	LAY_Below			=		0x0200,
	LAY_Right			=		0x0400,
	LAY_Left			=		0x0800,

	LAY_SameLeft		=		0x1000,
	LAY_SameRight		=		0x2000,
	LAY_SameTop			=		0x4000,
	LAY_SameBottom		=		0x8000,

	LAY_GrowToRight		=		0x10000,
	LAY_GrowToLeft		=		0x20000,
	LAY_GrowToTop		=		0x40000,
	LAY_GrowToBottom	=		0x80000,

	LAY_HCenter			=		0x100000,
	LAY_VCenter			=		0x200000,
	LAY_Max				=		0x400000,

	LAY_SameSize		=		LAY_SameWidth | LAY_SameHeight,
	LAY_SameCorner		=		LAY_SameLeft  | LAY_SameTop,
	LAY_SetPos			=		LAY_SetLeft   | LAY_SetTop,
	LAY_SetSize			=		LAY_SetWidth  | LAY_SetHeight
};


}

#endif //__WIDGET_H__
