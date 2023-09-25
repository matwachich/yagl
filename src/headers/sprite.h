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

#ifndef __SPRITE_H__
#define __SPRITE_H__

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline void __sprite_init(Sprite* spr);
inline void __sprite_set_tex(Sprite* spr, Texture* tex, float w, float h);
inline void __sprite_set_tex_rect(Sprite* spr, float x, float y, float w, float h);
inline void __sprite_add_del_from_collision_list(Sprite* spr, eSHAPE shape);
inline void __sprite_set_center(Sprite* spr, eCENTER flag);
inline void __sprite_keep_center(Sprite* spr);
inline void __sprite_get_point(Sprite* spr, float x, float y, float* new_x, float* new_y);
inline void __sprite_draw_no_tex(VectF pos, float angle, VectF center, VectF size, unsigned int color);
inline void __sprite_draw_quad(Texture* tex, eBLEND_MODE blend, VectF pos, VectF size, VectF center, VectI flip, float angle, YAGL_Color color, float tex_rect1[], float tex_rect2[], float tex_rect3[], float tex_rect4[]);
inline void __sprite_calc_dynamics (Sprite* spr);
inline void __sprite_calc_anim (Sprite* spr);
inline void __sprite_apply_anim_frame (Sprite* spr, unsigned int frame);

/* ------------------------------------------------------------------------- **/
/* Public functions **/

Sprite*         YAGL_API    Sprite_Create (Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h);
int             YAGL_API    Sprite_IsSprite (Sprite* spr);

void            YAGL_API    Sprite_SetTexture (Sprite* spr, Texture* tex);
void            YAGL_API    Sprite_SetTextureRect (Sprite* spr, int rect_x, int rect_y, int rect_w, int rect_h);
void            YAGL_API    Sprite_SetTextureEx (Sprite* spr, Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h);
Texture*        YAGL_API    Sprite_GetTexture (Sprite* spr);
void            YAGL_API    Sprite_GetTextureRect (Sprite* spr, int* rect_x, int* rect_y, int* rect_w, int* rect_h);
Texture*        YAGL_API    Sprite_GetTextureEx (Sprite* spr, int* rect_x, int* rect_y, int* rect_w, int* rect_h);

void            YAGL_API    Sprite_SetTextureMap (Sprite* spr, TextureMap* tex_map, unsigned int rect_id);

void            YAGL_API    Sprite_SetShape (Sprite* spr, eSHAPE shape_type, float x, float y, float w, float h);
void            YAGL_API    Sprite_GetShape (Sprite* spr, eSHAPE* shape_type, float* x, float* y, float* w, float* h);
void            YAGL_API    Sprite_SetCollisionMask (Sprite* spr, int collision_mask);
int             YAGL_API    Sprite_GetCollisionMask (Sprite* spr);
void            YAGL_API    Sprite_SetCollisionGroup (Sprite* spr, int collision_group);
int             YAGL_API    Sprite_GetCollisionGroup (Sprite* spr);

void            YAGL_API    Sprite_AnimationSet (Sprite* spr, Animation* anim);
Animation*      YAGL_API    Sprite_AnimationGet (Sprite* spr);
void            YAGL_API    Sprite_AnimationSetFrame (Sprite* spr, unsigned int frame_id);
void            YAGL_API    Sprite_AnimationDisplayFrame (Sprite* spr, unsigned int frame_id);
unsigned int    YAGL_API    Sprite_AnimationGetFrame (Sprite* spr);
void            YAGL_API    Sprite_AnimationSetStartFrame (Sprite* spr, unsigned int frame_id);
unsigned int    YAGL_API    Sprite_AnimationGetStartFrame (Sprite* spr);
void            YAGL_API    Sprite_AnimationSetTimerMult (Sprite* spr, float tm);
float           YAGL_API    Sprite_AnimationGetTimerMult (Sprite* spr);
void            YAGL_API    Sprite_AnimationGo (Sprite* spr, int loop);
int             YAGL_API    Sprite_AnimationGetStatus (Sprite* spr);
int             YAGL_API    Sprite_AnimationGetLoop (Sprite* spr);
void            YAGL_API    Sprite_AnimationStop (Sprite* spr, unsigned int stop_frame);

void            YAGL_API    Sprite_SetCenterEx (Sprite* spr, eCENTER flag);
void            YAGL_API    Sprite_Move (Sprite* spr, float x, float y);
void            YAGL_API    Sprite_Rotate (Sprite* spr, float angle);
void            YAGL_API    Sprite_Scale (Sprite* spr, float x, float y);

void            YAGL_API    Sprite_SetFlip (Sprite* spr, int x, int y);
void            YAGL_API    Sprite_GetFlip (Sprite* spr, int* x, int* y);

void            YAGL_API    Sprite_SetVelLen (Sprite* spr, float len);
void            YAGL_API    Sprite_SetVelEx (Sprite* spr, float len, float angle);
void            YAGL_API    Sprite_GetVelEx (Sprite* spr, float* len, float* angle);
void            YAGL_API    Sprite_SetVelAngle (Sprite* spr, float angle);
void            YAGL_API    Sprite_SetAccelLen (Sprite* spr, float len);
void            YAGL_API    Sprite_SetAccelEx (Sprite* spr, float len, float angle);
void            YAGL_API    Sprite_GetAccelEx (Sprite* spr, float* len, float* angle);
void            YAGL_API    Sprite_SetAccelAngle (Sprite* spr, float angle);

void            YAGL_API    Sprite_SpriteToWorld (Sprite* spr, float spr_x, float spr_y, float* world_x, float* world_y);
void            YAGL_API    Sprite_SpriteToWorldEx (Sprite* spr, float spr_x_ratio, float spr_y_ratio, float* world_x, float* world_y);
void            YAGL_API    Sprite_WorldToSprite (Sprite* spr, float world_x, float world_y, float* spr_x, float* spr_y, int folow_spr_angle);

void            YAGL_API    Sprite_Draw (Sprite* spr);
void            YAGL_API    Sprite_DrawShape (Sprite* spr);

int             YAGL_API    Sprite_Destroy (Sprite* spr);

#endif // __SPRITE_H__
