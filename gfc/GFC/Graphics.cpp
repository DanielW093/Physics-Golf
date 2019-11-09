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
#include "include\Graphics.h"
#include "include\Rectangle.h"

using namespace std;

unsigned char NO_IMAGE[] = { 
66,77,246,0,0,0,0,0,0,0,118,0,0,0,40,0,0,0,16,0,0,0,16,0,0,0,1,0,4,0,0,0,0,0,128,
0,0,0,0,0,0,0,0,0,0,0,16,0,0,0,16,0,0,0,0,0,0,0,0,0,128,0,0,128,0,0,0,128,128,0,
128,0,0,0,128,0,128,0,128,128,0,0,192,192,192,0,128,128,128,0,0,0,255,0,0,255,0,
0,0,255,255,0,255,0,0,0,255,0,255,0,255,255,0,0,255,255,255,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,153,153,153,153,153,153,0,0,159,249,153,153,159,249,0,0,159,255,
153,153,255,249,0,0,153,255,249,159,255,153,0,0,153,159,255,255,249,153,0,0,153,
153,255,255,153,153,0,0,153,153,255,255,153,153,0,0,153,159,255,255,249,153,0,0,
153,255,249,159,255,153,0,0,159,255,153,153,255,249,0,0,159,249,153,153,159,249,
0,0,153,153,153,153,153,153,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };


CFileMgr<SDL_Surface> CGraphics::c_filemgr("%;%images\\;.\\;images\\",
											[](string filename) 
											{ 
												return IMG_Load(filename.c_str()); 
											},
											[](SDL_Surface *pSurface) 
											{ 
												SDL_FreeSurface(pSurface); 
											});


/////////////////////////////////////////////////////////
// constructor

CGraphics::CGraphics(SDL_Surface* pSurface) 
{
	if (pSurface)
		m_pSurface = pSurface;
	else
		m_pSurface = SDL_LoadBMP_RW(SDL_RWFromMem(NO_IMAGE, sizeof(NO_IMAGE)), 1);
	m_ml = m_mr = 5; m_mu = m_mb = 2;
	memset(&m_curFont, 0, sizeof(m_curFont));
}

CGraphics::CGraphics(int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask)
{
	m_pSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, depth, Rmask, Gmask, Bmask, Amask);
	m_ml = m_mr = 5; m_mu = m_mb = 2;
	memset(&m_curFont, 0, sizeof(m_curFont));
}

CGraphics::CGraphics(int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask, CColor colorKey)
{
	m_pSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, depth, Rmask, Gmask, Bmask, Amask);
	SetColorKey(colorKey);
	m_ml = m_mr = 5; m_mu = m_mb = 2;
	memset(&m_curFont, 0, sizeof(m_curFont));
}

	static SDL_PixelFormat *_getVideoSurfaceFormat()
	{
		static SDL_PixelFormat stdformat = { NULL, 32, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0xff0000, 0xff00, 0xff, 0, 0, 0 };
		SDL_Surface *pVideo = SDL_GetVideoSurface();
		if (pVideo)
			return pVideo->format;
		else
			return &stdformat;
	}


CGraphics::CGraphics(int width, int height)
{
	SDL_PixelFormat* pVideoFormat = _getVideoSurfaceFormat();
	m_pSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, pVideoFormat->BitsPerPixel, pVideoFormat->Rmask, pVideoFormat->Gmask, pVideoFormat->Bmask, pVideoFormat->Amask);
	m_ml = m_mr = 5; m_mu = m_mb = 2;
	memset(&m_curFont, 0, sizeof(m_curFont));
}

CGraphics::CGraphics(int width, int height, CColor colorKey)
{
	SDL_PixelFormat* pVideoFormat = _getVideoSurfaceFormat();
	m_pSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, pVideoFormat->BitsPerPixel, pVideoFormat->Rmask, pVideoFormat->Gmask, pVideoFormat->Bmask, pVideoFormat->Amask);
	SetColorKey(colorKey);
	m_ml = m_mr = 5; m_mu = m_mb = 2;
	memset(&m_curFont, 0, sizeof(m_curFont));
}

