/**
    \addtogroup 100_sprite
    @{
*/

#define SPR_CHECK if (!mem_exists(spr, PTR_SPRITE)) { return; }
#define SPR_CHECK_RET(ret) if (!mem_exists(spr, PTR_SPRITE)) { return ret; }

#include <math.h>

#include "all.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline void __sprite_init(Sprite* spr)
{
    spr->visible = 1;
    spr->dynamic = 1;

    spr->tex = 0;
    spr->tex_rect_1[0] = 0; spr->tex_rect_1[1] = 0;
    spr->tex_rect_2[0] = 0; spr->tex_rect_2[1] = 0;
    spr->tex_rect_3[0] = 0; spr->tex_rect_3[1] = 0;
    spr->tex_rect_4[0] = 0; spr->tex_rect_4[1] = 0;
    spr->color = 0xFFFFFFFF; //YAGL_RGBA(255, 255, 255, 255);

    spr->pos.x = 0; spr->pos.y = 0;
    spr->size.x = 0; spr->size.y = 0;
    spr->center.x = 0; spr->center.y = 0;
    spr->center_enum = -1;
    spr->angle = 0;
    spr->blend_mode = BLEND_ALPHA;
    spr->flip.x = 1; spr->flip.y = 1;

    spr->vel.x = 0; spr->vel.y = 0;
    spr->accel.x = 0; spr->accel.y = 0;
    spr->vel_max = 0; spr->innertia = 0;
    spr->a_vel = 0; spr->a_accel = 0;
    spr->a_vel_max = 0; spr->a_innertia = 0;
    spr->tutor_vel = NULL;
    spr->tutor_avel = NULL;

    spr->shape_type = SHAPE_NONE;
    spr->shape_pos.x = 0; spr->shape_pos.y = 0;
    spr->shape_size.x = 0; spr->shape_size.y = 0;
    spr->collision_mask = 0; spr->collision_group = 0;

    spr->anim = NULL;
    spr->anim_start_frame = 1;
    spr->anim_frame = 1;
    spr->anim_status = 0;
    spr->anim_loop = 0;
    spr->anim_timer = 0;
    spr->anim_timer_mult = 1.0;

    spr->data = NULL;
}

inline void __sprite_set_tex(Sprite* spr, Texture* tex, float w, float h)
{
    if (tex != NULL) {
        spr->tex = tex;
        spr->size.x = tex->width;
        spr->size.y = tex->height;
    } else {
        spr->tex = NULL;
    }
    if (w > 0) { spr->size.x = w; }
    if (h > 0) { spr->size.y = h; }
}

inline void __sprite_set_tex_rect(Sprite* spr, float x, float y, float w, float h)
{
    if (spr->tex != NULL) {
        float fx, fy, fw, fh;
        if (w == 0) { w = spr->tex->width; }
        if (h == 0) { h = spr->tex->height; }
        fx = (float)x / spr->tex->width; fy = (float)y / spr->tex->height;
        fw = (float)w / spr->tex->width; fh = (float)h / spr->tex->height;
        spr->tex_rect_1[0] = fx;		spr->tex_rect_1[1] = fy;
		spr->tex_rect_2[0] = fx + fw;	spr->tex_rect_2[1] = fy;
		spr->tex_rect_3[0] = fx + fw;	spr->tex_rect_3[1] = fy + fh;
		spr->tex_rect_4[0] = fx;		spr->tex_rect_4[1] = fy + fh;
    } else {
        spr->tex_rect_1[0] = 0; spr->tex_rect_1[1] = 0;
        spr->tex_rect_2[0] = 0; spr->tex_rect_2[1] = 0;
        spr->tex_rect_3[0] = 0; spr->tex_rect_3[1] = 0;
        spr->tex_rect_4[0] = 0; spr->tex_rect_4[1] = 0;
    }
}

inline void __sprite_add_del_from_collision_list(Sprite* spr, eSHAPE shape)
{
    if (shape == SHAPE_NONE) {
        Set_Del(_engin_->collision_set, spr);
    } else {
        Set_Add(_engin_->collision_set, spr);
    }
    _engin_->coll_array_update = 1;
}

