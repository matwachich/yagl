/**
    \addtogroup 140_particles
    @{
*/

#define EMITTER_CHECK if (mem_exists(emit, PTR_PARTICLES) == 0) { return; }
#define EMITTER_CHECK_RET(ret) if (mem_exists(emit, PTR_PARTICLES) == 0) { return ret; }

#include <ctype.h> // for function: tolower()
#include <stdlib.h> // for function: strtof()
#include <string.h>

#include "all.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- **/
/* Internal functions **/

// Special Random Numbers Functions
inline int __particle_random_int(int val, int var)
{
    if (var == 0) { return val; }
    return __rnd_int(val - var, val + var + 1);
}

inline float __particle_random_float(float val, float var)
{
    if (var == 0) { return val; }
    return (float)__rnd_double(val - var, val + var);
}

inline int __particle_random_color(int col, int var)
{
    col = __particle_random_int(col, var);
    __particle_color_check_bounds(&col);
    return col;
}

inline void __particle_color_check_bounds(int* color)
{
	if (color != NULL && *color > 255) { *color = 255; }
	if (color != NULL && *color < 0) { *color = 0; }
}

// Init a particle emitter
inline void __particle_init(PEmitter* emit)
{
    emit->active = 0;
	emit->tex = NULL;
	emit->tex_rect_1[0] = 0; emit->tex_rect_1[0] = 0;
	emit->tex_rect_2[0] = 0; emit->tex_rect_2[0] = 0;
	emit->tex_rect_3[0] = 0; emit->tex_rect_3[0] = 0;
	emit->tex_rect_4[0] = 0; emit->tex_rect_4[0] = 0;
	emit->pos.x = 0; emit->pos.y = 0;
	emit->pos_var.x = 0; emit->pos_var.y = 0;
	emit->vel = 100; emit->vel_var = 0;
	emit->accel = 0; emit->accel_var = 0;
	emit->angle = 180; emit->angle_var = 180;
	emit->p_innertia = 0; emit->p_innertia_var = 0;
	emit->p_angle = 180; emit->p_angle_var = 180;
	emit->force = 0; emit->force_var = 0;
	emit->force_angle = 0; emit->force_angle_var = 0;
	emit->spin = 0; emit->spin_var = 0; emit->spin_flyvar = 0;
    emit->size = 16; emit->size_var = 0; emit->size_flyvar = 0;
	emit->life = 1; emit->life_var = 0;
	emit->p_per_sec = 50;
	emit->max_particles = 500;
	emit->blend_mode = BLEND_ALPHA;
	emit->col_r = 255; emit->col_g = 255; emit->col_b = 255; emit->col_a = 255;
	emit->col_r_var = 0; emit->col_g_var = 0; emit->col_b_var = 0; emit->col_a_var = 0;
	emit->col_r_flyvar = 0; emit->col_g_flyvar = 0; emit->col_b_flyvar = 0; emit->col_a_flyvar = 0;
	emit->p_emitte_proc = NULL; emit->p_dead_proc = NULL;
	emit->emitte_timer = glfwGetTime();
	emit->first = NULL;
	emit->count = 0;
}

inline void __particle_set_tex_rect(PEmitter* emit, int x, int y, int w, int h)
{
    if (emit->tex != NULL) {
        float fx, fy, fw, fh;
        if (w == 0) { w = emit->tex->width; }
        if (h == 0) { h = emit->tex->height; }
        fx = (float)x / emit->tex->width; fy = (float)y / emit->tex->height;
        fw = (float)w / emit->tex->width; fh = (float)h / emit->tex->height;
        emit->tex_rect_1[0] = fx;		emit->tex_rect_1[1] = fy;
		emit->tex_rect_2[0] = fx + fw;	emit->tex_rect_2[1] = fy;
		emit->tex_rect_3[0] = fx + fw;	emit->tex_rect_3[1] = fy + fh;
		emit->tex_rect_4[0] = fx;		emit->tex_rect_4[1] = fy + fh;
    } else {
        emit->tex_rect_1[0] = 0; emit->tex_rect_1[1] = 0;
        emit->tex_rect_2[0] = 0; emit->tex_rect_2[1] = 0;
        emit->tex_rect_3[0] = 0; emit->tex_rect_3[1] = 0;
        emit->tex_rect_4[0] = 0; emit->tex_rect_4[1] = 0;
    }
}

