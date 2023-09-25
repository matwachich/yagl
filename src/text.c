/**
    \addtogroup 190_bmptext
    @{
*/

#define BMPTXT_CHECK if (mem_exists(btxt, PTR_BMP_TEXT) == 0) { return; }
#define BMPTXT_CHECK_RET(ret) if (mem_exists(btxt, PTR_BMP_TEXT) == 0) { return ret; }

#include <string.h>

#include "all.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline void __bmpText_SetText (BmpText* btxt, const char text[])
{
    btxt->text = realloc(btxt->text, (strlen(text) + 1) * sizeof(char));
    if (btxt->text == NULL) { __DEBUG__("Unable to assign text for BmpText. (Out of memory)", 2); }
    sprintf(btxt->text, "%s", text);
}

/* ------------------------------------------------------------------------- **/
/* Public functions **/

/*
Function: BmpText_Create

Parameters:

Return:

*/
BmpText*   YAGL_API    BmpText_Create (BmpFont* bfnt, const char text[], unsigned int size, int multiligne)
{
    BmpText* btxt = (BmpText*)mem_alloc(sizeof(BmpText), PTR_BMP_TEXT);
    if (btxt == NULL) {
        __DEBUG__("Unable to create BmpText. (Out of memory)", 2);
    }

    btxt->visible = 1;
    btxt->text = NULL;
    __bmpText_SetText(btxt, text);
    btxt->font = bfnt;
	btxt->size = size;
	btxt->multiligne = multiligne;
	btxt->pos.x = 0;
	btxt->pos.y = 0;
	btxt->align = ALIGN_LEFT;
	btxt->angle = 0;
	btxt->color = YAGL_RGBA(255,255,255,255);
	btxt->blend_mode = BLEND_ALPHA;

	return btxt;
}

/*
Function: BmpText_IsBmpText

Parameters:

Return:

*/
int   YAGL_API    BmpText_IsBmpText (BmpText* btxt)
{
    return mem_exists(btxt, PTR_BMP_TEXT);
}

/*
Function: BmpText_Destroy

Parameters:

Return:

*/
int  YAGL_API    BmpText_Destroy (BmpText* btxt)
{
    BMPTXT_CHECK_RET(0)

    if (btxt->text != NULL) { free(btxt->text); }
    return mem_free(btxt, PTR_BMP_TEXT);
}

/*
Function: BmpText_SetText

Parameters:

Return:

*/
void        YAGL_API    BmpText_SetText (BmpText* btxt, const char text[])
{
    BMPTXT_CHECK

    __bmpText_SetText(btxt, text);
}

/*
Function: BmpText_GetLen

Parameters:

Return:

*/
int     YAGL_API    BmpText_GetLen (BmpText* btxt)
{
    BMPTXT_CHECK_RET(-1)

    return __bmpFont_Measure(btxt->font, btxt->text, btxt->size);
}

/*
Function: BmpText_Draw

Parameters:

Return:

*/
void    YAGL_API    BmpText_Draw (BmpText* btxt)
{
    BMPTXT_CHECK
    if (btxt->font == NULL) { return; }

    glColor4ubv((GLubyte*)&btxt->color);
    __set_blend_mode(btxt->blend_mode);

	if (btxt->multiligne == 0) {
		__bmpFont_Print(btxt->font, btxt->text, btxt->pos.x, btxt->pos.y, btxt->size, btxt->align, btxt->angle);
	} else {
		__bmpFont_PrintLines(btxt->font, btxt->text, btxt->pos.x, btxt->pos.y, btxt->size, btxt->align, btxt->angle);
	}
}

/**
    @}
*/
