#include "precompile.h"
#include "utility.h"
#include "vector_3d.h"
#include "camera_3d.h"
#include "transform_3d.h"

Camera_3d::Camera_3d (const Point_3d& eye, const Point_3d& to, real fov) {
    look (eye, to, fov);
}

void	Camera_3d::look (const Point_3d& e, const Point_3d& to, real fov) {
    eye = e;
    real tanfov = TAN (degreesToRadians (fov * R (0.5)));
    real distance = R (1.0) / tanfov;
    Vector_3d	vpn = (eye - to).normalize (),
        u = (Vector_3d (R (0.0), R (1.0), R (0.0)) ^ vpn).normalize (),
        v = vpn ^ u;
    Point_3d		vrp = eye + (vpn * -distance);
    viewing = Transform_3d::viewMatrix (u, v, vpn, vrp) * Transform_3d::perspective (distance);
    inverse = viewing.inverse ();
}

//------------------------------------------------------------------------------
//	compute the fov from a lens focal length and film size
//------------------------------------------------------------------------------
real	Camera_3d::lensToFov (int focal_length, real film_size) {
    real	fov = R (2.0) * ATAN2 (film_size * R (0.5), real (focal_length));
    return radiansToDegrees (fov);
}

//------------------------------------------------------------------------------