// Init a newly spawned particle
inline void __particle_init_child(PEmitter* emit, Particle* prt)
{
    float tmp1, tmp2;
    // Texture
	prt->tex = emit->tex;
	prt->tex_rect_1[0] = emit->tex_rect_1[0]; prt->tex_rect_1[1] = emit->tex_rect_1[1];
	prt->tex_rect_2[0] = emit->tex_rect_2[0]; prt->tex_rect_2[1] = emit->tex_rect_2[1];
	prt->tex_rect_3[0] = emit->tex_rect_3[0]; prt->tex_rect_3[1] = emit->tex_rect_3[1];
	prt->tex_rect_4[0] = emit->tex_rect_4[0]; prt->tex_rect_4[1] = emit->tex_rect_4[1];
	// Position
	prt->pos.x = __particle_random_float(emit->pos.x, emit->pos_var.x);
	prt->pos.y = __particle_random_float(emit->pos.y, emit->pos_var.y);
	// Velocity
	tmp1 = __particle_random_float(emit->angle, emit->angle_var); // Rnd vel/accel ange
	tmp2 = __particle_random_float(emit->vel, emit->vel_var); // Rnd vel len
	__polar_2_cartesian(tmp2, tmp1, &prt->vel.x, &prt->vel.y);
	// Acceleration
	tmp2 = __particle_random_float(emit->accel, emit->accel_var); // Rnd accel len
	__polar_2_cartesian(tmp2, tmp1, &prt->accel.x, &prt->accel.y);
	// Force
	tmp1 = __particle_random_float(emit->force_angle, emit->force_angle_var); // Rnd force angle
	tmp2 = __particle_random_float(emit->force, emit->force_var); // Rnd force len
	__polar_2_cartesian(tmp2, tmp1, &prt->force.x, &prt->force.y);
	// Add force to acceleration
	prt->accel.x += prt->force.x;
	prt->accel.y += prt->force.y;
	// Size
	prt->size = __particle_random_float(emit->size, emit->size_var);
	prt->size_var = emit->size_flyvar;
	// Innertia
	prt->innertia = __particle_random_float(emit->p_innertia, emit->p_innertia_var);
	if (prt->innertia < 0.0) { prt->innertia = 0.0; }
	// Angle
	prt->angle = __particle_random_float(emit->p_angle, emit->p_angle_var);
	// Spin
	prt->spin =	__particle_random_float(emit->spin, emit->spin_var);
	prt->spin_var = emit->spin_flyvar;
	// Life time
	prt->life = __particle_random_float(emit->life, emit->life_var);
	// Blend mode
	prt->blend_mode = emit->blend_mode;
	// Color
	prt->col_r = __particle_random_color(emit->col_r, emit->col_r_var);
	prt->col_g = __particle_random_color(emit->col_g, emit->col_g_var);
	prt->col_b = __particle_random_color(emit->col_b, emit->col_b_var);
	prt->col_a = __particle_random_color(emit->col_a, emit->col_a_var);
	// Color variation
	prt->col_r_var = emit->col_r_flyvar;
	prt->col_g_var = emit->col_g_flyvar;
	prt->col_b_var = emit->col_b_flyvar;
	prt->col_a_var = emit->col_a_flyvar;
	// Kill me
	prt->kill_me = 0;
	prt->life_timer = glfwGetTime();
}

