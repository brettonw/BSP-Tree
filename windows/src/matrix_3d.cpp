#include "precompile.h"
#include "utility.h"
#include "matrix_3d.h"

real	Matrix_3d::identity[4][4] = {
    { R (1.0), R (0.0), R (0.0), R (0.0) },
    { R (0.0), R (1.0), R (0.0), R (0.0) },
    { R (0.0), R (0.0), R (1.0), R (0.0) },
    { R (0.0), R (0.0), R (0.0), R (1.0) }
};

Matrix_3d	IDENTITY_MATRIX (Matrix_3d::identity);

Matrix_3d::Matrix_3d (const Matrix_3d& m) {
    for (short i = 0; i < 4; i++) {
        for (short j = 0; j < 4; j++) {
            mat[i][j] = m.mat[i][j];
        }
    }
}

Matrix_3d::Matrix_3d (real f[4][4]) {
    for (short i = 0; i < 4; i++) {
        for (short j = 0; j < 4; j++) {
            mat[i][j] = f[i][j];
        }
    }
}

void Matrix_3d::operator = (const Matrix_3d& m) {
    for (short i = 0; i < 4; i++) {
        for (short j = 0; j < 4; j++) {
            mat[i][j] = m.mat[i][j];
        }
    }
}

Matrix_3d Matrix_3d::operator * (const Matrix_3d& m) const {
    Matrix_3d result;
    for (short i = 0; i < 4; i++) {
        for (short j = 0; j < 4; j++) {
            Tuple_3d r (mat[i][0], mat[i][1], mat[i][2], mat[i][3]);
            Tuple_3d c (m.mat[0][j], m.mat[1][j], m.mat[2][j], m.mat[3][j]);
            result.mat[i][j] = r | c;
        }
    }
    return result;
}

real Matrix_3d::cofactor (int i, int j) const {
    int i0, i1, i2, j0, j1, j2;
    real det;
    switch (i) {
        case 0:	i0 = 1; i1 = 2; i2 = 3; break;
        case 1:	i0 = 0; i1 = 2; i2 = 3; break;
        case 2:	i0 = 0; i1 = 1; i2 = 3; break;
        case 3:	i0 = 0; i1 = 1; i2 = 2; break;
    }
    switch (j) {
        case 0:	j0 = 1; j1 = 2; j2 = 3; break;
        case 1:	j0 = 0; j1 = 2; j2 = 3; break;
        case 2:	j0 = 0; j1 = 1; j2 = 3; break;
        case 3:	j0 = 0; j1 = 1; j2 = 2; break;
    }

    det = mat[i0][j0] * (mat[i1][j1] * mat[i2][j2] - mat[i1][j2] * mat[i2][j1]) -
        mat[i0][j1] * (mat[i1][j0] * mat[i2][j2] - mat[i1][j2] * mat[i2][j0]) +
        mat[i0][j2] * (mat[i1][j0] * mat[i2][j1] - mat[i1][j1] * mat[i2][j0]);
    return odd (i + j) ? -det : det;
}

real Matrix_3d::determinant (void) const {
    return  mat[0][0] * cofactor (0, 0) +
        mat[0][1] * cofactor (0, 1) +
        mat[0][2] * cofactor (0, 2) +
        mat[0][3] * cofactor (0, 3);
}

Matrix_3d Matrix_3d::inverse (void) const {
    Matrix_3d inverse;
    real det = determinant ();
    for (short i = 0; i < 4; i++) {
        for (short j = 0; j < 4; j++) {
            inverse.mat[j][i] = cofactor (i, j) / det;
        }
    }
    return inverse;
}

Tuple_3d operator * (const Tuple_3d& t, const Matrix_3d& m) {
    Tuple_3d    c0 (m (0, 0), m (1, 0), m (2, 0), m (3, 0)),
        c1 (m (0, 1), m (1, 1), m (2, 1), m (3, 1)),
        c2 (m (0, 2), m (1, 2), m (2, 2), m (3, 2)),
        c3 (m (0, 3), m (1, 3), m (2, 3), m (3, 3));
    return Tuple_3d (t | c0, t | c1, t | c2, t | c3);
}

Tuple_3d operator * (const Matrix_3d& m, const Tuple_3d& t) {
    Tuple_3d    r0 (m (0, 0), m (0, 1), m (0, 2), m (0, 3)),
        r1 (m (1, 0), m (1, 1), m (1, 2), m (1, 3)),
        r2 (m (2, 0), m (2, 1), m (2, 2), m (2, 3)),
        r3 (m (3, 0), m (3, 1), m (3, 2), m (3, 3));
    return Tuple_3d (t | r0, t | r1, t | r2, t | r3);
}

Matrix_3d	quaternionMatrix (real x, real y, real z, real w) {
    Matrix_3d	m;
    m (0, 0) = w*w + x*x - y*y - z*z;
    m (0, 1) = R (2.0) * (x*y + w*z);
    m (0, 2) = R (2.0) * (x*z - w*y);
    m (0, 3) = R (0.0);
    m (1, 0) = R (2.0) * (x*y - w*z);
    m (1, 1) = w*w - x*x + y*y - z*z;
    m (1, 2) = R (2.0) * (y*z + w*x);
    m (1, 3) = R (0.0);
    m (2, 0) = R (2.0) * (x*z + w*y);
    m (2, 1) = R (2.0) * (y*z - w*x);
    m (2, 2) = w*w - x*x - y*y + z*z;
    m (2, 3) = R (0.0);
    m (3, 0) = R (0.0);
    m (3, 1) = R (0.0);
    m (3, 2) = R (0.0);
    m (3, 3) = w*w + x*x + y*y + z*z;
    return m;
}

Matrix_3d Matrix_3d::fromQuaternion (const Vector_3d& begin, const Vector_3d& end) {
    // compute a quaternion from two vectors defining a great arc on a unit sphere
    real		w = begin | end;
    Vector_3d	perp = begin ^ end;
    real	norm = perp.norm ();
    if (norm < EPSILON)
        return IDENTITY_MATRIX;
    //#define	HALF_SPEED_QUATERNION
#ifdef	HALF_SPEED_QUATERNION
    real theta = ACOS (w) / R (2.0);
    w = COS (theta);
    perp = (perp / norm) * SIN (theta);
#endif
    return quaternionMatrix (perp[X], perp[Y], perp[Z], w);
}
