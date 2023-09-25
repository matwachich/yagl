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

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

float   YAGL_API    Geo_PtoP_Dist (int x1, int y1, int x2, int y2);
float   YAGL_API    Geo_PtoP_Angle (int x1, int y1, int x2, int y2);
void    YAGL_API    Geo_PtoP_Vect (int x1, int y1, int x2, int y2, float len, float* v_x, float* v_y);

float   YAGL_API    Geo_SprtoP_Dist (Sprite* spr, int x, int y);
float   YAGL_API    Geo_SprtoP_Angle (Sprite* spr, int x, int y);
float   YAGL_API    Geo_SprtoP_AngleDiff (Sprite* spr, int x, int y);
void    YAGL_API    Geo_SprtoP_Vect (Sprite* spr, int x, int y, float len, float* v_x, float* v_y);

float   YAGL_API    Geo_SprtoSpr_Dist (Sprite* spr1, Sprite* spr2);
float   YAGL_API    Geo_SprtoSpr_Angle (Sprite* spr1, Sprite* spr2);
float   YAGL_API    Geo_SprtoSpr_AngleDiff (Sprite* spr1, Sprite* spr2);
void    YAGL_API    Geo_SprtoSpr_Vect (Sprite* spr1, Sprite* spr2, float len, float* v_x, float* v_y);

void    YAGL_API    Geo_PolarToCartesian (float angle, float len, float* x, float* y);
void    YAGL_API    Geo_CartesianToPolar (float x, float y, float* angle, float* len);

#endif // __GEOMETRY_H__
