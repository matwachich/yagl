/**
    \addtogroup 180_bmpfont
    @{
*/

#include <stdio.h>
#include <string.h>

#include "all.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

inline int __bmpFont_Measure(BmpFont* bfnt, const char text[], int size)
{
    float ratio = (float)size / bfnt->size;
	float measure = 0;
	int i = 0;
	int current = 0;
	for (i = 0; i < strlen(text); i++) {
	    current = text[i];
	    if (current < 0) { current += 256; }
		measure += (float)bfnt->chrs[current].advance * ratio;
	}
	return (int)measure;
}

inline void __bmpFont_Print (BmpFont* bfnt, const char text[], int x, int y, int size, eALIGN align, float angle)
{
    glPushMatrix();
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	if (_engin_->current_texture != bfnt->texture) {
		glBindTexture(GL_TEXTURE_2D, bfnt->texture);
		_engin_->current_texture = bfnt->texture;
	}
	glListBase(bfnt->display_lists_base);

	float scale_ratio = (float)size / bfnt->size;
	int len = 0;

	switch (align)
	{
	    case ALIGN_LEFT:
			glTranslatef(x, y, 0);
			glScalef(scale_ratio, scale_ratio, 1);
			glRotatef(angle, 0, 0, 1);
        break;
		case ALIGN_CENTER:
			len = BmpFont_Measure(bfnt, text, size);
			glTranslatef(x - (len/2), y, 0);
			glScalef(scale_ratio, scale_ratio, 1);
			glRotatef(angle, 0, 0, 1);
        break;
		case ALIGN_RIGHT:
			len = BmpFont_Measure(bfnt, text, size);
			glTranslatef(x - len, y, 0);
			glScalef(scale_ratio, scale_ratio, 1);
			glRotatef(angle, 0, 0, 1);
        break;
	}
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);

	glListBase(0);
	glPopMatrix();
}

inline void __bmpFont_PrintLines (BmpFont* bfnt, const char text[], int x, int y, int size, eALIGN align, float angle)
{
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	if (_engin_->current_texture != bfnt->texture) {
		glBindTexture(GL_TEXTURE_2D, bfnt->texture);
		_engin_->current_texture = bfnt->texture;
	}
	glListBase(bfnt->display_lists_base);

	int len = 0;
	int i = 0;
	float scale_ratio = (float)size / (float)bfnt->size;

    char string[strlen(text) + 1];
    sprintf(string, "%s", text);

    char* tok = NULL;
    tok = strtok(string, "\n");

    while (tok != NULL) {

        glLoadIdentity();

        switch (align)
        {
			case ALIGN_LEFT:
				glTranslatef(x, y + (i * bfnt->line_height * scale_ratio), 0);
				glScalef(scale_ratio, scale_ratio, 1);
				glRotatef(angle, 0, 0, 1);
            break;
			case ALIGN_CENTER:
				len = BmpFont_Measure(bfnt, tok, size);
				glTranslatef(x - (len/2), y + (i * bfnt->line_height * scale_ratio), 0);
				glScalef(scale_ratio, scale_ratio, 1);
				glRotatef(angle, 0, 0, 1);
            break;
			case ALIGN_RIGHT:
				len = BmpFont_Measure(bfnt, tok, size);
				glTranslatef(x - len, y + (i * bfnt->line_height * scale_ratio), 0);
				glScalef(scale_ratio, scale_ratio, 1);
				glRotatef(angle, 0, 0, 1);
            break;
        }

		glCallLists(strlen(tok), GL_UNSIGNED_BYTE, tok);

        tok = strtok(NULL, "\n");
        i++;
    }

	glListBase(0);
	glPopMatrix();
}

inline void __bmpFont_clean (BmpFont* bfnt)
{
    free(bfnt->face_name);
    free(bfnt->chrs);

    glDeleteTextures(1, &bfnt->texture);
    glDeleteLists(bfnt->display_lists_base, 256);
}

/* ------------------------------------------------------------------------- **/
/* Public functions **/

