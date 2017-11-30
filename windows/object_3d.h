#ifndef     _COUNTED_OBJECT_
#include    "counted_object.h"
#endif  //  _COUNTED_OBJECT_

#ifndef	    _RAY_3D_
#include    "ray_3d.h"
#endif  //  _RAY_3D_

#ifndef     _OBJECT_3D_
#define     _OBJECT_3D_

class	Object_3d : public CountedObject {
    public:
    Object_3d (void) {}
    virtual	~Object_3d (void);
    virtual	real rayIntersection (const Ray_3d& r) const = 0;
};

#endif  //  _OBJECT_3D_
