/**
    \addtogroup 105_multiset
    @{
*/

#define MS_CHECK if (!mem_exists(ms, PTR_MULTISET)) { return; }
#define MS_CHECK_RET(ret) if (!mem_exists(ms, PTR_MULTISET)) { return ret; }

#include "all.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline void __multiset_destroy_elem (MultiSet* ms, void* elem)
{
    switch (ms->type) {
        case SET_TYPE_QUAD:
            mem_free(elem, PTR_QUAD);
        break;
        case SET_TYPE_SPRITE:
            if (((Sprite*)elem)->shape_type != SHAPE_NONE) { __sprite_add_del_from_collision_list(elem, SHAPE_NONE); }
            mem_free(elem, PTR_SPRITE);
        break;
        case SET_TYPE_PEMITTER:
            __particle_destroy_all_parts((PEmitter*)elem);
            mem_free(elem, PTR_PARTICLES);
        break;
        case SET_TYPE_BMPTEXT:
            if (((BmpText*)elem)->text != NULL) { free(((BmpText*)elem)->text); }
            mem_free(elem, PTR_BMP_TEXT);
        break;
        case SET_TYPE_ANY: break;
    }
}

inline void __multiset_del_all (MultiSet* ms, int destroy)
{
    if (ms->count == 0 || ms->first == NULL) { return; }

    MultiSetElem* current = ms->first;
    MultiSetElem* tmp = NULL;

    do {
        //if (destroy != 0 && ms->DestroyFunc != NULL) { ms->DestroyFunc(current->data); }
        if (destroy != 0) { __multiset_destroy_elem(ms, current->data); }

        tmp = current->next;
        free(current);
        current = tmp;

    } while (current != NULL);

    ms->first = NULL;
    ms->last = NULL;

    ms->count = 0;
}

/* ------------------------------------------------------------------------- **/
/* Public functions **/

MultiSet*   YAGL_API    MultiSet_Create (eSET_TYPE type)
{
    MultiSet* ms = mem_alloc(sizeof(MultiSet), PTR_MULTISET);
    if (ms == NULL) { __DEBUG__("Unable to create MultiSet! (Out of memory)", 2); }

    ms->count = 0;
    ms->type = type;
    ms->first = NULL;
    ms->last = NULL;

    if (ms->type != SET_TYPE_ANY) {
        /*switch (ms->type) {
            case SET_TYPE_ANY:
                //ms->DestroyFunc = NULL;
                //ms->DrawFunc = NULL;
                //ms->SetColorFunc = NULL;
                //ms->SetColorExFunc = NULL;
                //ms->SetBlendModeFunc = NULL;
                //ms->SetVisibleFunc = NULL;
            break;
            case SET_TYPE_QUAD:
                //ms->DestroyFunc = Quad_Destroy;
                //ms->DrawFunc = Quad_Draw;
                //ms->SetColorFunc = Quad_SetColor;
                //ms->SetColorExFunc = Quad_SetColorEx;
                //ms->SetBlendModeFunc = Quad_SetBlendMode;
                //ms->SetVisibleFunc = Quad_SetVisible;
            break;
            case SET_TYPE_SPRITE:
                //ms->DestroyFunc = Sprite_Destroy;
                //ms->DrawFunc = Sprite_Draw;
                //ms->SetColorFunc = Sprite_SetColor;
                //ms->SetColorExFunc = Sprite_SetColorEx;
                //ms->SetBlendModeFunc = Sprite_SetBlendMode;
                //ms->SetVisibleFunc = Sprite_SetVisible;
            break;
            case SET_TYPE_PEMITTER:
                //ms->DestroyFunc = PEmitter_Destroy;
                //ms->DrawFunc = PEmitter_Draw;
                //ms->SetColorFunc = PEmitter_SetColor;
                //ms->SetColorExFunc = NULL;
                //ms->SetBlendModeFunc = PEmitter_SetBlendMode;
               // ms->SetVisibleFunc = PEmitter_SetVisible;
            break;
            case SET_TYPE_BMPTEXT:
                //ms->DestroyFunc = BmpText_Destroy;
                //ms->DrawFunc = BmpText_Draw;
                //ms->SetColorFunc = BmpText_SetColor;
                //ms->SetColorExFunc = BmpText_SetColorEx;
                //ms->SetBlendModeFunc = BmpText_SetBlendMode;
                //ms->SetVisibleFunc = BmpText_SetVisible;
            break;
        }*/
        //
        ms->check_data_type = 1;
    } else {
        ms->check_data_type = 0;
    }

    return ms;
}

