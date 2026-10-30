#ifndef __WIDGETCONTAINER_H__
#define __WIDGETCONTAINER_H__
#include <stdint.h>
#include "Flags.h"
#include "UnknownClass.h"
#include "Rect.h"

#pragma code_seg(".WidgetContainerVFunc")

namespace Sexy
{
	class Widget;
    class WidgetManager;
	class Graphics;
    typedef UnknownClass<0xC> WidgetList;
    typedef UnknownClass<0x8> WidgetIteratorList;

	class WidgetContainer
	{
	public:
        WidgetList mWidgets; // 0x4
        WidgetManager* mWidgetManager; // 0x10
        WidgetContainer* mParent; // 0x14
        bool mUpdateIteratorModified; // 0x18
        WidgetIteratorList mUpdateIterator; // 0x1c
        unsigned long mLastWMUpdateCount; // 0x24
        int mUpdateCnt; // 0x28
        bool mDirty; // 0x2c
        int mX; // 0x30
        int mY; // 0x34
        int mWidth; // 0x38
        int mHeight; // 0x3c
        bool mHasAlpha; // 0x40
        bool mClip; // 0x41
        FlagsMod mWidgetFlagsMod; // 0x44
        int mPriority; // 0x4c
        int mZOrder; // 0x50
    public:
        WidgetContainer();
        virtual ~WidgetContainer();

        // 返回 TRect 的指针，通过 result 输出
        virtual Rect GetRect();
        virtual bool Intersects(WidgetContainer* theWidget);
        virtual void AddWidget(Widget* theWidget);
        virtual void RemoveWidget(Widget* theWidget);
        virtual bool HasWidget(Widget* theWidget);
        virtual void DisableWidget(Widget* theWidget);
        virtual void RemoveAllWidgets(bool doDelete = false, bool recursive = false);
        virtual void SetFocus(Widget* theWidget);
        virtual bool IsBelow(Widget* theWidget1, Widget* theWidget2);
        virtual void MarkAllDirty();
        virtual void BringToFront(Widget* theWidget);
        virtual void BringToBack(Widget* theWidget);
        virtual void PutBehind(Widget* theWidget, Widget* theRefWidget);
        virtual void PutInfront(Widget* theWidget, Widget* theRefWidget);

        // 返回 TPoint 的指针，通过 result 输出
        virtual Rect GetAbsPos();

        // 重载函数：MarkDirty 和 MarkDirtyFull
        virtual void MarkDirty();  //MarkDirty_2
        virtual void MarkDirty(WidgetContainer* theWidget);
        virtual void MarkDirtyFull();  //MarkDirtyFull_2
        virtual void MarkDirtyFull(WidgetContainer* theWidget);

        virtual void AddedToManager(WidgetManager* theWidgetManager);
        virtual void RemovedFromManager(WidgetManager* theWidgetManager);
        virtual void Update();
        virtual void UpdateAll(ModalFlags* theFlags);
        virtual void UpdateF(float theFrac);
        virtual void UpdateFAll(ModalFlags* theFlags, float theFrac);
        virtual void Draw(Graphics* g);
        virtual void DrawAll(ModalFlags* theFlags, Graphics* g);
        virtual void SysColorChangedAll();
        virtual void SysColorChanged();
	};
}

#endif