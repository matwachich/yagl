#ifndef __ALL_H__
#define __ALL_H__


#ifdef BUILD_DLL
    #define YAGL_API __declspec(dllexport)
#endif

#ifdef BUILD_LIB
    #define YAGL_API
#endif

#ifndef YAGL_API
    #define YAGL_API __declspec(dllimport)
#endif

//#define YAGL_ADVANCED_COLLISIONS

/* -------------------------------------------------------------------------- */
/* External libs */

#include "glfw.h"
#include "ini.h"
#include "mem.h"
//#include "set.h" included by internal.h
#include "soil.h"

/* -------------------------------------------------------------------------- */
/* Color macros */

/**
    \addtogroup 203_consts_color
    @{
*/

/** \brief Convert RGBA color components ([0,255]) to a #YAGL_Color
 *
 * \param r Red
 * \param g Green
 * \param b Blue
 * \param a Alpha
 *
 * \return #YAGL_Color
 */
#define YAGL_RGBA(r, g, b, a) ((a) << 24 | (b) << 16 | (g) << 8 | (r) )

/** \brief Extracts the Red component ([0,255]) from a YAGL_Color */
#define YAGL_RGBA_R(u) (((u) >> 0)  & 0x000000FF)

/** \brief Extracts the Green component ([0,255]) from a YAGL_Color */
#define YAGL_RGBA_G(u) (((u) >> 8)  & 0x000000FF)

/** \brief Extracts the Blue component ([0,255]) from a YAGL_Color */
#define YAGL_RGBA_B(u) (((u) >> 16) & 0x000000FF)

/** \brief Extracts the Alpha component ([0,255]) from a YAGL_Color */
#define YAGL_RGBA_A(u) (((u) >> 24) & 0x000000FF)

/* -------------------------------------------------------------------------- */
/* Data types */

/** \brief An unsigned integer representing a RGBA Color (see YAGL_RGBA).
 */
typedef unsigned int    YAGL_Color;

/**
    @}
*/

/* -------------------------------------------------------------------------- */
/* Constants */

/**
    \addtogroup 200_consts_enums
    @{
*/

/**
    \addtogroup 202_consts_key_mouse
    @{
*/

/* Keyboard key definitions: 8-bit ISO-8859-1 (Latin 1) encoding is used
 * for printable keys (such as A-Z, 0-9 etc), and values above 256
 * represent special (non-printable) keys (e.g. F1, Page Up etc).
 */