CGraphics::CGraphics(string sFileName)
{
	SDL_Surface *pSurface = c_filemgr.Load(sFileName);
	if (pSurface)
	{
		m_pSurface = SDL_ConvertSurface(pSurface, pSurface->format, pSurface->flags);
		//if (m_pSurface->format->BitsPerPixel == 24)
		//{
		//	SDL_Surface *pBlit = SDL_CreateRGBSurface(SDL_SWSURFACE, m_pSurface->w, m_pSurface->h, 32, m_pSurface->format->Rmask, m_pSurface->format->Gmask, m_pSurface->format->Bmask, m_pSurface->format->Amask /*| 0xFF000000*/);
		//	SDL_BlitSurface(m_pSurface, NULL, pBlit, NULL);
		//	SDL_FreeSurface(m_pSurface);
		//	m_pSurface = pBlit;
		//}
	}
	else
		m_pSurface = SDL_LoadBMP_RW(SDL_RWFromMem(NO_IMAGE, sizeof(NO_IMAGE)), 1);

	m_ml = m_mr = 5; m_mu = m_mb = 2;
	memset(&m_curFont, 0, sizeof(m_curFont));
}

CGraphics::CGraphics(string sFileName, CColor colorKey)
{
	SDL_Surface *pSurface = c_filemgr.Load(sFileName);
	if (pSurface)
	{
		m_pSurface = SDL_ConvertSurface(pSurface, pSurface->format, pSurface->flags);
		if (m_pSurface->format->BitsPerPixel == 24)
		{
			SDL_Surface *pBlit = SDL_CreateRGBSurface(SDL_SWSURFACE, m_pSurface->w, m_pSurface->h, 32, m_pSurface->format->Rmask, m_pSurface->format->Gmask, m_pSurface->format->Bmask, m_pSurface->format->Amask);
			SDL_BlitSurface(m_pSurface, NULL, pBlit, NULL);
			SDL_FreeSurface(m_pSurface);
			m_pSurface = pBlit;
		}
	}
	else
		m_pSurface = SDL_LoadBMP_RW(SDL_RWFromMem(NO_IMAGE, sizeof(NO_IMAGE)), 1);

	SetColorKey(colorKey);
	m_ml = m_mr = 5; m_mu = m_mb = 2;
	memset(&m_curFont, 0, sizeof(m_curFont));
}

CGraphics::CGraphics(CGraphics &g)
{
	m_pSurface = SDL_ConvertSurface(g.GetSurface(), g.GetSurface()->format, g.GetSurface()->flags);
	
	m_ml = m_mr = 5; m_mu = m_mb = 2;
	memset(&m_curFont, 0, sizeof(m_curFont));
}

CGraphics::CGraphics(CGraphics *pG)
{
	if (pG)
		m_pSurface = SDL_ConvertSurface(pG->GetSurface(), pG->GetSurface()->format, pG->GetSurface()->flags);
	else
		m_pSurface = SDL_LoadBMP_RW(SDL_RWFromMem(NO_IMAGE, sizeof(NO_IMAGE)), 1);
	
	m_ml = m_mr = 5; m_mu = m_mb = 2;
	memset(&m_curFont, 0, sizeof(m_curFont));
}

CGraphics::CGraphics(CGraphics *pG, CColor colorKey)
{
	if (pG)
		m_pSurface = SDL_ConvertSurface(pG->GetSurface(), pG->GetSurface()->format, pG->GetSurface()->flags);
	else
		m_pSurface = SDL_LoadBMP_RW(SDL_RWFromMem(NO_IMAGE, sizeof(NO_IMAGE)), 1);
	
	SetColorKey(colorKey);
	m_ml = m_mr = 5; m_mu = m_mb = 2;
	memset(&m_curFont, 0, sizeof(m_curFont));
}

CGraphics::CGraphics(CGraphics *p, CRectangle rect)
{
	SDL_PixelFormat* pVideoFormat = _getVideoSurfaceFormat();
	m_pSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, rect.w, rect.h, pVideoFormat->BitsPerPixel, pVideoFormat->Rmask, pVideoFormat->Gmask, pVideoFormat->Bmask, pVideoFormat->Amask);
	SDL_BlitSurface(p->GetSurface(), &CRectangle(rect.x, rect.y, rect.w, rect.h).YInv(p->GetHeight()), GetSurface(), &CRectangle(0, 0, rect.w, rect.h).YInv(GetHeight()));

	m_ml = m_mr = 5; m_mu = m_mb = 2;
	memset(&m_curFont, 0, sizeof(m_curFont));
}

