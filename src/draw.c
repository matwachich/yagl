/**
    \addtogroup 160_draw
    @{
*/

#include <math.h>

#include "all.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline void __draw_bind_glow()
{
    if (_engin_->current_texture != _engin_->glow_texture) {
		glBindTexture(GL_TEXTURE_2D, _engin_->glow_texture);
		_engin_->current_texture = _engin_->glow_texture;
    }
}

/* ------------------------------------------------------------------------- **/
/* Public functions **/


/** \brief Set drawing parameters: color, blend mode, size (lines, points), glow (on/off)
 *
 * \param color[in]
 * \param blend_mode[in]
 * \param size[in]
 * \param glow[in]
 */
void    YAGL_API    Draw_SetParams (YAGL_Color color, eBLEND_MODE blend_mode, int size, int glow)
{
    glColor4ubv((GLubyte*)&color);
    _engin_->draw_color = color;

    __set_blend_mode(blend_mode);
    _engin_->draw_blend_mode = blend_mode;

    _engin_->draw_size = size;
	glPointSize(size);
	glLineWidth(size);

	_engin_->draw_glow_mode = glow;
}

/*
Function: Draw_SetColor

Parameters:

Return:

*/
void    YAGL_API    Draw_SetColor (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
    glColor4ub(red, green, blue, alpha);
	_engin_->draw_color = YAGL_RGBA(red, green, blue, alpha);
}


/*
Function: Draw_SetColorEx

Parameters:

Return:

*/
void    YAGL_API    Draw_SetColorEx (YAGL_Color color)
{
    glColor4ubv((GLubyte*)&color);
    _engin_->draw_color = color;
}


/*
Function: Draw_SetBlendMode

Parameters:

Return:

*/
void    YAGL_API    Draw_SetBlendMode (eBLEND_MODE blend_mode)
{
    __set_blend_mode(blend_mode);
    _engin_->draw_blend_mode = blend_mode;
}

/*
Function: Draw_SetGlow

Parameters:

Return:

*/
void    YAGL_API    Draw_SetGlow (int status)
{
    _engin_->draw_glow_mode = status;
}

/*
Function: Draw_SetSize

Parameters:

Return:

*/
void    YAGL_API    Draw_SetSize (int size)
{
    _engin_->draw_size = size;
	glPointSize(size);
	glLineWidth(size);
}

/*
Function: Draw_Point

Parameters:

Return:

*/
void    YAGL_API    Draw_Point (int x, int y)
{
    glLoadIdentity();
	glColor4ubv((GLubyte*)&_engin_->draw_color);
	__set_blend_mode(_engin_->draw_blend_mode);

	if (_engin_->draw_glow_mode == 0) {
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_POINTS);
			glVertex2i(x, y);
		glEnd();
		glEnable(GL_TEXTURE_2D);
	} else {
		__draw_bind_glow();

		glTranslatef(x - (_engin_->draw_size/2), y - (_engin_->draw_size/2), 0);
		glScalef(_engin_->draw_size, _engin_->draw_size, 1);

		glCallList(_engin_->display_list_1x1);
    }
}

/*
Function: Draw_Points

Parameters:

Return:

*/
void    YAGL_API    Draw_Points (int points[], int nbr)
{
    glLoadIdentity();
	glColor4ubv((GLubyte*)&_engin_->draw_color);
	__set_blend_mode(_engin_->draw_blend_mode);

	int i = 0;

	if (_engin_->draw_glow_mode == 0) {
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_POINTS);

		for (i = 0; i < nbr; i += 2) {
			if (i < nbr - 1) { glVertex2i(points[i], points[i + 1]); }
		}
		glEnd();
		glEnable(GL_TEXTURE_2D);
	} else {
		__draw_bind_glow();

		for (i = 0; i < nbr; i += 2) {
			if (i < nbr - 1) {
				glTranslatef(points[i] - (_engin_->draw_size/2), points[i + 1] - (_engin_->draw_size/2), 0);
				glScalef(_engin_->draw_size, _engin_->draw_size, 1);

				glCallList(_engin_->display_list_1x1);

				//glLoadIdentity();
			}
		}
	}
}

/*
Function: Draw_Line

Parameters:

Return:

*/
void    YAGL_API    Draw_Line (int x1, int y1, int x2, int y2)
{
    glLoadIdentity();
	glColor4ubv((GLubyte*)&_engin_->draw_color);
	__set_blend_mode(_engin_->draw_blend_mode);

	if (_engin_->draw_glow_mode == 0) {
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_LINES);
			glVertex2i(x1, y1); glVertex2i(x2, y2);
		glEnd();
		glEnable(GL_TEXTURE_2D);
	} else {
		__draw_bind_glow();
		__gl_glow_line(x1, y1, x2, y2, _engin_->draw_size);
	}
}

