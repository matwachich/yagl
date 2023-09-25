/**
    \addtogroup 120_animation
    @{
*/

#include "all.h"

extern Engin* _engin_;

/* -------------------------------------------------------------------------- */
/* Internal functions */

inline void __anim_frame_init (AnimFrame* frame)
{
    frame->is_set = 0;

    frame->tex = NULL;
    frame->tex_rect_1[0] = 0; frame->tex_rect_1[1] = 0;
    frame->tex_rect_2[0] = 0; frame->tex_rect_2[1] = 0;
    frame->tex_rect_3[0] = 0; frame->tex_rect_3[1] = 0;
    frame->tex_rect_4[0] = 0; frame->tex_rect_4[1] = 0;

    frame->color = -1; // -1 = no change
    frame->blend_mode = BLEND_NO_CHANGE; // -1 = no change

    frame->change_size = 0;
    frame->size.x = 0; frame->size.y = 0;

    frame->duration = 0;
}

inline void __anim_frame_set_blank (AnimFrame* frame)
{
    __anim_frame_init(frame);
    frame->is_set = 1;
}

inline int __anim_get_next_free_frame (Animation* anim)
{
    if (anim->frame_count == anim->frame_max) { return -1; }

    int i = 0;
    for (i=0; i!=anim->frame_max; i++) { // <
        if (anim->frames[i].is_set == 0) { return i; }
    }
    return -1;
}

inline void __anim_frame_set_tex_rect (AnimFrame* frame, int x, int y, int w, int h)
{
    if (frame->tex != NULL) {
        float fx, fy, fw, fh;
        if (w == 0) { w = frame->tex->width; }
        if (h == 0) { h = frame->tex->height; }
        fx = (float)x / frame->tex->width; fy = (float)y / frame->tex->height;
        fw = (float)w / frame->tex->width; fh = (float)h / frame->tex->height;
        frame->tex_rect_1[0] = fx;		frame->tex_rect_1[1] = fy;
		frame->tex_rect_2[0] = fx + fw;	frame->tex_rect_2[1] = fy;
		frame->tex_rect_3[0] = fx + fw;	frame->tex_rect_3[1] = fy + fh;
		frame->tex_rect_4[0] = fx;		frame->tex_rect_4[1] = fy + fh;
    } else {
        frame->tex_rect_1[0] = 0; frame->tex_rect_1[1] = 0;
        frame->tex_rect_2[0] = 0; frame->tex_rect_2[1] = 0;
        frame->tex_rect_3[0] = 0; frame->tex_rect_3[1] = 0;
        frame->tex_rect_4[0] = 0; frame->tex_rect_4[1] = 0;
    }
}

/* ------------------------------------------------------------------------- **/
/* Public functions **/

/**
 * \brief Create an Animation object
 *
 * \param frames_count[in] Maximum frames
 *
 * \return Animation pointer
 *
 */
Animation*      YAGL_API    Animation_Create (unsigned int frames_count)
{
    Animation* anim = mem_alloc(sizeof(Animation), PTR_ANIMATION);
    if (anim == NULL) { __DEBUG__("Unable to create Animation! (Out of memory)", 2); }

    anim->frames = malloc(sizeof(AnimFrame) * frames_count);
    if (anim->frames == NULL) { free(anim); __DEBUG__("Unable to create Animation! (Out of memory)", 2); }

    int i = 0;
    for (i=0; i!=frames_count; i++) { // <
        __anim_frame_init(&anim->frames[i]);
    }

    anim->frame_count = 0;
    anim->frame_max = frames_count;
    anim->timer_mult = 1.0;

    return anim;
}

/**
 * \brief Check if the pointer is an Animation object
 *
 * \param anim[in] Any pointer
 *
 * \return 1 if it's an Animation, 0 otherwise
 *
 */
int       YAGL_API    Animation_IsAnimation (Animation* anim)
{
    return mem_exists(anim, PTR_ANIMATION);
}

/**
 * \brief Add a frame to an Animation object
 *
 * \param anim[in] Animation object
 * \param duration[in] Frame duration (in seconds)
 * \param tex[in] Texture object
 * \param rect_x[in] Texture rectangle upper-left corner x-coord
 * \param rect_y[in] Texture rectangle upper-left corner y-coord
 * \param rect_w[in] Texture rectangle width
 * \param rect_h[in] Texture rectangle height
 * \param color[in] Frame color
 * \param change_size[in] Tell if the frame should change the size of the Sprite
 * \param size_x[in] New size (width)
 * \param size_y[in] New size (height)
 *
 * \return New frame id, or -1 if error (anim isn't an Animation, anim is full)
 *
 */
