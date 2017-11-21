#include "precompile.h"
#include "polygon_3d.h"

Polygon_3d::Polygon_3d (Point_3d *buffer, uint cnt, int a, ...) {
    va_list pts;
    va_start (pts, cnt);
    count = cnt;
    points = new Point_3d[count];
    for (uint i = 0; i < count; i++)
        points[i] = buffer[va_arg (pts, int)];
    plane.define (normal (), points[0]);
    va_end (pts);
}

Polygon_3d::Polygon_3d (Point_3d *buffer, uint cnt) {
    count = cnt;
    points = new Point_3d[count];
    for (uint i = 0; i < count; i++)
        points[i] = buffer[i];
    plane.define (normal (), points[0]);
}

Polygon_3d::~Polygon_3d (void) {
    delete[] points;
}

Vector_3d Polygon_3d::normal (void) const {
    Vector_3d	sum (ZERO_VECTOR);
    for (uint i = 0, last = count - 1; i < count; last = i, i++) {
        Point_3d	A = points[last],
            B = points[i];
        sum[X] += (A[Y] - B[Y]) * (A[Z] + B[Z]);
        sum[Y] += (A[Z] - B[Z]) * (A[X] + B[X]);
        sum[Z] += (A[X] - B[X]) * (A[Y] + B[Y]);
    }
    return sum.normalize ();
}

bool Polygon_3d::contains (const Point_3d& pt) const {
    Coord	x, y;
    switch (plane.majorAxis ()) {
        case X:	x = Y; y = Z; break;
        case Y:	x = Z; y = X; break;
        case Z:	x = X; y = Y; break;
    }
    real	tx = pt[x], ty = pt[y];
    Point_3d	*p1 = &points[count - 1], *p2 = points;
    int		yflag0 = ((*p1)[y] >= ty),
        inside = FALSE;
    for (int i = count; i--;) {
        int	yflag1 = ((*p2)[y] >= ty);
        if (yflag0 != yflag1) {
            int	xflag0 = ((*p1)[x] >= tx);
            if (xflag0 == ((*p2)[x] >= tx)) {
                if (xflag0)
                    inside = !inside;
            } else {
                if (((*p2)[x] - ((*p2)[y] - ty) * ((*p1)[x] - (*p2)[x]) / ((*p1)[y] - (*p2)[y])) >= tx)
                    inside = !inside;
            }
        }
        yflag0 = yflag1;
        p1 = p2;
        p2++;
    }
    return bool (inside);
}

void Polygon_3d::invert (void) {
    Point_3d	*pts = new Point_3d[count];
    short	reverse = count - 1;
    for (uint i = 0; i < count; i++)
        pts[i] = points[reverse - i];
    delete[] points;
    points = pts;
    plane.invert ();
}

real Polygon_3d::rayIntersection (const Ray_3d& r) const {
    return	plane.rayIntersection (r);
}

hclass Polygon_3d::Split (const PtrToPolygon_3d& poly, const Plane_3d& plane, PtrToPolygon_3d& in, PtrToPolygon_3d& out) {
    static Point_3d outpts[64];
    static Point_3d inpts[64];
    int out_c = 0;
    int in_c = 0;
    Point_3d ptA;
    Point_3d ptB;
    real sideA, sideB;
    hclass poly_class = HC_ON;
    ptA = poly->getVertex (poly->getCount () - 1);
    sideA = ptA | plane;
    for (uint i = 0 - 1; ++i < poly->getCount ();) {
        ptB = poly->getVertex (i);
        sideB = ptB | plane;
        if (sideB > EPSILON) {
            if (poly_class == HC_ON)
                poly_class = HC_OUT;
            else if (poly_class != HC_OUT)
                poly_class = HC_SPANNING;
            if (sideA < -EPSILON) {
                Vector_3d	v = ptB - ptA;
                outpts[out_c++] = inpts[in_c++] =
                    ptA + (v * (-(ptA | plane) / (v | plane)));
                poly_class = HC_SPANNING;
            }
            outpts[out_c++] = ptB;
        } else if (sideB < -EPSILON) {
            if (poly_class == HC_ON)
                poly_class = HC_IN;
            else if (poly_class != HC_IN)
                poly_class = HC_SPANNING;
            if (sideA > EPSILON) {
                Vector_3d	v = ptB - ptA;
                outpts[out_c++] = inpts[in_c++] =
                    ptA + (v * (-(ptA | plane) / (v | plane)));
                poly_class = HC_SPANNING;
            }
            inpts[in_c++] = ptB;
        } else
            outpts[out_c++] = inpts[in_c++] = ptB;
        ptA = ptB;
        sideA = sideB;
    }
    switch (poly_class) {
        case HC_OUT:
            out = poly;
            break;
        case HC_IN:
            in = poly;
            break;
        case HC_SPANNING:
            out = new Polygon_3d (outpts, out_c);
            in = new Polygon_3d (inpts, in_c);
            break;
    }
    return poly_class;
}
