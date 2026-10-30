#pragma once

#include "Common.h"
#include "Rect.h"
#include "Color.h"
#include "ButtonListener.h"
#include "DialogListener.h"
#include "Buffer.h"
#include "CritSect.h"
#include "SharedImage.h"
#include "Ratio.h"
#include "std_string_PVZ.h"
#include <set>
#include <vector>
#include <map>
#include "UnknownClass.h"
#include "std_wstring_PVZ.h"

namespace ImageLib
{
	class Image;
};

namespace Sexy
{
	class WidgetManager;
	class DDInterface;
	class Image;
	class DDImage;
	class Widget;
	class SoundManager;
	class MusicInterface;
	class MemoryImage;
	class HTTPTransfer;
	class Dialog;

	class ResourceManager;

	class WidgetSafeDeleteInfo
	{
	public:
		int						mUpdateAppDepth;
		Widget* mWidget;
	};

	typedef UnknownClass<0xC> WidgetSafeDeleteList;
	typedef UnknownClass<0xC> MemoryImageSet;
	typedef UnknownClass<0xC> DialogMap;
	typedef UnknownClass<0xC> DialogList;
	typedef UnknownClass<0xC> WindowsMessageList;
	typedef UnknownClass<0x10> StringVector;

	typedef UnknownClass<0xC> StringSexyStringMap;
	typedef UnknownClass<0xC> StringStringMap;
	typedef UnknownClass<0xC> StringWStringMap;
	typedef UnknownClass<0xC> StringBoolMap;
	typedef UnknownClass<0xC> StringIntMap;
	typedef UnknownClass<0xC> StringDoubleMap;
	typedef UnknownClass<0xC> StringStringVectorMap;
	typedef UnknownClass<0xC> DemoMarkerList;

	/*typedef std::list<WidgetSafeDeleteInfo> WidgetSafeDeleteList;
	typedef std::set<MemoryImage*> MemoryImageSet;
	typedef std::map<int, Dialog*> DialogMap;
	typedef std::list<Dialog*> DialogList;
	typedef std::list<MSG> WindowsMessageList;
	typedef std::vector<std_string_PVZ> StringVector;

	typedef std::map<std_string_PVZ, SexyString> StringSexyStringMap;
	typedef std::map<std_string_PVZ, std_string_PVZ> StringStringMap;
	typedef std::map<std_string_PVZ, std_wstring_PVZ> StringWStringMap;
	typedef std::map<std_string_PVZ, bool> StringBoolMap;
	typedef std::map<std_string_PVZ, int> StringIntMap;
	typedef std::map<std_string_PVZ, double> StringDoubleMap;
	typedef std::map<std_string_PVZ, StringVector> StringStringVectorMap;
	typedef std::list<DemoMarker> DemoMarkerList;*/

	enum
	{
		CURSOR_POINTER,
		CURSOR_HAND,
		CURSOR_DRAGGING,
		CURSOR_TEXT,
		CURSOR_CIRCLE_SLASH,
		CURSOR_SIZEALL,
		CURSOR_SIZENESW,
		CURSOR_SIZENS,
		CURSOR_SIZENWSE,
		CURSOR_SIZEWE,
		CURSOR_WAIT,
		CURSOR_NONE,
		CURSOR_CUSTOM,
		NUM_CURSORS
	};

	enum
	{
		DEMO_MOUSE_POSITION,
		DEMO_ACTIVATE_APP,
		DEMO_SIZE,
		DEMO_KEY_DOWN,
		DEMO_KEY_UP,
		DEMO_KEY_CHAR,
		DEMO_CLOSE,
		DEMO_MOUSE_ENTER,
		DEMO_MOUSE_EXIT,
		DEMO_LOADING_COMPLETE,
		DEMO_REGISTRY_GETSUBKEYS,
		DEMO_REGISTRY_READ,
		DEMO_REGISTRY_WRITE,
		DEMO_REGISTRY_ERASE,
		DEMO_FILE_EXISTS,
		DEMO_FILE_READ,
		DEMO_FILE_WRITE,
		DEMO_HTTP_RESULT,
		DEMO_SYNC,
		DEMO_ASSERT_STRING_EQUAL,
		DEMO_ASSERT_INT_EQUAL,
		DEMO_MOUSE_WHEEL,
		DEMO_HANDLE_COMPLETE,
		DEMO_VIDEO_DATA,
		DEMO_IDLE = 31
	};

	enum {
		FPS_ShowFPS,
		FPS_ShowCoords,
		Num_FPS_Types
	};