int         YAGL_API    MultiSet_IsMultiSet (MultiSet* ms)
{
    return mem_exists(ms, PTR_MULTISET);
}

eSET_TYPE   YAGL_API    MultiSet_GetDataType (MultiSet* ms)
{
    return ms->type;
}

int         YAGL_API    MultiSet_Destroy (MultiSet* ms, int destroy)
{
    MS_CHECK_RET(0)

    __multiset_del_all(ms, destroy);
    return mem_free(ms, PTR_MULTISET);
}


void        YAGL_API    MultiSet_Add (MultiSet* ms, void* data, int rank)
{
    MS_CHECK

    // on passe ms->type à mem_exists car il correspond à ePTR_TYPE
    if (ms->check_data_type != 0 && mem_exists(data, ms->type) == 0) { return; }

    MultiSetElem* elem = malloc(sizeof(MultiSetElem));
    if (elem == NULL) { __DEBUG__("Unable to add element to the MultiSet! (Out of memory)", 2); }

    elem->data = data;
    elem->rank = rank;
    elem->next = NULL;

    ms->count++;

    if (rank == -1) { // add to the end
        elem->next = NULL;
        if (ms->last != NULL) {
            ms->last->next = elem;
        }
        if (ms->first == NULL) {
            ms->first = elem;
        }
        ms->last = elem;
    } else {
        if (ms->first == NULL) { // it's the first element => no check
            ms->first = elem;
            ms->last = elem;
        } else {
            if (ms->first->rank > rank) { // the first element has bigger rank => add to the start
                elem->next = ms->first;
                ms->first = elem;
            } else {
                MultiSetElem* curr = NULL;
                for (curr = ms->first; curr != NULL; curr = curr->next) {
                    if (curr->next != NULL) {
                        if (curr->rank <= rank && curr->next->rank > rank) {
                            elem->next = curr->next;
                            curr->next = elem;
                            break;
                        }
                    } else { // add to the end
                        curr->next = elem;
                        ms->last = elem;
                        break;
                    }
                }
            }
        }
    }
}

int         YAGL_API    MultiSet_Exists (MultiSet* ms, void* data)
{
    MS_CHECK_RET(0)

    MultiSetElem* curr = NULL;
    for (curr = ms->first; curr != NULL; curr = curr->next) {
        if (curr->data == data) { return 1; }
    }
    return 0;
}

int         YAGL_API    MultiSet_Del (MultiSet* ms, void* data, int destroy)
{
    MS_CHECK_RET(0)

    MultiSetElem* current = ms->first;
    MultiSetElem* befor = NULL;

    do {
        if (current->data == data) {
            if (befor == NULL) {
                ms->first = current->next;
            } else {
                befor->next = current->next;
            }

            /*if (destroy && ms->DestroyFunc != NULL) {
                ms->DestroyFunc(current->data);
            }*/
            if (destroy != 0) { __multiset_destroy_elem(ms, current->data); }

            free(current);
            ms->count--;

            return 1;
        }
        befor = current;
        current = current->next;
    } while (current != NULL);

    return 0;
}

void        YAGL_API    MultiSet_DelAll (MultiSet* ms, int destroy)
{
    MS_CHECK
    __multiset_del_all(ms, destroy);
}


int         YAGL_API    MultiSet_Count (MultiSet* ms)
{
    MS_CHECK_RET(-1)

    return ms->count;
}

int         YAGL_API    MultiSet_GetAll (MultiSet* ms, void* data[], int size)
{
    MS_CHECK_RET(-1)
    if (ms->count == 0 || ms->first == NULL) { return 0; }

    if (size > ms->count) { size = ms->count; }

    int i = 0;
    MultiSetElem* current = ms->first;
    do {
        data[i] = current->data;
        // ---
        i++;
        current = current->next;
    } while (current != NULL && i < size);

    return i;
}

