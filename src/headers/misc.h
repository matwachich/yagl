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

#ifndef __MISC_H__
#define __MISC_H__

void        YAGL_API    Misc_Sleep (const double time);
void        YAGL_API    Misc_TimersSetFollowMult (int follow);
int         YAGL_API    Misc_TimersGetFollowMult ();
double      YAGL_API    Misc_TimerInit ();
double      YAGL_API    Misc_TimerDiff (const double timestamp);
int         YAGL_API    Misc_RandomI (const int min, const int max);
double      YAGL_API    Misc_RandomF (const double min, const double max);
YAGL_Color  YAGL_API    Misc_Color (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
void        YAGL_API    Misc_ColorComponents (YAGL_Color color, unsigned char* red, unsigned char* green, unsigned char* blue, unsigned char* alpha);

#endif // __MISC_H__
