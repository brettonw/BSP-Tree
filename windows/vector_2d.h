#ifndef	    _TUPLE_2D_
#include    "tuple_2d.h"
#endif  //  _TUPLE_2D_

#ifndef	    _VECTOR_2D_
#define     _VECTOR_2D_

#ifndef     _POINT_2D_
class Point_2d;
#endif	//  _POINT_2D_

class	Vector_2d : public Tuple_2d {
    public:
    Vector_2d (void) {}
    Vector_2d (real x, real y);
    Vector_2d (const Vector_2d& v);
    Vector_2d (const Point_2d& p);
    Vector_2d& operator = (const Vector_2d& v);
    Vector_2d operator * (real s) const;
    Vector_2d operator / (real s) const;
    Vector_2d operator + (const Vector_2d& v) const;
    Vector_2d operator - (const Vector_2d& v) const;
    real norm (void) const;
    Vector_2d& normalize (void);
};

#endif  //  _VECTOR_2D_
