#pragma once
#include "Image.h"
#include <stdint.h>
#include "UnknownClass.h"

namespace Sexy
{
	class Image;
	class DDImage;
	class MemoryImage;

	class SharedImage
	{
	public:
		DDImage* mImage;
		int						mRefCount;

		//SharedImage();
	};

	typedef UnknownClass<0xC> SharedImageMap;

	class SharedImageRef
	{
	public:
		Sexy::SharedImage* mSharedImage; // 0x0
		Sexy::MemoryImage* mUnsharedImage; // 0x4
		bool mOwnsUnshared; // 0x8
	public:
		SharedImageRef();
		~SharedImageRef();

		operator Sexy::Image* ()
		{
			uintptr_t func = 0x59A980;
			Sexy::Image* result;
			_asm
			{
				mov ecx, this;
				call func;
				mov result, eax;
			}
			return result;
		}

	};
}