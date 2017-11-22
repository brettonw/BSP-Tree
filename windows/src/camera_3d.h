#ifndef     _POINT_3D_
#include    "point_3d.h"
#endif  //  _POINT_3D_

#ifndef     _MATRIX_3D_
#include    "matrix_3d.h"
#endif  //  _MATRIX_3D_

#ifndef     _CAMERA_3D_
#define     _CAMERA_3D_

class	Camera_3d {
    protected:
    Point_3d eye;
    Matrix_3d viewing;
    Matrix_3d inverse;

    public:
    Camera_3d (const Point_3d& eye, const Point_3d& to, real fov);
    void look (const Point_3d& eye, const Point_3d& to, real fov);
    const Matrix_3d& getTransform (void) const;
    const Matrix_3d& getInverse (void) const;
    const Point_3d& getEye (void) const;

    // compute the field of view (FOV) from a film size (mm - measured 
    // diagonally) and lens focal length (mm)
    static real	lensToFov (int focal_length = 50, real film_size = 43.26661531);
};

inline const Matrix_3d& Camera_3d::getTransform (void) const {
    return viewing;
}

inline const Matrix_3d& Camera_3d::getInverse (void) const {
    return inverse;
}

inline const Point_3d& Camera_3d::getEye (void) const {
    return eye;
}

#endif  //  _CAMERA_3D_
