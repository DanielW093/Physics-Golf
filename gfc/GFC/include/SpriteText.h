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

class EXT_DECL CSpriteText : public CSprite
{
	Sint16 m_align, m_valign;
	std::string m_strFont;
	Sint16 m_nPtSize;
	std::string m_text;
	CColor m_color;

public:
	CSpriteText(CVector pt, std::string strFont, Sint16 nPtSize, std::string text, CColor color, long time);
	CSpriteText(CVector pt, Sint16 align, Sint16 valign, std::string strFont, Sint16 nPtSize, std::string text, CColor color, long time);
	CSpriteText(float x, float y, std::string strFont, Sint16 nPtSize, std::string text, CColor color, long time);
	CSpriteText(float x, float y, Sint16 align, Sint16 valign, std::string strFont, Sint16 nPtSize, std::string text, CColor color, long time);
	~CSpriteText();

protected:
	virtual void OnPrepareGraphics(CGraphics *pG = NULL);
	virtual void OnDraw(CGraphics *g);
};
