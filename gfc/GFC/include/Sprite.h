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

#include "Vector.h"
#include "Rectangle.h"
#include "Color.h"
#include "Property.h"
#include <list>
#include <map>
#include <vector>
#include <string>

class CGraphics;

class EXT_DECL CSprite
{
public:
	
	//////////////////////////////////////////
	// Constructors & Destructor

	// Parameters:
	// rect	- bounding rectangle
	// v	- pivot point, in the centre of the bounding rectangle
	// x, y	- pivot point, as above
	// w, h	- width and height
	// pFileBitmap - initial image file to load, may determine the size of the object
	// pGraphics - initial image to use, may determine the size of the object
	// colorKey    - sets colour key (alpha or transparent colour)
	// time	- current game time

	CSprite();

	CSprite(CVector v, float w, float h, Uint32 time);
	CSprite(CVector v, float w, float h, char *pFileBitmap, Uint32 time);
	CSprite(CVector v, float w, float h, char *pFileBitmap, CColor colorKey, Uint32 time);
	CSprite(CVector v, char *pFileBitmap, Uint32 time);
	CSprite(CVector v, char *pFileBitmap, CColor colorKey, Uint32 time);
	CSprite(CVector v, float w, float h, CGraphics *pGraphics, Uint32 time);
	CSprite(CVector v, float w, float h, CGraphics *pGraphics, CColor colorKey, Uint32 time);
	CSprite(CVector v, CGraphics *pGraphics, Uint32 time);
	CSprite(CVector v, CGraphics *pGraphics, CColor colorKey, Uint32 time);

	CSprite(float x, float y, float w, float h, Uint32 time);
	CSprite(float x, float y, float w, float h, char *pFileBitmap, Uint32 time);
	CSprite(float x, float y, float w, float h, char *pFileBitmap, CColor colorKey, Uint32 time);
	CSprite(float x, float y, char *pFileBitmap, Uint32 time);
	CSprite(float x, float y, char *pFileBitmap, CColor colorKey, Uint32 time);
	CSprite(float x, float y, float w, float h, CGraphics *pGraphics, Uint32 time);
	CSprite(float x, float y, float w, float h, CGraphics *pGraphics, CColor colorKey, Uint32 time);
	CSprite(float x, float y, CGraphics *pGraphics, Uint32 time);
	CSprite(float x, float y, CGraphics *pGraphics, CColor colorKey, Uint32 time);

	CSprite(CRectangle r, Uint32 time);
	CSprite(CRectangle r, char *pFileBitmap, Uint32 time);
	CSprite(CRectangle r, char *pFileBitmap, CColor colorKey, Uint32 time);
	CSprite(CRectangle r, CGraphics *pGraphics, Uint32 time);
	CSprite(CRectangle r, CGraphics *pGraphics, CColor colorKey, Uint32 time);

	virtual ~CSprite();

	//////////////////////////////////////////
	// Attributes

private:
	void _local_init(float x, float y, float w, float h, Uint32 time);		// constructor helper function

	// Position & Size
	CVector m_pos;			// position of the pivot point of the sprite 
	CVector m_pt1;			// coordinates of the bottom-left corner relative to the pivot point
	CVector m_pt2;			// coordinates of the top-right corner relative to the pivot point

	// Drawing State
	bool m_bValid;			// if set to false then re-draw is needed

	// Properties
	std::map<std::string, PROPERTY> m_properties;

	// Time
	Uint32 m_time;			// reference time
	
	// Internal State (User-Defined)
	Sint32 m_state;			// state (user defined)

	// Animation Phases
	CGraphics **m_pFrames;	// animation frames (pointers to CGraphics bitmaps)
	int m_nFrames;			// number of animation frames
	int m_nFramePeriod;		// period of a single animation frame [msec]
	long m_nFrameTime;		// reference time for animation: current frame index = ((GetTime() - m_nFrameTime) / m_nFramePeriod) % m_nFrames
	bool m_bFrameChangeSize;// if true, changes the sprite's size accordingly to the size of frame bitmap
	
