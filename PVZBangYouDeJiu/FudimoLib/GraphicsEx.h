#pragma once
#include "../PVZ/Graphics.h"

namespace Sexy
{
	class MemoryImage;
}

namespace Fudimo
{
	class GraphicsEx : public Sexy::Graphics
	{
	private:
		static Sexy::MemoryImage* mTriangleWhiteTexture;
		void InitTriangleWhiteTexture();
	public:
		////此函数仅3D加速时使用且只能整数坐标
		//bool DrawPolyline3D(Sexy::Point thePoints[], int theNumPoints, const Sexy::Color& theColor, float thickness);
		void DrawPolygonFilledF(Sexy::FPoint thePoints[], int theNumPoints, const Sexy::Color& theColor);
		void DrawPolygonF(Sexy::FPoint thePoints[], int theNumPoints, const Sexy::Color& theColor,float thickness);
		void DrawPolylineF(Sexy::FPoint thePoints[], int theNumPoints, const Sexy::Color& theColor, float thickness);
		void DrawLineF(Sexy::FPoint p1,Sexy::FPoint p2, const Sexy::Color& theColor, float thickness);
		void DrawCircleF(Sexy::FPoint theCenter, float theRadius, const Sexy::Color& theColor, float thickness, float theNumSegments);
		void DrawCircleFilledF(Sexy::FPoint theCenter, float theRadius, const Sexy::Color& theColor, float theNumSegments);
	};
}