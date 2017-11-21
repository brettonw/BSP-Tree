#ifndef     _VECTOR_3D_
#include    "vector_3d.h"
#endif  //  _VECTOR_3D_

#ifndef     _POINT_3D_
#include    "point_3d.h"
#endif  //  _POINT_3D_

#ifndef     _MATRIX_3D_
#include    "matrix_3d.h"
#endif  //  _MATRIX_3D_

#ifndef     _TRANSFORM_3D_
#define     _TRANSFORM_3D_

class Transform_3d {
    public:
    static Matrix_3d rotateX (real angle);
    static Matrix_3d rotateY (real angle);
    static Matrix_3d rotateZ (real angle);
    static Matrix_3d translate (real x, real y, real z);
    static Matrix_3d scale (real x, real y, real z);
    static Matrix_3d perspective (real distance);
    static Matrix_3d vectorMatrix (Tuple_3d& n);
    static Matrix_3d viewMatrix (const Vector_3d& u, const Vector_3d& v, const Vector_3d& n, const Point_3d& r);
};

#endif  //  _TRANSFORM_3D_
