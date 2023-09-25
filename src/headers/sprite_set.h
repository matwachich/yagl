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

#ifndef __SPRITE_SET_H__
#define __SPRITE_SET_H__

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline void __sprite_set_del (SpriteSet* spr_set, Sprite* spr, int destroy);
inline void __sprite_set_del_all (SpriteSet* spr_set, int destroy);

/* ------------------------------------------------------------------------- **/
/* Public functions **/

SpriteSet*  YAGL_API    SpriteSet_Create ();
int         YAGL_API    SpriteSet_IsSpriteSet (SpriteSet* spr_set);
int         YAGL_API    SpriteSet_Destroy (SpriteSet* spr_set, int destroy);

void        YAGL_API    SpriteSet_Add (SpriteSet* spr_set, Sprite* spr);
int         YAGL_API    SpriteSet_Exists (SpriteSet* spr_set, Sprite* spr);
void        YAGL_API    SpriteSet_Del (SpriteSet* spr_set, Sprite* spr, int destroy);
void        YAGL_API    SpriteSet_DelAll (SpriteSet* spr_set, int destroy);

void        YAGL_API    SpriteSet_SetColor (SpriteSet* spr_set, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void        YAGL_API    SpriteSet_SetColorEx (SpriteSet* spr_set, YAGL_Color color);
void        YAGL_API    SpriteSet_SetBlendMode (SpriteSet* spr_set, eBLEND_MODE blend_mode);
void        YAGL_API    SpriteSet_SetVisible (SpriteSet* spr_set, int visible);
void        YAGL_API    SpriteSet_SetDynamic (SpriteSet* spr_set, int dynamic);

int         YAGL_API    SpriteSet_Collide (SpriteSet* spr_set, Sprite* spr, int force_check, int must_touch_all);

void        YAGL_API    SpriteSet_Draw (SpriteSet* spr_set);
void        YAGL_API    SpriteSet_DrawShapes (SpriteSet* spr_set);

int         YAGL_API    SpriteSet_Count (SpriteSet* spr_set);
int         YAGL_API    SpriteSet_GetAll (SpriteSet* spr_set, Sprite* spr[], int size);
int         YAGL_API    SpriteSet_Iterate (SpriteSet* spr_set, YAGLSpriteSetIterateProc enum_proc, void* user_data);

#endif // __SPRITE_SET_H__
