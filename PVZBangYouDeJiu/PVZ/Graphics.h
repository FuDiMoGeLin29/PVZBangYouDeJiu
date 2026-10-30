#pragma once
#include "Color.h"
#include "Rect.h"
#include "Font.h"
#include "Image.h"
namespace Sexy
{
	class Font;
	class SexyMatrix3;
	class Transform;

	const int MAX_TEMP_SPANS = 8192;

	struct Edge
	{
		double mX;
		double mDX;
		int i;
		double b;
	};

	class Graphics;

	class GraphicsState
	{
	public:
		//static Image			mStaticImage;
		void* data;
		Image* mDestImage;
		float					mTransX;
		float					mTransY;
		float					mScaleX;
		float					mScaleY;
		float					mScaleOrigX;
		float					mScaleOrigY;
		Rect					mClipRect;
		Color					mColor;
		Font* mFont;
		int						mDrawMode;
		bool					mColorizeImages;
		bool					mFastStretch;
		bool					mWriteColoredString;
		bool					mLinearBlend;
		bool					mIs3D;

	public:
		//void					CopyStateFrom(const GraphicsState* theState);
	};

	class GraphicsStateList
	{
	public:
		uint8_t data[0x10];
	};

	class Graphics : public GraphicsState
	{
	public:
		enum
		{
			DRAWMODE_NORMAL,
			DRAWMODE_ADDITIVE
		};

		Edge* mPFActiveEdgeList;
		int						mPFNumActiveEdges;
		static const Point* mPFPoints;
		int						mPFNumVertices;

		GraphicsStateList		mStateStack;
	public:
		Graphics(const Graphics& theGraphics);
		void Translate(int theTransX, int theTransY);
		void SetScale(float theScaleX, float theScaleY, float theOrigX, float theOrigY);
		void SetColorizeImages(bool colorizeImages);
		bool GetColorizeImages();
		void SetColor(const Color& theColor);
		Color& GetColor();
		void SetDrawMode(int theDrawMode);
		int GetDrawMode();
		void DrawImage(Image* theImage, int theX, int theY);
		void DrawImage(Image* theImage, int theX, int theY, const Rect& theSrcRect);
		void DrawImage(Image* theImage, int theX, int theY, int theStretchedWidth, int theStretchedHeight);
		void DrawImage(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect);
		void DrawImageMirror(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, bool mirror);
		void DrawImageMirror(Image* theImage, int theX, int theY, bool mirror);
		void DrawImageMirror(Image* theImage, int theX, int theY, const Rect& theSrcRect, bool mirror);
		void DrawRect(int theX, int theY, int theWidth, int theHeight);
		void FillRect(int theX, int theY, int theWidth, int theHeight);
		void PushState();
		void PopState();
		void DrawTrianglesTex(Image* theTexture, const TriVertex theVertices[][3], int theNumTriangles);
	};
}