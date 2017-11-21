#ifndef	    _TUPLE_3D_
#include    "tuple_3d.h"
#endif  //  _TUPLE_3D_

#ifndef     _POINT_3D_
#define     _POINT_3D_

#ifndef     _VECTOR_3D_
class Vector_3d;
#endif  //  _VECTOR_3D_

class Point_3d : public Tuple_3d {
    public:
    Point_3d (void) {}
    Point_3d (real x, real y, real z, real w = R (1.0));
    Point_3d (const Point_3d& p);
    Point_3d (const Vector_3d& v);
    Point_3d (const Tuple_3d& t);
    Point_3d& operator = (const Point_3d& p);
    Point_3d& operator = (const Tuple_3d& t);
    void operator () (real x, real y, real z, real w = R (1.0));
    Vector_3d operator - (const Point_3d& p) const;
    Point_3d operator + (const Vector_3d& v) const;
};

extern	Point_3d	ORIGIN_3D;

#endif  //  _POINT_3D_