inline void __sprite_set_center(Sprite* spr, eCENTER flag)
{
    //if (spr->tex == NULL) {
    //    spr->center.x = 0; spr->center.y = 0;
    //    spr->center_enum = -1;
    //} else {
        spr->center_enum = flag;
        switch (flag)
        {
            case CENTER_CENTER:
				spr->center.x = spr->size.x / 2;
				spr->center.y = spr->size.y / 2;
            break;
			case CENTER_ULEFT:
				spr->center.x = 0;
				spr->center.y = 0;
            break;
			case CENTER_URIGHT:
				spr->center.x = spr->size.x;
				spr->center.y = 0;
            break;
			case CENTER_BLEFT:
				spr->center.x = 0;
				spr->center.y = spr->size.y;
            break;
			case CENTER_BRIGHT:
				spr->center.x = spr->size.x;
				spr->center.y = spr->size.y;
            break;
            case CENTER_CLEFT:
                spr->center.x = 0;
				spr->center.y = spr->size.y / 2;
            break;
            case CENTER_CRIGHT:
                spr->center.x = spr->size.x;
				spr->center.y = spr->size.y / 2;
            break;
            case CENTER_CUP:
                spr->center.x = spr->size.x / 2;
				spr->center.y = 0;
            break;
            case CENTER_CBOTTOM:
                spr->center.x = spr->size.x / 2;
				spr->center.y = spr->size.y;
            break;
        }
    //}
}

inline void __sprite_keep_center(Sprite* spr)
{
    if (spr->center_enum != -1) {
        __sprite_set_center(spr, spr->center_enum);
    }
}

inline void __sprite_get_point(Sprite* spr, float x, float y, float* new_x, float* new_y)
{
    float dist, angle;
    __cartesian_2_polar(x - spr->center.x, y - spr->center.y, &angle, &dist);
    if (dist == 0) {
        *new_x = spr->pos.x; *new_y = spr->pos.y;
    } else {
        angle = angle + spr->angle;
        __polar_2_cartesian(dist, angle, new_x, new_y);
        *new_x = *new_x + spr->pos.x;
        *new_y = *new_y + spr->pos.y;
    }
}

inline void __sprite_draw_no_tex(VectF pos, float angle, VectF center, VectF size, unsigned int color)
{
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);

    glTranslatef(pos.x, pos.y, 0);
    glRotatef(angle, 0, 0, 1);
    glTranslatef(-center.x, -center.y, 0);
    glScalef(size.x, size.y, 1);

    glColor4ubv((GLubyte*)&color);

    glBegin(GL_TRIANGLE_FAN);
        glVertex2i(0, 0);
        glVertex2i(1, 0);
        glVertex2i(1, 1);
        glVertex2i(0, 1);
    glEnd();

    glEnable(GL_TEXTURE_2D);
}

inline void __sprite_draw_quad(Texture* tex, eBLEND_MODE blend, VectF pos, VectF size, VectF center, VectI flip, float angle, YAGL_Color color, float tex_rect1[], float tex_rect2[], float tex_rect3[], float tex_rect4[])
{
    if (tex != NULL) {
        if (tex->tex_id != 0) {
            __texture_bind(tex);
            __set_blend_mode(blend);

            glLoadIdentity();

            glTranslatef(pos.x, pos.y, 0);
            glRotatef(angle, 0, 0, 1);
            glScalef(flip.x, flip.y, 1);
            glTranslatef(-center.x, -center.y, 0);
            glScalef(size.x, size.y, 1);

            glColor4ubv((GLubyte*)&color);

            glBegin(GL_TRIANGLE_FAN);
                glTexCoord2fv((GLfloat*)tex_rect1); glVertex2i(0, 0);
                glTexCoord2fv((GLfloat*)tex_rect2); glVertex2i(1, 0);
                glTexCoord2fv((GLfloat*)tex_rect3); glVertex2i(1, 1);
                glTexCoord2fv((GLfloat*)tex_rect4); glVertex2i(0, 1);
            glEnd();

        } else {
            __sprite_draw_no_tex(pos, angle, center, size, color);
        }
    } else {
        __sprite_draw_no_tex(pos, angle, center, size, color);
    }
}