CGraphics::CGraphics(string sFileName, CRectangle rect)
{
	SDL_Surface *pFileSurface = c_filemgr.Load(sFileName);
	if (pFileSurface)
	{
		SDL_PixelFormat* pVideoFormat = _getVideoSurfaceFormat();
		m_pSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, rect.w, rect.h, pVideoFormat->BitsPerPixel, pVideoFormat->Rmask, pVideoFormat->Gmask, pVideoFormat->Bmask, pVideoFormat->Amask);
		SDL_BlitSurface(pFileSurface, &CRectangle(rect.x, rect.y, rect.w, rect.h).YInv(pFileSurface->h), GetSurface(), &CRectangle(0, 0, rect.w, rect.h).YInv(GetHeight()));
	}
	else
		m_pSurface = SDL_LoadBMP_RW(SDL_RWFromMem(NO_IMAGE, sizeof(NO_IMAGE)), 1);

	m_ml = m_mr = 5; m_mu = m_mb = 2;
	memset(&m_curFont, 0, sizeof(m_curFont));
}

CGraphics::CGraphics(CGraphics *p, CRectangle rect, CColor colorKey)
{
	SDL_PixelFormat* pVideoFormat = _getVideoSurfaceFormat();
	m_pSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, rect.w, rect.h, pVideoFormat->BitsPerPixel, pVideoFormat->Rmask, pVideoFormat->Gmask, pVideoFormat->Bmask, pVideoFormat->Amask);
	SDL_BlitSurface(p->GetSurface(), &CRectangle(rect.x, rect.y, rect.w, rect.h).YInv(p->GetHeight()), GetSurface(), &CRectangle(0, 0, rect.w, rect.h).YInv(GetHeight()));

	SetColorKey(colorKey);
	m_ml = m_mr = 5; m_mu = m_mb = 2;
	memset(&m_curFont, 0, sizeof(m_curFont));
}

CGraphics::CGraphics(string sFileName, CRectangle rect, CColor colorKey)
{
	SDL_Surface *pFileSurface = c_filemgr.Load(sFileName);
	if (pFileSurface)
	{
		SDL_PixelFormat* pVideoFormat = _getVideoSurfaceFormat();
		m_pSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, rect.w, rect.h, pVideoFormat->BitsPerPixel, pVideoFormat->Rmask, pVideoFormat->Gmask, pVideoFormat->Bmask, pVideoFormat->Amask);
		SDL_BlitSurface(pFileSurface, &CRectangle(rect.x, rect.y, rect.w, rect.h).YInv(pFileSurface->h), GetSurface(), &CRectangle(0, 0, rect.w, rect.h).YInv(GetHeight()));
	}
	else
		m_pSurface = SDL_LoadBMP_RW(SDL_RWFromMem(NO_IMAGE, sizeof(NO_IMAGE)), 1);

	SetColorKey(colorKey);
	m_ml = m_mr = 5; m_mu = m_mb = 2;
	memset(&m_curFont, 0, sizeof(m_curFont));
}

CGraphics::CGraphics(CGraphics *p, short numCols, short numRows, short iCol, short iRow)
{
	int width = p->GetWidth() / numCols;
	int height = p->GetHeight() / numRows;

	SDL_PixelFormat* pVideoFormat = _getVideoSurfaceFormat();
	m_pSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, pVideoFormat->BitsPerPixel, pVideoFormat->Rmask, pVideoFormat->Gmask, pVideoFormat->Bmask, pVideoFormat->Amask);
	SDL_BlitSurface(p->GetSurface(), &CRectangle(iCol * width, iRow * height, width, height).YInv(p->GetHeight()), GetSurface(), &CRectangle(0, 0, width, height).YInv(GetHeight()));

	m_ml = m_mr = 5; m_mu = m_mb = 2;
	memset(&m_curFont, 0, sizeof(m_curFont));
}

