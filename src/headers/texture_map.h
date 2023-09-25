/**
	Copyright (c) 2012 matwachich@gmail.com

	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including without limitation
	the rights to use, copy, modify, merge, publish, distribute, sublicense,
	and/or sell copies of the Software, and to permit persons to whom
	the Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included
	in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
	DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
	TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
	THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
	YAGL - AutoIt OpenGL
	2D game engin for AutoIt3
	by Matwachich (matwachich at gmail dot com)
*/

#ifndef __TEXTURE_MAP_H__
#define __TEXTURE_MAP_H__

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline void __texture_map_empty (TextureMap* tex_map);
inline void __texture_map_get (TextureMap* tex_map, unsigned int rect_id, Texture** tex, int* rect_x, int* rect_y, int* rect_w, int* rect_h);

/* ------------------------------------------------------------------------- **/
/* Public functions **/

TextureMap*     YAGL_API    TextureMap_Create (const char filepath[], eTEXTURE_CHANNELS channels);
TextureMap*     YAGL_API    TextureMap_CreateFromTexture (Texture* tex);
int       YAGL_API    TextureMap_IsTextureMap (TextureMap* tex_map);
int       YAGL_API    TextureMap_Destroy (TextureMap* tex_map, int free_tex);

void            YAGL_API    TextureMap_SetTexture (TextureMap* tex_map, Texture* tex);
Texture*        YAGL_API    TextureMap_GetTexture (TextureMap* tex_map);

void            YAGL_API    TextureMap_SetParameter (TextureMap* tex_map, int flag, int value);
void            YAGL_API    TextureMap_SetDefaultParameter (TextureMap* tex_map);
void            YAGL_API    TextureMap_GetSize (TextureMap* tex_map, int* w, int* h);

int             YAGL_API    TextureMap_AddRect (TextureMap* tex_map, int rect_x, int rect_y, int rect_w, int rect_h);
void            YAGL_API    TextureMap_GetRect (TextureMap* tex_map, unsigned int rect_id, int* rect_x, int* rect_y, int* rect_w, int* rect_h);
void            YAGL_API    TextureMap_Empty (TextureMap* tex_map);

int             YAGL_API    TextureMap_Count (TextureMap* tex_map);

#endif // __TEXTURE_MAP_H__
