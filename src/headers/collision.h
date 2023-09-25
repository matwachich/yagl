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

#ifndef __COLLISION_H__
#define __COLLISION_H__

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline void __collision_array_update ();
inline void __collision_sprite_get_pos(Sprite* spr, float* x, float* y);
inline void __collision_rect_correct(float* x, float* y, float rx, float ry, float rw, float rh);
inline int __collision_Point_Point(Sprite* spr1, Sprite* spr2);
inline int __collision_Point_Circle(Sprite* spr1, Sprite* spr2);
inline int __collision_Point_Rect(Sprite* spr1, Sprite* spr2);
inline int __collision_Circle_Circle(Sprite* spr1, Sprite* spr2);
inline int __collision_Circle_Rect(Sprite* spr1, Sprite* spr2);
inline int __collision_Rect_Rect(Sprite* spr1, Sprite* spr2);
inline int __collision_check_mask_and_group (Sprite* spr1, Sprite* spr2);
inline int __collision_check_collision (Sprite* spr1, Sprite* spr2);

#ifdef YAGL_ADVANCED_COLLISIONS
inline void __collision_couple_add (SpriteCouple* spr_cpl, Sprite* spr1, Sprite* spr2);
inline SpriteCouple* __collision_couple_exists (Sprite* spr1, Sprite* spr2);
inline void __collision_couple_del (SpriteCouple* spr_cpl);
#endif

/* ------------------------------------------------------------------------- **/
/* Public functions **/

void    YAGL_API    Collision_SetCallback (YAGLCollisionProc proc);
void    YAGL_API    Collision_Process ();
void    YAGL_API    Collision_SetAutoProcess(int status);
int     YAGL_API    Collision_Check (Sprite* spr1, Sprite* spr2, int force_check);

#endif // __COLLISION_H__
