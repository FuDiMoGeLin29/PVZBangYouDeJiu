#ifndef __SEXYAPP_H__
#define __SEXYAPP_H__

#include "SexyAppBase.h"
#include "std_string_PVZ.h"

namespace Sexy
{

class InternetManager;
class BetaSupport;

class SexyApp : public SexyAppBase
{
public:
    Sexy::InternetManager* mInternetManager; // 0x640
    Sexy::BetaSupport* mBetaSupport; // 0x644
    std_string_PVZ mBetaSupportSiteOverride; // 0x648
    std_string_PVZ mBetaSupportProdNameOverride; // 0x664
    std_string_PVZ mReferId; // 0x680
    std_string_PVZ mVariation; // 0x69c
    unsigned long mDownloadId; // 0x6b8
    std_string_PVZ mRegSource; // 0x6bc
    unsigned long mLastVerCheckQueryTime; // 0x6d8
    bool mSkipAd; // 0x6dc
    bool mDontUpdate; // 0x6dd
    int mBuildNum; // 0x6e0
    std_string_PVZ mBuildDate; // 0x6e4
    std_string_PVZ mUserName; // 0x700
    std_string_PVZ mRegUserName; // 0x71c
    std_string_PVZ mRegCode; // 0x738
    bool mIsRegistered; // 0x754
    bool mBuildUnlocked; // 0x755
    int mTimesPlayed; // 0x758
    int mTimesExecuted; // 0x75c
    bool mTimedOut; // 0x760

public:
    virtual void UpdateFrames() = 0;
    virtual void WriteToRegistry() = 0;
    virtual void ReadFromRegistry() = 0;
    virtual bool CheckSignature(const Sexy::Buffer*, const std_string_PVZ*) = 0;
    virtual bool ShouldCheckForUpdate() = 0;
    virtual void UpdateCheckQueried() = 0;
    virtual void URLOpenSucceeded(const std_string_PVZ*) = 0;
    virtual ~SexyApp() = 0;                                 // 原 dtr_SexyAppBase
    virtual bool OpenRegisterPage(StringStringMap) = 0;  // 原 OpenRegisterPage_2，注意值传递
    virtual bool OpenRegisterPage() = 0;
    virtual void PreDisplayHook() = 0;
    virtual void InitPropertiesHook() = 0;
    virtual void Init() = 0;
    virtual void PreTerminate() = 0;
    virtual bool OpenHTMLTemplate(const std_string_PVZ*, const StringStringMap*) = 0;
    virtual void OpenUpdateURL() = 0;
    virtual void HandleCmdLineParam(const std_string_PVZ*, const std_string_PVZ*) = 0;
    virtual void HandleNotifyGameMessageCommandLine(const std_wstring_PVZ*) = 0;
    virtual std_string_PVZ* GetGameSEHInfo(std_string_PVZ* result) = 0;
    virtual void GetSEHWebParams(StringStringMap*) = 0;
    virtual bool OverrideWindowProc(HWND__*, unsigned int, unsigned int, int, int*) = 0;

    // --- Virtual Function Table --- 
    //=======================================
    // [0] void UpdateFrames()
    // [1] void WriteToRegistry()
    // [2] void ReadFromRegistry()
    // [3] bool CheckSignature()
    // [4] bool ShouldCheckForUpdate()
    // [5] void UpdateCheckQueried()
    // [6] void URLOpenSucceeded()
    // [7] void ~SexyApp()
    // [8] bool OpenRegisterPage()
    // [9] bool OpenRegisterPage()
    // [10] void PreDisplayHook()
    // [11] void InitPropertiesHook()
    // [12] void Init()
    // [13] void PreTerminate()
    // [14] bool OpenHTMLTemplate()
    // [15] void OpenUpdateURL()
    // [16] void HandleCmdLineParam()
    // [17] void HandleNotifyGameMessageCommandLine()
    // [18] std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetGameSEHInfo()
    // [19] void GetSEHWebParams()
    // [20] bool OverrideWindowProc()
    // [21] void* __vecDelDtor()
    //=======================================
};

//extern SexyApp* gSexyApp;

};

#endif //__SEXYAPP_H__