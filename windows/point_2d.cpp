//------------------------------------------------------------------------------
//	File:					point_2d.cp
//	Date:					11/07/94
//	Author:				Bretton Wade
//
//	Description:	this file contains the class definition for a (u, v) point_2d
//
//------------------------------------------------------------------------------

#include "precompile.h"
#include "point_2d.h"
#include "vector_2d.h"

//------------------------------------------------------------------------------
//	global variables
//------------------------------------------------------------------------------
Point_2d	ORIGIN_2D (R(0.0), R(0.0));																						//	the origin of the coordinate system

//------------------------------------------------------------------------------
//	constructor
//------------------------------------------------------------------------------
Point_2d::Point_2d (real x, real y) : Tuple_2d (x, y)														//	normal constructor
{																																								//	begin
}																																								//	end

//------------------------------------------------------------------------------
//	constructor
//------------------------------------------------------------------------------
Point_2d::Point_2d (const Point_2d& p) : Tuple_2d (p)														//	copy constructor
{																																								//	begin
}																																								//	end

//------------------------------------------------------------------------------
//	constructor
//------------------------------------------------------------------------------
Point_2d::Point_2d (const Vector_2d& v) : Tuple_2d (v)														//	constructor from a 2d vector
{																																								//	begin
}																																								//	end

//------------------------------------------------------------------------------
//	assignment operator
//------------------------------------------------------------------------------
Point_2d	&Point_2d::operator = (const Point_2d& p)															//	assignment operator
{																																								//	begin
	Tuple_2d::operator = (p);
	return *this;
}																																								//	end

//------------------------------------------------------------------------------
//	vector addition operator
//------------------------------------------------------------------------------
Point_2d	Point_2d::operator + (const Vector_2d& v) const												//	add a vector to a point
{																																								//	begin
	return Point_2d (xy[X] + v[X], xy[Y] + v[Y]);
}																																								//	end

//------------------------------------------------------------------------------
//	subtraction operator
//------------------------------------------------------------------------------
Vector_2d	Point_2d::operator - (const Point_2d& p) const												//	subtract two points
{																																								//	begin
	return Vector_2d (xy[X] - p[X], xy[Y] - p[Y]);
}																																								//	end

//------------------------------------------------------------------------------
