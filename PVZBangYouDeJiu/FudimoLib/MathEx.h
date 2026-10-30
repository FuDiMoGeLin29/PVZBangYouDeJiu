#pragma once
#include "../PVZ/SexyVector.h"
#include "../PVZ/Point.h"

class MathEx
{
public:
	static float LerpF(float theStart, float theEnd, float t)
	{
		return theStart + (theEnd - theStart) * t;
	}
	static double Lerp(double theStart, double theEnd, double t)
	{
		return theStart + (theEnd - theStart) * t;
	}
};