	// Dynamics - Linear
	CVector m_v;			// normalised velocity (direction)
	float m_fv;				// speed (scalar)
	
	float m_m;				// mass

	// Dynamics - Rotational
	float m_rot;			// rotation
	float m_sinrot;			// rotation sin
	float m_cosrot;			// rotation cos
	float m_omega;			// rotational speed

	// Deleted flag
	bool m_bDeleted;;

protected:
	CGraphics *m_pGraphics;	// graphics cache (no rotation)
	CGraphics *m_pRoto;		// graphics cache (for rotated image)

public:

	//////////////////////////////////////////
	// Position of the Sprite

	// Position of the sprite is the position of the Pivot Point (the geometrical centre by default)
	CVector GetPos()							{ return m_pos; }
	void SetPos(CVector v)						{ m_pos = v; }
	void SetPos(float x, float y)				{ SetPosition(CVector(x, y)); }

	CVector GetPosition()						{ return m_pos; }
	void SetPosition(CVector v)					{ m_pos = v; }
	void SetPosition(float x, float y)			{ SetPosition(CVector(x, y)); }

	void Move(CVector v)						{ m_pos += v; }
	void Move(float dx, float dy)				{ Move(CVector(dx, dy)); }

	// Various coordinates - global (no rotations taken into account)
	float GetX()								{ return m_pos.m_x; }
	float GetY()								{ return m_pos.m_y; }
	CVector GetBottomLeft()						{ return GetPos() + GetBottomLeftLocal(); }
	float GetLeft()								{ return GetX() + GetLeftLocal(); }
	float GetBottom()							{ return GetY() + GetBottomLocal(); }
	CVector GetTopRight()						{ return GetPos() + GetTopRightLocal(); }
	float GetRight()							{ return GetX() + GetRightLocal(); }
	float GetTop()								{ return GetY() + GetTopLocal(); }

	void SetX(float x)							{ m_pos.m_x = x; }
	void SetY(float y)							{ m_pos.m_y = y; }

	void SetBottomLeft(CVector v)				{ SetBottomLeftLocal(v - GetPos()); }
	void SetLeft(float x)						{ SetLeftLocal(x - GetX()); }
	void SetBottom(float y)						{ SetBottomLocal(y - GetY()); }
	void SetTopRight(CVector v)					{ SetTopRightLocal(v - GetPos()); }
	void SetRight(float x)						{ SetRightLocal(x - GetX()); }
	void SetTop(float y)						{ SetTopLocal(y - GetY()); }

	// Local Coordinates of the sides (relative to the Pivot Point)
	CVector GetBottomLeftLocal()				{ return m_pt1; }
	float GetLeftLocal()						{ return m_pt1.m_x; }
	float GetBottomLocal()						{ return m_pt1.m_y; }
	CVector GetTopRightLocal()					{ return m_pt2; }
	float GetRightLocal()						{ return m_pt2.m_x; }
	float GetTopLocal()							{ return m_pt2.m_y; }
	
	void SetBottomLeftLocal(CVector v)			{ m_pt1 = v; }
	void SetLeftLocal(float x1)					{ m_pt1.m_x = x1; }
	void SetBottomLocal(float y1)				{ m_pt1.m_y = y1; }
	void SetTopRightLocal(CVector v)			{ m_pt2 = v; }
	void SetRightLocal(float x2)				{ m_pt2.m_x = x2; }
	void SetTopLocal(float y2)					{ m_pt2.m_y = y2; }

	//////////////////////////////////////////
	// Size of the Sprite

	CVector GetSize()							{ return m_pt2 - m_pt1; }
	float GetWidth()							{ return m_pt2.m_x - m_pt1.m_x; }
	float GetW()								{ return m_pt2.m_x - m_pt1.m_x; }
	float GetHeight()							{ return m_pt2.m_y - m_pt1.m_y; }
	float GetH()								{ return m_pt2.m_y - m_pt1.m_y; }
	void SetSize(CVector v);
	void SetSize(float w, float h)				{ SetSize(CVector(w, h)); }