inline void __sprite_calc_dynamics (Sprite* spr)
{
    if (spr->dynamic != 0)
    {
        // Rotation
        if (spr->tutor_avel == NULL) {
            spr->a_vel = spr->a_vel + (spr->a_accel * _engin_->delta);
            if (spr->a_vel_max != 0 && fabs(spr->a_vel) > fabs(spr->a_vel_max)) {
                spr->a_vel = spr->a_vel / fabs(spr->a_vel);
                spr->a_vel = spr->a_vel * fabs(spr->a_vel_max);
            }

            if (spr->a_innertia != 0 && spr->a_accel == 0 && spr->a_vel != 0) {
                float a_vel_signe = spr->a_vel / fabs(spr->a_vel);
                spr->a_vel = spr->a_vel - (a_vel_signe * (fabs(spr->a_innertia) * _engin_->delta));
                if (a_vel_signe != spr->a_vel / fabs(spr->a_vel)) { spr->a_vel = 0; }
            }
        } else {
            spr->a_vel = spr->tutor_avel->a_vel;
        }

        spr->angle = spr->angle + (spr->a_vel * _engin_->delta);
        __reduce_angle(&spr->angle);

        // Mouvement
        if (spr->tutor_vel == NULL) {
            spr->vel.x = spr->vel.x + (spr->accel.x * _engin_->delta);
            spr->vel.y = spr->vel.y + (spr->accel.y * _engin_->delta);

            float vel_len = __vect_len(spr->vel.x, spr->vel.y);
            if (spr->vel_max > 0 && vel_len > spr->vel_max) {
                spr->vel.x = (spr->vel.x / vel_len) * spr->vel_max;
                spr->vel.y = (spr->vel.y / vel_len) * spr->vel_max;

                vel_len = spr->vel_max;
            }

            if (spr->innertia > 0 && vel_len > 0 && spr->accel.x == 0 && spr->accel.y == 0) {
                spr->vel.x /= vel_len;
                spr->vel.y /= vel_len;

                vel_len -= spr->innertia * _engin_->delta;
                if (vel_len < 0) { vel_len = 0; }

                spr->vel.x *= vel_len;
                spr->vel.y *= vel_len;
            }
        } else {
            spr->vel.x = spr->tutor_vel->vel.x;
            spr->vel.y = spr->tutor_vel->vel.y;
        }

        spr->pos.x += (spr->vel.x * _engin_->delta);
        spr->pos.y += (spr->vel.y * _engin_->delta);
    }
}

inline void __sprite_calc_anim (Sprite* spr)
{
    if (spr->anim == NULL || spr->anim_status == 0) { return; }

    if ((glfwGetTime() - spr->anim_timer) * spr->anim->timer_mult * spr->anim_timer_mult * _engin_->timer_mult >= spr->anim->frames[spr->anim_frame - 1].duration) {
        spr->anim_frame += 1;
        if (spr->anim_frame > spr->anim->frame_count) { spr->anim_frame = 1; }

        if (spr->anim_frame == spr->anim_start_frame && !spr->anim_loop) {
            __sprite_apply_anim_frame(spr, spr->anim_start_frame);
            spr->anim_status = 0;
        }

        __sprite_apply_anim_frame(spr, spr->anim_frame);
    }
}