CGraphics::CGraphics(string sFileName, short numCols, short numRows, short iCol, short iRow)
{
	SDL_Surface *pFileSurface = c_filemgr.Load(sFileName);

	if (pFileSurface)
	{
		int width = pFileSurface->w / numCols;
		int height = pFileSurface->h / numRows;

		SDL_PixelFormat* pVideoFormat = _getVideoSurfaceFormat();
		m_pSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, pVideoFormat->BitsPerPixel, pVideoFormat->Rmask, pVideoFormat->Gmask, pVideoFormat->Bmask, pVideoFormat->Amask);
		SDL_BlitSurface(pFileSurface, &CRectangle(iCol * width, iRow * height, width, height).YInv(pFileSurface->h), GetSurface(), &CRectangle(0, 0, width, height).YInv(GetHeight()));
	}
	else
		m_pSurface = SDL_LoadBMP_RW(SDL_RWFromMem(NO_IMAGE, sizeof(NO_IMAGE)), 1);

	m_ml = m_mr = 5; m_mu = m_mb = 2;
	memset(&m_curFont, 0, sizeof(m_curFont));
}

CGraphics::CGraphics(CGraphics *p, short numCols, short numRows, short iCol, short iRow, CColor colorKey)
{
	int width = p->GetWidth() / numCols;
	int height = p->GetHeight() / numRows;

	SDL_PixelFormat* pVideoFormat = _getVideoSurfaceFormat();
	m_pSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, pVideoFormat->BitsPerPixel, pVideoFormat->Rmask, pVideoFormat->Gmask, pVideoFormat->Bmask, pVideoFormat->Amask);
	SDL_BlitSurface(p->GetSurface(), &CRectangle(iCol * width, iRow * height, width, height).YInv(p->GetHeight()), GetSurface(), &CRectangle(0, 0, width, height).YInv(GetHeight()));

	SetColorKey(colorKey);
	m_ml = m_mr = 5; m_mu = m_mb = 2;
	memset(&m_curFont, 0, sizeof(m_curFont));
}

CGraphics::CGraphics(string sFileName, short numCols, short numRows, short iCol, short iRow, CColor colorKey)
{
	SDL_Surface *pFileSurface = c_filemgr.Load(sFileName);

	if (pFileSurface)
	{
		int width = pFileSurface->w / numCols;
		int height = pFileSurface->h / numRows;

		SDL_PixelFormat* pVideoFormat = _getVideoSurfaceFormat();
		m_pSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, pVideoFormat->BitsPerPixel, pVideoFormat->Rmask, pVideoFormat->Gmask, pVideoFormat->Bmask, pVideoFormat->Amask);
		SDL_BlitSurface(pFileSurface, &CRectangle(iCol * width, iRow * height, width, height).YInv(pFileSurface->h), GetSurface(), &CRectangle(0, 0, width, height).YInv(GetHeight()));
	}
	else
		m_pSurface = SDL_LoadBMP_RW(SDL_RWFromMem(NO_IMAGE, sizeof(NO_IMAGE)), 1);

	SetColorKey(colorKey);
	m_ml = m_mr = 5; m_mu = m_mb = 2;
	memset(&m_curFont, 0, sizeof(m_curFont));
}

/////////////////////////////////////////////////////////
// CGraphicsFragment

CGraphics::~CGraphics() 
{
	for (map<string, FONT>::iterator i = m_fonts.begin(); i != m_fonts.end(); i++)
		TTF_CloseFont((*i).second.pFont);
	if (GetSurface())
	{
		SDL_FreeSurface(GetSurface());
		m_pSurface = NULL;
	}
}

/////////////////////////////////////////////////////////
// Match color with the closest

CColor CGraphics::MatchColor(CColor color) 
{
	//convert it to the pixel format
	Uint32 col = SDL_MapRGB(GetSurface()->format, color.R(), color.G(), color.B());

	//convert it from the pixel format
	SDL_GetRGB(col, GetSurface()->format, &color.R(), &color.G(), &color.B());

	//return the matched color
	return (color);
}

/////////////////////////////////////////////////////////
// Color Key (Trasnparent Color)

bool CGraphics::SetColorKey(CColor& color) 
{
	Uint32 col = SDL_MapRGB(GetSurface()->format, color.R(), color.G(), color.B());
	return (SDL_SetColorKey(GetSurface(), SDL_SRCCOLORKEY, col) == 0);
}

bool CGraphics::IsColorKeySet()
{
	return (m_pSurface->flags & SDL_SRCCOLORKEY) != 0;
}

