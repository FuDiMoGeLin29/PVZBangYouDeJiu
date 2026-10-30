#include "GraphicsEx.h"
#include "../PVZ/SexyVector.h"
#include "../PVZ/TriVertex.h"
#include "../PVZ/MemoryImage.h"
#include "../PVZ/ReanimationLawn.h"
#include <vector>
#include <corecrt_math_defines.h>
#include <cmath>
using namespace Fudimo;

Sexy::MemoryImage* GraphicsEx::mTriangleWhiteTexture = nullptr;

// 在类定义中添加常量（或使用全局常量）
const float MAX_MITER_LIMIT = 4.0f;  // 最大斜接比例（推荐2-4倍线宽）

//bool GraphicsEx::DrawPolyline3D(Sexy::Point thePoints[], int theNumPoints, const Sexy::Color& theColor, float thickness)
//{
//	if (!this->mIs3D)
//	{
//		return false;
//	}
//	if (theNumPoints < 2)
//	{
//		return false;
//	}
//	else if (theNumPoints == 2)
//	{
//		Sexy::Point theVertices[4];
//		Sexy::SexyVector2 theDirection = Sexy::SexyVector2(thePoints[1].mX - thePoints[0].mX, thePoints[1].mY - thePoints[0].mY);
//		Sexy::SexyVector2 theDirectionNormalize = (theDirection.Normalize());
//		Sexy::SexyVector2 thePoint1 = Sexy::SexyVector2(thePoints[0].mX, thePoints[0].mY);
//		Sexy::SexyVector2 thePoint2 = Sexy::SexyVector2(thePoints[1].mX, thePoints[1].mY);
//		Sexy::SexyVector2 temp;
//		temp = theDirectionNormalize.Perp() * (thickness / 2) + thePoint1;
//		theVertices[0] = Sexy::Point(temp.x, temp.y);
//		temp = -theDirectionNormalize.Perp() * (thickness / 2) + thePoint1;
//		theVertices[1] = Sexy::Point(temp.x, temp.y);
//		temp = -theDirectionNormalize.Perp() * (thickness / 2) + thePoint2;
//		theVertices[2] = Sexy::Point(temp.x, temp.y);
//		temp = theDirectionNormalize.Perp() * (thickness / 2) + thePoint2;
//		theVertices[3] = Sexy::Point(temp.x, temp.y);
//		return this->mDestImage->PolyFill3D(theVertices, 4, &this->mClipRect, theColor, this->mDrawMode, this->mTransX, this->mTransY, false);
//	}
//	else
//	{
//		if (this->mIs3D)
//		{
//			bool isSuccess = true;
//			Sexy::SexyVector2 theVec1;
//			Sexy::SexyVector2 theVec2;
//			Sexy::SexyVector2 theVec1Normalize;
//			Sexy::SexyVector2 theVec2Normalize;
//			Sexy::SexyVector2 theAngularBisectorDirection;
//			float theSinTheta;
//			float theDistance;
//			Sexy::SexyVector2 thePoint1;
//			Sexy::SexyVector2 thePoint2;
//			Sexy::Point theVertices[4];
//			Sexy::SexyVector2 temp;
//			float theDistanceAbs;
//			float theMinMagnitude;
//
//			theVec1 = Sexy::SexyVector2(thePoints[1].mX - thePoints[0].mX, thePoints[1].mY - thePoints[0].mY);
//			theVec2 = Sexy::SexyVector2(thePoints[2].mX - thePoints[1].mX, thePoints[2].mY - thePoints[1].mY);
//			theVec1Normalize = theVec1.Normalize();
//			theVec2Normalize = theVec2.Normalize();
//			theAngularBisectorDirection = (-theVec1Normalize + theVec2Normalize).Normalize();
//			theSinTheta = ((-theVec1Normalize).Perp()).Dot(theAngularBisectorDirection) / (((-theVec1Normalize).Perp()).Magnitude() * theAngularBisectorDirection.Magnitude());
//			theDistance = thickness / theSinTheta;
//			theDistanceAbs = abs(theDistance);
//			theMinMagnitude = min(theVec1.Magnitude(), theVec2.Magnitude());
//
//			thePoint1 = Sexy::SexyVector2(thePoints[0].mX, thePoints[0].mY);
//			thePoint2 = Sexy::SexyVector2(thePoints[1].mX, thePoints[1].mY);
//			temp = -theAngularBisectorDirection * ((theDistanceAbs / 2.0f) <= theMinMagnitude ? (theDistance / 2.0f) : theMinMagnitude) + thePoint2;
//			theVertices[0] = Sexy::Point(temp.x, temp.y);
//			temp = theVec1Normalize.Perp() * (thickness / 2.0f) + thePoint1;
//			theVertices[1] = Sexy::Point(temp.x, temp.y);
//			temp = -theVec1Normalize.Perp() * (thickness / 2.0f) + thePoint1;
//			theVertices[2] = Sexy::Point(temp.x, temp.y);
//			temp = theAngularBisectorDirection * ((theDistanceAbs / 2.0f) <= theMinMagnitude ? (theDistance / 2.0f) : theMinMagnitude) + thePoint2;
//			theVertices[3] = Sexy::Point(temp.x, temp.y);
//			isSuccess &= this->mDestImage->PolyFill3D(theVertices, 4, &this->mClipRect, theColor, this->mDrawMode, this->mTransX, this->mTransY, false);
//			for (int i = 0; i < theNumPoints - 3; i++)
//			{
//				theVec1 = Sexy::SexyVector2(thePoints[i + 1].mX - thePoints[i + 0].mX, thePoints[i + 1].mY - thePoints[i + 0].mY);
//				theVec2 = Sexy::SexyVector2(thePoints[i + 2].mX - thePoints[i + 1].mX, thePoints[i + 2].mY - thePoints[i + 1].mY);
//				theVec1Normalize = theVec1.Normalize();
//				theVec2Normalize = theVec2.Normalize();
//				Sexy::SexyVector2 theAngularBisectorDirection1 = (-theVec1Normalize + theVec2Normalize).Normalize();
//				float theSinTheta1 = ((-theVec1Normalize).Perp()).Dot(theAngularBisectorDirection1) / (((-theVec1Normalize).Perp()).Magnitude() * theAngularBisectorDirection1.Magnitude());
//				float theDistance1 = thickness / theSinTheta1;
//				float theDistance1Abs = abs(theDistance1);
//				float theMinMagnitude1 = min(theVec1.Magnitude(), theVec2.Magnitude());
//
//				theVec1 = Sexy::SexyVector2(thePoints[i + 2].mX - thePoints[i + 1].mX, thePoints[i + 2].mY - thePoints[i + 1].mY);
//				theVec2 = Sexy::SexyVector2(thePoints[i + 3].mX - thePoints[i + 2].mX, thePoints[i + 3].mY - thePoints[i + 2].mY);
//				theVec1Normalize = theVec1.Normalize();
//				theVec2Normalize = theVec2.Normalize();
//				Sexy::SexyVector2 theAngularBisectorDirection2 = (-theVec1Normalize + theVec2Normalize).Normalize();
//				float theSinTheta2 = ((-theVec1Normalize).Perp()).Dot(theAngularBisectorDirection2) / (((-theVec1Normalize).Perp()).Magnitude() * theAngularBisectorDirection2.Magnitude());
//				float theDistance2 = thickness / theSinTheta2;
//				float theDistance2Abs = abs(theDistance2);
//				float theMinMagnitude2 = min(theVec1.Magnitude(), theVec2.Magnitude());
//
//
//				thePoint1 = Sexy::SexyVector2(thePoints[i + 1].mX, thePoints[i + 1].mY);
//				thePoint2 = Sexy::SexyVector2(thePoints[i + 2].mX, thePoints[i + 2].mY);
//				temp = -theAngularBisectorDirection1 * ((theDistance1Abs / 2.0f) <= theMinMagnitude1 ? (theDistance1 / 2.0f) : theMinMagnitude1) + thePoint1;
//				theVertices[0] = Sexy::Point(temp.x, temp.y);
//				temp = theAngularBisectorDirection1 * ((theDistance1Abs / 2.0f) <= theMinMagnitude1 ? (theDistance1 / 2.0f) : theMinMagnitude1) + thePoint1;
//				theVertices[1] = Sexy::Point(temp.x, temp.y);
//				temp = theAngularBisectorDirection2 * ((theDistance2Abs / 2.0f) <= theMinMagnitude2 ? (theDistance2 / 2.0f) : theMinMagnitude2) + thePoint2;
//				theVertices[2] = Sexy::Point(temp.x, temp.y);
//				temp = -theAngularBisectorDirection2 * ((theDistance2Abs / 2.0f) <= theMinMagnitude2 ? (theDistance2 / 2.0f) : theMinMagnitude2) + thePoint2;
//				theVertices[3] = Sexy::Point(temp.x, temp.y);
//				isSuccess &= this->mDestImage->PolyFill3D(theVertices, 4, &this->mClipRect, theColor, this->mDrawMode, this->mTransX, this->mTransY, false);
//			}
//			theVec1 = Sexy::SexyVector2(thePoints[theNumPoints - 1 - 1].mX - thePoints[theNumPoints - 1 - 0].mX, thePoints[theNumPoints - 1 - 1].mY - thePoints[theNumPoints - 1 - 0].mY);
//			theVec2 = Sexy::SexyVector2(thePoints[theNumPoints - 1 - 2].mX - thePoints[theNumPoints - 1 - 1].mX, thePoints[theNumPoints - 1 - 2].mY - thePoints[theNumPoints - 1 - 1].mY);
//			theVec1Normalize = theVec1.Normalize();
//			theVec2Normalize = theVec2.Normalize();
//			theAngularBisectorDirection = (-theVec1Normalize + theVec2Normalize).Normalize();
//			theSinTheta = ((-theVec1Normalize).Perp()).Dot(theAngularBisectorDirection) / (((-theVec1Normalize).Perp()).Magnitude() * theAngularBisectorDirection.Magnitude());
//			theDistance = thickness / theSinTheta;
//			theDistanceAbs = abs(theDistance);
//			theMinMagnitude = min(theVec1.Magnitude(), theVec2.Magnitude());
//
//			thePoint1 = Sexy::SexyVector2(thePoints[theNumPoints - 1 - 0].mX, thePoints[theNumPoints - 1 - 0].mY);
//			thePoint2 = Sexy::SexyVector2(thePoints[theNumPoints - 1 - 1].mX, thePoints[theNumPoints - 1 - 1].mY);
//			temp = -theAngularBisectorDirection * ((theDistanceAbs / 2.0f) <= theMinMagnitude ? (theDistance / 2.0f) : theMinMagnitude) + thePoint2;
//			theVertices[0] = Sexy::Point(temp.x, temp.y);
//			temp = theVec1Normalize.Perp() * (thickness / 2.0f) + thePoint1;
//			theVertices[1] = Sexy::Point(temp.x, temp.y);
//			temp = -theVec1Normalize.Perp() * (thickness / 2.0f) + thePoint1;
//			theVertices[2] = Sexy::Point(temp.x, temp.y);
//			temp = theAngularBisectorDirection * ((theDistanceAbs / 2.0f) <= theMinMagnitude ? (theDistance / 2.0f) : theMinMagnitude) + thePoint2;
//			theVertices[3] = Sexy::Point(temp.x, temp.y);
//			isSuccess &= this->mDestImage->PolyFill3D(theVertices, 4, &this->mClipRect, theColor, this->mDrawMode, this->mTransX, this->mTransY, false);
//			return isSuccess;
//		}
//		return false;
//	}
//}

