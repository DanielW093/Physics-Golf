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
#include "StdAfx.h"
#include "..\GFC\include\GFC.h"
#include "..\GFC\include\SpriteOval.h"

// Constructors with colour and outline colour
CSpriteOval::CSpriteOval(CVector v, float w, float h, CColor color, CColor colorOutline, long time)
	: CSprite(v, w, h, time), m_color(color), m_colorOutline(colorOutline)
	{ SetColorKey(CColor::AnyBut(color, colorOutline)); }
CSpriteOval::CSpriteOval(float x, float y, float w, float h, CColor color, CColor colorOutline, long time)
	: CSprite(x, y, w, h, time), m_color(color), m_colorOutline(colorOutline)
	{ SetColorKey(CColor::AnyBut(color, colorOutline)); }
CSpriteOval::CSpriteOval(CVector v, float radius, CColor color, CColor colorOutline, long time)
	: CSprite(v, radius+radius, radius+radius, time), m_color(color), m_colorOutline(colorOutline)
	{ SetColorKey(CColor::AnyBut(color, colorOutline)); }
CSpriteOval::CSpriteOval(float x, float y, float radius, CColor color, CColor colorOutline, long time)
	: CSprite(x, y, radius+radius, radius+radius, time), m_color(color), m_colorOutline(colorOutline)
	{ SetColorKey(CColor::AnyBut(color, colorOutline)); }
CSpriteOval::CSpriteOval(CRectangle r, CColor color, CColor colorOutline, long time)
	: CSprite(r, time), m_color(color), m_colorOutline(colorOutline)
	{ SetColorKey(CColor::AnyBut(color, colorOutline)); }

// Constructors with colour and no outline colour
CSpriteOval::CSpriteOval(CVector v, float w, float h, CColor color, long time)
	: CSprite(v, w, h, time), m_color(color), m_colorOutline(color)
	{ SetColorKey(CColor::AnyBut(color)); }
CSpriteOval::CSpriteOval(float x, float y, float w, float h, CColor color, long time)
	: CSprite(x, y, w, h, time), m_color(color), m_colorOutline(color)
	{ SetColorKey(CColor::AnyBut(color)); }
CSpriteOval::CSpriteOval(CVector v, float radius, CColor color, long time)
	: CSprite(v, radius+radius, radius+radius, time), m_color(color), m_colorOutline(color)
	{ SetColorKey(CColor::AnyBut(color)); }
CSpriteOval::CSpriteOval(float x, float y, float radius, CColor color, long time)
	: CSprite(x, y, radius+radius, radius+radius, time), m_color(color), m_colorOutline(color)
	{ SetColorKey(CColor::AnyBut(color)); }
CSpriteOval::CSpriteOval(CRectangle r, CColor color, long time)
	: CSprite(r, time), m_color(color), m_colorOutline(color)
	{ SetColorKey(CColor::AnyBut(color)); }

CSpriteOval::~CSpriteOval()
{
}

void CSpriteOval::OnDraw(CGraphics *g)
{
	if (IsValid()) return;
	CRectangle rect;
	GetClientRect(rect);
	g->FillRect(rect, GetColorKey());
	rect.Grow(0, -1, 0, -1);
	g->FillOval(rect, m_color);
	g->DrawOval(rect, m_colorOutline);
}
