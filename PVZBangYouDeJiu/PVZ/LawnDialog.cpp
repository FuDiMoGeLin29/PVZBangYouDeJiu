#include "LawnDialog.h"
#include "LawnApp.h"
#include "EffectSystem.h"

ReanimationWidget::ReanimationWidget()
{
	uintptr_t func = 0x4579A0;

	_asm
	{
		mov esi, this;
		call func;
	}
}

void ReanimationWidget::Dispose()
{
	if (mReanim)
	{
		mApp->mEffectSystem->mReanimationHolder->mReanimations.DataArrayFree(mReanim);
		mReanim = nullptr;
	}
}

void ReanimationWidget::AddReanimation(float x, float y, ReanimationType theReanimationType)
{
	TOD_ASSERT(mReanim == nullptr);

	mPosX = x;
	mPosY = y;
	mReanim = mApp->mEffectSystem->mReanimationHolder->AllocReanimation(x, y, 0, theReanimationType);
	mReanim->mLoopType = ReanimLoopType::REANIM_LOOP;
	mReanim->mIsAttachment = true;
	if (mReanim->TrackExists("anim_idle"))
		mReanim->SetFramesForLayer("anim_idle");

	Resize(x, y, 10, 10);
}

LawnDialog::LawnDialog(LawnApp* theApp, int theId, bool isModal, const SexyString& theDialogHeader, const SexyString& theDialogLines, const SexyString& theDialogFooter, int theButtonMode)
{
	uintptr_t func = 0x456A80;

	_asm
	{
		push theButtonMode;
		push theDialogFooter;
		push theDialogLines;
		mov ecx, theDialogHeader;
		push isModal;
		push theId;
		push theApp;
		push this;
		call func;
	}
}