/*
Function: BmpFont_Create

Parameters:

Return:

*/
BmpFont*   YAGL_API    BmpFont_Create (const char fnt_file[], const char img_file[])
{
    BmpFont* bfnt = (BmpFont*)mem_alloc(sizeof(BmpFont), PTR_BMP_FONT);
    if (bfnt == NULL) { __DEBUG__("Unable to create BmpFont. (Out of memory)", 2); }

    FILE* hfile = fopen(fnt_file, "r");
    if (hfile == NULL) {
        char tmp[1024];
        sprintf(tmp, "Unable to load file: %s", fnt_file);
        __DEBUG__(tmp, 1);
        free(bfnt);
        return NULL;
    }

    bfnt->texture = SOIL_load_OGL_texture(img_file, 4, 0, SOIL_FLAG_POWER_OF_TWO);
    if (bfnt->texture == 0) {
        char tmp[1024];
        sprintf(tmp, "Unable to load file: %s", img_file);
        __DEBUG__(tmp, 1);
        fclose(hfile);
        free(bfnt);
        return NULL;
    }

    glBindTexture(GL_TEXTURE_2D, bfnt->texture);
    _engin_->current_texture = bfnt->texture;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	bfnt->display_lists_base = glGenLists(256);
	if (bfnt->display_lists_base == 0) {
		__DEBUG__("Unable to create BmpFont. (OpenGL display lists allocation failed)", 1);
		fclose(hfile);
		glDeleteTextures(1, &bfnt->texture);
		free(bfnt);
		return NULL;
	}

	bfnt->chrs = malloc(256 * sizeof(Char));
	if (bfnt->chrs == NULL) {
		fclose(hfile);
		glDeleteTextures(1, &bfnt->texture);
		glDeleteLists(bfnt->display_lists_base, 256);
		free(bfnt);
		__DEBUG__("Unable to create BmpFont. (Out of memory)", 2);
	}

	int i = 0;
	for (i = 0; i < 256; i++) {
        bfnt->chrs[i].id = 0;
        bfnt->chrs[i].advance = 0;
	}

	char line[1024] = "";
	int id = 0, xadvance = 0, x = 0, y = 0, xoffset = 0, yoffset = 0, width = 0, height = 0;
	float tmp_x, tmp_y;

	while (fgets(line, 1024, hfile) != NULL) {
        if (strstr(line, "info ") != NULL) {
            char face[128] = "";
            sscanf(line, "info face=%s size=%d", face, &bfnt->size);

            int len = strlen(face);
            if (len <= 0) {
                sprintf(face, "%s", "unknown");
            } else {
                // pour le bug des "
                char tmp[len - 1];
                int i;
                for (i = 0; i < len - 1; i++) {
                    tmp[i] = face[i + 1];
                }
                tmp[len - 2] = '\0';
                // ---
                strcpy(face, tmp);
            }

            bfnt->face_name = (char*)malloc((strlen(face) + 1) * sizeof(char));
            if (bfnt->face_name == NULL) {
                fclose(hfile);
                glDeleteTextures(1, &bfnt->texture);
                glDeleteLists(bfnt->display_lists_base, 256);
                free(bfnt);
                __DEBUG__("Unable to create BmpFont. (Out of memory)", 2);
            }
            sprintf(bfnt->face_name, "%s", face);
        }

        if (strstr(line, "common ") != NULL) {
            sscanf(line, "common lineHeight=%d base=%d scaleW=%d scaleH=%d", &bfnt->line_height, &bfnt->line_base, &bfnt->texture_w, &bfnt->texture_h);
        }

        if (strstr(line, "chars ") != NULL) {
            sscanf(line, "chars count=%d", &bfnt->chars_count);
        }

        if (strstr(line, "char ") != NULL) {
            sscanf(line, "char id=%d x=%d y=%d width=%d height=%d xoffset=%d yoffset=%d xadvance=%d", &id, &x, &y, &width, &height, &xoffset, &yoffset, &xadvance);

            bfnt->chrs[id].id = id;
			bfnt->chrs[id].advance = xadvance;

			glNewList(id + bfnt->display_lists_base, GL_COMPILE);
				glBegin(GL_TRIANGLE_FAN);

					// Upper-left
					tmp_x = (float)x / bfnt->texture_w;
					tmp_y = (float)y / bfnt->texture_h;
					glTexCoord2f(tmp_x, tmp_y);

					tmp_x = (float)xoffset;
					tmp_y = (float)(-bfnt->line_base + yoffset);
					glVertex2f(tmp_x, tmp_y);

					// Upper-right
					tmp_x = (float)(x + width) / bfnt->texture_w;
					tmp_y = (float)y / bfnt->texture_h;
					glTexCoord2f(tmp_x, tmp_y);

					tmp_x = (float)(xoffset + width);
					tmp_y = (float)(-bfnt->line_base + yoffset);
					glVertex2f(tmp_x, tmp_y);

					// Lower-right
					tmp_x = (float)(x + width) / bfnt->texture_w;
					tmp_y = (float)(y + height) / bfnt->texture_h;
					glTexCoord2f(tmp_x, tmp_y);

					tmp_x = (float)(xoffset + width);
					tmp_y = (float)(-bfnt->line_base + yoffset + height);
					glVertex2f(tmp_x, tmp_y);

					// Lower-left
					tmp_x = (float)x / bfnt->texture_w;
					tmp_y = (float)(y + height) / bfnt->texture_h;
					glTexCoord2f(tmp_x, tmp_y);

					tmp_x = (float)xoffset;
					tmp_y = (float)(-bfnt->line_base + yoffset + height);
					glVertex2f(tmp_x, tmp_y);

				glEnd();

				glTranslatef(bfnt->chrs[id].advance, 0, 0);
			glEndList();
        }
	}
	fclose(hfile);
	return bfnt;
}

