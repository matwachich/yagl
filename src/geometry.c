/**
    \addtogroup 170_geo
    @{
*/

#include <math.h>

#include "all.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- **/
/* Public functions **/

/** \brief Return the distance between 2 points
 *
 * \param x1[in] X-pos 1
 * \param y1[in] Y-pos 1
 * \param x2[in] X-pos 2
 * \param y2[in] Y-pos 2
 *
 * \return Distance between the points (x1, y1) and (x2, y2)
 */
float  YAGL_API    Geo_PtoP_Dist (int x1, int y1, int x2, int y2)
{
    return __vect_len((float)x2 - x1, (float)y2 - y1);
}

/** \brief Return the angle between 2 points
 *
 * It's the angle of the vector from (x1,y1) to (x2,y2)
 *
 * \param x1[in] X-pos 1
 * \param y1[in] Y-pos 1
 * \param x2[in] X-pos 2
 * \param y2[in] Y-pos 2
 *
 * \return Angle in degrees
 */
float  YAGL_API    Geo_PtoP_Angle (int x1, int y1, int x2, int y2)
{
    float angle, len;
    __cartesian_2_polar(x2 - x1, y2 - y1, &angle, &len);
    return angle;
}

/** \brief Return the vector between (x1,y1) to (x2,y2)
 *
 * \param x1[in] X-pos 1
 * \param y1[in] Y-pos 1
 * \param x2[in] X-pos 2
 * \param y2[in] Y-pos 2
 * \param len[in] Length of the vector. 0 for the distance between (x1,y1) and (x2,y2)
 * \param v_x[out] Vector X
 * \param v_y[out] Vector Y
 */
void    YAGL_API    Geo_PtoP_Vect (int x1, int y1, int x2, int y2, float len, float* v_x, float* v_y)
{
    *v_x = x2 - x1;
	*v_y = y2 - y1;
	if (len != 0 && (*v_x != 0 || *v_y != 0)) {
		float l = __vect_len(*v_x, *v_y);
		*v_x = (*v_x/l) * fabs(len);
		*v_y = (*v_y/l) * fabs(len);
	}
}

/** \brief Return the distance between a Sprite and a point (x,y)
 *
 * \param spr[in] Sprite (see Sprite_Create())
 * \param x[in] X-pos
 * \param y[in] Y-pos
 *
 * \return Distance
 */
float  YAGL_API    Geo_SprtoP_Dist (Sprite* spr, int x, int y)
{
    return __vect_len((float)x - spr->pos.x, (float)y - spr->pos.y);
}

/** \brief Return the angle between a Sprite and a point
 *
 * \param spr[in] Sprite (Sprite_Create())
 * \param x[in] X-pos
 * \param y[in] Y-pos
 *
 * \return Angle (in degrees)
 */
float  YAGL_API    Geo_SprtoP_Angle (Sprite* spr, int x, int y)
{
    float angle, len;
    __cartesian_2_polar(x - spr->pos.x, y - spr->pos.y, &angle, &len);
    return angle;
}

/** \brief
 *
 * \param
 * \param
 * \param
 *
 * \return
 */
float  YAGL_API    Geo_SprtoP_AngleDiff (Sprite* spr, int x, int y)
{
    float angleDiff = Geo_SprtoP_Angle(spr, x, y);
	float angleCurr = spr->angle;
	if (angleCurr == 0) { angleCurr = 360; }
	// ---
	float angleInverse = angleCurr + 180;
	__reduce_angle(&angleInverse);
	// ---
	float result = 0;
	if (angleCurr >= 180) {
		if (angleDiff < angleCurr && angleDiff > angleInverse) { // -
			result = -1 * fabs(angleCurr - angleDiff);
		} else { // +
			if (angleDiff > angleCurr) {
				result = fabs(angleDiff - angleCurr);
			} else {
				result = fabs(fabs(360 - angleCurr) + angleDiff);
			}
		}
	} else {
		if (angleDiff > angleCurr && angleDiff < angleInverse) { // +
			result = fabs(angleDiff - angleCurr);
		} else { // -
			if (angleDiff < angleCurr) {
				result = -1 * fabs(angleCurr - angleDiff);
			} else if (angleDiff > angleInverse && angleDiff < 360) {
				result = -1 * fabs(angleCurr + fabs(360 - angleDiff));
			}
		}
	}
	// ---
	// NE JAMAIS appliquer ici _ReduceAngle(), car elle retourne toujour un angle (+)
	if (result == 360) { result = 0; } // cas spécial ou l'algoritme se trompe en retournant 360
	// ---
	return result;
}

