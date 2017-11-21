#ifndef     _POINT_3D_
#include    "point_3d.h"
#endif  //  _POINT_3D_

#ifndef	    _BOUND_3D_
#define     _BOUND_3D_

class	Bound_3d {
    protected:
    Point_3d max;
    Point_3d min;

    public:
    Bound_3d (void);
    void operator += (const Bound_3d& box);
    void operator += (const Point_3d& pt);
    bool contains (const Point_3d& pt) const;
};


#endif  //  _BOUND_3D_