inline void __particle_draw(Particle* prt, double dt, int visible)
{
    if (prt->kill_me == 1) { return; }

    VectF tmp_size, tmp_center;
    VectI tmp_flip = {1, 1};
    //YAGL_Color tmp_color;

    //// Dynamics calculations
    // Vel
    prt->vel.x = prt->vel.x + (prt->accel.x * dt);
    prt->vel.y = prt->vel.y + (prt->accel.y * dt);
    // Innertia
    float vel_len, vel_a;
    __cartesian_2_polar(prt->vel.x, prt->vel.y, &vel_a, &vel_len);
    if (vel_len != 0.0 && prt->innertia != 0.0) {
        vel_len -= prt->innertia * dt;
        if (vel_len < 0.0) { vel_len = 0.0; }
        __polar_2_cartesian(vel_len, vel_a, &prt->vel.x, &prt->vel.y);
    }
    // Pos
    prt->pos.x = prt->pos.x + (prt->vel.x * dt);
    prt->pos.y = prt->pos.y + (prt->vel.y * dt);
    // Size & Center
    prt->size = prt->size + (prt->size_var * dt);
    if (prt->size <= 0) { prt->kill_me = 1; return; }

    tmp_size.x = prt->size;
    tmp_size.y = prt->size;
    tmp_center.x = prt->size / 2;
    tmp_center.y = prt->size / 2;
    // Spin
    prt->spin = prt->spin + (prt->spin_var * dt);
    prt->angle = prt->angle + (prt->spin * dt);
    // Color
    int tmp;
    tmp = prt->col_a + (prt->col_a_var * dt); __particle_color_check_bounds(&tmp);
        prt->col_a = tmp;
        if (prt->col_a <= 0) { prt->kill_me = 1; return; }
    tmp = prt->col_r + (prt->col_r_var * dt); __particle_color_check_bounds(&tmp);
        prt->col_r = tmp;
    tmp = prt->col_g + (prt->col_g_var * dt); __particle_color_check_bounds(&tmp);
        prt->col_g = tmp;
    tmp = prt->col_b + (prt->col_b_var * dt); __particle_color_check_bounds(&tmp);
        prt->col_b = tmp;
    ////
    if ((glfwGetTime() - prt->life_timer) * _engin_->timer_mult >= prt->life) {
        prt->kill_me = 1; return;
    }
    ////
    if (visible) {
        __sprite_draw_quad(
            prt->tex,
            prt->blend_mode,
            prt->pos,
            tmp_size,
            tmp_center,
            tmp_flip,
            prt->angle,
            (YAGL_Color)YAGL_RGBA(prt->col_r, prt->col_g, prt->col_b, prt->col_a),
            prt->tex_rect_1, prt->tex_rect_2, prt->tex_rect_3, prt->tex_rect_4
        );
    }
}

inline void __particle_destroy_all_parts (PEmitter* emit)
{
    if (emit->first != NULL) {
		Particle* current = emit->first;
		Particle* tmp = NULL;

		while (current != NULL)
		{
		    tmp = current->_next;
			free(current);
			current = tmp;
		}

		emit->count = 0;
		emit->first = NULL;
    }
}