int         YAGL_API    MultiSet_Iterate (MultiSet* ms, YAGLMultiSetIterateProc enum_proc, void* user_data)
{
    MS_CHECK_RET(-1)
    if (enum_proc == NULL) { return -2; }
    if (ms->count == 0 || ms->first == NULL) { return 0; }

    MultiSetElem* current = ms->first;
    MultiSetElem* befor = NULL;
    MultiSetElem* to_free = NULL;

    int deleted = 0;

    do {
        switch (enum_proc(ms, current->data, user_data, current->rank, ms->type)) {
            default: // do nothing
            break;
            case 1: // remove sprite from spriteSet
                if (befor == NULL) {
                    ms->first = current->next;
                } else {
                    befor->next = current->next;
                }
                to_free = current;
            break;
            case 2: // remove sprite from spriteSet and destroy it (the sprite)
                if (befor == NULL) {
                    ms->first = current->next;
                } else {
                    befor->next = current->next;
                }
                //
                //ms->DestroyFunc(current->data);
                __multiset_destroy_elem(ms, current->data);
                //
                to_free = current;
            break;
        }
        // ---
        if (to_free != NULL) {
            current = current->next;

            if (ms->last == to_free) {
                ms->last = befor;
            }

            free(to_free);
            to_free = NULL;

            ms->count--;
            deleted++;
        } else {
            befor = current;
            current = current->next;
        }
    } while (current != NULL);

    return deleted;
}


/* Multi */
void        YAGL_API    MultiSet_Draw (MultiSet* ms) // quad, spr, pemitter, bmptext
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type == SET_TYPE_ANY) { return; }

    MultiSetElem* curr = NULL;
    switch (ms->type) {
        case SET_TYPE_QUAD: {
            Quad* qd = NULL;
            for (curr = ms->first; curr != NULL; curr = curr->next) {
                qd = (Quad*)curr->data;

                if (qd->visible != 0) {
                    __sprite_draw_quad(qd->tex, qd->blend_mode, qd->pos, qd->size, qd->center, qd->flip, qd->angle, qd->color, qd->tex_rect_1, qd->tex_rect_2, qd->tex_rect_3, qd->tex_rect_4);
                }
            }
        } break;
        case SET_TYPE_SPRITE: {
            Sprite* spr = NULL;
            for (curr = ms->first; curr != NULL; curr = curr->next) {
                spr = (Sprite*)curr->data;

                __sprite_calc_dynamics (spr);
                __sprite_calc_anim (spr);

                if (spr->visible != 0) {
                    __sprite_draw_quad(spr->tex, spr->blend_mode, spr->pos, spr->size, spr->center, spr->flip, spr->angle, spr->color, spr->tex_rect_1, spr->tex_rect_2, spr->tex_rect_3, spr->tex_rect_4);
                }
            }
        } break;
        case SET_TYPE_PEMITTER: {
            for (curr = ms->first; curr != NULL; curr = curr->next) {
                __pemitter_draw((PEmitter*)curr->data);
            }
        } break;
        case SET_TYPE_BMPTEXT: {
            BmpText* btxt = NULL;
            for (curr = ms->first; curr != NULL; curr = curr->next) {
                btxt = (BmpText*)curr->data;

                if (btxt->font == NULL) { return; }

                glColor4ubv((GLubyte*)&btxt->color);
                __set_blend_mode(btxt->blend_mode);

                if (btxt->multiligne == 0) {
                    __bmpFont_Print(btxt->font, btxt->text, btxt->pos.x, btxt->pos.y, btxt->size, btxt->align, btxt->angle);
                } else {
                    __bmpFont_PrintLines(btxt->font, btxt->text, btxt->pos.x, btxt->pos.y, btxt->size, btxt->align, btxt->angle);
                }
            }
        } break;
        case SET_TYPE_ANY: break;
    }

}

void        YAGL_API    MultiSet_SetColor (MultiSet* ms, unsigned char r, unsigned char g, unsigned char b, unsigned char a) // quad, spr, bmptext
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type == SET_TYPE_ANY) { return; }

    MultiSetElem* curr = NULL;
    switch (ms->type) {
        case SET_TYPE_QUAD:
            for (curr = ms->first; curr != NULL; curr = curr->next) {
                ((Quad*)curr->data)->color = YAGL_RGBA(r, g, b, a);
            }
        break;
        case SET_TYPE_SPRITE:
            for (curr = ms->first; curr != NULL; curr = curr->next) {
                ((Sprite*)curr->data)->color = YAGL_RGBA(r, g, b, a);
            }
        break;
        case SET_TYPE_PEMITTER:
            for (curr = ms->first; curr != NULL; curr = curr->next) {
                ((PEmitter*)curr->data)->col_r = r;
                ((PEmitter*)curr->data)->col_g = g;
                ((PEmitter*)curr->data)->col_b = b;
                ((PEmitter*)curr->data)->col_a = a;
            }
        break;
        case SET_TYPE_BMPTEXT:
            for (curr = ms->first; curr != NULL; curr = curr->next) {
                ((BmpText*)curr->data)->color = YAGL_RGBA(r, g, b, a);
            }
        break;
        case SET_TYPE_ANY: break;
    }
}