int             YAGL_API    Animation_AddFrameEx (Animation* anim, float duration, Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h, YAGL_Color color, eBLEND_MODE blend_mode, int change_size, float size_x, float size_y)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return -1; }

    int slot = __anim_get_next_free_frame(anim);
    if (slot == -1) { return -1; }

    anim->frame_count++;

    anim->frames[slot].is_set = 1;

    anim->frames[slot].duration = duration;
    anim->frames[slot].color = color;
    anim->frames[slot].blend_mode = blend_mode;
    anim->frames[slot].change_size = change_size;
    anim->frames[slot].size.x = size_x;
    anim->frames[slot].size.y = size_y;

    anim->frames[slot].tex = tex;
    __anim_frame_set_tex_rect(&anim->frames[slot], rect_x, rect_y, rect_w, rect_h);

    return slot + 1;
}

/** \brief Add an empty frame
 *
 * \param anim[in] Animation object
 * \param duration[in] Frame duration (in seconds)
 *
 * \return New frame id, or -1 if error (anim isn't an Animation, anim is full)
 *
 */
int             YAGL_API    Animation_AddFrame (Animation* anim, float duration)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return -1; }

    int slot = __anim_get_next_free_frame(anim);
    if (slot == -1) { return -1; }

    anim->frame_count++;
    __anim_frame_set_blank(&anim->frames[slot]);

    anim->frames[slot].duration = duration;

    return slot + 1;
}

/** \brief Set a Frame as blank
 *
 * \param anim[in] Animation object
 * \param frame_id[in] Frame ID to set blank
 *
 */
void            YAGL_API    Animation_FrameSetBlank (Animation* anim, unsigned int frame_id)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return; }

    if (frame_id < 1 || frame_id > anim->frame_max) { return; }

    __anim_frame_set_blank(&anim->frames[frame_id - 1]);

}

/** \brief Get frames count
 *
 * \param anim[in] Animation object
 *
 * \return Frames count, or -1 if error (anim isn't an Animation)
 *
 */
int             YAGL_API    Animation_FrameCount (Animation* anim)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return -1; }

    return anim->frame_count;
}

/** \brief Get max frames
 *
 * \param anim[in] Animation object
 *
 * \return Max frames count, or -1 if error (anim isn't an Animation)
 *
 */
int             YAGL_API    Animation_FrameMax (Animation* anim)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return -1; }

    return anim->frame_max;
}

/** \brief Delete all animation's frames
 *
 * \param anim[in] Animation object
 *
 */
void            YAGL_API    Animation_Empty (Animation* anim)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return; }

    int i = 0;
    for (i=0; i!=anim->frame_count; i++) { // <
        __anim_frame_init(&anim->frames[i]);
    }

    anim->frame_count = 0;
}

/** \brief
 *
 */
void            YAGL_API    Animation_SetTimerMult (Animation* anim, float tm)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return; }

    anim->timer_mult = tm;
}

/** \brief
 *
 */
float           YAGL_API    Animation_GetTimerMult (Animation* anim)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return 0; }

    return anim->timer_mult;
}

/** \brief Destroy animation
 *
 * \param anim[in] Animation object
 *
 * \return 1, or 0 on error
 *
 */
int       YAGL_API    Animation_Destroy (Animation* anim)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return 0; }

    free(anim->frames);
    return mem_free(anim, PTR_ANIMATION);
}

/* ------------------------------------------------------------------------- **/
/* Frames modification */

/** \brief Set the duration of a frame
 *
 * \param anim[in] Animation object
 * \param frame_id[in] Frame ID
 * \param duration[in] New duration (in seconds)
 *
 */
void            YAGL_API    Animation_FrameSetDuration (Animation* anim, unsigned int frame_id, float duration)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return; }

    if (frame_id < 1 || frame_id > anim->frame_max) { return; }

    anim->frames[frame_id - 1].duration = duration;
}

/** \brief Set the texture and texture rectangle of a frame
 *
 * \param anim[in] Animation object
 * \param frame_id[in] Frame ID
 * \param tex[in] Texture object
 * \param rect_x, rect_y[in] Upper-left corner of the texture rectangle
 * \param rect_w, rect_h[in] Size (width and height) of the texture rectangle
 *
 */
void            YAGL_API    Animation_FrameSetTexture (Animation* anim, unsigned int frame_id, Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return; }

    if (frame_id < 1 || frame_id > anim->frame_max) { return; }

    anim->frames[frame_id - 1].tex = tex;
    __anim_frame_set_tex_rect(&anim->frames[frame_id - 1], rect_x, rect_y, rect_w, rect_h);
}

/** \brief Set frame color
 *
 * \param anim[in] Animation object
 * \param frame_id[in] Frame ID
 * \param red, green, blue, alpha[in] New color (RGBA)
 *
 */
void            YAGL_API    Animation_FrameSetColor (Animation* anim, unsigned int frame_id, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return; }

    if (frame_id < 1 || frame_id > anim->frame_max) { return; }

    anim->frames[frame_id - 1].color = YAGL_RGBA(red, green, blue, alpha);
}

/** \brief Set frame color
 *
 * \param anim[in] Animation object
 * \param frame_id[in] Frame ID
 * \param color[in] Color (0xRRGGBBAA)
 *
 */
