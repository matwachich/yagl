/**
    \addtogroup 090_quad
    @{
*/

#define QUAD_CHECK if (!mem_exists(qd, PTR_QUAD)) { return; }
#define QUAD_CHECK_RET(ret) if (!mem_exists(qd, PTR_QUAD)) { return ret; }

#define QUAD_DBG(qd) printf("Quad: %i\nVisible: %i\nColor: %i\nBlend Mode: %i\nTex: %i\nTex Rect: (%f,%f), (%f,%f), (%f,%f), (%f,%f)\nPos: %f,%f\nSize: %f,%f\nCenter: %f,%f\n", qd, qd->visible, qd->color, qd->blend_mode, qd->tex, qd->tex_rect_1[0], qd->tex_rect_1[1], qd->tex_rect_2[0], qd->tex_rect_2[1], qd->tex_rect_3[0], qd->tex_rect_3[1], qd->tex_rect_4[0], qd->tex_rect_4[1], qd->pos.x, qd->pos.y, qd->size.x, qd->size.y, qd->center.x, qd->center.y); fflush(NULL);

#include "all.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline void __quad_init (Quad* qd)
{
    qd->visible = 1;
    qd->tex = 0;
    qd->tex_rect_1[0] = 0; qd->tex_rect_1[1] = 0;
    qd->tex_rect_2[0] = 0; qd->tex_rect_2[1] = 0;
    qd->tex_rect_3[0] = 0; qd->tex_rect_3[1] = 0;
    qd->tex_rect_4[0] = 0; qd->tex_rect_4[1] = 0;
	qd->color = 0xFFFFFFFF; //YAGL_RGBA(255, 255, 255, 255);
	qd->pos.x = 0; qd->pos.y = 0;
	qd->size.x = 0; qd->size.y = 0;
	qd->center.x = 0; qd->center.y = 0;
	qd->center_enum = -1;
	qd->angle = 0;
	qd->flip.x = 1; qd->flip.y = 1;
    qd->blend_mode = BLEND_ALPHA;
	qd->data = NULL;
}

inline void __quad_set_tex(Quad* qd, Texture* tex, float w, float h)
{
    if (tex != NULL) {
        qd->tex = tex;
        qd->size.x = tex->width;
        qd->size.y = tex->height;
    } else {
        qd->tex = NULL;
    }
    if (w > 0) { qd->size.x = w; }
    if (h > 0) { qd->size.y = h; }
}

inline void __quad_set_tex_rect(Quad* qd, float x, float y, float w, float h)
{
    if (qd->tex != NULL) {
        float fx, fy, fw, fh;
        if (w == 0) { w = qd->tex->width; }
        if (h == 0) { h = qd->tex->height; }
        fx = (float)x / qd->tex->width; fy = (float)y / qd->tex->height;
        fw = (float)w / qd->tex->width; fh = (float)h / qd->tex->height;
        qd->tex_rect_1[0] = fx;		    qd->tex_rect_1[1] = fy;
		qd->tex_rect_2[0] = fx + fw;	qd->tex_rect_2[1] = fy;
		qd->tex_rect_3[0] = fx + fw;	qd->tex_rect_3[1] = fy + fh;
		qd->tex_rect_4[0] = fx;		    qd->tex_rect_4[1] = fy + fh;
    } else {
        qd->tex_rect_1[0] = 0; qd->tex_rect_1[1] = 0;
        qd->tex_rect_2[0] = 0; qd->tex_rect_2[1] = 0;
        qd->tex_rect_3[0] = 0; qd->tex_rect_3[1] = 0;
        qd->tex_rect_4[0] = 0; qd->tex_rect_4[1] = 0;
    }
}

inline void __quad_set_center(Quad* qd, eCENTER flag)
{
    //if (spr->tex == NULL) {
    //    spr->center.x = 0; spr->center.y = 0;
    //    spr->center_enum = -1;
    //} else {
        qd->center_enum = flag;
        switch (flag)
        {
            case CENTER_CENTER:
				qd->center.x = qd->size.x / 2;
				qd->center.y = qd->size.y / 2;
            break;
			case CENTER_ULEFT:
				qd->center.x = 0;
				qd->center.y = 0;
            break;
			case CENTER_URIGHT:
				qd->center.x = qd->size.x;
				qd->center.y = 0;
            break;
			case CENTER_BLEFT:
				qd->center.x = 0;
				qd->center.y = qd->size.y;
            break;
			case CENTER_BRIGHT:
				qd->center.x = qd->size.x;
				qd->center.y = qd->size.y;
            break;
            case CENTER_CLEFT:
                qd->center.x = 0;
				qd->center.y = qd->size.y / 2;
            break;
            case CENTER_CRIGHT:
                qd->center.x = qd->size.x;
				qd->center.y = qd->size.y / 2;
            break;
            case CENTER_CUP:
                qd->center.x = qd->size.x / 2;
				qd->center.y = 0;
            break;
            case CENTER_CBOTTOM:
                qd->center.x = qd->size.x / 2;
				qd->center.y = qd->size.y;
            break;
        }
    //}
}

