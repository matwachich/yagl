/**
    \addtogroup 080_texture_map
    @{
*/

#include "all.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline void __texture_map_get (TextureMap* tex_map, unsigned int rect_id, Texture** tex, int* rect_x, int* rect_y, int* rect_w, int* rect_h)
{
    if (tex_map->count == 0 || rect_id < 1 || rect_id > tex_map->count) {
        if (tex != NULL) { *tex = NULL; }
        if (rect_x != NULL) { *rect_x = 0; }
        if (rect_y != NULL) { *rect_y = 0; }
        if (rect_w != NULL) { *rect_w = 0; }
        if (rect_h != NULL) { *rect_h = 0; }
        return;
    }

    TextureMapElem* current = tex_map->first;
    int iter = 1;

    do {
        if (iter == rect_id) {
            if (tex != NULL) { *tex = tex_map->tex; }
            if (rect_x != NULL) { *rect_x = current->x; }
            if (rect_y != NULL) { *rect_y = current->y; }
            if (rect_w != NULL) { *rect_w = current->w; }
            if (rect_h != NULL) { *rect_h = current->h; }
            return;
        }

        current = current->next;
        iter++;
    } while (current != NULL);
}

inline void __texture_map_empty (TextureMap* tex_map)
{
    if (tex_map->count == 0) { return; }

    TextureMapElem* current = tex_map->first;
    TextureMapElem* tmp = NULL;

    do {
        tmp = current;
        current = current->next;
        free(tmp);
    } while (current != NULL);

    tex_map->count = 0;
}

/* ------------------------------------------------------------------------- **/
/* Public functions **/

/*
Function: TextureMap_Create

Parameters:

Return:

*/
TextureMap*     YAGL_API    TextureMap_Create (const char filepath[], eTEXTURE_CHANNELS channels)
{
    TextureMap* tex_map = mem_alloc(sizeof(TextureMap), PTR_TEXTURE_MAP);
    if (tex_map == NULL) {
        __DEBUG__("Unable to create texture map! (Out of memory)", 2);
    }

    tex_map->tex = Texture_Create(filepath, channels);
    tex_map->count = 0;
    tex_map->first = NULL;
    tex_map->last = NULL;

    return tex_map;
}

/*
Function: TextureMap_CreateFromTexture

Parameters:

Return:

*/
TextureMap*     YAGL_API    TextureMap_CreateFromTexture (Texture* tex)
{
    TextureMap* tex_map = mem_alloc(sizeof(TextureMap), PTR_TEXTURE_MAP);
    if (tex_map == NULL) {
        __DEBUG__("Unable to create texture map! (Out of memory)", 2);
    }

    tex_map->tex = tex;
    tex_map->count = 0;
    tex_map->first = NULL;
    tex_map->last = NULL;

    return tex_map;
}

/*
Function: TextureMap_IsTextureMap

Parameters:

Return:

*/
int       YAGL_API    TextureMap_IsTextureMap (TextureMap* tex_map)
{
    return mem_exists(tex_map, PTR_TEXTURE_MAP);
}

/*
Function: TextureMap_Destroy

Parameters:

Return:

*/
int       YAGL_API    TextureMap_Destroy (TextureMap* tex_map, int free_tex)
{
    if (mem_exists(tex_map, PTR_TEXTURE_MAP) == 0) { return 0; }

    if (free_tex != 0) {
        Texture_Destroy(tex_map->tex);
    }

    __texture_map_empty(tex_map);
    mem_free(tex_map, PTR_TEXTURE_MAP);

    return 1;
}


/*
Function: TextureMap_SetTexture

Parameters:

Return:

*/
void            YAGL_API    TextureMap_SetTexture (TextureMap* tex_map, Texture* tex)
{
    if (mem_exists(tex_map, PTR_TEXTURE_MAP) == 0 || mem_exists(tex, PTR_TEXTURE) == 0) { return; }

    tex_map->tex = tex;
}

/*
Function: TextureMap_GetTexture

Parameters:

Return:

*/
Texture*        YAGL_API    TextureMap_GetTexture (TextureMap* tex_map)
{
    if (mem_exists(tex_map, PTR_TEXTURE_MAP) == 0) { return NULL; }

    return tex_map->tex;
}


/*
Function: TextureMap_SetParameter

Parameters:

Return:

*/
void            YAGL_API    TextureMap_SetParameter (TextureMap* tex_map, int flag, int value)
{
    if (mem_exists(tex_map, PTR_TEXTURE_MAP) == 0) { return; }

    Texture_SetParameter(tex_map->tex, flag, value);
}

/*
Function: TextureMap_SetDefaultParameter

Parameters:

Return:

*/
void            YAGL_API    TextureMap_SetDefaultParameter (TextureMap* tex_map)
{
    if (mem_exists(tex_map, PTR_TEXTURE_MAP) == 0) { return; }

    Texture_SetDefaultParameter(tex_map->tex);
}

/*
Function: TextureMap_GetSize

Parameters:

Return:

*/
void            YAGL_API    TextureMap_GetSize (TextureMap* tex_map, int* w, int* h)
{
    if (mem_exists(tex_map, PTR_TEXTURE_MAP) == 0) { return; }

    Texture_GetSize(tex_map->tex, w, h);
}


/*
Function: TextureMap_AddRect

Parameters:

Return:

*/
int             YAGL_API    TextureMap_AddRect (TextureMap* tex_map, int rect_x, int rect_y, int rect_w, int rect_h)
{
    if (mem_exists(tex_map, PTR_TEXTURE_MAP) == 0) { return -1; }

    TextureMapElem* elem = malloc(sizeof(TextureMapElem));
    if (elem == NULL) {
        __DEBUG__("Unable to create texture map element! (Out of memory)", 2);
    }

    elem->x = rect_x;
    elem->y = rect_y;
    elem->w = rect_w;
    elem->h = rect_h;

    elem->next = NULL;

    if (tex_map->first == NULL) {
        tex_map->first = elem;
    }
    if (tex_map->last != NULL) {
        tex_map->last->next = elem;
    }
    tex_map->last = elem;

    tex_map->count++;

    return tex_map->count;
}

/*
Function: TextureMap_GetRect

Parameters:

Return:

*/
void            YAGL_API    TextureMap_GetRect (TextureMap* tex_map, unsigned int rect_id, int* rect_x, int* rect_y, int* rect_w, int* rect_h)
{
    if (mem_exists(tex_map, PTR_TEXTURE_MAP) == 0) { return; }

    if (tex_map->count == 0) { return; }
    if (rect_id < 1 || rect_id > tex_map->count) { return; }

    TextureMapElem* current = tex_map->first;
    int iter = 1;

    do {
        if (iter == rect_id) {
            if (rect_x != NULL) { *rect_x = current->x; }
            if (rect_y != NULL) { *rect_y = current->y; }
            if (rect_w != NULL) { *rect_w = current->w; }
            if (rect_h != NULL) { *rect_h = current->h; }
            return;
        }

        current = current->next;
        iter++;
    } while (current != NULL);
}

/*
Function: TextureMap_Empty

Parameters:

Return:

*/
void            YAGL_API    TextureMap_Empty (TextureMap* tex_map)
{
    if (mem_exists(tex_map, PTR_TEXTURE_MAP) == 0) { return; }

    __texture_map_empty(tex_map);
}


/*
Function: TextureMap_Count

Parameters:

Return:

*/
int             YAGL_API    TextureMap_Count (TextureMap* tex_map)
{
    if (mem_exists(tex_map, PTR_TEXTURE_MAP) == 0) { return -1; }

    return tex_map->count;
}

/**
    @}
*/
