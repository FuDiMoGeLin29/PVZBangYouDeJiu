#include "GameObject.h"

bool GameObject::BeginDraw(Sexy::Graphics* g)
{
	if (!mVisible)
		return false;

	g->Translate(mX, mY);
	return true;
}
