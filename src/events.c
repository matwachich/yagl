/**
    \addtogroup 050_events
    @{
*/

#include "all.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- **/
/* Public functions **/

/** \brief Enable/Disable key repeat
 *
 * \param status[in] 0 to disable, 1 to enable
 */
void    YAGL_API    Events_KeySetRepeat (const int status)
{
    if (status == 0) {
        glfwDisable(GLFW_KEY_REPEAT);
        _engin_->key_repeat = 0;
    } else {
        glfwEnable(GLFW_KEY_REPEAT);
        _engin_->key_repeat = 1;
    }
}

/** \brief Get key repeat status
 *
 * \return 1 if enabled, 0 if disabled
 */
int     YAGL_API    Events_KeyGetRepeat ()
{
    return _engin_->key_repeat;
}


int     YAGL_API    Events_KeyGet (const int key)
{
    return glfwGetKey(key);
}

/*
Function: Events_MouseGetPos

Parameters:

Return:

*/
void    YAGL_API    Events_MouseGetPos (int* x, int* y)
{
    glfwGetMousePos(x, y);
    __correct_get_mouse_pos(x, y);
}

/*
Function: Events_MouseGetButton

Parameters:

Return:

*/
int     YAGL_API    Events_MouseGetButton (const int button)
{
    return glfwGetMouseButton(button);
}

/*
Function: Events_MouseGetWheel

Parameters:

Return:

*/
int     YAGL_API    Events_MouseGetWheel ()
{
    return glfwGetMouseWheel();
}

/*
Function: Events_MouseSetPos

Parameters:

Return:

*/
void    YAGL_API    Events_MouseSetPos (int x, int y)
{
    __correct_set_mouse_pos(&x, &y);
    glfwSetMousePos(x, y);
}

/*
Function: Events_MouseSetWheel

Parameters:

Return:

*/
void    YAGL_API    Events_MouseSetWheel (const int pos)
{
    glfwSetMouseWheel(pos);
}

/*
Function: Events_MouseSetPosMode

Parameters:

Return:

*/
void    YAGL_API    Events_MouseSetPosMode (eMOUSE_POS_MODE mode)
{
    _engin_->mouse_pos_mode = mode;
}

/*
Function: Events_MouseGetPosMode

Parameters:

Return:

*/
int     YAGL_API    Events_MouseGetPosMode ()
{
    return _engin_->mouse_pos_mode;
}

/*
Function: Events_SetMousePosCallback

Parameters:

Return:

*/
void    YAGL_API    Events_SetMousePosCallback (YAGLMousePosProc proc)
{
    _engin_->mouse_pos_proc = proc;
    if (proc != NULL) {
        glfwSetMousePosCallback((GLFWmouseposfun)__Internal_MousePosProc);
    } else {
        glfwSetMousePosCallback(NULL);
    }
}

/*
Function: Events_SetMouseButtonCallback

Parameters:

Return:

*/
void    YAGL_API    Events_SetMouseButtonCallback (YAGLMouseButtonProc proc)
{
    glfwSetMouseButtonCallback((GLFWmousebuttonfun)proc);
}

/*
Function: Events_SetMouseWheelCallback

Parameters:

Return:

*/
void    YAGL_API    Events_SetMouseWheelCallback (YAGLMouseWheelProc proc)
{
    glfwSetMouseWheelCallback((GLFWmousewheelfun)proc);
}

/*
Function: Events_SetKeyCallback

Parameters:

Return:

*/
void    YAGL_API    Events_SetKeyCallback (YAGLKeyProc proc)
{
    glfwSetKeyCallback((GLFWkeyfun)proc);
}

/*
Function: Events_SetCharCallback

Parameters:

Return:

*/
void    YAGL_API    Events_SetCharCallback (YAGLCharProc proc)
{
    glfwSetCharCallback((GLFWcharfun)proc);
}

/**
    @}
*/
