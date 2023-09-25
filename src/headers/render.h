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

#ifndef __RENDER_H__
#define __RENDER_H__

void    YAGL_API    Render_SetClearColor (const unsigned char red, const unsigned char green, const unsigned char blue);
void    YAGL_API    Render_SetClearColorEx (YAGL_Color color);
void    YAGL_API    Render_InitTimers ();
void    YAGL_API    Render_SetTimersMult (float tm);
float   YAGL_API    Render_GetTimersMult ();
void    YAGL_API    Render_Begin ();
void    YAGL_API    Render_End ();
void    YAGL_API    Render_SetCallbacks (YAGLRenderProc render_proc, YAGLFrameProc frame_proc);
void    YAGL_API    Render_StartLoop (YAGLRenderProc render_proc, YAGLFrameProc frame_proc, int exit_on_win_close);
double  YAGL_API    Render_GetFps (const double delay);
double  YAGL_API    Render_GetDelta ();
void    YAGL_API    Render_SetSwapInterval (const int interval);

#endif // __RENDER_H__