/*
Function: Draw_Lines

Parameters:

Return:

*/
void    YAGL_API    Draw_Lines (int points[], int nbr, int strip)
{
    glLoadIdentity();
	glColor4ubv((GLubyte*)&_engin_->draw_color);
	__set_blend_mode(_engin_->draw_blend_mode);

	int i = 0;

	if (_engin_->draw_glow_mode == 0) {
		glDisable(GL_TEXTURE_2D);
		if (strip == 0) {
			glBegin(GL_LINES);
		} else {
			glBegin(GL_LINE_STRIP);
		}
			for (i = 0; i < nbr; i += 2) {
				if (i < nbr - 1) { glVertex2i(points[i], points[i + 1]); }
			}
		glEnd();
		glEnable(GL_TEXTURE_2D);
	} else {
		__draw_bind_glow();
		if (strip == 0) {
			for (i = 0; i < nbr; i += 4) {
				if (i < nbr - 3) {
					__gl_glow_line(points[i], points[i + 1], points[i + 2], points[i + 3], _engin_->draw_size);
				}
			}
		} else {
			for (i = 0; i < nbr; i += 2) {
				if (i < nbr - 3) {
					__gl_glow_line(points[i], points[i + 1], points[i + 2], points[i + 3], _engin_->draw_size);
				}
			}
		}
	}
}

/*
Function: Draw_Triangle

Parameters:

Return:

*/
void    YAGL_API    Draw_Triangle (int x1, int y1, int x2, int y2, int x3, int y3)
{
    glLoadIdentity();
	glColor4ubv((GLubyte*)&_engin_->draw_color);
	__set_blend_mode(_engin_->draw_blend_mode);

	if (_engin_->draw_glow_mode == 0) {
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_LINE_STRIP);
			glVertex2i(x1, y1); glVertex2i(x2, y2); glVertex2i(x3, y3); glVertex2i(x1, y1);
		glEnd();
		glEnable(GL_TEXTURE_2D);
	} else {
		__draw_bind_glow();
		__gl_glow_line(x1, y1, x2, y2, _engin_->draw_size);
		__gl_glow_line(x1, y1, x3, y3, _engin_->draw_size);
		__gl_glow_line(x2, y2, x3, y3, _engin_->draw_size);
	}
}

/*
Function: Draw_TriangleF

Parameters:

Return:

*/
void    YAGL_API    Draw_TriangleF (int x1, int y1, int x2, int y2, int x3, int y3)
{
    glLoadIdentity();
	glColor4ubv((GLubyte*)&_engin_->draw_color);
	__set_blend_mode(_engin_->draw_blend_mode);

	if (_engin_->draw_glow_mode == 0) {
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_TRIANGLES);
			glVertex2i(x1, y1); glVertex2i(x2, y2); glVertex2i(x3, y3);
		glEnd();
		glEnable(GL_TEXTURE_2D);
	} else {
		__draw_bind_glow();
		__gl_glow_line(x1, y1, x2, y2, _engin_->draw_size);
		__gl_glow_line(x1, y1, x3, y3, _engin_->draw_size);
		__gl_glow_line(x2, y2, x3, y3, _engin_->draw_size);
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_TRIANGLES);
			glVertex2i(x1, y1); glVertex2i(x2, y2); glVertex2i(x3, y3);
		glEnd();
		glEnable(GL_TEXTURE_2D);
	}
}

/*
Function: Draw_Rect

Parameters:

Return:

*/
void    YAGL_API    Draw_Rect (int x, int y, int w, int h, float angle)
{
    glLoadIdentity();
	glColor4ubv((GLubyte*)&_engin_->draw_color);
	__set_blend_mode(_engin_->draw_blend_mode);

	if (_engin_->draw_glow_mode == 0) {
		glDisable(GL_TEXTURE_2D);

		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1);
		glScalef(w, h, 1);

		glBegin(GL_LINE_STRIP);
			glVertex2i(0, 0); glVertex2i(1, 0); glVertex2i(1, 1); glVertex2i(0, 1); glVertex2i(0, 0);
		glEnd();

		glEnable(GL_TEXTURE_2D);
	} else {
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(-x, -y, 0);

		__draw_bind_glow();
		__gl_glow_line(x, y, x+w, y, _engin_->draw_size);
		__gl_glow_line(x+w, y, x+w, y+h, _engin_->draw_size);
		__gl_glow_line(x+w, y+h, x, y+h, _engin_->draw_size);
		__gl_glow_line(x, y+h, x, y, _engin_->draw_size);
	}
}

