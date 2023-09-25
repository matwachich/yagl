/*
	Copyright (c) 2012 matwachich@gmail.com

	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including without limitation
	the rights to use, copy, modify, merge, publish, distribute, sublicense,
	and/or sell copies of the Software, and to permit persons to whom
	the Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included
	in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
	DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
	TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
	THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/* YAGL (Yet Another Game Library) Main header */

#ifndef __YAGL_H__
#define __YAGL_H__

#define YAGL_API __declspec(dllimport)

/*** ---------------------------------------------------------------------- ***/
/*** Color macros ***/

#define YAGL_RGBA(r, g, b, a) ((a) << 24 | (b) << 16 | (g) << 8 | (r) )

#define YAGL_RGBA_R(u) (((u) >> 0)  & 0x000000FF)
#define YAGL_RGBA_G(u) (((u) >> 8)  & 0x000000FF)
#define YAGL_RGBA_B(u) (((u) >> 16) & 0x000000FF)
#define YAGL_RGBA_A(u) (((u) >> 24) & 0x000000FF)

/*** ---------------------------------------------------------------------- ***/
/*** Data types ***/

typedef unsigned int    YAGL_Color;

/*** ---------------------------------------------------------------------- ***/
/*** Constants ***/

/* Keyboard key definitions: 8-bit ISO-8859-1 (Latin 1) encoding is used
 * for printable keys (such as A-Z, 0-9 etc), and values above 256
 * represent special (non-printable) keys (e.g. F1, Page Up etc).
 */
#define YAGL_KEY_UNKNOWN      -1
#define YAGL_KEY_SPACE        32
#define YAGL_KEY_SPECIAL      256
#define YAGL_KEY_ESC          (YAGL_KEY_SPECIAL+1)
#define YAGL_KEY_F1           (YAGL_KEY_SPECIAL+2)
#define YAGL_KEY_F2           (YAGL_KEY_SPECIAL+3)
#define YAGL_KEY_F3           (YAGL_KEY_SPECIAL+4)
#define YAGL_KEY_F4           (YAGL_KEY_SPECIAL+5)
#define YAGL_KEY_F5           (YAGL_KEY_SPECIAL+6)
#define YAGL_KEY_F6           (YAGL_KEY_SPECIAL+7)
#define YAGL_KEY_F7           (YAGL_KEY_SPECIAL+8)
#define YAGL_KEY_F8           (YAGL_KEY_SPECIAL+9)
#define YAGL_KEY_F9           (YAGL_KEY_SPECIAL+10)
#define YAGL_KEY_F10          (YAGL_KEY_SPECIAL+11)
#define YAGL_KEY_F11          (YAGL_KEY_SPECIAL+12)
#define YAGL_KEY_F12          (YAGL_KEY_SPECIAL+13)
#define YAGL_KEY_F13          (YAGL_KEY_SPECIAL+14)
#define YAGL_KEY_F14          (YAGL_KEY_SPECIAL+15)
#define YAGL_KEY_F15          (YAGL_KEY_SPECIAL+16)
#define YAGL_KEY_F16          (YAGL_KEY_SPECIAL+17)
#define YAGL_KEY_F17          (YAGL_KEY_SPECIAL+18)
#define YAGL_KEY_F18          (YAGL_KEY_SPECIAL+19)
#define YAGL_KEY_F19          (YAGL_KEY_SPECIAL+20)
#define YAGL_KEY_F20          (YAGL_KEY_SPECIAL+21)
#define YAGL_KEY_F21          (YAGL_KEY_SPECIAL+22)
#define YAGL_KEY_F22          (YAGL_KEY_SPECIAL+23)
#define YAGL_KEY_F23          (YAGL_KEY_SPECIAL+24)
#define YAGL_KEY_F24          (YAGL_KEY_SPECIAL+25)
#define YAGL_KEY_F25          (YAGL_KEY_SPECIAL+26)
#define YAGL_KEY_UP           (YAGL_KEY_SPECIAL+27)
#define YAGL_KEY_DOWN         (YAGL_KEY_SPECIAL+28)
#define YAGL_KEY_LEFT         (YAGL_KEY_SPECIAL+29)
#define YAGL_KEY_RIGHT        (YAGL_KEY_SPECIAL+30)
#define YAGL_KEY_LSHIFT       (YAGL_KEY_SPECIAL+31)
#define YAGL_KEY_RSHIFT       (YAGL_KEY_SPECIAL+32)
#define YAGL_KEY_LCTRL        (YAGL_KEY_SPECIAL+33)
#define YAGL_KEY_RCTRL        (YAGL_KEY_SPECIAL+34)
#define YAGL_KEY_LALT         (YAGL_KEY_SPECIAL+35)
#define YAGL_KEY_RALT         (YAGL_KEY_SPECIAL+36)
#define YAGL_KEY_TAB          (YAGL_KEY_SPECIAL+37)
#define YAGL_KEY_ENTER        (YAGL_KEY_SPECIAL+38)
#define YAGL_KEY_BACKSPACE    (YAGL_KEY_SPECIAL+39)
#define YAGL_KEY_INSERT       (YAGL_KEY_SPECIAL+40)
#define YAGL_KEY_DEL          (YAGL_KEY_SPECIAL+41)
#define YAGL_KEY_PAGEUP       (YAGL_KEY_SPECIAL+42)
#define YAGL_KEY_PAGEDOWN     (YAGL_KEY_SPECIAL+43)
#define YAGL_KEY_HOME         (YAGL_KEY_SPECIAL+44)
#define YAGL_KEY_END          (YAGL_KEY_SPECIAL+45)
#define YAGL_KEY_KP_0         (YAGL_KEY_SPECIAL+46)
#define YAGL_KEY_KP_1         (YAGL_KEY_SPECIAL+47)
#define YAGL_KEY_KP_2         (YAGL_KEY_SPECIAL+48)
#define YAGL_KEY_KP_3         (YAGL_KEY_SPECIAL+49)
#define YAGL_KEY_KP_4         (YAGL_KEY_SPECIAL+50)
#define YAGL_KEY_KP_5         (YAGL_KEY_SPECIAL+51)
#define YAGL_KEY_KP_6         (YAGL_KEY_SPECIAL+52)
#define YAGL_KEY_KP_7         (YAGL_KEY_SPECIAL+53)
#define YAGL_KEY_KP_8         (YAGL_KEY_SPECIAL+54)
#define YAGL_KEY_KP_9         (YAGL_KEY_SPECIAL+55)
#define YAGL_KEY_KP_DIVIDE    (YAGL_KEY_SPECIAL+56)
#define YAGL_KEY_KP_MULTIPLY  (YAGL_KEY_SPECIAL+57)
#define YAGL_KEY_KP_SUBTRACT  (YAGL_KEY_SPECIAL+58)
#define YAGL_KEY_KP_ADD       (YAGL_KEY_SPECIAL+59)
#define YAGL_KEY_KP_DECIMAL   (YAGL_KEY_SPECIAL+60)
#define YAGL_KEY_KP_EQUAL     (YAGL_KEY_SPECIAL+61)
#define YAGL_KEY_KP_ENTER     (YAGL_KEY_SPECIAL+62)
#define YAGL_KEY_KP_NUM_LOCK  (YAGL_KEY_SPECIAL+63)
#define YAGL_KEY_CAPS_LOCK    (YAGL_KEY_SPECIAL+64)
#define YAGL_KEY_SCROLL_LOCK  (YAGL_KEY_SPECIAL+65)
#define YAGL_KEY_PAUSE        (YAGL_KEY_SPECIAL+66)
#define YAGL_KEY_LSUPER       (YAGL_KEY_SPECIAL+67)
#define YAGL_KEY_RSUPER       (YAGL_KEY_SPECIAL+68)
#define YAGL_KEY_MENU         (YAGL_KEY_SPECIAL+69)
#define YAGL_KEY_LAST         YAGL_KEY_MENU

