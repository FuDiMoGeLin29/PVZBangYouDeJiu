#pragma once
//
//#ifdef _DEBUG
//
//#define TOD_ASSERT(condition, ...) {										\
//		if (!bool(condition))													\
//		{																		\
//			TodAssertFailed(""#condition, __FILE__, __LINE__, ##__VA_ARGS__);	\
//			if (IsDebuggerPresent())											\
//			{																	\
//				__debugbreak();													\
//			}																	\
//			TodTraceMemory();													\
//		}																		\
//	}
//
//#else
//
//#define TOD_ASSERT(condition, ...)
//
//#endif

#define TOD_ASSERT(condition, ...)