/** . */ #define YAGL_KEY_UNKNOWN      -1
/** . */ #define YAGL_KEY_SPACE        32
/** . */ #define YAGL_KEY_SPECIAL      256
/** . */ #define YAGL_KEY_ESC          (YAGL_KEY_SPECIAL+1)
/** . */ #define YAGL_KEY_F1           (YAGL_KEY_SPECIAL+2)
/** . */ #define YAGL_KEY_F2           (YAGL_KEY_SPECIAL+3)
/** . */ #define YAGL_KEY_F3           (YAGL_KEY_SPECIAL+4)
/** . */ #define YAGL_KEY_F4           (YAGL_KEY_SPECIAL+5)
/** . */ #define YAGL_KEY_F5           (YAGL_KEY_SPECIAL+6)
/** . */ #define YAGL_KEY_F6           (YAGL_KEY_SPECIAL+7)
/** . */ #define YAGL_KEY_F7           (YAGL_KEY_SPECIAL+8)
/** . */ #define YAGL_KEY_F8           (YAGL_KEY_SPECIAL+9)
/** . */ #define YAGL_KEY_F9           (YAGL_KEY_SPECIAL+10)
/** . */ #define YAGL_KEY_F10          (YAGL_KEY_SPECIAL+11)
/** . */ #define YAGL_KEY_F11          (YAGL_KEY_SPECIAL+12)
/** . */ #define YAGL_KEY_F12          (YAGL_KEY_SPECIAL+13)
/** . */ #define YAGL_KEY_F13          (YAGL_KEY_SPECIAL+14)
/** . */ #define YAGL_KEY_F14          (YAGL_KEY_SPECIAL+15)
/** . */ #define YAGL_KEY_F15          (YAGL_KEY_SPECIAL+16)
/** . */ #define YAGL_KEY_F16          (YAGL_KEY_SPECIAL+17)
/** . */ #define YAGL_KEY_F17          (YAGL_KEY_SPECIAL+18)
/** . */ #define YAGL_KEY_F18          (YAGL_KEY_SPECIAL+19)
/** . */ #define YAGL_KEY_F19          (YAGL_KEY_SPECIAL+20)
/** . */ #define YAGL_KEY_F20          (YAGL_KEY_SPECIAL+21)
/** . */ #define YAGL_KEY_F21          (YAGL_KEY_SPECIAL+22)
/** . */ #define YAGL_KEY_F22          (YAGL_KEY_SPECIAL+23)
/** . */ #define YAGL_KEY_F23          (YAGL_KEY_SPECIAL+24)
/** . */ #define YAGL_KEY_F24          (YAGL_KEY_SPECIAL+25)
/** . */ #define YAGL_KEY_F25          (YAGL_KEY_SPECIAL+26)
/** . */ #define YAGL_KEY_UP           (YAGL_KEY_SPECIAL+27)
/** . */ #define YAGL_KEY_DOWN         (YAGL_KEY_SPECIAL+28)
/** . */ #define YAGL_KEY_LEFT         (YAGL_KEY_SPECIAL+29)
/** . */ #define YAGL_KEY_RIGHT        (YAGL_KEY_SPECIAL+30)
/** . */ #define YAGL_KEY_LSHIFT       (YAGL_KEY_SPECIAL+31)
/** . */ #define YAGL_KEY_RSHIFT       (YAGL_KEY_SPECIAL+32)
/** . */ #define YAGL_KEY_LCTRL        (YAGL_KEY_SPECIAL+33)
/** . */ #define YAGL_KEY_RCTRL        (YAGL_KEY_SPECIAL+34)
/** . */ #define YAGL_KEY_LALT         (YAGL_KEY_SPECIAL+35)
/** . */ #define YAGL_KEY_RALT         (YAGL_KEY_SPECIAL+36)
/** . */ #define YAGL_KEY_TAB          (YAGL_KEY_SPECIAL+37)
/** . */ #define YAGL_KEY_ENTER        (YAGL_KEY_SPECIAL+38)
/** . */ #define YAGL_KEY_BACKSPACE    (YAGL_KEY_SPECIAL+39)
/** . */ #define YAGL_KEY_INSERT       (YAGL_KEY_SPECIAL+40)
/** . */ #define YAGL_KEY_DEL          (YAGL_KEY_SPECIAL+41)
/** . */ #define YAGL_KEY_PAGEUP       (YAGL_KEY_SPECIAL+42)
/** . */ #define YAGL_KEY_PAGEDOWN     (YAGL_KEY_SPECIAL+43)
/** . */ #define YAGL_KEY_HOME         (YAGL_KEY_SPECIAL+44)
/** . */ #define YAGL_KEY_END          (YAGL_KEY_SPECIAL+45)
/** . */ #define YAGL_KEY_KP_0         (YAGL_KEY_SPECIAL+46)
/** . */ #define YAGL_KEY_KP_1         (YAGL_KEY_SPECIAL+47)
/** . */ #define YAGL_KEY_KP_2         (YAGL_KEY_SPECIAL+48)
/** . */ #define YAGL_KEY_KP_3         (YAGL_KEY_SPECIAL+49)
/** . */ #define YAGL_KEY_KP_4         (YAGL_KEY_SPECIAL+50)
/** . */ #define YAGL_KEY_KP_5         (YAGL_KEY_SPECIAL+51)
/** . */ #define YAGL_KEY_KP_6         (YAGL_KEY_SPECIAL+52)
/** . */ #define YAGL_KEY_KP_7         (YAGL_KEY_SPECIAL+53)
/** . */ #define YAGL_KEY_KP_8         (YAGL_KEY_SPECIAL+54)
/** . */ #define YAGL_KEY_KP_9         (YAGL_KEY_SPECIAL+55)
/** . */ #define YAGL_KEY_KP_DIVIDE    (YAGL_KEY_SPECIAL+56)
/** . */ #define YAGL_KEY_KP_MULTIPLY  (YAGL_KEY_SPECIAL+57)
/** . */ #define YAGL_KEY_KP_SUBTRACT  (YAGL_KEY_SPECIAL+58)
/** . */ #define YAGL_KEY_KP_ADD       (YAGL_KEY_SPECIAL+59)
/** . */ #define YAGL_KEY_KP_DECIMAL   (YAGL_KEY_SPECIAL+60)
/** . */ #define YAGL_KEY_KP_EQUAL     (YAGL_KEY_SPECIAL+61)
/** . */ #define YAGL_KEY_KP_ENTER     (YAGL_KEY_SPECIAL+62)
/** . */ #define YAGL_KEY_KP_NUM_LOCK  (YAGL_KEY_SPECIAL+63)
/** . */ #define YAGL_KEY_CAPS_LOCK    (YAGL_KEY_SPECIAL+64)
/** . */ #define YAGL_KEY_SCROLL_LOCK  (YAGL_KEY_SPECIAL+65)
/** . */ #define YAGL_KEY_PAUSE        (YAGL_KEY_SPECIAL+66)
/** . */ #define YAGL_KEY_LSUPER       (YAGL_KEY_SPECIAL+67)
/** . */ #define YAGL_KEY_RSUPER       (YAGL_KEY_SPECIAL+68)
/** . */ #define YAGL_KEY_MENU         (YAGL_KEY_SPECIAL+69)
/** . */ #define YAGL_KEY_LAST         YAGL_KEY_MENU

