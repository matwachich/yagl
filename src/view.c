/**
    \addtogroup 040_view
    @{
*/

#include "all.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline void __view_rect (int x, int y, int w, int h)
{
    _engin_->view.x = x;
    _engin_->view.y = y;
    _engin_->view.w = w;
    _engin_->view.h = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(x, x + w, y + h, y);
    glMatrixMode(GL_MODELVIEW);
}

/* ------------------------------------------------------------------------- **/
/* Public functions **/

/*
Function: View_Move

Parameters:

Return:

*/
void    YAGL_API    View_Move (const int x, const int y)
{
    __view_rect(_engin_->view.x + x, _engin_->view.y + y, _engin_->view.w, _engin_->view.h);
}


/*
Function: View_SetRect

Parameters:

Return:

*/
void    YAGL_API    View_SetRect (const int x, const int y, const int w, const int h)
{
    __view_rect(x, y, w, h);
}


/*
Function: View_GetRect

Parameters:

Return:

*/
void    YAGL_API    View_GetRect (int* x, int* y, int* w, int* h)
{
    if (x != NULL) { *x = _engin_->view.x; }
    if (y != NULL) { *y = _engin_->view.y; }
    if (w != NULL) { *w = _engin_->view.w; }
    if (h != NULL) { *h = _engin_->view.h; }
}


/*
Function: View_SetCorners

Parameters:

Return:

*/
void    YAGL_API    View_SetCorners (const int x1, const int y1, const int x2, const int y2)
{
    __view_rect(x1, y1, x2 - x1, y2 - y1);
}


/*
Function: View_GetCorners

Parameters:

Return:

*/
void    YAGL_API    View_GetCorners (int* x1, int* y1, int* x2, int* y2)
{
    if (x1 != NULL) { *x1 = _engin_->view.x; }
    if (y1 != NULL) { *y1 = _engin_->view.y; }
    if (x2 != NULL) { *x2 = _engin_->view.x + _engin_->view.w; }
    if (y2 != NULL) { *y2 = _engin_->view.y + _engin_->view.h; }
}


/*
Function: View_SetCenter

Parameters:

Return:

*/
void    YAGL_API    View_SetCenter (const int x, const int y)
{
    __view_rect(x - (_engin_->view.w / 2), y - (_engin_->view.h / 2), _engin_->view.w, _engin_->view.h);
}


/*
Function: View_SetCenter

Parameters:

Return:

*/
void    YAGL_API    View_GetCenter (int* x, int* y)
{
    if (x != NULL) { *x = _engin_->view.x + (_engin_->view.w / 2); }
    if (y != NULL) { *y = _engin_->view.y + (_engin_->view.h / 2); }
}


/*
Function: View_SetSize

Parameters:

Return:

*/
void    YAGL_API    View_SetSize (const int w, const int h)
{
    __view_rect(_engin_->view.x + (_engin_->view.w / 2) - (w / 2), _engin_->view.y + (_engin_->view.h / 2) - (h / 2), w, h);
}


/*
Function: View_GetSize

Parameters:

Return:

*/
void    YAGL_API    View_GetSize (int* w, int* h)
{
    if (w != NULL) { *w = _engin_->view.w; }
    if (h != NULL) { *h = _engin_->view.h; }
}


/*
Function: View_SetZoom

Parameters:

Return:

*/
void    YAGL_API    View_SetZoom (const float factor)
{
    __view_rect(_engin_->view.x + (_engin_->view.w / 2) - ((_engin_->original_view_size.x / factor) / 2),
                _engin_->view.y + (_engin_->view.h / 2) - ((_engin_->original_view_size.y / factor) / 2),
                _engin_->original_view_size.x / factor,
                _engin_->original_view_size.y / factor);
    _engin_->current_zoom = factor;
}


/*
Function: View_AddZoom

Parameters:

Return:

*/
void    YAGL_API    View_AddZoom (float factor)
{
    factor = _engin_->current_zoom + factor;
    __view_rect(_engin_->view.x + (_engin_->view.w / 2) - ((_engin_->original_view_size.x / factor) / 2),
                _engin_->view.y + (_engin_->view.h / 2) - ((_engin_->original_view_size.y / factor) / 2),
                _engin_->original_view_size.x / factor,
                _engin_->original_view_size.y / factor);
    _engin_->current_zoom = factor;
}


/*
Function: View_GetZoom

Parameters:

Return:

*/
float  YAGL_API    View_GetZoom ()
{
    return _engin_->current_zoom;
}


/*
Function: View_ScreenToWorld

Parameters:

Return:

*/
void    YAGL_API    View_ScreenToWorld (const int scr_x, const int scr_y, int* world_x, int* world_y)
{
    *world_x = scr_x + _engin_->view.x;
    *world_y = scr_y + _engin_->view.y;
}


/*
Function: View_WorldToScreen

Parameters:

Return:

*/
void    YAGL_API    View_WorldToScreen (const int world_x, const int world_y, int* scr_x, int* scr_y)
{
    *scr_x = world_x - _engin_->view.x;
    *scr_y = world_y - _engin_->view.y;
}


/*
Function: View_PointIsVisible

Parameters:

Return:

*/
int     YAGL_API    View_PointIsVisible (const int x, const int y)
{
    if (x >= _engin_->view.x &&
        x <= _engin_->view.x + _engin_->view.w &&
        y >= _engin_->view.y &&
        y <= _engin_->view.y + _engin_->view.h) {
		return 1;
	} else {
		return 0;
	}
}

/**
    @}
*/
