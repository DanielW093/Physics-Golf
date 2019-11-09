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
#pragma once

#include "Color.h"
#include "Vector.h"

class CGame;
class CGraphics;

class EXT_DECL CGameApp
{
	CGame *m_pGame;				// The Game
	CGraphics* m_pGraphics;		// The main screen graphics
	CColor m_colorClear;		// Background Colour

	Uint16 m_FPS;				// Frames per Second rate

	Uint32 m_nTimeStarted;		// System Time when the clock was started/resumed
	Uint32 m_nTimePaused;		// Game Time when clock was suspended (or zero)
	bool m_bRunning;			// set if clock is running (not suspended)

public:
	//////////////////////////////////////
	// Constructor & Destructor

	CGameApp(CGame *pGame = NULL);
	virtual ~CGameApp(void);

	//////////////////////////////////////
	// Attribute Getters and Setters

	// The Game	
	CGame *GetGame()					{ return m_pGame; }
	void SetGame(CGame *pGame);

	// The Graphics
	CGraphics *GetGraphics()			{ return m_pGraphics; }

	// Size of the Canvas
	CVectorI GetSize();
	int GetWidth();
	int GetHeight();

	// Other
	CColor GetClearColor()				{ return m_colorClear; }
	void SetClearColor(CColor c)		{ m_colorClear = c; }
	Uint16 GetFPS()						{ return m_FPS; }
	void SetFPS(Uint16 fps)				{ m_FPS = fps; }
	
	//////////////////////////////////////
	// The Clock

	Uint32 GetSystemTime();		// System Time may be not relevant to the game

	Uint32 GetGameTime();		// Game Time, starts from 0 and suspends when paused

	void ResetClock();			// restarts the clock from zero
	void SuspendClock();		// pauses the clock, the time will not progress
	void ResumeClock();			// resumes the clock after a pause
	bool IsClockRunning();		// returns true when the clock is running (not suspended)

	//////////////////////////////////////
	// Application Operations

	// Open Window/Full Screen
	bool OpenWindow(int nWidth, int nHeight, std::string strTitle);
	bool OpenFullScreen(int nWidth, int nHeight, int nBpp);

	// Main Loop
	bool Run(CGame *pGame = NULL);

	//////////////////////////////////////
	// Ovverridables (rarely used)
	void OnInitialize()							{ }
	bool OnDispatchEvent(SDL_Event *anEvent)	{ return false; }
	bool OnUpdate()								{ return false; }
	void OnTerminate()							{ }
};
