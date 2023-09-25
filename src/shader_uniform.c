/**
    \addtogroup 150_shaders
    @{
*/

#include <string.h>

#include "all.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- **/

int         YAGL_API    Shader_UniformGetLocation (Shader* shd, const char* name)
{
    return _engin_->shaders->glGetUniformLocation(shd->program, name);
}

void        YAGL_API    Shader_UniformGetActive (Shader* shd, int id, int* lenght, int* size, eSHADER_UNIFORM_TYPE* type, char* name, int name_len)
{
    _engin_->shaders->glGetActiveUniform(shd->program, id, name_len, lenght, size, type, name);
}

void        YAGL_API    Shader_UniformGetF (Shader* shd, int id, float* data)
{
    _engin_->shaders->glGetUniformfv(shd->program, id, data);
}

void        YAGL_API    Shader_UniformGetI (Shader* shd, int id, int* data)
{
    _engin_->shaders->glGetUniformiv(shd->program, id, data);
}


void        YAGL_API    Shader_UniformSet1F (int id, float v1)
{
    _engin_->shaders->glUniform1f(id, v1);
}

void        YAGL_API    Shader_UniformSet2F (int id, float v1, float v2)
{
    _engin_->shaders->glUniform2f(id, v1, v2);
}

void        YAGL_API    Shader_UniformSet3F (int id, float v1, float v2, float v3)
{
    _engin_->shaders->glUniform3f(id, v1, v2, v3);
}

void        YAGL_API    Shader_UniformSet4F (int id, float v1, float v2, float v3, float v4)
{
    _engin_->shaders->glUniform4f(id, v1, v2, v3, v4);
}

void        YAGL_API    Shader_UniformSet1I (int id, int v1)
{
    _engin_->shaders->glUniform1i(id, v1);
}

void        YAGL_API    Shader_UniformSet2I (int id, int v1, int v2)
{
    _engin_->shaders->glUniform2i(id, v1, v2);
}

void        YAGL_API    Shader_UniformSet3I (int id, int v1, int v2, int v3)
{
    _engin_->shaders->glUniform3i(id, v1, v2, v3);
}

void        YAGL_API    Shader_UniformSet4I (int id, int v1, int v2, int v3, int v4)
{
    _engin_->shaders->glUniform4i(id, v1, v2, v3, v4);
}


void        YAGL_API    Shader_UniformSet1Fv (int id, int count, float* v)
{
    _engin_->shaders->glUniform1fv(id, count, v);
}

void        YAGL_API    Shader_UniformSet2Fv (int id, int count, float* v)
{
    _engin_->shaders->glUniform2fv(id, count, v);
}

void        YAGL_API    Shader_UniformSet3Fv (int id, int count, float* v)
{
    _engin_->shaders->glUniform3fv(id, count, v);
}

void        YAGL_API    Shader_UniformSet4Fv (int id, int count, float* v)
{
    _engin_->shaders->glUniform4fv(id, count, v);
}

void        YAGL_API    Shader_UniformSet1Iv (int id, int count, int* v)
{
    _engin_->shaders->glUniform1iv(id, count, v);
}

void        YAGL_API    Shader_UniformSet2Iv (int id, int count, int* v)
{
    _engin_->shaders->glUniform2iv(id, count, v);
}

void        YAGL_API    Shader_UniformSet3Iv (int id, int count, int* v)
{
    _engin_->shaders->glUniform3iv(id, count, v);
}

void        YAGL_API    Shader_UniformSet4Iv (int id, int count, int* v)
{
    _engin_->shaders->glUniform4iv(id, count, v);
}


void        YAGL_API    Shader_UniformMatrixSet2Fv (int id, int count, int transpose, float* v)
{
    _engin_->shaders->glUniformMatrix2fv(id, count, transpose, v);
}

void        YAGL_API    Shader_UniformMatrixSet3Fv (int id, int count, int transpose, float* v)
{
    _engin_->shaders->glUniformMatrix3fv(id, count, transpose, v);
}

void        YAGL_API    Shader_UniformMatrixSet4Fv (int id, int count, int transpose, float* v)
{
    _engin_->shaders->glUniformMatrix4fv(id, count, transpose, v);
}

void        YAGL_API    Shader_UniformMatrixSet2x3Fv (int id, int count, int transpose, float* v)
{
    _engin_->shaders->glUniformMatrix2x3fv(id, count, transpose, v);
}

void        YAGL_API    Shader_UniformMatrixSet3x2Fv (int id, int count, int transpose, float* v)
{
    _engin_->shaders->glUniformMatrix3x2fv(id, count, transpose, v);
}

void        YAGL_API    Shader_UniformMatrixSet2x4Fv (int id, int count, int transpose, float* v)
{
    _engin_->shaders->glUniformMatrix2x4fv(id, count, transpose, v);
}

void        YAGL_API    Shader_UniformMatrixSet4x2Fv (int id, int count, int transpose, float* v)
{
    _engin_->shaders->glUniformMatrix4x2fv(id, count, transpose, v);
}

void        YAGL_API    Shader_UniformMatrixSet3x4Fv (int id, int count, int transpose, float* v)
{
    _engin_->shaders->glUniformMatrix3x4fv(id, count, transpose, v);
}

void        YAGL_API    Shader_UniformMatrixSet4x3Fv (int id, int count, int transpose, float* v)
{
    _engin_->shaders->glUniformMatrix4x3fv(id, count, transpose, v);
}


/**
    @}
*/