	enum
	{
		UPDATESTATE_MESSAGES,
		UPDATESTATE_PROCESS_1,
		UPDATESTATE_PROCESS_2,
		UPDATESTATE_PROCESS_DONE
	};

	typedef UnknownClass<0xC> HandleToIntMap;

	class SexyAppBase : public ButtonListener, public DialogListener
	{
	public:
		unsigned long mRandSeed; // 0x8
		std_string_PVZ mCompanyName; // 0xc
		std_string_PVZ mFullCompanyName; // 0x28
		std_string_PVZ mProdName; // 0x44
		std_string_PVZ mTitle; // 0x60
		std_string_PVZ mRegKey; // 0x7c
		std_string_PVZ mChangeDirTo; // 0x98
		int mRelaxUpdateBacklogCount; // 0xb4
		int mPreferredX; // 0xb8
		int mPreferredY; // 0xbc
		int mWidth; // 0xc0
		int mHeight; // 0xc4
		int mFullscreenBits; // 0xc8
		double mMusicVolume; // 0xd0
		double mSfxVolume; // 0xd8
		double mDemoMusicVolume; // 0xe0
		double mDemoSfxVolume; // 0xe8
		bool mNoSoundNeeded; // 0xf0
		bool mWantFMod; // 0xf1
		bool mCmdLineParsed; // 0xf2
		bool mSkipSignatureChecks; // 0xf3
		bool mStandardWordWrap; // 0xf4
		bool mbAllowExtendedChars; // 0xf5
		void* mMutex; // 0xf8
		bool mOnlyAllowOneCopyToRun; // 0xfc
		unsigned int mNotifyGameMessage; // 0x100
		Sexy::CritSect mCritSect; // 0x104
		bool mBetaValidate; // 0x11c
		unsigned char mAdd8BitMaxTable[512]; // 0x11d
		Sexy::WidgetManager* mWidgetManager; // 0x320
		DialogMap mDialogMap; // 0x324
		DialogList mDialogList; // 0x330
		unsigned long mPrimaryThreadId; // 0x33c
		bool mSEHOccured; // 0x340
		bool mShutdown; // 0x341
		bool mExitToTop; // 0x342
		bool mIsWindowed; // 0x343
		bool mIsPhysWindowed; // 0x344
		bool mFullScreenWindow; // 0x345
		bool mForceFullscreen; // 0x346
		bool mForceWindowed; // 0x347
		bool mInitialized; // 0x348
		bool mProcessInTimer; // 0x349
		unsigned long mTimeLoaded; // 0x34c
		HWND__* mHWnd; // 0x350
		HWND__* mInvisHWnd; // 0x354
		bool mIsScreenSaver; // 0x358
		bool mAllowMonitorPowersave; // 0x359
		WindowsMessageList mDeferredMessages; // 0x35c
		bool mNoDefer; // 0x368
		bool mFullScreenPageFlip; // 0x369
		bool mTabletPC; // 0x36a
		Sexy::DDInterface* mDDInterface; // 0x36c
		bool mAlphaDisabled; // 0x370
		Sexy::MusicInterface* mMusicInterface; // 0x374
		bool mReadFromRegistry; // 0x378
		std_string_PVZ mRegisterLink; // 0x37c
		std_string_PVZ mProductVersion; // 0x398
		Sexy::Image* mCursorImages[13]; // 0x3b4
		HICON__* mOverrideCursor; // 0x3e8
		bool mIsOpeningURL; // 0x3ec
		bool mShutdownOnURLOpen; // 0x3ed
		std_string_PVZ mOpeningURL; // 0x3f0
		unsigned long mOpeningURLTime; // 0x40c
		unsigned long mLastTimerTime; // 0x410
		unsigned long mLastBigDelayTime; // 0x414
		double mUnmutedMusicVolume; // 0x418
		double mUnmutedSfxVolume; // 0x420
		int mMuteCount; // 0x428
		int mAutoMuteCount; // 0x42c
		bool mDemoMute; // 0x430
		bool mMuteOnLostFocus; // 0x431
		MemoryImageSet mMemoryImageSet; // 0x434
		SharedImageMap mSharedImageMap; // 0x440
		bool mCleanupSharedImages; // 0x44c
		int mNonDrawCount; // 0x450
		int mFrameTime; // 0x454
		bool mIsDrawing; // 0x458
		bool mLastDrawWasEmpty; // 0x459
		bool mHasPendingDraw; // 0x45a
		double mPendingUpdatesAcc; // 0x460
		double mUpdateFTimeAcc; // 0x468
		unsigned long mLastTimeCheck; // 0x470
		unsigned long mLastTime; // 0x474
		unsigned long mLastUserInputTick; // 0x478
		int mSleepCount; // 0x47c
		int mDrawCount; // 0x480
		int mUpdateCount; // 0x484
		int mUpdateAppState; // 0x488
		int mUpdateAppDepth; // 0x48c
		double mUpdateMultiplier; // 0x490
		bool mPaused; // 0x498
		int mFastForwardToUpdateNum; // 0x49c
		bool mFastForwardToMarker; // 0x4a0
		bool mFastForwardStep; // 0x4a1
		unsigned long mLastDrawTick; // 0x4a4
		unsigned long mNextDrawTick; // 0x4a8
		int mStepMode; // 0x4ac
		int mCursorNum; // 0x4b0
		Sexy::SoundManager* mSoundManager; // 0x4b4
		HICON__* mHandCursor; // 0x4b8
		HICON__* mDraggingCursor; // 0x4bc
		WidgetSafeDeleteList mSafeDeleteList; // 0x4c0
		bool mMouseIn; // 0x4cc
		bool mRunning; // 0x4cd
		bool mActive; // 0x4ce
		bool mMinimized; // 0x4cf
		bool mPhysMinimized; // 0x4d0
		bool mIsDisabled; // 0x4d1
		bool mHasFocus; // 0x4d2
		int mDrawTime; // 0x4d4
		unsigned long mFPSStartTick; // 0x4d8
		int mFPSFlipCount; // 0x4dc
		int mFPSDirtyCount; // 0x4e0
		int mFPSTime; // 0x4e4
		int mFPSCount; // 0x4e8
		bool mShowFPS; // 0x4ec
		int mShowFPSMode; // 0x4f0
		int mScreenBltTime; // 0x4f4
		bool mAutoStartLoadingThread; // 0x4f8
		bool mLoadingThreadStarted; // 0x4f9
		bool mLoadingThreadCompleted; // 0x4fa
		bool mLoaded; // 0x4fb
		bool mYieldMainThread; // 0x4fc
		bool mLoadingFailed; // 0x4fd
		bool mCursorThreadRunning; // 0x4fe
		bool mSysCursor; // 0x4ff
		bool mCustomCursorsEnabled; // 0x500
		bool mCustomCursorDirty; // 0x501
		bool mLastShutdownWasGraceful; // 0x502
		bool mIsWideWindow; // 0x503
		bool mWriteToSexyCache; // 0x504
		bool mSexyCacheBuffers; // 0x505
		int mNumLoadingThreadTasks; // 0x508
		int mCompletedLoadingThreadTasks; // 0x50c
		bool mRecordingDemoBuffer; // 0x510
		bool mPlayingDemoBuffer; // 0x511
		bool mManualShutdown; // 0x512
		std_string_PVZ mDemoPrefix; // 0x514
		std_string_PVZ mDemoFileName; // 0x530
		Sexy::Buffer mDemoBuffer; // 0x54c
		int mDemoLength; // 0x56c
		int mLastDemoMouseX; // 0x570
		int mLastDemoMouseY; // 0x574
		int mLastDemoUpdateCnt; // 0x578
		bool mDemoNeedsCommand; // 0x57c
		bool mDemoIsShortCmd; // 0x57d
		int mDemoCmdNum; // 0x580
		int mDemoCmdOrder; // 0x584
		int mDemoCmdBitPos; // 0x588
		bool mDemoLoadingComplete; // 0x58c
		HandleToIntMap mHandleToIntMap; // 0x590
		int mCurHandleNum; // 0x59c
		DemoMarkerList mDemoMarkerList; // 0x5a0
		bool mDebugKeysEnabled; // 0x5ac
		bool mEnableMaximizeButton; // 0x5ad
		bool mCtrlDown; // 0x5ae
		bool mAltDown; // 0x5af
		bool mAllowAltEnter; // 0x5b0
		int mSyncRefreshRate; // 0x5b4
		bool mVSyncUpdates; // 0x5b8
		bool mVSyncBroken; // 0x5b9
		int mVSyncBrokenCount; // 0x5bc
		unsigned long mVSyncBrokenTestStartTick; // 0x5c0
		unsigned long mVSyncBrokenTestUpdates; // 0x5c4
		bool mWaitForVSync; // 0x5c8
		bool mSoftVSyncWait; // 0x5c9
		bool mUserChanged3DSetting; // 0x5ca
		bool mAutoEnable3D; // 0x5cb
		bool mTest3D; // 0x5cc
		unsigned long mMinVidMemory3D; // 0x5d0
		unsigned long mRecommendedVidMemory3D; // 0x5d4
		bool mWidescreenAware; // 0x5d8
		bool mWidescreenTranslate; // 0x5d9
		Sexy::TRect<int> mScreenBounds; // 0x5dc
		bool mEnableWindowAspect; // 0x5ec
		Sexy::Ratio mWindowAspect; // 0x5f0
		StringWStringMap mStringProperties; // 0x5f8
		StringBoolMap mBoolProperties; // 0x604
		StringIntMap mIntProperties; // 0x610
		StringDoubleMap mDoubleProperties; // 0x61c
		StringStringVectorMap mStringVectorProperties; // 0x628
		Sexy::ResourceManager* mResourceManager; // 0x634
		long mOldWndProc; // 0x638

