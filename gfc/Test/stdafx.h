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
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

#define max(x, y)	((x) > (y) ? (x) : (y))
#define min(x, y)	((x) < (y) ? (x) : (y))

#include "GFC.h"

//#ifdef _DEBUG
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#endif
