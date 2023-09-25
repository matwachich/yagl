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

#ifndef __QUAD_H__
#define __QUAD_H__

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline void __quad_init (Quad* qd);
inline void __quad_set_tex(Quad* qd, Texture* tex, float w, float h);
inline void __quad_set_tex_rect(Quad* qd, float x, float y, float w, float h);
inline void __quad_set_center(Quad* qd, eCENTER flag);
inline void __quad_keep_center(Quad* qd);
inline void __quad_get_point(Quad* qd, float x, float y, float* new_x, float* new_y);

/* ------------------------------------------------------------------------- **/
/* Public functions **/

Quad*       YAGL_API    Quad_Create (Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h);
int         YAGL_API    Quad_IsQuad (Quad* qd);

void        YAGL_API    Quad_SetTexture (Quad* qd, Texture* tex);
void        YAGL_API    Quad_SetTextureRect (Quad* qd, int rect_x, int rect_y, int rect_w, int rect_h);
void        YAGL_API    Quad_SetTextureEx (Quad* qd, Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h);
Texture*    YAGL_API    Quad_GetTexture (Quad* qd);
void        YAGL_API    Quad_GetTextureRect (Quad* qd, int* rect_x, int* rect_y, int* rect_w, int* rect_h);
Texture*    YAGL_API    Quad_GetTextureEx (Quad* qd, int* rect_x, int* rect_y, int* rect_w, int* rect_h);

void        YAGL_API    Quad_SetTextureMap (Quad* qd, TextureMap* tex_map, unsigned int rect_id);

void        YAGL_API    Quad_SetCenterEx (Quad* qd, eCENTER flag);
void        YAGL_API    Quad_Move (Quad* qd, float x, float y);
void        YAGL_API    Quad_Rotate (Quad* qd, float angle);
void        YAGL_API    Quad_Scale (Quad* qd, float x, float y);

void        YAGL_API    Quad_SetFlip (Quad* qd, int x, int y);
void        YAGL_API    Quad_GetFlip (Quad* qd, int* x, int* y);

void        YAGL_API    Quad_QuadToWorld (Quad* qd, float qd_x, float qd_y, float* world_x, float* world_y);
void        YAGL_API    Quad_QuadToWorldEx (Quad* qd, float qd_x_ratio, float qd_y_ratio, float* world_x, float* world_y);

void        YAGL_API    Quad_Draw (Quad* qd);

int         YAGL_API    Quad_Destroy (Quad* qd);

#endif // __QUAD_H__
