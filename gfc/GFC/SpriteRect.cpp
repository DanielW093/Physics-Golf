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
#include "..\GFC\include\GFC.h"
#include "..\GFC\include\SpriteRect.h"

// Constructors with colour and outline colour
CSpriteRect::CSpriteRect(CVector v, float w, float h, CColor color, CColor colorOutline, long time)
	: CSprite(v, w, h, time), m_color(color), m_colorOutline(colorOutline)
	{ SetColorKey(CColor::AnyBut(color, colorOutline)); }
CSpriteRect::CSpriteRect(float x, float y, float w, float h, CColor color, CColor colorOutline, long time)
	: CSprite(x, y, w, h, time), m_color(color), m_colorOutline(colorOutline)
	{ SetColorKey(CColor::AnyBut(color, colorOutline)); }
CSpriteRect::CSpriteRect(CRectangle r, CColor color, CColor colorOutline, long time)
	: CSprite(r, time), m_color(color), m_colorOutline(colorOutline)
	{ SetColorKey(CColor::AnyBut(color, colorOutline)); }

// Constructors with colour and no outline colour
CSpriteRect::CSpriteRect(CVector v, float w, float h, CColor color, long time)
	: CSprite(v, w, h, time), m_color(color), m_colorOutline(color)
	{ SetColorKey(CColor::AnyBut(color)); }
CSpriteRect::CSpriteRect(float x, float y, float w, float h, CColor color, long time)
	: CSprite(x, y, w, h, time), m_color(color), m_colorOutline(color)
	{ SetColorKey(CColor::AnyBut(color)); }
CSpriteRect::CSpriteRect(CRectangle r, CColor color, long time)
	: CSprite(r, time), m_color(color), m_colorOutline(color)
	{ SetColorKey(CColor::AnyBut(color)); }


CSpriteRect::~CSpriteRect()
{
}

void CSpriteRect::OnDraw(CGraphics *g)
{
	if (IsValid()) return;
	CRectangle rect;
	GetClientRect(rect);
	g->FillRect(rect, m_color);
	rect.Grow(0, -1, 0, -1);
	g->DrawRect(rect, m_colorOutline);
}