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

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline void __anim_frame_init (AnimFrame* frame);
inline void __anim_frame_set_blank (AnimFrame* frame);
inline int __anim_get_next_free_frame (Animation* anim);
inline void __anim_frame_set_tex_rect (AnimFrame* frame, int rect_x, int rect_y, int rect_w, int rect_h);

/* ------------------------------------------------------------------------- **/
/* Public functions **/

Animation*  YAGL_API    Animation_Create (unsigned int frames_count);
int         YAGL_API    Animation_IsAnimation (Animation* anim);

int         YAGL_API    Animation_AddFrameEx (Animation* anim, float duration, Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h, YAGL_Color color, eBLEND_MODE blend_mode, int change_size, float size_x, float size_y);
int         YAGL_API    Animation_AddFrame (Animation* anim, float duration);
void        YAGL_API    Animation_FrameSetBlank (Animation* anim, unsigned int frame_id);
int         YAGL_API    Animation_FrameCount (Animation* anim);
int         YAGL_API    Animation_FrameMax (Animation* anim);
void        YAGL_API    Animation_Empty (Animation* anim);

void        YAGL_API    Animation_SetTimerMult (Animation* anim, float tm);
float       YAGL_API    Animation_GetTimerMult (Animation* anim);

int         YAGL_API    Animation_Destroy (Animation* anim);

void        YAGL_API    Animation_FrameSetDuration (Animation* anim, unsigned int frame_id, float duration);
void        YAGL_API    Animation_FrameSetTexture (Animation* anim, unsigned int frame_id, Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h);
void        YAGL_API    Animation_FrameSetColor (Animation* anim, unsigned int frame_id, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
void        YAGL_API    Animation_FrameSetColorEx (Animation* anim, unsigned int frame_id, YAGL_Color color);
void        YAGL_API    Animation_FrameSetBlendMode (Animation* anim, unsigned int frame_id, eBLEND_MODE blend_mode);
void        YAGL_API    Animation_FrameSetSize (Animation* anim, unsigned int frame_id, int change_size, float size_x, float size_y);

float       YAGL_API    Animation_FrameGetDuration (Animation* anim, unsigned int frame_id);
Texture*    YAGL_API    Animation_FrameGetTexture (Animation* anim, unsigned int frame_id, int* rect_x, int* rect_y, int* rect_w, int* rect_h);
void        YAGL_API    Animation_FrameGetColor (Animation* anim, unsigned int frame_id, unsigned char* red, unsigned char* green, unsigned char* blue, unsigned char* alpha);
YAGL_Color  YAGL_API    Animation_FrameGetColorEx (Animation* anim, unsigned int frame_id);
int         YAGL_API    Animation_FrameGetBlendMode (Animation* anim, unsigned int frame_id);
int         YAGL_API    Animation_FrameGetSize (Animation* anim, unsigned int frame_id, float* size_x, float* size_y);

#endif // __ANIMATION_H__
