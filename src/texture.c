/**
    \addtogroup 070_texture
    @{
*/

#include "all.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline void __texture_bind(Texture* tex)
{
    if (tex != NULL) {
        if (_engin_->current_texture != tex->tex_id && tex->tex_id != 0) {
            _engin_->current_texture = tex->tex_id;
            glBindTexture(GL_TEXTURE_2D, tex->tex_id);
        }
    }
}

inline  void __texture_empty(Texture* tex)
{
    if (tex != NULL) {
        if (tex->tex_id != 0) {
            if (tex->tex_id == _engin_->current_texture) {
                _engin_->current_texture = 0;
                glBindTexture(GL_TEXTURE_2D, 0);
            }
            glDeleteTextures(1, &tex->tex_id);
            tex->tex_id = 0;
            tex->width = 0;
            tex->height = 0;
        }
    }
}

inline void __texture_set_default_param(Texture* tex)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

/* ------------------------------------------------------------------------- **/
/* Public functions **/

Texture*    YAGL_API    Texture_CreateEmpty ()
{
    Texture* tex = mem_alloc(sizeof(Texture), PTR_TEXTURE);
    if (tex == NULL) {
        __DEBUG__("Unable to create texture! (Out of memory)", 2);
    }

    __texture_empty(tex);
    return tex;
}

/*
Function: Texture_Create

Parameters:

Return:

*/
Texture*    YAGL_API    Texture_Create (const char filepath[], eTEXTURE_CHANNELS channels)
{
    Texture* tex = mem_alloc(sizeof(Texture), PTR_TEXTURE);
    if (tex == NULL) {
        __DEBUG__("Unable to create texture! (Out of memory)", 2);
    }

    int w, h, chan;
    unsigned char* img_data = SOIL_load_image(filepath, &w, &h, &chan, channels);
    if (img_data == NULL) {
        char tmp[1024];
        sprintf(tmp, "Unable to load file: %s", filepath);
        __DEBUG__(tmp, 1);
        tex->tex_id = 0;
		tex->width = 0;
		tex->height = 0;
		return tex;
    }

    if (channels == 0) { channels = chan; }

    tex->tex_id = SOIL_create_OGL_texture(img_data, w, h, channels, SOIL_CREATE_NEW_ID, SOIL_FLAG_POWER_OF_TWO);
    SOIL_free_image_data(img_data);

    if (tex->tex_id <= 0) {
        char tmp[1024];
        sprintf(tmp, "Unable to load file: %s", filepath);
        __DEBUG__(tmp, 1);
        tex->tex_id = 0;
		tex->width = 0;
		tex->height = 0;
		return tex;
    }

    tex->width = w; tex->height = h;

    glBindTexture(GL_TEXTURE_2D, tex->tex_id);
    _engin_->current_texture = tex->tex_id;

    __texture_set_default_param(tex);

	return tex;
}

/*
Function: Texture_CreateFromMem

Parameters:

Return:

*/
Texture*    YAGL_API    Texture_CreateFromMem (const unsigned char* data, const int buffer_size, eTEXTURE_CHANNELS channels)
{
    Texture* tex = mem_alloc(sizeof(Texture), PTR_TEXTURE);
    if (tex == NULL) {
        __DEBUG__("Unable to create texture! (Out of memory)", 2);
    }

    int w, h, chan;
    unsigned char* img_data = SOIL_load_image_from_memory(data, buffer_size, &w, &h, &chan, channels);
    if (img_data == NULL) {
        char tmp[1024];
        sprintf(tmp, "Unable to load image from memory (buffer size: %d)", buffer_size);
        __DEBUG__(tmp, 1);
        tex->tex_id = 0;
		tex->width = 0;
		tex->height = 0;
		return tex;
    }

    if (channels == 0) { channels = chan; }

    tex->tex_id = SOIL_create_OGL_texture(img_data, w, h, channels, SOIL_CREATE_NEW_ID, SOIL_FLAG_POWER_OF_TWO);
    SOIL_free_image_data(img_data);

    if (tex->tex_id <= 0) {
        char tmp[1024];
        sprintf(tmp, "Unable to load image from memory (buffer size: %d)", buffer_size);
        __DEBUG__(tmp, 1);
        tex->tex_id = 0;
		tex->width = 0;
		tex->height = 0;
		return tex;
    }

    tex->width = w; tex->height = h;

    glBindTexture(GL_TEXTURE_2D, tex->tex_id);
    _engin_->current_texture = tex->tex_id;

    __texture_set_default_param(tex);

	return tex;
}

/*
Function: Texture_Load

Parameters:

Return:

*/
int   YAGL_API    Texture_IsTexture (Texture* tex)
{
    return mem_exists(tex, PTR_TEXTURE);
}

