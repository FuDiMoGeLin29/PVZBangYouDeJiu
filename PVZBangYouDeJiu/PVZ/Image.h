#pragma once
#include "Rect.h"
#include "Color.h"

namespace Sexy
{
	struct Span
	{
		int						mY;
		int						mX;
		int						mWidth;
	};
	class TriVertex;

	class Image
	{
	public:

	public:
		int GetWidth();
		int GetHeight();
		int GetCelWidth();
		int GetCelHeight();
		void BltMirror(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode);
	};
}