		public:
			bool							RegistryWriteInteger(const std_string_PVZ& theValueName, int theValue); //SexyAppBase
			bool							RegistryWriteBoolean(const std_string_PVZ& theValueName, bool theValue); //SexyAppBase
			bool							RegistryReadInteger(const std_string_PVZ& theValueName, int* theValue); //SexyAppBase
			bool							RegistryReadBoolean(const std_string_PVZ& theValueName, bool* theValue); //SexyAppBase
			void							ClearUpdateBacklog();

			void					RehupFocus();
			void					ClearKeysDown();
			bool					ProcessDeferredMessages(bool singleMessage);
			void					UpdateFTimeAcc();
			static void				LoadingThreadProcStub(void* theArg);

			// Cursor thread methods
			void					CursorThreadProc();
			static void				CursorThreadProcStub(void* theArg);
			void					StartCursorThread();

			void					WaitForLoadingThread();
			void					ProcessSafeDeleteList();
			void					RestoreScreenResolution();
			void					DoExit(int theCode);

			void					TakeScreenshot();
			void					DumpProgramInfo();
			void					ShowMemoryUsage();

			// Registry helpers
			bool					RegistryRead(const std_string_PVZ& theValueName, ulong* theType, uchar* theValue, ulong* theLength);
			bool					RegistryReadKey(const std_string_PVZ& theValueName, ulong* theType, uchar* theValue, ulong* theLength, HKEY theMainKey = HKEY_CURRENT_USER);
			bool					RegistryWrite(const std_string_PVZ& theValueName, ulong theType, const uchar* theValue, ulong theLength);