	//////////////////////////////////////////
	// Geometrical Centre

	// centre point
	CVector GetCenter()							{ CVector v = GetCenterLocal(); LtoG(v); return v; } 
	CVector GetCenterLocal()					{ return (m_pt1 + m_pt2) / 2; }

	//////////////////////////////////////////
	// Coordinate Convertors
	void GtoL(CVector &p, bool bUseRot = true);
	void LtoG(CVector &p, bool bUseRot = true);

	//////////////////////////////////////////
	// Sprite Rectangles
	
	// - Client Rectangle - has its bottom-left corner set to (0, 0) and the size set to the size of the sprite.
	// - Bounding Rectangle - the smallest rectangle to cover the whole area of the sprite in screen coordinates
	// - NoRot Bounding Rectangle - as above, ignoring any Rotations

	void GetClientRect(CRectangle &rect)		{ rect = CRectangle(0, 0, (Uint16)GetWidth(), (Uint16)GetHeight()); }
	void GetBoundingRect(CRectangle &rect);
	void GetNoRotBoundingRect(CRectangle &rect)	{ rect = CRectangle((Sint16)GetLeft(), (Sint16)GetBottom(), (Uint16)GetWidth(), (Uint16)GetHeight()); }

	//////////////////////////////////////////
	// Pivot Point
	// These functions only change the pivot location but do not move the sprite

	// Pivot Point in Global Coordinates
	void SetPivot(CVector v)					{ GtoL(v); SetPivotLocal(v); }
	void SetPivot(float x, float y)				{ SetPivot(CVector(x, y)); }

	// Pivot Point in Local Coordinates
	// Set functions effectively move the Pivot Point by the given amount
	void SetPivotLocal(CVector v);
	void SetPivotLocal(float x = 0, float y = 0){ SetPivotLocal(CVector(x, y)); }

	// Pivot Point, relative to the centre of the sprite
	CVector GetPivotFromCenter()				{ return -GetCenterLocal(); }
	void SetPivotFromCenter(CVector v)			{ SetPivotLocal(GetCenterLocal() + v); }
	void SetPivotFromCenter(float x = 0, float y = 0)	{ SetPivotFromCenter(CVector(x, y)); }

	// Pivot Point in relation to the sprite area: BottomLeft = (0.0, 0.0), Centre = (0.5, 0.5), TopRight = (1.0, 1.0)
	CVector GetPivotRel()						{ float x, y; GetPivotRel(x, y); return CVector(x, y); }
	void GetPivotRel(float &x, float &y);
	void SetPivotRel(CVector v)					{ SetPivotLocal(m_pt1 + v * (m_pt2 - m_pt1)); }
	void SetPivotRel(float x, float y)			{ SetPivotRel(CVector(x, y)); }

	/////////////////////////////////////////////////////////////////////
	// Image & Animation Functions

	// Removes the current image and clears any animation set
	void ClearImage();

