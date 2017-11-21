#include "precompile.h"
#include "view.h"
#include "bsp_tree_3d.h"

#define moveTo(x, y) MoveToEx (offscreenDC, x, y, 0)
#define lineTo(x, y) LineTo (offscreenDC, x, y)

View* gView;																													//	the world viewer

View::View (HWND wind) :
    transformation (Matrix_3d::identity),
    inverse (Matrix_3d::identity),
    cam (Point_3d (R (0.0), R (0.0), R (6.0)), ORIGIN_3D, Camera_3d::lensToFov (60)) {
    gui = new Arcball (ORIGIN_2D, R (0.95));
    eye = cam.getEye ();
    window = wind;

    GetClientRect (window,& clientRect);
    createOffscreen ();

    ysize = (clientRect.bottom - clientRect.top) * R (0.5);
    xsize = (clientRect.right - clientRect.left) * R (0.5);
    aspect = ysize;
}

View::~View (void) {
    delete gui;
}

void View::createOffscreen () {
    HDC screenDC = GetDC (window);
    void* pixels;
    BITMAPINFO bitMapInfo;

    offscreenDC = CreateCompatibleDC (screenDC);

    bitMapInfo.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
    bitMapInfo.bmiHeader.biWidth = clientRect.right;
    bitMapInfo.bmiHeader.biHeight = clientRect.bottom;
    bitMapInfo.bmiHeader.biPlanes = 1;
    bitMapInfo.bmiHeader.biBitCount = 32;
    bitMapInfo.bmiHeader.biCompression = BI_RGB;
    bitMapInfo.bmiHeader.biSizeImage = 0;
    bitMapInfo.bmiHeader.biXPelsPerMeter = GetDeviceCaps (screenDC, LOGPIXELSX) / 72;
    bitMapInfo.bmiHeader.biYPelsPerMeter = GetDeviceCaps (screenDC, LOGPIXELSY) / 72;
    bitMapInfo.bmiHeader.biClrUsed = 0;
    bitMapInfo.bmiHeader.biClrImportant = 0;

    offscreenBitmap = CreateDIBSection (offscreenDC,& bitMapInfo, DIB_RGB_COLORS,& pixels, 0, 0);
    oldOffscreenBitmap = static_cast<HBITMAP> (SelectObject (offscreenDC, offscreenBitmap));
    ReleaseDC (window, screenDC);
}

void View::eraseOffscreen () {
    COLORREF color = RGB (255, 255, 255);
    HBRUSH brush = CreateSolidBrush (color);
    RECT rt;
    GetClientRect (window,& rt);
    FillRect (offscreenDC,& rt, brush);
    DeleteObject (brush);
}

void View::swapOffscreen () {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint (window,& ps);
    BitBlt (hdc, 0, 0, clientRect.right, clientRect.bottom, offscreenDC, 0, 0, SRCCOPY);
    //SetStretchBltMode (hdc, HALFTONE);
    //StretchBlt (hdc, 0, 0, clientRect.right, clientRect.bottom, offscreenDC, 0, 0, clientRect.right * 2, clientRect.bottom * 2, SRCCOPY);
    EndPaint (window,& ps);
}

void View::moveToPt (const Point_2d& vp) const {
    POINT p = vdcToDc (vp);
    moveTo (p.x, p.y);
}

void View::drawLineToPt (const Point_2d& vp, COLORREF strokeColor) const {
    HPEN	pen = CreatePen (PS_SOLID, 0, strokeColor);															//	make a pen for the arc
    HGDIOBJ	oldpen = SelectObject (offscreenDC, pen);																			//	select the pen

    POINT p = vdcToDc (vp);
    lineTo (p.x, p.y);

    SelectObject (offscreenDC, oldpen);																										//	restore the old pen
    DeleteObject (pen);																														//	free up the pen
}

