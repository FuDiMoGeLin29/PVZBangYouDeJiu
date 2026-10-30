#pragma once
#include "Common.h"
#include "Color.h"
#include "Rect.h"

namespace Sexy
{
	class Graphics;

	class Font
	{
	public:
		virtual ~Font() = 0;

		virtual int				GetAscent() = 0;
		virtual int				GetAscentPadding() = 0;
		virtual int				GetDescent() = 0;
		virtual int				GetHeight() = 0;
		virtual int				GetLineSpacingOffset() = 0;
		virtual int				GetLineSpacing() = 0;
		virtual int				StringWidth(const SexyString& theString) = 0;
		virtual int				CharWidth(SexyChar theChar) = 0;
		virtual int				CharWidthKern(SexyChar theChar, SexyChar thePrevChar) = 0;

		virtual void			DrawString(Graphics* g, int theX, int theY, const SexyString& theString, const Color& theColor, const Rect& theClipRect) = 0;

		virtual Font*			Duplicate() = 0;
	};
}