#include	"precompile.h"
#include	"view.h"
#include	"cube.h"
#include	"bsp_tree_3d.h"
#include	"transform_3d.h"

#define	CLASS_NAME L"BSP Tree Demo"

static	MSG			gMessage;
static	HWND		gWindow;
static	bool		gClick = FALSE;
static	bool		gDrawn;
static  BspTree_3d  gWorld;

PtrToPolygonList_3d	Extrude (const Point_3d* pts, int size, const Vector_3d& extrude) {
    Point_3d*   all_pts = new Point_3d[size * 2];

    for (int i = 0; i < size; ++i) {
        all_pts[i] = pts[i];
        all_pts[size + ((size - 1) - i)] = pts[i] + extrude;
    }

    int         num_faces = size + 2;
    PtrToPolygonList_3d extruded_polys = new PolygonList_3d;

    extruded_polys->addToList (new Polygon_3d (all_pts, (uint) size, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12));
    extruded_polys->addToList (new Polygon_3d (all_pts, (uint) size, size, size + 1, size + 2, size + 3, size + 4, size + 5, size + 6, size + 7, size + 8, size + 9, size + 10, size + 11, size + 12));

    for (int i = 0; i < size; ++i) {
        int h = (i + 1) % size;
        int j = size + ((size - 1) - i);
        int k = size + ((size - 1) - h);
        extruded_polys->addToList (new Polygon_3d (all_pts, 4, h, i, j, k));
    }

    delete[] all_pts;

    return extruded_polys;
}


