/**
    \addtogroup 020_window
    @{
*/

#include "all.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- **/
/* Public functions **/

/** \brief Create a render context, window or fullscreen
 *
 * \param width[in]
 * \param height[in]
 * \param red_bits[in]
 * \param green_bits[in]
 * \param blue_bits[in]
 * \param fullscreen[in]
 * \param title[in]
 * \param resizable[in]
 * \param multisample[in]
 *
 * \return 1 on succes, 0 otherwise
 */
int     YAGL_API    Window_Create (const int width, const int height, const int red_bits, const int green_bits, const int blue_bits, const int fullscreen, const char title[], int resizable, const int multisample)
{
    if (_engin_ == NULL) { return 0; }
    if (_engin_->window_opened != 0) { return 1; }

    if (resizable == 0) { glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, 1); }
    int open_flag = GLFW_WINDOW;
    if (fullscreen != 0) { open_flag = GLFW_FULLSCREEN; }

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, multisample);

    if (glfwOpenWindow(width, height, red_bits, green_bits, blue_bits, 0, 0, 0, open_flag) != 1) {
        __DEBUG__("Window creation failed. (glfwOpenWindow failed)", 2);
    }

    glfwEnable(GLFW_MOUSE_CURSOR);
    glfwSetWindowTitle(title);

    // internal window size procedure
    glfwSetWindowSizeCallback((GLFWwindowsizefun)__Internal_WinSizeProc);

    _engin_->window_opened = 1;
    _engin_->fullscreen = fullscreen;

    _engin_->window_size.x = width;
    _engin_->window_size.y = height;
    _engin_->view.x = 0;
    _engin_->view.y = 0;
    _engin_->view.w = width;
    _engin_->view.h = height;
    _engin_->original_view_size.x = width;
    _engin_->original_view_size.y = height;

    // OpenGL init
    __opengl_init(width, height);

    // ---
    int oglM, oglm, oglrev;
    int glfwM, glfwm, glfwrev;
    glfwGetVersion(&glfwM, &glfwm, &glfwrev);
    glfwGetGLVersion(&oglM, &oglm, &oglrev);

    char tmp[256];

    sprintf(tmp, "Creating window: %ix%i - [R:%i G:%i B:%i]", width, height, red_bits, green_bits, blue_bits);
    __DEBUG__(tmp, 0);

    sprintf(tmp, "%s - %s", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
    __DEBUG__(tmp, 0);

    sprintf(tmp, "OpenGL version: %i.%i.%i", oglM, oglm, oglrev);
    __DEBUG__(tmp, 0);

    const GLubyte* shader_ver = glGetString(GL_SHADING_LANGUAGE_VERSION);
    if (shader_ver != 0) {
        sprintf(tmp, "Shaders version: %s", shader_ver);
        __DEBUG__(tmp, 0);
    } else {
        __DEBUG__("Shaders version: Unknown", 1);
    }

    sprintf(tmp, "GLFW version: %i.%i.%i", glfwM, glfwm, glfwrev);
    __DEBUG__(tmp, 0);

    return 1;
}

/** \brief Open fullscreen render window according to a video mode
 *
 * \param video_mode_id[in] Video mode ID
 * \param title[in] Window title
 * \param multisample[in] Multisample
 *
 * \return 1 on succes, 0 otherwise
 */
int     YAGL_API    Window_CreateEx(int video_mode_id, const char title[], int multisample)
{
    int w = 0, h = 0, r = 0, g = 0, b = 0;
    System_GetVideoMode(video_mode_id, &w, &h, &r, &g, &b);
    if (w == 0 || h == 0 || r == 0 || g == 0 || b == 0) {
        __DEBUG__("Window creation failed. (Invalid video mode id)", 2);
    }

    return Window_Create(w, h, r, g, b, 1, title, 1, multisample);
}

/** \brief Close window
 */
void    YAGL_API    Window_Close ()
{
    glfwCloseWindow();
    _engin_->window_opened = 0;
}

/** \brief Check if a rendering window is opened
 *
 * \return 1 if it's opened, 0 otherwise
 */
int     YAGL_API    Window_IsOpened ()
{
    if (glfwGetWindowParam(GLFW_OPENED) == 0) {
        _engin_->window_opened = 0;
        return 0;
    } else {
        return 1;
    }
}

/** \brief Center the rendering window on the desktop
 *
 * No effect on fullscreen window
 */