/* Mouse button definitions */
/** . */ #define YAGL_MOUSE_BUTTON_1      0
/** . */ #define YAGL_MOUSE_BUTTON_2      1
/** . */ #define YAGL_MOUSE_BUTTON_3      2
/** . */ #define YAGL_MOUSE_BUTTON_4      3
/** . */ #define YAGL_MOUSE_BUTTON_5      4
/** . */ #define YAGL_MOUSE_BUTTON_6      5
/** . */ #define YAGL_MOUSE_BUTTON_7      6
/** . */ #define YAGL_MOUSE_BUTTON_8      7
/** . */ #define YAGL_MOUSE_BUTTON_LAST   YAGL_MOUSE_BUTTON_8

/* Mouse button aliases */
/** . */ #define YAGL_MOUSE_BUTTON_LEFT   YAGL_MOUSE_BUTTON_1
/** . */ #define YAGL_MOUSE_BUTTON_RIGHT  YAGL_MOUSE_BUTTON_2
/** . */ #define YAGL_MOUSE_BUTTON_MIDDLE YAGL_MOUSE_BUTTON_3

/**
    @}
*/

/**
    \addtogroup 203_consts_color
    @{
*/

/* Colors */
/** . */ #define YAGL_COLOR_BLACK    0xFF000000
/** . */ #define YAGL_COLOR_MAROON   0xFF000080
/** . */ #define YAGL_COLOR_GREEN    0xFF008000
/** . */ #define YAGL_COLOR_OLIVE    0xFF008080
/** . */ #define YAGL_COLOR_NAVY     0xFF800000
/** . */ #define YAGL_COLOR_PURPLE   0xFF800080
/** . */ #define YAGL_COLOR_TEAL     0xFF808000
/** . */ #define YAGL_COLOR_SILVER   0xFFCECECE
/** . */ #define YAGL_COLOR_GRAY     0xFF808080
/** . */ #define YAGL_COLOR_RED      0xFF0000FF
/** . */ #define YAGL_COLOR_LIME     0xFF00FF00
/** . */ #define YAGL_COLOR_YELLOW   0xFF00FFFF
/** . */ #define YAGL_COLOR_BLUE     0xFFFF0000
/** . */ #define YAGL_COLOR_FUSCHIA  0xFFFF00FF
/** . */ #define YAGL_COLOR_MAGENTA  YAGL_COLOR_FUSCHIA
/** . */ #define YAGL_COLOR_AQUA     0xFFFFFF00
/** . */ #define YAGL_COLOR_CYAN     YAGL_COLOR_AQUA
/** . */ #define YAGL_COLOR_WHITE    0xFFFFFFFF

