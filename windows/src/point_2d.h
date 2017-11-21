#ifndef	    _TUPLE_2D_
#include    "tuple_2d.h"
#endif  //  _TUPLE_2D_

#ifndef     _POINT_2D_
#define     _POINT_2D_

#ifndef     _VECTOR_2D_
class Vector_2d;																																//	forward declaration
#endif  //  _VECTOR_2D_

class Point_2d : public Tuple_2d																								//	point_2d class
{																																								//	begin
	public:																																				//	members available externally
				Point_2d (void) {}																											//	default constructor
				Point_2d (real x, real y);																							//	normal constructor
				Point_2d (const Point_2d& p);																						//	copy constructor
				Point_2d (const Vector_2d& v);																					//	constructor from a 2d vector_3d
				Point_2d& operator = (const Point_2d& p);															//	assignment operator
				Point_2d operator + (const Vector_2d& v) const;												//	add a vector_3d to a point
				Vector_2d operator - (const Point_2d& p) const;													//	subtract two points
};																																							//	end

extern Point_2d ORIGIN_2D;																										//	the origin of the coordinate system

#endif	//  POINT_2D
