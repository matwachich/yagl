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

#ifndef __ACCESSORS_PEMITTER_H__
#define __ACCESSORS_PEMITTER_H__

/* ------------------------------------------------------------------------- **/
/* Public functions **/

void            YAGL_API    PEmitter_SetVisible (PEmitter* emit, int visible);
int             YAGL_API    PEmitter_GetVisible (PEmitter* emit);

void            YAGL_API    PEmitter_SetPos (PEmitter* emit, float x, float y);
void            YAGL_API    PEmitter_GetPos (PEmitter* emit, float* x, float* y);

void            YAGL_API    PEmitter_SetPosVar (PEmitter* emit, float x, float y);
void            YAGL_API    PEmitter_GetPosVar (PEmitter* emit, float* x, float* y);

void            YAGL_API    PEmitter_SetVel (PEmitter* emit, float vel, float vel_var);
void            YAGL_API    PEmitter_GetVel (PEmitter* emit, float* vel, float* vel_var);

void            YAGL_API    PEmitter_SetAccel (PEmitter* emit, float accel, float accel_var);
void            YAGL_API    PEmitter_GetAccel (PEmitter* emit, float* accel, float* accel_var);

void            YAGL_API    PEmitter_SetAngle (PEmitter* emit, float angle, float angle_var);
void            YAGL_API    PEmitter_GetAngle (PEmitter* emit, float* angle, float* angle_var);

void            YAGL_API    PEmitter_SetForce (PEmitter* emit, float force, float force_var);
void            YAGL_API    PEmitter_GetForce (PEmitter* emit, float* force, float* force_var);

void            YAGL_API    PEmitter_SetForceAngle (PEmitter* emit, float f_angle, float f_angle_var);
void            YAGL_API    PEmitter_GetForceAngle (PEmitter* emit, float* f_angle, float* f_angle_var);

void            YAGL_API    PEmitter_SetInnertia (PEmitter* emit, float innertia, float innertia_var);
void            YAGL_API    PEmitter_GetInnertia (PEmitter* emit, float* innertia, float* innertia_var);

void            YAGL_API    PEmitter_SetParticleAngle (PEmitter* emit, float angle, float angle_var);
void            YAGL_API    PEmitter_GetParticleAngle (PEmitter* emit, float* angle, float* angle_var);

void            YAGL_API    PEmitter_SetSpin (PEmitter* emit, float spin, float spin_var, float spin_flyvar);
void            YAGL_API    PEmitter_GetSpin (PEmitter* emit, float* spin, float* spin_var, float* spin_flyvar);

void            YAGL_API    PEmitter_SetSize (PEmitter* emit, float size, float size_var, float size_flyvar);
void            YAGL_API    PEmitter_GetSize (PEmitter* emit, float* size, float* size_var, float* size_flyvar);

void            YAGL_API    PEmitter_SetLife (PEmitter* emit, float life, float life_var);
void            YAGL_API    PEmitter_GetLife (PEmitter* emit, float* life, float* life_var);

void            YAGL_API    PEmitter_SetEmitteRate (PEmitter* emit, unsigned int particles_per_second);
unsigned int    YAGL_API    PEmitter_GetEmitteRate (PEmitter* emit);

void            YAGL_API    PEmitter_SetMaxParticles (PEmitter* emit, unsigned int max);
unsigned int    YAGL_API    PEmitter_GetMaxParticles (PEmitter* emit);

void            YAGL_API    PEmitter_SetBlendMode (PEmitter* emit, eBLEND_MODE blend_mode);
int             YAGL_API    PEmitter_GetBlendMode (PEmitter* emit);

void            YAGL_API    PEmitter_SetColor (PEmitter* emit, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void            YAGL_API    PEmitter_SetColorVar (PEmitter* emit, short r, short g, short b, short a);
void            YAGL_API    PEmitter_SetColorFlyVar (PEmitter* emit, short r, short g, short b, short a);
void            YAGL_API    PEmitter_GetColor (PEmitter* emit, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a);
void            YAGL_API    PEmitter_GetColorVar (PEmitter* emit, short* r, short* g, short* b, short* a);
void            YAGL_API    PEmitter_GetColorFlyVar (PEmitter* emit, short* r, short* g, short* b, short* a);

void            YAGL_API    PEmitter_SetCallbacks (PEmitter* emit, YAGLParticleSpawnProc emitte_proc, YAGLParticleDeadProc dead_proc);

unsigned int    YAGL_API    PEmitter_GetCount (PEmitter* emit);

#endif // __ACCESSORS_PEMITTER_H__