/** . */ #define YAGL_COLOR_BLACK_A128   0x80000000
/** . */ #define YAGL_COLOR_MAROON_A128  0x80000080
/** . */ #define YAGL_COLOR_GREEN_A128   0x80008000
/** . */ #define YAGL_COLOR_OLIVE_A128   0x80008080
/** . */ #define YAGL_COLOR_NAVY_A128    0x80800000
/** . */ #define YAGL_COLOR_PURPLE_A128  0x80800080
/** . */ #define YAGL_COLOR_TEAL_A128    0x80808000
/** . */ #define YAGL_COLOR_SILVER_A128  0x80CECECE
/** . */ #define YAGL_COLOR_GRAY_A128    0x80808080
/** . */ #define YAGL_COLOR_RED_A128     0x800000FF
/** . */ #define YAGL_COLOR_LIME_A128    0x8000FF00
/** . */ #define YAGL_COLOR_YELLOW_A128  0x8000FFFF
/** . */ #define YAGL_COLOR_BLUE_A128    0x80FF0000
/** . */ #define YAGL_COLOR_FUSCHIA_A128 0x80FF00FF
/** . */ #define YAGL_COLOR_MAGENTA_A128 YAGL_COLOR_FUSCHIA_A128
/** . */ #define YAGL_COLOR_AQUA_A128    0x80FFFF00
/** . */ #define YAGL_COLOR_CYAN_A128    YAGL_COLOR_AQUA_A128
/** . */ #define YAGL_COLOR_WHITE_A128   0x80FFFFFF

/**
    @}
*/

/**
    \addtogroup 204_consts_ogltex
    @{
*/

/* OpenGL texture parameters (for Texture_SetParameter) */
/** . */ #define YAGL_TEXTURE_MIN_FILTER			0x2801
/** . */ #define YAGL_TEXTURE_MAG_FILTER			0x2800
/** . */ #define YAGL_TEXTURE_WRAP_S				0x2802
/** . */ #define YAGL_TEXTURE_WRAP_T				0x2803
/** . */ #define YAGL_GL_NEAREST                 0x2600
/** . */ #define YAGL_GL_LINEAR                  0x2601
/** . */ #define YAGL_GL_NEAREST_MIPMAP_NEAREST  0x2700
/** . */ #define YAGL_GL_LINEAR_MIPMAP_NEAREST   0x2701
/** . */ #define YAGL_GL_NEAREST_MIPMAP_LINEAR   0x2702
/** . */ #define YAGL_GL_LINEAR_MIPMAP_LINEAR    0x2703
/** . */ #define YAGL_GL_CLAMP                   0x2900
/** . */ #define YAGL_GL_REPEAT                  0x2901

/**
    @}
*/

/* -------------------------------------------------------------------------- */
/* Enumerations */

/**
    \addtogroup 201_enums
    @{
*/

/** \brief Select debug informations output mode
 *
 * Passed to System_Init()
 */
enum eDEBUG {
	DEBUG_OFF = 0,  /**< No debug output */
	DEBUG_ON_STD,   /**< Output to standard output (stdout) */
	DEBUG_ON_FILE   /**< Output to a file */
};
typedef enum eDEBUG eDEBUG;


/** \brief Passed to System_GetVersion()
 */
enum eVERSION {
	VERSION_YAGL = 0,   /**< Engine version */
	VERSION_GLFW,       /**< GLFW version */
	VERSION_OGL         /**< OpenGL version */
};
typedef enum eVERSION eVERSION;


/** \brief Passed to Window_Capture()
 */
enum eCAPTURE_TYPE {
	CAPTURE_TGA = 0,    /**< Screen capture in TGA format */
	CAPTURE_BMP,        /**< Screen capture in BMP format */
	CAPTURE_DDS         /**< Screen capture in DDS format */
};
typedef enum eCAPTURE_TYPE eCAPTURE_TYPE;


/** \brief Passed to Events_SetMousePosMode()
 *
 * This function determines how the mouse position is returned by Event_MouseGetPos(), and how it is
 * passed to YAGLMousePosProc
 *
 * MOUSE_POS_WORLD_RELATIVE is the default
 *
 */
enum eMOUSE_POS_MODE {
	MOUSE_POS_WIN_RELATIVE = 0, /**< Relative to the client area of the window */
	MOUSE_POS_WORLD_RELATIVE    /**< Relative to the displayed world (takes care of view modifications) */
};
typedef enum eMOUSE_POS_MODE eMOUSE_POS_MODE;


/** \brief Specify how a texture is loaded (see Texture_Create(), Texture_CreateFromMem(), Texture_Load(), Texture_LoadFromMem())
 */