void        YAGL_API    MultiSet_SetColorEx (MultiSet* ms, YAGL_Color color) // quad, spr, bmptext
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type == SET_TYPE_ANY) { return; }

    MultiSetElem* curr = NULL;
    switch (ms->type) {
        case SET_TYPE_QUAD:
            for (curr = ms->first; curr != NULL; curr = curr->next) {
                ((Quad*)curr->data)->color = color;
            }
        break;
        case SET_TYPE_SPRITE:
            for (curr = ms->first; curr != NULL; curr = curr->next) {
                ((Sprite*)curr->data)->color = color;
            }
        break;
        case SET_TYPE_PEMITTER:
            for (curr = ms->first; curr != NULL; curr = curr->next) {
                ((PEmitter*)curr->data)->col_r = YAGL_RGBA_R(color);
                ((PEmitter*)curr->data)->col_g = YAGL_RGBA_G(color);
                ((PEmitter*)curr->data)->col_b = YAGL_RGBA_B(color);
                ((PEmitter*)curr->data)->col_a = YAGL_RGBA_A(color);
            }
        break;
        case SET_TYPE_BMPTEXT:
            for (curr = ms->first; curr != NULL; curr = curr->next) {
                ((BmpText*)curr->data)->color = color;
            }
        break;
        case SET_TYPE_ANY: break;
    }
}

void        YAGL_API    MultiSet_SetBlendMode (MultiSet* ms, eBLEND_MODE blend_mode)  // quad, spr, pemitter, bmptext
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type == SET_TYPE_ANY) { return; }

    MultiSetElem* curr = NULL;
    switch (ms->type) {
        case SET_TYPE_QUAD: {
            for (curr = ms->first; curr != NULL; curr = curr->next) {
                ((Quad*)curr->data)->blend_mode = blend_mode;
            }
        } break;
        case SET_TYPE_SPRITE: {
            for (curr = ms->first; curr != NULL; curr = curr->next) {
                ((Sprite*)curr->data)->blend_mode = blend_mode;
            }
        }  break;
        case SET_TYPE_PEMITTER: {
            for (curr = ms->first; curr != NULL; curr = curr->next) {
                ((PEmitter*)curr->data)->blend_mode = blend_mode;
            }
        } break;
        case SET_TYPE_BMPTEXT: {
            for (curr = ms->first; curr != NULL; curr = curr->next) {
                ((BmpText*)curr->data)->blend_mode = blend_mode;
            }
        } break;
        case SET_TYPE_ANY: break;
    }
}

void        YAGL_API    MultiSet_SetVisible (MultiSet* ms, int visible) // quad, spr, pemitter, bmptext
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type == SET_TYPE_ANY) { return; }

    MultiSetElem* curr = NULL;
    switch (ms->type) {
        case SET_TYPE_QUAD: {
            for (curr = ms->first; curr != NULL; curr = curr->next) {
                ((Quad*)curr->data)->visible = visible;
            }
        } break;
        case SET_TYPE_SPRITE: {
            for (curr = ms->first; curr != NULL; curr = curr->next) {
                ((Sprite*)curr->data)->visible = visible;
            }
        }  break;
        case SET_TYPE_PEMITTER: {
            for (curr = ms->first; curr != NULL; curr = curr->next) {
                ((PEmitter*)curr->data)->visible = visible;
            }
        } break;
        case SET_TYPE_BMPTEXT: {
            for (curr = ms->first; curr != NULL; curr = curr->next) {
                ((BmpText*)curr->data)->visible = visible;
            }
        } break;
        case SET_TYPE_ANY: break;
    }
}


/* Quad specific */
/* Sprite specific */
void        YAGL_API    MultiSet_SpriteDrawShape (MultiSet* ms)
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_SPRITE) { return; }

    MultiSetElem* curr = NULL;
    float x, y;
    Sprite* spr = NULL;

    for (curr = ms->first; curr != NULL; curr = curr->next) {
        spr = (Sprite*)curr->data;
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
}

void        YAGL_API    MultiSet_SpriteSetDynamic (MultiSet* ms, int dynamic)
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_SPRITE) { return; }

    MultiSetElem* curr = NULL;
    for (curr = ms->first; curr != NULL; curr = curr->next) {
        ((Sprite*)curr->data)->dynamic = dynamic;
    }
}

