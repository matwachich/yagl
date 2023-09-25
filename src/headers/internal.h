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

#ifndef __INTERNAL_H__
#define __INTERNAL_H__

#include <stdio.h>
#include <stdlib.h>

#include <GL\glext.h>

#define SET_DATA_TYPE Sprite*
#include "set.h"

/* ------------------------------------------------------------------------- **/

#define _DBG_(args) printf(args); fflush(NULL);
#ifndef _DBG_
    #define _DBG_(v)
#endif

/* ------------------------------------------------------------------------- **/
/* Internal macros **/

#define YAGL_VERSION_MAJOR 1
#define YAGL_VERSION_MINOR 0
#define YAGL_VERSION_REVISION 0
#define YAGL_VERSION_STR "1.0.0"

#define PI 3.141592653589793

// mingw header excluding GL_BGRA in windows
#ifndef GL_BGRA
#define GL_BGRA  0x80E1
#endif

/* ------------------------------------------------------------------------- **/
/* Internal data storage structure **/

#ifdef YAGL_ADVANCED_COLLISIONS
typedef struct SpriteCouple SpriteCouple;
struct SpriteCouple {
    Sprite* spr1, spr2;
    SpriteCouple* next;
};
#endif

typedef struct Shaders Shaders;
struct Shaders {
    PFNGLCREATESHADERPROC       glCreateShader;
    PFNGLSHADERSOURCEPROC       glShaderSource;
    PFNGLCOMPILESHADERPROC      glCompileShader;
    PFNGLGETSHADERIVPROC        glGetShaderiv;
    PFNGLGETSHADERINFOLOGPROC   glGetShaderInfoLog;
    PFNGLCREATEPROGRAMPROC      glCreateProgram;
    PFNGLATTACHSHADERPROC       glAttachShader;
    PFNGLLINKPROGRAMPROC        glLinkProgram;
    PFNGLGETPROGRAMIVPROC       glGetProgramiv;
    PFNGLGETPROGRAMINFOLOGPROC  glGetProgramInfoLog;
    PFNGLUSEPROGRAMPROC         glUseProgram;
    PFNGLDETACHSHADERPROC       glDetachShader;
    PFNGLDELETEPROGRAMPROC      glDeleteProgram;
    PFNGLDELETESHADERPROC       glDeleteShader;

    PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
    PFNGLGETUNIFORMFVPROC       glGetUniformfv;
    PFNGLGETUNIFORMIVPROC       glGetUniformiv;
    PFNGLGETACTIVEUNIFORMPROC   glGetActiveUniform;

    PFNGLUNIFORM1FPROC glUniform1f;
    PFNGLUNIFORM2FPROC glUniform2f;
    PFNGLUNIFORM3FPROC glUniform3f;
    PFNGLUNIFORM4FPROC glUniform4f;
    PFNGLUNIFORM1IPROC glUniform1i;
    PFNGLUNIFORM2IPROC glUniform2i;
    PFNGLUNIFORM3IPROC glUniform3i;
    PFNGLUNIFORM4IPROC glUniform4i;

    PFNGLUNIFORM1FVPROC glUniform1fv;
    PFNGLUNIFORM2FVPROC glUniform2fv;
    PFNGLUNIFORM3FVPROC glUniform3fv;
    PFNGLUNIFORM4FVPROC glUniform4fv;
    PFNGLUNIFORM1IVPROC glUniform1iv;
    PFNGLUNIFORM2IVPROC glUniform2iv;
    PFNGLUNIFORM3IVPROC glUniform3iv;
    PFNGLUNIFORM4IVPROC glUniform4iv;

    PFNGLUNIFORMMATRIX2FVPROC   glUniformMatrix2fv;
    PFNGLUNIFORMMATRIX3FVPROC   glUniformMatrix3fv;
    PFNGLUNIFORMMATRIX4FVPROC   glUniformMatrix4fv;
    PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv;
    PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv;
    PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv;
    PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv;
    PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv;
    PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv;

    int compile_err_fatal, link_err_fatal;
    int show_info_log;
    GLuint current_shader;
};

typedef struct Engin Engin;
struct Engin {
    // debug mode
	eDEBUG debug_mode;
	FILE* debug_file;
	// Video modes
	GLFWvidmode* video_modes;
	unsigned char video_modes_count;
	// Window creation
	int window_opened, fullscreen;
	// Window and View
	VectI window_size;
	RectI view;
	VectI original_view_size;
	float current_zoom;
	eMOUSE_POS_MODE mouse_pos_mode;
	// Timer and FPS
	double old_time, delta, delay;
	float timer_mult;
	int timer_follow_mult;
	// Callbacks
	YAGLWinSizeProc win_size_proc;
	YAGLMousePosProc mouse_pos_proc;

	YAGLRenderProc render_proc;
	YAGLFrameProc frame_proc;

	YAGLDebugProc debug_proc;
	// Events
	int key_repeat;
	// Texture
	unsigned int current_texture;
	// Blend Mode
	eBLEND_MODE current_blend_mode;
	// Glow
	unsigned int glow_texture;
	unsigned int display_list_1x1;
	// Draw
	int draw_size;
	YAGL_Color draw_color;
	int draw_glow_mode;
	eBLEND_MODE draw_blend_mode;
	// Circles Display List
	unsigned int display_list_circle, display_list_disc;
	// Shaders structure
	Shaders* shaders;
	// Collisions
	int collision_autoprocess;
	Set* collision_set;
	int coll_array_update;
	YAGLCollisionProc collision_proc;
	Sprite** collision_array;
	int collision_array_size;
	#ifdef YAGL_ADVANCED_COLLISIONS
	SpriteCouple* spr_cpl;
	#endif
};

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

/* System */
inline void __set_blend_mode(eBLEND_MODE mode);

inline void __t_engin_init(Engin* engin);
inline void __opengl_init (int win_w, int win_h);
inline int __opengl_shaders_init (Shaders* shaders, const int fatal_fail);
inline void __opengl_last_err ();

inline void __collision_init ();
inline void __collision_terminate ();

/* Custom callbacks */
void __Internal_WinSizeProc (int w, int h);
void __Internal_MousePosProc (int x, int y);

/* Debug output */
inline void __DEBUG_TIME__ (char text[], int size);
inline void __DEBUG_PRINT__ (const char text[]);
inline void __DEBUG__ (const char text[], int err_lvl);

/* Mouse pos correction according to vide mode */
inline void __correct_get_mouse_pos (int* x, int* y);
inline void __correct_set_mouse_pos (int* x, int* y);

/* Random numbers */
inline int __rnd_int (int min, int max);
inline double __rnd_double (double min, double max);

/* geometry */
inline void __reduce_angle(float* angle);
inline float __vect_len(float x, float y);
inline void __polar_2_cartesian(float len, float angle, float* x, float* y);
inline void __cartesian_2_polar(float x, float y, float* angle, float* len);

/* Glow */
inline unsigned int __glow_texture();
inline void __gl_glow_line(int x1, int y1, int x2, int y2, int width);

#endif // __INTERNAL_H__
