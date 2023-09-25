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

#ifndef __FONT_H__
#define __FONT_H__

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline int __bmpFont_Measure(BmpFont* bfnt, const char text[], int size);
inline void __bmpFont_Print (BmpFont* bfnt, const char text[], int x, int y, int size, eALIGN align, float angle);
inline void __bmpFont_PrintLines (BmpFont* bfnt, const char text[], int x, int y, int size, eALIGN align, float angle);
inline void __bmpFont_clean (BmpFont* bfnt);

/* ------------------------------------------------------------------------- **/
/* Public functions **/

BmpFont*    YAGL_API    BmpFont_Create (const char fnt_file[], const char img_file[]);
int         YAGL_API    BmpFont_IsBmpFont (BmpFont* bfnt);
int         YAGL_API    BmpFont_Destroy (BmpFont* bfnt);
int         YAGL_API    BmpFont_CharExists (BmpFont* bfnt, const char chr);
void        YAGL_API    BmpFont_Print (BmpFont* bfnt, const char text[], int x, int y, int size, eALIGN align, float angle);
void        YAGL_API    BmpFont_PrintLines (BmpFont* bfnt, const char text[], int x, int y, int size, eALIGN align, float angle);
int         YAGL_API    BmpFont_Measure (BmpFont* bfnt, const char text[], int size);

//int         YAGL_API    BmpFont_GetFaceName (BmpFont* bfnt, char* face_name);
//int         YAGL_API    BmpFont_GetCharsCount (BmpFont* bfnt);

#endif // __FONT_H__
