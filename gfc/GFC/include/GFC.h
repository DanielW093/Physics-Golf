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

#ifndef GFC_VERSION
#define GFC_VERSION	160
#endif

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_net.h"
#include "SDL_ttf.h"
#include "SDL_rotozoom.h"
#include "SDL_gfxPrimitives.h"

#ifndef max
#define max(x, y)	((x) > (y) ? (x) : (y))
#endif

#ifndef min
#define min(x, y)	((x) < (y) ? (x) : (y))
#endif

#ifndef RAD2DEG
#define RAD2DEG(x)	((float)(x) * 180.0f / (float)M_PI)
#endif

#ifndef DEG2RAD
#define DEG2RAD(x)  ((float)(x) * (float)M_PI / 180.0f)
#endif

#include <sstream>

#ifdef _USRDLL
   #define EXT_DECL		__declspec(dllexport)
#else
   #define EXT_DECL		__declspec(dllimport)
#endif


#include "Color.h"
#include "Vector.h"
#include "Rectangle.h"
#include "GameApp.h"
#include "Game.h"
#include "Graphics.h"
#include "Sprite.h"
#include "SpriteRect.h"
#include "SpriteOval.h"
#include "SpriteText.h"
#include "Sound.h"

