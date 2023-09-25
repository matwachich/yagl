/**
    \addtogroup 110_sprite_set
    @{
*/

#include "all.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline void __sprite_set_del (SpriteSet* spr_set, Sprite* spr, int destroy)
{
    if (spr_set->count == 0 || spr_set->first == NULL) { return; }

    SpriteSetElem* curr = spr_set->first;
    SpriteSetElem* befor = NULL;

    do {
        if (curr->spr == spr) {
			if (befor == NULL) {
				spr_set->first = curr->next;
			} else {
				befor->next = curr->next;
			}

			if (destroy) {
                Sprite_Destroy(spr);
			}

			free(curr);
			spr_set->count--;

			return;
		}
		// ---
		befor = curr;
		curr = curr->next;
    } while (curr != NULL);

    spr_set->first = NULL;
}

inline void __sprite_set_del_all (SpriteSet* spr_set, int destroy)
{
    if (spr_set->count == 0 || spr_set->first == NULL) { return; }

    SpriteSetElem* current = spr_set->first;
    SpriteSetElem* tmp = NULL;

    do {
        if (destroy) { Sprite_Destroy(current->spr); }

        tmp = current->next;
        free(current);
        current = tmp;

    } while (current != NULL);

    spr_set->count = 0;
}

/* ------------------------------------------------------------------------- **/
/* Public functions **/

/*
Function: SpriteSet_Create

Parameters:

Return:

*/
SpriteSet*  YAGL_API    SpriteSet_Create ()
{
    SpriteSet* spr_set = mem_alloc(sizeof(SpriteSet), PTR_SPRITE_SET);
    if (spr_set == NULL) { __DEBUG__("Unable to create Sprite Set! (Out of memory)", 2); }

    spr_set->first = NULL;
    spr_set->count = 0;

    return spr_set;
}


/*
Function: SpriteSet_IsSpriteSet

Parameters:

Return:

*/
int   YAGL_API    SpriteSet_IsSpriteSet (SpriteSet* spr_set)
{
    return mem_exists(spr_set, PTR_SPRITE_SET);
}


/*
Function: SpriteSet_Destroy

Parameters:

Return:

*/
int   YAGL_API    SpriteSet_Destroy (SpriteSet* spr_set, int destroy)
{
    if (mem_exists(spr_set, PTR_SPRITE_SET) == 0) { return 0; }

    __sprite_set_del_all(spr_set, destroy);
    return mem_free(spr_set, PTR_SPRITE_SET);
}


/*
Function: SpriteSet_Add

Parameters:

Return:

*/
void        YAGL_API    SpriteSet_Add (SpriteSet* spr_set, Sprite* spr)
{
    if (mem_exists(spr_set, PTR_SPRITE_SET) == 0 || mem_exists(spr, PTR_SPRITE) == 0) { return; }

    SpriteSetElem* elem = malloc(sizeof(SpriteSetElem));
    if (elem == NULL) { __DEBUG__("Unable to add Sprite to the Sprite Set! (Out of memory)", 2); }

    __sprite_set_del(spr_set, spr, 0);

    elem->spr = spr;
    elem->next = spr_set->first;
    spr_set->first = elem;

    spr_set->count += 1;
}


/*
Function: SpriteSet_Del

Parameters:

Return:

*/
int         YAGL_API    SpriteSet_Exists (SpriteSet* spr_set, Sprite* spr)
{
    if (mem_exists(spr_set, PTR_SPRITE_SET) == 0 || mem_exists(spr, PTR_SPRITE) == 0) { return -1; }

    if (spr_set->count == 0 || spr_set->first == NULL) { return 0; }

    SpriteSetElem* current = spr_set->first;

    do {
        if (current->spr == spr) { return 1; }

        current = current->next;
    } while (current != NULL);

    return 0;
}


/*
Function: SpriteSet_Del

Parameters:

Return:

*/
void        YAGL_API    SpriteSet_Del (SpriteSet* spr_set, Sprite* spr, int destroy)
{
    if (mem_exists(spr_set, PTR_SPRITE_SET) == 0) { return; }

    __sprite_set_del(spr_set, spr, destroy);
}