void    YAGL_API    Window_Center ()
{
    if (_engin_->window_opened == 0 || _engin_->fullscreen != 0) { return; }

    int w, h;
    System_GetDesktopMode(&w, &h, NULL, NULL, NULL);
    if (w == 0 || h == 0) { return; }

    glfwSetWindowPos((w / 2) - (_engin_->window_size.x / 2), (h / 2) - (_engin_->window_size.y / 2));
}

/** \brief Set the position of the upper-left corner of the rendering window
 *
 * (0,0) is the upper-left corner of the desktop
 *
 * \param x[in] X-position
 * \param y[in] Y-position
 */
void    YAGL_API    Window_SetPos (const int x, const int y)
{
    glfwSetWindowPos(x, y);
}

/** \brief Set window size, or fullscreen display resolution
 *
 * \param w[in] Width
 * \param h[in] Height
 */
void    YAGL_API    Window_SetSize (const int w, const int h)
{
    glfwSetWindowSize(w, h);
}

/** \brief Get window size, or fullscreen display resolution
 *
 * \param w[out] Width
 * \param h[out] Height
 */
void    YAGL_API    Window_GetSize (int* w, int* h)
{
    glfwGetWindowSize(w, h);
}

/** \brief Set window title
 *
 * \param title[in] NULL-terminated string
 */
void    YAGL_API    Window_SetTitle (const char title[])
{
    glfwSetWindowTitle(title);
}

/** \brief Iconify/Restor a window
 *
 * If fullscreen, then switch between desktop and window video mode
 *
 * \param flag[in] 1 to restor, 0 to iconify
 */
void    YAGL_API    Window_SetVisible (const int flag)
{
    if (flag != 0) {
        glfwRestoreWindow();
    } else {
        glfwIconifyWindow();
    }
}

/** \brief Check if a window is iconified
 *
 * \return 1 if visible, 0 if iconified
 */
int     YAGL_API    Window_IsVisible ()
{
    return 1 - glfwGetWindowParam(GLFW_ICONIFIED);
}

/** \brief Check if a window has the focus
 *
 * \return 1 if it has focus, 0 otherwise
 */
int     YAGL_API    Window_IsActive ()
{
    return glfwGetWindowParam(GLFW_ACTIVE);
}

/** \brief Check if a window is hardware accelerated
 *
 * \return 1 if it is hardware accelerated, 0 otherwise
 */
int     YAGL_API    Window_IsAccelerated ()
{
    return glfwGetWindowParam(GLFW_ACCELERATED);
}

/** \brief Take a screenshot of the rendering window (or a part of it) to a file
 *
 * \param filepath[in] NULL-terminated string representing a filepath
 * \param type[in] Capture file format (see #eCAPTURE_TYPE)
 * \param x[in] Upper-left corner x-position of the rectangle to capture
 * \param y[in] Upper-left corner y-position of the rectangle to capture
 * \param w[in] Upper-left corner width of the rectangle to capture
 * \param h[in] Upper-left corner height of the rectangle to capture
 */
void    YAGL_API    Window_Capture (const char filepath[], eCAPTURE_TYPE type, int x, int y, int w, int h)
{
    if (x < 0) { x = 0; }
    if (y < 0) { y = 0; }
    if (w <= 0) { w = _engin_->window_size.x; }
    if (h <= 0) { h = _engin_->window_size.y; }
    SOIL_save_screenshot(filepath, type, x, y, w, h);
}

/** \brief Display/hide the mouse cursor
 *
 * \param status[in] 1 to show, 0 to hide
 */
void    YAGL_API    Window_SetCursor (const int status)
{
    if (status != 0) {
        glfwEnable(GLFW_MOUSE_CURSOR);
    } else {
        glfwDisable(GLFW_MOUSE_CURSOR);
    }
}

/** \brief Set a YAGLWinCloseProc()
 *
 * \param proc[in] Pointer to a YAGLWinCloseProc or NULL
 */
void    YAGL_API    Window_SetCloseCallback (YAGLWinCloseProc proc)
{
    glfwSetWindowCloseCallback((GLFWwindowclosefun)proc);
}

/** \brief Set a YAGLWinSizeProc()
 *
 * \param proc[in] Pointer to a YAGLWinSizeProc or NULL
 */
void    YAGL_API    Window_SetSizeCallback (YAGLWinSizeProc proc)
{
    _engin_->win_size_proc = proc;
}

/** \brief Set a YAGLWinRefreshProc()
 *
 * \param proc[in] Pointer to a YAGLWinRefreshProc or NULL
 */
void    YAGL_API    Window_SetRefreshCallback (YAGLWinRefreshProc proc)
{
    glfwSetWindowRefreshCallback((GLFWwindowrefreshfun)proc);
}

/**
    @}
*/
