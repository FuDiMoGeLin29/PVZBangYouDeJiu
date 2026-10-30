#pragma once
#include "std_string_PVZ.h"
#include "SharedImage.h"
class Sexy::SharedImageRef;

namespace Sexy
{
	class ResourceManager
	{
	public:

	public:
		Sexy::SharedImageRef GetImageThrow(const std_string_PVZ& theId);
		bool					ParseResourcesFile(const std_string_PVZ& theFilename);
	};
}