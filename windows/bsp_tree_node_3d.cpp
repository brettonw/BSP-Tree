#include "precompile.h"
#include "utility.h"
#include "bsp_tree_node_3d.h"

BspTreeNode_3d::BspTreeNode_3d (const PtrToPolygon_3d& poly) {
    plane = poly->getPlane ();
    on = new PolygonList_3d ();
    on->addToList (poly);
}

BspTreeNode_3d::~BspTreeNode_3d (void) {}

void BspTreeNode_3d::insert (PtrToPolygonList_3d& list, HClass keep) {
    PtrToPolygonList_3d	inside (new PolygonList_3d ());
    PtrToPolygonList_3d outside (new PolygonList_3d ());
    PtrToPolygon_3d		poly, inp, outp;
    for (poly = list->pop (); poly.getPtr (); poly = list->pop ()) {
        HClass	sgn = Polygon_3d::Split (poly, plane, inp, outp);
        if (sgn == HC_ON)
            on->addToList (poly);
        else {
            if ((sgn == HC_IN) || (sgn == HC_SPANNING))
                inside->addToList (inp);
            if ((sgn == HC_OUT) || (sgn == HC_SPANNING))
                outside->addToList (outp);
        }
    }
    if (!inside->empty ())
        in.insert (inside, keep, HC_IN);
    if (!outside->empty ())
        out.insert (outside, keep, HC_OUT);
}

void BspTreeNode_3d::push (const PtrToPolygon_3d& poly, PtrToPolygonList_3d& result, HClass keep) {
    PtrToPolygonList_3d	inside (new PolygonList_3d ());
    PtrToPolygonList_3d outside (new PolygonList_3d ());
    PtrToPolygon_3d	inp, outp;
    HClass	sgn = Polygon_3d::Split (poly, plane, inp, outp);
    if (sgn == HC_ON)
        result->addToList (poly);
    else {
        if ((sgn == HC_IN) || (sgn == HC_SPANNING))
            in.push (inp, result, keep, HC_IN);
        if ((sgn == HC_OUT) || (sgn == HC_SPANNING))
            out.push (outp, result, keep, HC_OUT);
    }
}

void BspTreeNode_3d::push (PtrToPolygonList_3d& list, PtrToPolygonList_3d& result, HClass keep) {
    PtrToPolygonList_3d	inside (new PolygonList_3d ());
    PtrToPolygonList_3d outside (new PolygonList_3d ());
    PtrToPolygon_3d		poly, inp, outp;
    for (poly = list->pop (); poly.getPtr (); poly = list->pop ()) {
        HClass	sgn = Polygon_3d::Split (poly, plane, inp, outp);
        if (sgn == HC_ON)
            result->addToList (poly);
        else {
            if ((sgn == HC_IN) || (sgn == HC_SPANNING))
                inside->addToList (inp);
            if ((sgn == HC_OUT) || (sgn == HC_SPANNING))
                outside->addToList (outp);
        }
    }
    if (!inside->empty ())
        in.push (inside, result, keep, HC_IN);
    if (!outside->empty ())
        out.push (outside, result, keep, HC_OUT);
}

void BspTreeNode_3d::reduce (void) {
    PtrToPolygonList_3d	results (new PolygonList_3d ());
    PtrToPolygonList_3d boundary (new PolygonList_3d ());
    for (PtrToPolygon_3d poly = on->pop (); poly.getPtr (); poly = on->pop ()) {
        if (FABS (poly->getPlane ()[W] + plane[W]) > EPSILON) {
            in.push (poly, results, HC_IN, HC_IN);
            out.push (results, boundary, HC_OUT, HC_OUT);
        } else {
            out.push (poly, results, HC_OUT, HC_OUT);
            in.push (results, boundary, HC_IN, HC_IN);
        }
    }
    on = boundary;
    in.reduce ();
    out.reduce ();
}

void BspTreeNode_3d::draw (const Point_3d &eye) const {
    real	sgn = eye | plane;
    if (sgn < R (0.0)) {
        out.draw (eye);
        on->draw ();
        in.draw (eye);
    } else {
        in.draw (eye);
        on->draw ();
        out.draw (eye);
    }
}

bool BspTreeNode_3d::rayIntersection (const Ray_3d& r, PtrToPolygon_3d& poly_hit, Point_3d& ipt) const {
    real	dist = r.getOrigin () | plane,
        costheta = r.getDirection () | plane;
    if (dist > EPSILON) {
        if (out.rayIntersection (r, poly_hit, ipt)) return TRUE;
        if (costheta < -EPSILON) {
            if (planeSearch (r, poly_hit, ipt)) return TRUE;
            return in.rayIntersection (r, poly_hit, ipt);
        }
    } else if (dist < -EPSILON) {
        if (in.rayIntersection (r, poly_hit, ipt)) return TRUE;
        if (costheta > EPSILON) {
            if (planeSearch (r, poly_hit, ipt)) return TRUE;
            return out.rayIntersection (r, poly_hit, ipt);
        }
    } else {
        if (costheta < -EPSILON)
            return in.rayIntersection (r, poly_hit, ipt);
        else if (costheta > EPSILON)
            return out.rayIntersection (r, poly_hit, ipt);
    }
    return FALSE;
}

bool	BspTreeNode_3d::planeSearch (const Ray_3d& r, PtrToPolygon_3d& poly_hit, Point_3d& ipt) const {
    real	dist = plane.rayIntersection (r);
    if (dist > R (0.0)) {
        ipt = r.intersectionPoint (dist);
        if (on->getBoundingBox ().contains (ipt)) {
            /*
            iterator	entry (on);
            for (polyptr poly = entry (); poly (); poly = entry ())
            if (poly->Contains (ipt))
            {
            poly_hit = poly;
            return TRUE;
            }
            */
        }
    }
    return FALSE;
}
