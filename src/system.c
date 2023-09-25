/**
    \addtogroup 010_system
    @{
*/

#include <time.h> // for srand()

#include "all.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- **/
/* Public functions **/

/**
 * \brief Initiate the engine.
 *
 * Must be called before any other YAGL function.
 *
 * \param debug_mode[in] See #eDEBUG
 *
 * \return 1 on succes, 0 otherwise
 */
int     YAGL_API    System_Init (eDEBUG debug_mode)
{
    if (_engin_ != NULL) { return 0; }

    _engin_ = malloc(sizeof(Engin));
    if (_engin_ == NULL) {
        __DEBUG__("YAGL init failed! (Out of memory)", 2);
    }

    __t_engin_init(_engin_);
    srand(time(NULL));

    // Debug mode
    _engin_->debug_mode = debug_mode;
    if (_engin_->debug_mode == DEBUG_ON_FILE) {
        _engin_->debug_file = fopen("YAGL_log.txt", "w");
    } else {
        _engin_->debug_file = NULL;
    }

    // GLFW init
	if (glfwInit() == GL_FALSE) {
	    if (_engin_->debug_file != NULL) { fclose(_engin_->debug_file); }
        free(_engin_);
        __DEBUG__("YAGL init failed! (Could not initiate GLFW)", 2);
    }

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 0);

    // video modes
    GLFWvidmode array[100];
    int count = glfwGetVideoModes(array, 100);
    if (count == 0) {
        if (_engin_->debug_file != NULL) { fclose(_engin_->debug_file); }
        free(_engin_);
        __DEBUG__("YAGL init failed! (Could not get supported video modes)", 2);
    }

    _engin_->video_modes_count = count;
    _engin_->video_modes = calloc(count, sizeof(GLFWvidmode));
    if (_engin_->video_modes == NULL) {
        if (_engin_->debug_file != NULL) { fclose(_engin_->debug_file); }
        free(_engin_);
        __DEBUG__("YAGL init failed! (Out of memory)", 2);
    }

    int i = 0;
    for (i = 0; i < count; i++) {
        _engin_->video_modes[i].Width = array[i].Width;
        _engin_->video_modes[i].Height = array[i].Height;
        _engin_->video_modes[i].RedBits = array[i].RedBits;
        _engin_->video_modes[i].GreenBits = array[i].GreenBits;
        _engin_->video_modes[i].BlueBits = array[i].BlueBits;
    }

    // Init collisions
    __collision_init();

    // Init Garbage Collector
    if (mem_init(MEM_PTR_TYPES_COUNT) != 1) {
        if (_engin_->debug_file != NULL) { fclose(_engin_->debug_file); }
        free(_engin_->video_modes);
        free(_engin_);
        __DEBUG__("YAGL init failed! (Out of memory)", 2);
    }

    // ---
    char tmp[128];
    sprintf(tmp, "YAGL v%s initiated. %i videos modes supported.", YAGL_VERSION_STR, count);
    __DEBUG__(tmp, 0);

    return 1;
}

/** \brief Output data to the debug output
 *
 * \param data[in] NULL-terminated string to output
 * \param err_lvl[in] 0 No error, 1 Error, 2 Fatal error (program will exit)
 */
void    YAGL_API    System_DebugOut (const char* data, int err_lvl)
{
    if (_engin_ == NULL) { return; }

    __DEBUG__(data, err_lvl);
}

/** \brief Set a function to be called when debug info is outputed
 *
 * \param debug_proc[in] See YAGLDebugProc
 */
void    YAGL_API    System_SetDebugCallback (YAGLDebugProc debug_proc)
{
    if (_engin_ == NULL) { return; }

    _engin_->debug_proc = debug_proc;
}

/** \brief Free all ressources and terminate the engine
 */
void    YAGL_API    System_Terminate ()
{
    if (_engin_ == NULL) { return; }

    // Garbage collector
    __DEBUG__("Releasing ressources...", 0);
    mem_clean();
    __DEBUG__("Done!", 0);

    // collisions terminate
    __collision_terminate();

    // free ressources
    glDeleteLists(_engin_->display_list_1x1, 1);
    glDeleteLists(_engin_->display_list_circle, 1);
    glDeleteLists(_engin_->display_list_disc, 1);

    glDeleteTextures(1, &_engin_->glow_texture);

    glfwTerminate();

    __DEBUG__("YAGL terminated", 0);

    if (_engin_->debug_file != NULL) { fclose(_engin_->debug_file); }
    if (_engin_->shaders != NULL) { free(_engin_->shaders); }

    free(_engin_->video_modes);
    free(_engin_);

    _engin_ = NULL;
}

