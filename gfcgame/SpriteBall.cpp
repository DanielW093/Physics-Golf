#include "stdafx.h"
#include "SpriteBall.h"


SpriteBall::SpriteBall(Sint16 x, Sint16 y, Uint32 time) : CSprite(x, y, 20, 20, "images/golfball.gif", time)
{
	beenHit = false;
	reachedCentre = false;
	inHole = false;
}

SpriteBall::~SpriteBall(void)
{
}

void SpriteBall::hitBall(int power)
{
	beenHit = true;
	SetSpeed(power*15);
}
void SpriteBall::OnUpdate(Uint32 time, Uint32 deltaTime)
{
	float s = GetSpeed();
	float friction = 0.3;
	float xDampen = 0.8;
	float yDampen = 0.4;
	CVector velocity = GetVelocity(); 

	if (GetX() > 512)
	{
		reachedCentre = true;
	}

	if (beenHit)
	{
		if(GetSpeed() > 5)
		{			
			if (GetY() > 15)
			{
				Accelerate(0, -7);
			}
			if (HitTest(GetX(), 4) && velocity.Y() < 0)
			{
				float yVelocity = velocity.Y();
				float xVelocity = velocity.X();

				SetVelocity(xVelocity * xDampen, -(yVelocity * yDampen));

				SetY(15);
			}
		}

		if (GetY() < 15)
		{
			SetY(15);
		}

		if (GetY() == 15)
		{
			float fr = sqrt(s) * friction;
			SetSpeed(s - fr);
		}

		if (GetSpeed() <= 5 &&  GetY() <= 16)
		{
			SetPosition(GetX(), 15);
			SetSpeed(0);
		}
	}

	CSprite::OnUpdate(time, deltaTime);
}