enum eTEXTURE_CHANNELS {
    TEXTURE_CHANNELS_AUTO = 0,  /**<  */
	TEXTURE_CHANNELS_LUM,       /**<  */
	TEXTURE_CHANNELS_LUMALPHA,  /**<  */
	TEXTURE_CHANNELS_RGB,       /**<  */
	TEXTURE_CHANNELS_RGBA       /**<  */
};
typedef enum eTEXTURE_CHANNELS eTEXTURE_CHANNELS;


/** \brief Select blending/bliting mode
 */
enum eBLEND_MODE {
    BLEND_NO_CHANGE = -1,   /**< No change */
	BLEND_BLACK = 0,        /**< Black color blit */
	BLEND_SOLID,            /**< Solid blit */
	BLEND_TRANS,            /**< Transparent blit */
	BLEND_ALPHA,            /**< Alpha Transparent blit */
	BLEND_BLENDED,          /**< Alpha blended blit */
	BLEND_GLOW              /**< Additive blended blit */
};
typedef enum eBLEND_MODE eBLEND_MODE;


/** \brief Set the center of a Quad/Sprite
 */
enum eCENTER {
	CENTER_CENTER = 0,  /**< Centered */
	CENTER_ULEFT,       /**< Upper-left corner */
	CENTER_URIGHT,      /**< Upper-right corner */
	CENTER_BLEFT,       /**< Bottom-left corner */
	CENTER_BRIGHT,      /**< Bottom-right corner */
	CENTER_CLEFT,       /**< Center left */
	CENTER_CRIGHT,      /**< Center right */
	CENTER_CUP,         /**< Center up */
	CENTER_CBOTTOM      /**< Center bottom */
};
typedef enum eCENTER eCENTER;


/** \brief Passed to Sprite_SetShape()
 */
enum eSHAPE {
	SHAPE_NONE = 0, /**< No shape, no collision */
	SHAPE_POINT,    /**< A point */
	SHAPE_CIRCLE,   /**< A circle */
	SHAPE_RECT      /**< A rectangle (AABB) */
};
typedef enum eSHAPE eSHAPE;


/** \brief Used to set text alignement for BmpFont_Print(), BmpFont_PrintLines() and BmpText_SetAlign()
 */
enum eALIGN {
	ALIGN_LEFT = 0, /**< Left aligned (default) */
	ALIGN_CENTER,   /**< Centered */
	ALIGN_RIGHT     /**< Right aligned */
};
typedef enum eALIGN eALIGN;


/** \brief Used to define the MultiSet's data type of it's elements
 */
enum eSET_TYPE {
    SET_TYPE_ANY = 0,   /**< No type specified */
    SET_TYPE_QUAD,      /**< Quad */
    SET_TYPE_SPRITE,    /**< Sprite */
    SET_TYPE_PEMITTER,  /**< Particles Emitter */
    SET_TYPE_BMPTEXT,   /**< Bitmap Text */
};
typedef enum eSET_TYPE eSET_TYPE;


/** \brief Passed to Shader_AddSource()
 */
enum eSHADER_TYPE {
    SHADER_VERTEX,  /**< Vertex shader */
    SHADER_FRAGMENT /**< Fragment/Pixel shader */
};
typedef enum eSHADER_TYPE eSHADER_TYPE;

/** \brief Return by Shader_UniformGetActive() (see documentation of glUniformGetActive)
 */
