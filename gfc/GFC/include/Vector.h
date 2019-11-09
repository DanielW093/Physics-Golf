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

// CVector - a fast inline class

#ifndef __VECTOR_H__
#define __VECTOR_H__

#define TVECTOR TVector<T,U>

template <class T, class U>
class TVector
{
public:
	T m_x;
	T m_y;

public:
	// Constructor
	TVECTOR(T x, T y)						{ Set(x, y); }
	TVECTOR()								{ Set(0, 0); }
	TVECTOR(TVECTOR &pt)					{ Set(pt); }
	TVECTOR(TVector<U,T> &pt)				{ Set((T)pt.m_x, (T)pt.m_y); }

	// Destructor
	~TVECTOR()								{ }

	// Getters & Setters
	T &X()									{ return m_x; }
	T &Y()									{ return m_y; }
	T GetX() const							{ return m_x; }
	T GetY() const							{ return m_y; }

	void SetX(T x)							{ m_x = x; }
	void SetY(T y)							{ m_y = y; }
	TVECTOR &Set(T x, T y)					{ m_x = x; m_y = y; return(*this); }
	TVECTOR &Set(TVECTOR &pt)				{ m_x = pt.m_x; m_y = pt.m_y; return(*this); }

	// Operations - Add, Subtract, Scale
	TVECTOR &Add(TVECTOR &pt)				{ m_x += pt.m_x; m_y += pt.m_y; return *this; }
	TVECTOR &Subtract(TVECTOR &pt)			{ m_x -= pt.m_x; m_y -= pt.m_y; return *this; }
	TVECTOR &Scale(TVECTOR &pt)				{ m_x *= pt.m_x; m_y *= pt.m_y; return *this; }
	
	TVECTOR &Scale(T scalar)				{ m_x *= scalar; m_y *= scalar; return *this; }
	TVECTOR &ScaleUp(T scalar)				{ m_x *= scalar; m_y *= scalar; return *this; }
	TVECTOR &ScaleDown(T scalar)			{ m_x /= scalar; m_y /= scalar; return *this; }

	friend TVECTOR AddVectors(TVECTOR &pt1, TVECTOR &pt2)		{ return TVECTOR(pt1.m_x + pt2.m_x, pt1.m_y + pt2.m_y); }
	friend TVECTOR SubtractVectors(TVECTOR &pt1, TVECTOR &pt2)	{ return TVECTOR(pt1.m_x - pt2.m_x, pt1.m_y - pt2.m_y); }
	friend TVECTOR ScaleVectors(TVECTOR &pt1, TVECTOR &pt2)		{ return TVECTOR(pt1.m_x * pt2.m_x, pt1.m_y * pt2.m_y); }

	friend TVECTOR ScaleVector(TVECTOR &pt, T scalar)			{ return TVECTOR(pt.m_x * scalar, pt.m_y * scalar); }
	friend TVECTOR ScaleVectorUp(TVECTOR &pt, T scalar)			{ return TVECTOR(pt.m_x * scalar, pt.m_y * scalar); }
	friend TVECTOR ScaleVectorDown(TVECTOR &pt, T scalar)		{ return TVECTOR(pt.m_x / scalar, pt.m_y / scalar); }

	// Normalization
	TVECTOR &Normalize()							{ float l = Length(); if (l > 0) { m_x = (T)(m_x / l); m_y = (T)(m_y / l); } return *this; }
	friend TVECTOR Normalize(TVECTOR v)				{ TVECTOR v1(v); v1.Normalize(); return v1; }
	TVECTOR &Normalise()							{ float l = Length(); if (l > 0) { m_x = (T)(m_x / l); m_y = (T)(m_y / l); } return *this; }
	friend TVECTOR Normalise(TVECTOR v)				{ TVECTOR v1(v); v1.Normalize(); return v1; }

	// Dot & Cross Products
	friend T Dot(TVECTOR &p, TVECTOR &q)			{ return p.m_x * q.m_x + p.m_y * q.m_y; }

	// Cross Product
	friend T Cross(TVECTOR &p, TVECTOR &q)			{ return p.m_x * q.m_y - p.m_y * q.m_x; }
	friend TVECTOR Cross(T f, TVECTOR &q)			{ return TVECTOR(-f * q.m_y, f * q.m_x); }

	// Reflection
	friend TVECTOR Reflect(TVECTOR &vec, TVECTOR &normal)	{ return vec - 2 * Dot(vec, normal) * normal; }

	// Length and Distance
	float SqrLength()								{ return (float)(m_x * m_x + m_y * m_y); }
	float Length()									{ return (float)sqrt((float)(m_x * m_x + m_y * m_y)); }
	friend float Length(TVECTOR &p)					{ return p.Length(); }
	float Distance(TVECTOR &pt)						{ return Subtract(pt).Length(); }
	friend float Distance(TVECTOR &p, TVECTOR &q)	{ return p.Distance(q); }

	
	
	// Operators

	// unary
	TVECTOR operator -()							{ return TVECTOR(-m_x, -m_y); } 
	TVECTOR operator +()							{ return TVECTOR(m_x, m_y); } 

	// binary
	friend TVECTOR operator +(TVECTOR &pt1, TVECTOR &pt2)	{ return AddVectors(pt1, pt2); }
	friend TVECTOR operator -(TVECTOR &pt1, TVECTOR &pt2)	{ return SubtractVectors(pt1, pt2); }
	friend TVECTOR operator *(TVECTOR &pt1, TVECTOR &pt2)	{ return ScaleVectors(pt1, pt2); }

	friend TVECTOR operator *(TVECTOR &pt, T scalar)		{ return ScaleVector(pt, scalar); }
	friend TVECTOR operator *(T scalar, TVECTOR &pt)		{ return ScaleVector(pt, scalar); }
	friend TVECTOR operator /(TVECTOR &pt, T scalar)		{ return ScaleVectorDown(pt, scalar); }
	
	// assignment
	TVECTOR &operator =(TVECTOR &pt)		{ return Set(pt); }
	TVECTOR &operator +=(TVECTOR &pt)		{ return Add(pt); }
	TVECTOR &operator -=(TVECTOR &pt)		{ return Subtract(pt); }
	TVECTOR &operator *=(TVECTOR &pt)		{ return Scale(pt); }

	TVECTOR &operator *=(T scalar)			{ return Scale(scalar); }
	TVECTOR &operator /=(T scalar)			{ return ScaleDown(scalar); }

	// comparison
	bool operator ==(TVECTOR pt)			{ return (m_x == pt.m_x && m_y == pt.m_y); }
	bool operator !=(TVECTOR pt)			{ return (m_x != pt.m_x || m_y != pt.m_y); }
};

template class EXT_DECL TVector<float,Sint16>;
template class EXT_DECL TVector<Sint16,float>;

typedef TVector<float,Sint16> CVector;
typedef TVector<Sint16,float> CVectorI;

#endif