/*
Function: SpriteSet_DelAll

Parameters:

Return:

*/
void        YAGL_API    SpriteSet_DelAll (SpriteSet* spr_set, int destroy)
{
    if (mem_exists(spr_set, PTR_SPRITE_SET) == 0) { return; }

    __sprite_set_del_all(spr_set, destroy);
}


/*
Function: SpriteSet_SetColor

Parameters:

Return:

*/
void        YAGL_API    SpriteSet_SetColor (SpriteSet* spr_set, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    if (mem_exists(spr_set, PTR_SPRITE_SET) == 0) { return; }

    if (spr_set->count == 0 || spr_set->first == NULL) { return; }

    SpriteSetElem* current = spr_set->first;

    do {
        current->spr->color = YAGL_RGBA(r, g, b, a);

        current = current->next;
    } while (current != NULL);
}

/*
Function: SpriteSet_SetColorEx

Parameters:

Return:

*/
void        YAGL_API    SpriteSet_SetColorEx (SpriteSet* spr_set, YAGL_Color color)
{
    if (mem_exists(spr_set, PTR_SPRITE_SET) == 0) { return; }

    if (spr_set->count == 0 || spr_set->first == NULL) { return; }

    SpriteSetElem* current = spr_set->first;

    do {
        current->spr->color = color;

        current = current->next;
    } while (current != NULL);
}

/*
Function: SpriteSet_SetBlendMode

Parameters:

Return:

*/
void        YAGL_API    SpriteSet_SetBlendMode (SpriteSet* spr_set, eBLEND_MODE blend_mode)
{
    if (mem_exists(spr_set, PTR_SPRITE_SET) == 0) { return; }

    if (spr_set->count == 0 || spr_set->first == NULL) { return; }

    SpriteSetElem* current = spr_set->first;

    do {
        current->spr->blend_mode = blend_mode;

        current = current->next;
    } while (current != NULL);
}

/*
Function: SpriteSet_SetVisible

Parameters:

Return:

*/
void        YAGL_API    SpriteSet_SetVisible (SpriteSet* spr_set, int visible)
{
    if (mem_exists(spr_set, PTR_SPRITE_SET) == 0) { return; }

    if (spr_set->count == 0 || spr_set->first == NULL) { return; }

    SpriteSetElem* current = spr_set->first;

    do {
        current->spr->visible = visible;

        current = current->next;
    } while (current != NULL);
}

/*
Function: SpriteSet_SetDynamic

Parameters:

Return:

*/
void        YAGL_API    SpriteSet_SetDynamic (SpriteSet* spr_set, int dynamic)
{
    if (mem_exists(spr_set, PTR_SPRITE_SET) == 0) { return; }

    if (spr_set->count == 0 || spr_set->first == NULL) { return; }

    SpriteSetElem* current = spr_set->first;

    do {
        current->spr->dynamic = dynamic;

        current = current->next;
    } while (current != NULL);
}


