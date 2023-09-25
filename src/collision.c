/**
    \addtogroup 130_collision
    @{
*/

#include <math.h>

#include "all.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

// Récupère les Sprites "collisionnables" du Set et les mets dans collision_array
inline void __collision_array_update ()
{
    _engin_->collision_array_size = Set_GetArray(_engin_->collision_set, &_engin_->collision_array);
    if (_engin_->collision_array_size == -1) { _engin_->collision_array_size = 0; }
    _engin_->coll_array_update = 0;
}

inline void __collision_sprite_get_pos(Sprite* spr, float* x, float* y)
{
    __sprite_get_point(spr, spr->shape_pos.x, spr->shape_pos.y, x, y);
}

inline void __collision_rect_correct(float* x, float* y, float rx, float ry, float rw, float rh)
{
    *x = rx - (rw/2); *y = ry - (rh/2);
}

// Collision detection
// -------------------
inline int __collision_Point_Point(Sprite* spr1, Sprite* spr2)
{
    float x1, y1, x2, y2;
    __collision_sprite_get_pos(spr1, &x1, &y1);
    __collision_sprite_get_pos(spr2, &x2, &y2);
    if (x1 == x2 && y1 == y2) { return 1; } else { return 0; }
}

inline int __collision_Point_Circle(Sprite* spr1, Sprite* spr2)
{
    float x1, y1, x2, y2;
    __collision_sprite_get_pos(spr1, &x1, &y1);
    __collision_sprite_get_pos(spr2, &x2, &y2);
    if (sqrt(((x2 - x1)*(x2 - x1)) + ((y2 - y1)*(y2 - y1))) <= spr2->shape_size.x) { return 1; } else { return 0; }
}

inline int __collision_Point_Rect(Sprite* spr1, Sprite* spr2)
{
    float x1, y1, x2, y2;
    __collision_sprite_get_pos(spr1, &x1, &y1);
    __collision_sprite_get_pos(spr2, &x2, &y2);
    __collision_rect_correct(&x2, &y2, x2, y2, spr2->shape_size.x, spr2->shape_size.y);
    if (x1 >= x2 && x1 <= x2 + spr2->shape_size.x && y1 >= y2 && y1 <= y2 + spr2->shape_size.y) { return 1; } else { return 0; }
}

inline int __collision_Circle_Circle(Sprite* spr1, Sprite* spr2)
{
    float x1, y1, x2, y2;
    __collision_sprite_get_pos(spr1, &x1, &y1);
    __collision_sprite_get_pos(spr2, &x2, &y2);
    if (sqrt(((x2 - x1)*(x2 - x1)) + ((y2 - y1)*(y2 - y1))) <= spr1->shape_size.x + spr2->shape_size.x) { return 1; } else { return 0; }
}

inline int __collision_Circle_Rect(Sprite* spr1, Sprite* spr2)
{
    float x1, y1, x2, y2, TestX, TestY;
    __collision_sprite_get_pos(spr1, &x1, &y1);
    __collision_sprite_get_pos(spr2, &x2, &y2);
    __collision_rect_correct(&x2, &y2, x2, y2, spr2->shape_size.x, spr2->shape_size.y);
    TestX = x1; TestY = y1;

    if (TestX < x2) { TestX = x2; }
    if (TestX > x2 + spr2->shape_size.x) { TestX = x2 + spr2->shape_size.x; }
    if (TestY < y2) { TestY = y2; }
    if (TestY > y2 + spr2->shape_size.y) { TestY = y2 + spr2->shape_size.y; }

    if (((x1-TestX)*(x1-TestX)+(y1-TestY)*(y1-TestY)) < spr1->shape_size.x*spr1->shape_size.x) { return 1; } else { return 0; }
}

inline int __collision_Rect_Rect(Sprite* spr1, Sprite* spr2)
{
    float halfW1, halfH1, halfW2, halfH2;
	halfW1 = spr1->shape_size.x / 2;
	halfH1 = spr1->shape_size.y / 2;
	halfW2 = spr2->shape_size.x / 2;
	halfH2 = spr2->shape_size.y / 2;

	float x1, y1, x2, y2;
	__collision_sprite_get_pos(spr1, &x1, &y1);
	__collision_sprite_get_pos(spr2, &x2, &y2);
	__collision_rect_correct(&x1, &y1, x1, y1, spr1->shape_size.x, spr1->shape_size.y);
	__collision_rect_correct(&x2, &y2, x2, y2, spr2->shape_size.x, spr2->shape_size.y);

	float center1X, center1Y, center2X, center2Y;
	center1X = x1 + halfW1;
	center1Y = y1 + halfH1;
	center2X = x2 + halfW2;
	center2Y = y2 + halfH2;

	float distX, distY;
	distX = fabs(center1X - center2X);
	distY = fabs(center1Y - center2Y);

	if (distX <= halfW1 + halfW2 && distY <= halfH1 + halfH2) { return 1; } else { return 0; }
}