/*
Function: Draw_RectF

Parameters:

Return:

*/
void    YAGL_API    Draw_RectF (int x, int y, int w, int h, float angle)
{
    glLoadIdentity();
	glColor4ubv((GLubyte*)&_engin_->draw_color);
	__set_blend_mode(_engin_->draw_blend_mode);

	if (_engin_->draw_glow_mode == 0) {
		glDisable(GL_TEXTURE_2D);

		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1);
		glScalef(w, h, 1);

		glCallList(_engin_->display_list_1x1);

		glEnable(GL_TEXTURE_2D);
	} else {
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1);
		glScalef(w, h, 1);

		glDisable(GL_TEXTURE_2D);
		glCallList(_engin_->display_list_1x1);

		glLoadIdentity();

		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(-x, -y, 0);

		glEnable(GL_TEXTURE_2D);
		__draw_bind_glow();
		__gl_glow_line(x, y, x+w, y, _engin_->draw_size);
		__gl_glow_line(x+w, y, x+w, y+h, _engin_->draw_size);
		__gl_glow_line(x+w, y+h, x, y+h, _engin_->draw_size);
		__gl_glow_line(x, y+h, x, y, _engin_->draw_size);
    }
}

/*
Function: Draw_RectCenter

Parameters:

Return:

*/
void    YAGL_API    Draw_RectCenter (int x, int y, int w, int h, float angle)
{
    glLoadIdentity();
	glColor4ubv((GLubyte*)&_engin_->draw_color);
	__set_blend_mode(_engin_->draw_blend_mode);

	if (_engin_->draw_glow_mode == 0) {
		glDisable(GL_TEXTURE_2D);

		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(-w/2, -h/2, 0);
		glScalef(w, h, 1);

		glBegin(GL_LINE_STRIP);
			glVertex2i(0, 0); glVertex2i(1, 0); glVertex2i(1, 1); glVertex2i(0, 1); glVertex2i(0, 0);
		glEnd();

		glEnable(GL_TEXTURE_2D);
	} else {
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(-w/2, -h/2, 0);
		glTranslatef(-x, -y, 0);

		__draw_bind_glow();
		__gl_glow_line(x, y, x+w, y, _engin_->draw_size);
		__gl_glow_line(x+w, y, x+w, y+h, _engin_->draw_size);
		__gl_glow_line(x+w, y+h, x, y+h, _engin_->draw_size);
		__gl_glow_line(x, y+h, x, y, _engin_->draw_size);
	}
}

/*
Function: Draw_RectCenterF

Parameters:

Return:

*/
void    YAGL_API    Draw_RectCenterF (int x, int y, int w, int h, float angle)
{
    glLoadIdentity();
	glColor4ubv((GLubyte*)&_engin_->draw_color);
	__set_blend_mode(_engin_->draw_blend_mode);

	if (_engin_->draw_glow_mode == 0) {
		glDisable(GL_TEXTURE_2D);

		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(-w/2, -h/2, 0);
		glScalef(w, h, 1);

		glCallList(_engin_->display_list_1x1);

		glEnable(GL_TEXTURE_2D);
	} else {
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(-w/2, -h/2, 0);
		glScalef(w, h, 1);

		glDisable(GL_TEXTURE_2D);
		glCallList(_engin_->display_list_1x1);

		glLoadIdentity();

		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(-w/2, -h/2, 0);

		glEnable(GL_TEXTURE_2D);
		__draw_bind_glow();
		__gl_glow_line(0, 0, w, 0, _engin_->draw_size);
		__gl_glow_line(w, 0, w, h, _engin_->draw_size);
		__gl_glow_line(w, h, 0, h, _engin_->draw_size);
		__gl_glow_line(0, h, 0, 0, _engin_->draw_size);
	}
}

/*
Function: Draw_Ellipse

Parameters:

Return:

*/
void    YAGL_API    Draw_Ellipse (int x, int y, int rx, int ry, float angle, int precision)
{
    glLoadIdentity();
	glColor4ubv((GLubyte*)&_engin_->draw_color);
	__set_blend_mode(_engin_->draw_blend_mode);

	if (_engin_->draw_glow_mode == 0) {
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1);
		glScalef(rx, ry, 1);

		glDisable(GL_TEXTURE_2D);
		glCallList(_engin_->display_list_circle);
		glEnable(GL_TEXTURE_2D);
	} else {
		__draw_bind_glow();
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1);

		VectF old_point = {0.0, 0.0}, curr_point = {0.0, 0.0};
		int angle_step = 360/precision, i = 0;

		for (i = 0; i <= 360 + fabs(angle_step); i += fabs(angle_step)) {
			curr_point.x = cos(PI*i/180) * (rx);
			curr_point.y = sin(PI*i/180) * (ry);

			if (old_point.x != 0.0 && old_point.y != 0.0) {
				__gl_glow_line(curr_point.x, curr_point.y, old_point.x, old_point.y, _engin_->draw_size);
			}

			old_point = curr_point;
		}
	}
}