void            YAGL_API    Animation_FrameSetColorEx (Animation* anim, unsigned int frame_id, YAGL_Color color)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return; }

    if (frame_id < 1 || frame_id > anim->frame_max) { return; }

    anim->frames[frame_id - 1].color = color;
}

/** \brief Set frame blend mode
 *
 * \param anim[in] Animation object
 * \param frame_id[in] Frame ID
 * \param blend_mode[in] See eBLEND_MODE
 *
 */
void            YAGL_API    Animation_FrameSetBlendMode (Animation* anim, unsigned int frame_id, eBLEND_MODE blend_mode)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return; }

    if (frame_id < 1 || frame_id > anim->frame_max) { return; }

    anim->frames[frame_id - 1].blend_mode = blend_mode;
}

/** \brief
 *
 * \param anim[in] Animation object
 * \param frame_id[in] Frame ID
 * \param change_size[in]
 * \param size_x, size_y[in]
 *
 */
void            YAGL_API    Animation_FrameSetSize (Animation* anim, unsigned int frame_id, int change_size, float size_x, float size_y)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return; }

    if (frame_id < 1 || frame_id > anim->frame_max) { return; }

    anim->frames[frame_id - 1].change_size = change_size;
    anim->frames[frame_id - 1].size.x = size_x;
    anim->frames[frame_id - 1].size.y = size_y;
}

/* ------------------------------------------------------------------------- **/

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
float           YAGL_API    Animation_FrameGetDuration (Animation* anim, unsigned int frame_id)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return -1.0; }

    if (frame_id < 1 || frame_id > anim->frame_max) { return 0.0; }

    return anim->frames[frame_id - 1].duration;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
Texture*        YAGL_API    Animation_FrameGetTexture (Animation* anim, unsigned int frame_id, int* rect_x, int* rect_y, int* rect_w, int* rect_h)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return NULL; }

    if (frame_id < 1 || frame_id > anim->frame_max) { return NULL; }

    if (anim->frames[frame_id - 1].tex != NULL) {
        if (rect_x != NULL) { *rect_x = anim->frames[frame_id - 1].tex_rect_1[0] * anim->frames[frame_id - 1].tex->width; }
        if (rect_y != NULL) { *rect_y = anim->frames[frame_id - 1].tex_rect_1[1] * anim->frames[frame_id - 1].tex->height; }
        if (rect_w != NULL) { *rect_w = (anim->frames[frame_id - 1].tex_rect_3[0] - anim->frames[frame_id - 1].tex_rect_1[0]) * anim->frames[frame_id - 1].tex->width; }
        if (rect_h != NULL) { *rect_h = (anim->frames[frame_id - 1].tex_rect_3[1] - anim->frames[frame_id - 1].tex_rect_1[1]) * anim->frames[frame_id - 1].tex->height; }
    } else {
        if (rect_x != NULL) { *rect_x = 0; }
        if (rect_y != NULL) { *rect_y = 0; }
        if (rect_w != NULL) { *rect_w = 0; }
        if (rect_h != NULL) { *rect_h = 0; }
    }

    return anim->frames[frame_id - 1].tex;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void            YAGL_API    Animation_FrameGetColor (Animation* anim, unsigned int frame_id, unsigned char* red, unsigned char* green, unsigned char* blue, unsigned char* alpha)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return; }

    if (frame_id < 1 || frame_id > anim->frame_max) { return; }

    if (red != NULL) { *red = YAGL_RGBA_R(anim->frames[frame_id - 1].color); }
    if (green != NULL) { *green = YAGL_RGBA_G(anim->frames[frame_id - 1].color); }
    if (blue != NULL) { *blue = YAGL_RGBA_B(anim->frames[frame_id - 1].color); }
    if (alpha != NULL) { *alpha = YAGL_RGBA_A(anim->frames[frame_id - 1].color); }
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
YAGL_Color      YAGL_API    Animation_FrameGetColorEx (Animation* anim, unsigned int frame_id)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return -1; }

    if (frame_id < 1 || frame_id > anim->frame_max) { return 0; }

    return anim->frames[frame_id - 1].color;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
int             YAGL_API    Animation_FrameGetBlendMode (Animation* anim, unsigned int frame_id)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return -1; }

    if (frame_id < 1 || frame_id > anim->frame_max) { return 0; }

    return anim->frames[frame_id - 1].blend_mode;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
int             YAGL_API    Animation_FrameGetSize (Animation* anim, unsigned int frame_id, float* size_x, float* size_y)
{
    if (mem_exists(anim, PTR_ANIMATION) == 0) { return -1; }

    if (frame_id < 1 || frame_id > anim->frame_max) { return 0; }

    if (size_x != NULL) { *size_x = anim->frames[frame_id - 1].size.x; }
    if (size_y != NULL) { *size_x = anim->frames[frame_id - 1].size.y; }

    return anim->frames[frame_id - 1].change_size;
}

/**
    @}
*/
