/**
    \addtogroup 9_quad
    @{
*/

/**
    \defgroup _accessors_quad Textured Quad accessors
    \brief Functions for accessing Textured Quads data
*/

/**
    \addtogroup _accessors_quad
    @{
*/

#define QUAD_CHECK if (!mem_exists(qd, PTR_QUAD)) { return; }
#define QUAD_CHECK_RET(ret) if (!mem_exists(qd, PTR_QUAD)) { return ret; }

#include "all.h"

void        YAGL_API    Quad_SetVisible (Quad* qd, int visible)
{
    QUAD_CHECK

    qd->visible = visible;
}

int   YAGL_API    Quad_GetVisible (Quad* qd)
{
    QUAD_CHECK_RET(0)

    return qd->visible;
}


void        YAGL_API    Quad_SetPos (Quad* qd, float x, float y)
{
    QUAD_CHECK

    qd->pos.x = x;
    qd->pos.y = y;
}

void        YAGL_API    Quad_GetPos (Quad* qd, float* x, float* y)
{
    QUAD_CHECK

    if (x != NULL) { *x = qd->pos.x; }
    if (y != NULL) { *y = qd->pos.y; }
}


void        YAGL_API    Quad_SetSize (Quad* qd, float w, float h)
{
    QUAD_CHECK

    if ((w <= 0 || h <= 0) && qd->tex != NULL) {
        w = qd->tex->width;
        h = qd->tex->height;
    }

    qd->size.x = w;
    qd->size.y = h;

    __quad_keep_center(qd);
}

void        YAGL_API    Quad_GetSize (Quad* qd, float* w, float* h)
{
    QUAD_CHECK

    if (w != NULL) { *w = qd->size.x; }
    if (h != NULL) { *h = qd->size.y; }
}


void        YAGL_API    Quad_SetCenter (Quad* qd, float x, float y)
{
    QUAD_CHECK

    qd->center_enum = -1;

    qd->center.x = x;
    qd->center.y = y;
}

void        YAGL_API    Quad_GetCenter (Quad* qd, float* x, float* y)
{
    QUAD_CHECK

    if (x != NULL) { *x = qd->center.x; }
    if (y != NULL) { *y = qd->center.y; }
}


void        YAGL_API    Quad_SetAngle (Quad* qd, float angle)
{
    QUAD_CHECK

    qd->angle = angle;
}

float       YAGL_API    Quad_GetAngle (Quad* qd)
{
    QUAD_CHECK_RET(0)

    __reduce_angle(&qd->angle);
    return qd->angle;
}


void        YAGL_API    Quad_SetBlendMode (Quad* qd, eBLEND_MODE blend_mode)
{
    QUAD_CHECK

    qd->blend_mode = blend_mode;
}

int         YAGL_API    Quad_GetBlendMode (Quad* qd)
{
    QUAD_CHECK_RET(-1)

    return qd->blend_mode;
}


void        YAGL_API    Quad_SetColor (Quad* qd, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    QUAD_CHECK

    qd->color = YAGL_RGBA(r, g, b, a);
}

void        YAGL_API    Quad_GetColor (Quad* qd, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a)
{
    QUAD_CHECK

    if (r != NULL) { *r = YAGL_RGBA_R(qd->color); }
    if (g != NULL) { *g = YAGL_RGBA_G(qd->color); }
    if (b != NULL) { *b = YAGL_RGBA_B(qd->color); }
    if (a != NULL) { *a = YAGL_RGBA_A(qd->color); }
}

void        YAGL_API    Quad_SetColorEx (Quad* qd, YAGL_Color color)
{
    QUAD_CHECK

    qd->color = color;
}

YAGL_Color  YAGL_API    Quad_GetColorEx (Quad* qd)
{
    QUAD_CHECK_RET(0)

    return qd->color;
}


void        YAGL_API    Quad_SetAttachedData (Quad* qd, void* data)
{
    QUAD_CHECK

    qd->data = data;
}

void*       YAGL_API    Quad_GetAttachedData (Quad* qd)
{
    QUAD_CHECK_RET(NULL)

    return qd->data;
}

/**
    @}
*/

/**
    @}
*/
