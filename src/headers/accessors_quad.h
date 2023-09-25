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

#ifndef __ACCESSORS_QUAD_H__
#define __ACCESSORS_QUAD_H__

/* ------------------------------------------------------------------------- **/
/* Public functions **/

void        YAGL_API    Quad_SetVisible (Quad* qd, int visible);
int         YAGL_API    Quad_GetVisible (Quad* qd);

void        YAGL_API    Quad_SetPos (Quad* qd, float x, float y);
void        YAGL_API    Quad_GetPos (Quad* qd, float* x, float* y);

void        YAGL_API    Quad_SetSize (Quad* qd, float w, float h);
void        YAGL_API    Quad_GetSize (Quad* qd, float* w, float* h);

void        YAGL_API    Quad_SetCenter (Quad* qd, float x, float y);
void        YAGL_API    Quad_GetCenter (Quad* qd, float* x, float* y);

void        YAGL_API    Quad_SetAngle (Quad* qd, float angle);
float       YAGL_API    Quad_GetAngle (Quad* qd);

void        YAGL_API    Quad_SetBlendMode (Quad* qd, eBLEND_MODE blend_mode);
int         YAGL_API    Quad_GetBlendMode (Quad* qd);

void        YAGL_API    Quad_SetColor (Quad* qd, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void        YAGL_API    Quad_GetColor (Quad* qd, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a);
void        YAGL_API    Quad_SetColorEx (Quad* qd, YAGL_Color color);
YAGL_Color  YAGL_API    Quad_GetColorEx (Quad* qd);

void        YAGL_API    Quad_SetAttachedData (Quad* qd, void* data);
void*       YAGL_API    Quad_GetAttachedData (Quad* qd);

#endif // __ACCESSORS_QUAD_H__