void GraphicsEx::InitTriangleWhiteTexture()
{
	unsigned long theWhiteColor = 0xFFFFFFFF;
	mTriangleWhiteTexture = ReanimatorCache::MakeBlankMemoryImage(1, 1);
	mTriangleWhiteTexture->SetBits(&theWhiteColor, 1, 1, true);
}

void GraphicsEx::DrawPolygonFilledF(Sexy::FPoint thePoints[], int theNumPoints, const Sexy::Color& theColor)
{
	if (mTriangleWhiteTexture == nullptr)
	{
		this->InitTriangleWhiteTexture();
	}
	if (theNumPoints < 3)
	{
		return;
	}
	Sexy::TriVertex* theVertices = new Sexy::TriVertex[(theNumPoints - 2) * 3];
	for (int i = 0; i < theNumPoints - 2; i++)
	{
		theVertices[0 + i * 3] = Sexy::TriVertex(thePoints[0].mX, thePoints[0].mY, 0, 0, theColor.ToInt());
		theVertices[1 + i * 3] = Sexy::TriVertex(thePoints[i + 1].mX, thePoints[i + 1].mY, 0, 0, theColor.ToInt());
		theVertices[2 + i * 3] = Sexy::TriVertex(thePoints[i + 2].mX, thePoints[i + 2].mY, 0, 0, theColor.ToInt());
	}
	this->DrawTrianglesTex(mTriangleWhiteTexture, (Sexy::TriVertex(*)[3])theVertices, theNumPoints - 2);
	delete[] theVertices;
}

