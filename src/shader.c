/**
    \addtogroup 150_shaders
    @{
*/

#include <string.h>

#include "all.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- **/
/* Public functions **/

inline const char* __shader_load (const char* filepath)
{
    FILE* fp = fopen(filepath, "rb");
    if(fp == NULL) {
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);

    rewind(fp);

    char* src = calloc(size + 1, sizeof(char)); // +1 pour le caractere de fin de chaine '\0'
    if(src == NULL) {
        fclose(fp);
        __DEBUG__("Unbale to load shader source! (Out of memory)", 2);
    }

    fread(src, sizeof(char), size, fp);
    src[size] = '\0';

    fclose(fp);

    return src;
}

inline int __shader_add_source (Shader* shd, const char* source, eSHADER_TYPE type)
{
    switch (type) {
        case SHADER_VERTEX: type = GL_VERTEX_SHADER; break;
        case SHADER_FRAGMENT: type = GL_FRAGMENT_SHADER; break;
    }

    GLuint shader_id = _engin_->shaders->glCreateShader(type);
    _engin_->shaders->glShaderSource(shader_id, 1, &source, NULL);
    _engin_->shaders->glCompileShader(shader_id);

    int err_lvl = 1;
    if (_engin_->shaders->compile_err_fatal != 0) {
        err_lvl = 2;
    }

    if (__shader_check_compilation(shader_id, err_lvl) == 0) {
        _engin_->shaders->glDeleteShader(shader_id);
        return 0;
    } else {
        _engin_->shaders->glAttachShader(shd->program, shader_id);
        _engin_->shaders->glDeleteShader(shader_id);
        return 1;
    }
}

inline int __shader_check_compilation (GLuint shader_id, int err_lvl)
{
    GLint compile_status = 0;
    _engin_->shaders->glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);

    if (compile_status != GL_TRUE) {
        if (_engin_->shaders->show_info_log != 0) {
            GLsizei log_size = 0;
            _engin_->shaders->glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_size);

            if (log_size == 0) {
                if (err_lvl == 2) { _engin_->shaders->glDeleteShader(shader_id); }

                __DEBUG__("Unable to compile Shader: [no info log]", err_lvl);
                return 0;
            }

            char* log = malloc(log_size);
            if (log == NULL) {
                _engin_->shaders->glDeleteShader(shader_id);
                __DEBUG__("Unable to compile Shader! (Out of memory)", 2);
            }

            //GLsizei size = 0;
            _engin_->shaders->glGetShaderInfoLog(shader_id, log_size, NULL, log);

            char* debug = malloc(sizeof(char) * (log_size + 26));
            sprintf(debug, "Unable to compile Shader:\n%s", log);

            if (err_lvl == 2) { _engin_->shaders->glDeleteShader(shader_id); }
            __DEBUG__(debug, err_lvl);

            free((void*)log);
            free((void*)debug);
        } else {
            if (err_lvl == 2) { _engin_->shaders->glDeleteShader(shader_id); }
            __DEBUG__("Unable to compile Shader", err_lvl);
        }
        // ---
        return 0;
    } else {
        return 1;
    }
}

inline int __shader_program_check_linkage (GLuint program_id, int err_lvl)
{
    GLint link_status = 0;
    _engin_->shaders->glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);

    if (link_status != GL_TRUE) {
        if (_engin_->shaders->show_info_log != 0) {
            GLsizei log_size = 0;
            _engin_->shaders->glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_size);

            printf("Log Size: %i\n", log_size);
            fflush(NULL);

            if (log_size == 0) {
                __DEBUG__("Unable to link Shader: [no info log]", err_lvl);
                return 0;
            }

            char* log = malloc(log_size);
            if (log == NULL) {
                __DEBUG__("Unable to link Shader! (Out of memory)", 2);
            }

            _engin_->shaders->glGetProgramInfoLog(program_id, log_size, NULL, log);

            printf("Log strlen: %i\n", strlen(log));
            fflush(NULL);
            __opengl_last_err("glGetProgramInfoLog");

            char* debug = malloc(sizeof(char) * (log_size + 23));
            sprintf(debug, "Unable to link Shader:\n%s", log);
            __DEBUG__(debug, err_lvl);

            free((void*)log);
            free((void*)debug);
        } else {
            __DEBUG__("Unable to link Shader", err_lvl);
        }
        // ---
        return 0;
    } else {
        return 1;
    }
}

inline void __shader_use (GLuint id)
{
    if (_engin_->shaders->current_shader != id) {
        _engin_->shaders->glUseProgram(id);
        _engin_->shaders->current_shader = id;
    }
}

/* ------------------------------------------------------------------------- **/
/* Public functions **/

/*
Function: Shader_Init

Parameters:

Return:

*/
int   YAGL_API    Shader_Init (const int fatal_fail)
{
    if (_engin_->shaders != NULL) { return 1; }

    _engin_->shaders = malloc(sizeof(Shaders));
    if (_engin_->shaders == NULL) {
        __DEBUG__("Unable to intialize shaders! (Out of memory)", 2);
    }

    if (__opengl_shaders_init(_engin_->shaders, fatal_fail) == 0) {
        free(_engin_->shaders);
        _engin_->shaders = NULL;
        return 0;
    }

    return 1;
}