inline void __sprite_apply_anim_frame (Sprite* spr, unsigned int frame)
{
    if (spr->anim == NULL) { return; }
    if (frame < 1 || frame > spr->anim->frame_count) { return; }
    if (spr->anim->frames[frame - 1].is_set == 0) { return; }

    frame = frame - 1;

    spr->tex = spr->anim->frames[frame].tex;
    spr->tex_rect_1[0] = spr->anim->frames[frame].tex_rect_1[0];
    spr->tex_rect_1[1] = spr->anim->frames[frame].tex_rect_1[1];
    spr->tex_rect_2[0] = spr->anim->frames[frame].tex_rect_2[0];
    spr->tex_rect_2[1] = spr->anim->frames[frame].tex_rect_2[1];
    spr->tex_rect_3[0] = spr->anim->frames[frame].tex_rect_3[0];
    spr->tex_rect_3[1] = spr->anim->frames[frame].tex_rect_3[1];
    spr->tex_rect_4[0] = spr->anim->frames[frame].tex_rect_4[0];
    spr->tex_rect_4[1] = spr->anim->frames[frame].tex_rect_4[1];

    spr->color = spr->anim->frames[frame].color;
    spr->blend_mode = spr->anim->frames[frame].blend_mode;

    if (spr->anim->frames[frame].change_size) {
        spr->size.x = spr->anim->frames[frame].size.x;
        spr->size.y = spr->anim->frames[frame].size.y;

        __sprite_keep_center(spr);
    }

    spr->anim_timer = glfwGetTime();
}

/* ------------------------------------------------------------------------- **/
/* Public functions **/

/** \brief Create a Sprite
 *
 * \param tex[in] Texture object (Texture_Create())
 * \param rect_x[in] X-pos of the upper left corner of the rectangle to take from the texture
 * \param rect_y[in] Y-pos of the upper left corner of the rectangle to take from the texture
 * \param rect_w[in] Width of the rectangle to take from the texture (0 to take it all)
 * \param rect_h[in] Heigth of the rectangle to take from the texture (0 to take it all)
 *
 * \return Sprite object
 */
Sprite*     YAGL_API    Sprite_Create (Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h)
{
    Sprite* spr = mem_alloc(sizeof(Sprite), PTR_SPRITE);
    if (spr == NULL) {
        __DEBUG__("Unable to create Sprite! (Out of memory)", 2);
    }

    __sprite_init(spr);
    __sprite_set_tex(spr, tex, rect_w, rect_h);
    __sprite_set_tex_rect(spr, rect_x, rect_y, rect_w, rect_h);
    __sprite_set_center(spr, CENTER_CENTER);

    return spr;
}

/*
Function: Sprite_Create

Parameters:

Return:

*/
int   YAGL_API    Sprite_IsSprite (Sprite* spr)
{
    return mem_exists(spr, PTR_SPRITE);
}

/*
Function: Sprite_SetTexture

Parameters:

Return:

*/
void        YAGL_API    Sprite_SetTexture (Sprite* spr, Texture* tex)
{
    SPR_CHECK

    __sprite_set_tex(spr, tex, 0, 0);
}

/*
Function: Sprite_SetTextureRect

Parameters:

Return:

*/
void        YAGL_API    Sprite_SetTextureRect (Sprite* spr, int rect_x, int rect_y, int rect_w, int rect_h)
{
    SPR_CHECK

    __sprite_set_tex_rect(spr, rect_x, rect_y, rect_w, rect_h);
}

/*
Function: Sprite_SetTextureEx

Parameters:

Return:

*/
void        YAGL_API    Sprite_SetTextureEx (Sprite* spr, Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h)
{
    SPR_CHECK

    __sprite_set_tex(spr, tex, rect_w, rect_h);
    __sprite_set_tex_rect(spr, rect_x, rect_y, rect_w, rect_h);
}

/*
Function: Sprite_GetTexture

Parameters:

Return:

*/
Texture*    YAGL_API    Sprite_GetTexture (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return spr->tex;
}