			// Demo recording helpers	
			void					ProcessDemo();

		public:
			virtual void			ButtonPress(int theId) = 0;
			virtual void			ButtonPress(int theId, int theClickCount) = 0;
			virtual void			ButtonDepress(int theId) = 0;
			virtual void			ButtonDownTick(int theId) = 0;
			virtual void			ButtonMouseEnter(int theId) = 0;
			virtual void			ButtonMouseLeave(int theId) = 0;
			virtual void			ButtonMouseMove(int theId, int theX, int theY) = 0;
			virtual bool Process(bool) = 0;
			virtual void UpdateFrames() = 0;
			virtual bool DoUpdateFrames() = 0;
			virtual void DoUpdateFramesF(float) = 0;
			virtual void MakeWindow() = 0;
			virtual void EnforceCursor() = 0;
			virtual void ReInitImages() = 0;
			virtual void DeleteNativeImageData() = 0;
			virtual void DeleteExtraImageData() = 0;
			virtual void LoadingThreadCompleted() = 0;
			virtual ~SexyAppBase() = 0;                             // ԭ dtr_SexyAppBase
			virtual Sexy::MusicInterface* CreateMusicInterface(HWND__*) = 0;
			virtual void InitHook() = 0;
			virtual void ShutdownHook() = 0;
			virtual void PreTerminate() = 0;
			virtual void LoadingThreadProc() = 0;
			virtual void WriteToRegistry() = 0;
			virtual void ReadFromRegistry() = 0;
			virtual Sexy::Dialog* NewDialog(int, bool, const std_string_PVZ*, const std_string_PVZ*, const std_string_PVZ*, int) = 0;
			virtual void PreDisplayHook() = 0;
			virtual void BeginPopup() = 0;
			virtual void EndPopup() = 0;
			virtual int MsgBox(const std_string_PVZ*, const std_string_PVZ*, int) = 0;   // ԭ MsgBox_2
			virtual int MsgBox(const std_wstring_PVZ*, const std_wstring_PVZ*, int) = 0;
			virtual void Popup(const std_string_PVZ*) = 0;                            // ԭ Popup_2
			virtual void Popup(const std_wstring_PVZ*) = 0;
			virtual void LogScreenSaverError(const std_string_PVZ*) = 0;
			virtual void SafeDeleteWidget(Sexy::Widget*) = 0;
			virtual void URLOpenFailed(const std_string_PVZ*) = 0;
			virtual void URLOpenSucceeded(const std_string_PVZ*) = 0;
			virtual bool OpenURL(const std_string_PVZ*, bool) = 0;
			virtual std_string_PVZ* GetProductVersion(std_string_PVZ* result, const std_string_PVZ*) = 0;
			virtual void SEHOccured() = 0;
			virtual std_string_PVZ* GetGameSEHInfo(std_string_PVZ* result) = 0;
			virtual void GetSEHWebParams(StringStringMap*) = 0;
			virtual void Shutdown() = 0;
			virtual void DoParseCmdLine() = 0;
			virtual void ParseCmdLine(const std_string_PVZ*) = 0;
			virtual void HandleCmdLineParam(const std_string_PVZ*, const std_string_PVZ*) = 0;
			virtual void HandleNotifyGameMessage(int, int) = 0;
			virtual void HandleGameAlreadyRunning() = 0;
			virtual void Start() = 0;
			virtual void Init() = 0;
			virtual void PreDDInterfaceInitHook() = 0;
			virtual void PostDDInterfaceInitHook() = 0;
			virtual bool ChangeDirHook(const char*) = 0;
			virtual void PlaySample(int theSoundNum) = 0;                       // ԭ PlaySample_2
			virtual void PlaySample(int theSoundNum, int thePan) = 0;
			virtual long double GetMasterVolume() = 0;
			virtual long double GetMusicVolume() = 0;
			virtual long double GetSfxVolume() = 0;
			virtual bool IsMuted() = 0;
			virtual void SetMasterVolume(long double) = 0;
			virtual void SetMusicVolume(long double) = 0;
			virtual void SetSfxVolume(long double) = 0;
			virtual void Mute(bool) = 0;
			virtual void Unmute(bool) = 0;
			virtual long double GetLoadingThreadProgress() = 0;
			virtual Sexy::DDImage* GetImage(const std_string_PVZ&, bool) = 0;
			virtual Sexy::SharedImageRef* SetSharedImage(Sexy::SharedImageRef* result, const std_string_PVZ*, const std_string_PVZ*, Sexy::DDImage*, bool*) = 0;
			virtual Sexy::SharedImageRef* GetSharedImage(Sexy::SharedImageRef* result, const std_string_PVZ*, const std_string_PVZ*, bool*) = 0;
			virtual void SwitchScreenMode() = 0;                    // ԭ SwitchScreenMode_3
			virtual void SwitchScreenMode(bool) = 0;                // ԭ SwitchScreenMode_2
			virtual void SwitchScreenMode(bool, bool, bool) = 0;
			virtual void SetAlphaDisabled(bool) = 0;
			virtual Sexy::Dialog* DoDialog(int, bool, const std_string_PVZ*, const std_string_PVZ*, const std_string_PVZ*, int) = 0;
			virtual Sexy::Dialog* GetDialog(int) = 0;
			virtual void AddDialog(int, Sexy::Dialog*) = 0;         // ԭ AddDialog_2
			virtual void AddDialog(Sexy::Dialog*) = 0;
			virtual bool KillDialog(int, bool, bool) = 0;           // ԭ KillDialog_3
			virtual bool KillDialog(int) = 0;                       // ԭ KillDialog_2
			virtual bool KillDialog(Sexy::Dialog*) = 0;
			virtual int GetDialogCount() = 0;
			virtual void ModalOpen() = 0;
			virtual void ModalClose() = 0;
			virtual void GotFocus() = 0;
			virtual void LostFocus() = 0;
			virtual bool IsAltKeyUsed(unsigned int) = 0;
			virtual bool DebugKeyDown(int) = 0;
			virtual bool DebugKeyDownAsync(int, bool, bool) = 0;
			virtual void CloseRequestAsync() = 0;
			virtual void Done3dTesting() = 0;
			virtual std_string_PVZ* NotifyCrashHook(std_string_PVZ* result) = 0;
			virtual bool CheckSignature(const Sexy::Buffer*, const std_string_PVZ*) = 0;
			virtual bool DrawDirtyStuff() = 0;
			virtual void Redraw(Sexy::TRect<int>*) = 0;
			virtual void InitPropertiesHook() = 0;
			virtual void DoMainLoop() = 0;
			virtual bool UpdateAppStep(bool*) = 0;
			virtual bool UpdateApp() = 0;
			virtual bool AppCanRestore() = 0;
			virtual bool OverrideWindowProc(HWND__*, unsigned int, unsigned int, int, int*) = 0;