int         YAGL_API    MultiSet_SpriteCollide (MultiSet* ms, Sprite* spr, int force_check, int must_touch_all)
{
    MS_CHECK_RET(0)
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_SPRITE) { return 0; }

    MultiSetElem* current = ms->first;

    do {
        if ((force_check != 0 && __collision_check_mask_and_group((Sprite*)current->data, spr) && __collision_check_collision((Sprite*)current->data, spr)) ||
            (force_check == 0 && __collision_check_collision((Sprite*)current->data, spr))
            ) {
            if (must_touch_all == 0) { // si pas besoin de tout toucher, alors il suffit d'une seule collision pour retourner 1
                return 1;
            //} else {
            //    coll_count++; // s'il faut tout toucher, on compte le nombre de collision... plus besoin ...(*)
            }
        } else {
            if (must_touch_all != 0) { // si il faut tout toucher, alors une seule non-collision et on retourne 0
                return 0;
            }
        }
        // ---
        current = current->next;
    } while (current != NULL);

    // (*) il suffit d'arriver à la fin de la boucle pour être sur qu'ils se touchent tous
    /*if (coll_count == spr_set->count) {
        return 1;
    } else {
        return 0;
    }*/
    return 1;
}

void        YAGL_API    MultiSet_SpriteSetFlip (MultiSet* ms, int x, int y)
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_SPRITE) { return; }

    MultiSetElem* curr = NULL;
    for (curr = ms->first; curr != NULL; curr = curr->next) {
        if (x == 0) {
            ((Sprite*)curr->data)->flip.x = 1;
        } else {
            ((Sprite*)curr->data)->flip.x = -1;
        }
        if (y == 0) {
            ((Sprite*)curr->data)->flip.y = 1;
        } else {
            ((Sprite*)curr->data)->flip.y = -1;
        }
    }
}

// vel
void        YAGL_API    MultiSet_SpriteSetVel (MultiSet* ms, float x, float y)
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_SPRITE) { return; }

    MultiSetElem* curr = NULL;
    for (curr = ms->first; curr != NULL; curr = curr->next) {
        ((Sprite*)curr->data)->vel.x = x;
        ((Sprite*)curr->data)->vel.y = y;
    }
}

void        YAGL_API    MultiSet_SpriteSetVelLen (MultiSet* ms, float len)
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_SPRITE) { return; }

    MultiSetElem* curr = NULL;
    Sprite* spr = NULL;

    for (curr = ms->first; curr != NULL; curr = curr->next) {
        spr = ((Sprite*)curr->data);
        __polar_2_cartesian(len, spr->angle, &spr->vel.x, &spr->vel.y);
    }
}

void        YAGL_API    MultiSet_SpriteSetVelAngle (MultiSet* ms, float angle)
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_SPRITE) { return; }

    MultiSetElem* curr = NULL;
    Sprite* spr = NULL;

    for (curr = ms->first; curr != NULL; curr = curr->next) {
        spr = ((Sprite*)curr->data);
        __polar_2_cartesian(__vect_len(spr->vel.x, spr->vel.y), angle, &spr->vel.x, &spr->vel.y);
    }
}

void        YAGL_API    MultiSet_SpriteSetVelEx (MultiSet* ms, float len, float angle)
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_SPRITE) { return; }

    MultiSetElem* curr = NULL;
    Sprite* spr = NULL;

    for (curr = ms->first; curr != NULL; curr = curr->next) {
        spr = ((Sprite*)curr->data);
        __polar_2_cartesian(len, angle, &spr->vel.x, &spr->vel.y);
    }
}

// velmax
void        YAGL_API    MultiSet_SpriteSetVelMax (MultiSet* ms, float vel_max)
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_SPRITE) { return; }

    MultiSetElem* curr = NULL;
    for (curr = ms->first; curr != NULL; curr = curr->next) {
        ((Sprite*)curr->data)->vel_max = vel_max;
    }
}

// accel
void        YAGL_API    MultiSet_SpriteSetAccel (MultiSet* ms, float x, float y)
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_SPRITE) { return; }

    MultiSetElem* curr = NULL;
    for (curr = ms->first; curr != NULL; curr = curr->next) {
        ((Sprite*)curr->data)->accel.x = x;
        ((Sprite*)curr->data)->accel.y = y;
    }
}

