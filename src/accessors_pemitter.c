/**
    \addtogroup 140_particles
    @{
*/

/**
    \defgroup _accessors_particles Particle emitter accessors
    \brief Functions for accessing Particle emitters data
*/

/**
    \addtogroup _accessors_particles
    @{
*/

#define EMITTER_CHECK if (mem_exists(emit, PTR_PARTICLES) == 0) { return; }
#define EMITTER_CHECK_RET(ret) if (mem_exists(emit, PTR_PARTICLES) == 0) { return ret; }

#include "all.h"

void            YAGL_API    PEmitter_SetVisible (PEmitter* emit, int visible)
{
    EMITTER_CHECK

    emit->visible = visible;
}

int             YAGL_API    PEmitter_GetVisible (PEmitter* emit)
{
    EMITTER_CHECK_RET(0)

    return emit->visible;
}

void            YAGL_API    PEmitter_SetPos (PEmitter* emit, float x, float y)
{
    EMITTER_CHECK

    emit->pos.x = x;
    emit->pos.y = y;
}

void            YAGL_API    PEmitter_GetPos (PEmitter* emit, float* x, float* y)
{
    EMITTER_CHECK

    if (x != NULL) { *x = emit->pos.x; }
    if (y != NULL) { *y = emit->pos.y; }
}

void            YAGL_API    PEmitter_SetPosVar (PEmitter* emit, float x, float y)
{
    EMITTER_CHECK

    emit->pos_var.x = x;
    emit->pos_var.y = y;
}

void            YAGL_API    PEmitter_GetPosVar (PEmitter* emit, float* x, float* y)
{
    EMITTER_CHECK

    if (x != NULL) { *x = emit->pos_var.x; }
    if (y != NULL) { *y = emit->pos_var.y; }
}

void            YAGL_API    PEmitter_SetVel (PEmitter* emit, float vel, float vel_var)
{
    EMITTER_CHECK

    emit->vel = vel;
    emit->vel_var = vel_var;
}

void            YAGL_API    PEmitter_GetVel (PEmitter* emit, float* vel, float* vel_var)
{
    EMITTER_CHECK

    if (vel != NULL) { *vel = emit->vel; }
    if (vel_var != NULL) { *vel_var = emit->vel_var; }
}

void            YAGL_API    PEmitter_SetAccel (PEmitter* emit, float accel, float accel_var)
{
    EMITTER_CHECK

    emit->accel = accel;
    emit->accel_var = accel_var;
}

void            YAGL_API    PEmitter_GetAccel (PEmitter* emit, float* accel, float* accel_var)
{
    EMITTER_CHECK

    if (accel != NULL) { *accel = emit->accel; }
    if (accel_var != NULL) { *accel_var = emit->accel_var; }
}

void            YAGL_API    PEmitter_SetAngle (PEmitter* emit, float angle, float angle_var)
{
    EMITTER_CHECK

    emit->angle = angle;
    emit->angle_var = angle_var;
}

void            YAGL_API    PEmitter_GetAngle (PEmitter* emit, float* angle, float* angle_var)
{
    EMITTER_CHECK

    if (angle != NULL) { *angle = emit->angle; }
    if (angle_var != NULL) { *angle_var = emit->angle_var; }
}

void            YAGL_API    PEmitter_SetForce (PEmitter* emit, float force, float force_var)
{
    EMITTER_CHECK

    emit->force = force;
    emit->force_var = force_var;
}

void            YAGL_API    PEmitter_GetForce (PEmitter* emit, float* force, float* force_var)
{
    EMITTER_CHECK

    if (force != NULL) { *force = emit->force; }
    if (force_var != NULL) { *force_var = emit->force_var; }
}

void            YAGL_API    PEmitter_SetForceAngle (PEmitter* emit, float f_angle, float f_angle_var)
{
    EMITTER_CHECK

    emit->force_angle = f_angle;
    emit->force_angle_var = f_angle_var;
}

void            YAGL_API    PEmitter_GetForceAngle (PEmitter* emit, float* f_angle, float* f_angle_var)
{
    EMITTER_CHECK

    if (f_angle != NULL) { *f_angle = emit->force_angle; }
    if (f_angle_var != NULL) { *f_angle_var = emit->force_angle_var; }
}

void            YAGL_API    PEmitter_SetInnertia (PEmitter* emit, float innertia, float innertia_var)
{
    EMITTER_CHECK

    emit->p_innertia = innertia;
    emit->p_innertia_var = innertia_var;
}

void            YAGL_API    PEmitter_GetInnertia (PEmitter* emit, float* innertia, float* innertia_var)
{
    EMITTER_CHECK

    if (innertia != NULL) { *innertia = emit->p_innertia; }
    if (innertia_var != NULL) { *innertia_var = emit->p_innertia_var; }
}

void            YAGL_API    PEmitter_SetParticleAngle (PEmitter* emit, float angle, float angle_var)
{
    EMITTER_CHECK

    emit->p_angle = angle;
    emit->p_angle_var = angle_var;
}

void            YAGL_API    PEmitter_GetParticleAngle (PEmitter* emit, float* angle, float* angle_var)
{
    EMITTER_CHECK

    if (angle != NULL) { *angle = emit->p_angle; }
    if (angle_var != NULL) { *angle_var = emit->p_angle_var; }
}