CColor CGraphics::GetColorKey() 
{
	Uint32 col = GetSurface()->format->colorkey;
	CColor color;
	SDL_GetRGB(col, GetSurface()->format, &color.R(), &color.G(), &color.B());
	return (color);
}

bool CGraphics::ClearColorKey() 
{
	return (SDL_SetColorKey(GetSurface(), 0, 0) == 0);
}

/////////////////////////////////////////////////////////
// Flip Function

bool CGraphics::Flip() 
{
	return (SDL_Flip(GetSurface()) == 0);
}

/////////////////////////////////////////////////////////
// lock and unlock (for direct pixel access)

bool CGraphics::Lock() 
{
	if (!SDL_MUSTLOCK(GetSurface()))
		return true;
	return (SDL_LockSurface(GetSurface()) == 0);
}

void CGraphics::Unlock() 
{
	if (SDL_MUSTLOCK(GetSurface())) 
		SDL_UnlockSurface(GetSurface());
}


/////////////////////////////////////////////////////////
// Drawing Functions

CColor CGraphics::GetPixel(int x, int y) 
{
	Uint32 color = 0;
	int position = (GetHeight() - y - 1) * GetSurface()->pitch + GetSurface()->format->BytesPerPixel * x;
	char* buffer =(char*) GetSurface()->pixels;
	buffer += position;
	Lock();
	memcpy(&color, buffer, GetSurface()->format->BytesPerPixel);
	Unlock();
	CColor col;
	SDL_GetRGB(color, GetSurface()->format, &col.R(), &col.G(), &col.B());
	return (col);
}

void CGraphics::SetPixel(int x, int y, CColor& color) 
{
	int position = (GetHeight() - y - 1) * GetSurface()->pitch + GetSurface()->format->BytesPerPixel * x;
	char* buffer =(char*) GetSurface()->pixels;
	buffer += position;
	Uint32 col = SDL_MapRGB(GetSurface()->format, color.R(), color.G(), color.B());
	Lock();
	memcpy(buffer, &col, GetSurface()->format->BytesPerPixel);
	Unlock();
}

bool CGraphics::FillRect(CRectangle& rect, CColor& color) 
{
	Uint32 col = SDL_MapRGB(GetSurface()->format, color.R(), color.G(), color.B());
	return (SDL_FillRect(GetSurface(), &rect.YInv(GetHeight()), col) == 0);
}

bool CGraphics::Clear(CColor& clr) 
{
	m_ss.flags(ios::dec | ios::skipws | ios::left);
	m_ss.precision(6);
	m_ss.width(0);
	m_ss.str("");

	*this << margins() << font("arial.ttf", 18) << color(CColor::Black()) << top << left;

	Uint32 col = SDL_MapRGB(GetSurface()->format, clr.R(), clr.G(), clr.B());
	return (SDL_FillRect(GetSurface(), NULL, col) == 0);
}

bool CGraphics::Blit(CRectangle& rectDest, CGraphics& Src, CRectangle& rectSrc) 
{
	return (SDL_BlitSurface(Src.GetSurface(), &rectSrc.YInv(Src.GetHeight()), GetSurface(), &rectDest.YInv(GetHeight())) == 0);
}

bool CGraphics::Blit(CRectangle& rectDest, CGraphics& Src)
{
	return Blit(rectDest, Src, CRectangle(0, 0, Src.GetWidth(), Src.GetHeight()));
}

bool CGraphics::Blit(CVectorI ptDest, CGraphics& Src, CRectangle& rectSrc)
{
	CRectangle rect(ptDest.GetX(), ptDest.GetY(), rectSrc.w, rectSrc.h);
	return Blit(rect, Src, rectSrc);
}

bool CGraphics::Blit(CVectorI ptDest, CGraphics& Src)
{
	return Blit(CRectangle(ptDest.GetX(), ptDest.GetY(), Src.GetWidth(), Src.GetHeight()), Src, CRectangle(0, 0, Src.GetWidth(), Src.GetHeight()));
}

