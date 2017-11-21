#ifndef	    _VECTOR_3D_
#include    "vector_3d.h"
#endif  //  _VECTOR_3D_

#ifndef     _MATRIX_3D_
#define     _MATRIX_3D_

class	Matrix_3d {
    protected:
    real mat[4][4];

    public:
    static real	identity[4][4];
    Matrix_3d (void) {}
    Matrix_3d (const Matrix_3d& m);
    Matrix_3d (real f[4][4]);
    void operator = (const Matrix_3d& m);
    real& operator () (int r, int c);
    const real& operator () (int r, int c) const;
    Matrix_3d operator * (const Matrix_3d& m) const;
    real cofactor (int r, int c) const;
    real determinant (void) const;
    Matrix_3d inverse (void) const;
    static Matrix_3d fromQuaternion (const Vector_3d& begin, const Vector_3d& end);
};

inline	real& Matrix_3d::operator () (int r, int c) {
    return (mat[r][c]);
}

inline	const	real& Matrix_3d::operator () (int r, int c) const {
    return (mat[r][c]);
}

Tuple_3d operator * (const Tuple_3d& t, const Matrix_3d& m);
Tuple_3d operator * (const Matrix_3d& m, const Tuple_3d& t);

extern	Matrix_3d	IDENTITY_MATRIX;

#endif  //  _MATRIX_3D_
