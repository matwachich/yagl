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

#ifndef __EVENTS_H__
#define __EVENTS_H__

void    YAGL_API    Events_KeySetRepeat (const int status);
int     YAGL_API    Events_KeyGetRepeat ();
int     YAGL_API    Events_KeyGet (const int key);
void    YAGL_API    Events_MouseGetPos (int* x, int* y);
int     YAGL_API    Events_MouseGetButton (const int button);
int     YAGL_API    Events_MouseGetWheel ();
void    YAGL_API    Events_MouseSetPos (int x, int y);
void    YAGL_API    Events_MouseSetWheel (const int pos);
void    YAGL_API    Events_MouseSetPosMode (eMOUSE_POS_MODE mode);
int     YAGL_API    Events_MouseGetPosMode ();

void    YAGL_API    Events_SetMousePosCallback (YAGLMousePosProc proc);
void    YAGL_API    Events_SetMouseButtonCallback (YAGLMouseButtonProc proc);
void    YAGL_API    Events_SetMouseWheelCallback (YAGLMouseWheelProc proc);
void    YAGL_API    Events_SetKeyCallback (YAGLKeyProc proc);
void    YAGL_API    Events_SetCharCallback (YAGLCharProc proc);

#endif // __EVENTS_H__