	// LoadImage - load image from either a CGraphics object or a file and store it internally as alias-name. 
	// NOTE: These functions do not change the appearance of the sprite - use SetImage to set the current appearance of the sprite
	// If no alias-name is provided, the filename is re-used as the alias-name.
	// If the colorKey is provided, the image transparency is set with the color key
	// If nIndex is provided, indexed alias-name is created.
	// If rect is provided, a rectangular fragment is cut-off from the image
	// If numCols, numRows, iCol, iRow areprovided, the image is divided into numCols x numRows tiles and the tile (iCol, iRow) is cut-off from the image
	void LoadImage(CGraphics *p, char *pAliasName)													{ SetProperty(pAliasName, &CGraphics(p)); }
	void LoadImage(char *pFileName, char *pAliasName)												{ SetProperty(pAliasName, &CGraphics(pFileName)); }
	void LoadImage(char *pFileName)																	{ LoadImage(pFileName, pFileName); }
	void LoadImage(CGraphics *p, char *pAliasName, CColor colorKey)									{ SetProperty(pAliasName, &CGraphics(p, colorKey)); }
	void LoadImage(char *pFileName, char *pAliasName, CColor colorKey)								{ SetProperty(pAliasName, &CGraphics(pFileName, colorKey)); }
	void LoadImage(char *pFileName, CColor colorKey)												{ LoadImage(pFileName, pFileName, colorKey); }
	void LoadImage(CGraphics *p, char *pAliasName, int nIndex)										{ SetProperty(pAliasName, nIndex, &CGraphics(p)); }
	void LoadImage(char *pFileName, char *pAliasName, int nIndex)									{ SetProperty(pAliasName, nIndex, &CGraphics(pFileName)); }
	void LoadImage(char *pFileName, int nIndex)														{ LoadImage(pFileName, pFileName, nIndex); }
	void LoadImage(CGraphics *p, char *pAliasName, int nIndex, CColor colorKey)						{ SetProperty(pAliasName, nIndex, &CGraphics(p, colorKey)); }
	void LoadImage(char *pFileName, char *pAliasName, int nIndex, CColor colorKey)					{ SetProperty(pAliasName, nIndex, &CGraphics(pFileName, colorKey)); }
	void LoadImage(char *pFileName, int nIndex, CColor colorKey)									{ LoadImage(pFileName, pFileName, nIndex, colorKey); }

	void LoadImage(CGraphics *p, char *pAliasName, CRectangle rect)									{ SetProperty(pAliasName, &CGraphics(p, rect)); }
	void LoadImage(char *pFileName, char *pAliasName, CRectangle rect)								{ SetProperty(pAliasName, &CGraphics(pFileName, rect)); }
	void LoadImage(char *pFileName, CRectangle rect)												{ LoadImage(pFileName, pFileName, rect); }
	void LoadImage(CGraphics *p, char *pAliasName, CRectangle rect, CColor colorKey)				{ SetProperty(pAliasName, &CGraphics(p, rect, colorKey)); }
	void LoadImage(char *pFileName, char *pAliasName, CRectangle rect, CColor colorKey)				{ SetProperty(pAliasName, &CGraphics(pFileName, rect, colorKey)); }
	void LoadImage(char *pFileName, CRectangle rect, CColor colorKey)								{ LoadImage(pFileName, pFileName, rect, colorKey); }
	void LoadImage(CGraphics *p, char *pAliasName, int nIndex, CRectangle rect)						{ SetProperty(pAliasName, nIndex, &CGraphics(p, rect)); }
	void LoadImage(char *pFileName, char *pAliasName, int nIndex, CRectangle rect)					{ SetProperty(pAliasName, nIndex, &CGraphics(pFileName, rect)); }
	void LoadImage(char *pFileName, int nIndex, CRectangle rect)									{ LoadImage(pFileName, pFileName, nIndex, rect); }
	void LoadImage(CGraphics *p, char *pAliasName, int nIndex, CRectangle rect, CColor colorKey)	{ SetProperty(pAliasName, nIndex, &CGraphics(p, rect, colorKey)); }
	void LoadImage(char *pFileName, char *pAliasName, int nIndex, CRectangle rect, CColor colorKey)	{ SetProperty(pAliasName, nIndex, &CGraphics(pFileName, rect, colorKey)); }
	void LoadImage(char *pFileName, int nIndex, CRectangle rect, CColor colorKey)					{ LoadImage(pFileName, pFileName, nIndex, rect, colorKey); }

