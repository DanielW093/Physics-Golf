#pragma once

class SpriteBall : public CSprite
{
private:
	bool beenHit;
	
	int power;

public:
	bool inHole;

	SpriteBall(Sint16 x, Sint16 y, Uint32 time);
	~SpriteBall(void);

	bool reachedCentre;

	virtual void OnUpdate(Uint32 time, Uint32 deltaTime);

	void hitBall(int power);	

	void setBeenHit(bool value) { beenHit = value; }

	bool getBeenHit() { return beenHit; }

};

