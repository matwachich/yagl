/**
    \addtogroup 030_render
    @{
*/

#include "all.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- **/
/* Public functions **/

/*
Function: Render_SetClearColor

Parameters:

Return:

*/
void    YAGL_API    Render_SetClearColor (const unsigned char red, const unsigned char green, const unsigned char blue)
{
    glClearColor((double)red / 255.0, (double)green / 255.0, (double)blue / 255.0, 1.0);
}

/*
Function: Render_SetClearColorEx

Parameters:

Return:

*/
void    YAGL_API    Render_SetClearColorEx (YAGL_Color color)
{
    glClearColor((double)YAGL_RGBA_R(color) / 255.0, (double)YAGL_RGBA_G(color) / 255.0, (double)YAGL_RGBA_B(color) / 255.0, 1.0);
}

/*
Function: Render_InitTimers

Parameters:

Return:

*/
void    YAGL_API    Render_InitTimers ()
{
    _engin_->old_time = glfwGetTime();
}

/*
Function: Render_SetTimersMult

Parameters:

Return:

*/
void    YAGL_API    Render_SetTimersMult (float tm)
{
    _engin_->timer_mult = tm;
}

/*
Function: Render_GetTimersMult

Parameters:

Return:

*/
float   YAGL_API    Render_GetTimersMult ()
{
    return _engin_->timer_mult;
}

/*
Function: Render_Begin

Parameters:

Return:

*/
void    YAGL_API    Render_Begin ()
{
    double now = glfwGetTime();
    _engin_->delta = (now - _engin_->old_time) * _engin_->timer_mult;
    _engin_->old_time = now;

    glClear(GL_COLOR_BUFFER_BIT);
}


/*
Function: Render_End

Parameters:

Return:

*/
void    YAGL_API    Render_End ()
{
    if (_engin_->collision_autoprocess != 0) { Collision_Process(); }
    glfwSwapBuffers();
}


/*
Function: Render_SetCallbacks

Parameters:

Return:

*/
void    YAGL_API    Render_SetCallbacks (YAGLRenderProc render_proc, YAGLFrameProc frame_proc)
{
    _engin_->render_proc = render_proc;
	_engin_->frame_proc = frame_proc;
}


/*
Function: Render_StartLoop

Parameters:

Return:

*/
void    YAGL_API    Render_StartLoop (YAGLRenderProc render_proc, YAGLFrameProc frame_proc, int exit_on_win_close)
{
    __DEBUG__("Entering main loop ...", 0);

    _engin_->render_proc = render_proc;
    _engin_->frame_proc = frame_proc;

    _engin_->old_time = glfwGetTime();
    double now;
    int runing = 1;

    do {
        now = glfwGetTime();

        _engin_->delta = now - _engin_->old_time;
        _engin_->old_time = now;

        glClear(GL_COLOR_BUFFER_BIT);

        if (_engin_->render_proc != NULL) {
            if (_engin_->render_proc(_engin_->delta) == 0) { runing = 0; }
        }

        if (exit_on_win_close && !glfwGetWindowParam(GLFW_OPENED)) { runing = 0; }
        if (_engin_->collision_autoprocess != 0) { Collision_Process(); }
		glFlush();

		if (_engin_->frame_proc != NULL) {
            if (_engin_->frame_proc(_engin_->delta) == 0) { runing = 0; }
        }

        glfwSwapBuffers();
    } while (runing != 0);

    __DEBUG__("Main loop end", 0);
}


/*
Function: Render_GetFps

Parameters:

Return:

*/
double  YAGL_API    Render_GetFps (const double delay)
{
    double ret = 0.0;
    if (_engin_->delay == 0.0) {
        _engin_->delay = glfwGetTime();
    } else {
        if (glfwGetTime() - _engin_->delay >= delay) {
            ret = 1 / _engin_->delta;
            _engin_->delay = glfwGetTime();
        }
    }
    return ret;
}


/*
Function: Render_GetDelta

Parameters:

Return:

*/
double  YAGL_API    Render_GetDelta ()
{
    return _engin_->delta;
}


/*
Function: Render_SetSwapInterval

Parameters:

Return:

*/
void    YAGL_API    Render_SetSwapInterval (const int interval)
{
    glfwSwapInterval(interval);
}

/**
    @}
*/
