
#include <string.h>
#include <time.h>
#include <math.h>

#include "all.h"

Engin* _engin_ = NULL;

// Internal window size handler
void __Internal_WinSizeProc (int w, int h)
{
    glViewport(0, 0, w, h);
	_engin_->window_size.x = w;
	_engin_->window_size.y = h;

	if (_engin_->win_size_proc != NULL) { _engin_->win_size_proc(w, h); }
}

// Internal mouse pos handler
void __Internal_MousePosProc (int x, int y)
{
    __correct_get_mouse_pos(&x, &y); // selon que c'est World's ou Window's relative
	if (_engin_->mouse_pos_proc != NULL) { _engin_->mouse_pos_proc(x, y); }
}

// Write info, if err_lvl = 2 Then exit
inline void __DEBUG__(const char text[], int err_lvl)
{
    char* new_text = NULL;
    char str_time[20];

    __DEBUG_TIME__(str_time, 20);

    switch (err_lvl)
    {
        case 0:
            new_text = malloc((strlen(text) + strlen(str_time) + 5 + 1) * sizeof(char));
            sprintf(new_text, "[%s] - %s", str_time, text);
        break;
        case 1:
            new_text = malloc((strlen(text) + strlen(str_time) + 12 + 1) * sizeof(char));
            sprintf(new_text, "[%s] - Error: %s", str_time, text);
        break;
        case 2:
            new_text = malloc((strlen(text) + strlen(str_time) + 18 + 1) * sizeof(char));
            sprintf(new_text, "[%s] - Fatal Error: %s", str_time, text);
        break;
    }
    // ---
    if (_engin_->debug_proc != NULL) {
        _engin_->debug_proc(new_text, err_lvl);
    }
    // ---
    if (_engin_->debug_mode != DEBUG_OFF) {
        switch (err_lvl)
        {
            case 0: __DEBUG_PRINT__(new_text);
            break;
            case 1: __DEBUG_PRINT__(new_text);
            break;
            case 2: __DEBUG_PRINT__(new_text); System_Terminate(); free(new_text); exit(-1);
            break;
        }
    } else {
        if (err_lvl == 2) {
            __DEBUG_PRINT__(new_text);
            System_Terminate();
            free(new_text);
            exit(-1);
        }
    }
    free(new_text);
}

inline void __DEBUG_PRINT__ (const char text[])
{
    switch (_engin_->debug_mode)
    {
        case DEBUG_OFF:
        break;
        case DEBUG_ON_STD:
           printf("%s\n", text);
           fflush(NULL);
        break;
        case DEBUG_ON_FILE:
            fprintf(_engin_->debug_file, "%s\n", text);
        break;
    }
}

inline void __DEBUG_TIME__ (char text[], int size)
{
    time_t tt;
    time(&tt);
    struct tm* t = localtime(&tt);
    strftime(text, size, "%Y/%m/%d %H:%M:%S", t);
}

// Change blend mode only if it needs
inline void __set_blend_mode(eBLEND_MODE mode)
{
    if (mode == BLEND_NO_CHANGE) { return; }

    if (_engin_->current_blend_mode != mode) {
        _engin_->current_blend_mode = mode;
        switch (mode)
        {
            case BLEND_TRANS:
				glDisable(GL_BLEND);
				glEnable(GL_ALPHA_TEST);
            break;
			case BLEND_SOLID:
				glDisable(GL_BLEND);
				glDisable(GL_ALPHA_TEST);
            break;
			case BLEND_BLENDED:
				glEnable(GL_BLEND);
				glEnable(GL_ALPHA_TEST);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            break;
			case BLEND_GLOW:
				glEnable(GL_BLEND);
				glEnable(GL_ALPHA_TEST);
				glBlendFunc(GL_ONE, GL_ONE);
            break;
			case BLEND_ALPHA:
				glEnable(GL_BLEND);
				glEnable(GL_ALPHA_TEST);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;
			case BLEND_BLACK:
				glEnable(GL_BLEND);
				glEnable(GL_ALPHA_TEST);
				glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
            break;
			default:
				glDisable(GL_BLEND);
				glEnable(GL_ALPHA_TEST);
            break;
        }
    }
}

inline void __correct_get_mouse_pos(int* x, int* y)
{
    if (_engin_->mouse_pos_mode == MOUSE_POS_WORLD_RELATIVE) {
        *x = ((*x) * ((float)_engin_->view.w / _engin_->window_size.x)) + (float)_engin_->view.x;
        *y = ((*y) * ((float)_engin_->view.h / _engin_->window_size.y)) + (float)_engin_->view.y;
    }
}

inline void __correct_set_mouse_pos(int* x, int* y)
{
    if (_engin_->mouse_pos_mode == MOUSE_POS_WORLD_RELATIVE) {
        *x = ((*x) * ((float)_engin_->window_size.x / _engin_->view.w)) + (float)_engin_->view.x;
        *y = ((*y) * ((float)_engin_->window_size.y / _engin_->view.h)) + (float)_engin_->view.y;
    }
}

inline int __rnd_int (int min, int max)
{
    return (int)((rand() % (max - min + 1)) + min);
}

inline double __rnd_double (double min, double max)
{
    return ((max - min) * ((double)rand() / RAND_MAX)) + min;
}