/*
Function: SpriteSet_Collide

Parameters:

Return:

*/
int         YAGL_API    SpriteSet_Collide (SpriteSet* spr_set, Sprite* spr, int force_check, int must_touch_all)
{
    if (mem_exists(spr_set, PTR_SPRITE_SET) == 0 || mem_exists(spr, PTR_SPRITE) == 0) { return 0; }

    if (spr_set->count == 0 || spr_set->first == NULL) { return 0; }

    SpriteSetElem* current = spr_set->first;

    do {
        if ((force_check != 0 && __collision_check_mask_and_group(current->spr, spr) && __collision_check_collision(current->spr, spr)) ||
            (force_check == 0 && __collision_check_collision(current->spr, spr))
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


/*
Function: SpriteSet_Draw

Parameters:

Return:

*/
void        YAGL_API    SpriteSet_Draw (SpriteSet* spr_set)
{
    if (mem_exists(spr_set, PTR_SPRITE_SET) == 0) { return; }

    if (spr_set->count == 0 || spr_set->first == NULL) { return; }

    SpriteSetElem* current = spr_set->first;

    do {
        __sprite_calc_dynamics(current->spr);
        __sprite_calc_anim(current->spr);

        if (current->spr->visible != 0) {
            __sprite_draw_quad(current->spr->tex, current->spr->blend_mode, current->spr->pos, current->spr->size, current->spr->center, current->spr->flip, current->spr->angle, current->spr->color, current->spr->tex_rect_1, current->spr->tex_rect_2, current->spr->tex_rect_3, current->spr->tex_rect_4);
        }
        // ---
        current = current->next;
    } while (current != NULL);
}

/*
Function: SpriteSet_DrawShapes

Parameters:

Return:

*/
void        YAGL_API    SpriteSet_DrawShapes (SpriteSet* spr_set)
{
    if (mem_exists(spr_set, PTR_SPRITE_SET) == 0) { return; }

    if (spr_set->count == 0 || spr_set->first == NULL) { return; }

    SpriteSetElem* current = spr_set->first;
    float x, y;

    do {
        if (current->spr->shape_type != SHAPE_NONE) {
            __sprite_get_point(current->spr, current->spr->shape_pos.x, current->spr->shape_pos.y, &x, &y);

            switch (current->spr->shape_type)
            {
                case SHAPE_POINT:
                    Draw_Point(x, y);
                break;
                case SHAPE_CIRCLE:
                    Draw_Ellipse(x, y, current->spr->shape_size.x, current->spr->shape_size.x, 0, 30);
                break;
                case SHAPE_RECT:
                    Draw_RectCenter(x, y, current->spr->shape_size.x, current->spr->shape_size.y, 0);
                break;
                case SHAPE_NONE: break;
            }
        }
        // ---
        current = current->next;
    } while (current != NULL);
}

/*
Function: SpriteSet_Count

Parameters:

Return:

*/
int         YAGL_API    SpriteSet_Count (SpriteSet* spr_set)
{
    if (mem_exists(spr_set, PTR_SPRITE_SET) == 0) { return -1; }

    return spr_set->count;
}


/*
Function: SpriteSet_GetAll

Parameters:

Return:

*/
int         YAGL_API    SpriteSet_GetAll (SpriteSet* spr_set, Sprite* spr[], int size)
{
    if (mem_exists(spr_set, PTR_SPRITE_SET) == 0) { return -1; }

    if (spr_set->count == 0 || spr_set->first == NULL) { return 0; }

    if (size > spr_set->count) { size = spr_set->count; }

    int i = 0;
    SpriteSetElem* current = spr_set->first;
    do {
        spr[i] = current->spr;
        // ---
        i++;
        current = current->next;
    } while (current != NULL && i < size);

    return i;
}

/*
Function: SpriteSet_Enum

Parameters:

Return:

*/
int         YAGL_API    SpriteSet_Iterate (SpriteSet* spr_set, YAGLSpriteSetIterateProc enum_proc, void* user_data)
{
    if (mem_exists(spr_set, PTR_SPRITE_SET) == 0) { return -1; }

    if (spr_set->count == 0 || spr_set->first == NULL) { return 0; }

    if (enum_proc == NULL) { return 0; }

    SpriteSetElem* current = spr_set->first;
    SpriteSetElem* befor = NULL;
    SpriteSetElem* to_free = NULL;

    int deleted = 0;

    do {
        switch (enum_proc(spr_set, current->spr, user_data)) {
            default: // do nothing
            break;
            case 1: // remove sprite from spriteSet
                if (befor == NULL) {
                    spr_set->first = current->next;
                } else {
                    befor->next = current->next;
                }
                to_free = current;
            break;
            case 2: // remove sprite from spriteSet and destroy it (the sprite)
                if (befor == NULL) {
                    spr_set->first = current->next;
                } else {
                    befor->next = current->next;
                }
                Sprite_Destroy(current->spr);
                to_free = current;
            break;
        }
        // ---
        if (to_free != NULL) {
            free(to_free);
            to_free = NULL;

            spr_set->count--;
            deleted++;

            current = current->next;
        } else {
            befor = current;
            current = current->next;
        }
    } while (current != NULL);

    return deleted;
}

/**
    @}
*/