void CGraphics::DrawHLine(CVectorI pt1, Sint16 x2, CColor& color)
{
	hlineRGBA(GetSurface(), pt1.GetX(), x2, GetHeight() - pt1.GetY() - 1, color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void CGraphics::DrawVLine(CVectorI pt1, Sint16 y2, CColor& color)
{
	vlineRGBA(GetSurface(), pt1.GetX(), GetHeight() - pt1.GetY() - 1, GetHeight() - y2 - 1, color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void CGraphics::DrawLine(CVectorI pt1, CVectorI pt2, CColor& color)
{
	lineRGBA(GetSurface(), pt1.GetX(), GetHeight() - pt1.GetY() - 1, pt2.GetX(), GetHeight() - pt2.GetY() - 1, color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void CGraphics::DrawLine(CVectorI pt1, CVectorI pt2, Uint8 width, CColor& color)
{
	thickLineRGBA(GetSurface(), pt1.GetX(), GetHeight() - pt1.GetY() - 1, pt2.GetX(), GetHeight() - pt2.GetY() - 1, width, color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void CGraphics::DrawRect(CRectangle& rect, CColor& color)
{
	rectangleRGBA(GetSurface(), rect.Left(), GetHeight() - rect.Top(), rect.Right(), GetHeight() - rect.Bottom(), color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void CGraphics::DrawRect(CRectangle& rect, CColor& color, Sint16 rad)
{
	roundedRectangleRGBA(GetSurface(), rect.Left(), GetHeight() - rect.Top(), rect.Right(), GetHeight() - rect.Bottom(), rad, color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void CGraphics::FillRect(CRectangle& rect, CColor& color, Sint16 rad)
{
	roundedBoxRGBA(GetSurface(), rect.Left(), GetHeight() - rect.Top(), rect.Right(), GetHeight() - rect.Bottom(), rad, color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void CGraphics::DrawOval(CRectangle& rect, CColor& color)
{
	ellipseRGBA(GetSurface(), rect.GetCenterX(), GetHeight() - rect.GetCenterY(), rect.w/2, rect.h/2, color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void CGraphics::FillOval(CRectangle& rect, CColor& color)
{
	filledEllipseRGBA(GetSurface(), rect.GetCenterX(), GetHeight() - rect.GetCenterY(), rect.w/2, rect.h/2, color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void CGraphics::DrawCircle(CVectorI pt, Uint16 radius, CColor& color)
{
	circleRGBA(GetSurface(), pt.GetX(), GetHeight() - pt.GetY(), radius, color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void CGraphics::FillCircle(CVectorI pt, Uint16 radius, CColor& color)
{
	filledCircleRGBA(GetSurface(), pt.GetX(), GetHeight() - pt.GetY(), radius, color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void CGraphics::DrawPie(CVectorI pt, Uint16 radius, Uint16 angleStart, Uint16 angleEnd, CColor& color)
{
	pieRGBA(GetSurface(), pt.GetX(), GetHeight() - pt.GetY(), radius, angleStart-90, angleEnd-90, color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void CGraphics::FillPie(CVectorI pt, Uint16 radius, Uint16 angleStart, Uint16 angleEnd, CColor& color)
{
	filledPieRGBA(GetSurface(), pt.GetX(), GetHeight() - pt.GetY(), radius, angleStart-90, angleEnd-90, color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void CGraphics::DrawTriangle(CVectorI pt1, CVectorI pt2, CVectorI pt3, CColor& color)
{
	trigonRGBA(GetSurface(), pt1.GetX(), GetHeight() - pt1.GetY(), pt2.GetX(), GetHeight() - pt2.GetY(), pt3.GetX(), GetHeight() - pt3.GetY(), color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void CGraphics::FillTriangle(CVectorI pt1, CVectorI pt2, CVectorI pt3, CColor& color)
{
	filledTrigonRGBA(GetSurface(), pt1.GetX(), GetHeight() - pt1.GetY(), pt2.GetX(), GetHeight() - pt2.GetY(), pt3.GetX(), GetHeight() - pt3.GetY(), color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void CGraphics::DrawPolyLine(CVectorI pts[], Uint16 num, CColor& color)
{
	if (num >= 2)
		for (int i = 0; i < num-1; i++)
			DrawLine(pts[i], pts[i+1], color);
}

void CGraphics::DrawPolygon(CVectorI pts[], Uint16 num, CColor& color)
{
	Sint16 *xs = new Sint16[num];
	Sint16 *ys = new Sint16[num];
	for (int i = 0; i < num; i++)
	{
		xs[i] = pts[i].GetX(); 
		ys[i] = GetHeight() - pts[i].GetY(); 
	}
	polygonRGBA(GetSurface(), xs, ys, num, color.GetR(), color.GetG(), color.GetB(), color.GetA());
	delete [] xs;
	delete [] ys;
}

void CGraphics::FillPolygon(CVectorI pts[], Uint16 num, CColor& color)
{
	Sint16 *xs = new Sint16[num];
	Sint16 *ys = new Sint16[num];
	for (int i = 0; i < num; i++)
	{
		xs[i] = pts[i].GetX(); 
		ys[i] = GetHeight() - pts[i].GetY(); 
	}
	filledPolygonRGBA(GetSurface(), xs, ys, num, color.GetR(), color.GetG(), color.GetB(), color.GetA());
	delete [] xs;
	delete [] ys;
}

void CGraphics::DrawBezierLine(CVectorI pts[], Uint16 num, Uint16 nSteps, CColor& color)
{
	Sint16 *xs = new Sint16[num];
	Sint16 *ys = new Sint16[num];
	for (int i = 0; i < num; i++)
	{
		xs[i] = pts[i].GetX(); 
		ys[i] = GetHeight() - pts[i].GetY(); 
	}
	bezierRGBA(GetSurface(), xs, ys, num, nSteps, color.GetR(), color.GetG(), color.GetB(), color.GetA());
	delete [] xs;
	delete [] ys;
}

/////////////////////////////////////////////////////////
// Text Drawing Functions

#pragma warning (disable:4996)
void CGraphics::SetFont(string file, int nPtSize)
{
	if (nPtSize == 0) nPtSize = m_curFont.s;
	if (nPtSize == 0) nPtSize = 18;

	stringstream s;
	s << file << "." << nPtSize;
	string label = s.str();

	m_y += m_curFont.l;

	m_curFontFile = file;
	if (m_fonts.find(label) != m_fonts.end())
		m_curFont = m_fonts[label];
	else
	{
		m_curFont.pFont = TTF_OpenFont(c_filemgr.FindPathStr(m_curFontFile).c_str(), nPtSize);
		m_curFont.s = nPtSize;
		m_curFont.h = TTF_FontHeight(m_curFont.pFont);
		m_curFont.w = m_curFont.h;
		m_curFont.a = TTF_FontAscent(m_curFont.pFont);
		m_curFont.d = TTF_FontDescent(m_curFont.pFont);
		m_curFont.l = TTF_FontLineSkip(m_curFont.pFont);
		m_fonts[label] = m_curFont;
	}

	m_y -= m_curFont.l;
}

void CGraphics::SetFont(int nPtSize)
{
	if (m_curFontFile.empty())
		m_curFontFile = "arial.ttf";
	SetFont(m_curFontFile, nPtSize);
}

CGraphics *CGraphics::GetTextGraphics(string pText)
{
	if (!m_curFont.pFont)
		SetFont(0);
	if (m_curFont.pFont)
		return new CGraphics(TTF_RenderText_Blended(m_curFont.pFont, pText.c_str(), m_textColor));
	else
		return NULL;
}

Sint16 CGraphics::DrawText(CVectorI pt, string pText)
{
	ios::fmtflags fl = m_ss.flags() & ios::adjustfield;
	if (fl == ios::left)
		return DrawTextLt(pt, pText);
	else if (fl == ios::right)
		return DrawTextRt(pt, pText);
	else
		return DrawTextCt(pt, pText);
}

Sint16 CGraphics::DrawTextLt(CVectorI pt, string pText)
{
	CGraphics *pG;
	if (pText.length() && (pG = GetTextGraphics(pText)))
	{
		Sint16 w = pG->GetWidth();
		Blit(pt, *pG);
		delete pG;
		return w;
	}
	return 0;
}

Sint16 CGraphics::DrawTextCt(CVectorI pt, string pText)
{
	CGraphics *pG;
	if (pText.length() && (pG = GetTextGraphics(pText)))
	{
		Sint16 w = pG->GetWidth() / 2;
		pt.X() -= w;
		Blit(pt, *pG);
		delete pG;
		return w;
	}
	return 0;
}

Sint16 CGraphics::DrawTextRt(CVectorI pt, string pText)
{
	CGraphics *pG;
	if (pText.length() && (pG = GetTextGraphics(pText)))
	{
		pt.X() -= pG->GetWidth();
		Blit(pt, *pG);
		delete pG;
	}
	return 0;
}

void CGraphics::Flush()
{
	if (m_ss.eof()) return;

	string str;

	getline(m_ss, str);
	m_x += DrawText(CVectorI(m_x, m_y), str);
	while (!m_ss.eof())
	{
		GotoLn(); 
		getline(m_ss, str);
		m_x += DrawText(CVectorI(m_x, m_y), str);
	}
	m_ss.clear();
	m_ss.str("");
}

CGraphics &CGraphics::_DrawText()
{
	ios::fmtflags fl = m_ss.flags() & ios::adjustfield;
	if (fl == ios::left)
		Flush();
	else
	{
		// special flush - up to the most recent eol
		if (m_ss.eof()) return *this;

		string str = m_ss.str();
		if (str.find('\n') == string::npos) return *this;	// no eol

		getline(m_ss, str);
		m_x += DrawText(CVectorI(m_x, m_y), str);
		while (!m_ss.eof())
		{
			GotoLn(); 
			getline(m_ss, str);
			
			if (str.size() && m_ss.eof())
			{
				m_ss.clear();
				m_ss.str();
				m_ss << str;
				return *this;
			}
			else
				m_x += DrawText(CVectorI(m_x, m_y), str);
		}
		m_ss.clear();
		m_ss.str("");
	}
	return *this;
}

CGraphics &CGraphics::_DrawText(ostream&(*f)(ostream&))
{
	m_ss << f;
	if (f == endl || f == flush)
		Flush();
	return *this;
}

CGraphics &CGraphics::_DrawText(ios_base& (__cdecl *f)(ios_base&))
{
	// output f, monitoring adjustfield flags
	ios::fmtflags fl1 = m_ss.flags() & ios::adjustfield;
	m_ss << f;
	ios::fmtflags fl2 = m_ss.flags() & ios::adjustfield;
	
	// if adjustfield flags changed
	if (fl1 != fl2)
	{	// undo; flush; redo & init
		m_ss.setf(fl1, ios::adjustfield);
		Flush();
		m_ss.setf(fl2, ios::adjustfield);
		GotoCol();
	}
	return *this;
}

///////////////////////////////////////////////////////////
// NOT SUPPORTED CODE

///////////////////////////////////////////////////////////
//// Update Region Functions
//
//// Declared in the class definition:
//// list <SDL_Rect*> m_lstUpdateRects;		// a list of update rectangles
//
//void CGraphics::AddUpdateRect(CRectangle& UpdateRect) 
//{
//	SDL_Rect* pRect = NULL;
//	pRect = new SDL_Rect;
//	*pRect = UpdateRect;
//	m_lstUpdateRects.push_back(pRect);
//}
//
//void CGraphics::ClearUpdateRects() 
//{
//	list < SDL_Rect* >::iterator iter;
//	SDL_Rect* pRect;
//	while(!m_lstUpdateRects.empty())
//	{
//		iter = m_lstUpdateRects.begin();
//		pRect = *iter;
//		m_lstUpdateRects.erase(iter);
//		if (pRect) delete pRect;
//	}
//}
//
//void CGraphics::UpdateRects() 
//{
//	list <SDL_Rect*>::iterator iter;
//	for(iter = m_lstUpdateRects.begin(); iter != m_lstUpdateRects.end(); iter ++)
//		note: Y not yet inverted in this function!
//		SDL_UpdateRect(GetSurface(), (*iter)->x, (*iter)->y, (*iter)->w, (*iter)->h);
//	ClearUpdateRects();
//}
//
///////////////////////////////////////////////////////////
//// Clipping Rectangle
//
//void CGraphics::SetClipRect(CRectangle* pRect) 
//{
//	if (pRect)
//		SDL_SetClipRect(GetSurface(), pRect->YInv(GetHeight()));
//	else
//		SDL_SetClipRect(GetSurface(), NULL);
//}
//
//CRectangle CGraphics::GetClipRect() 
//{
//	SDL_Rect rect;
//	SDL_GetClipRect(GetSurface(), &rect);
//	rect.y = GetHeight() - rect.y - rect.h;
//	return (rect);
//}

