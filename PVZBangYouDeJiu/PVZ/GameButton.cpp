#include "GameButton.h"
#include <stdint.h>

LawnStoneButton* MakeButton(int theId, Sexy::ButtonListener* theListener, const std_string_PVZ& theText)
{
    uintptr_t func = 0x448620;
    LawnStoneButton* result;
    _asm
    {
        push theText;
        push theListener;
        push theId;
        call func;
        add esp, 0xC;
        mov result, eax;
    }
    return result;
}

NewLawnButton* MakeNewButton(int theId, Sexy::ButtonListener* theListener, const std_string_PVZ& theText, Sexy::Font* theFont, Sexy::Image* theImageNormal, Sexy::Image* theImageOver, Sexy::Image* theImageDown)
{
    uintptr_t func = 0x448BC0;
    NewLawnButton* result;
    _asm
    {
        push theImageDown;
        mov ebx, theImageOver;
        mov edi, theImageNormal;
        push theFont;
        push theText;
        push theListener;
        push theId;
        call func;
        add esp, 0x14;
        mov result, eax;
    }
    return result;
}

NewLawnButton::NewLawnButton(Sexy::Image* theComponentImage, int theId, Sexy::ButtonListener* theListener)
{
    uintptr_t func = 0x4486C0;

    _asm
    {
        push theListener;
        mov ecx,theId;
        push this;
        call func;
    }
    mComponentImage = theComponentImage;
}

void NewLawnButton::SetLabel(const SexyString& theLabel)
{
    uintptr_t func = 0x4484E0;

    _asm
    {
        mov edx,theLabel;
        push this;
        call func;
    }
}

void LawnStoneButton::SetLabel(const SexyString& theLabel)
{
    uintptr_t func = 0x448550;

    _asm
    {
        mov edx,theLabel;
        push this;
        call func;
    }
}

GameButton::GameButton(int theId)
{
    uintptr_t func = 0x447C60;

    _asm
    {
        push theId;
        mov esi, this;
        call func;
    }
}

GameButton::~GameButton()
{
    uintptr_t func = 0x447DE0;

    _asm
    {
        push this;
        call func;
    }
}

bool GameButton::HaveButtonImage(Sexy::Image* theImage, const Sexy::Rect& theRect)
{
    return theImage != nullptr || theRect.mWidth != 0;
}

void GameButton::DrawButtonImage(Sexy::Graphics* g, Sexy::Image* theImage, const Sexy::Rect& theRect, int theX, int theY)
{
    uintptr_t func = 0x447E60;

    _asm
    {
        push theY;
        mov edi, theX;
        mov eax, theRect;
        push theImage;
        mov ecx, g;
        mov edx, this;
        call func;
    }
}

void GameButton::SetFont(Sexy::Font* theFont)
{
    if (mFont)
        delete mFont;

    mFont = theFont->Duplicate();
}

bool GameButton::IsButtonDown()
{
    return mIsDown && mIsOver && !mDisabled && !mBtnNoDraw;
}

void GameButton::Draw(Sexy::Graphics* g)
{
    uintptr_t func = 0x447EC0;

    _asm
    {
        push g;
        mov esi, this;
        call func;
    }
}

void GameButton::SetDisabled(bool theDisabled)
{
    mDisabled = theDisabled;
}

bool GameButton::IsMouseOver()
{
    return mIsOver && !mDisabled && !mBtnNoDraw;
}

void GameButton::Update()
{
    uintptr_t func = 0x448330;

    _asm
    {
        mov esi, this;
        call func;
    }
}

void GameButton::Resize(int theX, int theY, int theWidth, int theHeight)
{
    mX = theX;
    mY = theY;
    mWidth = theWidth;
    mHeight = theHeight;
}

//0x448470
void GameButton::SetLabel(const SexyString& theLabel)
{
    uintptr_t func = 0x448470;

    _asm
    {
        mov edx, theLabel;
        push this;
        call func;
    }
}
