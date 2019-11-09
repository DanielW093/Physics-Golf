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
#include "..\GFC\include\GameApp.h"
#include "..\GFC\include\Game.h"
#include "..\GFC\include\Graphics.h"

//////////////////////////////////////
// Constructor & Destructor

CGameApp::CGameApp(CGame *pGame) : m_pGame(pGame), m_pGraphics(NULL), m_colorClear(0, 0, 0), m_FPS(60)
{
	srand((unsigned)time(NULL));
	while (rand() < 2000);
	if (m_pGame) m_pGame->SetApp(this);
}

CGameApp::~CGameApp()
{
	if (m_pGraphics) delete m_pGraphics;
}

//////////////////////////////////////
// Attribute Getters and Setters

void CGameApp::SetGame(CGame *pGame)
{
	m_pGame = pGame;
	if (!m_pGame) return;
	m_pGame->SetApp(this);
	m_pGame->SetSize(GetWidth(), GetHeight());
}

CVectorI CGameApp::GetSize()	{ return CVectorI(GetWidth(), GetHeight()); }
int CGameApp::GetWidth()		{ return GetGraphics() ? GetGraphics()->GetWidth() : 0; }
int CGameApp::GetHeight()		{ return GetGraphics() ? GetGraphics()->GetHeight() : 0; }

//////////////////////////////////////
// The Clock

Uint32 CGameApp::GetSystemTime()
{
	return SDL_GetTicks();
}

Uint32 CGameApp::GetGameTime()
{
	Uint32 t = GetSystemTime();
	if (m_bRunning)
		return m_nTimePaused + t - m_nTimeStarted;
	else
		return m_nTimePaused;
}

void CGameApp::ResetClock()
{
	m_nTimeStarted = GetSystemTime();
	m_nTimePaused = 0;
	m_bRunning = true;
}

void CGameApp::SuspendClock()
{
	if (!m_bRunning) return;
	m_nTimePaused = GetGameTime();
	m_bRunning = false;
}

void CGameApp::ResumeClock()
{
	if (m_bRunning) return;
	m_nTimeStarted = GetSystemTime();
	m_bRunning = true;
}

bool CGameApp::IsClockRunning()
{
	return m_bRunning;
}

//////////////////////////////////////
// Application Operations

bool CGameApp::OpenWindow(int nWidth, int nHeight, std::string strTitle)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return false;

	if (TTF_Init() == -1)
		return false;

	if (m_pGame) m_pGame->SetSize(nWidth, nHeight);
	
	atexit(SDL_Quit);
	m_pGraphics = new CGraphics(SDL_SetVideoMode(nWidth, nHeight, 0, SDL_ANYFORMAT | SDL_SWSURFACE));
	if (!m_pGraphics)
		return false;

	SDL_WM_SetCaption(strTitle.c_str(), strTitle.c_str());

	return true;
}

bool CGameApp::OpenFullScreen(int nWidth, int nHeight, int nBpp)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return false;
	
	if (TTF_Init() == -1)
		return false;

	if (m_pGame) m_pGame->SetSize(nWidth, nHeight);

	atexit(SDL_Quit);
	m_pGraphics = new CGraphics(SDL_SetVideoMode(nWidth, nHeight, nBpp, SDL_FULLSCREEN));
	if (!m_pGraphics)
		return false;

	return true;
}

bool CGameApp::Run(CGame *pGame)
{
	if (pGame) SetGame(pGame);
	if (!m_pGame) return false;
	if (!m_pGraphics) return false;

	SDL_Event anEvent;
	int idGame = 0;

	ResetClock();
	Uint32 timeStamp = GetSystemTime();
	OnInitialize();
	m_pGame->OnInitialize();
	m_pGame->OnDisplayMenu();
	Uint32 nFrames;

	// again..
	ResetClock();
	timeStamp = GetSystemTime();

	// The Main Animation Loop
	while (m_pGame->IsRunning())
	{
		Uint32 period = 1000 / m_FPS;

		while (m_pGame->IsRunning() && SDL_PollEvent(&anEvent))
			if (!OnDispatchEvent(&anEvent))
			{
				m_pGame->SetTime(GetGameTime());
				if (anEvent.type == SDL_QUIT)
					m_pGame->StopGame();
				m_pGame->DispatchEvents(&anEvent);
			}
		
		if (!m_pGame->IsRunning()) break;
		if (!OnUpdate())
		{
			// calculate timing (considering pausing)
			if (m_pGame->IsPaused())
				SuspendClock();
			else
				ResumeClock();

			// handle the game mode requests
			m_pGame->HandleGameState();

			// update the game
			if (!m_pGame->IsPaused())
			{
				Uint32 T = GetGameTime();
				
				// check the number of frames to cover
				m_pGame->SetTime(T);
				nFrames = max(1, m_pGame->GetDeltaTime() / period);

				for (int iFrame = 1 - nFrames; iFrame < 1; iFrame++)
				{
					m_pGame->SetTime(T + iFrame * period);
					m_pGame->OnUpdate();
					m_pGame->CatchDeltaTime();
				}
			}

			if (!m_pGame->IsRunning()) break;

			// draw the game
			m_pGraphics->Clear(m_colorClear);
			m_pGame->OnDraw(m_pGraphics);

			//time_t theTime = time(NULL);
			//struct tm *aTime = localtime(&theTime);
			//if (aTime->tm_year > 113)
			//{
			//	*m_pGraphics << font(32) << vcenter << center << color(CColor::Red()) << "GFC VERSION YOU ARE USING" << endl << "IS OUTDATED" << endl;
			//	*m_pGraphics << font(22) << endl << "PLEASE DOWNLOAD & INSTALL THE CURRENT VERSION" << endl;
			//}

			// flush any remaining text
			m_pGraphics->Flush();

			// flip buffers
			m_pGraphics->Flip();
		}
		// Controlling the Time
		Sint32 sleepTime = period * nFrames - (GetSystemTime() - timeStamp);
		timeStamp += period * nFrames;

		if (sleepTime > 0)
			SDL_Delay(sleepTime);
	}
	m_pGame->OnTerminate();
	OnTerminate();
	if (m_pGraphics) delete m_pGraphics;
	m_pGraphics = NULL;
	TTF_Quit();
	SDL_Quit();
	return true;
}

