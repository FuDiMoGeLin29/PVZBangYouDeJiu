#pragma once
#include <Windows.h>

#define MAX_TRIANGLES 256

namespace Sexy
{
	class Image;
}

namespace Sexy
{

	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	class TriVertex
	{
	public:
		float x, y, u, v;
		DWORD color; //ARGB (0 = use color specified in function call)

	public:
		//TriVertex() { color = 0; }
		//TriVertex(float theX, float theY) : x(theX), y(theY) { color = 0; }
		//TriVertex(float theX, float theY, float theU, float theV) : x(theX), y(theY), u(theU), v(theV) { color = 0; }
		//TriVertex(float theX, float theY, float theU, float theV, DWORD theColor) : x(theX), y(theY), u(theU), v(theV), color(theColor) { }
	};

} // namespace Sexy

class TodTriVertex
{
public:
	float						x;
	float						y;
	float						u;
	float						v;
	unsigned long				color;
};

class TodTriangleGroup
{
public:
	Sexy::Image* mImage;
	Sexy::TriVertex				mVertArray[MAX_TRIANGLES][3];
	int							mTriangleCount;
	int							mDrawMode;

	//TodTriangleGroup();
	//void						DrawGroup(Sexy::Graphics* g);
	//void						AddTriangle(Sexy::Graphics* g, Sexy::Image* theImage, const Sexy::SexyMatrix3& theMatrix, const Sexy::Rect& theClipRect, const Sexy::Color& theColor, int theDrawMode, const Sexy::Rect& theSrcRect);
};

class TodParticleHolder;
class TrailHolder;
class ReanimationHolder;
class AttachmentHolder;
class EffectSystem
{
public:
	TodParticleHolder* mParticleHolder;
	TrailHolder* mTrailHolder;
	ReanimationHolder* mReanimationHolder;
	AttachmentHolder* mAttachmentHolder;

public:
	//EffectSystem();
	//~EffectSystem();

	//void						EffectSystemInitialize();
	//void						EffectSystemDispose();
	//void						EffectSystemFreeAll();
	//void						ProcessDeleteQueue();
	//void						Update();
};