void GraphicsEx::DrawPolygonF(Sexy::FPoint thePoints[], int theNumPoints, const Sexy::Color& theColor, float thickness)
{
	if (mTriangleWhiteTexture == nullptr)
	{
		this->InitTriangleWhiteTexture();
	}
	if (theNumPoints < 3)
	{
		return;
	}
	Sexy::TriVertex(*theVertices)[3] = new Sexy::TriVertex[theNumPoints * 2][3];
	auto GetVertices = [&](int theIndex,int p1Index, int p2Index, int p3Index,int p4Index) {
		Sexy::SexyVector2 theVec1;
		Sexy::SexyVector2 theVec2;
		Sexy::SexyVector2 theVec1Normalize;
		Sexy::SexyVector2 theVec2Normalize;
		Sexy::SexyVector2 theAngularBisectorDirection;
		Sexy::SexyVector2 thePoint1;
		Sexy::SexyVector2 thePoint2;
		Sexy::SexyVector2 temp;
		float maxExtension = thickness * MAX_MITER_LIMIT; // 最大延伸长度

		theVec1 = Sexy::SexyVector2(thePoints[p2Index].mX - thePoints[p1Index].mX, thePoints[p2Index].mY - thePoints[p1Index].mY);
		theVec2 = Sexy::SexyVector2(thePoints[p3Index].mX - thePoints[p2Index].mX, thePoints[p3Index].mY - thePoints[p2Index].mY);
		theVec1Normalize = theVec1.Normalize();
		theVec2Normalize = theVec2.Normalize();
		Sexy::SexyVector2 theAngularBisectorDirection1 = (-theVec1Normalize + theVec2Normalize).Normalize();
		if (theAngularBisectorDirection1 == Sexy::SexyVector2(0, 0))
		{
			theAngularBisectorDirection1 = theVec1Normalize.Perp();
		}
		float theSinTheta1 = ((-theVec1Normalize).Perp()).Dot(theAngularBisectorDirection1) / (((-theVec1Normalize).Perp()).Magnitude() * theAngularBisectorDirection1.Magnitude());
		float theDistance1 = thickness / theSinTheta1;
		// 应用斜接限制
		if (std::abs(theDistance1) > maxExtension) {
			theDistance1 = (theDistance1 > 0) ? maxExtension : -maxExtension;
		}

		theVec1 = Sexy::SexyVector2(thePoints[p3Index].mX - thePoints[p2Index].mX, thePoints[p3Index].mY - thePoints[p2Index].mY);
		theVec2 = Sexy::SexyVector2(thePoints[p4Index].mX - thePoints[p3Index].mX, thePoints[p4Index].mY - thePoints[p3Index].mY);
		theVec1Normalize = theVec1.Normalize();
		theVec2Normalize = theVec2.Normalize();
		Sexy::SexyVector2 theAngularBisectorDirection2 = (-theVec1Normalize + theVec2Normalize).Normalize();
		if (theAngularBisectorDirection2 == Sexy::SexyVector2(0, 0))
		{
			theAngularBisectorDirection2 = theVec1Normalize.Perp();
		}
		float theSinTheta2 = ((-theVec1Normalize).Perp()).Dot(theAngularBisectorDirection2) / (((-theVec1Normalize).Perp()).Magnitude() * theAngularBisectorDirection2.Magnitude());
		float theDistance2 = thickness / theSinTheta2;
		// 应用斜接限制
		if (std::abs(theDistance2) > maxExtension) {
			theDistance2 = (theDistance2 > 0) ? maxExtension : -maxExtension;
		}

		thePoint1 = Sexy::SexyVector2(thePoints[p2Index].mX, thePoints[p2Index].mY);
		thePoint2 = Sexy::SexyVector2(thePoints[p3Index].mX, thePoints[p3Index].mY);
		temp = -theAngularBisectorDirection1 * (theDistance1 / 2.0f) + thePoint1;
		theVertices[theIndex * 2 + 0][0] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
		temp = theAngularBisectorDirection1 * (theDistance1 / 2.0f) + thePoint1;
		theVertices[theIndex * 2 + 0][1] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
		temp = theAngularBisectorDirection2 * (theDistance2 / 2.0f) + thePoint2;
		theVertices[theIndex * 2 + 0][2] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());

		temp = theAngularBisectorDirection2 * (theDistance2 / 2.0f) + thePoint2;
		theVertices[theIndex * 2 + 1][0] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
		temp = -theAngularBisectorDirection2 * (theDistance2 / 2.0f) + thePoint2;
		theVertices[theIndex * 2 + 1][1] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
		temp = -theAngularBisectorDirection1 * (theDistance1 / 2.0f) + thePoint1;
		theVertices[theIndex * 2 + 1][2] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
		};

	GetVertices(0,2,1,0, theNumPoints - 1);
	for (int i = 0; i < theNumPoints - 3;i++)
	{
		GetVertices(i + 1,i, i + 1, i + 2, i + 3);
	}

	GetVertices(theNumPoints - 2,0, theNumPoints - 1, theNumPoints - 2, theNumPoints - 3);
	GetVertices(theNumPoints - 1,1, 0, theNumPoints - 1, theNumPoints - 2);
	this->DrawTrianglesTex(mTriangleWhiteTexture, theVertices, theNumPoints * 2);
	delete[] theVertices;
}

