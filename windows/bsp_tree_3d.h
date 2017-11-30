#ifndef	    _POLYGON_LIST_3D_
#include    "polygon_list_3d.h"
#endif  //  _POLYGON_LIST_3D_

#ifndef     _BSP_TREE_3D_
#define     _BSP_TREE_3D_

MAKE_PTR_TO (BspTreeNode_3d);

class	BspTree_3d : public PtrToBspTreeNode_3d {

    public:
    void insert (PtrToPolygonList_3d& list, HClass keep, HClass cur);
    void push (const PtrToPolygon_3d& poly, PtrToPolygonList_3d& result, HClass keep, HClass cur);
    void push (PtrToPolygonList_3d& list, PtrToPolygonList_3d& result, HClass keep, HClass cur);
    void reduce (void);
    void draw (const Point_3d& eye) const;
    bool rayIntersection (const Ray_3d& r, PtrToPolygon_3d& poly_hit, Point_3d& ipt) const;
};

#endif  //  _BSP_TREE_3D_
