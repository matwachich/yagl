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

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline int __particle_random_int(int val, int var);
inline float __particle_random_float(float val, float var);
inline int __particle_random_color(int col, int var);
inline void __particle_color_check_bounds(int* color);
inline void __particle_init(PEmitter* emit);
inline void __particle_set_tex_rect(PEmitter* emit, int x, int y, int w, int h);
inline void __particle_init_child(PEmitter* emit, Particle* prt);
inline void __particle_draw(Particle* prt, double dt, int visible);
inline void __particle_destroy_all_parts (PEmitter* emit);

int __particle_ini_parse_callback (PEmitterAndSection* emit, char* section, char* name, char* value);
inline void __particle_ini_load_tex_rect (PEmitter* emit, char* value);
void inline __tolower (char* str);

void inline __pemitter_draw (PEmitter* emit);

/* ------------------------------------------------------------------------- **/
/* Public functions **/

PEmitter*   YAGL_API    PEmitter_Create (Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h);
int         YAGL_API    PEmitter_IsPEmitter (PEmitter* emit);
int         YAGL_API    PEmitter_ReadCfg (PEmitter* emit, const char* file, const char* section, int load_tex_rect);
int         YAGL_API    PEmitter_WriteCfg (PEmitter* emit, const char* file, const char* section, int save_tex_rect);
int         YAGL_API    PEmitter_Copy (PEmitter* source, PEmitter* dest, int copy_texture);
void        YAGL_API    PEmitter_SetTexture (PEmitter* emit, Texture* tex);
Texture*    YAGL_API    PEmitter_GetTexture (PEmitter* emit);
void        YAGL_API    PEmitter_SetTextureRect (PEmitter* emit, int rect_x, int rect_y, int rect_w, int rect_h);
void        YAGL_API    PEmitter_GetTextureRect (PEmitter* emit, int* rect_x, int* rect_y, int* rect_w, int* rect_h);
void        YAGL_API    PEmitter_SetTextureMap (PEmitter* emit, TextureMap* tex_map, unsigned int rect_id);
void        YAGL_API    PEmitter_SetActive (PEmitter* emit, int status);
int         YAGL_API	PEmitter_GetActive (PEmitter* emit);
void        YAGL_API    PEmitter_Emitte (PEmitter* emit, unsigned int nbr);
void        YAGL_API    PEmitter_EmitteAt (PEmitter* emit, float x, float y, unsigned int nbr);
void        YAGL_API    PEmitter_Draw (PEmitter* emit);
int         YAGL_API    PEmitter_Destroy (PEmitter* emit);

#endif // __PARTICLE_H__
