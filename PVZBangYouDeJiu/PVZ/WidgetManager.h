#ifndef __WIDGETMANAGER_H__
#define __WIDGETMANAGER_H__

#include "Common.h"
#include "KeyCodes.h"
#include "UnknownClass.h"
#include "WidgetContainer.h"

namespace Sexy
{

class Widget;
class Image;
class MemoryImage;
class SexyAppBase;
class Graphics;
class WidgetContainer;

//typedef std::list<Widget*> WidgetList;

typedef UnknownClass<0xC> WidgetList;

enum
{
	WIDGETFLAGS_UPDATE			= 1,
	WIDGETFLAGS_MARK_DIRTY		= 2,
	WIDGETFLAGS_DRAW			= 4,
	WIDGETFLAGS_CLIP			= 8,	
	WIDGETFLAGS_ALLOW_MOUSE		= 16,
	WIDGETFLAGS_ALLOW_FOCUS		= 32,	
};

class PreModalInfo
{
public:
	Widget*					mBaseModalWidget;
	Widget*					mPrevBaseModalWidget;
	Widget*					mPrevFocusWidget;
	FlagsMod				mPrevBelowModalFlagsMod;
};

//typedef std::list<PreModalInfo> PreModalInfoList;
//
//typedef std::vector<std::pair<Widget*, int> > DeferredOverlayVector;

typedef UnknownClass<0xC> PreModalInfoList;

typedef UnknownClass<0x10> DeferredOverlayVector;

class WidgetManager : public WidgetContainer
{
public:	
	Widget* mDefaultTab; // 0x54
	Graphics* mCurG; // 0x58
	SexyAppBase* mApp; // 0x5c
	MemoryImage* mImage; // 0x60
	MemoryImage* mTransientImage; // 0x64
	bool mLastHadTransients; // 0x68
	Widget* mPopupCommandWidget; // 0x6c
	DeferredOverlayVector mDeferredOverlayWidgets; // 0x70
	int mMinDeferredOverlayPriority; // 0x80
	bool mHasFocus; // 0x84
	Widget* mFocusWidget; // 0x88
	Widget* mLastDownWidget; // 0x8c
	Widget* mOverWidget; // 0x90
	Widget* mBaseModalWidget; // 0x94
	FlagsMod mLostFocusFlagsMod; // 0x98
	FlagsMod mBelowModalFlagsMod; // 0xa0
	FlagsMod mDefaultBelowModalFlagsMod; // 0xa8
	PreModalInfoList mPreModalInfoList; // 0xb0
	TRect<int> mMouseDestRect; // 0xbc
	TRect<int> mMouseSourceRect; // 0xcc
	bool mMouseIn; // 0xdc
	int mLastMouseX; // 0xe0
	int mLastMouseY; // 0xe4
	int mDownButtons; // 0xe8
	int mActualDownButtons; // 0xec
	int mLastInputUpdateCnt; // 0xf0
	bool mKeyDown[0xFF]; // 0xf4
	int mLastDownButtonId; // 0x1f4
	int mWidgetFlags; // 0x1f8

protected:
	//int						GetWidgetFlags();
	//void					MouseEnter(Widget* theWidget);
	//void					MouseLeave(Widget* theWidget);

protected:
	//void					SetBaseModal(Widget* theWidget, const FlagsMod& theBelowFlagsMod);

public:
	WidgetManager(SexyAppBase* theApplet);
	virtual ~WidgetManager();
	//
	//void					FreeResources();		
	//void					AddBaseModal(Widget* theWidget, const FlagsMod& theBelowFlagsMod);
	//void					AddBaseModal(Widget* theWidget);
	//void					RemoveBaseModal(Widget* theWidget);
	//void					Resize(const Rect& theMouseDestRect, const Rect& theMouseSourceRect);
	//void					DisableWidget(Widget* theWidget);	
	//Widget*					GetAnyWidgetAt(int x, int y, int* theWidgetX, int* theWidgetY);
	//Widget*					GetWidgetAt(int x, int y, int* theWidgetX, int* theWidgetY);
	//void					SetFocus(Widget* theWidget);
	//void					GotFocus();	
	//void					LostFocus();	
	//void					InitModalFlags(ModalFlags* theModalFlags);
	//void					DrawWidgetsTo(Graphics* g);
	//void					DoMouseUps(Widget* theWidget, ulong theDownCode);	
	//void					DoMouseUps();
	//void					DeferOverlay(Widget* theWidget, int thePriority);
	//void					FlushDeferredOverlayWidgets(int theMaxPriority);
	//
	//bool					DrawScreen();
	//bool					UpdateFrame();				
	//bool					UpdateFrameF(float theFrac);
	//void					SetPopupCommandWidget(Widget* theList);
	//void					RemovePopupCommandWidget();	
	//void					MousePosition(int x, int y);	
	//void					RehupMouse();
	//void					RemapMouse(int& theX, int& theY);
	//bool					MouseUp(int x, int y, int theClickCount);
	//bool					MouseDown(int x, int y, int theClickCount);
	//bool					MouseMove(int x, int y);
	//bool					MouseDrag(int x, int y);
	//bool					MouseExit(int x, int y);
	//void					MouseWheel(int theDelta);
	//bool					KeyChar(SexyChar theChar);
	//bool					KeyDown(KeyCode key);
	//bool					KeyUp(KeyCode key);

	//bool					IsLeftButtonDown();
	//bool					IsMiddleButtonDown();
	//bool					IsRightButtonDown();
};

}

#endif // __WIDGETMANAGER_H__