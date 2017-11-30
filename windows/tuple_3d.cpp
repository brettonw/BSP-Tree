#include "precompile.h"
#include "utility.h"
#include "tuple_3d.h"

Tuple_3d::Tuple_3d (const Tuple_3d& t) {
    xyz[X] = t[X]; xyz[Y] = t[Y]; xyz[Z] = t[Z]; xyz[W] = t[W];
}

Tuple_3d::Tuple_3d (real x, real y, real z, real w) {
    xyz[X] = x; xyz[Y] = y; xyz[Z] = z; xyz[W] = w;
}

void	Tuple_3d::operator = (const Tuple_3d& t) {
    xyz[X] = t[X]; xyz[Y] = t[Y]; xyz[Z] = t[Z]; xyz[W] = t[W];
}

bool	Tuple_3d::operator == (const Tuple_3d& t) const {
    return	bool ((FABS (xyz[X] - t[X]) < EPSILON) and
        (FABS (xyz[Y] - t[Y]) < EPSILON) and
        (FABS (xyz[Z] - t[Z]) < EPSILON) and
        (FABS (xyz[W] - t[W]) < EPSILON));
}

bool	Tuple_3d::operator != (const Tuple_3d& t) const {
    return	bool ((FABS (xyz[X] - t[X]) > EPSILON) or
        (FABS (xyz[Y] - t[Y]) > EPSILON) or
        (FABS (xyz[Z] - t[Z]) > EPSILON) or
        (FABS (xyz[W] - t[W]) > EPSILON));
}

void	Tuple_3d::operator () (real x, real y, real z, real w) {
    xyz[X] = x; xyz[Y] = y; xyz[Z] = z; xyz[W] = w;
}

real	Tuple_3d::operator | (const Tuple_3d& t) const {
    return 	(xyz[X] * t[X]) +
        (xyz[Y] * t[Y]) +
        (xyz[Z] * t[Z]) +
        (xyz[W] * t[W]);
}

Coord	Tuple_3d::majorAxis (void) const {
    Coord	axis = X;
    if (FABS (xyz[Y]) > FABS (xyz[X]))
        axis = Y;
    if (FABS (xyz[Z]) > FABS (xyz[axis]))
        axis = Z;
    return axis;
}

Coord	Tuple_3d::minorAxis (void) const {
    Coord	axis = X;
    if (FABS (xyz[Y]) <= FABS (xyz[X]))
        axis = Y;
    if (FABS (xyz[Z]) <= FABS (xyz[axis]))
        axis = Z;
    return axis;
}
