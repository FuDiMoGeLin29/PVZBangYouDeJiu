#pragma once
#include "../PVZ/Rect.h"
#include "../PVZ/SexyVector.h"
#include <cmath>

namespace Fudimo
{
	class RectEx :
		public Sexy::Rect
	{
	public:
		/*RectEx(Sexy::Rect& theRect)
		{
			mX = theRect.mX;
			mY = theRect.mY;
			mWidth = theRect.mWidth;
			mHeight = theRect.mHeight;
		}*/
		RectEx(Sexy::Rect theRect)
		{
			mX = theRect.mX;
			mY = theRect.mY;
			mWidth = theRect.mWidth;
			mHeight = theRect.mHeight;
		}
		operator Sexy::Rect()
		{
			return *this;
		}

		Sexy::Point getCenter()
		{
			return Sexy::Point(this->mX + std::round((float)this->mWidth / 2.0f), this->mY + std::round((float)this->mHeight / 2.0f));
		}

		Sexy::Point getTopCenter()
		{
			return Sexy::Point(this->mX + std::round((float)this->mWidth / 2.0f), this->mY);
		}

		Sexy::Point getBottomCenter()
		{
			return Sexy::Point(this->mX + std::round((float)this->mWidth / 2.0f), this->mY + this->mHeight);
		}

		Sexy::Point getLeftCenter()
		{
			return Sexy::Point(this->mX, this->mY + std::round((float)this->mHeight / 2.0f));
		}

		Sexy::Point getRightCenter()
		{
			return Sexy::Point(this->mX + this->mWidth, this->mY + std::round((float)this->mHeight / 2.0f));
		}

		Sexy::Point getTopLeft()
		{
			return Sexy::Point(this->mX, this->mY);
		}

		Sexy::Point getTopRight()
		{
			return Sexy::Point(this->mX + this->mWidth, this->mY);
		}

		Sexy::Point getBottomLeft()
		{
			return Sexy::Point(this->mX, this->mY + this->mHeight);
		}

		Sexy::Point getBottomRight()
		{
			return Sexy::Point(this->mX + this->mWidth, this->mY + this->mHeight);
		}
	};
}