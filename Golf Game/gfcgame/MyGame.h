#pragma once
#include "SpriteBall.h"
#include "SpriteHole.h"

class CMyGame : public CGame
{
public:
	CMyGame(void);
	~CMyGame(void);
	//Sprites
	CSprite city1;	CSprite city2;
	CSprite tree1;	CSprite tree2;	CSprite tree3;	CSprite tree4;	CSprite tree5;
	CSprite hedge1;	CSprite hedge2;
	CSprite grass1;	CSprite grass2;
	CSprite background;
	CSprite arrow;
	CSprite windArrow;
	CSprite powerBar;
	CSprite powerBarInside;
	SpriteHole *hole;
	SpriteBall *ball;
	CSprite cloud1;	CSprite cloud2;	CSprite cloud3;	CSprite cloud4;

	void parallaxScroll();
	void controls();

	// Per-Frame Callback Funtions (must be implemented!)
	virtual void OnUpdate();
	virtual void OnDraw(CGraphics* g);

	// Game Life Cycle
	virtual void OnInitialize();
	virtual void OnDisplayMenu();
	virtual void OnStartGame();
	virtual void OnStartLevel(Sint16 nLevel);
	virtual void OnGameOver();
	virtual void OnTerminate();

	// Keyboard Event Handlers
	virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	// Mouse Events Handlers
	virtual void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	virtual void OnLButtonDown(Uint16 x,Uint16 y);
	virtual void OnLButtonUp(Uint16 x,Uint16 y);
	virtual void OnRButtonDown(Uint16 x,Uint16 y);
	virtual void OnRButtonUp(Uint16 x,Uint16 y);
	virtual void OnMButtonDown(Uint16 x,Uint16 y);
	virtual void OnMButtonUp(Uint16 x,Uint16 y);
};