/** \brief Return the number of supported video modes
 *
 * \return Number of supported video modes
 */
int     YAGL_API    System_GetVideoModesCount ()
{
    return _engin_->video_modes_count;
}

/** \brief Get a supported video mode
 *
 * \param mode[in] Video mode to get ([1, System_GetVideoModesCount()])
 * \param width[out]
 * \param height[out]
 * \param red_bits[out]
 * \param green_bits[out]
 * \param blue_bits[out]
 */
void    YAGL_API    System_GetVideoMode (int mode, int* width, int* height, int* red_bits, int* green_bits, int* blue_bits)
{
    if (mode < 1 || mode > _engin_->video_modes_count) { return; }

    mode -= 1;
	if (width != NULL) { *width = _engin_->video_modes[mode].Width; }
	if (height != NULL) { *height = _engin_->video_modes[mode].Height; }
	if (red_bits != NULL) { *red_bits = _engin_->video_modes[mode].RedBits; }
	if (green_bits != NULL) { *green_bits = _engin_->video_modes[mode].GreenBits; }
	if (blue_bits != NULL) { *blue_bits = _engin_->video_modes[mode].BlueBits; }
}

/** \brief Get current desktop video mode
 *
 * \param width[out]
 * \param height[out]
 * \param red_bits[out]
 * \param green_bits[out]
 * \param blue_bits[out]
 */
void    YAGL_API    System_GetDesktopMode (int* width, int* height, int* red_bits, int* green_bits, int* blue_bits)
{
    GLFWvidmode mode;
    glfwGetDesktopMode(&mode);
    if (width != NULL) { *width = mode.Width; }
	if (height != NULL) { *height = mode.Height; }
	if (red_bits != NULL) { *red_bits = mode.RedBits; }
	if (green_bits != NULL) { *green_bits = mode.GreenBits; }
	if (blue_bits != NULL) { *blue_bits = mode.BlueBits; }
}

/** \brief Get some stats about the runing engine
 *
 * \param num_textures[out]
 * \param num_texture_maps[out]
 * \param num_quads[out]
 * \param num_sprites[out]
 * \param num_sprite_sets[out]
 * \param num_animations[out]
 * \param num_particle_emitters[out]
 * \param num_shaders[out]
 * \param num_bmp_fonts[out]
 * \param num_bmp_texts[out]
 */
void    YAGL_API    System_GetStats (int* num_textures, int* num_texture_maps, int* num_quads, int* num_sprites, int* num_sprite_sets, int* num_animations, int* num_particle_emitters, int* num_shaders, int* num_bmp_fonts, int* num_bmp_texts)
{
    if (num_textures != NULL)           { *num_textures = mem_type_get_size(PTR_TEXTURE); }
    if (num_texture_maps != NULL)       { *num_textures = mem_type_get_size(PTR_TEXTURE_MAP); }
    if (num_quads != NULL)              { *num_quads = mem_type_get_size(PTR_QUAD); }
    if (num_sprites != NULL)            { *num_sprites = mem_type_get_size(PTR_SPRITE); }
    if (num_sprite_sets != NULL)        { *num_sprite_sets = mem_type_get_size(PTR_SPRITE_SET); }
    if (num_animations != NULL)         { *num_animations = mem_type_get_size(PTR_ANIMATION); }
    if (num_particle_emitters != NULL)  { *num_particle_emitters = mem_type_get_size(PTR_PARTICLES); }
    if (num_shaders != NULL)            { *num_particle_emitters = mem_type_get_size(PTR_SHADER); }
    if (num_bmp_fonts != NULL)          { *num_bmp_fonts = mem_type_get_size(PTR_BMP_FONT); }
    if (num_bmp_texts != NULL)          { *num_bmp_texts = mem_type_get_size(PTR_BMP_TEXT); }
}

/** \brief Get various version numbers
 *
 * \param flag[in] See #eVERSION
 * \param major[out] Major version number
 * \param minor[out] Minor version number
 * \param revision[out] Revision number
 */
void    YAGL_API    System_GetVersion (eVERSION flag, int* major, int* minor, int* revision)
{
    switch (flag)
    {
        case VERSION_YAGL:
            if (major != NULL) { *major = YAGL_VERSION_MAJOR; }
            if (minor != NULL) { *major = YAGL_VERSION_MINOR; }
            if (revision != NULL) { *major = YAGL_VERSION_REVISION; }
        break;
        case VERSION_GLFW:
            glfwGetVersion(major, minor, revision);
        break;
        case VERSION_OGL:
            glfwGetGLVersion(major, minor, revision);
        break;
    }
}

/**
    @}
*/