void View::drawCircle (const Point_2d& a, const Point_2d& b, COLORREF strokeColor, COLORREF fillColor) const {
    HPEN pen = CreatePen (PS_SOLID, 0, strokeColor);														//	make a pen for the polygon outlines
    HBRUSH brush = CreateSolidBrush (fillColor);																//	make a brush for the polygon fill
    HGDIOBJ oldpen = SelectObject (offscreenDC, pen);																			//	select the pen
    HGDIOBJ oldbrush = SelectObject (offscreenDC, brush);																	//	select teh brush

    POINT p1 = vdcToDc (a);
    POINT p2 = vdcToDc (b);
    Ellipse (offscreenDC, p1.x, p2.y, p2.x + 1, p1.y + 1);

    SelectObject (offscreenDC, oldbrush);																									//	restore the old brush
    SelectObject (offscreenDC, oldpen);																										//	restore the old pen
    DeleteObject (pen);																														//	free up the pen
    DeleteObject (brush);																													//	free up the pen
}

void View::drawCrossHair (const Point_2d& vp, COLORREF strokeColor) const {
    HPEN pen = CreatePen (PS_SOLID, 0, strokeColor);																		//	make a pen for the crosshair
    HGDIOBJ oldpen = SelectObject (offscreenDC, pen);																							//	select the pen

    POINT p = vdcToDc (vp);
    moveTo (p.x - 5, p.y);
    lineTo (p.x + 6, p.y);
    moveTo (p.x, p.y - 5);
    lineTo (p.x, p.y + 6);

    SelectObject (offscreenDC, oldpen);																										//	restore the old pen
    DeleteObject (pen);																														//	free up the pen
}

void View::drawPolygon (const PtrToPolygon_3d& poly, COLORREF strokeColor, COLORREF fillColor) {
    HPEN pen = CreatePen (PS_SOLID, 0, strokeColor);																		//	make a pen for the crosshair
    HGDIOBJ oldpen = SelectObject (offscreenDC, pen);																							//	select the pen

    HBRUSH brush = CreateSolidBrush (fillColor);
    HGDIOBJ oldbrush = SelectObject (offscreenDC, brush);
    for (uint i = 0; i < poly->getCount (); i++) {
        Point_3d pt = poly->getVertex (i) * viewing;
        pts[i] = vdcToDc (Point_2d (pt[X], pt[Y]));
    }
    Polygon (offscreenDC, pts, poly->getCount ());

    SelectObject (offscreenDC, oldbrush);
    DeleteObject (brush);

    SelectObject (offscreenDC, oldpen);																										//	restore the old pen
    DeleteObject (pen);																														//	free up the pen
}

void View::drawPolygon (const PtrToPolygon_3d& poly) {
    if ((eye | poly->getPlane ()) > R (0.0)) {
        static Vector_3d light = Vector_3d (R (4.0), R (8.0), R (6.0)).normalize ();
        real shade = (poly->getPlane () | light) * R (0.8) + R (0.2);
        if (shade < R (0.3)) shade = R (0.3);
        if (shade > R (0.9)) shade = R (0.9);
        shade *= R (255.0);
        COLORREF color = RGB (int (shade), int (shade), int (shade));
        drawPolygon (poly, 0, color);
    }
}

void View::drawScene (BspTree_3d tree) {
    viewing = transformation * cam.getTransform ();
    eye = cam.getEye () * inverse;
    tree.draw (eye);

    // queue up the offscreen swap
    InvalidateRect (window, 0, false);
}

void View::handleClick (POINT where, BspTree_3d tree) {
    sum = transformation;
    gui->click (dcToVdc (where));
    gui->drag (dcToVdc (where));
    gui->drawBackground ();
    drawScene (tree);
    gui->drawForeground ();
}

void View::handleDrag (POINT where, BspTree_3d tree) {
    transformation = sum * gui->drag (dcToVdc (where));
    inverse = transformation.inverse ();
    gui->drawBackground ();
    drawScene (tree);
    gui->drawForeground ();
}

Point_2d View::dcToVdc (const POINT& p) const {
    return Point_2d ((p.x - xsize) / aspect, (p.y - ysize) / -aspect);
}

POINT View::vdcToDc (const Point_2d& p) const {
    POINT pt;
    pt.x = (short) ((p[X] * aspect) + xsize);
    pt.y = (short) ((p[Y] * -aspect) + ysize);
    return pt;
}
