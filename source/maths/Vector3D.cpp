/**
 * =========================================================================
 * File        : Vector3D.cpp
 * Project     : 0 A.D.
 * Description : Provides an interface for a vector in R3 and
 *               allows vector and scalar operations on it
 * =========================================================================
 */

#include "precompiled.h"

#include "Vector3D.h"

#include <math.h>
#include <float.h>
#include "MathUtil.h"

int CVector3D::operator ! () const 
{
	if (X != 0.0f ||
		Y != 0.0f ||
		Z != 0.0f)
		
		return 0;
	
	return 1;
}

bool CVector3D::operator== (const CVector3D &vector) const
{
	return (X == vector.X && Y == vector.Y && Z == vector.Z);
}

//vector addition
CVector3D CVector3D::operator + (const CVector3D &vector) const 
{
	return CVector3D(X+vector.X, Y+vector.Y, Z+vector.Z);
}

//vector addition/assignment
CVector3D &CVector3D::operator += (const CVector3D &vector)
{
	X += vector.X;
	Y += vector.Y;
	Z += vector.Z;

	return *this;
}

//vector subtraction
CVector3D CVector3D::operator - (const CVector3D &vector) const 
{
	return CVector3D(X-vector.X, Y-vector.Y, Z-vector.Z);
}

//vector negation
CVector3D CVector3D::operator-() const 
{
	return CVector3D(-X, -Y, -Z);
}
//vector subtrcation/assignment
CVector3D &CVector3D::operator -= (const CVector3D &vector) 
{
	X -= vector.X;
	Y -= vector.Y;
	Z -= vector.Z;

	return *this;
}

//scalar multiplication
CVector3D CVector3D::operator * (float value) const 
{
	return CVector3D(X*value, Y*value, Z*value);
}

//scalar multiplication/assignment
CVector3D& CVector3D::operator *= (float value)
{
	X *= value;
	Y *= value;
	Z *= value;

	return *this;
}

void CVector3D::Set (float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

void CVector3D::Clear ()
{
	X = Y = Z = 0.0f;
}

//Dot product
float CVector3D::Dot (const CVector3D &vector) const 
{
	return ( X * vector.X +
			 Y * vector.Y +
			 Z * vector.Z );
}

//Cross product
CVector3D CVector3D::Cross (const CVector3D &vector) const 
{
	CVector3D Temp;

	Temp.X = (Y * vector.Z) - (Z * vector.Y);
	Temp.Y = (Z * vector.X) - (X * vector.Z);
	Temp.Z = (X * vector.Y) - (Y * vector.X);

	return Temp;
}


float CVector3D::LengthSquared () const 
{
	return ( SQR(X) + SQR(Y) + SQR(Z) );
}

float CVector3D::Length () const 
{
	return sqrtf ( LengthSquared() );
}

void CVector3D::Normalize ()
{
	float scale = 1.0f/Length ();

	X *= scale;
	Y *= scale;
	Z *= scale;
}


//-----------------------------------------------------------------------------

float MaxComponent(const CVector3D& v)
{
	float max = -FLT_MAX;
	for(int i = 0; i < 3; i++)
		max = std::max(max, v[i]);
	return max;
}
