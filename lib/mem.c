#include <stdlib.h>
#include <stdio.h>

#include "all.h"
#include "mem.h"

extern Engin* _engin_;

/* ------------------------------------------------------------------------- */

typedef struct Elem Elem;
typedef struct GC_Set GC_Set;

struct Elem {
	void* ptr;
	Elem* next;
};

struct GC_Set {
	Elem* first;
	int size;
	int type;
};

// Global vars
unsigned int _num_lists = 0;
GC_Set* _lists = NULL;

/* ------------------------------------------------------------------------- */

inline int _list_add (GC_Set* list, void* data)
{
	Elem* last = list->first;

	Elem* elem = malloc(sizeof(Elem));
	if (elem == NULL) { return 0; }

	elem->ptr = data;
	elem->next = last;

	list->first = elem;
	list->size++;

	return 1;
}

inline int _list_exists (GC_Set* list, void* data)
{
    if (data == NULL) { return 0; }

	Elem* curr = list->first;
	if (curr == NULL) { return 0; }

	do {
		if (curr->ptr == data) { return 1; }
		curr = curr->next;
	} while (curr != NULL);

	return 0;
}

inline int _list_del (GC_Set* list, void* data)
{
	Elem* prev = NULL;
	Elem* curr = list->first;
	if (curr == NULL) { return 0; }

	do {
		if (curr->ptr == data) {
			if (prev == NULL) {
				list->first = curr->next;
			} else {
				prev->next = curr->next;
			}
			free(curr);
			list->size--;
			return 1;
		}
		prev = curr;
		curr = curr->next;
	} while (curr != NULL);

	return 0;
}

inline void _list_delall (GC_Set* list, ePTR_TYPE type)
{
	Elem* tmp = NULL;
	Elem* curr = list->first;
	if (curr == NULL) { return; }

	Animation* tmp_anim = NULL;
	BmpText* tmp_btxt = NULL;

    Shader* tmp_shader = NULL;
	if (_engin_->shaders != NULL) {
        __shader_use(0); // pour que les shaders ne soient pas empécher de se détruire (on sais jamais!)
	}

	do {
		tmp = curr->next;
		// ---
		// Clean objects
		switch (type) {
            case PTR_TEXTURE: // free OpenGL texture
                __texture_empty(curr->ptr);
            break;
            case PTR_TEXTURE_MAP: // free texture map elements
                __texture_map_empty(curr->ptr);
            break;
            case PTR_QUAD: break; // nothing to free
            case PTR_SPRITE: break; // nothing to free
            case PTR_SPRITE_SET: break; // nothing to free (the sprites are freed)
            case PTR_ANIMATION: // free Animation's frames
                tmp_anim = curr->ptr;
                free(tmp_anim->frames);
            break;
            case PTR_PARTICLES: // free all particles
                __particle_destroy_all_parts(curr->ptr);
            break;
            case PTR_SHADER: // destroy shader and program
                if (_engin_->shaders != NULL) {
                    tmp_shader = curr->ptr;
                    _engin_->shaders->glDeleteProgram(tmp_shader->program);
                }
            break;
            case PTR_BMP_FONT: // free caracters and face name
                __bmpFont_clean(curr->ptr);
            break;
            case PTR_BMP_TEXT: // free the text
                tmp_btxt = curr->ptr;
                if (tmp_btxt->text != NULL) { free(tmp_btxt->text); }
            break;
            case PTR_MULTISET:

            break;
		}
        // ---
		free(curr->ptr);
		free(curr);

		curr = tmp;
	} while (curr != NULL);

	list->size = 0;
}

/* ------------------------------------------------------------------------- */

#define CHECK_TYPE(type, ret) if (type < 0 || type >= _num_lists) { return ret; }

inline int		mem_init (unsigned int num_types)
{
	_lists = malloc(sizeof(GC_Set) * num_types);
	if (_lists == NULL) { return 0; }

	int i = 0;
	for (i=0; i!=num_types; i++) { // <
		_lists[i].first = NULL;
		_lists[i].size = 0;
		_lists[i].type = i;
	}

	_num_lists = num_types;
	return 1;
}

inline void	    mem_clean ()
{
	int i = 0;
	for (i=0; i!=_num_lists; i++) { // <
		_list_delall(&_lists[i], i);
	}
	free(_lists);

	_num_lists = 0;
	_lists = NULL;
}

inline void*	mem_alloc (size_t size, unsigned int type)
{
	CHECK_TYPE(type, NULL)

	void* ptr = malloc(size);
	if (ptr == NULL) { return NULL; }

	if (_list_add(&_lists[type], ptr) == 0) { free(ptr); return NULL; }

	return ptr;
}

inline int		mem_exists (void* ptr, unsigned int type)
{
	CHECK_TYPE(type, -1)

	return _list_exists(&_lists[type], ptr);
}

inline int		mem_free (void* ptr, unsigned int type)
{
	CHECK_TYPE(type, -1)

	if (_list_del(&_lists[type], ptr) == 1) {
		free(ptr);
		return 1;
	} else {
		return 0;
	}
}

inline int		mem_type_get_size (unsigned int type)
{
	CHECK_TYPE(type, -1)

	return _lists[type].size;
}
