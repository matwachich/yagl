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

#ifndef __DRAW_H__
#define __DRAW_H__

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline void __draw_bind_glow();

/* ------------------------------------------------------------------------- **/
/* Public functions **/

void    YAGL_API    Draw_SetParams (YAGL_Color color, eBLEND_MODE blend_mode, int size, int glow);
void    YAGL_API    Draw_SetColor (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
void    YAGL_API    Draw_SetColorEx (YAGL_Color color);
void    YAGL_API    Draw_SetBlendMode (eBLEND_MODE blend_mode);
void    YAGL_API    Draw_SetGlow (int status);
void    YAGL_API    Draw_SetSize (int size);
void    YAGL_API    Draw_Point (int x, int y);
void    YAGL_API    Draw_Points (int points[], int nbr);
void    YAGL_API    Draw_Line (int x1, int y1, int x2, int y2);
void    YAGL_API    Draw_Lines (int points[], int nbr, int strip);
void    YAGL_API    Draw_Triangle (int x1, int y1, int x2, int y2, int x3, int y3);
void    YAGL_API    Draw_TriangleF (int x1, int y1, int x2, int y2, int x3, int y3);
void    YAGL_API    Draw_Rect (int x, int y, int w, int h, float angle);
void    YAGL_API    Draw_RectF (int x, int y, int w, int h, float angle);
void    YAGL_API    Draw_RectCenter (int x, int y, int w, int h, float angle);
void    YAGL_API    Draw_RectCenterF (int x, int y, int w, int h, float angle);
void    YAGL_API    Draw_Ellipse (int x, int y, int rx, int ry, float angle, int precision);
void    YAGL_API    Draw_EllipseF (int x, int y, int rx, int ry, float angle, int precision);
void    YAGL_API    Draw_EllipseRect (int x, int y, int w, int h, float angle, int precision);
void    YAGL_API    Draw_EllipseRectF (int x, int y, int w, int h, float angle, int precision);

#endif // __DRAW_H__
