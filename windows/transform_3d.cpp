#include "precompile.h"
#include "utility.h"
#include "transform_3d.h"

Matrix_3d Transform_3d::rotateX (real angle) {
    angle = degreesToRadians (angle);
    real	cosine = COS (angle),
        sine = SIN (angle);
    Matrix_3d	m (Matrix_3d::identity);
    m (1, 1) = cosine;
    m (2, 2) = cosine;
    m (2, 1) = -sine;
    m (1, 2) = sine;
    return m;
}

Matrix_3d Transform_3d::rotateY (real angle) {
    angle = degreesToRadians (angle);
    real	cosine = COS (angle),
        sine = SIN (angle);
    Matrix_3d	m (Matrix_3d::identity);
    m (0, 0) = cosine;
    m (2, 2) = cosine;
    m (2, 0) = sine;
    m (0, 2) = -sine;
    return m;
}

Matrix_3d Transform_3d::rotateZ (real angle) {
    angle = degreesToRadians (angle);
    real	cosine = COS (angle),
        sine = SIN (angle);
    Matrix_3d	m (Matrix_3d::identity);
    m (0, 0) = cosine;
    m (1, 1) = cosine;
    m (1, 0) = -sine;
    m (0, 1) = sine;
    return m;
}

Matrix_3d Transform_3d::translate (real x, real y, real z) {
    Matrix_3d	m (Matrix_3d::identity);
    m (3, 0) = x;
    m (3, 1) = y;
    m (3, 2) = z;
    return m;
}

Matrix_3d Transform_3d::scale (real x, real y, real z) {
    Matrix_3d	m (Matrix_3d::identity);
    m (0, 0) = x;
    m (1, 1) = y;
    m (2, 2) = z;
    return m;
}

Matrix_3d Transform_3d::perspective (real distance) {
    Matrix_3d	m (Matrix_3d::identity);
    m (2, 3) = R (-1.0) / distance;
    return m;
}

Matrix_3d Transform_3d::vectorMatrix (Tuple_3d& n) {
    Vector_3d	t (n),
        w (n);
    t[w.minorAxis ()] = R (1.0);
    Vector_3d	u = (t ^ w).normalize (),
        v = w ^ u;
    Matrix_3d	m (Matrix_3d::identity);
    m (0, 0) = u[X];
    m (0, 1) = u[Y];
    m (0, 2) = u[Z];

    m (1, 0) = v[X];
    m (1, 1) = v[Y];
    m (1, 2) = v[Z];

    m (2, 0) = w[X];
    m (2, 1) = w[Y];
    m (2, 2) = w[Z];
    return m;
}

Matrix_3d Transform_3d::viewMatrix (const Vector_3d& u, const Vector_3d& v, const Vector_3d& n, const Point_3d& r) {
    Matrix_3d	m;
    m (0, 0) = u[X];
    m (1, 0) = u[Y];
    m (2, 0) = u[Z];
    m (3, 0) = -(r | u);

    m (0, 1) = v[X];
    m (1, 1) = v[Y];
    m (2, 1) = v[Z];
    m (3, 1) = -(r | v);

    m (0, 2) = n[X];
    m (1, 2) = n[Y];
    m (2, 2) = n[Z];
    m (3, 2) = -(r | n);

    m (0, 3) = R (0.0);
    m (1, 3) = R (0.0);
    m (2, 3) = R (0.0);
    m (3, 3) = R (1.0);
    return m;
}

