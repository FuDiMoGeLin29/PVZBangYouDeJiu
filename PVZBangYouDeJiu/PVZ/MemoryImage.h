#pragma once
#include "Image.h"

namespace Sexy
{
	class MemoryImage : public Image
	{
	public:

	public:
		void SetBits(unsigned long* theBits, int theWidth, int theHeight, bool commitBits);
	};
}