/* Mouse button definitions */
#define YAGL_MOUSE_BUTTON_1      0
#define YAGL_MOUSE_BUTTON_2      1
#define YAGL_MOUSE_BUTTON_3      2
#define YAGL_MOUSE_BUTTON_4      3
#define YAGL_MOUSE_BUTTON_5      4
#define YAGL_MOUSE_BUTTON_6      5
#define YAGL_MOUSE_BUTTON_7      6
#define YAGL_MOUSE_BUTTON_8      7
#define YAGL_MOUSE_BUTTON_LAST   YAGL_MOUSE_BUTTON_8

/* Mouse button aliases */
#define YAGL_MOUSE_BUTTON_LEFT   YAGL_MOUSE_BUTTON_1
#define YAGL_MOUSE_BUTTON_RIGHT  YAGL_MOUSE_BUTTON_2
#define YAGL_MOUSE_BUTTON_MIDDLE YAGL_MOUSE_BUTTON_3

/* Colors */
#define YAGL_COLOR_BLACK    0xFF000000
#define YAGL_COLOR_MAROON   0xFF000080
#define YAGL_COLOR_GREEN    0xFF008000
#define YAGL_COLOR_OLIVE    0xFF008080
#define YAGL_COLOR_NAVY     0xFF800000
#define YAGL_COLOR_PURPLE   0xFF800080
#define YAGL_COLOR_TEAL     0xFF808000
#define YAGL_COLOR_SILVER   0xFFCECECE
#define YAGL_COLOR_GRAY     0xFF808080
#define YAGL_COLOR_RED      0xFF0000FF
#define YAGL_COLOR_LIME     0xFF00FF00
#define YAGL_COLOR_YELLOW   0xFF00FFFF
#define YAGL_COLOR_BLUE     0xFFFF0000
#define YAGL_COLOR_FUSCHIA  0xFFFF00FF
#define YAGL_COLOR_MAGENTA  YAGL_COLOR_FUSCHIA
#define YAGL_COLOR_AQUA     0xFFFFFF00
#define YAGL_COLOR_CYAN     YAGL_COLOR_AQUA
#define YAGL_COLOR_WHITE    0xFFFFFFFF

#define YAGL_COLOR_BLACK_A128   0x80000000
#define YAGL_COLOR_MAROON_A128  0x80000080
#define YAGL_COLOR_GREEN_A128   0x80008000
#define YAGL_COLOR_OLIVE_A128   0x80008080
#define YAGL_COLOR_NAVY_A128    0x80800000
#define YAGL_COLOR_PURPLE_A128  0x80800080
#define YAGL_COLOR_TEAL_A128    0x80808000
#define YAGL_COLOR_SILVER_A128  0x80CECECE
#define YAGL_COLOR_GRAY_A128    0x80808080
#define YAGL_COLOR_RED_A128     0x800000FF
#define YAGL_COLOR_LIME_A128    0x8000FF00
#define YAGL_COLOR_YELLOW_A128  0x8000FFFF
#define YAGL_COLOR_BLUE_A128    0x80FF0000
#define YAGL_COLOR_FUSCHIA_A128 0x80FF00FF
#define YAGL_COLOR_MAGENTA_A128 YAGL_COLOR_FUSCHIA_A128
#define YAGL_COLOR_AQUA_A128    0x80FFFF00
#define YAGL_COLOR_CYAN_A128    YAGL_COLOR_AQUA_A128
#define YAGL_COLOR_WHITE_A128   0x80FFFFFF

/* OpenGL texture parameters (for Texture_SetParameter) */
#define YAGL_TEXTURE_MIN_FILTER			0x2801
#define YAGL_TEXTURE_MAG_FILTER			0x2800
#define YAGL_TEXTURE_WRAP_S				0x2802
#define YAGL_TEXTURE_WRAP_T				0x2803
#define YAGL_GL_NEAREST                 0x2600
#define YAGL_GL_LINEAR                  0x2601
#define YAGL_GL_NEAREST_MIPMAP_NEAREST  0x2700
#define YAGL_GL_LINEAR_MIPMAP_NEAREST   0x2701
#define YAGL_GL_NEAREST_MIPMAP_LINEAR   0x2702
#define YAGL_GL_LINEAR_MIPMAP_LINEAR    0x2703
#define YAGL_GL_CLAMP                   0x2900
#define YAGL_GL_REPEAT                  0x2901

/*** ---------------------------------------------------------------------- ***/
/*** Enumerations ***/

enum eDEBUG {
	DEBUG_OFF = 0,
	DEBUG_ON_STD,
	DEBUG_ON_FILE
};
typedef enum eDEBUG eDEBUG;

enum eVERSION {
	VERSION_YAGL = 0,
	VERSION_GLFW,
	VERSION_OGL
};
typedef enum eVERSION eVERSION;

enum eCAPTURE_TYPE {
	CAPTURE_TGA = 0,
	CAPTURE_BMP,
	CAPTURE_DDS
};
typedef enum eCAPTURE_TYPE eCAPTURE_TYPE;

enum eMOUSE_POS_MODE {
	MOUSE_POS_WIN_RELATIVE = 0,
	MOUSE_POS_WORLD_RELATIVE
};
typedef enum eMOUSE_POS_MODE eMOUSE_POS_MODE;

enum eTEXTURE_CHANNELS {
    TEXTURE_CHANNELS_AUTO = 0,
	TEXTURE_CHANNELS_LUM,
	TEXTURE_CHANNELS_LUMALPHA,
	TEXTURE_CHANNELS_RGB,
	TEXTURE_CHANNELS_RGBA
};
typedef enum eTEXTURE_CHANNELS eTEXTURE_CHANNELS;

enum eBLEND_MODE {
    BLEND_NO_CHANGE = -1,
	BLEND_BLACK = 0,
	BLEND_SOLID,
	BLEND_TRANS,
	BLEND_ALPHA,
	BLEND_BLENDED,
	BLEND_GLOW
};
typedef enum eBLEND_MODE eBLEND_MODE;

enum eCENTER {
	CENTER_CENTER = 0,
	CENTER_ULEFT,
	CENTER_URIGHT,
	CENTER_BLEFT,
	CENTER_BRIGHT,
	CENTER_CLEFT,
	CENTER_CRIGHT,
	CENTER_CUP,
	CENTER_CBOTTOM
};
typedef enum eCENTER eCENTER;

enum eSHAPE {
	SHAPE_NONE = 0,
	SHAPE_POINT,
	SHAPE_CIRCLE,
	SHAPE_RECT
};
typedef enum eSHAPE eSHAPE;

enum eALIGN {
	ALIGN_LEFT,
	ALIGN_CENTER,
	ALIGN_RIGHT
};
typedef enum eALIGN eALIGN;

enum eSET_TYPE {
    SET_TYPE_ANY = 0,
    SET_TYPE_QUAD,
    SET_TYPE_SPRITE,
    SET_TYPE_PEMITTER,
    SET_TYPE_BMPTEXT,
};
typedef enum eSET_TYPE eSET_TYPE;

enum eSHADER_TYPE {
    SHADER_VERTEX,
    SHADER_FRAGMENT
};
typedef enum eSHADER_TYPE eSHADER_TYPE;

