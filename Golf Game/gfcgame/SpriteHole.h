#pragma once
class SpriteHole : public CSprite
{
public:
	SpriteHole(Sint16 x, Sint16 y, Uint32 time);
	~SpriteHole(void);

	virtual void OnUpdate(Uint32 time, Uint32 deltaTime);
};

