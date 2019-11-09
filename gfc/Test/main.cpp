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
#include  "crtdbg.h"

CMyGame game;
CGameApp app;

int main(int argc, char* argv[])
{
	#ifndef NDEBUG
		int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
		flag |= _CRTDBG_LEAK_CHECK_DF;
		_CrtSetDbgFlag(flag); 
	#endif

	app.OpenWindow(800, 600, "My Game!");
	//app.OpenFullScreen(800, 600, 24);
	app.SetClearColor(CColor::LightGray());
	app.Run(&game);
	return(0);
}
