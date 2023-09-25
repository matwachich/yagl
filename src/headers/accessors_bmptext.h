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
	AuGL - AutoIt OpenGL
	2D game engin for AutoIt3
	by Matwachich (matwachich at gmail dot com)
*/

#ifndef __ACCESSORS_BMPTEXT_H__
#define __ACCESSORS_BMPTEXT_H__

/* ------------------------------------------------------------------------- **/
/* Public functions **/

char*       YAGL_API    BmpText_GetText (BmpText* btxt);

void        YAGL_API    BmpText_SetFont (BmpText* btxt, BmpFont* bfnt);
BmpFont*    YAGL_API    BmpText_GetFont (BmpText* btxt);

void        YAGL_API    BmpText_SetVisible (BmpText* btxt, int visible);
int         YAGL_API    BmpText_GetVisible (BmpText* btxt);

void        YAGL_API    BmpText_SetMultiligne (BmpText* btxt, int multiligne);
int         YAGL_API    BmpText_GetMultiligne (BmpText* btxt);

void        YAGL_API    BmpText_SetPos (BmpText* btxt, int x, int y);
void        YAGL_API    BmpText_GetPos (BmpText* btxt, int* x, int* y);

void        YAGL_API    BmpText_SetSize (BmpText* btxt, int size);
int         YAGL_API    BmpText_GetSize (BmpText* btxt);

void        YAGL_API    BmpText_SetAlign (BmpText* btxt, eALIGN align);
int         YAGL_API    BmpText_GetAlign (BmpText* btxt);

void        YAGL_API    BmpText_SetAngle (BmpText* btxt, float angle);
float       YAGL_API    BmpText_GetAngle (BmpText* btxt);

void        YAGL_API    BmpText_SetBlendMode (BmpText* btxt, eBLEND_MODE blend_mode);
int         YAGL_API    BmpText_GetBlendMode (BmpText* btxt);

void        YAGL_API    BmpText_SetColor (BmpText* btxt, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void        YAGL_API    BmpText_GetColor (BmpText* btxt, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a);
void        YAGL_API    BmpText_SetColorEx (BmpText* btxt, YAGL_Color color);
YAGL_Color  YAGL_API    BmpText_GetColorEx (BmpText* btxt);

#endif // __ACCESSORS_BMPTEXT_H__