/*
Function: BmpFont_IsBmpFont

Parameters:

Return:

*/
int   YAGL_API    BmpFont_IsBmpFont (BmpFont* bfnt)
{
    return mem_exists(bfnt, PTR_BMP_FONT);
}

/*
Function: BmpFont_Destroy

Parameters:

Return:

*/
int   YAGL_API    BmpFont_Destroy (BmpFont* bfnt)
{
    if (mem_exists(bfnt, PTR_BMP_FONT) == 0) { return 0; }

    __bmpFont_clean(bfnt);

    return mem_free(bfnt, PTR_BMP_FONT);
}

/*
Function: BmpFont_CharExists

Parameters:

Return:

*/
int     YAGL_API    BmpFont_CharExists (BmpFont* bfnt, const char chr)
{
    if (mem_exists(bfnt, PTR_BMP_FONT) == 0) { return -1; }

    if (bfnt->chrs[(int)chr].id == 0 && bfnt->chrs[(int)chr].advance == 0) {
        return 0;
    } else {
        return 1;
    }
}

/*
Function: BmpFont_Print

Parameters:

Return:

*/
void    YAGL_API    BmpFont_Print (BmpFont* bfnt, const char text[], int x, int y, int size, eALIGN align, float angle)
{
    if (mem_exists(bfnt, PTR_BMP_FONT) == 0) { return; }

    glColor4ubv((GLubyte*)&_engin_->draw_color);
	__set_blend_mode(_engin_->draw_blend_mode);

	__bmpFont_Print(bfnt, text, x, y, size, align, angle);
}

/*
Function: BmpFont_PrintLines

Parameters:

Return:

*/
void    YAGL_API    BmpFont_PrintLines (BmpFont* bfnt, const char text[], int x, int y, int size, eALIGN align, float angle)
{
    if (mem_exists(bfnt, PTR_BMP_FONT) == 0) { return; }

    glColor4ubv((GLubyte*)&_engin_->draw_color);
	__set_blend_mode(_engin_->draw_blend_mode);

    __bmpFont_PrintLines(bfnt, text, x, y, size, align, angle);
}

/*
Function: BmpFont_Measure

Parameters:

Return:

*/
int     YAGL_API    BmpFont_Measure (BmpFont* bfnt, const char text[], int size)
{
    if (mem_exists(bfnt, PTR_BMP_FONT) == 0) { return -1; }

    return __bmpFont_Measure(bfnt, text, size);
}

/*
Function: BmpFont_GetFontFace

Parameters:

Return:

*/
char*       YAGL_API    BmpFont_GetFaceName (BmpFont* bfnt)
{
    if (mem_exists(bfnt, PTR_BMP_FONT) == 0) { return NULL; }

    return bfnt->face_name;
}

/*
Function: BmpFont_GetCharsCount

Parameters:

Return:

*/
int         YAGL_API    BmpFont_GetCharsCount (BmpFont* bfnt)
{
    if (mem_exists(bfnt, PTR_BMP_FONT) == 0) { return -1; }

    return bfnt->chars_count;
}

/**
    @}
*/
