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
#ifndef __PROPERTY_H__
#define __PROPERTY_H__

#include "Graphics.h"
#include <vector>

class EXT_DECL PROPERTY
{
	enum { INT, FLOAT, STR, IMG, NONE } type;

	union
	{
		int numi;
		float numf;
	};
	CGraphics *pIm;
	std::string str;

public:
	std::vector<PROPERTY> m_indexedProperties;

public:
	PROPERTY()					{ type = NONE; pIm = NULL; }
	PROPERTY(int d)				{ type = INT; numi = d; pIm = NULL; }
	PROPERTY(float d)			{ type = FLOAT; numf = d; pIm = NULL; }
	PROPERTY(const char *p)		{ type = STR; str = p; pIm = NULL; }
	PROPERTY(CGraphics *p)		{ type = IMG; pIm = new CGraphics(*p); }

	void Erase()				{ if (pIm) delete pIm; for each (PROPERTY prop in m_indexedProperties) prop.Erase(); }

	operator int()				{ if (type == INT) return numi; else if (type == FLOAT) return (int)numf; else return 0; } 
	operator unsigned()			{ if (type == INT) return (unsigned)numi; else if (type == FLOAT) return (unsigned)numf; else return 0; } 
	operator float()			{ if (type == FLOAT) return numf; else if (type == INT) return (float)numi; else return 0; }
	operator const char *()		{ if (type == STR) return str.c_str(); else return ""; }
	operator char *()			{ if (type == STR) return (char*)str.c_str(); else return "NO VALUE"; }
	operator CGraphics *()		{ if (type == IMG) return pIm; else return (pIm = new CGraphics("")); }
};

	
	

#endif //#ifndef __PROPERTY_H__