/*
Function: Sprite_GetTextureRect

Parameters:

Return:

*/
void        YAGL_API    Sprite_GetTextureRect (Sprite* spr, int* rect_x, int* rect_y, int* rect_w, int* rect_h)
{
    SPR_CHECK

    if (spr->tex != NULL) {
        if (rect_x != NULL) { *rect_x = spr->tex_rect_1[0] * spr->tex->width; }
        if (rect_y != NULL) { *rect_y = spr->tex_rect_1[1] * spr->tex->height; }
        if (rect_w != NULL) { *rect_w = (spr->tex_rect_3[0] - spr->tex_rect_1[0]) * spr->tex->width; }
        if (rect_h != NULL) { *rect_h = (spr->tex_rect_3[1] - spr->tex_rect_1[1]) * spr->tex->height; }
    } else {
        if (rect_x != NULL) { *rect_x = 0; }
        if (rect_y != NULL) { *rect_y = 0; }
        if (rect_w != NULL) { *rect_w = 0; }
        if (rect_h != NULL) { *rect_h = 0; }
    }
}

/*
Function: Sprite_GetTextureEx

Parameters:

Return:

*/
Texture*    YAGL_API    Sprite_GetTextureEx (Sprite* spr, int* rect_x, int* rect_y, int* rect_w, int* rect_h)
{
    SPR_CHECK_RET(0)

    if (spr->tex != NULL) {
        if (rect_x != NULL) { *rect_x = spr->tex_rect_1[0] * spr->tex->width; }
        if (rect_y != NULL) { *rect_y = spr->tex_rect_1[1] * spr->tex->height; }
        if (rect_w != NULL) { *rect_w = (spr->tex_rect_3[0] - spr->tex_rect_1[0]) * spr->tex->width; }
        if (rect_h != NULL) { *rect_h = (spr->tex_rect_3[1] - spr->tex_rect_1[1]) * spr->tex->height; }
    } else {
        if (rect_x != NULL) { *rect_x = 0; }
        if (rect_y != NULL) { *rect_y = 0; }
        if (rect_w != NULL) { *rect_w = 0; }
        if (rect_h != NULL) { *rect_h = 0; }
    }

    return spr->tex;
}

/*
Function: Sprite_SetTextureMap

Parameters:

Return:

*/
void            YAGL_API    Sprite_SetTextureMap (Sprite* spr, TextureMap* tex_map, unsigned int rect_id)
{
    SPR_CHECK
    if (mem_exists(tex_map, PTR_TEXTURE_MAP) == 0) { return; }

    int x, y, w, h;
    __texture_map_get(tex_map, rect_id, &spr->tex, &x, &y, &w, &h);

    __sprite_set_tex(spr, tex_map->tex, w, h);
    __sprite_set_tex_rect(spr, x, y, w, h);
    __sprite_keep_center(spr);
}

/*
Function: Sprite_SetShape

Parameters:

Return:

*/
void        YAGL_API    Sprite_SetShape (Sprite* spr, eSHAPE shape_type, float x, float y, float w, float h)
{
    SPR_CHECK

    spr->shape_pos.x = x; spr->shape_pos.y = y;
    spr->shape_size.x = w; spr->shape_size.y = h;

    if (spr->shape_type != shape_type) {
        spr->shape_type = shape_type;
        __sprite_add_del_from_collision_list(spr, shape_type);
    }
}

/*
Function: Sprite_GetShape

Parameters:

Return:

*/
void        YAGL_API    Sprite_GetShape (Sprite* spr, eSHAPE* shape_type, float* x, float* y, float* w, float* h)
{
    SPR_CHECK

    if (shape_type != NULL) { *shape_type = spr->shape_type; }
    if (x != NULL) { *x = spr->shape_pos.x; }
    if (y != NULL) { *y = spr->shape_pos.y; }
    if (w != NULL) { *w = spr->shape_size.x; }
    if (h != NULL) { *h = spr->shape_size.y; }
}

/*
Function: Sprite_SetCollisionMask

Parameters:

Return:

*/
void        YAGL_API    Sprite_SetCollisionMask (Sprite* spr, int collision_mask)
{
    SPR_CHECK

    spr->collision_mask = collision_mask;
}

/*
Function: Sprite_GetCollisionMask

Parameters:

Return:

*/
int         YAGL_API    Sprite_GetCollisionMask (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return spr->collision_mask;
}

