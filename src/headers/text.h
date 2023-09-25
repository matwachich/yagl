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

#ifndef __TEXT_H__
#define __TEXT_H__

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline void __bmpText_SetText (BmpText* btxt, const char text[]);

/* ------------------------------------------------------------------------- **/
/* Public functions **/

BmpText*    YAGL_API    BmpText_Create (BmpFont* bfnt, const char text[], unsigned int size, int multiligne);
int         YAGL_API    BmpText_IsBmpText (BmpText* btxt);
int         YAGL_API    BmpText_Destroy (BmpText* btxt);
void        YAGL_API    BmpText_SetText (BmpText* btxt, const char text[]);
int         YAGL_API    BmpText_GetLen (BmpText* btxt);
void        YAGL_API    BmpText_Draw (BmpText* btxt);

#endif // __TEXT_H__