inline void __quad_keep_center(Quad* qd)
{
    if (qd->center_enum != -1) {
        __quad_set_center(qd, qd->center_enum);
    }
}

inline void __quad_get_point(Quad* qd, float x, float y, float* new_x, float* new_y)
{
    float dist, angle;
    __cartesian_2_polar(x - qd->center.x, y - qd->center.y, &angle, &dist);
    if (dist == 0) {
        *new_x = qd->pos.x; *new_y = qd->pos.y;
    } else {
        angle = angle + qd->angle;
        __polar_2_cartesian(dist, angle, new_x, new_y);
        *new_x = *new_x + qd->pos.x;
        *new_y = *new_y + qd->pos.y;
    }
}

/* ------------------------------------------------------------------------- **/
/* Public functions **/

/** \brief Create a textured Quad
 *
 * \param tex[in] Texture object (Texture_Create())
 * \param rect_x[in] X-pos of the upper left corner of the rectangle to take from the texture
 * \param rect_y[in] Y-pos of the upper left corner of the rectangle to take from the texture
 * \param rect_w[in] Width of the rectangle to take from the texture (0 to take it all)
 * \param rect_h[in] Heigth of the rectangle to take from the texture (0 to take it all)
 *
 * \return Quad object
 */
Quad*       YAGL_API    Quad_Create (Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h)
{
    Quad* qd = mem_alloc(sizeof(Quad), PTR_QUAD);
    if (qd == NULL) {
        __DEBUG__("Unable to create Quad! (Out of memory)", 2);
    }

    __quad_init(qd);
    __quad_set_tex(qd, tex, rect_w, rect_h);
    __quad_set_tex_rect(qd, rect_x, rect_y, rect_w, rect_h);
    __quad_set_center(qd, CENTER_CENTER);

    return qd;
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
int   YAGL_API    Quad_IsQuad (Quad* qd)
{
    return mem_exists(qd, PTR_QUAD);
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void        YAGL_API    Quad_SetTexture (Quad* qd, Texture* tex)
{
    QUAD_CHECK

    __quad_set_tex(qd, tex, 0, 0);
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void        YAGL_API    Quad_SetTextureRect (Quad* qd, int rect_x, int rect_y, int rect_w, int rect_h)
{
    QUAD_CHECK

    __quad_set_tex_rect(qd, rect_x, rect_y, rect_w, rect_h);
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void        YAGL_API    Quad_SetTextureEx (Quad* qd, Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h)
{
    QUAD_CHECK

    __quad_set_tex(qd, tex, rect_w, rect_h);
    __quad_set_tex_rect(qd, rect_x, rect_y, rect_w, rect_h);
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
Texture*    YAGL_API    Quad_GetTexture (Quad* qd)
{
    QUAD_CHECK_RET(NULL)

    return qd->tex;
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void        YAGL_API    Quad_GetTextureRect (Quad* qd, int* rect_x, int* rect_y, int* rect_w, int* rect_h)
{
    QUAD_CHECK

    if (qd->tex != NULL) {
        if (rect_x != NULL) { *rect_x = qd->tex_rect_1[0] * qd->tex->width; }
        if (rect_y != NULL) { *rect_y = qd->tex_rect_1[1] * qd->tex->height; }
        if (rect_w != NULL) { *rect_w = (qd->tex_rect_3[0] - qd->tex_rect_1[0]) * qd->tex->width; }
        if (rect_h != NULL) { *rect_h = (qd->tex_rect_3[1] - qd->tex_rect_1[1]) * qd->tex->height; }
    } else {
        if (rect_x != NULL) { *rect_x = 0; }
        if (rect_y != NULL) { *rect_y = 0; }
        if (rect_w != NULL) { *rect_w = 0; }
        if (rect_h != NULL) { *rect_h = 0; }
    }
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
Texture*    YAGL_API    Quad_GetTextureEx (Quad* qd, int* rect_x, int* rect_y, int* rect_w, int* rect_h)
{
    QUAD_CHECK_RET(NULL)

    if (qd->tex != NULL) {
        if (rect_x != NULL) { *rect_x = qd->tex_rect_1[0] * qd->tex->width; }
        if (rect_y != NULL) { *rect_y = qd->tex_rect_1[1] * qd->tex->height; }
        if (rect_w != NULL) { *rect_w = (qd->tex_rect_3[0] - qd->tex_rect_1[0]) * qd->tex->width; }
        if (rect_h != NULL) { *rect_h = (qd->tex_rect_3[1] - qd->tex_rect_1[1]) * qd->tex->height; }
    } else {
        if (rect_x != NULL) { *rect_x = 0; }
        if (rect_y != NULL) { *rect_y = 0; }
        if (rect_w != NULL) { *rect_w = 0; }
        if (rect_h != NULL) { *rect_h = 0; }
    }

    return qd->tex;
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void        YAGL_API    Quad_SetTextureMap (Quad* qd, TextureMap* tex_map, unsigned int rect_id)
{
    QUAD_CHECK
    if (mem_exists(tex_map, PTR_TEXTURE_MAP) == 0) { return; }

    int x, y, w, h;
    __texture_map_get(tex_map, rect_id, &qd->tex, &x, &y, &w, &h);

    __quad_set_tex(qd, tex_map->tex, w, h);
    __quad_set_tex_rect(qd, x, y, w, h);
    __quad_keep_center(qd);
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void        YAGL_API    Quad_SetCenterEx (Quad* qd, eCENTER flag)
{
    QUAD_CHECK

    __quad_set_center(qd, flag);
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void        YAGL_API    Quad_Move (Quad* qd, float x, float y)
{
    QUAD_CHECK

    qd->pos.x = qd->pos.x + x;
    qd->pos.y = qd->pos.y + y;
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void        YAGL_API    Quad_Rotate (Quad* qd, float angle)
{
    QUAD_CHECK

    qd->angle = qd->angle + angle;
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void        YAGL_API    Quad_Scale (Quad* qd, float x, float y)
{
    QUAD_CHECK

    if (x >= 0) { qd->size.x = qd->size.x * x; }
    if (y >= 0) { qd->size.y = qd->size.y * y; }

    __quad_keep_center(qd);
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void        YAGL_API    Quad_SetFlip (Quad* qd, int x, int y)
{
    QUAD_CHECK

    if (x == 0) {
        qd->flip.x = 1;
    } else {
        qd->flip.x = -1;
    }
    if (y == 0) {
        qd->flip.y = 1;
    } else {
        qd->flip.y = -1;
    }
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void        YAGL_API    Quad_GetFlip (Quad* qd, int* x, int* y)
{
    QUAD_CHECK

    if (x != NULL) {
        if (qd->flip.x == 1) {
            *x = 0;
        } else {
            *x = 1;
        }
    }
    if (y != NULL) {
        if (qd->flip.y == 1) {
            *y = 0;
        } else {
            *y = 1;
        }
    }
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void        YAGL_API    Quad_QuadToWorld (Quad* qd, float qd_x, float qd_y, float* world_x, float* world_y)
{
    QUAD_CHECK

    __quad_get_point(qd, qd_x, qd_y, world_x, world_y);
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void        YAGL_API    Quad_QuadToWorldEx (Quad* qd, float qd_x_ratio, float qd_y_ratio, float* world_x, float* world_y)
{
    QUAD_CHECK

    __quad_get_point(qd, qd_x_ratio * qd->size.x, qd_y_ratio * qd->size.y, world_x, world_y);
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void        YAGL_API    Quad_Draw (Quad* qd)
{
    QUAD_CHECK

    if (qd->visible != 0) {
        __sprite_draw_quad(qd->tex, qd->blend_mode, qd->pos, qd->size, qd->center, qd->flip, qd->angle, qd->color, qd->tex_rect_1, qd->tex_rect_2, qd->tex_rect_3, qd->tex_rect_4);
    }
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
int   YAGL_API    Quad_Destroy (Quad* qd)
{
    /* nécessaire seulement si on effectue des actions sur
    l'Objet avant de le détruire */
    //QUAD_CHECK_RET(0)

    return mem_free(qd, PTR_QUAD);
}

/**
    @}
*/