inline void __reduce_angle(float* angle)
{
    if (*angle >= 360) {
        while (*angle >= 360) {
            *angle = *angle - 360;
        };
    } else {
        while (*angle < 0) {
            *angle = *angle + 360;
        };
    }
}

inline float __vect_len(float x, float y)
{
    return sqrt((x*x) + (y*y));
}

inline void __polar_2_cartesian(float len, float angle, float* x, float* y)
{
    angle = PI * angle / 180;
    if (x != NULL) { *x = len * cos(angle); }
    if (y != NULL) { *y = len * sin(angle); }
}

inline void __cartesian_2_polar(float x, float y, float* angle, float* len)
{
    if (len != NULL) {
        *len = sqrt((x*x) + (y*y));
        // ---
        if (angle != NULL) {
            *angle = 0;
            if (*len > 0) {
                *angle = fabs(atan(y / x));
                if (x < 0) { *angle = PI - *angle; }
                if (y < 0) { *angle = PI + PI - *angle; }
                *angle = *angle * 180 / PI;
                __reduce_angle(angle);
            }
        }
    }
}

inline void __t_engin_init(Engin* engin)
{
    // debug mode
	engin->debug_mode = 0;
	engin->debug_file = NULL;
	// Video modes
	engin->video_modes = NULL;
	engin->video_modes_count = 0;
	// Window creation
	engin->window_opened = 0;
	engin->fullscreen = 0;
	// Window and View
	engin->window_size.x = 0.0;
	engin->window_size.y = 0.0;
	engin->view.x = 0;
	engin->view.y = 0;
	engin->view.w = 0;
	engin->view.h = 0;
	engin->original_view_size.x = 0;
	engin->original_view_size.y = 0;
	engin->current_zoom = 1.0;
	engin->mouse_pos_mode = MOUSE_POS_WORLD_RELATIVE;
	// Timer and FPS
	engin->old_time = 0.0;
	engin->delta = 0.0;
	engin->delay = 0.0;
	engin->timer_mult = 1.0;
	engin->timer_follow_mult = 1;
	// Callbacks
	engin->win_size_proc = NULL;
	engin->mouse_pos_proc = NULL;
	engin->render_proc = NULL;
	engin->frame_proc = NULL;
	engin->debug_proc = NULL;
	// Events
	engin->key_repeat = 0;
	// Texture
	engin->current_texture = 0;
	// Blend Mode
	engin->current_blend_mode = BLEND_ALPHA;
	// Glow
	engin->glow_texture = 0;
	// Draw
	engin->draw_size = 1;
	engin->draw_color = YAGL_RGBA(255, 255, 255, 255);
	engin->draw_glow_mode = 0;
	engin->draw_blend_mode = BLEND_ALPHA;
	// Circles Display List
	engin->display_list_1x1 = 0;
	engin->display_list_circle = 0;
	engin->display_list_disc = 0;
	// Shaders struct
	engin->shaders = NULL;
	// Collisions
	engin->collision_autoprocess = 1;
	engin->collision_set = NULL;
	engin->coll_array_update = 0;
	engin->collision_proc = NULL;
	engin->collision_array = NULL;
	engin->collision_array_size = 0;
	#ifdef YAGL_ADVANCED_COLLISIONS
	_engin_->spr_cpl = NULL;
	#endif
}

inline void __opengl_init (int win_w, int win_h)
{
    glViewport(0, 0, win_w, win_h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, win_w, win_h, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);

	_engin_->current_blend_mode = BLEND_ALPHA;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearDepth(1.0);

	glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
	glDisable(GL_STENCIL_TEST);
    glDisable(GL_TEXTURE_1D);
    glDisable(GL_LIGHTING);
    glDisable(GL_LOGIC_OP);
    glDisable(GL_DITHER);
    glDisable(GL_FOG);

	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT, GL_FILL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glPointSize(1.0);
    glLineWidth(1.0);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor4f(1.0, 1.0, 1.0, 1.0);

	// 1x1 Display list
	_engin_->display_list_1x1 = glGenLists(1);
	glNewList(_engin_->display_list_1x1, GL_COMPILE);
		glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f(0, 0); glVertex2i(0, 0);
			glTexCoord2f(1, 0); glVertex2i(1, 0);
			glTexCoord2f(1, 1); glVertex2i(1, 1);
			glTexCoord2f(0, 1); glVertex2i(0, 1);
		glEnd();
	glEndList();

	// Glow texture
	_engin_->glow_texture = __glow_texture();

	// Circles display lists
	int i = 0;

	_engin_->display_list_circle = glGenLists(1);
	glNewList(_engin_->display_list_circle, GL_COMPILE);
        glBegin(GL_LINE_STRIP);
            for (i = 0; i <= 90; i++) {
                glVertex2f(cos(2*PI*i/90), sin(2*PI*i/90));
            }
        glEnd();
    glEndList();

    _engin_->display_list_disc = glGenLists(1);
    glNewList(_engin_->display_list_disc, GL_COMPILE);
        glBegin(GL_POLYGON);
            for (i = 0; i <= 90; i++) {
                glVertex2f(cos(2*PI*i/90), sin(2*PI*i/90));
            }
        glEnd();
    glEndList();
}