enum eSHADER_UNIFORM_TYPE {
    YAGL_GL_FLOAT             = 0x1406,
	YAGL_GL_FLOAT_VEC2        = 0x8B50,
	YAGL_GL_FLOAT_VEC3        = 0x8B51,
	YAGL_GL_FLOAT_VEC4        = 0x8B52,
	YAGL_GL_INT               = 0x1404,
	YAGL_GL_INT_VEC2          = 0x8B53,
	YAGL_GL_INT_VEC3          = 0x8B54,
	YAGL_GL_INT_VEC4          = 0x8B55,
	YAGL_GL_BOOL              = 0x8B56,
	YAGL_GL_BOOL_VEC2         = 0x8B57,
	YAGL_GL_BOOL_VEC3         = 0x8B58,
	YAGL_GL_BOOL_VEC4         = 0x8B59,
	YAGL_GL_FLOAT_MAT2        = 0x8B5A,
	YAGL_GL_FLOAT_MAT3        = 0x8B5B,
	YAGL_GL_FLOAT_MAT4        = 0x8B5C,
	YAGL_GL_FLOAT_MAT2x3      = 0x8B65,
	YAGL_GL_FLOAT_MAT2x4      = 0x8B66,
	YAGL_GL_FLOAT_MAT3x2      = 0x8B67,
	YAGL_GL_FLOAT_MAT3x4      = 0x8B68,
	YAGL_GL_FLOAT_MAT4x2      = 0x8B69,
	YAGL_GL_FLOAT_MAT4x3      = 0x8B6A,
	YAGL_GL_SAMPLER_1D        = 0x8B5D,
	YAGL_GL_SAMPLER_2D        = 0x8B5E,
	YAGL_GL_SAMPLER_3D        = 0x8B5F,
	YAGL_GL_SAMPLER_CUBE      = 0x8B60,
	YAGL_GL_SAMPLER_1D_SHADOW = 0x8B61,
	YAGL_GL_SAMPLER_2D_SHADOW = 0x8B62
};
typedef enum eSHADER_UNIFORM_TYPE eSHADER_UNIFORM_TYPE;

/*** ---------------------------------------------------------------------- ***/
/*** Data Types ***/

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
//typedef struct StrTable StrTable;

/*** ---------------------------------------------------------------------- ***/
/*** Callbacks ***/

typedef int(*YAGLRenderProc)(float dt);
typedef int(*YAGLFrameProc)(float dt);

typedef int(*YAGLWinCloseProc)();
typedef void(*YAGLWinSizeProc)(int w, int h);
typedef void(*YAGLWinRefreshProc)();
typedef void(*YAGLDebugProc)(char* text, int err_lvl);

typedef void(*YAGLMousePosProc)(int x, int h);
typedef void(*YAGLMouseButtonProc)(int button, int event);
typedef void(*YAGLMouseWheelProc)(int pos);

typedef void(*YAGLKeyProc)(int key, int event);
typedef void(*YAGLCharProc)(int key, int event);

typedef void(*YAGLParticleSpawnProc)(PEmitter*, int event, int x, int y);
typedef void(*YAGLParticleDeadProc)(PEmitter*, int event, int x, int y);

typedef int(*YAGLSpriteSetIterateProc)(SpriteSet* sprset, Sprite* spr, void* user_data);
typedef int(*YAGLMultiSetIterateProc)(MultiSet* ms, void* elem, void* user_data, int elem_rank, eSET_TYPE ms_type);

typedef void(*YAGLCollisionProc)(Sprite* spr1, Sprite* spr2);

/*** ---------------------------------------------------------------------- ***/
/*** Functions ***/

/* System */
int     YAGL_API    System_Init (eDEBUG debug_mode);
void    YAGL_API    System_DebugOut (const char* data, int err_lvl);
void    YAGL_API    System_SetDebugCallback (YAGLDebugProc debug_proc);
void    YAGL_API    System_Terminate ();
int     YAGL_API    System_GetVideoModesCount ();
void    YAGL_API    System_GetVideoMode (int mode, int* width, int* height, int* red_bits, int* green_bits, int* blue_bits);
void    YAGL_API    System_GetDesktopMode (int* width, int* height, int* red_bits, int* green_bits, int* blue_bits);
void    YAGL_API    System_GetStats (int* num_textures, int* num_texture_maps, int* num_quads, int* num_sprites, int* num_sprite_sets, int* num_animations, int* num_particle_emitters, int* num_shaders, int* num_bmp_fonts, int* num_bmp_texts);
void    YAGL_API    System_GetVersion (eVERSION flag, int* major, int* minor, int* revision);

/* Window */
int     YAGL_API    Window_Create (const int width, const int height, const int red_bits, const int green_bits, const int blue_bits, const int fullscreen, const char title[], int resizable, const int multisample);
int     YAGL_API    Window_CreateEx(int video_mode_id, const char title[], int multisample);
void    YAGL_API    Window_Close ();
int     YAGL_API    Window_IsOpened ();
void    YAGL_API    Window_Center ();
void    YAGL_API    Window_SetPos (const int x, const int y);
void    YAGL_API    Window_SetSize (const int w, const int h);
void    YAGL_API    Window_GetSize (int* w, int* h);
void    YAGL_API    Window_SetTitle (const char title[]);
void    YAGL_API    Window_SetVisible (const int flag);
int     YAGL_API    Window_IsVisible ();
int     YAGL_API    Window_IsActive ();
int     YAGL_API    Window_IsAccelerated ();
void    YAGL_API    Window_Capture (const char filepath[], eCAPTURE_TYPE type, int x, int y, int w, int h);
void    YAGL_API    Window_SetCursor (const int status);
void    YAGL_API    Window_SetCloseCallback (YAGLWinCloseProc proc);
void    YAGL_API    Window_SetSizeCallback (YAGLWinSizeProc proc);
void    YAGL_API    Window_SetRefreshCallback (YAGLWinRefreshProc proc);

/* Render */
void    YAGL_API    Render_SetClearColor (const unsigned char red, const unsigned char green, const unsigned char blue);
void    YAGL_API    Render_SetClearColorEx (YAGL_Color color);
void    YAGL_API    Render_InitTimers ();
void    YAGL_API    Render_SetTimersMult (float tm);
float   YAGL_API    Render_GetTimersMult ();
void    YAGL_API    Render_Begin ();
void    YAGL_API    Render_End ();
void    YAGL_API    Render_SetCallbacks (YAGLRenderProc render_proc, YAGLFrameProc frame_proc);
void    YAGL_API    Render_StartLoop (YAGLRenderProc render_proc, YAGLFrameProc frame_proc, int exit_on_win_close);
double  YAGL_API    Render_GetFps (const double delay);
double  YAGL_API    Render_GetDelta ();
void    YAGL_API    Render_SetSwapInterval (const int interval);

/* View */
void    YAGL_API    View_Move (const int x, const int y);
void    YAGL_API    View_SetRect (const int x, const int y, const int w, const int h);
void    YAGL_API    View_GetRect (int* x, int* y, int* w, int* h);
void    YAGL_API    View_SetCorners (const int x1, const int y1, const int x2, const int y2);
void    YAGL_API    View_GetCorners (int* x1, int* y1, int* x2, int* y2);
void    YAGL_API    View_SetCenter (const int x, const int y);
void    YAGL_API    View_GetCenter (int* x, int* y);
void    YAGL_API    View_SetSize (const int w, const int h);
void    YAGL_API    View_GetSize (int* w, int* h);
void    YAGL_API    View_SetZoom (const float factor);
void    YAGL_API    View_AddZoom (float factor);
float   YAGL_API    View_GetZoom ();
void    YAGL_API    View_ScreenToWorld (const int scr_x, const int scr_y, int* world_x, int* world_y);
void    YAGL_API    View_WorldToScreen (const int world_x, const int world_y, int* scr_x, int* scr_y);
int     YAGL_API    View_PointIsVisible (const int x, const int y);

/* Events */
void    YAGL_API    Events_KeySetRepeat (const int status);
int     YAGL_API    Events_KeyGetRepeat ();
int     YAGL_API    Events_KeyGet (const int key);

void    YAGL_API    Events_MouseGetPos (int* x, int* y);
int     YAGL_API    Events_MouseGetButton (const int button);
int     YAGL_API    Events_MouseGetWheel ();
void    YAGL_API    Events_MouseSetPos (int x, int y);
void    YAGL_API    Events_MouseSetWheel (const int pos);
void    YAGL_API    Events_MouseSetPosMode (eMOUSE_POS_MODE mode);
int     YAGL_API    Events_MouseGetPosMode ();