/*
Function: Draw_EllipseF

Parameters:

Return:

*/
void    YAGL_API    Draw_EllipseF (int x, int y, int rx, int ry, float angle, int precision)
{
    glLoadIdentity();
	glColor4ubv((GLubyte*)&_engin_->draw_color);
	__set_blend_mode(_engin_->draw_blend_mode);

	if (_engin_->draw_glow_mode == 0) {
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1);
		glScalef(rx, ry, 1);

		glDisable(GL_TEXTURE_2D);
		glCallList(_engin_->display_list_disc);
		glEnable(GL_TEXTURE_2D);
	} else {
	    __draw_bind_glow();

		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1);

		VectF old_point = {0.0, 0.0};
		VectF curr_point = {0.0, 0.0};
		int angle_step = 360/precision;

        int i = 0;
		for (i = 0; i <= 360 + fabs(angle_step); i += fabs(angle_step)) {
			curr_point.x = cos(PI*i/180) * rx;
			curr_point.y = sin(PI*i/180) * ry;
			if (old_point.x != 0.0 && old_point.y != 0.0) {
				__gl_glow_line(curr_point.x, curr_point.y, old_point.x, old_point.y, _engin_->draw_size);
			}
			old_point = curr_point;
		}

		glScalef(rx, ry, 1);

		glDisable(GL_TEXTURE_2D);
		glCallList(_engin_->display_list_disc);
		glEnable(GL_TEXTURE_2D);
	}
}

/*
Function: Draw_EllipseRect

Parameters:

Return:

*/
void    YAGL_API    Draw_EllipseRect (int x, int y, int w, int h, float angle, int precision)
{
    glLoadIdentity();
	glColor4ubv((GLubyte*)&_engin_->draw_color);
	__set_blend_mode(_engin_->draw_blend_mode);

	if (_engin_->draw_glow_mode == 0) {
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(w/2, h/2, 0);
		glScalef(w/2, h/2, 1);

		glDisable(GL_TEXTURE_2D);
		glCallList(_engin_->display_list_circle);
		glEnable(GL_TEXTURE_2D);
	} else {
		__draw_bind_glow();

		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(w/2, h/2, 0);

		VectF old_point = {0.0, 0.0};
		VectF curr_point = {0.0, 0.0};
		int angle_step = 360/precision;

		int i = 0;
		for (i = 0; i <= 360 + fabs(angle_step); i += fabs(angle_step)) {
            curr_point.x = cos(PI*i/180) * (w/2);
			curr_point.y = sin(PI*i/180) * (h/2);
			if (old_point.x != 0.0 && old_point.y != 0.0) {
				__gl_glow_line(curr_point.x, curr_point.y, old_point.x, old_point.y, _engin_->draw_size);
			}
			old_point = curr_point;
		}
	}
}

/*
Function: Draw_EllipseRectF

Parameters:

Return:

*/
void    YAGL_API    Draw_EllipseRectF (int x, int y, int w, int h, float angle, int precision)
{
    glLoadIdentity();
	glColor4ubv((GLubyte*)&_engin_->draw_color);
	__set_blend_mode(_engin_->draw_blend_mode);

	if (_engin_->draw_glow_mode == 0) {
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(w/2, h/2, 0);
		glScalef(w/2, h/2, 1);

		glDisable(GL_TEXTURE_2D);
		glCallList(_engin_->display_list_disc);
		glEnable(GL_TEXTURE_2D);
	} else {
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(w/2, h/2, 0);

		__draw_bind_glow();

		VectF old_point = {0.0, 0.0};
		VectF curr_point = {0.0, 0.0};
		int angle_step = 360/precision;

		int i = 0;
		for (i = 0; i <= 360 + fabs(angle_step); i += fabs(angle_step)) {
			curr_point.x = cos(PI*i/180) * (w/2);
			curr_point.y = sin(PI*i/180) * (h/2);
			if (old_point.x != 0.0 && old_point.y != 0.0) {
				__gl_glow_line(curr_point.x, curr_point.y, old_point.x, old_point.y, _engin_->draw_size);
			}
			old_point = curr_point;
		}

		glScalef(w/2, h/2, 1);

		glDisable(GL_TEXTURE_2D);
		glCallList(_engin_->display_list_disc);
		glEnable(GL_TEXTURE_2D);
	}
}

/**
    @}
*/
