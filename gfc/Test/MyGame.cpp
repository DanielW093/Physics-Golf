/****************************************************************************
GFC - Games Fundamental Classes
Copyright (C) 2009-2014 Jarek Francik, Kingston University London

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source distribution.

   Jarek Francik
   jarek@kingston.ac.uk
****************************************************************************/
#include "stdafx.h"
#include "MyGame.h"

CMyGame::CMyGame(void) : m_sprite(50, 50, "rocket.bmp", CColor::Blue(), 0)
{ 

}

CMyGame::~CMyGame(void)
{
	for (CSpriteIter i = m_sprites.begin(); i != m_sprites.end(); i++)
		delete *i;
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	for each (CSprite *p in m_sprites)
	{
		p->Update(GetTime());
	}

	m_sprite.SetVelocity(m_sprite.GetVelocity() + CVector(0, -1));
	m_sprite.SetRotation(m_sprite.GetDirection());
	m_sprite.Update(GetTime());
}

void CMyGame::OnDraw(CGraphics* g)
{
	for (int i = 0; i < 800; i += 10) g->DrawVLine(CVector((float)i, (float)0), 600, CColor::DarkGray());
	for (int i = 0; i < 600; i += 10) g->DrawHLine(CVector((float)0, (float)i), 800, CColor::DarkGray());

	for (CSpriteIter i = m_sprites.begin(); i != m_sprites.end(); i++)
		(*i)->Draw(g);


	if (IsKeyDown(SDLK_UP))		{ *g << bottom << endl << centre << "Arrow UP is pressed"; }
	if (IsKeyDown(SDLK_DOWN))	{ *g << bottom << centre << "Arrow DOWN is pressed"; }
	if (IsKeyDown(SDLK_LEFT))	{ *g << bottom << left << "Arrow LEFT is pressed"; 	}
	if (IsKeyDown(SDLK_RIGHT))	{ *g << bottom << right << "Arrow RIGHT is pressed"; }
	if (!IsKeyDown(SDLK_UP) && !IsKeyDown(SDLK_DOWN) && !IsKeyDown(SDLK_LEFT) && !IsKeyDown(SDLK_RIGHT)) { *g << bottom << centre << "Use Arrows to change this text"; }

	m_sprite.Draw(g);
}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
}


// called at the start of a new game - display menu here
void CMyGame::OnDisplayMenu()
{
	CSprite *pSprite;
	m_sprites.push_back(pSprite = new CSpriteRect(60, 540, 101, 101, CColor::Red(), CColor::Black(), GetTime()));
	m_sprites.push_back(pSprite = new CSpriteRect(60, 340, 101, 101, CColor::Red(), CColor::Black(), GetTime()));
	pSprite->SetOmega(30);
	m_sprites.push_back(pSprite = new CSpriteOval(260, 540, 101, 101, CColor::Yellow(), CColor::Black(), GetTime()));
	m_sprites.push_back(pSprite = new CSpriteOval(260, 340, 101, 101, CColor::Yellow(), CColor::Black(), GetTime()));
	pSprite->SetOmega(30);
	m_sprites.push_back(pSprite = new CSpriteText(510, 540, "arial.ttf", 24, "THIS IS A TEXT", CColor::Black(), GetTime()));
	m_sprites.push_back(pSprite = new CSpriteText(510, 340, "arial.ttf", 24, "THIS IS A TEXT", CColor::Black(), GetTime()));
	pSprite->SetOmega(30);
	m_sprites.push_back(pSprite = new CSprite(710, 540, "rocket.bmp", CColor::Blue(), GetTime()));
	m_sprites.push_back(pSprite = new CSprite(710, 340, "rocket.bmp", CColor::Blue(), GetTime()));
	pSprite->SetOmega(30);
	m_sprites.push_back(pSprite = new CSprite(235, 130, 250, 120, "rocket.bmp", CColor::Blue(), GetTime()));
	m_sprites.push_back(pSprite = new CSprite(735, 130, 250, 120, "rocket.bmp", CColor::Blue(), GetTime()));
	pSprite->SetOmega(30);
	m_sprites.push_back(pSprite = new CSpriteRect(461, 130, 2, 120, CColor::Blue(), GetTime()));
	//pSprite->SetPivotFromCenter(0, -50);
	pSprite->SetOmega(30);

	m_sprite.SetPosition(400, 300);
	m_sprite.SetDirection(-30);
	m_sprite.SetSpeed(100);
	m_sprite.SetRotation(m_sprite.GetDirection());
}

// called when Game Mode entered
void CMyGame::OnStartGame()
{
}

// called when Game is Over
void CMyGame::OnGameOver()
{
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_SPACE)
		PauseGame();
	if (sym == SDLK_F2)
		NewGame();
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