	void LoadImage(CGraphics *p, char *pAliasName, short numCols, short numRows, short iCol, short iRow)									{ SetProperty(pAliasName, &CGraphics(p, numCols, numRows, iCol, iRow)); }
	void LoadImage(char *pFileName, char *pAliasName, short numCols, short numRows, short iCol, short iRow)									{ SetProperty(pAliasName, &CGraphics(pFileName, numCols, numRows, iCol, iRow)); }
	void LoadImage(char *pFileName, short numCols, short numRows, short iCol, short iRow)													{ LoadImage(pFileName, pFileName, numCols, numRows, iCol, iRow); }
	void LoadImage(CGraphics *p, char *pAliasName, short numCols, short numRows, short iCol, short iRow, CColor colorKey)					{ SetProperty(pAliasName, &CGraphics(p, numCols, numRows, iCol, iRow, colorKey)); }
	void LoadImage(char *pFileName, char *pAliasName, short numCols, short numRows, short iCol, short iRow, CColor colorKey)				{ SetProperty(pAliasName, &CGraphics(pFileName, numCols, numRows, iCol, iRow, colorKey)); }
	void LoadImage(char *pFileName, short numCols, short numRows, short iCol, short iRow, CColor colorKey)									{ LoadImage(pFileName, pFileName, numCols, numRows, iCol, iRow, colorKey); }
	void LoadImage(CGraphics *p, char *pAliasName, int nIndex, short numCols, short numRows, short iCol, short iRow)						{ SetProperty(pAliasName, nIndex, &CGraphics(p, numCols, numRows, iCol, iRow)); }
	void LoadImage(char *pFileName, char *pAliasName, int nIndex, short numCols, short numRows, short iCol, short iRow)						{ SetProperty(pAliasName, nIndex, &CGraphics(pFileName, numCols, numRows, iCol, iRow)); }
	void LoadImage(char *pFileName, int nIndex, short numCols, short numRows, short iCol, short iRow)										{ LoadImage(pFileName, pFileName, nIndex, numCols, numRows, iCol, iRow); }
	void LoadImage(CGraphics *p, char *pAliasName, int nIndex, short numCols, short numRows, short iCol, short iRow, CColor colorKey)		{ SetProperty(pAliasName, nIndex, &CGraphics(p, numCols, numRows, iCol, iRow, colorKey)); }
	void LoadImage(char *pFileName, char *pAliasName, int nIndex, short numCols, short numRows, short iCol, short iRow, CColor colorKey)	{ SetProperty(pAliasName, nIndex, &CGraphics(pFileName, numCols, numRows, iCol, iRow, colorKey)); }
	void LoadImage(char *pFileName, int nIndex, short numCols, short numRows, short iCol, short iRow, CColor colorKey)						{ LoadImage(pFileName, pFileName, nIndex, numCols, numRows, iCol, iRow, colorKey); }

	// AddImage - load image from either a CGraphics object or a file and store it internally at the next available index at the given alias-name
	void AddImage(CGraphics *p, char *pAliasName)																			{ AddProperty(pAliasName, &CGraphics(p)); }
	void AddImage(char *pFileName, char *pAliasName)																		{ AddProperty(pAliasName, &CGraphics(pFileName)); }
	void AddImage(char *pFileName)																							{ AddImage(pFileName, pFileName); }
	void AddImage(CGraphics *p, char *pAliasName, CColor colorKey)															{ AddProperty(pAliasName, &CGraphics(p, colorKey)); }
	void AddImage(char *pFileName, char *pAliasName, CColor colorKey)														{ AddProperty(pAliasName, &CGraphics(pFileName, colorKey)); }
	void AddImage(char *pFileName, CColor colorKey)																			{ AddImage(pFileName, pFileName, colorKey); }