void GraphicsEx::DrawPolylineF(Sexy::FPoint thePoints[], int theNumPoints, const Sexy::Color& theColor, float thickness)
{
	if (mTriangleWhiteTexture == nullptr)
	{
		this->InitTriangleWhiteTexture();
	}
	if (theNumPoints < 2)
	{
		return;
	}
	else if (theNumPoints == 2)
	{
		Sexy::TriVertex theVertices[2][3];
		Sexy::SexyVector2 theDirection = Sexy::SexyVector2(thePoints[1].mX - thePoints[0].mX, thePoints[1].mY - thePoints[0].mY);
		Sexy::SexyVector2 theDirectionNormalize = (theDirection.Normalize());
		Sexy::SexyVector2 thePoint1 = Sexy::SexyVector2(thePoints[0].mX, thePoints[0].mY);
		Sexy::SexyVector2 thePoint2 = Sexy::SexyVector2(thePoints[1].mX, thePoints[1].mY);
		Sexy::SexyVector2 temp;
		temp = theDirectionNormalize.Perp() * (thickness / 2) + thePoint1;
		theVertices[0][0] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
		temp = -theDirectionNormalize.Perp() * (thickness / 2) + thePoint1;
		theVertices[0][1] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
		temp = -theDirectionNormalize.Perp() * (thickness / 2) + thePoint2;
		theVertices[0][2] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
		
		temp = theDirectionNormalize.Perp() * (thickness / 2) + thePoint1;
		theVertices[1][0] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
		temp = -theDirectionNormalize.Perp() * (thickness / 2) + thePoint2;
		theVertices[1][1] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
		temp = theDirectionNormalize.Perp() * (thickness / 2) + thePoint2;
		theVertices[1][2] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
		this->DrawTrianglesTex(mTriangleWhiteTexture, theVertices, 2);
	}
	else
	{
		Sexy::SexyVector2 theVec1;
		Sexy::SexyVector2 theVec2;
		Sexy::SexyVector2 theVec1Normalize;
		Sexy::SexyVector2 theVec2Normalize;
		Sexy::SexyVector2 theAngularBisectorDirection;
		float theSinTheta;
		float theDistance;
		Sexy::SexyVector2 thePoint1;
		Sexy::SexyVector2 thePoint2;
		Sexy::TriVertex(*theVertices)[3] = new Sexy::TriVertex[(theNumPoints - 1) * 2][3];
		Sexy::SexyVector2 temp;
		float theDistanceAbs;
		float theMinMagnitude; 
		float maxExtension = thickness * MAX_MITER_LIMIT; // 最大延伸长度
		auto GetStartOrEndVertices = [&](int theIndex, int p1Index, int p2Index, int p3Index) {
			theVec1 = Sexy::SexyVector2(thePoints[p2Index].mX - thePoints[p1Index].mX, thePoints[p2Index].mY - thePoints[p1Index].mY);
			theVec2 = Sexy::SexyVector2(thePoints[p3Index].mX - thePoints[p2Index].mX, thePoints[p3Index].mY - thePoints[p2Index].mY);
			theVec1Normalize = theVec1.Normalize();
			theVec2Normalize = theVec2.Normalize();
			theAngularBisectorDirection = (-theVec1Normalize + theVec2Normalize).Normalize();
			if (theAngularBisectorDirection == Sexy::SexyVector2(0, 0))
			{
				theAngularBisectorDirection = theVec1Normalize.Perp();
			}
			theSinTheta = ((-theVec1Normalize).Perp()).Dot(theAngularBisectorDirection) / (((-theVec1Normalize).Perp()).Magnitude() * theAngularBisectorDirection.Magnitude());
			theDistance = thickness / theSinTheta;

			// 应用斜接限制
			if (std::abs(theDistance) > maxExtension) {
				theDistance = (theDistance > 0) ? maxExtension : -maxExtension;
			}

			thePoint1 = Sexy::SexyVector2(thePoints[p1Index].mX, thePoints[p1Index].mY);
			thePoint2 = Sexy::SexyVector2(thePoints[p2Index].mX, thePoints[p2Index].mY);
			temp = -theAngularBisectorDirection * (theDistance / 2.0f) + thePoint2;
			theVertices[theIndex * 2 + 0][0] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
			temp = theVec1Normalize.Perp() * (thickness / 2.0f) + thePoint1;
			theVertices[theIndex * 2 + 0][1] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
			temp = -theVec1Normalize.Perp() * (thickness / 2.0f) + thePoint1;
			theVertices[theIndex * 2 + 0][2] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());

			temp = -theAngularBisectorDirection * (theDistance / 2.0f) + thePoint2;
			theVertices[theIndex * 2 + 1][0] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
			temp = -theVec1Normalize.Perp() * (thickness / 2.0f) + thePoint1;
			theVertices[theIndex * 2 + 1][1] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
			temp = theAngularBisectorDirection * (theDistance / 2.0f) + thePoint2;
			theVertices[theIndex * 2 + 1][2] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
			};

		GetStartOrEndVertices(0, 0, 1, 2);
		for (int i = 0; i < theNumPoints - 3; i++)
		{
			theVec1 = Sexy::SexyVector2(thePoints[i + 1].mX - thePoints[i + 0].mX, thePoints[i + 1].mY - thePoints[i + 0].mY);
			theVec2 = Sexy::SexyVector2(thePoints[i + 2].mX - thePoints[i + 1].mX, thePoints[i + 2].mY - thePoints[i + 1].mY);
			theVec1Normalize = theVec1.Normalize();
			theVec2Normalize = theVec2.Normalize();
			Sexy::SexyVector2 theAngularBisectorDirection1 = (-theVec1Normalize + theVec2Normalize).Normalize();
			if (theAngularBisectorDirection1 == Sexy::SexyVector2(0, 0))
			{
				theAngularBisectorDirection1 = theVec1Normalize.Perp();
			}
			float theSinTheta1 = ((-theVec1Normalize).Perp()).Dot(theAngularBisectorDirection1) / (((-theVec1Normalize).Perp()).Magnitude() * theAngularBisectorDirection1.Magnitude());
			float theDistance1 = thickness / theSinTheta1;

			// 应用斜接限制
			if (std::abs(theDistance1) > maxExtension) {
				theDistance1 = (theDistance1 > 0) ? maxExtension : -maxExtension;
			}

			theVec1 = Sexy::SexyVector2(thePoints[i + 2].mX - thePoints[i + 1].mX, thePoints[i + 2].mY - thePoints[i + 1].mY);
			theVec2 = Sexy::SexyVector2(thePoints[i + 3].mX - thePoints[i + 2].mX, thePoints[i + 3].mY - thePoints[i + 2].mY);
			theVec1Normalize = theVec1.Normalize();
			theVec2Normalize = theVec2.Normalize();
			Sexy::SexyVector2 theAngularBisectorDirection2 = (-theVec1Normalize + theVec2Normalize).Normalize();
			if (theAngularBisectorDirection2 == Sexy::SexyVector2(0, 0))
			{
				theAngularBisectorDirection2 = theVec1Normalize.Perp();
			}
			float theSinTheta2 = ((-theVec1Normalize).Perp()).Dot(theAngularBisectorDirection2) / (((-theVec1Normalize).Perp()).Magnitude() * theAngularBisectorDirection2.Magnitude());
			float theDistance2 = thickness / theSinTheta2;

			// 应用斜接限制
			if (std::abs(theDistance2) > maxExtension) {
				theDistance2 = (theDistance2 > 0) ? maxExtension : -maxExtension;
			}

			thePoint1 = Sexy::SexyVector2(thePoints[i + 1].mX, thePoints[i + 1].mY);
			thePoint2 = Sexy::SexyVector2(thePoints[i + 2].mX, thePoints[i + 2].mY);
			temp = -theAngularBisectorDirection1 * (theDistance1 / 2.0f) + thePoint1;
			theVertices[(i + 1) * 2 + 0][0] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
			temp = theAngularBisectorDirection1 * (theDistance1 / 2.0f) + thePoint1;
			theVertices[(i + 1) * 2 + 0][1] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
			temp = theAngularBisectorDirection2 * (theDistance2 / 2.0f) + thePoint2;
			theVertices[(i + 1) * 2 + 0][2] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());

			temp = -theAngularBisectorDirection1 * (theDistance1 / 2.0f) + thePoint1;
			theVertices[(i + 1) * 2 + 1][0] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
			temp = theAngularBisectorDirection2 * (theDistance2 / 2.0f) + thePoint2;
			theVertices[(i + 1) * 2 + 1][1] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
			temp = -theAngularBisectorDirection2 * (theDistance2 / 2.0f) + thePoint2;
			theVertices[(i + 1) * 2 + 1][2] = Sexy::TriVertex(temp.x, temp.y, 0, 0, theColor.ToInt());
		}

		GetStartOrEndVertices(theNumPoints - 2, theNumPoints - 1 - 0, theNumPoints - 1 - 1, theNumPoints - 1 - 2);
		this->DrawTrianglesTex(mTriangleWhiteTexture, theVertices, (theNumPoints - 1) * 2);
		delete[] theVertices;
	}
}

