/**
    \addtogroup 100_sprite
    @{
*/

/**
    \defgroup _sprite_accessors Sprite accessors
    \brief Functions for accessing Sprite data
*/

/**
    \addtogroup _sprite_accessors
    @{
*/

#define SPR_CHECK if (!mem_exists(spr, PTR_SPRITE)) { return; }
#define SPR_CHECK_RET(ret) if (!mem_exists(spr, PTR_SPRITE)) { return ret; }

#include "all.h"

void        YAGL_API    Sprite_SetVisible (Sprite* spr, int visible)
{
    SPR_CHECK

    spr->visible = visible;
}

void        YAGL_API    Sprite_SetDynamic (Sprite* spr, int dynamic)
{
    SPR_CHECK

    spr->dynamic = dynamic;
}

int   YAGL_API    Sprite_GetVisible (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return spr->visible;
}

int   YAGL_API    Sprite_GetDynamic (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return spr->dynamic;
}

void        YAGL_API    Sprite_SetPos (Sprite* spr, float x, float y)
{
    SPR_CHECK

    spr->pos.x = x;
    spr->pos.y = y;
}

void        YAGL_API    Sprite_GetPos (Sprite* spr, float* x, float* y)
{
    SPR_CHECK

    if (x != NULL) { *x = spr->pos.x; }
    if (y != NULL) { *y = spr->pos.y; }
}

void        YAGL_API    Sprite_SetSize (Sprite* spr, float w, float h)
{
    SPR_CHECK

    if ((w <= 0 || h <= 0) && spr->tex != NULL) {
        w = spr->tex->width;
        h = spr->tex->height;
    }

    spr->size.x = w;
    spr->size.y = h;

    __sprite_keep_center(spr);
}

void        YAGL_API    Sprite_GetSize (Sprite* spr, float* w, float* h)
{
    SPR_CHECK

    if (w != NULL) { *w = spr->size.x; }
    if (h != NULL) { *h = spr->size.y; }
}

void        YAGL_API    Sprite_SetCenter (Sprite* spr, float x, float y)
{
    SPR_CHECK

    spr->center_enum = -1;

    spr->center.x = x;
    spr->center.y = y;
}

void        YAGL_API    Sprite_GetCenter (Sprite* spr, float* x, float* y)
{
    SPR_CHECK

    if (x != NULL) { *x = spr->center.x; }
    if (y != NULL) { *y = spr->center.y; }
}

void        YAGL_API    Sprite_SetAngle (Sprite* spr, float angle)
{
    SPR_CHECK

    spr->angle = angle;
}

float       YAGL_API    Sprite_GetAngle (Sprite* spr)
{
    SPR_CHECK_RET(0)

    __reduce_angle(&spr->angle);
    return spr->angle;
}

void        YAGL_API    Sprite_SetBlendMode (Sprite* spr, eBLEND_MODE blend_mode)
{
    SPR_CHECK

    spr->blend_mode = blend_mode;
}

int         YAGL_API    Sprite_GetBlendMode (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return spr->blend_mode;
}

void        YAGL_API    Sprite_SetColor (Sprite* spr, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    SPR_CHECK

    spr->color = YAGL_RGBA(r, g, b, a);
}

void        YAGL_API    Sprite_GetColor (Sprite* spr, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a)
{
    SPR_CHECK

    if (r != NULL) { *r = YAGL_RGBA_R(spr->color); }
    if (g != NULL) { *g = YAGL_RGBA_G(spr->color); }
    if (b != NULL) { *b = YAGL_RGBA_B(spr->color); }
    if (a != NULL) { *a = YAGL_RGBA_A(spr->color); }
}

void        YAGL_API    Sprite_SetColorEx (Sprite* spr, YAGL_Color color)
{
    SPR_CHECK

    spr->color = color;
}

YAGL_Color  YAGL_API    Sprite_GetColorEx (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return spr->color;
}

void        YAGL_API    Sprite_SetVel (Sprite* spr, float x, float y)
{
    SPR_CHECK

    spr->vel.x = x;
    spr->vel.y = y;
}

