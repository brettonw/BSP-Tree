#ifndef     _BSP_TREE_3D_
#include    "bsp_tree_3d.h"
#endif  //  _BSP_TREE_3D_

#ifndef     _BSP_TREE_NODE_3D_
#define     _BSP_TREE_NODE_3D_

class	BspTreeNode_3d : public CountedObject {
    friend	class	BspTree_3d;

    protected:
    Plane_3d plane;
    PtrToPolygonList_3d on;
    BspTree_3d in;
    BspTree_3d out;

    BspTreeNode_3d (const PtrToPolygon_3d& poly);
    ~BspTreeNode_3d (void);

    public:
    void		insert (PtrToPolygonList_3d& list, HClass keep);
    void		push (const PtrToPolygon_3d& poly, PtrToPolygonList_3d& result, HClass keep);
    void		push (PtrToPolygonList_3d& list, PtrToPolygonList_3d& result, HClass keep);
    void		reduce (void);
    void		draw (const Point_3d	&eye) const;
    bool		rayIntersection (const Ray_3d& r, PtrToPolygon_3d& poly_hit, Point_3d& ipt) const;
    bool		planeSearch (const Ray_3d& r, PtrToPolygon_3d& poly_hit, Point_3d& ipt) const;//	find the intersection of a ray and the plane_3d list
};

#endif  //  _BSP_TREE_NODE_3D_
