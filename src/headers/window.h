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

#ifndef __WINDOW_H__
#define __WINDOW_H__

int     YAGL_API    Window_Create (const int width, const int height, const int red_bits, const int green_bits, const int blue_bits, const int fullscreen, const char title[], int resizable, const int multisample);
int     YAGL_API    Window_CreateEx(int video_mode_id, const char title[], int multisample);
void    YAGL_API    Window_Close ();
int     YAGL_API    Window_IsOpened ();
void    YAGL_API    Window_Center ();
void    YAGL_API    Window_SetPos (const int x, const int y);
void    YAGL_API    Window_SetSize (const int w, const int h);
void    YAGL_API    Window_GetSize (int* w, int* h);
void    YAGL_API    Window_SetTitle (const char title[]);
void    YAGL_API    Window_SetVisible (const int flag);
int     YAGL_API    Window_IsVisible ();
int     YAGL_API    Window_IsActive ();
int     YAGL_API    Window_IsAccelerated ();
void    YAGL_API    Window_Capture (const char filepath[], eCAPTURE_TYPE type, int x, int y, int w, int h);
void    YAGL_API    Window_SetCursor (const int status);
void    YAGL_API    Window_SetCloseCallback (YAGLWinCloseProc proc);
void    YAGL_API    Window_SetSizeCallback (YAGLWinSizeProc proc);
void    YAGL_API    Window_SetRefreshCallback (YAGLWinRefreshProc proc);

#endif // __WINDOW_H__
