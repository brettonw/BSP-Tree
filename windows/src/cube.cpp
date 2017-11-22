#include "precompile.h"
#include "cube.h"

PtrToPolygonList_3d	Cube (Matrix_3d transformation) {
    Point_3d		cube_points[8];
    //	compute the vertices
    cube_points[0] = Point_3d (R (1.0), R (1.0), R (1.0)) * transformation;
    cube_points[1] = Point_3d (R (-1.0), R (1.0), R (1.0)) * transformation;
    cube_points[2] = Point_3d (R (-1.0), R (-1.0), R (1.0)) * transformation;
    cube_points[3] = Point_3d (R (1.0), R (-1.0), R (1.0)) * transformation;
    cube_points[4] = Point_3d (R (1.0), R (1.0), R (-1.0)) * transformation;
    cube_points[5] = Point_3d (R (-1.0), R (1.0), R (-1.0)) * transformation;
    cube_points[6] = Point_3d (R (-1.0), R (-1.0), R (-1.0)) * transformation;
    cube_points[7] = Point_3d (R (1.0), R (-1.0), R (-1.0)) * transformation;

    //	now compute the polygons
    PtrToPolygonList_3d	cube_polys = new PolygonList_3d ();
    cube_polys->addToList (new Polygon_3d (cube_points, 4, 0, 1, 2, 3));
    cube_polys->addToList (new Polygon_3d (cube_points, 4, 7, 6, 5, 4));
    cube_polys->addToList (new Polygon_3d (cube_points, 4, 0, 3, 7, 4));
    cube_polys->addToList (new Polygon_3d (cube_points, 4, 0, 4, 5, 1));
    cube_polys->addToList (new Polygon_3d (cube_points, 4, 5, 6, 2, 1));
    cube_polys->addToList (new Polygon_3d (cube_points, 4, 3, 2, 6, 7));

    //	return the result
    return cube_polys;
}

