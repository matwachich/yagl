/**
    \addtogroup 190_bmptext
    @{
*/

/**
    \defgroup _accessors_bmptext Bitmap text accessors
    \brief Functions for accessing Bitmap text data
*/

/**
    \addtogroup _accessors_bmptext
    @{
*/

#define BMPTXT_CHECK if (mem_exists(btxt, PTR_BMP_TEXT) == 0) { return; }
#define BMPTXT_CHECK_RET(ret) if (mem_exists(btxt, PTR_BMP_TEXT) == 0) { return ret; }

#include "all.h"

char*       YAGL_API    BmpText_GetText (BmpText* btxt)
{
    BMPTXT_CHECK_RET(NULL)

    return btxt->text;
}

void        YAGL_API    BmpText_SetFont (BmpText* btxt, BmpFont* bfnt)
{
    BMPTXT_CHECK

    btxt->font = bfnt;
}

BmpFont*    YAGL_API    BmpText_GetFont (BmpText* btxt)
{
    BMPTXT_CHECK_RET(NULL)

    return btxt->font;
}

void        YAGL_API    BmpText_SetVisible (BmpText* btxt, int visible)
{
    BMPTXT_CHECK

    btxt->visible = visible;
}

int   YAGL_API    BmpText_GetVisible (BmpText* btxt)
{
    BMPTXT_CHECK_RET(0)

    return btxt->visible;
}

void        YAGL_API    BmpText_SetMultiligne (BmpText* btxt, int multiligne)
{
    BMPTXT_CHECK

    btxt->multiligne = multiligne;
}

int   YAGL_API    BmpText_GetMultiligne (BmpText* btxt)
{
    BMPTXT_CHECK_RET(0)

    return btxt->multiligne;
}

void        YAGL_API    BmpText_SetPos (BmpText* btxt, int x, int y)
{
    BMPTXT_CHECK

    btxt->pos.x = x;
    btxt->pos.y = y;
}

void        YAGL_API    BmpText_GetPos (BmpText* btxt, int* x, int* y)
{
    BMPTXT_CHECK

    if (x != NULL) { *x = btxt->pos.x; }
    if (y != NULL) { *y = btxt->pos.y; }
}

void        YAGL_API    BmpText_SetSize (BmpText* btxt, int size)
{
    BMPTXT_CHECK

    btxt->size = size;
}

int         YAGL_API    BmpText_GetSize (BmpText* btxt)
{
    BMPTXT_CHECK_RET(0)

    return btxt->size;
}

void        YAGL_API    BmpText_SetAlign (BmpText* btxt, eALIGN align)
{
    BMPTXT_CHECK

    btxt->align = align;
}

int         YAGL_API    BmpText_GetAlign (BmpText* btxt)
{
    BMPTXT_CHECK_RET(0)

    return btxt->align;
}

void        YAGL_API    BmpText_SetAngle (BmpText* btxt, float angle)
{
    BMPTXT_CHECK

    btxt->angle = angle;
}

float       YAGL_API    BmpText_GetAngle (BmpText* btxt)
{
    BMPTXT_CHECK_RET(0)

    return btxt->angle;
}

void        YAGL_API    BmpText_SetBlendMode (BmpText* btxt, eBLEND_MODE blend_mode)
{
    BMPTXT_CHECK

    btxt->blend_mode = blend_mode;
}

int         YAGL_API    BmpText_GetBlendMode (BmpText* btxt)
{
    BMPTXT_CHECK_RET(0)

    return btxt->blend_mode;
}

void        YAGL_API    BmpText_SetColor (BmpText* btxt, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    BMPTXT_CHECK

    btxt->color = YAGL_RGBA(r, g, b, a);
}

void        YAGL_API    BmpText_GetColor (BmpText* btxt, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a)
{
    BMPTXT_CHECK

    if (r != NULL) { *r = YAGL_RGBA_R(btxt->color); }
    if (g != NULL) { *g = YAGL_RGBA_G(btxt->color); }
    if (b != NULL) { *b = YAGL_RGBA_B(btxt->color); }
    if (a != NULL) { *a = YAGL_RGBA_A(btxt->color); }
}

void        YAGL_API    BmpText_SetColorEx (BmpText* btxt, YAGL_Color color)
{
    BMPTXT_CHECK

    btxt->color = color;
}

YAGL_Color  YAGL_API    BmpText_GetColorEx (BmpText* btxt)
{
    BMPTXT_CHECK_RET(0)

    return btxt->color;
}

/**
    @}
*/

/**
    @}
*/