int __particle_ini_parse_callback (PEmitterAndSection* data, char* section, char* name, char* value)
{
    __tolower(section);
    __tolower(name);
    // ---
    #define CMP(v) strcmp(name, v) == 0
    #define SET_f(v) data->emit->v = (float)strtof(value, NULL);
    #define SET_i(v) data->emit->v = (int)atoi(value);
    #define SET_ui(v) data->emit->v = (unsigned int)atoi(value);
    #define SET_uc(v) data->emit->v = (unsigned char)atoi(value);
    #define SET_s(v) data->emit->v = (short)atoi(value);
    // ---
    if (strcmp(data->section, section) == 0) {
        if (strcmp(name, "tex_rect") == 0 && data->load_tex_rect != 0) {
            __particle_ini_load_tex_rect (data->emit, value);
        }
        // ---
        else if (CMP("pos_var_x")) {
            SET_f(pos_var.x)
        }
        else if (CMP("pos_var_y")) {
            SET_f(pos_var.y)
        }
        else if (CMP("vel")) {
            SET_f(vel)
        }
        else if (CMP("vel_var")) {
            SET_f(vel_var)
        }
        else if (CMP("accel")) {
            SET_f(accel)
        }
        else if (CMP("accel_var")) {
            SET_f(accel_var)
        }
        else if (CMP("angle")) {
            SET_f(angle)
        }
        else if (CMP("angle_var")) {
            SET_f(angle_var)
        }
        else if (CMP("force")) {
            SET_f(force)
        }
        else if (CMP("force_var")) {
            SET_f(force_var)
        }
        else if (CMP("force_angle")) {
            SET_f(force_angle)
        }
        else if (CMP("force_angle_var")) {
            SET_f(force_angle_var)
        }
        else if (CMP("p_innertia")) {
            SET_f(p_innertia)
        }
        else if (CMP("p_innertia_var")) {
            SET_f(p_innertia_var)
        }
        else if (CMP("p_angle")) {
            SET_f(p_angle)
        }
        else if (CMP("p_angle_var")) {
            SET_f(p_angle_var)
        }
        else if (CMP("spin")) {
            SET_f(spin)
        }
        else if (CMP("spin_var")) {
            SET_f(spin_var)
        }
        else if (CMP("spin_flyvar")) {
            SET_f(spin_flyvar)
        }
        else if (CMP("size")) {
            SET_f(size)
        }
        else if (CMP("size_var")) {
            SET_f(size_var)
        }
        else if (CMP("size_flyvar")) {
            SET_f(size_flyvar)
        }
        else if (CMP("life")) {
            SET_f(life)
        }
        else if (CMP("life_var")) {
            SET_f(life_var)
        }
        else if (CMP("p_per_sec")) {
            SET_ui(p_per_sec)
        }
        else if (CMP("max_particles")) {
            SET_ui(max_particles)
        }
        else if (CMP("blend_mode")) {
            SET_i(blend_mode)
        }
        else if (CMP("col_r")) {
            SET_uc(col_r)
        }
        else if (CMP("col_g")) {
            SET_uc(col_g)
        }
        else if (CMP("col_b")) {
            SET_uc(col_b)
        }
        else if (CMP("col_a")) {
            SET_uc(col_a)
        }
        else if (CMP("col_r_var")) {
            SET_s(col_r_var)
        }
        else if (CMP("col_g_var")) {
            SET_s(col_g_var)
        }
        else if (CMP("col_b_var")) {
            SET_s(col_b_var)
        }
        else if (CMP("col_a_var")) {
            SET_s(col_a_var)
        }
        else if (CMP("col_r_flyvar")) {
            SET_s(col_r_flyvar)
        }
        else if (CMP("col_g_flyvar")) {
            SET_s(col_g_flyvar)
        }
        else if (CMP("col_b_flyvar")) {
            SET_s(col_b_flyvar)
        }
        else if (CMP("col_a_flyvar")) {
            SET_s(col_a_flyvar)
        }
    }
    // ---
    return 1;
}

inline void __particle_ini_load_tex_rect (PEmitter* emit, char* value)
{
    int count = 0;
    int tex_rect[4] = {0, 0, 0, 0};

    char* tok = NULL;
    tok = strtok(value, ",");

    while (tok != NULL && count <= 3) {
        tex_rect[count] = atoi(tok);
        // ---
        tok = strtok(NULL, ",");
        count++;
    }

    PEmitter_SetTextureRect(emit, tex_rect[0], tex_rect[1], tex_rect[2], tex_rect[3]);
}

