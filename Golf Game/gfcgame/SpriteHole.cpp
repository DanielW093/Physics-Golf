#include "stdafx.h"
#include "SpriteHole.h"


SpriteHole::SpriteHole(Sint16 x, Sint16 y, Uint32 time) : CSprite(x, y, 20, 100, "images/hole.gif", time)
{
}


SpriteHole::~SpriteHole(void)
{
}

void SpriteHole::OnUpdate(Uint32 time, Uint32 deltaTime)
{

	CSprite::OnUpdate(time, deltaTime);
}