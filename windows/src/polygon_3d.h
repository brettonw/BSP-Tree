#ifndef     _PTR_TO_H_
#include    "ptr_to.h"
#endif  //  _PTR_TO_H_

#ifndef     _PLANE_3D_
#include    "plane_3d.h"
#endif  //  _PLANE_3D_

#ifndef     _POLYGON_3D_
#define     _POLYGON_3D_

MAKE_PTR_TO (Polygon_3d);

enum HClass { HC_IN = -1, HC_ON = 0, HC_OUT = 1, HC_SPANNING = 2 };

class Polygon_3d : public Object_3d {
    protected:
    Plane_3d plane;
    uint count;
    Point_3d* points;

    public:
    Polygon_3d (Point_3d* buffer, uint count, int a, ...);
    Polygon_3d (Point_3d* buffer, uint count);
    virtual	~Polygon_3d (void);
    uint getCount (void) const;
    const Point_3d& getVertex (int i) const;
    const Plane_3d& getPlane (void) const;
    Vector_3d normal (void) const;
    bool contains (const Point_3d& pt) const;
    void invert (void);
    virtual	real rayIntersection (const Ray_3d& r) const;

    static HClass Split (const PtrToPolygon_3d&, const Plane_3d&, PtrToPolygon_3d&, PtrToPolygon_3d&);
};

inline uint Polygon_3d::getCount (void) const {
    return count;
}

inline const Point_3d& Polygon_3d::getVertex (int i) const {
    return points[i];
}

inline const Plane_3d& Polygon_3d::getPlane (void) const {
    return plane;
}

#endif  //  _POLYGON_3D_
