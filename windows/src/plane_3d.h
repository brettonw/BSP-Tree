#ifndef     _OBJECT_3D_
#include    "object_3d.h"
#endif  //  _OBJECT_3D_

#ifndef     _PLANE_3D_
#define     _PLANE_3D_

class	Plane_3d : public Tuple_3d, public Object_3d {
    public:
    Plane_3d (void) {}
    Plane_3d (const Vector_3d& v, const Point_3d& p);
    Plane_3d (const Point_3d& a, const Point_3d& b, const Point_3d& c);
    Plane_3d (real a, real b, real c, real d);
    Plane_3d (const Plane_3d& p);
    Plane_3d (const Tuple_3d& t);
    virtual	~Plane_3d (void);
    Plane_3d& operator = (const Plane_3d& p);
    Plane_3d& operator = (const Tuple_3d& t);
    void define (const Vector_3d& v, const Point_3d& p);
    void define (const Point_3d& a, const Point_3d& b, const Point_3d& c);
    void invert (void);
    virtual	real rayIntersection (const Ray_3d& r) const;
};

#endif  //  _PLANE_3D_
