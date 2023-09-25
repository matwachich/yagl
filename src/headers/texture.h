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

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

/* Internal functions */
inline void __texture_bind(Texture* tex);
inline void __texture_empty(Texture* tex);
inline void __texture_set_default_param(Texture* tex);

/* Public functions */
Texture*    YAGL_API    Texture_CreateEmpty ();
Texture*    YAGL_API    Texture_Create (const char filepath[], eTEXTURE_CHANNELS channels);
Texture*    YAGL_API    Texture_CreateFromMem (const unsigned char* data, const int buffer_size, eTEXTURE_CHANNELS channels);
int         YAGL_API    Texture_IsTexture (Texture* tex);
int         YAGL_API    Texture_Load (Texture* tex, const char filepath[], eTEXTURE_CHANNELS channels);
int         YAGL_API    Texture_LoadFromMem (Texture* tex, const unsigned char* data, const int buffer_size, eTEXTURE_CHANNELS channels);
void        YAGL_API    Texture_SetParameter (Texture* tex, int flag, int value);
void        YAGL_API    Texture_SetDefaultParameter (Texture* tex);
void        YAGL_API    Texture_GetSize (Texture* tex, int* w, int* h);
void        YAGL_API    Texture_SetEmpty (Texture* tex);
int         YAGL_API    Texture_Destroy (Texture* tex);

#endif // __TEXTURE_H__
