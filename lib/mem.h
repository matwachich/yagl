#ifndef __MEM_H__
#define __MEM_H__

#define MEM_PTR_TYPES_COUNT 11

typedef enum ePTR_TYPE ePTR_TYPE;
enum ePTR_TYPE { // les valeurs sont comme ça pour correspondre à eSET_TYPE
    PTR_TEXTURE = 0,
    PTR_QUAD = 1, //
    PTR_SPRITE = 2, //
    PTR_PARTICLES = 3, //
    PTR_BMP_TEXT = 4, //
    PTR_SPRITE_SET = 5,
    PTR_ANIMATION = 6,
    PTR_SHADER = 7,
    PTR_BMP_FONT = 8,
    PTR_TEXTURE_MAP = 9,
    PTR_MULTISET = 10
};

inline int		mem_init (unsigned int num_types);
inline void	    mem_clean ();

inline void*	mem_alloc (size_t size, unsigned int type);
inline int		mem_exists (void* ptr, unsigned int type);
inline int		mem_free (void* ptr, unsigned int type);
inline int		mem_type_get_size (unsigned int type);

#endif // __MEM_H__
