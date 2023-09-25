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

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

/* ------------------------------------------------------------------------- **/
/* Public functions **/

int     YAGL_API    System_Init (eDEBUG debug_mode);
void    YAGL_API    System_DebugOut (const char* data, int err_lvl);
void    YAGL_API    System_SetDebugCallback (YAGLDebugProc debug_proc);
void    YAGL_API    System_Terminate ();
int     YAGL_API    System_GetVideoModesCount ();
void    YAGL_API    System_GetVideoMode (int mode, int* width, int* height, int* red_bits, int* green_bits, int* blue_bits);
void    YAGL_API    System_GetDesktopMode (int* width, int* height, int* red_bits, int* green_bits, int* blue_bits);
void    YAGL_API    System_GetStats (int* num_textures, int* num_texture_maps, int* num_quads, int* num_sprites, int* num_sprite_sets, int* num_animations, int* num_particle_emitters, int* num_shaders, int* num_bmp_fonts, int* num_bmp_texts);
void    YAGL_API    System_GetVersion (eVERSION flag, int* major, int* minor, int* revision);

#endif // __SYSTEM_H__