	void AddImage(CGraphics *p, char *pAliasName, CRectangle rect)															{ AddProperty(pAliasName, &CGraphics(p, rect)); }
	void AddImage(char *pFileName, char *pAliasName, CRectangle rect)														{ AddProperty(pAliasName, &CGraphics(pFileName, rect)); }
	void AddImage(char *pFileName, CRectangle rect)																			{ AddImage(pFileName, pFileName, rect); }
	void AddImage(CGraphics *p, char *pAliasName, CRectangle rect, CColor colorKey)											{ AddProperty(pAliasName, &CGraphics(p, rect, colorKey)); }
	void AddImage(char *pFileName, char *pAliasName, CRectangle rect, CColor colorKey)										{ AddProperty(pAliasName, &CGraphics(pFileName, rect, colorKey)); }
	void AddImage(char *pFileName, CRectangle rect, CColor colorKey)														{ AddImage(pFileName, pFileName, rect, colorKey); }

	void AddImage(CGraphics *p, char *pAliasName, short numCols, short numRows, short iCol, short iRow)						{ AddImage(p, pAliasName, numCols, numRows, iCol, iRow, iCol, iRow); }
	void AddImage(char *pFileName, char *pAliasName, short numCols, short numRows, short iCol, short iRow)					{ AddImage(pFileName, pAliasName, numCols, numRows, iCol, iRow, iCol, iRow); }
	void AddImage(char *pFileName, short numCols, short numRows, short iCol, short iRow)									{ AddImage(pFileName, pFileName, numCols, numRows, iCol, iRow); }
	void AddImage(CGraphics *p, char *pAliasName, short numCols, short numRows, short iCol, short iRow, CColor colorKey)	{ AddImage(p, pAliasName, numCols, numRows, iCol, iRow, iCol, iRow, colorKey); }
	void AddImage(char *pFileName, char *pAliasName, short numCols, short numRows, short iCol, short iRow, CColor colorKey)	{ AddImage(pFileName, pAliasName, numCols, numRows, iCol, iRow, iCol, iRow, colorKey); }
	void AddImage(char *pFileName, short numCols, short numRows, short iCol, short iRow, CColor colorKey)					{ AddImage(pFileName, pFileName, numCols, numRows, iCol, iRow, colorKey); }

	void AddImage(CGraphics *p, char *pAliasName, short numCols, short numRows, short iColFrom, short iRowFrom, short iColTo, short iRowTo, bool bHorizontally = true);
	void AddImage(char *pFileName, char *pAliasName, short numCols, short numRows, short iColFrom, short iRowFrom, short iColTo, short iRowTo, bool bHorizontally = true);
	void AddImage(char *pFileName, short numCols, short numRows, short iColFrom, short iRowFrom, short iColTo, short iRowTo, bool bHorizontally = true)						{ AddImage(pFileName, pFileName, numCols, numRows, iColFrom, iRowFrom, iColTo, iRowTo, bHorizontally); }
	void AddImage(CGraphics *p, char *pAliasName, short numCols, short numRows, short iColFrom, short iRowFrom, short iColTo, short iRowTo, CColor colorKey, bool bHorizontally = true);
	void AddImage(char *pFileName, char *pAliasName, short numCols, short numRows, short iColFrom, short iRowFrom, short iColTo, short iRowTo, CColor colorKey, bool bHorizontally = true);
	void AddImage(char *pFileName, short numCols, short numRows, short iColFrom, short iRowFrom, short iColTo, short iRowTo, CColor colorKey, bool bHorizontally = true)	{ AddImage(pFileName, pFileName, numCols, numRows, iColFrom, iRowFrom, iColTo, iRowTo, colorKey, bHorizontally); }

	// Sets the current image from either a CGraphics object
	// or a previously stored image identified by pAliasName
	void SetImage(CGraphics *p, bool bChangeSize = true);
	void SetImage(char *pImageName, bool bChangeSize = true)				{ SetImage((CGraphics*)GetProperty(pImageName), bChangeSize); }
	void SetImage(char *pImageName, int nIndex, bool bChangeSize = true)	{ SetImage((CGraphics*)GetProperty(pImageName, nIndex), bChangeSize); }