/*
Function: Sprite_SetCollisionMask

Parameters:

Return:

*/
void        YAGL_API    Sprite_SetCollisionGroup (Sprite* spr, int collision_group)
{
    SPR_CHECK

    spr->collision_group = collision_group;
}

/*
Function: Sprite_GetCollisionMask

Parameters:

Return:

*/
int         YAGL_API    Sprite_GetCollisionGroup (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return spr->collision_group;
}

/*
Function: Sprite_AnimationSet

Parameters:

Return:

*/
void        YAGL_API    Sprite_AnimationSet (Sprite* spr, Animation* anim)
{
    SPR_CHECK

    spr->anim = anim;
    spr->anim_start_frame = 1;
    spr->anim_frame = 1;
    spr->anim_status = 0;
    spr->anim_loop = 0;
    spr->anim_timer = 0;
}

/*
Function: Sprite_AnimationSet

Parameters:

Return:

*/
Animation*  YAGL_API    Sprite_AnimationGet (Sprite* spr)
{
    SPR_CHECK_RET(NULL)

    return spr->anim;
}

/*
Function: Sprite_AnimationSetFrame

Parameters:

Return:

*/
void        YAGL_API    Sprite_AnimationSetFrame (Sprite* spr, unsigned int frame_id)
{
    SPR_CHECK

    if (spr->anim == NULL) { return; }

    if (frame_id < 1) { frame_id = 1; }
    if (frame_id > spr->anim->frame_count) { frame_id = spr->anim->frame_count; }

    spr->anim_frame = frame_id;
}

/*
Function: Sprite_AnimationDisplayFrame

Parameters:

Return:

*/
void            YAGL_API    Sprite_AnimationDisplayFrame (Sprite* spr, unsigned int frame_id)
{
    SPR_CHECK

    if (spr->anim == NULL) { return; }

    //if (frame_id = -1) { frame_id = spr->anim_frame; }
    if (frame_id < 1) { frame_id = 1; }
    if (frame_id > spr->anim->frame_count) { frame_id = spr->anim->frame_count; }

    spr->anim_frame = frame_id;
    __sprite_apply_anim_frame(spr, frame_id);
}

/*
Function: Sprite_AnimationGetFrame

Parameters:

Return:

*/
unsigned int    YAGL_API    Sprite_AnimationGetFrame (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return spr->anim_frame;
}

/*
Function: Sprite_AnimationSetStartFrame

Parameters:

Return:

*/
void        YAGL_API    Sprite_AnimationSetStartFrame (Sprite* spr, unsigned int frame_id)
{
    SPR_CHECK

    if (spr->anim == NULL) { return; }

    if (frame_id < 1) { frame_id = 1; }
    if (frame_id > spr->anim->frame_count) { frame_id = spr->anim->frame_count; }

    spr->anim_start_frame = frame_id;
}

/*
Function: Sprite_AnimationGetStartFrame

Parameters:

Return:

*/
unsigned int    YAGL_API    Sprite_AnimationGetStartFrame (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return spr->anim_start_frame;
}

/*
Function: Sprite_AnimationSetTimerMult

Parameters:

Return:

*/
void            YAGL_API    Sprite_AnimationSetTimerMult (Sprite* spr, float tm)
{
    SPR_CHECK

    spr->anim_timer_mult = tm;
}

/*
Function: Sprite_AnimationGetTimerMult

Parameters:

Return:

*/
float           YAGL_API    Sprite_AnimationGetTimerMult (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return spr->anim_timer_mult;
}

/*
Function: Sprite_AnimationGo

Parameters:

Return:

*/
void        YAGL_API    Sprite_AnimationGo (Sprite* spr, int loop)
{
    SPR_CHECK

    if (spr->anim == NULL) { return; }

    spr->anim_status = 1;
    spr->anim_loop = loop;

    __sprite_apply_anim_frame(spr, spr->anim_start_frame);
}

/*
Function: Sprite_AnimationGetStatus

Parameters:

Return:

*/
int       YAGL_API    Sprite_AnimationGetStatus (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return spr->anim_status;
}