void	InitializeModel (void) {
    //gWorld = BspTree;

#if 1
    Point_3d		house_pts[5];
    house_pts[0] = Point_3d(R (-1.0), R (-1.0), R (-1.0));
    house_pts[1] = Point_3d(R (-1.0), R (0.5), R (-1.0));
    house_pts[2] = Point_3d(R (0.0), R (1.5), R (-1.0));
    house_pts[3] = Point_3d(R (1.0), R (0.5), R (-1.0));
    house_pts[4] = Point_3d(R (1.0), R (-1.0), R (-1.0));
    PtrToPolygonList_3d house = Extrude(house_pts, 5, Vector_3d(R(0.0), R(0.0), R(2.0)));
    gWorld.insert (house, HC_OUT, HC_OUT);


    Point_3d		chimney_pts[5];
    chimney_pts[0] = Point_3d(R (-1.0), R (-1.0), R (-1.0));
    chimney_pts[1] = Point_3d(R (-1.0), R (0.5), R (-1.0));
    chimney_pts[2] = Point_3d(R (0.0), R (1.5), R (-1.0));
    chimney_pts[3] = Point_3d(R (1.0), R (0.5), R (-1.0));
    chimney_pts[4] = Point_3d(R (1.0), R (-1.0), R (-1.0));
    PtrToPolygonList_3d chimney = Extrude(chimney_pts, 5, Vector_3d(R(0.0), R(0.0), R(1.0)));
    gWorld.insert(
        Cube(
            Transform_3d::scale(R(-1.5), R(-0.55), R(-1.5)) *
            Transform_3d::translate(R(0.75), R(0.0), R(0.0))
        ),
        HC_IN, HC_SPANNING);

    gWorld.reduce();
#endif


#if 0
    gWorld.insert (Cube (IDENTITY_MATRIX), HC_OUT, HC_OUT);
    gWorld.insert (
        Cube (
            Transform_3d::scale (R (-1.5), R (-0.875), R (-1.5)) *
            Transform_3d::translate (R (0.625), R (0.0), R (0.0))
        ),
        HC_IN, HC_SPANNING);
    gWorld.reduce ();
    gWorld.insert (
        Cube (
            Transform_3d::scale (R (0.75), R (1.25), R (0.125)) *
            Transform_3d::rotateY (R (-15.0)) *
            Transform_3d::translate (R (0.5), R (0.0), R (0.0))
        ),
        HC_OUT, HC_SPANNING);
#endif

#if 0
    Point_3d		g_points[4];																										//	eight vertices    g_points[0] = Point_3d(R(1.25), R(-0.5), R(1.25));    g_points[1] = Point_3d(R(1.25), R(-0.5), R(-1.25));    g_points[2] = Point_3d(R(-1.25), R(-0.5), R(-1.25));    g_points[3] = Point_3d(R(-1.25), R(-0.5), R(1.25));    PtrToPolygonList_3d	ground = new PolygonList_3d;    ground->addToList(new Polygon_3d(g_points, 4, 0, 1, 2, 3));    gWorld.insert(ground, HC_OUT, HC_OUT);    gWorld.insert(Cube(Transform_3d::scale(R(0.25), R(1.0), R(1.0)) * Transform_3d::rotateZ(R(-10.0)) * Transform_3d::translate(R(0.5), R(0.0), R(0.0))), HC_OUT, HC_OUT);    gWorld.insert(Cube(Transform_3d::scale(R(0.25), R(1.0), R(1.0)) * Transform_3d::rotateZ(R(10.0)) * Transform_3d::translate(R(-0.5), R(0.0), R(0.0))), HC_OUT, HC_OUT);    gWorld.insert(Cube(Transform_3d::scale(R(-1.0), R(-0.5), R(-0.5))), HC_IN, HC_OUT);    gWorld.reduce();    //gWorld.insert(Triangle(Transform_3d::scale(R(0.5), R(0.5), R(1.0)) * Transform_3d::rotateY(R(90.0)) * Transform_3d::translate(R(0.0), R(0.75), R(-0.75))), HC_OUT, HC_OUT);    //gWorld.insert(Triangle(Transform_3d::scale(R(0.5), R(0.5), R(1.0)) * Transform_3d::rotateY(R(-90.0)) * Transform_3d::translate(R(0.0), R(0.75), R(0.75))), HC_OUT, HC_OUT);    gWorld.insert(Cube(Transform_3d::scale(R(0.75), R(0.025), R(0.9)) * Transform_3d::rotateY(R(90.0)) * Transform_3d::translate(R(0.0), R(-0.225), R(0.0))), HC_OUT, HC_OUT);    gWorld.insert(Cube(Transform_3d::scale(R(-0.4), R(-0.25), R(-0.4)) * Transform_3d::translate(R(0.0), R(0.5), R(0.0))), HC_IN, HC_OUT);    gWorld.reduce();    gWorld.insert(Cube(Transform_3d::scale(R(0.25), R(0.025), R(0.0125)) * Transform_3d::translate(R(0.25), R(-0.0125), R(0.0)) * Transform_3d::rotateZ(R(-10.0)) * Transform_3d::translate(R(0.0), R(1.125), R(-0.2))), HC_OUT, HC_OUT);    gWorld.insert(Cube(Transform_3d::scale(R(0.25), R(0.025), R(0.0125)) * Transform_3d::translate(R(-0.25), R(-0.0125), R(0.0)) * Transform_3d::rotateZ(R(10.0)) * Transform_3d::translate(R(0.0), R(1.125), R(-0.2))), HC_OUT, HC_OUT);    gWorld.insert(Cube(Transform_3d::scale(R(0.25), R(0.025), R(0.0125)) * Transform_3d::translate(R(0.25), R(-0.0125), R(0.0)) * Transform_3d::rotateZ(R(-10.0)) * Transform_3d::translate(R(0.0), R(1.125), R(-0.1))), HC_OUT, HC_OUT);    gWorld.insert(Cube(Transform_3d::scale(R(0.25), R(0.025), R(0.0125)) * Transform_3d::translate(R(-0.25), R(-0.0125), R(0.0)) * Transform_3d::rotateZ(R(10.0)) * Transform_3d::translate(R(0.0), R(1.125), R(-0.1))), HC_OUT, HC_OUT);    gWorld.insert(Cube(Transform_3d::scale(R(0.25), R(0.025), R(0.0125)) * Transform_3d::translate(R(0.25), R(-0.0125), R(0.0)) * Transform_3d::rotateZ(R(-10.0)) * Transform_3d::translate(R(0.0), R(1.125), R(0.0))), HC_OUT, HC_OUT);    gWorld.insert(Cube(Transform_3d::scale(R(0.25), R(0.025), R(0.0125)) * Transform_3d::translate(R(-0.25), R(-0.0125), R(0.0)) * Transform_3d::rotateZ(R(10.0)) * Transform_3d::translate(R(0.0), R(1.125), R(0.0))), HC_OUT, HC_OUT);    gWorld.insert(Cube(Transform_3d::scale(R(0.25), R(0.025), R(0.0125)) * Transform_3d::translate(R(0.25), R(-0.0125), R(0.0)) * Transform_3d::rotateZ(R(-10.0)) * Transform_3d::translate(R(0.0), R(1.125), R(0.1))), HC_OUT, HC_OUT);    gWorld.insert(Cube(Transform_3d::scale(R(0.25), R(0.025), R(0.0125)) * Transform_3d::translate(R(-0.25), R(-0.0125), R(0.0)) * Transform_3d::rotateZ(R(10.0)) * Transform_3d::translate(R(0.0), R(1.125), R(0.1))), HC_OUT, HC_OUT);    gWorld.insert(Cube(Transform_3d::scale(R(0.25), R(0.025), R(0.0125)) * Transform_3d::translate(R(0.25), R(-0.0125), R(0.0)) * Transform_3d::rotateZ(R(-10.0)) * Transform_3d::translate(R(0.0), R(1.125), R(0.2))), HC_OUT, HC_OUT);    gWorld.insert(Cube(Transform_3d::scale(R(0.25), R(0.025), R(0.0125)) * Transform_3d::translate(R(-0.25), R(-0.0125), R(0.0)) * Transform_3d::rotateZ(R(10.0)) * Transform_3d::translate(R(0.0), R(1.125), R(0.2))), HC_OUT, HC_OUT);
#endif
}