/** \brief
 *
 * \param
 * \param
 * \param
 * \param
 * \param
 */
void    YAGL_API    Geo_SprtoP_Vect (Sprite* spr, int x, int y, float len, float* v_x, float* v_y)
{
    *v_x = x - spr->pos.x;
	*v_y = y - spr->pos.y;
	if (len > 0 && (*v_x != 0 || *v_y != 0)) {
		float l = __vect_len(*v_x, *v_y);
		*v_x = (*v_x/l) * len;
		*v_y = (*v_y/l) * len;
	}
}

/** \brief
 *
 * \param
 * \param
 *
 * \return
 */
float  YAGL_API    Geo_SprtoSpr_Dist (Sprite* spr1, Sprite* spr2)
{
    return __vect_len(spr2->pos.x - spr1->pos.x, spr2->pos.y - spr1->pos.y);
}

/** \brief
 *
 * \param
 * \param
 *
 * \return
 */
float  YAGL_API    Geo_SprtoSpr_Angle (Sprite* spr1, Sprite* spr2)
{
    float angle, len;
    __cartesian_2_polar(spr2->pos.x - spr1->pos.x, spr2->pos.y - spr1->pos.y, &angle, &len);
    return angle;
}

/** \brief
 *
 * \param
 * \param
 *
 * \return
 */
float  YAGL_API    Geo_SprtoSpr_AngleDiff (Sprite* spr1, Sprite* spr2)
{
    float angleDiff = Geo_SprtoSpr_Angle(spr1, spr2);
	float angleCurr = spr1->angle;
	if (angleCurr == 0) { angleCurr = 360; }
	// ---
	float angleInverse = angleCurr + 180;
	__reduce_angle(&angleInverse);
	// ---
	float result = 0;
	if (angleCurr >= 180) {
		if (angleDiff < angleCurr && angleDiff > angleInverse) { // -
			result = -1 * fabs(angleCurr - angleDiff);
		} else { // +
			if (angleDiff > angleCurr) {
				result = fabs(angleDiff - angleCurr);
			} else {
				result = fabs(fabs(360 - angleCurr) + angleDiff);
			}
		}
	} else {
		if (angleDiff > angleCurr && angleDiff < angleInverse) { // +
			result = fabs(angleDiff - angleCurr);
		} else { // -
			if (angleDiff < angleCurr) {
				result = -1 * fabs(angleCurr - angleDiff);
			} else if (angleDiff > angleInverse && angleDiff < 360) {
				result = -1 * fabs(angleCurr + fabs(360 - angleDiff));
			}
		}
	}
	// ---
	// NE JAMAIS appliquer ici _ReduceAngle(), car elle retourne toujour un angle (+)
	if (result == 360) { result = 0; } // cas spécial ou l'algoritme se trompe en retournant 360
	// ---
	return result;
}

/** \brief
 *
 * \param
 * \param
 * \param
 * \param
 * \param
 */
void    YAGL_API    Geo_SprtoSpr_Vect (Sprite* spr1, Sprite* spr2, float len, float* v_x, float* v_y)
{
    *v_x = spr2->pos.x - spr1->pos.x;
	*v_y = spr2->pos.y - spr1->pos.y;
	if (len > 0 && (*v_x != 0 || *v_y != 0)) {
		float l = __vect_len(*v_x, *v_y);
		*v_x = (*v_x/l) * len;
		*v_y = (*v_y/l) * len;
	}
}

/** \brief
 *
 * \param
 * \param
 * \param
 * \param
 */
void    YAGL_API    Geo_PolarToCartesian (float angle, float len, float* x, float* y)
{
    __polar_2_cartesian(len, angle, x, y);
}

/** \brief
 *
 * \param
 * \param
 * \param
 * \param
 */
void    YAGL_API    Geo_CartesianToPolar (float x, float y, float* angle, float* len)
{
    __cartesian_2_polar(x, y, angle, len);
}

/**
    @}
*/