void        YAGL_API    Sprite_SetVelMax (Sprite* spr, float max)
{
    SPR_CHECK

    spr->vel_max = max;
}

void        YAGL_API    Sprite_GetVel (Sprite* spr, float* x, float* y)
{
    SPR_CHECK

    if (x != NULL) { *x = spr->vel.x; }
    if (y != NULL) { *y = spr->vel.y; }
}

float       YAGL_API    Sprite_GetVelLen (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return __vect_len(spr->vel.x, spr->vel.y);
}

float       YAGL_API    Sprite_GetVelAngle (Sprite* spr)
{
    SPR_CHECK_RET(0)

    float a, l;
    __cartesian_2_polar(spr->vel.x, spr->vel.y, &a, &l);

    return a;
}

float       YAGL_API    Sprite_GetVelMax (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return spr->vel_max;
}

void        YAGL_API    Sprite_SetAccel (Sprite* spr, float x, float y)
{
    SPR_CHECK

    spr->accel.x = x;
    spr->accel.y = y;
}

void        YAGL_API    Sprite_GetAccel (Sprite* spr, float* x, float* y)
{
    SPR_CHECK

    if (x != NULL) { *x = spr->accel.x; }
    if (y != NULL) { *y = spr->accel.y; }
}

float       YAGL_API    Sprite_GetAccelLen (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return __vect_len(spr->accel.x, spr->accel.y);
}

float       YAGL_API    Sprite_GetAccelAngle (Sprite* spr)
{
    SPR_CHECK_RET(0)

    float a, l;
    __cartesian_2_polar(spr->accel.x, spr->accel.y, &a, &l);

    return a;
}

void        YAGL_API    Sprite_SetInnertia (Sprite* spr, float innertia)
{
    SPR_CHECK

    spr->innertia = innertia;
}

float       YAGL_API    Sprite_GetInnertia (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return spr->innertia;
}

void        YAGL_API    Sprite_SetAVel (Sprite* spr, float avel)
{
    SPR_CHECK

    spr->a_vel = avel;
}

void        YAGL_API    Sprite_SetAVelMax (Sprite* spr, float max)
{
    SPR_CHECK

    spr->a_vel_max = max;
}

float       YAGL_API    Sprite_GetAVel (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return spr->a_vel;
}

float       YAGL_API    Sprite_GetAVelMax (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return spr->a_vel_max;
}

void        YAGL_API    Sprite_SetAAccel (Sprite* spr, float aaccel)
{
    SPR_CHECK

    spr->a_accel = aaccel;
}

float       YAGL_API    Sprite_GetAAccel (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return spr->a_accel;
}

void        YAGL_API    Sprite_SetAInnertia (Sprite* spr, float ainnertia)
{
    SPR_CHECK

    spr->a_innertia = ainnertia;
}

float       YAGL_API    Sprite_GetAInnertia (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return spr->a_innertia;
}


void        YAGL_API    Sprite_SetParentV (Sprite* spr, Sprite* spr_parent)
{
    SPR_CHECK
    if (mem_exists(spr_parent, PTR_SPRITE) == 0) { return; }

    spr->tutor_vel = spr_parent;
}

void        YAGL_API    Sprite_SetParentA (Sprite* spr, Sprite* spr_parent)
{
    SPR_CHECK
    if (mem_exists(spr_parent, PTR_SPRITE) == 0) { return; }

    spr->tutor_avel = spr_parent;
}

Sprite*     YAGL_API    Sprite_GetParentV (Sprite* spr)
{
    SPR_CHECK_RET(NULL)

    return spr->tutor_vel;
}

Sprite*     YAGL_API    Sprite_GetParentA (Sprite* spr)
{
    SPR_CHECK_RET(NULL)

    return spr->tutor_avel;
}


void        YAGL_API    Sprite_SetAttachedData (Sprite* spr, void* data)
{
    SPR_CHECK

    spr->data = data;
}

void*       YAGL_API    Sprite_GetAttachedData (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return spr->data;
}

/**
    @}
*/

/**
    @}
*/
