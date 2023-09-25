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

#ifndef __VIEW_H__
#define __VIEW_H__

void    YAGL_API    View_Move (const int x, const int y);
void    YAGL_API    View_SetRect (const int x, const int y, const int w, const int h);
void    YAGL_API    View_GetRect (int* x, int* y, int* w, int* h);
void    YAGL_API    View_SetCorners (const int x1, const int y1, const int x2, const int y2);
void    YAGL_API    View_GetCorners (int* x1, int* y1, int* x2, int* y2);
void    YAGL_API    View_SetCenter (const int x, const int y);
void    YAGL_API    View_GetCenter (int* x, int* y);
void    YAGL_API    View_SetSize (const int w, const int h);
void    YAGL_API    View_GetSize (int* w, int* h);
void    YAGL_API    View_SetZoom (const float factor);
void    YAGL_API    View_AddZoom (float factor);
float   YAGL_API    View_GetZoom ();
void    YAGL_API    View_ScreenToWorld (const int scr_x, const int scr_y, int* world_x, int* world_y);
void    YAGL_API    View_WorldToScreen (const int world_x, const int world_y, int* scr_x, int* scr_y);
int     YAGL_API    View_PointIsVisible (const int x, const int y);

#endif // __VIEW_H__