inline int __opengl_shaders_init (Shaders* shaders, const int fatal_fail)
{
    int err_lvl = 1;
    if (fatal_fail != 0) {
        err_lvl = 2;
    }

    int oglM, oglm, oglrev;
    glfwGetGLVersion(&oglM, &oglm, &oglrev);
    if (oglM < 2) {
        if (oglm < 1) { __DEBUG__("Unable to intialize shaders! (Minimum OpenGL version must be 2.1)", err_lvl); return 0; }
    }

    if (!glfwExtensionSupported("GL_ARB_shading_language_100") || !glfwExtensionSupported("GL_ARB_shader_objects") || !glfwExtensionSupported("GL_ARB_vertex_shader") || !glfwExtensionSupported("GL_ARB_fragment_shader")) {
        __DEBUG__("Unable to intialize shaders! (Extensions are not supported)", err_lvl);
        return 0;
    }

    #define LOAD_GL_FUNC(func_name) shaders->func_name = glfwGetProcAddress(#func_name); \
                                    if (shaders->func_name == NULL) { __DEBUG__("Unable to intialize shaders! ("#func_name" not found)", err_lvl); return 0; }

    //// Shaders base functions
    LOAD_GL_FUNC(glCreateShader)
    LOAD_GL_FUNC(glShaderSource)
    LOAD_GL_FUNC(glCompileShader)
    LOAD_GL_FUNC(glGetShaderiv)
    LOAD_GL_FUNC(glGetShaderInfoLog)
    LOAD_GL_FUNC(glCreateProgram)
    LOAD_GL_FUNC(glAttachShader)
    LOAD_GL_FUNC(glLinkProgram)
    LOAD_GL_FUNC(glGetProgramiv)
    LOAD_GL_FUNC(glGetProgramInfoLog)
    LOAD_GL_FUNC(glUseProgram)
    LOAD_GL_FUNC(glDetachShader)
    LOAD_GL_FUNC(glDeleteProgram)
    LOAD_GL_FUNC(glDeleteShader)

    //// Shader communication
    // Uniforms
    LOAD_GL_FUNC(glGetUniformLocation)
    LOAD_GL_FUNC(glGetUniformfv)
    LOAD_GL_FUNC(glGetUniformiv)
    LOAD_GL_FUNC(glGetActiveUniform)

    LOAD_GL_FUNC(glUniform1f)
    LOAD_GL_FUNC(glUniform2f)
    LOAD_GL_FUNC(glUniform3f)
    LOAD_GL_FUNC(glUniform4f)
    LOAD_GL_FUNC(glUniform1i)
    LOAD_GL_FUNC(glUniform2i)
    LOAD_GL_FUNC(glUniform3i)
    LOAD_GL_FUNC(glUniform4i)

    LOAD_GL_FUNC(glUniform1fv)
    LOAD_GL_FUNC(glUniform2fv)
    LOAD_GL_FUNC(glUniform3fv)
    LOAD_GL_FUNC(glUniform4fv)
    LOAD_GL_FUNC(glUniform1iv)
    LOAD_GL_FUNC(glUniform2iv)
    LOAD_GL_FUNC(glUniform3iv)
    LOAD_GL_FUNC(glUniform4iv)

    LOAD_GL_FUNC(glUniformMatrix2fv)
    LOAD_GL_FUNC(glUniformMatrix3fv)
    LOAD_GL_FUNC(glUniformMatrix4fv)
    LOAD_GL_FUNC(glUniformMatrix2x3fv)
    LOAD_GL_FUNC(glUniformMatrix3x2fv)
    LOAD_GL_FUNC(glUniformMatrix2x4fv)
    LOAD_GL_FUNC(glUniformMatrix4x2fv)
    LOAD_GL_FUNC(glUniformMatrix3x4fv)
    LOAD_GL_FUNC(glUniformMatrix4x3fv)

    ////

    shaders->compile_err_fatal = 0;
    shaders->link_err_fatal = 0;
    shaders->show_info_log = 0;
    shaders->current_shader = 0;

    return 1;
}

inline void __opengl_last_err (const char* indication)
{
    GLenum err = glGetError();
    switch (err) {
        case GL_NO_ERROR: printf("OpenGL [%s]: GL_NO_ERROR\n", indication); break;
        case GL_INVALID_ENUM: printf("OpenGL Error [%s]: GL_INVALID_ENUM\n", indication); break;
        case GL_INVALID_VALUE: printf("OpenGL Error [%s]: GL_INVALID_VALUE\n", indication); break;
        case GL_INVALID_OPERATION: printf("OpenGL Error [%s]: GL_INVALID_OPERATION\n", indication); break;
        case GL_STACK_OVERFLOW: printf("OpenGL Error [%s]: GL_STACK_OVERFLOW\n", indication); break;
        case GL_STACK_UNDERFLOW: printf("OpenGL Error [%s]: GL_STACK_UNDERFLOW\n", indication); break;
        case GL_OUT_OF_MEMORY: printf("OpenGL Error [%s]: GL_OUT_OF_MEMORY\n", indication); break;
        //case GL_TABLE_TOO_LARGE: printf("OpenGL Error [%s]: GL_TABLE_TOO_LARGE\n", indication); break;
    }
}

inline void __collision_init ()
{
    _engin_->collision_set = Set_Create();
    _engin_->collision_array = NULL;
    _engin_->collision_array_size = 0;
    _engin_->coll_array_update = 0;
    _engin_->collision_autoprocess = 1;
    _engin_->collision_proc = NULL;
}

inline void __collision_terminate ()
{
    if (_engin_->collision_array != NULL) { free(_engin_->collision_array); }
    Set_Destroy(_engin_->collision_set);
}

inline unsigned int __glow_texture()
{
    unsigned int image_array[1024] = {
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x01FFFFFF, 0x02FFFFFF, 0x03FFFFFF, 0x04FFFFFF, 0x04FFFFFF,
		0x04FFFFFF, 0x04FFFFFF, 0x04FFFFFF, 0x03FFFFFF, 0x02FFFFFF, 0x01FFFFFF, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x01FFFFFF, 0x03FFFFFF, 0x05FFFFFF, 0x06FFFFFF, 0x07FFFFFF, 0x08FFFFFF, 0x08FFFFFF,
		0x08FFFFFF, 0x08FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x06FFFFFF, 0x05FFFFFF, 0x03FFFFFF, 0x01FFFFFF,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x01FFFFFF,
		0x03FFFFFF, 0x05FFFFFF, 0x07FFFFFF, 0x08FFFFFF, 0x0AFFFFFF, 0x0BFFFFFF, 0x0CFFFFFF, 0x0CFFFFFF,
		0x0CFFFFFF, 0x0CFFFFFF, 0x0BFFFFFF, 0x0BFFFFFF, 0x0AFFFFFF, 0x08FFFFFF, 0x07FFFFFF, 0x05FFFFFF,
		0x03FFFFFF, 0x01FFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x02FFFFFF, 0x04FFFFFF,
		0x06FFFFFF, 0x09FFFFFF, 0x0AFFFFFF, 0x0CFFFFFF, 0x0EFFFFFF, 0x0FFFFFFF, 0x10FFFFFF, 0x10FFFFFF,
		0x10FFFFFF, 0x10FFFFFF, 0x10FFFFFF, 0x0FFFFFFF, 0x0EFFFFFF, 0x0CFFFFFF, 0x0AFFFFFF, 0x09FFFFFF,
		0x06FFFFFF, 0x04FFFFFF, 0x02FFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x02FFFFFF, 0x05FFFFFF, 0x07FFFFFF,
		0x0AFFFFFF, 0x0CFFFFFF, 0x0EFFFFFF, 0x10FFFFFF, 0x12FFFFFF, 0x13FFFFFF, 0x14FFFFFF, 0x14FFFFFF,
		0x14FFFFFF, 0x14FFFFFF, 0x14FFFFFF, 0x13FFFFFF, 0x12FFFFFF, 0x10FFFFFF, 0x0EFFFFFF, 0x0CFFFFFF,
		0x0AFFFFFF, 0x07FFFFFF, 0x05FFFFFF, 0x02FFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x02FFFFFF, 0x05FFFFFF, 0x08FFFFFF, 0x0AFFFFFF,
		0x0DFFFFFF, 0x0FFFFFFF, 0x12FFFFFF, 0x14FFFFFF, 0x15FFFFFF, 0x17FFFFFF, 0x18FFFFFF, 0x18FFFFFF,
		0x18FFFFFF, 0x18FFFFFF, 0x17FFFFFF, 0x17FFFFFF, 0x15FFFFFF, 0x14FFFFFF, 0x12FFFFFF, 0x10FFFFFF,
		0x0DFFFFFF, 0x0AFFFFFF, 0x08FFFFFF, 0x05FFFFFF, 0x01FFFFFF, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x01FFFFFF, 0x04FFFFFF, 0x07FFFFFF, 0x0AFFFFFF, 0x0EFFFFFF,
		0x10FFFFFF, 0x13FFFFFF, 0x15FFFFFF, 0x17FFFFFF, 0x19FFFFFF, 0x1BFFFFFF, 0x1CFFFFFF, 0x1CFFFFFF,
		0x1CFFFFFF, 0x1CFFFFFF, 0x1CFFFFFF, 0x1BFFFFFF, 0x19FFFFFF, 0x17FFFFFF, 0x15FFFFFF, 0x13FFFFFF,
		0x10FFFFFF, 0x0EFFFFFF, 0x0AFFFFFF, 0x07FFFFFF, 0x04FFFFFF, 0x01FFFFFF, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x03FFFFFF, 0x06FFFFFF, 0x0AFFFFFF, 0x0DFFFFFF, 0x10FFFFFF,
		0x13FFFFFF, 0x16FFFFFF, 0x18FFFFFF, 0x1BFFFFFF, 0x1DFFFFFF, 0x1EFFFFFF, 0x20FFFFFF, 0x20FFFFFF,
		0x20FFFFFF, 0x20FFFFFF, 0x20FFFFFF, 0x1EFFFFFF, 0x1DFFFFFF, 0x1BFFFFFF, 0x18FFFFFF, 0x16FFFFFF,
		0x13FFFFFF, 0x10FFFFFF, 0x0DFFFFFF, 0x0AFFFFFF, 0x06FFFFFF, 0x03FFFFFF, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x02FFFFFF, 0x05FFFFFF, 0x09FFFFFF, 0x0CFFFFFF, 0x0FFFFFFF, 0x13FFFFFF,
		0x16FFFFFF, 0x19FFFFFF, 0x1CFFFFFF, 0x1EFFFFFF, 0x20FFFFFF, 0x22FFFFFF, 0x23FFFFFF, 0x24FFFFFF,
		0x25FFFFFF, 0x24FFFFFF, 0x23FFFFFF, 0x22FFFFFF, 0x20FFFFFF, 0x1EFFFFFF, 0x1CFFFFFF, 0x19FFFFFF,
		0x16FFFFFF, 0x13FFFFFF, 0x0FFFFFFF, 0x0CFFFFFF, 0x09FFFFFF, 0x05FFFFFF, 0x01FFFFFF, 0x00000000,
		0x00000000, 0x00000000, 0x03FFFFFF, 0x07FFFFFF, 0x0BFFFFFF, 0x0EFFFFFF, 0x12FFFFFF, 0x15FFFFFF,
		0x18FFFFFF, 0x1CFFFFFF, 0x1EFFFFFF, 0x21FFFFFF, 0x24FFFFFF, 0x26FFFFFF, 0x28FFFFFF, 0x28FFFFFF,
		0x29FFFFFF, 0x28FFFFFF, 0x28FFFFFF, 0x26FFFFFF, 0x24FFFFFF, 0x21FFFFFF, 0x1FFFFFFF, 0x1CFFFFFF,
		0x18FFFFFF, 0x15FFFFFF, 0x12FFFFFF, 0x0EFFFFFF, 0x0AFFFFFF, 0x07FFFFFF, 0x03FFFFFF, 0x00000000,
		0x00000000, 0x01FFFFFF, 0x05FFFFFF, 0x08FFFFFF, 0x0CFFFFFF, 0x10FFFFFF, 0x14FFFFFF, 0x17FFFFFF,
		0x1BFFFFFF, 0x1EFFFFFF, 0x21FFFFFF, 0x24FFFFFF, 0x27FFFFFF, 0x29FFFFFF, 0x2BFFFFFF, 0x2CFFFFFF,
		0x2DFFFFFF, 0x2CFFFFFF, 0x2BFFFFFF, 0x29FFFFFF, 0x27FFFFFF, 0x24FFFFFF, 0x21FFFFFF, 0x1EFFFFFF,
		0x1BFFFFFF, 0x17FFFFFF, 0x13FFFFFF, 0x10FFFFFF, 0x0CFFFFFF, 0x08FFFFFF, 0x05FFFFFF, 0x00000000,
		0x00000000, 0x02FFFFFF, 0x06FFFFFF, 0x0AFFFFFF, 0x0EFFFFFF, 0x11FFFFFF, 0x15FFFFFF, 0x19FFFFFF,
		0x1DFFFFFF, 0x20FFFFFF, 0x24FFFFFF, 0x27FFFFFF, 0x2AFFFFFF, 0x2DFFFFFF, 0x2FFFFFFF, 0x30FFFFFF,
		0x31FFFFFF, 0x30FFFFFF, 0x2FFFFFFF, 0x2DFFFFFF, 0x2AFFFFFF, 0x27FFFFFF, 0x24FFFFFF, 0x20FFFFFF,
		0x1DFFFFFF, 0x19FFFFFF, 0x15FFFFFF, 0x12FFFFFF, 0x0EFFFFFF, 0x0AFFFFFF, 0x06FFFFFF, 0x01FFFFFF,
		0x00000000, 0x03FFFFFF, 0x07FFFFFF, 0x0BFFFFFF, 0x0FFFFFFF, 0x13FFFFFF, 0x16FFFFFF, 0x1BFFFFFF,
		0x1EFFFFFF, 0x22FFFFFF, 0x26FFFFFF, 0x29FFFFFF, 0x2DFFFFFF, 0x30FFFFFF, 0x32FFFFFF, 0x34FFFFFF,
		0x35FFFFFF, 0x34FFFFFF, 0x32FFFFFF, 0x30FFFFFF, 0x2DFFFFFF, 0x29FFFFFF, 0x26FFFFFF, 0x22FFFFFF,
		0x1EFFFFFF, 0x1AFFFFFF, 0x16FFFFFF, 0x13FFFFFF, 0x0FFFFFFF, 0x0BFFFFFF, 0x07FFFFFF, 0x02FFFFFF,
		0x00000000, 0x04FFFFFF, 0x08FFFFFF, 0x0CFFFFFF, 0x10FFFFFF, 0x14FFFFFF, 0x18FFFFFF, 0x1CFFFFFF,
		0x20FFFFFF, 0x23FFFFFF, 0x27FFFFFF, 0x2BFFFFFF, 0x2FFFFFFF, 0x32FFFFFF, 0x36FFFFFF, 0x38FFFFFF,
		0x39FFFFFF, 0x38FFFFFF, 0x36FFFFFF, 0x32FFFFFF, 0x2FFFFFFF, 0x2BFFFFFF, 0x27FFFFFF, 0x23FFFFFF,
		0x20FFFFFF, 0x1CFFFFFF, 0x17FFFFFF, 0x14FFFFFF, 0x10FFFFFF, 0x0BFFFFFF, 0x07FFFFFF, 0x03FFFFFF,
		0x00000000, 0x04FFFFFF, 0x08FFFFFF, 0x0CFFFFFF, 0x10FFFFFF, 0x14FFFFFF, 0x18FFFFFF, 0x1CFFFFFF,
		0x20FFFFFF, 0x24FFFFFF, 0x28FFFFFF, 0x2CFFFFFF, 0x30FFFFFF, 0x34FFFFFF, 0x38FFFFFF, 0xB3FFFFFF,
		0xB3FFFFFF, 0x3BFFFFFF, 0x38FFFFFF, 0x34FFFFFF, 0x30FFFFFF, 0x2CFFFFFF, 0x28FFFFFF, 0x24FFFFFF,
		0x20FFFFFF, 0x1CFFFFFF, 0x18FFFFFF, 0x14FFFFFF, 0x10FFFFFF, 0x0CFFFFFF, 0x08FFFFFF, 0x04FFFFFF,
		0x00000000, 0x04FFFFFF, 0x08FFFFFF, 0x0CFFFFFF, 0x10FFFFFF, 0x14FFFFFF, 0x18FFFFFF, 0x1CFFFFFF,
		0x21FFFFFF, 0x25FFFFFF, 0x29FFFFFF, 0x2DFFFFFF, 0x31FFFFFF, 0x35FFFFFF, 0x39FFFFFF, 0xB3FFFFFF,
		0xB3FFFFFF, 0x3DFFFFFF, 0x39FFFFFF, 0x35FFFFFF, 0x31FFFFFF, 0x2DFFFFFF, 0x29FFFFFF, 0x25FFFFFF,
		0x20FFFFFF, 0x1CFFFFFF, 0x18FFFFFF, 0x14FFFFFF, 0x10FFFFFF, 0x0CFFFFFF, 0x08FFFFFF, 0x04FFFFFF,
		0x00000000, 0x04FFFFFF, 0x08FFFFFF, 0x0CFFFFFF, 0x10FFFFFF, 0x14FFFFFF, 0x18FFFFFF, 0x1CFFFFFF,
		0x20FFFFFF, 0x24FFFFFF, 0x28FFFFFF, 0x2CFFFFFF, 0x30FFFFFF, 0x34FFFFFF, 0x38FFFFFF, 0x3BFFFFFF,
		0x3DFFFFFF, 0x3BFFFFFF, 0x38FFFFFF, 0x34FFFFFF, 0x30FFFFFF, 0x2CFFFFFF, 0x28FFFFFF, 0x24FFFFFF,
		0x20FFFFFF, 0x1CFFFFFF, 0x18FFFFFF, 0x14FFFFFF, 0x10FFFFFF, 0x0CFFFFFF, 0x08FFFFFF, 0x04FFFFFF,
		0x00000000, 0x04FFFFFF, 0x08FFFFFF, 0x0BFFFFFF, 0x10FFFFFF, 0x14FFFFFF, 0x17FFFFFF, 0x1CFFFFFF,
		0x1FFFFFFF, 0x23FFFFFF, 0x27FFFFFF, 0x2BFFFFFF, 0x2FFFFFFF, 0x32FFFFFF, 0x36FFFFFF, 0x38FFFFFF,
		0x39FFFFFF, 0x38FFFFFF, 0x36FFFFFF, 0x32FFFFFF, 0x2FFFFFFF, 0x2BFFFFFF, 0x27FFFFFF, 0x23FFFFFF,
		0x1FFFFFFF, 0x1CFFFFFF, 0x17FFFFFF, 0x14FFFFFF, 0x10FFFFFF, 0x0BFFFFFF, 0x08FFFFFF, 0x03FFFFFF,
		0x00000000, 0x03FFFFFF, 0x07FFFFFF, 0x0BFFFFFF, 0x0FFFFFFF, 0x13FFFFFF, 0x17FFFFFF, 0x1AFFFFFF,
		0x1EFFFFFF, 0x22FFFFFF, 0x26FFFFFF, 0x29FFFFFF, 0x2DFFFFFF, 0x30FFFFFF, 0x32FFFFFF, 0x34FFFFFF,
		0x35FFFFFF, 0x34FFFFFF, 0x32FFFFFF, 0x30FFFFFF, 0x2DFFFFFF, 0x29FFFFFF, 0x26FFFFFF, 0x22FFFFFF,
		0x1EFFFFFF, 0x1BFFFFFF, 0x16FFFFFF, 0x13FFFFFF, 0x0FFFFFFF, 0x0BFFFFFF, 0x07FFFFFF, 0x02FFFFFF,
		0x00000000, 0x02FFFFFF, 0x06FFFFFF, 0x0AFFFFFF, 0x0EFFFFFF, 0x12FFFFFF, 0x15FFFFFF, 0x19FFFFFF,
		0x1DFFFFFF, 0x20FFFFFF, 0x24FFFFFF, 0x27FFFFFF, 0x2AFFFFFF, 0x2DFFFFFF, 0x2FFFFFFF, 0x30FFFFFF,
		0x31FFFFFF, 0x30FFFFFF, 0x2FFFFFFF, 0x2DFFFFFF, 0x2AFFFFFF, 0x27FFFFFF, 0x24FFFFFF, 0x20FFFFFF,
		0x1DFFFFFF, 0x19FFFFFF, 0x15FFFFFF, 0x11FFFFFF, 0x0EFFFFFF, 0x0AFFFFFF, 0x06FFFFFF, 0x01FFFFFF,
		0x00000000, 0x01FFFFFF, 0x05FFFFFF, 0x08FFFFFF, 0x0CFFFFFF, 0x10FFFFFF, 0x14FFFFFF, 0x17FFFFFF,
		0x1BFFFFFF, 0x1EFFFFFF, 0x21FFFFFF, 0x24FFFFFF, 0x27FFFFFF, 0x29FFFFFF, 0x2BFFFFFF, 0x2CFFFFFF,
		0x2DFFFFFF, 0x2CFFFFFF, 0x2BFFFFFF, 0x29FFFFFF, 0x27FFFFFF, 0x24FFFFFF, 0x21FFFFFF, 0x1EFFFFFF,
		0x1BFFFFFF, 0x17FFFFFF, 0x14FFFFFF, 0x10FFFFFF, 0x0CFFFFFF, 0x08FFFFFF, 0x05FFFFFF, 0x00000000,
		0x00000000, 0x00000000, 0x03FFFFFF, 0x07FFFFFF, 0x0AFFFFFF, 0x0EFFFFFF, 0x12FFFFFF, 0x15FFFFFF,
		0x18FFFFFF, 0x1CFFFFFF, 0x1FFFFFFF, 0x21FFFFFF, 0x24FFFFFF, 0x26FFFFFF, 0x27FFFFFF, 0x28FFFFFF,
		0x29FFFFFF, 0x28FFFFFF, 0x28FFFFFF, 0x26FFFFFF, 0x24FFFFFF, 0x21FFFFFF, 0x1FFFFFFF, 0x1CFFFFFF,
		0x18FFFFFF, 0x15FFFFFF, 0x12FFFFFF, 0x0EFFFFFF, 0x0BFFFFFF, 0x07FFFFFF, 0x02FFFFFF, 0x00000000,
		0x00000000, 0x00000000, 0x01FFFFFF, 0x05FFFFFF, 0x08FFFFFF, 0x0CFFFFFF, 0x0FFFFFFF, 0x13FFFFFF,
		0x16FFFFFF, 0x19FFFFFF, 0x1CFFFFFF, 0x1EFFFFFF, 0x20FFFFFF, 0x22FFFFFF, 0x23FFFFFF, 0x24FFFFFF,
		0x25FFFFFF, 0x24FFFFFF, 0x23FFFFFF, 0x22FFFFFF, 0x20FFFFFF, 0x1EFFFFFF, 0x1CFFFFFF, 0x19FFFFFF,
		0x16FFFFFF, 0x13FFFFFF, 0x10FFFFFF, 0x0CFFFFFF, 0x09FFFFFF, 0x05FFFFFF, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x03FFFFFF, 0x07FFFFFF, 0x0AFFFFFF, 0x0DFFFFFF, 0x10FFFFFF,
		0x13FFFFFF, 0x16FFFFFF, 0x18FFFFFF, 0x1BFFFFFF, 0x1DFFFFFF, 0x1EFFFFFF, 0x1FFFFFFF, 0x20FFFFFF,
		0x21FFFFFF, 0x20FFFFFF, 0x20FFFFFF, 0x1EFFFFFF, 0x1DFFFFFF, 0x1BFFFFFF, 0x18FFFFFF, 0x16FFFFFF,
		0x13FFFFFF, 0x10FFFFFF, 0x0DFFFFFF, 0x0AFFFFFF, 0x07FFFFFF, 0x02FFFFFF, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x01FFFFFF, 0x04FFFFFF, 0x07FFFFFF, 0x0AFFFFFF, 0x0DFFFFFF,
		0x10FFFFFF, 0x13FFFFFF, 0x15FFFFFF, 0x17FFFFFF, 0x19FFFFFF, 0x1BFFFFFF, 0x1CFFFFFF, 0x1CFFFFFF,
		0x1CFFFFFF, 0x1CFFFFFF, 0x1CFFFFFF, 0x1BFFFFFF, 0x19FFFFFF, 0x17FFFFFF, 0x15FFFFFF, 0x13FFFFFF,
		0x10FFFFFF, 0x0DFFFFFF, 0x0AFFFFFF, 0x07FFFFFF, 0x03FFFFFF, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x02FFFFFF, 0x05FFFFFF, 0x07FFFFFF, 0x0AFFFFFF,
		0x0DFFFFFF, 0x0FFFFFFF, 0x12FFFFFF, 0x14FFFFFF, 0x15FFFFFF, 0x16FFFFFF, 0x17FFFFFF, 0x18FFFFFF,
		0x18FFFFFF, 0x18FFFFFF, 0x17FFFFFF, 0x17FFFFFF, 0x15FFFFFF, 0x14FFFFFF, 0x12FFFFFF, 0x10FFFFFF,
		0x0DFFFFFF, 0x0AFFFFFF, 0x08FFFFFF, 0x04FFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x02FFFFFF, 0x05FFFFFF, 0x07FFFFFF,
		0x0AFFFFFF, 0x0CFFFFFF, 0x0EFFFFFF, 0x10FFFFFF, 0x12FFFFFF, 0x13FFFFFF, 0x14FFFFFF, 0x14FFFFFF,
		0x14FFFFFF, 0x14FFFFFF, 0x14FFFFFF, 0x13FFFFFF, 0x12FFFFFF, 0x10FFFFFF, 0x0EFFFFFF, 0x0CFFFFFF,
		0x0AFFFFFF, 0x07FFFFFF, 0x04FFFFFF, 0x01FFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x01FFFFFF, 0x04FFFFFF,
		0x06FFFFFF, 0x09FFFFFF, 0x0AFFFFFF, 0x0CFFFFFF, 0x0EFFFFFF, 0x0FFFFFFF, 0x10FFFFFF, 0x10FFFFFF,
		0x10FFFFFF, 0x10FFFFFF, 0x10FFFFFF, 0x0FFFFFFF, 0x0EFFFFFF, 0x0CFFFFFF, 0x0AFFFFFF, 0x09FFFFFF,
		0x06FFFFFF, 0x03FFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x01FFFFFF,
		0x03FFFFFF, 0x05FFFFFF, 0x07FFFFFF, 0x08FFFFFF, 0x0AFFFFFF, 0x0BFFFFFF, 0x0CFFFFFF, 0x0CFFFFFF,
		0x0CFFFFFF, 0x0CFFFFFF, 0x0CFFFFFF, 0x0BFFFFFF, 0x0AFFFFFF, 0x08FFFFFF, 0x07FFFFFF, 0x05FFFFFF,
		0x02FFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x01FFFFFF, 0x03FFFFFF, 0x05FFFFFF, 0x06FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x08FFFFFF,
		0x08FFFFFF, 0x08FFFFFF, 0x08FFFFFF, 0x07FFFFFF, 0x06FFFFFF, 0x05FFFFFF, 0x02FFFFFF, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x01FFFFFF, 0x02FFFFFF, 0x03FFFFFF, 0x04FFFFFF,
		0x04FFFFFF, 0x04FFFFFF, 0x03FFFFFF, 0x02FFFFFF, 0x01FFFFFF, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

	unsigned int gGlowTexture = 0;

	glGenTextures(1, &gGlowTexture);
	glBindTexture(GL_TEXTURE_2D, gGlowTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32, 32, 0, GL_BGRA, GL_UNSIGNED_BYTE, image_array);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	return gGlowTexture;
}

inline void __gl_glow_line(int x1, int y1, int x2, int y2, int w)
{
    float nx, ny;
	nx = -(y2 - y1);
	ny =  (x2 - x1);

	float leng;
    leng = sqrt((nx * nx) + (ny * ny));
    nx = nx / leng;
    ny = ny / leng;

	nx *= w / 2.0;
	ny *= w / 2.0;

	float lx1, ly1, lx2, ly2, lx3, ly3, lx4, ly4;
	lx1 = x2 + nx;
    ly1 = y2 + ny;
    lx2 = x2 - nx;
    ly2 = y2 - ny;
    lx3 = x1 - nx;
    ly3 = y1 - ny;
    lx4 = x1 + nx;
    ly4 = y1 + ny;

	// MAIN
	glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.5, 0.0); glVertex2f(lx1, ly1);
		glTexCoord2f(0.5, 1.0); glVertex2f(lx2, ly2);
		glTexCoord2f(0.5, 1.0); glVertex2f(lx3, ly3);
		glTexCoord2f(0.5, 0.0); glVertex2f(lx4, ly4);
	glEnd();

	// RIGHT
	float lx5, ly5, lx6, ly6, vx, vy;
	vx = ( x2 - x1 );
	vy = ( y2 - y1 );
	leng = sqrt( vx * vx + vy * vy );
	vx = vx / leng;
	vy = vy / leng;
	vx *= w / 2.0;
	vy *= w / 2.0;

	lx5 = lx1 + vx;
	ly5 = ly1 + vy;
	lx6 = lx2 + vx;
	ly6 = ly2 + vy;

	glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.5, 0.0); glVertex2f(lx1, ly1);
		glTexCoord2f(1.0, 0.0); glVertex2f(lx5, ly5);
		glTexCoord2f(1.0, 1.0); glVertex2f(lx6, ly6);
		glTexCoord2f(0.5, 1.0); glVertex2f(lx2, ly2);
	glEnd();

	// LEFT
	lx5 = lx4 - vx;
	ly5 = ly4 - vy;
	lx6 = lx3 - vx;
	ly6 = ly3 - vy;

	glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.5, 0.0); glVertex2f(lx4, ly4);
		glTexCoord2f(0.5, 1.0); glVertex2f(lx3, ly3);
		glTexCoord2f(1.0, 1.0); glVertex2f(lx6, ly6);
		glTexCoord2f(1.0, 0.0); glVertex2f(lx5, ly5);
	glEnd();
}

/**
    @}
*/
