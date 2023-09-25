/**
    \addtogroup 060_misc
    @{
*/

#include "all.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- **/
/* Public functions **/

/** \brief Sleep
 *
 * \param time[in] Seconds
 */
void    YAGL_API    Misc_Sleep (const double time)
{
    glfwSleep(time);
}

/** \brief Set if the Misc_TimerDiff() function should follow the global timers multiplier (Render_SetTimersMult())
 *
 * \param follow[in] 0 to not follow, 1 to follow (default)
 */
void        YAGL_API    Misc_TimersSetFollowMult (int follow)
{
    _engin_->timer_follow_mult = follow;
}

/** \brief Get current status of global timers multiplier following by Misc_TimerDiff()
 *
 * \return 1 if following (default), 0 otherwise
 */
int         YAGL_API    Misc_TimersGetFollowMult ()
{
    return _engin_->timer_follow_mult;
}

/** \brief Return a timestamp to use with Misc_TimerDiff()
 *
 * \return Timestamp
 */
double  YAGL_API    Misc_TimerInit ()
{
    return glfwGetTime();
}

/** \brief Return the elapsed time since the provided timestamp
 *
 * \param timestamp[in] Timestamp (see Misc_TimerInit())
 *
 * \return Seconds elapsed since the timestamp
 */
double  YAGL_API    Misc_TimerDiff (const double timestamp)
{
    double t = glfwGetTime() - timestamp;
    if (_engin_->timer_follow_mult != 0) {
        t *= _engin_->timer_mult;
    }
    return t;
}

/** \brief Return a random integer
 *
 * \param min[in] Lower bound (inclusive)
 * \param min[in] Upper bound (not inclusive)
 *
 * \return Random integer in the range [min,max[
 */
int     YAGL_API    Misc_RandomI (const int min, const int max)
{
    return __rnd_int(min, max);
}

/** \brief Return a random floating point number
 *
 * \param min[in] Lower bound (inclusive)
 * \param min[in] Upper bound (not inclusive)
 *
 * \return Random integer in the range [min,max[
 */
double  YAGL_API    Misc_RandomF (const double min, const double max)
{
    return __rnd_double(min, max);
}

/** \brief Wrapper to #YAGL_RGBA
 *
 * \param red[in] Red
 * \param green[in] Green
 * \param blue[in] Blue
 * \param alpha[in] Alpha
 *
 * \return #YAGL_Color
 */
YAGL_Color YAGL_API Misc_Color (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
    return YAGL_RGBA(red, green, blue, alpha);
}

/** \brief Wrapper to #YAGL_RGBA_R, #YAGL_RGBA_G, #YAGL_RGBA_B and #YAGL_RGBA_A
 *
 * \param red[out]
 * \param green[out]
 * \param blue[out]
 * \param alpha[out]
 */
void    YAGL_API    Misc_ColorComponents (YAGL_Color color, unsigned char* red, unsigned char* green, unsigned char* blue, unsigned char* alpha)
{
    if (red != NULL) { *red = YAGL_RGBA_R(color); }
    if (green != NULL) { *green = YAGL_RGBA_G(color); }
    if (blue != NULL) { *blue = YAGL_RGBA_B(color); }
    if (alpha != NULL) { *alpha = YAGL_RGBA_A(color); }
}

/**
    @}
*/