void        YAGL_API    MultiSet_SpriteSetAccelLen (MultiSet* ms, float len)
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_SPRITE) { return; }

    MultiSetElem* curr = NULL;
    Sprite* spr = NULL;

    for (curr = ms->first; curr != NULL; curr = curr->next) {
        spr = ((Sprite*)curr->data);
        __polar_2_cartesian(len, spr->angle, &spr->accel.x, &spr->accel.y);
    }
}

void        YAGL_API    MultiSet_SpriteSetAccelAngle (MultiSet* ms, float angle)
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_SPRITE) { return; }

    MultiSetElem* curr = NULL;
    Sprite* spr = NULL;

    for (curr = ms->first; curr != NULL; curr = curr->next) {
        spr = ((Sprite*)curr->data);
        __polar_2_cartesian(__vect_len(spr->accel.x, spr->accel.y), angle, &spr->accel.x, &spr->accel.y);
    }
}

void        YAGL_API    MultiSet_SpriteSetAccelEx (MultiSet* ms, float len, float angle)
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_SPRITE) { return; }

    MultiSetElem* curr = NULL;
    Sprite* spr = NULL;

    for (curr = ms->first; curr != NULL; curr = curr->next) {
        spr = ((Sprite*)curr->data);
        __polar_2_cartesian(len, angle, &spr->accel.x, &spr->accel.y);
    }
}

// innertia
void        YAGL_API    MultiSet_SpriteSetInnertia (MultiSet* ms, float innertia)
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_SPRITE) { return; }

    MultiSetElem* curr = NULL;
    for (curr = ms->first; curr != NULL; curr = curr->next) {
        ((Sprite*)curr->data)->innertia = innertia;
    }
}

// angles
void        YAGL_API    MultiSet_SpriteSetAVel (MultiSet* ms, float avel)
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_SPRITE) { return; }

    MultiSetElem* curr = NULL;
    for (curr = ms->first; curr != NULL; curr = curr->next) {
        ((Sprite*)curr->data)->a_vel = avel;
    }
}

void        YAGL_API    MultiSet_SpriteSetAVelMax (MultiSet* ms, float avel_max)
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_SPRITE) { return; }

    MultiSetElem* curr = NULL;
    for (curr = ms->first; curr != NULL; curr = curr->next) {
        ((Sprite*)curr->data)->a_vel_max = avel_max;
    }
}

void        YAGL_API    MultiSet_SpriteSetAAccel (MultiSet* ms, float aaccel)
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_SPRITE) { return; }

    MultiSetElem* curr = NULL;
    for (curr = ms->first; curr != NULL; curr = curr->next) {
        ((Sprite*)curr->data)->a_accel = aaccel;
    }
}

void        YAGL_API    MultiSet_SpriteSetAInnertia (MultiSet* ms, float ainnertia)
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_SPRITE) { return; }

    MultiSetElem* curr = NULL;
    for (curr = ms->first; curr != NULL; curr = curr->next) {
        ((Sprite*)curr->data)->a_innertia = ainnertia;
    }
}

/* PEmitter specific */
void        YAGL_API    MultiSet_PEmitterSetActive (MultiSet* ms, int active)
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_PEMITTER) { return; }

    MultiSetElem* current = NULL;
    for (current = ms->first; current != NULL; current = current->next) {
        ((PEmitter*)current->data)->active = active;
    }
}

void        YAGL_API    MultiSet_PEmitterEmitte (MultiSet* ms, unsigned int nbr)
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_PEMITTER) { return; }

    MultiSetElem* current = NULL;
    for (current = ms->first; current != NULL; current = current->next) {
        PEmitter_Emitte(current->data, nbr);
    }
}

void        YAGL_API    MultiSet_PEmitterEmitteAt (MultiSet* ms, float x, float y, unsigned int nbr)
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_PEMITTER) { return; }

    MultiSetElem* current = NULL;
    for (current = ms->first; current != NULL; current = current->next) {
        PEmitter_EmitteAt(current->data, x, y, nbr);
    }
}


/* BmpText specific */
void        YAGL_API    MultiSet_BmpTextSetText (MultiSet* ms, const char text[])
{
    MS_CHECK
    if (ms->count == 0 || ms->first == NULL || ms->type != SET_TYPE_BMPTEXT) { return; }

    MultiSetElem* current = NULL;
    for (current = ms->first; current != NULL; current = current->next) {
        BmpText_SetText(current->data, text);
    }
}

/**
    @}
*/
