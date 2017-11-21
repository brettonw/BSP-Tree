#include "precompile.h"
#include "utility.h"
#include "plane_3d.h"

Plane_3d::Plane_3d (const Vector_3d& v, const Point_3d& p)
    : Tuple_3d (v[X], v[Y], v[Z], -(v | p)) {}

Plane_3d::Plane_3d (const Point_3d& a, const Point_3d& b, const Point_3d& c) {
    Vector_3d	v = ((b - a) ^ (c - b)).normalize ();
    Tuple_3d::operator () (v[X], v[Y], v[Z], -(v | a));
}

Plane_3d::Plane_3d (real a, real b, real c, real d) : Tuple_3d (a, b, c, d) {}

Plane_3d::Plane_3d (const Plane_3d& p) : Tuple_3d (p) {}

Plane_3d::Plane_3d (const Tuple_3d& t) : Tuple_3d (t) {}

Plane_3d::~Plane_3d (void) {}

Plane_3d	&Plane_3d::operator = (const Plane_3d& p) {
    Tuple_3d::operator () (p[X], p[Y], p[Z], p[W]);
    return *this;
}

Plane_3d	&Plane_3d::operator = (const Tuple_3d& t) {
    Tuple_3d::operator = (t);
    return *this;
}

void	Plane_3d::define (const Vector_3d& v, const Point_3d& p) {
    Tuple_3d::operator () (v[X], v[Y], v[Z], -(v | p));
}

void	Plane_3d::define (const Point_3d& a, const Point_3d& b, const Point_3d& c)
{
    Vector_3d	v = (b - a) ^ (c - b);
    Tuple_3d::operator () (v[X], v[Y], v[Z], -(v | a));
}

void	Plane_3d::invert (void) {
    xyz[X] *= R (-1.0); xyz[Y] *= R (-1.0); xyz[Z] *= R (-1.0); xyz[W] *= R (-1.0);
}

real		Plane_3d::rayIntersection (const Ray_3d& r) const {
    real costheta = -(r.getDirection () | *this);
    if (FABS (costheta) < EPSILON) return R (-1.0);
    return (r.getOrigin () | *this) / costheta;
}