void            YAGL_API    PEmitter_SetSpin (PEmitter* emit, float spin, float spin_var, float spin_flyvar)
{
    EMITTER_CHECK

    emit->spin = spin;
    emit->spin_var = spin_var;
    emit->spin_flyvar = spin_flyvar;
}

void            YAGL_API    PEmitter_GetSpin (PEmitter* emit, float* spin, float* spin_var, float* spin_flyvar)
{
    EMITTER_CHECK

    if (spin != NULL) { *spin = emit->spin; }
    if (spin_var != NULL) { *spin_var = emit->spin_var; }
    if (spin_flyvar != NULL) { *spin_flyvar = emit->spin_flyvar; }
}

void            YAGL_API    PEmitter_SetSize (PEmitter* emit, float size, float size_var, float size_flyvar)
{
    EMITTER_CHECK

    emit->size = size;
    emit->size_var = size_var;
    emit->size_flyvar = size_flyvar;
}

void            YAGL_API    PEmitter_GetSize (PEmitter* emit, float* size, float* size_var, float* size_flyvar)
{
    EMITTER_CHECK

    if (size != NULL) { *size = emit->size; }
    if (size_var != NULL) { *size_var = emit->size_var; }
    if (size_flyvar != NULL) { *size_flyvar = emit->size_flyvar; }
}

void            YAGL_API    PEmitter_SetLife (PEmitter* emit, float life, float life_var)
{
    EMITTER_CHECK

    emit->life = life;
    emit->life_var = life_var;
}

void            YAGL_API    PEmitter_GetLife (PEmitter* emit, float* life, float* life_var)
{
    EMITTER_CHECK

    if (life != NULL) { *life = emit->life; }
    if (life_var != NULL) { *life_var = emit->life_var; }
}

void            YAGL_API    PEmitter_SetEmitteRate (PEmitter* emit, unsigned int particles_per_second)
{
    EMITTER_CHECK

    emit->p_per_sec = particles_per_second;
}

unsigned int    YAGL_API    PEmitter_GetEmitteRate (PEmitter* emit)
{
    EMITTER_CHECK_RET(0)

    return emit->p_per_sec;
}

void            YAGL_API    PEmitter_SetMaxParticles (PEmitter* emit, unsigned int max)
{
    EMITTER_CHECK

    emit->max_particles = max;
}

unsigned int    YAGL_API    PEmitter_GetMaxParticles (PEmitter* emit)
{
    EMITTER_CHECK_RET(0)

    return emit->max_particles;
}

void            YAGL_API    PEmitter_SetBlendMode (PEmitter* emit, eBLEND_MODE blend_mode)
{
    EMITTER_CHECK

    emit->blend_mode = blend_mode;
}

int             YAGL_API    PEmitter_GetBlendMode (PEmitter* emit)
{
    EMITTER_CHECK_RET(-1)

    return emit->blend_mode;
}

void            YAGL_API    PEmitter_SetColor (PEmitter* emit, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    EMITTER_CHECK

    emit->col_r = r;
    emit->col_g = g;
    emit->col_b = b;
    emit->col_a = a;
}

void            YAGL_API    PEmitter_SetColorVar (PEmitter* emit, short r, short g, short b, short a)
{
    EMITTER_CHECK

    emit->col_r_var = r;
    emit->col_g_var = g;
    emit->col_b_var = b;
    emit->col_a_var = a;
}

void            YAGL_API    PEmitter_SetColorFlyVar (PEmitter* emit, short r, short g, short b, short a)
{
    EMITTER_CHECK

    emit->col_r_flyvar = r;
    emit->col_g_flyvar = g;
    emit->col_b_flyvar = b;
    emit->col_a_flyvar = a;
}

void            YAGL_API    PEmitter_GetColor (PEmitter* emit, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a)
{
    EMITTER_CHECK

    if (r != NULL) { *r = emit->col_r; }
    if (g != NULL) { *g = emit->col_g; }
    if (b != NULL) { *b = emit->col_b; }
    if (a != NULL) { *a = emit->col_a; }
}

void            YAGL_API    PEmitter_GetColorVar (PEmitter* emit, short* r, short* g, short* b, short* a)
{
    EMITTER_CHECK

    if (r != NULL) { *r = emit->col_r_var; }
    if (g != NULL) { *g = emit->col_g_var; }
    if (b != NULL) { *b = emit->col_b_var; }
    if (a != NULL) { *a = emit->col_a_var; }
}

void            YAGL_API    PEmitter_GetColorFlyVar (PEmitter* emit, short* r, short* g, short* b, short* a)
{
    EMITTER_CHECK

    if (r != NULL) { *r = emit->col_r_flyvar; }
    if (g != NULL) { *g = emit->col_g_flyvar; }
    if (b != NULL) { *b = emit->col_b_flyvar; }
    if (a != NULL) { *a = emit->col_a_flyvar; }
}

void            YAGL_API    PEmitter_SetCallbacks (PEmitter* emit, YAGLParticleSpawnProc emitte_proc, YAGLParticleDeadProc dead_proc)
{
    EMITTER_CHECK

    emit->p_emitte_proc = emitte_proc;
    emit->p_dead_proc = dead_proc;
}

unsigned int    YAGL_API    PEmitter_GetCount (PEmitter* emit)
{
    EMITTER_CHECK_RET(0)

    return emit->count;
}

/**
    @}
*/

/**
    @}
*/