/*
Function: Texture_Load

Parameters:

Return:

*/
int         YAGL_API    Texture_Load (Texture* tex, const char filepath[], eTEXTURE_CHANNELS channels)
{
    if (mem_exists(tex, PTR_TEXTURE) == 0) { return 0; }

    __texture_empty(tex);

    int w, h, chan;
    unsigned char* img_data = SOIL_load_image(filepath, &w, &h, &chan, channels);
    if (img_data == NULL) {
        char tmp[1024];
        sprintf(tmp, "Unable to load file: %s", filepath);
        __DEBUG__(tmp, 1);
        tex->tex_id = 0;
		tex->width = 0;
		tex->height = 0;
		return 0;
    }

    if (channels == 0) { channels = chan; }

    tex->tex_id = SOIL_create_OGL_texture(img_data, w, h, channels, SOIL_CREATE_NEW_ID, SOIL_FLAG_POWER_OF_TWO);
    SOIL_free_image_data(img_data);

    if (tex->tex_id <= 0) {
        char tmp[1024];
        sprintf(tmp, "Unable to load file: %s", filepath);
        __DEBUG__(tmp, 1);
        tex->tex_id = 0;
		tex->width = 0;
		tex->height = 0;
		return 0;
    }

    tex->width = w; tex->height = h;

    glBindTexture(GL_TEXTURE_2D, tex->tex_id);
    _engin_->current_texture = tex->tex_id;

    __texture_set_default_param(tex);

	return 1;
}

/*
Function: Texture_LoadFromMem

Parameters:

Return:

*/
int         YAGL_API    Texture_LoadFromMem (Texture* tex, const unsigned char* data, const int buffer_size, eTEXTURE_CHANNELS channels)
{
    if (mem_exists(tex, PTR_TEXTURE) == 0) { return 0; }

    __texture_empty(tex);

    int w, h, chan;
    unsigned char* img_data = SOIL_load_image_from_memory(data, buffer_size, &w, &h, &chan, channels);
    if (img_data == NULL) {
        char tmp[1024];
        sprintf(tmp, "Unable to load image from memory (buffer size: %d)", buffer_size);
        __DEBUG__(tmp, 1);
        tex->tex_id = 0;
		tex->width = 0;
		tex->height = 0;
		return 0;
    }

    if (channels == 0) { channels = chan; }

    tex->tex_id = SOIL_create_OGL_texture(img_data, w, h, channels, SOIL_CREATE_NEW_ID, SOIL_FLAG_POWER_OF_TWO);
    SOIL_free_image_data(img_data);

    if (tex->tex_id <= 0) {
        char tmp[1024];
        sprintf(tmp, "Unable to load image from memory (buffer size: %d)", buffer_size);
        __DEBUG__(tmp, 1);
        tex->tex_id = 0;
		tex->width = 0;
		tex->height = 0;
		return 0;
    }

    tex->width = w; tex->height = h;

    glBindTexture(GL_TEXTURE_2D, tex->tex_id);
    _engin_->current_texture = tex->tex_id;

    __texture_set_default_param(tex);

	return 1;
}

/*
Function: Texture_SetPrameter

Parameters:

Return:

*/
void        YAGL_API    Texture_SetParameter (Texture* tex, int flag, int value)
{
    if (mem_exists(tex, PTR_TEXTURE) == 0) { return; }

    __texture_bind(tex);
    glTexParameteri(GL_TEXTURE_2D, flag, value);
}

/*
Function: Texture_SetDefaultParameter

Parameters:

Return:

*/
void        YAGL_API    Texture_SetDefaultParameter (Texture* tex)
{
    if (mem_exists(tex, PTR_TEXTURE) == 0) { return; }

    __texture_set_default_param(tex);
}

/*
Function: Texture_GetSize

Parameters:

Return:

*/
void        YAGL_API    Texture_GetSize (Texture* tex, int* w, int* h)
{
    if (mem_exists(tex, PTR_TEXTURE) == 0) { return; }

    *w = tex->width;
    *h = tex->height;
}

/*
Function: Texture_SetEmpty

Parameters:

Return:

*/
void        YAGL_API    Texture_SetEmpty (Texture* tex)
{
    if (mem_exists(tex, PTR_TEXTURE) == 0) { return; }

    __texture_empty(tex);
}

/*
Function: Texture_Destroy

Parameters:

Return:

*/
int   YAGL_API    Texture_Destroy (Texture* tex)
{
    if (mem_exists(tex, PTR_TEXTURE) == 1) { __texture_empty(tex); }
    return (int)mem_free(tex, PTR_TEXTURE);
}

/**
    @}
*/