/*
Function: Sprite_AnimationGetLoop

Parameters:

Return:

*/
int       YAGL_API    Sprite_AnimationGetLoop (Sprite* spr)
{
    SPR_CHECK_RET(0)

    return spr->anim_loop;
}

/*
Function: Sprite_AnimationStop

Parameters:

Return:

*/
void        YAGL_API    Sprite_AnimationStop (Sprite* spr, unsigned int stop_frame)
{
    SPR_CHECK

    if (spr->anim == NULL) { return; }

    spr->anim_status = 0;
    spr->anim_timer = 0;

    if (stop_frame < 1) { stop_frame = spr->anim_start_frame; }
    __sprite_apply_anim_frame(spr, stop_frame);
}

/*
Function: Sprite_SetCenterEx

Parameters:

Return:

*/
void        YAGL_API    Sprite_SetCenterEx (Sprite* spr, eCENTER flag)
{
    SPR_CHECK

    __sprite_set_center(spr, flag);
}

/*
Function: Sprite_Move

Parameters:

Return:

*/
void        YAGL_API    Sprite_Move (Sprite* spr, float x, float y)
{
    SPR_CHECK

    spr->pos.x = spr->pos.x + x;
    spr->pos.y = spr->pos.y + y;
}

/*
Function: Sprite_Rotate

Parameters:

Return:

*/
void        YAGL_API    Sprite_Rotate (Sprite* spr, float angle)
{
    SPR_CHECK

    spr->angle = spr->angle + angle;
}

/*
Function: Sprite_Rotate

Parameters:

Return:

*/
void        YAGL_API    Sprite_Scale (Sprite* spr, float x, float y)
{
    SPR_CHECK

    if (x >= 0) { spr->size.x = spr->size.x * x; }
    if (y >= 0) { spr->size.y = spr->size.y * y; }

    __sprite_keep_center(spr);
}

/*
Function: Sprite_SetFlip

Parameters:

Return:

*/
void            YAGL_API    Sprite_SetFlip (Sprite* spr, int x, int y)
{
    SPR_CHECK

    if (x == 0) {
        spr->flip.x = 1;
    } else {
        spr->flip.x = -1;
    }
    if (y == 0) {
        spr->flip.y = 1;
    } else {
        spr->flip.y = -1;
    }
}

/*
Function: Sprite_GetFlip

Parameters:

Return:

*/
void            YAGL_API    Sprite_GetFlip (Sprite* spr, int* x, int* y)
{
    SPR_CHECK

    if (x != NULL) {
        if (spr->flip.x == 1) {
            *x = 0;
        } else {
            *x = 1;
        }
    }
    if (y != NULL) {
        if (spr->flip.y == 1) {
            *y = 0;
        } else {
            *y = 1;
        }
    }
}

/*
Function: Sprite_SetVelLen

Parameters:

Return:

*/
void        YAGL_API    Sprite_SetVelLen (Sprite* spr, float len)
{
    SPR_CHECK

    __polar_2_cartesian(len, spr->angle, &spr->vel.x, &spr->vel.y);
}

/*
Function: Sprite_SetVelEx

Parameters:

Return:

*/
void        YAGL_API    Sprite_SetVelEx (Sprite* spr, float len, float angle)
{
    SPR_CHECK

    __polar_2_cartesian(len, angle, &spr->vel.x, &spr->vel.y);
}

/*
Function: Sprite_GetVelEx

Parameters:

Return:

*/
void        YAGL_API    Sprite_GetVelEx (Sprite* spr, float* len, float* angle)
{
    SPR_CHECK

    __cartesian_2_polar(spr->vel.x, spr->vel.y, angle, len);
}

/*
Function: Sprite_SetVelAngle

Parameters:

Return:

*/
void        YAGL_API    Sprite_SetVelAngle (Sprite* spr, float angle)
{
    SPR_CHECK

    __polar_2_cartesian(__vect_len(spr->vel.x, spr->vel.y), angle, &spr->vel.x, &spr->vel.y);
}