void GraphicsEx::DrawLineF(Sexy::FPoint p1, Sexy::FPoint p2, const Sexy::Color& theColor, float thickness)
{
	Sexy::FPoint thePoints[2] = { p1,p2 };
	DrawPolygonF(thePoints, 2, theColor, thickness);
}

void GraphicsEx::DrawCircleF(Sexy::FPoint theCenter, float theRadius, const Sexy::Color& theColor, float thickness, float theNumSegments)
{
	if (theRadius < 0.0f)
	{
		return;
	}
	Sexy::FPoint* thePoints = new Sexy::FPoint[theNumSegments];
	float theAngleStep = 2.0f * M_PI / theNumSegments;
	for (int i = 0; i < theNumSegments; i++)
	{
		thePoints[i] = Sexy::FPoint(theCenter.mX + cos(theAngleStep * i) * theRadius, theCenter.mY + sin(theAngleStep * i) * theRadius);
	}
	DrawPolygonF(thePoints, theNumSegments, theColor, thickness);
	delete[] thePoints;
}

void GraphicsEx::DrawCircleFilledF(Sexy::FPoint theCenter, float theRadius, const Sexy::Color& theColor, float theNumSegments)
{
	if (theRadius < 0.0f)
	{
		return;
	}
	Sexy::FPoint* thePoints = new Sexy::FPoint[theNumSegments + 2];
	thePoints[0] = theCenter;
	float theAngleStep = 2.0f * M_PI / theNumSegments;
	for (int i = 0; i < theNumSegments + 1; i++)
	{
		thePoints[i + 1] = Sexy::FPoint(theCenter.mX + cos(theAngleStep * i) * theRadius, theCenter.mY + sin(theAngleStep * i) * theRadius);
	}
	DrawPolygonFilledF(thePoints, theNumSegments + 2, theColor);
	delete[] thePoints;
}