#ifndef     _VECTOR_3D_
#include    "vector_3d.h"
#endif  //  _VECTOR_3D_

#ifndef     _POINT_3D_
#include    "point_3d.h"
#endif  //  _POINT_3D_

#ifndef	    _RAY_3D_
#define     _RAY_3D_

class Ray_3d {
    protected:
    Point_3d origin;
    Vector_3d direction;

    public:
    Ray_3d (const Point_3d& origin, const Vector_3d& direction);
    const Point_3d& getOrigin (void) const;
    const Vector_3d& getDirection (void) const;
    Point_3d intersectionPoint (real distance) const;
};

inline	const Point_3d& Ray_3d::getOrigin (void) const {
    return origin;
}

inline	const Vector_3d& Ray_3d::getDirection (void) const {
    return direction;
}

#endif  //  _RAY_3D_
