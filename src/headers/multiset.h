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

#ifndef __MULTISET_H__
#define __MULTISET_H__

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline void __multiset_destroy_elem (MultiSet* ms, void* elem);
inline void __multiset_del_all (MultiSet* ms, int destroy);

/* ------------------------------------------------------------------------- **/
/* Public functions **/

MultiSet*   YAGL_API    MultiSet_Create (eSET_TYPE type);
int         YAGL_API    MultiSet_IsMultiSet (MultiSet* ms);
eSET_TYPE   YAGL_API    MultiSet_GetDataType (MultiSet* ms);
int         YAGL_API    MultiSet_Destroy (MultiSet* ms, int destroy);

void        YAGL_API    MultiSet_Add (MultiSet* ms, void* data, int rank);
int         YAGL_API    MultiSet_Exists (MultiSet* ms, void* data);
void        YAGL_API    MultiSet_Del (MultiSet* ms, void* data, int destroy);
void        YAGL_API    MultiSet_DelAll (MultiSet* ms, int destroy);

int         YAGL_API    MultiSet_Count (MultiSet* ms);
int         YAGL_API    MultiSet_GetAll (MultiSet* ms, void* data[], int size);
int         YAGL_API    MultiSet_Iterate (MultiSet* ms, YAGLMultiSetIterateProc enum_proc, void* user_data);

/* Multi */
void        YAGL_API    MultiSet_Draw (MultiSet* ms); // quad, spr, pemitter, bmptext
void        YAGL_API    MultiSet_SetColor (MultiSet* ms, unsigned char r, unsigned char g, unsigned char b, unsigned char a); // quad, spr, pemitter, bmptext
void        YAGL_API    MultiSet_SetColorEx (MultiSet* ms, YAGL_Color color); // quad, spr, pemitter, bmptext
void        YAGL_API    MultiSet_SetBlendMode (MultiSet* ms, eBLEND_MODE blend_mode);  // quad, spr, pemitter, bmptext
void        YAGL_API    MultiSet_SetVisible (MultiSet* ms, int visible); // quad, spr, pemitter, bmptext

/* Quad specific */
/* Sprite specific */
void        YAGL_API    MultiSet_SpriteDrawShape (MultiSet* ms); // spr
void        YAGL_API    MultiSet_SpriteSetDynamic (MultiSet* ms, int dynamic); // spr
int         YAGL_API    MultiSet_SpriteCollide (MultiSet* ms, Sprite* spr, int force_check, int must_touch_all); // spr
void        YAGL_API    MultiSet_SpriteSetFlip (MultiSet* ms, int x, int y);

// vel
void        YAGL_API    MultiSet_SpriteSetVel (MultiSet* ms, float x, float y);
void        YAGL_API    MultiSet_SpriteSetVelLen (MultiSet* ms, float len);
void        YAGL_API    MultiSet_SpriteSetVelAngle (MultiSet* ms, float angle);
void        YAGL_API    MultiSet_SpriteSetVelEx (MultiSet* ms, float len, float angle);
// velmax
void        YAGL_API    MultiSet_SpriteSetVelMax (MultiSet* ms, float vel_max);
// accel
void        YAGL_API    MultiSet_SpriteSetAccel (MultiSet* ms, float x, float y);
void        YAGL_API    MultiSet_SpriteSetAccelLen (MultiSet* ms, float len);
void        YAGL_API    MultiSet_SpriteSetAccelAngle (MultiSet* ms, float angle);
void        YAGL_API    MultiSet_SpriteSetAccelEx (MultiSet* ms, float len, float angle);
// innertia
void        YAGL_API    MultiSet_SpriteSetInnertia (MultiSet* ms, float innertia);

// angles
void        YAGL_API    MultiSet_SpriteSetAVel (MultiSet* ms, float avel);
void        YAGL_API    MultiSet_SpriteSetAVelMax (MultiSet* ms, float avel_max);
void        YAGL_API    MultiSet_SpriteSetAAccel (MultiSet* ms, float aaccel);
void        YAGL_API    MultiSet_SpriteSetAInnertia (MultiSet* ms, float ainnertia);

/* PEmitter specific */
void        YAGL_API    MultiSet_PEmitterSetActive (MultiSet* ms, int active); // pemitter
void        YAGL_API    MultiSet_PEmitterEmitte (MultiSet* ms, unsigned int nbr); // pemitter
void        YAGL_API    MultiSet_PEmitterEmitteAt (MultiSet* ms, float x, float y, unsigned int nbr); // pemitter

/* BmpText specific */
void        YAGL_API    MultiSet_BmpTextSetText (MultiSet* ms, const char text[]);


#endif __MULTISET_H__
