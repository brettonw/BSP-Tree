#ifndef     _ARCBALL_
#include	"arcball.h"
#endif  //  _ARCBALL_

#ifndef     _CAMERA_3D_
#include	"camera_3d.h"
#endif  //  _CAMERA_3D_

#ifndef     _BSP_TREE_3D_
#include	"bsp_tree_3d.h"
#endif  //  _BSP_TREE_3D_

#ifndef     _VIEW_
#define     _VIEW_

#define WIDTH   640
#define HEIGHT  480

class View {
    protected:
    // map screen coordinates (dc) to virtual device coordinates (vdc) and back
    Point_2d dcToVdc (const POINT& p) const;
    POINT vdcToDc (const Point_2d& p) const;

    void createOffscreen ();

    protected:
    Camera_3d cam;
    bool cull;
    Arcball* gui;
    Matrix_3d sum;
    Matrix_3d transformation;
    Matrix_3d inverse;
    Matrix_3d viewing;
    real xsize;
    real ysize;
    real aspect;
    Point_3d eye;
    POINT pts[128];
    HWND window;
    RECT clientRect;

    HDC offscreenDC;
    HBITMAP offscreenBitmap;
    HBITMAP oldOffscreenBitmap;

    public:
    View (HWND window);
    ~View (void);
    void moveToPt (const Point_2d& pt) const;
    void drawLineToPt (const Point_2d& pt, COLORREF strokeColor) const;
    void drawCircle (const Point_2d& a, const Point_2d& b, COLORREF strokeColor, COLORREF fillColor) const;
    void drawCrossHair (const Point_2d& p, COLORREF strokeColor) const;
    void drawPolygon (const PtrToPolygon_3d& poly, COLORREF strokeColor, COLORREF fillColor);
    void drawPolygon (const PtrToPolygon_3d& poly);
    void drawScene (BspTree_3d tree);
    void handleClick (POINT where, BspTree_3d tree);
    void handleDrag (POINT where, BspTree_3d tree);

    void eraseOffscreen ();
    void swapOffscreen ();
};

extern View* gView;																													//	the world viewer

#endif  //  _VIEW_
