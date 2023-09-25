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

#ifndef __ACCESSORS_SPRITE_H__
#define __ACCESSORS_SPRITE_H__

/* ------------------------------------------------------------------------- **/
/* Public functions **/

void        YAGL_API    Sprite_SetVisible (Sprite* spr, int visible);
void        YAGL_API    Sprite_SetDynamic (Sprite* spr, int dynamic);
int         YAGL_API    Sprite_GetVisible (Sprite* spr);
int         YAGL_API    Sprite_GetDynamic (Sprite* spr);

void        YAGL_API    Sprite_SetPos (Sprite* spr, float x, float y);
void        YAGL_API    Sprite_GetPos (Sprite* spr, float* x, float* y);

void        YAGL_API    Sprite_SetSize (Sprite* spr, float w, float h);
void        YAGL_API    Sprite_GetSize (Sprite* spr, float* w, float* h);

void        YAGL_API    Sprite_SetCenter (Sprite* spr, float x, float y);
void        YAGL_API    Sprite_GetCenter (Sprite* spr, float* x, float* y);

void        YAGL_API    Sprite_SetAngle (Sprite* spr, float angle);
float       YAGL_API    Sprite_GetAngle (Sprite* spr);

void        YAGL_API    Sprite_SetBlendMode (Sprite* spr, eBLEND_MODE blend_mode);
int         YAGL_API    Sprite_GetBlendMode (Sprite* spr);

void        YAGL_API    Sprite_SetColor (Sprite* spr, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void        YAGL_API    Sprite_GetColor (Sprite* spr, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a);
void        YAGL_API    Sprite_SetColorEx (Sprite* spr, YAGL_Color color);
YAGL_Color  YAGL_API    Sprite_GetColorEx (Sprite* spr);

void        YAGL_API    Sprite_SetVel (Sprite* spr, float x, float y);
void        YAGL_API    Sprite_SetVelMax (Sprite* spr, float max);
void        YAGL_API    Sprite_GetVel (Sprite* spr, float* x, float* y);
float       YAGL_API    Sprite_GetVelLen (Sprite* spr);
float       YAGL_API    Sprite_GetVelAngle (Sprite* spr);
float       YAGL_API    Sprite_GetVelMax (Sprite* spr);

void        YAGL_API    Sprite_SetAccel (Sprite* spr, float x, float y);
void        YAGL_API    Sprite_GetAccel (Sprite* spr, float* x, float* y);
float       YAGL_API    Sprite_GetAccelLen (Sprite* spr);
float       YAGL_API    Sprite_GetAccelAngle (Sprite* spr);

void        YAGL_API    Sprite_SetInnertia (Sprite* spr, float innertia);
float       YAGL_API    Sprite_GetInnertia (Sprite* spr);

void        YAGL_API    Sprite_SetAVel (Sprite* spr, float avel);
void        YAGL_API    Sprite_SetAVelMax (Sprite* spr, float max);
float       YAGL_API    Sprite_GetAVel (Sprite* spr);
float       YAGL_API    Sprite_GetAVelMax (Sprite* spr);

void        YAGL_API    Sprite_SetAAccel (Sprite* spr, float aaccel);
float       YAGL_API    Sprite_GetAAccel (Sprite* spr);

void        YAGL_API    Sprite_SetAInnertia (Sprite* spr, float ainnertia);
float       YAGL_API    Sprite_GetAInnertia (Sprite* spr);

void        YAGL_API    Sprite_SetParentV (Sprite* spr, Sprite* spr_parent);
void        YAGL_API    Sprite_SetParentA (Sprite* spr, Sprite* spr_parent);
Sprite*     YAGL_API    Sprite_GetParentV (Sprite* spr);
Sprite*     YAGL_API    Sprite_GetParentA (Sprite* spr);

void        YAGL_API    Sprite_SetAttachedData (Sprite* spr, void* data);
void*       YAGL_API    Sprite_GetAttachedData (Sprite* spr);

#endif // __ACCESSORS_SPRITE_H__