void inline __tolower (char* str)
{
    int i = 0;
    for (i=0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void inline __pemitter_draw (PEmitter* emit)
{
    // Call Emitte
    if (emit->active && emit->p_per_sec != 0) {
        float min_delay = 1.0f / emit->p_per_sec;
        double dt = (glfwGetTime() - emit->emitte_timer) * _engin_->timer_mult;
        if (dt >= min_delay) {
            int nbr = (unsigned int)(dt / min_delay);
            if (nbr == 0) { nbr = 1; }
            if (emit->count + nbr > emit->max_particles) {
                nbr = emit->max_particles - emit->count;
                if (nbr < 0) { nbr = 0; }
            }
            PEmitter_Emitte(emit, nbr);
            emit->emitte_timer = glfwGetTime();
        }
    }

	Particle* current = emit->first;
	Particle* previous = NULL;

	double dt = _engin_->delta * _engin_->timer_mult;

	while (current != NULL)
	{
	    // Draw
		__particle_draw(current, dt, emit->visible);
		// Check if particle is dead
		if (current->kill_me != 0) {
			// Call particle dead callback
			if (emit->p_dead_proc != NULL) { emit->p_dead_proc(emit, 0, current->pos.x, current->pos.y); }

			if (previous == NULL) { // delete the first element
				emit->first = current->_next;
				free(current);
				current = emit->first;
			} else { // other elements
				previous->_next = current->_next;
				free(current);
				current = previous->_next;
			}
			emit->count -= 1;
		}

		if (current != NULL) {
			previous = current;
			current = current->_next;
		}
	}
}

/* ------------------------------------------------------------------------- **/
/* Public functions **/

/*
Function: PEmitter_Create

Parameters:

Return:

*/
PEmitter*   YAGL_API    PEmitter_Create (Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h)
{
    PEmitter* emit = mem_alloc(sizeof(PEmitter), PTR_PARTICLES);
    if (emit == NULL) {
        __DEBUG__("Unable to create particle emitter. (Out of memory)", 2);
    }

    __particle_init(emit);
    emit->tex = tex;
    __particle_set_tex_rect(emit, rect_x, rect_y, rect_w, rect_h);

    return emit;
}

/*
Function: PEmitter_Copy

Parameters:

Return:

*/
int   YAGL_API    PEmitter_IsPEmitter (PEmitter* emit)
{
    return mem_exists(emit, PTR_PARTICLES);
}

/*
Function: PEmitter_LoadCfg

Parameters:

Return:

*/
int         YAGL_API    PEmitter_ReadCfg (PEmitter* emit, const char* file, const char* section, int load_tex_rect)
{
    char section_cpy[strlen(section) + 1];
    sprintf(section_cpy, "%s", section);
    __tolower(section_cpy);

    PEmitterAndSection data;
    data.emit = emit;
    data.section = section_cpy;
    data.load_tex_rect = load_tex_rect;

    // Pour éviter le warning du compilateur
    typedef int(*INIHandler)(void*,const char*,const char*,const char*);
    int ret = ini_parse(file, (INIHandler)__particle_ini_parse_callback, &data);

    return ret;
}

/*
Function: PEmitter_WriteCfg

Parameters:

Return:

*/
int         YAGL_API    PEmitter_WriteCfg (PEmitter* emit, const char* file, const char* section, int save_tex_rect)
{
    FILE* f = fopen(file, "a");
    if (f == NULL) {
        return -1;
    }

    fprintf(f, "[%s]\n", section);

    if (save_tex_rect != 0) {
        int tex_x, tex_y, tex_w, tex_h;
        PEmitter_GetTextureRect(emit, &tex_x, &tex_y, &tex_w, &tex_h);
        fprintf(f, "tex_rect=%i,%i,%i,%i\n", tex_x, tex_y, tex_w, tex_h);
    }

    fprintf(f, "pos_var_x=%f\npos_var_y=%f\nvel=%f\nvel_var=%f\naccel=%f\naccel_var=%f\nangle=%f\nangle_var=%f\nforce=%f\nforce_var=%f\nforce_angle=%f\nforce_angle_var=%f\np_innertia=%f\np_innertia_var=%f\np_angle=%f\np_angle_var=%f\nspin=%f\nspin_var=%f\nspin_flyvar=%f\nsize=%f\nsize_var=%f\nsize_flyvar=%f\nlife=%f\nlife_var=%f\np_per_sec=%i\nmax_particles=%i\nblend_mode=%i\ncol_r=%i\ncol_g=%i\ncol_b=%i\ncol_a=%i\ncol_r_var=%i\ncol_g_var=%i\ncol_b_var=%i\ncol_a_var=%i\ncol_r_flyvar=%i\ncol_g_flyvar=%i\ncol_b_flyvar=%i\ncol_a_flyvar=%i\n",
                emit->pos_var.x, emit->pos_var.y, emit->vel, emit->vel_var, emit->accel, emit->accel_var, emit->angle, emit->angle_var, emit->force, emit->force_var, emit->force_angle, emit->force_angle_var, emit->p_innertia, emit->p_innertia_var, emit->p_angle, emit->p_angle_var, emit->spin, emit->spin_var, emit->spin_flyvar, emit->size, emit->size_var, emit->size_flyvar, emit->life, emit->life_var, emit->p_per_sec, emit->max_particles, emit->blend_mode, emit->col_r, emit->col_g, emit->col_b, emit->col_a, emit->col_r_var, emit->col_g_var, emit->col_b_var, emit->col_a_var, emit->col_r_flyvar, emit->col_g_flyvar, emit->col_b_flyvar, emit->col_a_flyvar);

    fclose(f);
    return 1;
}

/*
Function: PEmitter_Copy

Parameters:

Return:

*/
int   YAGL_API    PEmitter_Copy (PEmitter* source, PEmitter* dest, int copy_texture)
{
    if (mem_exists(source, PTR_PARTICLES) == 0 || mem_exists(dest, PTR_PARTICLES) == 0) { return -1; }

    #define CPY(field) dest->field = source->field;

    if (copy_texture != 0) {
        CPY(tex)
        CPY(tex_rect_1[0]) CPY(tex_rect_2[0]) CPY(tex_rect_3[0]) CPY(tex_rect_4[0])
        CPY(tex_rect_1[1]) CPY(tex_rect_2[1]) CPY(tex_rect_3[1]) CPY(tex_rect_4[1])
    }

    CPY(pos.x) CPY(pos.y)
    CPY(pos_var.x) CPY(pos_var.y)

    CPY(vel) CPY(vel_var)
    CPY(accel) CPY(accel_var)
    CPY(angle) CPY(angle_var)

    CPY(force) CPY(force_var)
    CPY(force_angle) CPY(force_angle_var)

    CPY(p_innertia) CPY(p_innertia_var)
    CPY(p_angle) CPY(p_angle_var)

    CPY(spin) CPY(spin_var) CPY(spin_flyvar)
    CPY(size) CPY(size_var) CPY(size_flyvar)

    CPY(life) CPY(life_var)
    CPY(p_per_sec) CPY(max_particles)

    CPY(blend_mode)

    CPY(col_r) CPY(col_g) CPY(col_b) CPY(col_a)
    CPY(col_r_var) CPY(col_g_var) CPY(col_b_var) CPY(col_a_var)
    CPY(col_r_flyvar) CPY(col_g_flyvar) CPY(col_b_flyvar) CPY(col_a_flyvar)

    return 1;
}

/*
Function: PEmitter_SetTexture

Parameters:

Return:

*/
void        YAGL_API    PEmitter_SetTexture (PEmitter* emit, Texture* tex)
{
    EMITTER_CHECK

    emit->tex = tex;
}

/*
Function: PEmitter_GetTexture

Parameters:

Return:

*/
Texture*    YAGL_API    PEmitter_GetTexture (PEmitter* emit)
{
    EMITTER_CHECK_RET(0)

    return emit->tex;
}

/*
Function: PEmitter_SetTextureRect

Parameters:

Return:

*/
void        YAGL_API    PEmitter_SetTextureRect (PEmitter* emit, int rect_x, int rect_y, int rect_w, int rect_h)
{
    EMITTER_CHECK

    __particle_set_tex_rect(emit, rect_x, rect_y, rect_w, rect_h);
}

/*
Function: PEmitter_GetTextureRect

Parameters:

Return:

*/
void        YAGL_API    PEmitter_GetTextureRect (PEmitter* emit, int* rect_x, int* rect_y, int* rect_w, int* rect_h)
{
    EMITTER_CHECK

    if (emit->tex != NULL) {
        if (rect_x != NULL) { *rect_x = emit->tex_rect_1[0] * emit->tex->width; }
        if (rect_y != NULL) { *rect_y = emit->tex_rect_1[1] * emit->tex->height; }
        if (rect_w != NULL) { *rect_w = (emit->tex_rect_3[0] - emit->tex_rect_1[0]) * emit->tex->width; }
        if (rect_h != NULL) { *rect_h = (emit->tex_rect_3[1] - emit->tex_rect_1[1]) * emit->tex->height; }
    } else {
        if (rect_x != NULL) { *rect_x = 0; }
        if (rect_y != NULL) { *rect_y = 0; }
        if (rect_w != NULL) { *rect_w = 0; }
        if (rect_h != NULL) { *rect_h = 0; }
    }
}

/*
Function: PEmitter_SetTextureMap

Parameters:

Return:

*/
void        YAGL_API    PEmitter_SetTextureMap (PEmitter* emit, TextureMap* tex_map, unsigned int rect_id)
{
    EMITTER_CHECK
    if (mem_exists(tex_map, PTR_TEXTURE_MAP) == 0) { return; }

    int x, y, w, h;
    __texture_map_get(tex_map, rect_id, &emit->tex, &x, &y, &w, &h);
    __particle_set_tex_rect(emit, x, y, w, h);
}

/*
Function: PEmitter_SetActive

Parameters:

Return:

*/
void        YAGL_API    PEmitter_SetActive (PEmitter* emit, int status)
{
    EMITTER_CHECK

    if (status == emit->active) { return; }

    emit->active = status;
    if (status) { emit->emitte_timer = glfwGetTime(); }
}

/*
Function: PEmitter_GetActive

Parameters:

Return:

*/
int	YAGL_API	PEmitter_GetActive (PEmitter* emit)
{
    EMITTER_CHECK_RET(-1)

    return emit->active;
}

/*
Function: PEmitter_Emitte

Parameters:

Return:

*/
void        YAGL_API    PEmitter_Emitte (PEmitter* emit, unsigned int nbr)
{
    EMITTER_CHECK

    if (nbr == 0) { return; }

    Particle* current[nbr];

    int i;
	for (i = 0; i < nbr; i++) {
		current[i] = malloc(sizeof(Particle));
		if (current[i] == NULL) {
            __DEBUG__("Unable to create particle. (Out of memory)", 2);
		}

		__particle_init_child(emit, current[i]);
		if (emit->p_emitte_proc != NULL) { emit->p_emitte_proc(emit, 1, current[i]->pos.x, current[i]->pos.y); }

		if (i > 0) {
			current[i - 1]->_next = current[i];
		}

		emit->count += 1;
	}

	current[nbr - 1]->_next = emit->first;
	emit->first = current[0];
}

/*
Function: PEmitter_EmitteAt

Parameters:

Return:

*/
void        YAGL_API    PEmitter_EmitteAt (PEmitter* emit, float x, float y, unsigned int nbr)
{
    EMITTER_CHECK

    if (nbr == 0) { return; }

    float old_x, old_y;
    old_x = emit->pos.x;
    old_y = emit->pos.y;

    emit->pos.x = x;
    emit->pos.y = y;

    Particle* current[nbr];

    int i;
	for (i = 0; i < nbr; i++) {
		current[i] = malloc(sizeof(Particle));
		if (current[i] == NULL) {
            __DEBUG__("Unable to create particle. (Out of memory)", 2);
		}

		__particle_init_child(emit, current[i]);
		if (emit->p_emitte_proc != NULL) { emit->p_emitte_proc(emit, 1, current[i]->pos.x, current[i]->pos.y); }

		if (i > 0) {
			current[i - 1]->_next = current[i];
		}

		emit->count += 1;
	}

	current[nbr - 1]->_next = emit->first;
	emit->first = current[0];

    emit->pos.x = old_x;
    emit->pos.y = old_y;
}

/*
Function: PEmitter_Draw

Parameters:

Return:

*/
void        YAGL_API    PEmitter_Draw (PEmitter* emit)
{
    EMITTER_CHECK

    __pemitter_draw(emit);
}

/*
Function: PEmitter_Destroy

Parameters:

Return:

*/
int   YAGL_API    PEmitter_Destroy (PEmitter* emit)
{
    EMITTER_CHECK_RET(0)

    __particle_destroy_all_parts(emit);

	return mem_free(emit, PTR_PARTICLES);
}

/**
    @}
*/
