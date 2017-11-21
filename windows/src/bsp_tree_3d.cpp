#include "precompile.h"
#include "bsp_tree_node_3d.h"

void BspTree_3d::insert (PtrToPolygonList_3d& list, hclass keep, hclass cur) {
    if (list->empty ()) return;
    if (ptrTo) {
        ptrTo->insert (list, keep);
    } else if ((cur == keep) or (keep == HC_SPANNING)) {
        setPtr (new BspTreeNode_3d (list->pop ()));
        // add ref

        if (!list->empty ()) {
            ptrTo->insert (list, HC_SPANNING);
        }
    }
}

void BspTree_3d::push (const PtrToPolygon_3d& poly, PtrToPolygonList_3d& result, hclass keep, hclass cur) {
    if (ptrTo) {
        ptrTo->push (poly, result, keep);
    } else if (cur == keep) {
        result->addToList (poly);
    }
}

void BspTree_3d::push (PtrToPolygonList_3d& list, PtrToPolygonList_3d& result, hclass keep, hclass cur) {
    if (list->empty ()) return;
    if (ptrTo) {
        ptrTo->push (list, result, keep);
    } else if (cur == keep) {
        result->append (list);
    }
}

void BspTree_3d::reduce (void) {
    if (ptrTo) {
        ptrTo->reduce ();
    }
}

void BspTree_3d::draw (const Point_3d& eye) const {
    if (ptrTo) {
        ptrTo->draw (eye);
    }
}

bool BspTree_3d::rayIntersection (const Ray_3d & r, PtrToPolygon_3d& poly_hit, Point_3d& ipt) const {
    if (ptrTo) {
        return ptrTo->rayIntersection (r, poly_hit, ipt);
    }
    return FALSE;
}

