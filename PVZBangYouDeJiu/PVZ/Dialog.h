#ifndef __DIALOG_H__
#define __DIALOG_H__

#include "Widget.h"
#include "ButtonListener.h"
#include "Common.h"

namespace Sexy
{

class DialogListener;
class ButtonWidget;
class DialogButton;
class Font;

extern SexyString DIALOG_YES_STRING;
extern SexyString DIALOG_NO_STRING;
extern SexyString DIALOG_OK_STRING;
extern SexyString DIALOG_CANCEL_STRING;

class Dialog : public Widget, public ButtonListener
{
public:
	enum
	{
		BUTTONS_NONE,
		BUTTONS_YES_NO,
		BUTTONS_OK_CANCEL,
		BUTTONS_FOOTER
	};

	enum
	{
		ID_YES		= 1000,
		ID_NO		= 1001,
		ID_OK		= 1000,
		ID_CANCEL	= 1001,
		ID_FOOTER	= 1000
	};
	
	enum
	{
		COLOR_HEADER = 0,
		COLOR_LINES,
		COLOR_FOOTER,
		COLOR_BUTTON_TEXT,
		COLOR_BUTTON_TEXT_HILITE,
		COLOR_BKG,
		COLOR_OUTLINE,		
		NUM_COLORS
	};

public:
	Sexy::DialogListener* mDialogListener; // 0x8c
	Sexy::Image* mComponentImage; // 0x90
	Sexy::DialogButton* mYesButton; // 0x94
	Sexy::DialogButton* mNoButton; // 0x98
	int mNumButtons; // 0x9c
	SexyString mDialogHeader; // 0xa0
	SexyString mDialogFooter; // 0xbc
	SexyString mDialogLines; // 0xd8
	int mButtonMode; // 0xf4
	Sexy::Font* mHeaderFont; // 0xf8
	Sexy::Font* mLinesFont; // 0xfc
	int mTextAlign; // 0x100
	int mLineSpacingOffset; // 0x104
	int mButtonHeight; // 0x108
	Sexy::Insets mBackgroundInsets; // 0x10c
	Sexy::Insets mContentInsets; // 0x11c
	int mSpaceAfterHeader; // 0x12c
	bool mDragging; // 0x130
	int mDragMouseX; // 0x134
	int mDragMouseY; // 0x138
	int mId; // 0x13c
	bool mIsModal; // 0x140
	int mResult; // 0x144
	int mButtonHorzSpacing; // 0x148
	int mButtonSidePadding; // 0x14c
	

public:
	void					EnsureFonts();

public:
	Dialog() {};
	Dialog(int theId, bool isModal, const SexyString& theDialogHeader, const SexyString& theDialogLines, const SexyString& theDialogFooter, int theButtonMode); //UNICODE

	virtual ~Dialog();

	virtual void			SetColor(int theIdx, const Color& theColor);
	virtual void			Draw(Graphics* g);
	virtual void			AddedToManager(WidgetManager* theWidgetManager);
	virtual void			RemovedFromManager(WidgetManager* theWidgetManager);
	virtual void			OrderInManagerChanged();
	virtual void			Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void			MouseDown(int x, int y, int theClickCount);
	virtual void			MouseDown(int x, int y, int theBtnNum, int theClickCount);
	virtual void			MouseDrag(int x, int y);
	virtual void			MouseUp(int x, int y);
	virtual void			MouseUp(int x, int y, int theClickCount);
	virtual void			MouseUp(int x, int y, int theBtnNum, int theClickCount);
	virtual void			Update();

	// ÐÂÔöÐéº¯Êý
	virtual void SetButtonFont(Sexy::Font* theFont);
	virtual void SetHeaderFont(Sexy::Font* theFont);
	virtual void SetLinesFont(Sexy::Font* theFont);
	virtual int GetPreferredHeight(int theWidth);
	virtual bool IsModal();
	virtual int WaitForResult(bool autoKill = true);

	virtual void			ButtonPress(int theId);
	virtual void			ButtonDepress(int theId);
	//virtual void			ButtonDownTick(int theId);
};

}

#endif //__DIALOG_H__