LRESULT	WinProc (HWND window, UINT message, WPARAM wpar, LPARAM lpar) {
    switch (message) {
        case WM_CREATE:
            break;
        case WM_ACTIVATE:
            gDrawn = FALSE;
            break;
        case WM_PAINT:
            gView->swapOffscreen ();
            break;
        case WM_MOUSEMOVE:
            if (gClick) {
                POINT	pt;
                pt.x = LOWORD (lpar);
                pt.y = HIWORD (lpar);
                gView->eraseOffscreen ();
                gView->handleDrag (pt, gWorld);
            }
            break;
        case WM_LBUTTONDOWN:
        {
            ShowCursor (FALSE);
            gClick = TRUE;
            POINT	pt;
            pt.x = LOWORD (lpar);
            pt.y = HIWORD (lpar);
            gView->eraseOffscreen ();
            gView->handleClick (pt, gWorld);
        }
        return 0;
        case WM_LBUTTONUP:
            ShowCursor (TRUE);
            gClick = FALSE;
            gView->eraseOffscreen ();
            gView->drawScene (gWorld);
            return 0;
        case WM_KEYDOWN:
            if (wpar == VK_ESCAPE) {
                delete gView;
                PostMessage (window, WM_CLOSE, 0, 0);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage (0);
            break;
    }
    return DefWindowProc (window, message, wpar, lpar);
}

static	void	Open (HINSTANCE instance, int show) {
    InitializeModel ();
    WNDCLASS	wClass;
    wClass.style = CS_BYTEALIGNCLIENT | CS_OWNDC;
    wClass.lpfnWndProc = WinProc;
    wClass.cbClsExtra = 0;
    wClass.cbWndExtra = 0;
    wClass.hInstance = instance;
    wClass.hIcon = LoadIcon (instance, IDI_APPLICATION);
    wClass.hCursor = LoadCursor (0, IDC_ARROW);
    wClass.hbrBackground = 0;
    wClass.lpszMenuName = CLASS_NAME;
    wClass.lpszClassName = CLASS_NAME;
    RegisterClass (&wClass);
    gWindow = CreateWindowEx (WS_EX_TOPMOST, CLASS_NAME, CLASS_NAME, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT, 0, 0, instance, 0);//	create the window
    ShowWindow (gWindow, show);
    gView = new View (gWindow);
    UpdateWindow (gWindow);
    SetFocus (gWindow);
}

static	void	Loop (void) {
    bool	done = FALSE;
    while (!done) {
        if (PeekMessage (&gMessage, 0, 0, 0, PM_NOREMOVE)) {
            if (GetMessage (&gMessage, gWindow, 0, 0) == TRUE)
                DispatchMessage (&gMessage);
            else
                done = TRUE;
        } else {
            if (!gDrawn) {
                gView->eraseOffscreen ();
                gView->drawScene (gWorld);
                gDrawn = TRUE;
            } else
                WaitMessage ();
        }
    }
}

static void	Close (void) {}

int PASCAL WinMain (HINSTANCE inst, HINSTANCE prev, LPSTR cmdLine, int show) {
    Open (inst, show);
    Loop ();
    Close ();
    return TRUE;
}


