//------------------------------------------------------------------------------
//	File:					vector_3d.cp
//	Date:					8/26/94
//	Author:				Bretton Wade
//
//	Description:	this file contains the methods for a vector_3d
//
//------------------------------------------------------------------------------

#include "precompile.h"
#include "point_3d.h"
#include "vector_3d.h"

//------------------------------------------------------------------------------
//	global variables
//------------------------------------------------------------------------------
Vector_3d	ZERO_VECTOR (R(0.0), R(0.0), R(0.0));																	//	a zero value vector_3d

//------------------------------------------------------------------------------
//	constructor
//------------------------------------------------------------------------------
Vector_3d::Vector_3d (real x, real y, real z, real w) : Tuple_3d (x, y, z, w)		//	constructor from three values
{																																								//	begin
}																																								//	end

//------------------------------------------------------------------------------
//	constructor
//------------------------------------------------------------------------------
Vector_3d::Vector_3d (const Vector_3d& v) : Tuple_3d (v)												//	copy constructor
{																																								//	begin
}																																								//	end

//------------------------------------------------------------------------------
//	constructor
//------------------------------------------------------------------------------
Vector_3d::Vector_3d (const Point_3d& p) : Tuple_3d (p[X], p[Y], p[Z], R(0.0))	//	constructor from a point_3d
{																																								//	begin
}																																								//	end

//------------------------------------------------------------------------------
//	constructor
//------------------------------------------------------------------------------
Vector_3d::Vector_3d (const Tuple_3d& t)																				//	constructor from a tuple_3d
{																																								//	begin
	xyz[X] = t[X]; xyz[Y] = t[Y]; xyz[Z] = t[Z]; xyz[W] = R(0.0);									//	copy the values into the tuple_3d
}																																								//	end

//------------------------------------------------------------------------------
//	assignment
//------------------------------------------------------------------------------
Vector_3d	&Vector_3d::operator = (const Vector_3d& v)														//	assignment operator
{																																								//	begin
	Tuple_3d::operator () (v[X], v[Y], v[Z], v[W]);																//	copy the values
	return *this;																																	//	return the reference to this
}																																								//	end

//------------------------------------------------------------------------------
//	assignment
//------------------------------------------------------------------------------
Vector_3d	&Vector_3d::operator = (const Tuple_3d& t)														//	assignment operator
{																																								//	begin
	Tuple_3d::operator () (t[X], t[Y], t[Z], R(0.0));															//	copy the values
	return *this;																																	//	return the reference to this
}																																								//	end

//------------------------------------------------------------------------------
//	assignment by values
//------------------------------------------------------------------------------
void	Vector_3d::operator () (real x, real y, real z, real w)										//	function call operator
{																																								//	begin
	Tuple_3d::operator () (x, y, z, w);																						//	assign the coordinates
}																																								//	end

//------------------------------------------------------------------------------
//	scalar multiplication
//------------------------------------------------------------------------------
Vector_3d 	Vector_3d::operator * (real s) const																//	scalar multiplication
{																																								//	begin
	return Vector_3d (xyz[X] * s, xyz[Y] * s, xyz[Z] * s);												//	return the multiplied vector_3d
}																																								//	end

//------------------------------------------------------------------------------
//	division by a scalar
//------------------------------------------------------------------------------
Vector_3d 	Vector_3d::operator / (real s) const																//	scalar division
{																																								//	begin
	return Vector_3d (xyz[X] / s, xyz[Y] / s, xyz[Z] / s);												//	return the divided vector_3d
}																																								//	end

//------------------------------------------------------------------------------
//	cross product
//------------------------------------------------------------------------------
Vector_3d	Vector_3d::operator ^ (const Vector_3d& v) const											//	cross product
{																																								//	begin
	return Vector_3d (	(xyz[Y] * v[Z]) - (xyz[Z] * v[Y]), 												//	return a vector_3d, x coordinate
									(xyz[Z] * v[X]) - (xyz[X] * v[Z]),														//	y coordinate
									(xyz[X] * v[Y]) - (xyz[Y] * v[X]));														//	z coordinate
}																																								//	end

//------------------------------------------------------------------------------
//	addition
//------------------------------------------------------------------------------
Vector_3d	Vector_3d::operator + (const Vector_3d& v) const											//	addition operator
{																																								//	begin
	return Vector_3d (	xyz[X] + v[X], 																						//	return a vector_3d, x coordinate
									xyz[Y] + v[Y],																								//	y coordinate
									xyz[Z] + v[Z]);																								//	z coordinate
}																																								//	end

//------------------------------------------------------------------------------
//	self addition
//------------------------------------------------------------------------------
Vector_3d	&Vector_3d::operator += (const Vector_3d& v)													//	self addition operator
{																																								//	begin
	xyz[X] += v[X]; 																															//	x coordinate
	xyz[Y] += v[Y];																																//	y coordinate
	xyz[Z] += v[Z];																																//	z coordinate
	return *this;																																	//	return the vector_3d reference
}																																								//	end

//------------------------------------------------------------------------------
//	subtraction
//------------------------------------------------------------------------------
Vector_3d	Vector_3d::operator - (const Vector_3d& v) const											//	subtraction operator
{																																								//	begin
	return Vector_3d (	xyz[X] - v[X], 																						//	return a vector_3d, x coordinate
									xyz[Y] - v[Y],																								//	y coordinate
									xyz[Z] - v[Z]);																								//	z coordinate
}																																								//	end

//------------------------------------------------------------------------------
//	negation
//------------------------------------------------------------------------------
Vector_3d	Vector_3d::operator - (void) const																		//	unary minus operator
{																																								//	begin
	return Vector_3d (-xyz[X], -xyz[Y], -xyz[Z]);																	//	z coordinate
}																																								//	end

//------------------------------------------------------------------------------
//	compute the length
//------------------------------------------------------------------------------
real	Vector_3d::norm (void) const																							//	compute the length of the vector_3d
{																																								//	begin
	return SQRT ((*this) | (*this));																							//	return the square root of the dot product
}																																								//	end

//------------------------------------------------------------------------------
//	reduce to length 1
//------------------------------------------------------------------------------
Vector_3d	&Vector_3d::normalize (void)																					//	reduce the vector_3d to length 1.0
{																																								//	begin
	real	n = norm ();																														//	compute the length of the vector_3d
	xyz[X] /= n; xyz[Y] /= n; xyz[Z] /= n;																				//	divide through by the length
	return *this;																																	//	return a referencre to this vector_3d
}																																								//	end

//------------------------------------------------------------------------------