	// Set up an animation (NEW FORMAT!)
	void SetAnimation(char *pPropName, int fps = 10, int nIndexStart = 0, int numFrames = -1);
	void SetAnimationKeepSize(char *pPropName, int fps = 10, int nIndexStart = 0, int numFrames = -1);

	// These two functions are DEPRECATED and will be removed from the future versions of GFC
	void SetImageFromFile(char *pFileBitmap, bool bChangeSize = true)		{ LoadImage(pFileBitmap); SetImage(pFileBitmap, bChangeSize); }
	void SetAnimation(char *pPropName, int nIndexStart, int numFrames, int nPeriod, long nTime, bool bChangeSize = true);

	/////////////////////////////////////////////////////////////////////
	// Hit Tests

	virtual bool HitTest(CVector pt);					// point
	bool HitTest(float x, float y)						{ return HitTest(CVector(x, y)); }
	virtual bool HitTest(CVector pt, float radius);		// circular area
	bool HitTest(float x, float y, float r)				{ return HitTest(CVector(x, y), r); }
	virtual bool HitTest(CRectangle rect);				// rectangular area

	// Collision with another sprite - with pixel precision
	// nSkip skips pixels between test, high values increase efficiency but decrease accuracy, 1 for maximum accuracy, 0 to switch pixel precision off
	// Based on SDL_Collide by genjix & robloach (http://sdl-collide.sourceforge.net/)
	virtual bool HitTest(CSprite *pSprite, int nSkip = 4);

	/////////////////////////////////////////////////////////////////////
	// Deleting
	// Does not physically delete sprites, but disables their Update and Draw cycles
	// You can physically delete removed sprites from a collection by calling
	// list.remove_if(deleted) to actually remove them

	void Delete()								{ m_bDeleted = true; }
	void UnDelete()								{ m_bDeleted = false; }
	bool IsDeleted()							{ return m_bDeleted; }

	/////////////////////////////////////////////////////////////////////
	// Drawing State

	bool IsValid()								{ return m_bValid; }
	void Invalidate()							{ m_bValid = false; }
	void Validate()								{ m_bValid = true; }

	/////////////////////////////////////////////////////////////////////
	// Colour Key (Alpha Color)

	bool IsColorKeySet()						{ return m_pGraphics ? m_pGraphics->IsColorKeySet() : false; }
	CColor GetColorKey()						{ return m_pGraphics ? m_pGraphics->GetColorKey() : CColor::Black(); }
	void SetColorKey(CColor color)				{ if (m_pGraphics) m_pGraphics->SetColorKey(color); }
	void ClearColorKey()						{ if (m_pGraphics) m_pGraphics->ClearColorKey(); }
	void ResetColorKey()						{ if (m_pGraphics) m_pGraphics->ClearColorKey(); }

	//////////////////////////////////////////
	// Time
	void ResetTime(Uint32 time)					{ m_time = time; }

	//////////////////////////////////////////
	// State (User-Defined Value)
	Sint32 GetState()							{ return m_state; }
	void SetState(Sint32 state)					{ m_state = state; }

	//////////////////////////////////////////
	// Properties
	void SetProperty(char *pLabel, PROPERTY p);						// sets a named unindexed property
	void SetProperty(char *pLabel, unsigned nIndex, PROPERTY p);	// sets a named indexed property
	void AddProperty(char *pLabel, PROPERTY p);						// adds a named property at the next available index
	PROPERTY GetProperty(char *pLabel);								// gets the value of a named unindexed property
	PROPERTY GetProperty(char *pLabel, unsigned nIndex);			// gets the value of a named indexed property
	unsigned GetPropertyIndexCount(char *pLabel);					// returns the count of the indexed properties at a given name

	//////////////////////////////////////////
	// Automatic Motion: Velocity, Speed and Direction
	
	// Velocity vector
	CVector GetVelocity()						{ return m_v * m_fv; }
	void SetVelocity(CVector vec)				{ SetNormalisedVelocity(vec); SetSpeed(vec.Length()); }
	void SetVelocity(float vx, float vy)		{ SetVelocity(CVector(vx, vy)); }