void    YAGL_API    Events_SetMousePosCallback (YAGLMousePosProc proc);
void    YAGL_API    Events_SetMouseButtonCallback (YAGLMouseButtonProc proc);
void    YAGL_API    Events_SetMouseWheelCallback (YAGLMouseWheelProc proc);
void    YAGL_API    Events_SetKeyCallback (YAGLKeyProc proc);
void    YAGL_API    Events_SetCharCallback (YAGLCharProc proc);

/* Misc */
void        YAGL_API    Misc_Sleep (const double time);
void        YAGL_API    Misc_TimersSetFollowMult (int follow);
int         YAGL_API    Misc_TimersGetFollowMult ();
double      YAGL_API    Misc_TimerInit ();
double      YAGL_API    Misc_TimerDiff (const double timestamp);
int         YAGL_API    Misc_RandomI (const int min, const int max);
double      YAGL_API    Misc_RandomF (const double min, const double max);
YAGL_Color  YAGL_API    Misc_Color (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
void        YAGL_API    Misc_ColorComponents (YAGL_Color color, unsigned char* red, unsigned char* green, unsigned char* blue, unsigned char* alpha);

/* Texture */
Texture*    YAGL_API    Texture_Create (const char filepath[], eTEXTURE_CHANNELS channels);
Texture*    YAGL_API    Texture_CreateFromMem (const unsigned char* data, const int buffer_size, eTEXTURE_CHANNELS channels);
int         YAGL_API    Texture_IsTexture (Texture* tex);
int         YAGL_API    Texture_Load (Texture* tex, const char filepath[], eTEXTURE_CHANNELS channels);
int         YAGL_API    Texture_LoadFromMem (Texture* tex, const unsigned char* data, const int buffer_size, eTEXTURE_CHANNELS channels);
void        YAGL_API    Texture_SetParameter (Texture* tex, int flag, int value);
void        YAGL_API    Texture_SetDefaultParameter (Texture* tex);
void        YAGL_API    Texture_GetSize (Texture* tex, int* w, int* h);
void        YAGL_API    Texture_SetEmpty (Texture* tex);
int         YAGL_API    Texture_Destroy (Texture* tex);

/* Texture Map */
TextureMap*     YAGL_API    TextureMap_Create (const char filepath[], eTEXTURE_CHANNELS channels);
TextureMap*     YAGL_API    TextureMap_CreateFromTexture (Texture* tex);
int             YAGL_API    TextureMap_IsTextureMap (TextureMap* tex_map);
int             YAGL_API    TextureMap_Destroy (TextureMap* tex_map, int free_tex);

void            YAGL_API    TextureMap_SetTexture (TextureMap* tex_map, Texture* tex);
Texture*        YAGL_API    TextureMap_GetTexture (TextureMap* tex_map);

void            YAGL_API    TextureMap_SetParameter (TextureMap* tex_map, int flag, int value);
void            YAGL_API    TextureMap_SetDefaultParameter (TextureMap* tex_map);
void            YAGL_API    TextureMap_GetSize (TextureMap* tex_map, int* w, int* h);

int             YAGL_API    TextureMap_AddRect (TextureMap* tex_map, int rect_x, int rect_y, int rect_w, int rect_h);
void            YAGL_API    TextureMap_GetRect (TextureMap* tex_map, unsigned int rect_id, int* rect_x, int* rect_y, int* rect_w, int* rect_h);
void            YAGL_API    TextureMap_Empty (TextureMap* tex_map);

int             YAGL_API    TextureMap_Count (TextureMap* tex_map);

/* Quad */
Quad*   YAGL_API    Quad_Create (Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h);
int     YAGL_API    Quad_IsQuad (Quad* qd);

void        YAGL_API    Quad_SetTexture (Quad* qd, Texture* tex);
void        YAGL_API    Quad_SetTextureRect (Quad* qd, int rect_x, int rect_y, int rect_w, int rect_h);
void        YAGL_API    Quad_SetTextureEx (Quad* qd, Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h);
Texture*    YAGL_API    Quad_GetTexture (Quad* qd);
void        YAGL_API    Quad_GetTextureRect (Quad* qd, int* rect_x, int* rect_y, int* rect_w, int* rect_h);
Texture*    YAGL_API    Quad_GetTextureEx (Quad* qd, int* rect_x, int* rect_y, int* rect_w, int* rect_h);

void    YAGL_API    Quad_SetTextureMap (Quad* qd, TextureMap* tex_map, unsigned int rect_id);

void    YAGL_API    Quad_SetCenterEx (Quad* qd, eCENTER flag);
void    YAGL_API    Quad_Move (Quad* qd, float x, float y);
void    YAGL_API    Quad_Rotate (Quad* qd, float angle);
void    YAGL_API    Quad_Scale (Quad* qd, float x, float y);

void    YAGL_API    Quad_SetFlip (Quad* qd, int x, int y);
void    YAGL_API    Quad_GetFlip (Quad* qd, int* x, int* y);

void    YAGL_API    Quad_QuadToWorld (Quad* qd, float qd_x, float qd_y, float* world_x, float* world_y);
void    YAGL_API    Quad_QuadToWorldEx (Quad* qd, float qd_x_ratio, float qd_y_ratio, float* world_x, float* world_y);

void    YAGL_API    Quad_Draw (Quad* qd);

int     YAGL_API    Quad_Destroy (Quad* qd);

/* Quad Accessors */
void        YAGL_API    Quad_SetVisible (Quad* qd, int visible);
int         YAGL_API    Quad_GetVisible (Quad* qd);

void        YAGL_API    Quad_SetPos (Quad* qd, float x, float y);
void        YAGL_API    Quad_GetPos (Quad* qd, float* x, float* y);

void        YAGL_API    Quad_SetSize (Quad* qd, float w, float h);
void        YAGL_API    Quad_GetSize (Quad* qd, float* w, float* h);

void        YAGL_API    Quad_SetCenter (Quad* qd, float x, float y);
void        YAGL_API    Quad_GetCenter (Quad* qd, float* x, float* y);

void        YAGL_API    Quad_SetAngle (Quad* qd, float angle);
float       YAGL_API    Quad_GetAngle (Quad* qd);

void        YAGL_API    Quad_SetBlendMode (Quad* qd, eBLEND_MODE blend_mode);
int         YAGL_API    Quad_GetBlendMode (Quad* qd);

void        YAGL_API    Quad_SetColor (Quad* qd, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void        YAGL_API    Quad_GetColor (Quad* qd, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a);
void        YAGL_API    Quad_SetColorEx (Quad* qd, YAGL_Color color);
YAGL_Color  YAGL_API    Quad_GetColorEx (Quad* qd);

void        YAGL_API    Quad_SetAttachedData (Quad* qd, void* data);
void*       YAGL_API    Quad_GetAttachedData (Quad* qd);

/* Sprite */
Sprite*         YAGL_API    Sprite_Create (Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h);
int             YAGL_API    Sprite_IsSprite (Sprite* spr);

void            YAGL_API    Sprite_SetTexture (Sprite* spr, Texture* tex);
void            YAGL_API    Sprite_SetTextureRect (Sprite* spr, int rect_x, int rect_y, int rect_w, int rect_h);
void            YAGL_API    Sprite_SetTextureEx (Sprite* spr, Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h);
Texture*        YAGL_API    Sprite_GetTexture (Sprite* spr);
void            YAGL_API    Sprite_GetTextureRect (Sprite* spr, int* rect_x, int* rect_y, int* rect_w, int* rect_h);
Texture*        YAGL_API    Sprite_GetTextureEx (Sprite* spr, int* rect_x, int* rect_y, int* rect_w, int* rect_h);

void            YAGL_API    Sprite_SetTextureMap (Sprite* spr, TextureMap* tex_map, unsigned int rect_id);

void            YAGL_API    Sprite_SetShape (Sprite* spr, eSHAPE shape_type, float x, float y, float w, float h);
void            YAGL_API    Sprite_GetShape (Sprite* spr, eSHAPE* shape_type, float* x, float* y, float* w, float* h);
void            YAGL_API    Sprite_SetCollisionMask (Sprite* spr, int collision_mask);
int             YAGL_API    Sprite_GetCollisionMask (Sprite* spr);
void            YAGL_API    Sprite_SetCollisionGroup (Sprite* spr, int collision_group);
int             YAGL_API    Sprite_GetCollisionGroup (Sprite* spr);

void            YAGL_API    Sprite_AnimationSet (Sprite* spr, Animation* anim);
Animation*      YAGL_API    Sprite_AnimationGet (Sprite* spr);
void            YAGL_API    Sprite_AnimationSetFrame (Sprite* spr, unsigned int frame_id);
void            YAGL_API    Sprite_AnimationDisplayFrame (Sprite* spr, unsigned int frame_id);
unsigned int    YAGL_API    Sprite_AnimationGetFrame (Sprite* spr);
void            YAGL_API    Sprite_AnimationSetStartFrame (Sprite* spr, unsigned int frame_id);
unsigned int    YAGL_API    Sprite_AnimationGetStartFrame (Sprite* spr);
void            YAGL_API    Sprite_AnimationSetTimerMult (Sprite* spr, float tm);
float           YAGL_API    Sprite_AnimationGetTimerMult (Sprite* spr);
void            YAGL_API    Sprite_AnimationGo (Sprite* spr, int loop);
int             YAGL_API    Sprite_AnimationGetStatus (Sprite* spr);
int             YAGL_API    Sprite_AnimationGetLoop (Sprite* spr);
void            YAGL_API    Sprite_AnimationStop (Sprite* spr, unsigned int stop_frame);

void            YAGL_API    Sprite_SetCenterEx (Sprite* spr, eCENTER flag);
void            YAGL_API    Sprite_Move (Sprite* spr, float x, float y);
void            YAGL_API    Sprite_Rotate (Sprite* spr, float angle);
void            YAGL_API    Sprite_Scale (Sprite* spr, float x, float y);

void            YAGL_API    Sprite_SetFlip (Sprite* spr, int x, int y);
void            YAGL_API    Sprite_GetFlip (Sprite* spr, int* x, int* y);

void            YAGL_API    Sprite_SetVelLen (Sprite* spr, float len);
void            YAGL_API    Sprite_SetVelEx (Sprite* spr, float len, float angle);
void            YAGL_API    Sprite_GetVelEx (Sprite* spr, float* len, float* angle);
void            YAGL_API    Sprite_SetVelAngle (Sprite* spr, float angle);
void            YAGL_API    Sprite_SetAccelLen (Sprite* spr, float len);
void            YAGL_API    Sprite_SetAccelEx (Sprite* spr, float len, float angle);
void            YAGL_API    Sprite_GetAccelEx (Sprite* spr, float* len, float* angle);
void            YAGL_API    Sprite_SetAccelAngle (Sprite* spr, float angle);

void            YAGL_API    Sprite_SpriteToWorld (Sprite* spr, float spr_x, float spr_y, float* world_x, float* world_y);
void            YAGL_API    Sprite_SpriteToWorldEx (Sprite* spr, float spr_x_ratio, float spr_y_ratio, float* world_x, float* world_y);
void            YAGL_API    Sprite_WorldToSprite (Sprite* spr, float world_x, float world_y, float* spr_x, float* spr_y, int folow_spr_angle);

void            YAGL_API    Sprite_Draw (Sprite* spr);
void            YAGL_API    Sprite_DrawShape (Sprite* spr);

int             YAGL_API    Sprite_Destroy (Sprite* spr);

/* Sprite Accessors */
void        YAGL_API    Sprite_SetVisible (Sprite* spr, int visible);
void        YAGL_API    Sprite_SetDynamic (Sprite* spr, int dynamic);
int         YAGL_API    Sprite_GetVisible (Sprite* spr);
int         YAGL_API    Sprite_GetDynamic (Sprite* spr);

void        YAGL_API    Sprite_SetPos (Sprite* spr, float x, float y);
void        YAGL_API    Sprite_GetPos (Sprite* spr, float* x, float* y);

void        YAGL_API    Sprite_SetSize (Sprite* spr, float w, float h);
void        YAGL_API    Sprite_GetSize (Sprite* spr, float* w, float* h);

void        YAGL_API    Sprite_SetCenter (Sprite* spr, float x, float y);
void        YAGL_API    Sprite_GetCenter (Sprite* spr, float* x, float* y);

void        YAGL_API    Sprite_SetAngle (Sprite* spr, float angle);
float       YAGL_API    Sprite_GetAngle (Sprite* spr);

void        YAGL_API    Sprite_SetBlendMode (Sprite* spr, eBLEND_MODE blend_mode);
int         YAGL_API    Sprite_GetBlendMode (Sprite* spr);

void        YAGL_API    Sprite_SetColor (Sprite* spr, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void        YAGL_API    Sprite_GetColor (Sprite* spr, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a);
void        YAGL_API    Sprite_SetColorEx (Sprite* spr, YAGL_Color color);
YAGL_Color  YAGL_API    Sprite_GetColorEx (Sprite* spr);

void        YAGL_API    Sprite_SetVel (Sprite* spr, float x, float y);
void        YAGL_API    Sprite_SetVelMax (Sprite* spr, float max);
void        YAGL_API    Sprite_GetVel (Sprite* spr, float* x, float* y);
float       YAGL_API    Sprite_GetVelLen (Sprite* spr);
float       YAGL_API    Sprite_GetVelAngle (Sprite* spr);
float       YAGL_API    Sprite_GetVelMax (Sprite* spr);

void        YAGL_API    Sprite_SetAccel (Sprite* spr, float x, float y);
void        YAGL_API    Sprite_GetAccel (Sprite* spr, float* x, float* y);
float       YAGL_API    Sprite_GetAccelLen (Sprite* spr);
float       YAGL_API    Sprite_GetAccelAngle (Sprite* spr);

void        YAGL_API    Sprite_SetInnertia (Sprite* spr, float innertia);
float       YAGL_API    Sprite_GetInnertia (Sprite* spr);

void        YAGL_API    Sprite_SetAVel (Sprite* spr, float avel);
void        YAGL_API    Sprite_SetAVelMax (Sprite* spr, float max);
float       YAGL_API    Sprite_GetAVel (Sprite* spr);
float       YAGL_API    Sprite_GetAVelMax (Sprite* spr);

void        YAGL_API    Sprite_SetAAccel (Sprite* spr, float aaccel);
float       YAGL_API    Sprite_GetAAccel (Sprite* spr);

void        YAGL_API    Sprite_SetAInnertia (Sprite* spr, float ainnertia);
float       YAGL_API    Sprite_GetAInnertia (Sprite* spr);

void        YAGL_API    Sprite_SetParentV (Sprite* spr, Sprite* spr_parent);
void        YAGL_API    Sprite_SetParentA (Sprite* spr, Sprite* spr_parent);
Sprite*     YAGL_API    Sprite_GetParentV (Sprite* spr);
Sprite*     YAGL_API    Sprite_GetParentA (Sprite* spr);

void        YAGL_API    Sprite_SetAttachedData (Sprite* spr, void* data);
void*       YAGL_API    Sprite_GetAttachedData (Sprite* spr);

/* Sprite Set */
SpriteSet*  YAGL_API    SpriteSet_Create ();
int         YAGL_API    SpriteSet_IsSpriteSet (SpriteSet* spr_set);
int         YAGL_API    SpriteSet_Destroy (SpriteSet* spr_set, int destroy);

void        YAGL_API    SpriteSet_Add (SpriteSet* spr_set, Sprite* spr);
int         YAGL_API    SpriteSet_Exists (SpriteSet* spr_set, Sprite* spr);
void        YAGL_API    SpriteSet_Del (SpriteSet* spr_set, Sprite* spr, int destroy);
void        YAGL_API    SpriteSet_DelAll (SpriteSet* spr_set, int destroy);

void        YAGL_API    SpriteSet_SetColor (SpriteSet* spr_set, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void        YAGL_API    SpriteSet_SetColorEx (SpriteSet* spr_set, YAGL_Color color);
void        YAGL_API    SpriteSet_SetBlendMode (SpriteSet* spr_set, eBLEND_MODE blend_mode);
void        YAGL_API    SpriteSet_SetVisible (SpriteSet* spr_set, int visible);
void        YAGL_API    SpriteSet_SetDynamic (SpriteSet* spr_set, int dynamic);

int         YAGL_API    SpriteSet_Collide (SpriteSet* spr_set, Sprite* spr, int force_check, int must_touch_all);

void        YAGL_API    SpriteSet_Draw (SpriteSet* spr_set);
void        YAGL_API    SpriteSet_DrawShapes (SpriteSet* spr_set);

int         YAGL_API    SpriteSet_Count (SpriteSet* spr_set);
int         YAGL_API    SpriteSet_GetAll (SpriteSet* spr_set, Sprite* spr[], int size);
int         YAGL_API    SpriteSet_Iterate (SpriteSet* spr_set, YAGLSpriteSetIterateProc enum_proc, void* user_data);

/* Animation */
Animation*  YAGL_API    Animation_Create (unsigned int frames_count);
int         YAGL_API    Animation_IsAnimation (Animation* anim);

int         YAGL_API    Animation_AddFrameEx (Animation* anim, float duration, Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h, YAGL_Color color, eBLEND_MODE blend_mode, int change_size, float size_x, float size_y);
int         YAGL_API    Animation_AddFrame (Animation* anim, float duration);
void        YAGL_API    Animation_FrameSetBlank (Animation* anim, unsigned int frame_id);
int         YAGL_API    Animation_FrameCount (Animation* anim);
int         YAGL_API    Animation_FrameMax (Animation* anim);
void        YAGL_API    Animation_Empty (Animation* anim);

void        YAGL_API    Animation_SetTimerMult (Animation* anim, float tm);
float       YAGL_API    Animation_GetTimerMult (Animation* anim);

int         YAGL_API    Animation_Destroy (Animation* anim);

void        YAGL_API    Animation_FrameSetDuration (Animation* anim, unsigned int frame_id, float duration);
void        YAGL_API    Animation_FrameSetTexture (Animation* anim, unsigned int frame_id, Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h);
void        YAGL_API    Animation_FrameSetColor (Animation* anim, unsigned int frame_id, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
void        YAGL_API    Animation_FrameSetColorEx (Animation* anim, unsigned int frame_id, YAGL_Color color);
void        YAGL_API    Animation_FrameSetBlendMode (Animation* anim, unsigned int frame_id, eBLEND_MODE blend_mode);
void        YAGL_API    Animation_FrameSetSize (Animation* anim, unsigned int frame_id, int change_size, float size_x, float size_y);

float       YAGL_API    Animation_FrameGetDuration (Animation* anim, unsigned int frame_id);
Texture*    YAGL_API    Animation_FrameGetTexture (Animation* anim, unsigned int frame_id, int* rect_x, int* rect_y, int* rect_w, int* rect_h);
void        YAGL_API    Animation_FrameGetColor (Animation* anim, unsigned int frame_id, unsigned char* red, unsigned char* green, unsigned char* blue, unsigned char* alpha);
YAGL_Color  YAGL_API    Animation_FrameGetColorEx (Animation* anim, unsigned int frame_id);
int         YAGL_API    Animation_FrameGetBlendMode (Animation* anim, unsigned int frame_id);
int         YAGL_API    Animation_FrameGetSize (Animation* anim, unsigned int frame_id, float* size_x, float* size_y);

/* Collision */
void    YAGL_API    Collision_SetCallback (YAGLCollisionProc proc);
void    YAGL_API    Collision_Process ();
void    YAGL_API    Collision_SetAutoProcess(int status);
int     YAGL_API    Collision_Check (Sprite* spr1, Sprite* spr2, int force_check);

/* Particles */
PEmitter*   YAGL_API    PEmitter_Create (Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h);
int         YAGL_API    PEmitter_IsPEmitter (PEmitter* emit);
int         YAGL_API    PEmitter_ReadCfg (PEmitter* emit, const char* file, const char* section, int load_tex_rect);
int         YAGL_API    PEmitter_WriteCfg (PEmitter* emit, const char* file, const char* section, int save_tex_rect);
int         YAGL_API    PEmitter_Copy (PEmitter* source, PEmitter* dest, int copy_texture);
void        YAGL_API    PEmitter_SetTexture (PEmitter* emit, Texture* tex);
Texture*    YAGL_API    PEmitter_GetTexture (PEmitter* emit);
void        YAGL_API    PEmitter_SetTextureRect (PEmitter* emit, int rect_x, int rect_y, int rect_w, int rect_h);
void        YAGL_API    PEmitter_GetTextureRect (PEmitter* emit, int* rect_x, int* rect_y, int* rect_w, int* rect_h);
void        YAGL_API    PEmitter_SetTextureMap (PEmitter* emit, TextureMap* tex_map, unsigned int rect_id);
void        YAGL_API    PEmitter_SetActive (PEmitter* emit, int status);
int         YAGL_API	PEmitter_GetActive (PEmitter* emit);
void        YAGL_API    PEmitter_Emitte (PEmitter* emit, unsigned int nbr);
void        YAGL_API    PEmitter_EmitteAt (PEmitter* emit, float x, float y, unsigned int nbr);
void        YAGL_API    PEmitter_Draw (PEmitter* emit);
int         YAGL_API    PEmitter_Destroy (PEmitter* emit);

/* Particles Emitter Accessors */
void            YAGL_API    PEmitter_SetVisible (PEmitter* emit, int visible);
int             YAGL_API    PEmitter_GetVisible (PEmitter* emit);

void            YAGL_API    PEmitter_SetPos (PEmitter* emit, float x, float y);
void            YAGL_API    PEmitter_GetPos (PEmitter* emit, float* x, float* y);

void            YAGL_API    PEmitter_SetPosVar (PEmitter* emit, float x, float y);
void            YAGL_API    PEmitter_GetPosVar (PEmitter* emit, float* x, float* y);

void            YAGL_API    PEmitter_SetVel (PEmitter* emit, float vel, float vel_var);
void            YAGL_API    PEmitter_GetVel (PEmitter* emit, float* vel, float* vel_var);

void            YAGL_API    PEmitter_SetAccel (PEmitter* emit, float accel, float accel_var);
void            YAGL_API    PEmitter_GetAccel (PEmitter* emit, float* accel, float* accel_var);

void            YAGL_API    PEmitter_SetAngle (PEmitter* emit, float angle, float angle_var);
void            YAGL_API    PEmitter_GetAngle (PEmitter* emit, float* angle, float* angle_var);

void            YAGL_API    PEmitter_SetForce (PEmitter* emit, float force, float force_var);
void            YAGL_API    PEmitter_GetForce (PEmitter* emit, float* force, float* force_var);

void            YAGL_API    PEmitter_SetForceAngle (PEmitter* emit, float f_angle, float f_angle_var);
void            YAGL_API    PEmitter_GetForceAngle (PEmitter* emit, float* f_angle, float* f_angle_var);

void            YAGL_API    PEmitter_SetInnertia (PEmitter* emit, float innertia, float innertia_var);
void            YAGL_API    PEmitter_GetInnertia (PEmitter* emit, float* innertia, float* innertia_var);

void            YAGL_API    PEmitter_SetParticleAngle (PEmitter* emit, float angle, float angle_var);
void            YAGL_API    PEmitter_GetParticleAngle (PEmitter* emit, float* angle, float* angle_var);

void            YAGL_API    PEmitter_SetSpin (PEmitter* emit, float spin, float spin_var, float spin_flyvar);
void            YAGL_API    PEmitter_GetSpin (PEmitter* emit, float* spin, float* spin_var, float* spin_flyvar);

void            YAGL_API    PEmitter_SetSize (PEmitter* emit, float size, float size_var, float size_flyvar);
void            YAGL_API    PEmitter_GetSize (PEmitter* emit, float* size, float* size_var, float* size_flyvar);

void            YAGL_API    PEmitter_SetLife (PEmitter* emit, float life, float life_var);
void            YAGL_API    PEmitter_GetLife (PEmitter* emit, float* life, float* life_var);

void            YAGL_API    PEmitter_SetEmitteRate (PEmitter* emit, unsigned int particles_per_second);
unsigned int    YAGL_API    PEmitter_GetEmitteRate (PEmitter* emit);

void            YAGL_API    PEmitter_SetMaxParticles (PEmitter* emit, unsigned int max);
unsigned int    YAGL_API    PEmitter_GetMaxParticles (PEmitter* emit);

void            YAGL_API    PEmitter_SetBlendMode (PEmitter* emit, eBLEND_MODE blend_mode);
int             YAGL_API    PEmitter_GetBlendMode (PEmitter* emit);

void            YAGL_API    PEmitter_SetColor (PEmitter* emit, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void            YAGL_API    PEmitter_SetColorVar (PEmitter* emit, short r, short g, short b, short a);
void            YAGL_API    PEmitter_SetColorFlyVar (PEmitter* emit, short r, short g, short b, short a);
void            YAGL_API    PEmitter_GetColor (PEmitter* emit, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a);
void            YAGL_API    PEmitter_GetColorVar (PEmitter* emit, short* r, short* g, short* b, short* a);
void            YAGL_API    PEmitter_GetColorFlyVar (PEmitter* emit, short* r, short* g, short* b, short* a);

void            YAGL_API    PEmitter_SetCallbacks (PEmitter* emit, YAGLParticleSpawnProc emitte_proc, YAGLParticleDeadProc dead_proc);

unsigned int    YAGL_API    PEmitter_GetCount (PEmitter* emit);

/* Shaders */
int         YAGL_API    Shader_Init (const int fatal_fail);
int         YAGL_API    Shader_IsInit ();
void        YAGL_API    Shader_SetCompileErrFatal (const int flag);
void        YAGL_API    Shader_SetLinkErrFatal (const int flag);
void        YAGL_API    Shader_SetInfoLogShow (const int flag);
Shader*     YAGL_API    Shader_Create ();
int         YAGL_API    Shader_IsShader (Shader* shd);
int         YAGL_API    Shader_AddSource (Shader* shd, const char* filepath, eSHADER_TYPE type);
int         YAGL_API    Shader_Link (Shader* shd);
int         YAGL_API    Shader_IsReady (Shader* shd);
int         YAGL_API    Shader_Destroy (Shader* shd);
void        YAGL_API    Shader_Use (Shader* shd);

int         YAGL_API    Shader_UniformGetLocation (Shader* shd, const char* name);
void        YAGL_API    Shader_UniformGetActive (Shader* shd, int id, int* lenght, int* size, eSHADER_UNIFORM_TYPE* type, char* name, int name_len);
void        YAGL_API    Shader_UniformGetF (Shader* shd, int id, float* data);
void        YAGL_API    Shader_UniformGetI (Shader* shd, int id, int* data);

void        YAGL_API    Shader_UniformSet1F (int id, float v1);
void        YAGL_API    Shader_UniformSet2F (int id, float v1, float v2);
void        YAGL_API    Shader_UniformSet3F (int id, float v1, float v2, float v3);
void        YAGL_API    Shader_UniformSet4F (int id, float v1, float v2, float v3, float v4);
void        YAGL_API    Shader_UniformSet1I (int id, int v1);
void        YAGL_API    Shader_UniformSet2I (int id, int v1, int v2);
void        YAGL_API    Shader_UniformSet3I (int id, int v1, int v2, int v3);
void        YAGL_API    Shader_UniformSet4I (int id, int v1, int v2, int v3, int v4);

void        YAGL_API    Shader_UniformSet1Fv (int id, int count, float* v);
void        YAGL_API    Shader_UniformSet2Fv (int id, int count, float* v);
void        YAGL_API    Shader_UniformSet3Fv (int id, int count, float* v);
void        YAGL_API    Shader_UniformSet4Fv (int id, int count, float* v);
void        YAGL_API    Shader_UniformSet1Iv (int id, int count, int* v);
void        YAGL_API    Shader_UniformSet2Iv (int id, int count, int* v);
void        YAGL_API    Shader_UniformSet3Iv (int id, int count, int* v);
void        YAGL_API    Shader_UniformSet4Iv (int id, int count, int* v);

void        YAGL_API    Shader_UniformMatrixSet2Fv (int id, int count, int transpose, float* v);
void        YAGL_API    Shader_UniformMatrixSet3Fv (int id, int count, int transpose, float* v);
void        YAGL_API    Shader_UniformMatrixSet4Fv (int id, int count, int transpose, float* v);
void        YAGL_API    Shader_UniformMatrixSet2x3Fv (int id, int count, int transpose, float* v);
void        YAGL_API    Shader_UniformMatrixSet3x2Fv (int id, int count, int transpose, float* v);
void        YAGL_API    Shader_UniformMatrixSet2x4Fv (int id, int count, int transpose, float* v);
void        YAGL_API    Shader_UniformMatrixSet4x2Fv (int id, int count, int transpose, float* v);
void        YAGL_API    Shader_UniformMatrixSet3x4Fv (int id, int count, int transpose, float* v);
void        YAGL_API    Shader_UniformMatrixSet4x3Fv (int id, int count, int transpose, float* v);

/* Drawing */
void    YAGL_API    Draw_SetParams (YAGL_Color color, eBLEND_MODE blend_mode, int size, int glow);
void    YAGL_API    Draw_SetColor (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
void    YAGL_API    Draw_SetColorEx (YAGL_Color color);
void    YAGL_API    Draw_SetBlendMode (eBLEND_MODE blend_mode);
void    YAGL_API    Draw_SetGlow (int status);
void    YAGL_API    Draw_SetSize (int size);
void    YAGL_API    Draw_Point (int x, int y);
void    YAGL_API    Draw_Points (int points[], int nbr);
void    YAGL_API    Draw_Line (int x1, int y1, int x2, int y2);
void    YAGL_API    Draw_Lines (int points[], int nbr, int strip);
void    YAGL_API    Draw_Triangle (int x1, int y1, int x2, int y2, int x3, int y3);
void    YAGL_API    Draw_TriangleF (int x1, int y1, int x2, int y2, int x3, int y3);
void    YAGL_API    Draw_Rect (int x, int y, int w, int h, float angle);
void    YAGL_API    Draw_RectF (int x, int y, int w, int h, float angle);
void    YAGL_API    Draw_RectCenter (int x, int y, int w, int h, float angle);
void    YAGL_API    Draw_RectCenterF (int x, int y, int w, int h, float angle);
void    YAGL_API    Draw_Ellipse (int x, int y, int rx, int ry, float angle, int precision);
void    YAGL_API    Draw_EllipseF (int x, int y, int rx, int ry, float angle, int precision);
void    YAGL_API    Draw_EllipseRect (int x, int y, int w, int h, float angle, int precision);
void    YAGL_API    Draw_EllipseRectF (int x, int y, int w, int h, float angle, int precision);

/* Geometry */
float   YAGL_API    Geo_PtoP_Dist (int x1, int y1, int x2, int y2);
float   YAGL_API    Geo_PtoP_Angle (int x1, int y1, int x2, int y2);
void    YAGL_API    Geo_PtoP_Vect (int x1, int y1, int x2, int y2, float len, float* v_x, float* v_y);

float   YAGL_API    Geo_SprtoP_Dist (Sprite* spr, int x, int y);
float   YAGL_API    Geo_SprtoP_Angle (Sprite* spr, int x, int y);
float   YAGL_API    Geo_SprtoP_AngleDiff (Sprite* spr, int x, int y);
void    YAGL_API    Geo_SprtoP_Vect (Sprite* spr, int x, int y, float len, float* v_x, float* v_y);

float   YAGL_API    Geo_SprtoSpr_Dist (Sprite* spr1, Sprite* spr2);
float   YAGL_API    Geo_SprtoSpr_Angle (Sprite* spr1, Sprite* spr2);
float   YAGL_API    Geo_SprtoSpr_AngleDiff (Sprite* spr1, Sprite* spr2);
void    YAGL_API    Geo_SprtoSpr_Vect (Sprite* spr1, Sprite* spr2, float len, float* v_x, float* v_y);

void    YAGL_API    Geo_PolarToCartesian (float angle, float len, float* x, float* y);
void    YAGL_API    Geo_CartesianToPolar (float x, float y, float* angle, float* len);

/* Bitmap font and text */
BmpFont*    YAGL_API    BmpFont_Create (const char fnt_file[], const char img_file[]);
int         YAGL_API    BmpFont_IsBmpFont (BmpFont* bfnt);
int         YAGL_API    BmpFont_Destroy (BmpFont* bfnt);
int         YAGL_API    BmpFont_CharExists (BmpFont* bfnt, const char chr);
void        YAGL_API    BmpFont_Print (BmpFont* bfnt, const char text[], int x, int y, int size, eALIGN align, float angle);
void        YAGL_API    BmpFont_PrintLines (BmpFont* bfnt, const char text[], int x, int y, int size, eALIGN align, float angle);
int         YAGL_API    BmpFont_Measure (BmpFont* bfnt, const char text[], int size);

/* Bitmap text */
BmpText*    YAGL_API    BmpText_Create (BmpFont* bfnt, const char text[], unsigned int size, int multiligne);
int         YAGL_API    BmpText_IsBmpText (BmpText* btxt);
int         YAGL_API    BmpText_Destroy (BmpText* btxt);
void        YAGL_API    BmpText_SetText (BmpText* btxt, const char text[]);
int         YAGL_API    BmpText_GetLen (BmpText* btxt);
void        YAGL_API    BmpText_Draw (BmpText* btxt);

/* Bitmap text Accessors */
char*       YAGL_API    BmpText_GetText (BmpText* btxt);

void        YAGL_API    BmpText_SetFont (BmpText* btxt, BmpFont* bfnt);
BmpFont*    YAGL_API    BmpText_GetFont (BmpText* btxt);

void        YAGL_API    BmpText_SetVisible (BmpText* btxt, int visible);
int         YAGL_API    BmpText_GetVisible (BmpText* btxt);

void        YAGL_API    BmpText_SetMultiligne (BmpText* btxt, int multiligne);
int         YAGL_API    BmpText_GetMultiligne (BmpText* btxt);

void        YAGL_API    BmpText_SetPos (BmpText* btxt, int x, int y);
void        YAGL_API    BmpText_GetPos (BmpText* btxt, int* x, int* y);

void        YAGL_API    BmpText_SetSize (BmpText* btxt, int size);
int         YAGL_API    BmpText_GetSize (BmpText* btxt);

void        YAGL_API    BmpText_SetAlign (BmpText* btxt, eALIGN align);
int         YAGL_API    BmpText_GetAlign (BmpText* btxt);

void        YAGL_API    BmpText_SetAngle (BmpText* btxt, float angle);
float       YAGL_API    BmpText_GetAngle (BmpText* btxt);

void        YAGL_API    BmpText_SetBlendMode (BmpText* btxt, eBLEND_MODE blend_mode);
int         YAGL_API    BmpText_GetBlendMode (BmpText* btxt);

void        YAGL_API    BmpText_SetColor (BmpText* btxt, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void        YAGL_API    BmpText_GetColor (BmpText* btxt, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a);
void        YAGL_API    BmpText_SetColorEx (BmpText* btxt, YAGL_Color color);
YAGL_Color  YAGL_API    BmpText_GetColorEx (BmpText* btxt);

/* MultiSet */
MultiSet*   YAGL_API    MultiSet_Create (eSET_TYPE type);
int         YAGL_API    MultiSet_IsMultiSet (MultiSet* ms);
eSET_TYPE   YAGL_API    MultiSet_GetDataType (MultiSet* ms);
int         YAGL_API    MultiSet_Destroy (MultiSet* ms, int destroy);

void        YAGL_API    MultiSet_Add (MultiSet* ms, void* data, int rank);
int         YAGL_API    MultiSet_Exists (MultiSet* ms, void* data);
void        YAGL_API    MultiSet_Del (MultiSet* ms, void* data, int destroy);
void        YAGL_API    MultiSet_DelAll (MultiSet* ms, int destroy);

int         YAGL_API    MultiSet_Count (MultiSet* ms);
int         YAGL_API    MultiSet_GetAll (MultiSet* ms, void* data[], int size);
int         YAGL_API    MultiSet_Iterate (MultiSet* ms, YAGLMultiSetIterateProc enum_proc, void* user_data);

/* Multi */
void        YAGL_API    MultiSet_Draw (MultiSet* ms); // quad, spr, pemitter, bmptext
void        YAGL_API    MultiSet_SetColor (MultiSet* ms, unsigned char r, unsigned char g, unsigned char b, unsigned char a); // quad, spr, bmptext
void        YAGL_API    MultiSet_SetColorEx (MultiSet* ms, YAGL_Color color); // quad, spr, bmptext
void        YAGL_API    MultiSet_SetBlendMode (MultiSet* ms, eBLEND_MODE blend_mode);  // quad, spr, pemitter, bmptext
void        YAGL_API    MultiSet_SetVisible (MultiSet* ms, int visible); // quad, spr, pemitter, bmptext

/* Quad specific */
/* Sprite specific */
void        YAGL_API    MultiSet_SpriteDrawShape (MultiSet* ms); // spr
void        YAGL_API    MultiSet_SpriteSetDynamic (MultiSet* ms, int dynamic); // spr
int         YAGL_API    MultiSet_SpriteCollide (MultiSet* ms, Sprite* spr, int force_check, int must_touch_all); // spr
void        YAGL_API    MultiSet_SpriteSetFlip (MultiSet* ms, int x, int y);

// vel
void        YAGL_API    MultiSet_SpriteSetVel (MultiSet* ms, float x, float y);
void        YAGL_API    MultiSet_SpriteSetVelLen (MultiSet* ms, float len);
void        YAGL_API    MultiSet_SpriteSetVelAngle (MultiSet* ms, float angle);
void        YAGL_API    MultiSet_SpriteSetVelEx (MultiSet* ms, float len, float angle);
// velmax
void        YAGL_API    MultiSet_SpriteSetVelMax (MultiSet* ms, float vel_max);
// accel
void        YAGL_API    MultiSet_SpriteSetAccel (MultiSet* ms, float x, float y);
void        YAGL_API    MultiSet_SpriteSetAccelLen (MultiSet* ms, float len);
void        YAGL_API    MultiSet_SpriteSetAccelAngle (MultiSet* ms, float angle);
void        YAGL_API    MultiSet_SpriteSetAccelEx (MultiSet* ms, float len, float angle);
// innertia
void        YAGL_API    MultiSet_SpriteSetInnertia (MultiSet* ms, float innertia);

// angles
void        YAGL_API    MultiSet_SpriteSetAVel (MultiSet* ms, float avel);
void        YAGL_API    MultiSet_SpriteSetAVelMax (MultiSet* ms, float avel_max);
void        YAGL_API    MultiSet_SpriteSetAAccel (MultiSet* ms, float aaccel);
void        YAGL_API    MultiSet_SpriteSetAInnertia (MultiSet* ms, float ainnertia);

/* PEmitter specific */
void        YAGL_API    MultiSet_PEmitterSetActive (MultiSet* ms, int active); // pemitter
void        YAGL_API    MultiSet_PEmitterEmitte (MultiSet* ms, unsigned int nbr); // pemitter
void        YAGL_API    MultiSet_PEmitterEmitteAt (MultiSet* ms, float x, float y, unsigned int nbr); // pemitter

/* BmpText specific */
void        YAGL_API    MultiSet_BmpTextSetText (MultiSet* ms, const char text[]);


#endif // __YAGL_H__