// ----------------------------------------------------------------------------

inline int __collision_check_mask_and_group (Sprite* spr1, Sprite* spr2)
{
    if (spr1->collision_group != 0 && spr2->collision_group != 0 && spr1->collision_group == spr2->collision_group) { return 0; }
    if (spr1->collision_mask != 0 && spr2->collision_mask != 0 && !(spr1->collision_mask & spr2->collision_mask)) { return 0; }
    return 1;
}

inline int __collision_check_collision (Sprite* spr1, Sprite* spr2)
{
    int result = 0;

    switch (spr1->shape_type)
    {
        case SHAPE_POINT:
			switch (spr2->shape_type)
			{
			    case SHAPE_POINT:
					result = __collision_Point_Point(spr1, spr2);
                break;
				case SHAPE_CIRCLE:
					result = __collision_Point_Circle(spr1, spr2);
                break;
				case SHAPE_RECT:
					result = __collision_Point_Rect(spr1, spr2);
                break;
                case SHAPE_NONE: break;
			}
        break;
		case SHAPE_CIRCLE:
			switch (spr2->shape_type)
			{
			    case SHAPE_POINT:
					result = __collision_Point_Circle(spr2, spr1);
                break;
				case SHAPE_CIRCLE:
					result = __collision_Circle_Circle(spr1, spr2);
                break;
				case SHAPE_RECT:
					result = __collision_Circle_Rect(spr1, spr2);
                break;
                case SHAPE_NONE: break;
			}
        break;
		case SHAPE_RECT:
			switch (spr2->shape_type)
			{
			    case SHAPE_POINT:
					result = __collision_Point_Rect(spr2, spr1);
                break;
				case SHAPE_CIRCLE:
					result = __collision_Circle_Rect(spr2, spr1);
                break;
				case SHAPE_RECT:
					result = __collision_Rect_Rect(spr1, spr2);
                break;
                case SHAPE_NONE: break;
			}
        break;
        case SHAPE_NONE: break;
    }

    return result;
}

#ifdef YAGL_ADVANCED_COLLISIONS
inline void __collision_couple_add (SpriteCouple* spr_cpl, Sprite* spr1, Sprite* spr2)
{

}

inline SpriteCouple* __collision_couple_exists (Sprite* spr1, Sprite* spr2)
{

}

inline void __collision_couple_del (SpriteCouple* spr_cpl)
{

}
#endif

/* ------------------------------------------------------------------------- **/
/* Public functions **/

/*
Function: Collision_SetCallback

Parameters:

Return:

*/
void    YAGL_API    Collision_SetCallback (YAGLCollisionProc proc)
{
    _engin_->collision_proc = proc;
}

/*
Function: Collision_Process

Parameters:

Return:

*/
void    YAGL_API    Collision_Process ()
{
    if (_engin_->collision_proc == NULL) { return; }

    if (_engin_->coll_array_update != 0) {
        __collision_array_update();
    }

    #ifdef YAGL_ADVANCED_COLLISIONS
    SpriteCouple* temp = NULL;
    #endif

    int i, j;
    for (i = _engin_->collision_array_size - 1; i >= 0; i--) {
        for (j = i - 1; j >= 0; j--) {
            if (i != j &&
                __collision_check_mask_and_group(_engin_->collision_array[i], _engin_->collision_array[j]) == 1 &&
                __collision_check_collision(_engin_->collision_array[i], _engin_->collision_array[j]) == 1
                ) {
                    _engin_->collision_proc(_engin_->collision_array[i], _engin_->collision_array[j]);
            }
        }
    }
}

/*
Function: Collision_SetAutoProcess

Parameters:

Return:

*/
void    YAGL_API    Collision_SetAutoProcess(int status)
{
    _engin_->collision_autoprocess = status;
}

/*
Function: Collision_Check

Parameters:

Return:

*/
int     YAGL_API    Collision_Check (Sprite* spr1, Sprite* spr2, int force_check)
{
    if (mem_exists(spr1, PTR_SPRITE) == 0 || mem_exists(spr2, PTR_SPRITE) == 0) { return 0; }
    if (spr1 == spr2 || spr1->shape_type == SHAPE_NONE || spr2->shape_type == SHAPE_NONE) { return 0; }

    if (!force_check && __collision_check_mask_and_group(spr1, spr2) == 0) {
        return 0;
    }

    return __collision_check_collision(spr1, spr2);
}

/**
    @}
*/