enum eSHADER_UNIFORM_TYPE {
    YAGL_GL_FLOAT = 0x1406,
	YAGL_GL_FLOAT_VEC2 = 0x8B50,
	YAGL_GL_FLOAT_VEC3 = 0x8B51,
	YAGL_GL_FLOAT_VEC4 = 0x8B52,
	YAGL_GL_INT = 0x1404,
	YAGL_GL_INT_VEC2 = 0x8B53,
	YAGL_GL_INT_VEC3 = 0x8B54,
	YAGL_GL_INT_VEC4 = 0x8B55,
	YAGL_GL_BOOL = 0x8B56,
	YAGL_GL_BOOL_VEC2 = 0x8B57,
	YAGL_GL_BOOL_VEC3 = 0x8B58,
	YAGL_GL_BOOL_VEC4 = 0x8B59,
	YAGL_GL_FLOAT_MAT2 = 0x8B5A,
	YAGL_GL_FLOAT_MAT3 = 0x8B5B,
	YAGL_GL_FLOAT_MAT4 = 0x8B5C,
	YAGL_GL_FLOAT_MAT2x3 = 0x8B65,
	YAGL_GL_FLOAT_MAT2x4 = 0x8B66,
	YAGL_GL_FLOAT_MAT3x2 = 0x8B67,
	YAGL_GL_FLOAT_MAT3x4 = 0x8B68,
	YAGL_GL_FLOAT_MAT4x2 = 0x8B69,
	YAGL_GL_FLOAT_MAT4x3 = 0x8B6A,
	YAGL_GL_SAMPLER_1D = 0x8B5D,
	YAGL_GL_SAMPLER_2D = 0x8B5E,
	YAGL_GL_SAMPLER_3D = 0x8B5F,
	YAGL_GL_SAMPLER_CUBE = 0x8B60,
	YAGL_GL_SAMPLER_1D_SHADOW = 0x8B61,
	YAGL_GL_SAMPLER_2D_SHADOW = 0x8B62
};
typedef enum eSHADER_UNIFORM_TYPE eSHADER_UNIFORM_TYPE;

/**
    @}
*/

/**
    @}
*/

/* -------------------------------------------------------------------------- */
/* Data types */

typedef struct Texture Texture;
typedef struct TextureMap TextureMap;
typedef struct Quad Quad;
typedef struct Sprite Sprite;
typedef struct SpriteSet SpriteSet;
typedef struct PEmitter PEmitter;
typedef struct Shader Shader;
typedef struct BmpFont BmpFont;
typedef struct BmpText BmpText;
typedef struct Animation Animation;
typedef struct MultiSet MultiSet;

/* -------------------------------------------------------------------------- */
/* Callbacks */

/**
    \addtogroup 210_callbacks
    @{
*/

/** \brief
 *
 */
typedef int(*YAGLRenderProc)(float dt);

/** \brief
 *
 */
typedef int(*YAGLFrameProc)(float dt);

/** \brief Called when debug data is outputed (see System_SetDebugCallback())
 *
 * \param data[in] NULL-terminated string
 * \param err_lvl[in] Error level (see System_DebugOut())
 */
typedef void(*YAGLDebugProc)(char* text, int err_lvl);

/** \brief Called on window close attempt (see Window_SetCloseCallback())
 *
 * \return 1 to close the window, 0 to cancel window closing
 */
typedef int(*YAGLWinCloseProc)();

/** \brief Called on window resize (see Window_SetResizeCallback())
 *
 * \param width[in] New window width
 * \param height[in] New window height
 */
typedef void(*YAGLWinSizeProc)(int w, int h);

/** \brief Called when the window client area needs to be refreshed (see Window_SetRefreshCallback())
 */
typedef void(*YAGLWinRefreshProc)();

/** \brief Called when the mouse position changes (see Events_SetMousePosCallback())
 *
 * The mouse position is reported according to #eMOUSE_POS_MODE (see Events_SetMousePosMode())
 *
 * \param x[in] X mouse pos
 * \param y[in] Y mouse pos
 */
typedef void(*YAGLMousePosProc)(int x, int y);

/** \brief Called when a mouse button is pressed/released (see Events_SetMouseButtonCallback)
 *
 * \param button[in] Mouse button identifier (see #202_consts_key_mouse)
 * \param event[in] 1 if pressed, 0 if released
 */
typedef void(*YAGLMouseButtonProc)(int button, int event);

/** \brief Called on mouse wheel event (see Events_SetMouseWheelCallback())
 *
 * \param pos[in] Wheel position
 */
typedef void(*YAGLMouseWheelProc)(int pos);

/** \brief Called on key press/release (see Events_SetKeyCallback())
 *
 * \param key[in] Upper-case ISO 8859-1 or special key identifier (see #202_consts_key_mouse)
 * \param event[in] 1 if pressed, 0 if released
 */
typedef void(*YAGLKeyProc)(int key, int event);

/** \brief Called when a printable caracter is generated by the keyboard (see Events_SetCharCallback())
 *
 * \param key[in] Unicode (ISO 10646) caracter
 * \param event[in] 1 if pressed, 0 if released
 */
typedef void(*YAGLCharProc)(int key, int event);

