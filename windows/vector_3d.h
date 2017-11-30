#ifndef	    _TUPLE_3D_
#include    "tuple_3d.h"
#endif  //  _TUPLE_3D_

#ifndef     _VECTOR_3D_
#define     _VECTOR_3D_

#ifndef     _POINT_3D_
class Point_3d;
#endif  //  _POINT_3D_

class Vector_3d : public Tuple_3d {
    public:
    Vector_3d (void) {}
    Vector_3d (real x, real y, real z, real w = R (0.0));
    Vector_3d (const Vector_3d& v);
    Vector_3d (const Point_3d& p);
    Vector_3d (const Tuple_3d& t);
    Vector_3d& operator = (const Vector_3d& v);
    Vector_3d& operator = (const Tuple_3d& t);
    void operator () (real x, real y, real z, real w = R (0.0));
    Vector_3d operator * (real s) const;
    Vector_3d operator / (real s) const;
    Vector_3d operator ^ (const Vector_3d& v) const;
    Vector_3d operator + (const Vector_3d& v) const;
    Vector_3d& operator += (const Vector_3d& v);
    Vector_3d operator - (const Vector_3d& v) const;
    Vector_3d operator - (void) const;
    real norm (void) const;
    Vector_3d& normalize (void);
};

extern	Vector_3d	ZERO_VECTOR;

#endif  //  _VECTOR_3D_