/*
Function: Sprite_SetAccelLen

Parameters:

Return:

*/
void        YAGL_API    Sprite_SetAccelLen (Sprite* spr, float len)
{
    SPR_CHECK

    __polar_2_cartesian(len, spr->angle, &spr->accel.x, &spr->accel.y);
}

/*
Function: Sprite_SetAccelEx

Parameters:

Return:

*/
void        YAGL_API    Sprite_SetAccelEx (Sprite* spr, float len, float angle)
{
    SPR_CHECK

    __polar_2_cartesian(len, angle, &spr->accel.x, &spr->accel.y);
}

/*
Function: Sprite_GetAccelEx

Parameters:

Return:

*/
void        YAGL_API    Sprite_GetAccelEx (Sprite* spr, float* len, float* angle)
{
    SPR_CHECK

    __cartesian_2_polar(spr->accel.x, spr->accel.y, angle, len);
}

/*
Function: Sprite_SetAccelAngle

Parameters:

Return:

*/
void        YAGL_API    Sprite_SetAccelAngle (Sprite* spr, float angle)
{
    SPR_CHECK

    __polar_2_cartesian(__vect_len(spr->accel.x, spr->accel.y), angle, &spr->accel.x, &spr->accel.y);
}

/*
Function: Sprite_SpriteToWorld

Parameters:

Return:

*/
void        YAGL_API    Sprite_SpriteToWorld (Sprite* spr, float spr_x, float spr_y, float* world_x, float* world_y)
{
    SPR_CHECK

    __sprite_get_point(spr, spr_x, spr_y, world_x, world_y);
}

/*
Function: Sprite_SpriteToWorldEx

Parameters:

Return:

*/
void        YAGL_API    Sprite_SpriteToWorldEx (Sprite* spr, float spr_x_ratio, float spr_y_ratio, float* world_x, float* world_y)
{
    SPR_CHECK

    __sprite_get_point(spr, spr_x_ratio * spr->size.x, spr_y_ratio * spr->size.y, world_x, world_y);
}

/*
Function: Sprite_WorldToSprite

Parameters:

Return:

*/
void            YAGL_API    Sprite_WorldToSprite (Sprite* spr, float world_x, float world_y, float* spr_x, float* spr_y, int folow_spr_angle)
{
    SPR_CHECK
}

/*
Function: Sprite_Draw

Parameters:

Return:

*/
void        YAGL_API    Sprite_Draw (Sprite* spr)
{
    SPR_CHECK

    __sprite_calc_dynamics (spr);
    __sprite_calc_anim (spr);

    if (spr->visible != 0) {
        __sprite_draw_quad(spr->tex, spr->blend_mode, spr->pos, spr->size, spr->center, spr->flip, spr->angle, spr->color, spr->tex_rect_1, spr->tex_rect_2, spr->tex_rect_3, spr->tex_rect_4);
    }
}

/*
Function: Sprite_DrawShape

Parameters:

Return:

*/
void        YAGL_API    Sprite_DrawShape (Sprite* spr)
{
    SPR_CHECK

    if (spr->shape_type == SHAPE_NONE) { return; }

    float x, y;
    __sprite_get_point(spr, spr->shape_pos.x, spr->shape_pos.y, &x, &y);

    switch (spr->shape_type)
    {
        case SHAPE_POINT:
            Draw_Point(x, y);
        break;
        case SHAPE_CIRCLE:
            Draw_Ellipse(x, y, spr->shape_size.x, spr->shape_size.x, 0, 30);
        break;
        case SHAPE_RECT:
            Draw_RectCenter(x, y, spr->shape_size.x, spr->shape_size.y, 0);
        break;
        case SHAPE_NONE: break;
    }
}

/*
Function: Sprite_Destroy

Parameters:

Return:

*/
int   YAGL_API    Sprite_Destroy (Sprite* spr)
{
    SPR_CHECK_RET(0)

    if (spr->shape_type != SHAPE_NONE) { __sprite_add_del_from_collision_list(spr, SHAPE_NONE); }

    return mem_free(spr, PTR_SPRITE);
}

/**
    @}
*/