/*
Function: Shader_IsInit

Parameters:

Return:

*/
int   YAGL_API    Shader_IsInit ()
{
    if (_engin_->shaders != NULL) { return 1; }
    return 0;
}

/*
Function: Shader_SetCompileErrFatal

Parameters:

Return:

*/
void        YAGL_API    Shader_SetCompileErrFatal (const int flag)
{
    if (_engin_->shaders == NULL) { return; }

    _engin_->shaders->compile_err_fatal = flag;
}

/*
Function: Shader_SetLinkErrFatal

Parameters:

Return:

*/
void        YAGL_API    Shader_SetLinkErrFatal (const int flag)
{
    if (_engin_->shaders == NULL) { return; }

    _engin_->shaders->link_err_fatal = flag;
}

/*
Function: Shader_SetInfoLogShow

Parameters:

Return:

*/
void        YAGL_API    Shader_SetInfoLogShow (const int flag)
{
    if (_engin_->shaders == NULL) { return; }

    _engin_->shaders->show_info_log = flag;
}

/*
Function: Shader_Create

Parameters:

Return:

*/
Shader*     YAGL_API    Shader_Create ()
{
    if (_engin_->shaders == NULL) { return NULL; }

    Shader* shd = mem_alloc(sizeof(Shader), PTR_SHADER);
    if (shd == NULL) {
        __DEBUG__("Unable to create Shader! (Out of memory)", 2);
    }

    shd->ready = 0;
    shd->program = _engin_->shaders->glCreateProgram();

    return shd;
}

/*
Function: Shader_IsShader

Parameters:

Return:

*/
int   YAGL_API    Shader_IsShader (Shader* shd)
{
    if (_engin_->shaders == NULL) { return 0; }

    return mem_exists(shd, PTR_SHADER);
}

/*
Function: Shader_AddSource

Parameters:

Return:

*/
int   YAGL_API    Shader_AddSource (Shader* shd, const char* source, eSHADER_TYPE type)
{
    if (_engin_->shaders == NULL || mem_exists(shd, PTR_SHADER) == 0) { return 0; }
    if (shd->ready != 0) { return 0; }

    return __shader_add_source(shd, source, type);
}

/*
Function: Shader_AddSourceFile

Parameters:

Return:

*/
int   YAGL_API    Shader_AddSourceFile (Shader* shd, const char* filepath, eSHADER_TYPE type)
{
    if (_engin_->shaders == NULL || mem_exists(shd, PTR_SHADER) == 0) { return 0; }
    if (shd->ready != 0) { return 0; }

    const char* source = __shader_load(filepath);
    if (source == NULL) {
        char tmp[22 + strlen(filepath)];
        sprintf(tmp, "Unable to load file: %s", filepath);
        __DEBUG__(tmp, 1);
        return 0;
    }

    int ret = __shader_add_source(shd, source, type);
    free((void*)source);

    return ret;
}

/*
Function: Shader_Compile

Parameters:

Return:

*/
int   YAGL_API    Shader_Link (Shader* shd)
{
    if (_engin_->shaders == NULL || mem_exists(shd, PTR_SHADER) == 0) { return 0; }
    if (shd->ready != 0) { return 0; }

    _engin_->shaders->glLinkProgram(shd->program);

    int err_lvl = 1;
    if (_engin_->shaders->link_err_fatal != 0) { err_lvl = 2; }

    if (__shader_program_check_linkage(shd->program, err_lvl) == 0) {
        return 0;
    } else {
        shd->ready = 1;
        return 1;
    }
}

/*
Function: Shader_IsReady

Parameters:

Return:

*/
int   YAGL_API    Shader_IsReady (Shader* shd)
{
    if (_engin_->shaders == NULL || mem_exists(shd, PTR_SHADER) == 0) { return 0; }

    return shd->ready;
}

/*
Function: Shader_Destroy

Parameters:

Return:

*/
int   YAGL_API    Shader_Destroy (Shader* shd)
{
    if (_engin_->shaders == NULL || mem_exists(shd, PTR_SHADER) == 0) { return 0; }

    if (_engin_->shaders->current_shader == shd->program) {
        _engin_->shaders->glUseProgram(0);
        _engin_->shaders->current_shader = 0;
    }

    _engin_->shaders->glDeleteProgram(shd->program);
    return mem_free(shd, PTR_SHADER);
}

/*
Function: Shader_Activate

Parameters:

Return:

*/
void        YAGL_API    Shader_Use (Shader* shd)
{
    if (_engin_->shaders == NULL || mem_exists(shd, PTR_SHADER) == 0) { return; }
    if (shd->ready == 0) { return; }

    if (shd != NULL) {
        __shader_use(shd->program);
    } else {
        __shader_use(0);
    }
}

/**
    @}
*/