	// Speed (with no directional info)
	float GetSpeed()							{ return m_fv; }
	void SetSpeed(float newV)					{ m_fv = newV; }

	// Direction angle - in which the sprite is moving - in degrees, anti-clockwise, with value of 0 pointing upwards
	float GetDirection()						{ return RAD2DEG(atan2(m_v.m_x, m_v.m_y)); }
	void SetDirection(float dir)				{ dir = DEG2RAD(dir); m_v = CVector(sin(dir), cos(dir)); } 
	
	// Normalised Velocity - determines the direction but not speed
	CVector GetNormalisedVelocity()				{ return m_v; }
	void SetNormalisedVelocity(CVector v)		{ m_v = Normalize(v); }	// tan dir = dH/dV
	void SetNormalisedVelocity(float vx, float vy)		{ SetNormalisedVelocity(CVector(vx, vy)); }

	//////////////////////////////////////////
	// Simple Dynamics

	float GetMass()								{ return m_m; }
	void SetMass(float m)						{ m_m = m; }

	void Accelerate(CVector a)					{ SetVelocity(GetVelocity() + a); }
	void Accelerate(float ax, float ay)			{ Accelerate(CVector(ax, ay)); }
	void ApplyForce(CVector f)					{ if (m_m > 0) Accelerate(f / m_m); }
	void ApplyForce(float fx, float fy)			{ ApplyForce(CVector(fx, fy)); }

	
	//////////////////////////////////////////
	// Rotation & Automatic Rotational Motion

	// rotation angle of the sprite
	float GetRotation()							{ return RAD2DEG(m_rot); }
	void SetRotation(float newRot);
	void SetRotation(float a, float b)			{ SetRotation(RAD2DEG(atan2(a, b))); }
	void Rotate(float rot)						{ SetRotation(GetRotation() + rot); }
	
	// rotational speed of the sprite
	float GetOmega()							{ return RAD2DEG(m_omega); }
	void SetOmega(float newOmega) 				{ m_omega = DEG2RAD(newOmega); }


	/////////////////////////////////////////////////////////////////////
	// Update & Draw

	// Call this function from your application
	void Update(Uint32 nGameTime);
	void Draw(CGraphics *g);

	// emulates drawing by preparing all internal structures, without the actual output
	void VoidDraw();

	/////////////////////////////////////////////////////////////////////
	// Access to the CGraphics objects

	CGraphics *GetGraphics()					{ return m_pGraphics; }
	CGraphics *GetRotoGraphics()				{ return m_pRoto ? m_pRoto : m_pGraphics; }
	
	// Deprecated function - use VoidDraw instead
	CGraphics *PrepareGraphics()				{ VoidDraw(); return GetRotoGraphics(); }


	/////////////////////////////////////////////////////////////////////
	// Overridables
	// Override these functions but NEVER call them directly
protected:

	// default update uses velocity & omega to automatically move & rotate the sprite
	// you will often want to override this function
	virtual void OnUpdate(Uint32 time, Uint32 deltaTime);

	// you will rarely need to override this
	virtual void OnPrepareGraphics(CGraphics *pG = NULL);

	// you will rarely need to override this
	// returns true if pSpriteRotoGraphics prepared here should be used instead of pSpriteGraphics
	virtual bool OnPrepareRotoGraphics(CGraphics *pG = NULL);

	// empty implementation will display the content of m_pGraphics object
	virtual void OnDraw(CGraphics *g);
};

typedef std::list<CSprite*> CSpriteList;
typedef std::list<CSprite*>::iterator CSpriteIter;
template <class T> bool deleted(T p)	{ return p->IsDeleted(); }
inline bool deleted(CSprite *p)			{ return deleted<CSprite*>(p); }

typedef std::vector<CSprite*> CSpriteVector;