/** \brief Called when a Particle is spawned by a Particles Emitter
 *
 * \param emit[in] Particle Emitter
 * \param event[in] 1 if spawn, 0 if dead
 * \param x[in] X-pos of the new particle
 * \param y[in] Y-pos of the new particle
 */
typedef void(*YAGLParticleSpawnProc)(PEmitter* emit, int event, int x, int y);

/** \brief Called when a Particle is dead
 *
 * \param emit[in] Particle Emitter
 * \param event[in] 1 if spawn, 0 if dead
 * \param x[in] X-pos of the new particle
 * \param y[in] Y-pos of the new particle
 */
typedef void(*YAGLParticleDeadProc)(PEmitter* emit, int event, int x, int y);

/** \brief
 *
 */
typedef int(*YAGLSpriteSetIterateProc)(SpriteSet* sprset, Sprite* spr, void* user_data);

/** \brief
 *
 */
typedef int(*YAGLMultiSetIterateProc)(MultiSet* ms, void* elem, void* user_data, int elem_rank, eSET_TYPE ms_type);

/** \brief Called when a collision occures between 2 Sprites.
 *
 * Collision auto-process must be true (Collision_SetAutoProcess()) or you must manually call
 * Collision_Process() in order for this callback to be called.
 *
 * \param spr1[in] Sprite
 * \param spr2[in] Sprite
 */
typedef void(*YAGLCollisionProc)(Sprite* spr1, Sprite* spr2);

/**
    @}
*/

/* -------------------------------------------------------------------------- */
/* Data Types */

typedef struct VectI VectI;
struct VectI {
	int x, y;
};

typedef struct VectF VectF;
struct VectF {
	float x, y;
};

typedef struct RectI RectI;
struct RectI {
	int x, y, w, h;
};

typedef struct RectF RectF;
struct RectF {
	float x, y, w, h;
};

struct Texture {
    unsigned int tex_id;
    int width, height;
};

typedef struct TextureMapElem TextureMapElem;
struct TextureMapElem {
    float x, y, w, h;
    TextureMapElem* next;
};

struct TextureMap {
    Texture* tex;

    int count;
    TextureMapElem* first;
    TextureMapElem* last;
};

struct Quad {
    int visible;
    Texture* tex;
	float tex_rect_1[2], tex_rect_2[2], tex_rect_3[2], tex_rect_4[2];
	YAGL_Color color;
	VectF pos, size, center;
	eCENTER center_enum;
	float angle;
	eBLEND_MODE blend_mode;
	VectI flip;
	void* data;
};

typedef struct AnimFrame AnimFrame;
struct AnimFrame {
    int is_set;

    Texture* tex;
    float tex_rect_1[2], tex_rect_2[2], tex_rect_3[2], tex_rect_4[2];

    YAGL_Color color; // -1 = no change
    eBLEND_MODE blend_mode; // -1 = no change

    int change_size;
    VectF size;

    float duration;
};

struct Animation {
    AnimFrame* frames;
    unsigned int frame_max;
    unsigned int frame_count;
    float timer_mult;
};

struct Sprite {
    int visible, dynamic;
	Texture* tex;
	float tex_rect_1[2], tex_rect_2[2], tex_rect_3[2], tex_rect_4[2];
	YAGL_Color color;
	VectF pos, size, center;
	eCENTER center_enum;
	float angle;
	eBLEND_MODE blend_mode;
	VectI flip;
	//
	VectF vel, accel;
	float vel_max, innertia;
	float a_vel, a_accel, a_vel_max, a_innertia;
	Sprite* tutor_vel;
	Sprite* tutor_avel;
	//
	eSHAPE shape_type;
	VectF shape_pos;
	VectF shape_size;
	int collision_mask, collision_group;
	//
	Animation* anim;
	unsigned int anim_start_frame;
	unsigned int anim_frame;
	int anim_status;
	int anim_loop;
	double anim_timer;
	float anim_timer_mult;
	//
	void* data;
};

typedef struct SpriteSetElem SpriteSetElem;
struct SpriteSetElem {
    Sprite* spr;
    SpriteSetElem* next;
};

struct SpriteSet {
    SpriteSetElem* first;
    unsigned int count;
};

