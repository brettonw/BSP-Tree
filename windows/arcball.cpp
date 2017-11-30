#include "precompile.h"
#include "arcball.h"
#include "view.h"

Arcball::Arcball (const Point_2d& cent, real rad) {
    center = Vector_2d (cent);
    radius = rad;
}

void Arcball::click (const Point_2d& pt) {
    start_vec = mapToSphere (pt - center);
    start_pt = Point_2d (start_vec[X], start_vec[Y]) + center;
}

Matrix_3d Arcball::drag (const Point_2d& pt) {
    end_vec = mapToSphere (pt - center);
    end_pt = Point_2d (end_vec[X], end_vec[Y]) + center;
    return Matrix_3d::fromQuaternion (start_vec, end_vec);
}

void Arcball::drawBackground (void) const {
    Point_2d A = Point_2d (-radius, -radius) + center;
    Point_2d B = Point_2d (radius, radius) + center;
    gView->drawCircle (A, B, 0x00555555, 0x00999999);
}

void Arcball::drawForeground (void) const {
    drawArc (5);
    gView->drawCrossHair (end_pt, 0x000000ff);
    gView->drawCrossHair (start_pt, 0x00ffffff);
}

void Arcball::computeArc (short segs, const Vector_3d& a, const Vector_3d& b) const {
    if (segs) {
        Vector_3d bisector = (a + b).normalize () * radius;
        computeArc (segs - 1, a, bisector);
        computeArc (segs - 1, bisector, b);
    } else
        gView->drawLineToPt (Point_2d (b[X], b[Y]) + center, 0x00ff0000);
}

void Arcball::drawArc (short numsegs) const {
    gView->moveToPt (start_pt);
    computeArc (numsegs, start_vec, end_vec);
}

Vector_3d Arcball::mapToSphere (const Point_2d& pt) {
    real r = (pt[X] * pt[X]) + (pt[Y] * pt[Y]);
    real radsq = radius * radius;
    if (r > radsq) {
        real s = radius / SQRT (r);
        return Vector_3d (pt[X] * s, pt[Y] * s, R (0.0));
    } else
        return Vector_3d (pt[X], pt[Y], SQRT (radsq - r));
}
