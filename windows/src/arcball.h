#ifndef     _POINT_2D_
#include    "point_2d.h"
#endif  //  _POINT_2D_

#ifndef     _VECTOR_2D_
#include    "vector_2d.h"
#endif  //  _VECTOR_2D_

#ifndef     _POINT_3D_
#include    "point_3d.h"
#endif  //  _POINT_3D_

#ifndef     _VECTOR_3D_
#include    "vector_3d.h"
#endif  //  _VECTOR_3D_

#ifndef     _MATRIX_3D_
#include    "matrix_3d.h"
#endif  //  _MATRIX_3D_

#ifndef     _ARCBALL_
#define     _ARCBALL_

class	Arcball {
private:
    void computeArc (short, const Vector_3d&, const Vector_3d&) const;
    void drawArc (short numsegs) const;
    Vector_3d mapToSphere (const Point_2d& pt);

protected:
    Vector_2d center;
    real radius;
    Vector_3d start_vec;
    Vector_3d end_vec;
    Point_2d start_pt;
    Point_2d end_pt;

public:
    Arcball (const Point_2d&, real);
    virtual	void click (const Point_2d&);
    virtual	Matrix_3d drag (const Point_2d&);
    virtual	void drawBackground (void) const;
    virtual	void drawForeground (void) const;
};

#endif  //  _ARCBALL_