		// --- Virtual Function Table --- 
		//=======================================
		// [0] bool Process()
		// [1] void UpdateFrames()
		// [2] bool DoUpdateFrames()
		// [3] void DoUpdateFramesF()
		// [4] void MakeWindow()
		// [5] void EnforceCursor()
		// [6] void ReInitImages()
		// [7] void DeleteNativeImageData()
		// [8] void DeleteExtraImageData()
		// [9] void LoadingThreadCompleted()
		// [10] void ~SexyAppBase()
		// [11] Sexy::MusicInterface* CreateMusicInterface()
		// [12] void InitHook()
		// [13] void ShutdownHook()
		// [14] void PreTerminate()
		// [15] void LoadingThreadProc()
		// [16] void WriteToRegistry()
		// [17] void ReadFromRegistry()
		// [18] Sexy::Dialog* NewDialog()
		// [19] void PreDisplayHook()
		// [20] void BeginPopup()
		// [21] void EndPopup()
		// [22] int MsgBox()
		// [23] int MsgBox()
		// [24] void Popup()
		// [25] void Popup()
		// [26] void LogScreenSaverError()
		// [27] void SafeDeleteWidget()
		// [28] void URLOpenFailed()
		// [29] void URLOpenSucceeded()
		// [30] bool OpenURL()
		// [31] std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetProductVersion()
		// [32] void SEHOccured()
		// [33] std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetGameSEHInfo()
		// [34] void GetSEHWebParams()
		// [35] void Shutdown()
		// [36] void DoParseCmdLine()
		// [37] void ParseCmdLine()
		// [38] void HandleCmdLineParam()
		// [39] void HandleNotifyGameMessage()
		// [40] void HandleGameAlreadyRunning()
		// [41] void Start()
		// [42] void Init()
		// [43] void PreDDInterfaceInitHook()
		// [44] void PostDDInterfaceInitHook()
		// [45] bool ChangeDirHook()
		// [46] void PlaySample()
		// [47] void PlaySample()
		// [48] double GetMasterVolume()
		// [49] double GetMusicVolume()
		// [50] double GetSfxVolume()
		// [51] bool IsMuted()
		// [52] void SetMasterVolume()
		// [53] void SetMusicVolume()
		// [54] void SetSfxVolume()
		// [55] void Mute()
		// [56] void Unmute()
		// [57] double GetLoadingThreadProgress()
		// [58] Sexy::DDImage* GetImage()
		// [59] Sexy::SharedImageRef SetSharedImage()
		// [60] Sexy::SharedImageRef GetSharedImage()
		// [61] void SwitchScreenMode()
		// [62] void SwitchScreenMode()
		// [63] void SwitchScreenMode()
		// [64] void SetAlphaDisabled()
		// [65] Sexy::Dialog* DoDialog()
		// [66] Sexy::Dialog* GetDialog()
		// [67] void AddDialog()
		// [68] void AddDialog()
		// [69] bool KillDialog()
		// [70] bool KillDialog()
		// [71] bool KillDialog()
		// [72] int GetDialogCount()
		// [73] void ModalOpen()
		// [74] void ModalClose()
		// [75] void DialogButtonPress()
		// [76] void DialogButtonDepress()
		// [77] void GotFocus()
		// [78] void LostFocus()
		// [79] bool IsAltKeyUsed()
		// [80] bool DebugKeyDown()
		// [81] bool DebugKeyDownAsync()
		// [82] void CloseRequestAsync()
		// [83] void Done3dTesting()
		// [84] std::basic_string<char,std::char_traits<char>,std::allocator<char> > NotifyCrashHook()
		// [85] bool CheckSignature()
		// [86] bool DrawDirtyStuff()
		// [87] void Redraw()
		// [88] void InitPropertiesHook()
		// [89] void DoMainLoop()
		// [90] bool UpdateAppStep()
		// [91] bool UpdateApp()
		// [92] bool AppCanRestore()
		// [93] bool OverrideWindowProc()
		// [94] void* __vecDelDtor()
		//=======================================
	};

	//extern SexyAppBase* gSexyAppBase;

};
