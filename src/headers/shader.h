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

#ifndef __SHADER_H__
#define __SHADER_H__

/* -------------------------------------------------------------------------- */
/* Private functions */

inline const char* __shader_load (const char* filepath);
inline int __shader_add_source (Shader* shd, const char* source, eSHADER_TYPE type);
inline int __shader_check_compilation (GLuint shader_id, int err_lvl);
inline int __shader_program_check_linkage (GLuint program_id, int err_lvl);
inline void __shader_use (GLuint id);

/* ------------------------------------------------------------------------- */
/* Public functions */

int         YAGL_API    Shader_Init (const int fatal_fail);
int         YAGL_API    Shader_IsInit ();
void        YAGL_API    Shader_SetCompileErrFatal (const int flag);
void        YAGL_API    Shader_SetLinkErrFatal (const int flag);
void        YAGL_API    Shader_SetInfoLogShow (const int flag);
Shader*     YAGL_API    Shader_Create ();
int         YAGL_API    Shader_IsShader (Shader* shd);
int         YAGL_API    Shader_AddSource (Shader* shd, const char* source, eSHADER_TYPE type);
int         YAGL_API    Shader_AddSourceFile (Shader* shd, const char* filepath, eSHADER_TYPE type);
int         YAGL_API    Shader_Link (Shader* shd);
int         YAGL_API    Shader_IsReady (Shader* shd);
int         YAGL_API    Shader_Destroy (Shader* shd);
void        YAGL_API    Shader_Use (Shader* shd);

int         YAGL_API    Shader_UniformGetLocation (Shader* shd, const char* name);
void        YAGL_API    Shader_UniformGetActive (Shader* shd, int id, int* lenght, int* size, eSHADER_UNIFORM_TYPE* type, char* name, int name_len);
void        YAGL_API    Shader_UniformGetF (Shader* shd, int id, float* data);
void        YAGL_API    Shader_UniformGetI (Shader* shd, int id, int* data);

void        YAGL_API    Shader_UniformSet1F (int id, float v1);
void        YAGL_API    Shader_UniformSet2F (int id, float v1, float v2);
void        YAGL_API    Shader_UniformSet3F (int id, float v1, float v2, float v3);
void        YAGL_API    Shader_UniformSet4F (int id, float v1, float v2, float v3, float v4);
void        YAGL_API    Shader_UniformSet1I (int id, int v1);
void        YAGL_API    Shader_UniformSet2I (int id, int v1, int v2);
void        YAGL_API    Shader_UniformSet3I (int id, int v1, int v2, int v3);
void        YAGL_API    Shader_UniformSet4I (int id, int v1, int v2, int v3, int v4);

void        YAGL_API    Shader_UniformSet1Fv (int id, int count, float* v);
void        YAGL_API    Shader_UniformSet2Fv (int id, int count, float* v);
void        YAGL_API    Shader_UniformSet3Fv (int id, int count, float* v);
void        YAGL_API    Shader_UniformSet4Fv (int id, int count, float* v);
void        YAGL_API    Shader_UniformSet1Iv (int id, int count, int* v);
void        YAGL_API    Shader_UniformSet2Iv (int id, int count, int* v);
void        YAGL_API    Shader_UniformSet3Iv (int id, int count, int* v);
void        YAGL_API    Shader_UniformSet4Iv (int id, int count, int* v);

void        YAGL_API    Shader_UniformMatrixSet2Fv (int id, int count, int transpose, float* v);
void        YAGL_API    Shader_UniformMatrixSet3Fv (int id, int count, int transpose, float* v);
void        YAGL_API    Shader_UniformMatrixSet4Fv (int id, int count, int transpose, float* v);
void        YAGL_API    Shader_UniformMatrixSet2x3Fv (int id, int count, int transpose, float* v);
void        YAGL_API    Shader_UniformMatrixSet3x2Fv (int id, int count, int transpose, float* v);
void        YAGL_API    Shader_UniformMatrixSet2x4Fv (int id, int count, int transpose, float* v);
void        YAGL_API    Shader_UniformMatrixSet4x2Fv (int id, int count, int transpose, float* v);
void        YAGL_API    Shader_UniformMatrixSet3x4Fv (int id, int count, int transpose, float* v);
void        YAGL_API    Shader_UniformMatrixSet4x3Fv (int id, int count, int transpose, float* v);

#endif // __SHADER_H__