typedef struct Particle Particle;
struct Particle {
    Texture* tex;
	float tex_rect_1[2], tex_rect_2[2], tex_rect_3[2], tex_rect_4[2];

	VectF pos, vel, accel, force;

    float innertia;
	float angle, size, size_var;
	float spin, spin_var;

	float life;

	eBLEND_MODE blend_mode;
	unsigned char col_r, col_g, col_b, col_a;
	short col_r_var, col_g_var, col_b_var, col_a_var;

	int kill_me;
	double life_timer;

	Particle* _next;
};

struct PEmitter {
    int visible;
    int active; // Emitter active

	// Texture
	Texture* tex;
	float tex_rect_1[2], tex_rect_2[2], tex_rect_3[2], tex_rect_4[2];

	// Dynamics
	VectF pos, pos_var;
	float vel, vel_var;
	float accel, accel_var;
	float angle, angle_var;

	float force, force_var;
	float force_angle, force_angle_var;

    float p_innertia, p_innertia_var;
    float p_angle, p_angle_var;
	float spin, spin_var, spin_flyvar;

	// Size
	float size, size_var, size_flyvar;

	// Life time
	float life, life_var;

	// Emitte Speed
	unsigned int p_per_sec;

	// Maximum particles number
	unsigned int max_particles;

	// Blend Mode
	eBLEND_MODE blend_mode;

	// Color
	unsigned char col_r, col_g, col_b, col_a;
	short col_r_var, col_g_var, col_b_var, col_a_var;
	short col_r_flyvar, col_g_flyvar, col_b_flyvar, col_a_flyvar;

	// Callbacks
	YAGLParticleSpawnProc p_emitte_proc;
	YAGLParticleDeadProc p_dead_proc;

	// WARNING: Internal use only
	double emitte_timer;
	Particle* first;
	unsigned int count; // You can acces it, but avoid modification
};

// Utilisé pour le chargement de configuration à partir d'un .ini
typedef struct PEmitterAndSection PEmitterAndSection;
struct PEmitterAndSection {
    PEmitter* emit;
    char* section;
    int load_tex_rect;
};

struct Shader {
    int ready;
    GLuint program;
};

typedef struct Char Char;
struct Char {
    unsigned char id;
    int advance;
};

struct BmpFont {
    unsigned int texture;
    int texture_w, texture_h;

	unsigned int display_lists_base;

	Char* chrs;

	char* face_name;
	int chars_count;
	int size, line_height, line_base;
};

struct BmpText {
    int visible;
    char* text;
	BmpFont* font;
	int size;
	int multiligne;
	VectI pos;
    eALIGN align;
	float angle;
	YAGL_Color color;
	eBLEND_MODE blend_mode;
};

typedef struct MultiSetElem MultiSetElem;
struct MultiSetElem {
    void* data;
    int rank;
    MultiSetElem* next;
};

struct MultiSet {
    unsigned int count;
    eSET_TYPE type;
    int check_data_type;

    //int(*DestroyFunc)(void*);
    //void(*DrawFunc)(void*);
    //void(*SetColorFunc)(void*,unsigned char,unsigned char,unsigned char,unsigned char);
    //void(*SetColorExFunc)(void*,YAGL_Color);
    //void(*SetBlendModeFunc)(void*,eBLEND_MODE);
    //void(*SetVisibleFunc)(void*,int);

    MultiSetElem* first;
    MultiSetElem* last;
};

/*
typedef struct StrTableElem StrTableElem;
struct StrTableElem {
    char* section;
    char* key;
    char* data;
    StrTableElem* next;
};

typedef struct StrTable StrTable;
struct Strtable {
    int count;
    StrTableElem* first;
};
*/

/* -------------------------------------------------------------------------- */

#include "internal.h"

#include "system.h"
#include "window.h"
#include "render.h"
#include "view.h"
#include "events.h"
#include "misc.h"
#include "texture.h"
#include "texture_map.h"
#include "quad.h"
#include "sprite.h"
#include "sprite_set.h"
#include "animation.h"
#include "collision.h"
#include "particle.h"
#include "shader.h"
#include "draw.h"
#include "geometry.h"
#include "font.h"
#include "text.h"

#include "accessors_quad.h"
#include "accessors_sprite.h"
#include "accessors_pemitter.h"
#include "accessors_bmptext.h"

#endif // __ALL_H__
