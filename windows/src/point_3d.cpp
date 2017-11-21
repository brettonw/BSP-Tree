#include "precompile.h"
#include "point_3d.h"
#include "vector_3d.h"

Point_3d	ORIGIN_3D (R (0.0), R (0.0), R (0.0));

Point_3d::Point_3d (real x, real y, real z, real w) : Tuple_3d (x, y, z, w) {
    if (w != R (1.0)) {
        xyz[X] /= w; xyz[Y] /= w; xyz[Z] /= w; xyz[W] = R (1.0);
    }
}

Point_3d::Point_3d (const Point_3d& p) : Tuple_3d (p) {}

Point_3d::Point_3d (const Vector_3d& v) : Tuple_3d (v[X], v[Y], v[Z], R (1.0)) {}

Point_3d::Point_3d (const Tuple_3d& t) {
    real	w = t[W];
    if (w != R (1.0)) {
        xyz[X] = t[X] / w; xyz[Y] = t[Y] / w;
        xyz[Z] = t[Z] / w; xyz[W] = R (1.0);
    } else {
        xyz[X] = t[X]; xyz[Y] = t[Y];
        xyz[Z] = t[Z]; xyz[W] = t[W];
    }
}

Point_3d& Point_3d::operator = (const Point_3d& p) {
    Tuple_3d::operator () (p[X], p[Y], p[Z], p[W]);
    return *this;
}

Point_3d& Point_3d::operator = (const Tuple_3d& t) {
    real	w = t[W];
    if (w != R (1.0))
        Tuple_3d::operator () (t[X] / w, t[Y] / w, t[Z] / w, R (1.0));
    else
        Tuple_3d::operator = (t);
    return *this;
}

void	Point_3d::operator () (real x, real y, real z, real w) {
    Tuple_3d::operator () (x, y, z, w);
}

Vector_3d	Point_3d::operator - (const Point_3d& p) const {
    return Vector_3d (xyz[X] - p[X],
        xyz[Y] - p[Y],
        xyz[Z] - p[Z]);
}

Point_3d	Point_3d::operator + (const Vector_3d& v) const {
    return Point_3d (xyz[X] + v[X],
        xyz[Y] + v[Y],
        xyz[Z] + v[Z]);
}
