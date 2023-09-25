
'/ YAGL (Yet Another Games Library) Main header
'/ Copyright (c) 2012 matwachich@gmail.com

#ifndef __YAGL_BI__
#define __YAGL_BI__

#inclib "yagl"

#define YAGL_DECLARE(func_type, func_name) Declare func_type func_name cdecl alias #func_name

'/'' ---------------------------------------------------------------------- '''/
'/'' Color macros '''/

#define YAGL_RGBA(r, g, b, a) RGBA((b), (g), (r), (a))

#define YAGL_RGBA_R( c ) ( CUInt( c )        And 255 )
#define YAGL_RGBA_G( c ) ( CUInt( c ) Shr  8 And 255 )
#define YAGL_RGBA_B( c ) ( CUInt( c ) Shr 16 And 255 )
#define YAGL_RGBA_A( c ) ( CUInt( c ) Shr 24         )

'/'' ---------------------------------------------------------------------- '''/
'/'' Data types '''/

Type YAGL_COLOR As UInteger

'/'' ---------------------------------------------------------------------- '''/
'/'' Keyboard and Mouse '''/

'' Keyboard key definitions: 8-bit ISO-8859-1 (Latin 1) encoding is used
 ' for printable keys (such as A-Z, 0-9 etc), and values above 256
 ' represent special (non-printable) keys (e.g. F1, Page Up etc).
 '/
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

'/' Mouse button definitions '/
#define YAGL_MOUSE_BUTTON_1      0
#define YAGL_MOUSE_BUTTON_2      1
#define YAGL_MOUSE_BUTTON_3      2
#define YAGL_MOUSE_BUTTON_4      3
#define YAGL_MOUSE_BUTTON_5      4
#define YAGL_MOUSE_BUTTON_6      5
#define YAGL_MOUSE_BUTTON_7      6
#define YAGL_MOUSE_BUTTON_8      7
#define YAGL_MOUSE_BUTTON_LAST   YAGL_MOUSE_BUTTON_8

'/' Mouse button aliases '/
#define YAGL_MOUSE_BUTTON_LEFT   YAGL_MOUSE_BUTTON_1
#define YAGL_MOUSE_BUTTON_RIGHT  YAGL_MOUSE_BUTTON_2
#define YAGL_MOUSE_BUTTON_MIDDLE YAGL_MOUSE_BUTTON_3

'/' Colors '/
#define YAGL_COLOR_BLACK    &HFF000000
#define YAGL_COLOR_MAROON   &HFF000080
#define YAGL_COLOR_GREEN    &HFF008000
#define YAGL_COLOR_OLIVE    &HFF008080
#define YAGL_COLOR_NAVY     &HFF800000
#define YAGL_COLOR_PURPLE   &HFF800080
#define YAGL_COLOR_TEAL     &HFF808000
#define YAGL_COLOR_SILVER   &HFFCECECE
#define YAGL_COLOR_GRAY     &HFF808080
#define YAGL_COLOR_RED      &HFF0000FF
#define YAGL_COLOR_LIME     &HFF00FF00
#define YAGL_COLOR_YELLOW   &HFF00FFFF
#define YAGL_COLOR_BLUE     &HFFFF0000
#define YAGL_COLOR_FUSCHIA  &HFFFF00FF
#define YAGL_COLOR_MAGENTA  YAGL_COLOR_FUSCHIA
#define YAGL_COLOR_AQUA     &HFFFFFF00
#define YAGL_COLOR_CYAN     YAGL_COLOR_AQUA
#define YAGL_COLOR_WHITE    &HFFFFFFFF

#define YAGL_COLOR_BLACK_A128   &H80000000
#define YAGL_COLOR_MAROON_A128  &H80000080
#define YAGL_COLOR_GREEN_A128   &H80008000
#define YAGL_COLOR_OLIVE_A128   &H80008080
#define YAGL_COLOR_NAVY_A128    &H80800000
#define YAGL_COLOR_PURPLE_A128  &H80800080
#define YAGL_COLOR_TEAL_A128    &H80808000
#define YAGL_COLOR_SILVER_A128  &H80CECECE
#define YAGL_COLOR_GRAY_A128    &H80808080
#define YAGL_COLOR_RED_A128     &H800000FF
#define YAGL_COLOR_LIME_A128    &H8000FF00
#define YAGL_COLOR_YELLOW_A128  &H8000FFFF
#define YAGL_COLOR_BLUE_A128    &H80FF0000
#define YAGL_COLOR_FUSCHIA_A128 &H80FF00FF
#define YAGL_COLOR_MAGENTA_A128 YAGL_COLOR_FUSCHIA_A128
#define YAGL_COLOR_AQUA_A128    &H80FFFF00
#define YAGL_COLOR_CYAN_A128    YAGL_COLOR_AQUA_A128
#define YAGL_COLOR_WHITE_A128   &H80FFFFFF

'/' OpenGL Texture parameters (for Texture_SetParameter) '/
#define YAGL_TEXTURE_MIN_FILTER			&H2801
#define YAGL_TEXTURE_MAG_FILTER			&H2800
#define YAGL_TEXTURE_WRAP_S				&H2802
#define YAGL_TEXTURE_WRAP_T				&H2803
#define YAGL_GL_NEAREST                 &H2600
#define YAGL_GL_LINEAR                  &H2601
#define YAGL_GL_NEAREST_MIPMAP_NEAREST  &H2700
#define YAGL_GL_LINEAR_MIPMAP_NEAREST   &H2701
#define YAGL_GL_NEAREST_MIPMAP_LINEAR   &H2702
#define YAGL_GL_LINEAR_MIPMAP_LINEAR    &H2703
#define YAGL_GL_CLAMP                   &H2900
#define YAGL_GL_REPEAT                  &H2901

'/'' ---------------------------------------------------------------------- '''/
'/'' Enumerations '''/

Enum eDEBUG
	DEBUG_OFF = 0,
	DEBUG_ON_STD,
	DEBUG_ON_FILE
End Enum

Enum eVERSION
	VERSION_YAGL = 0,
	VERSION_GLFW,
	VERSION_OGL
End Enum

Enum eCAPTURE_TYPE
	CAPTURE_TGA = 0,
	CAPTURE_BMP,
	CAPTURE_DDS
End Enum

Enum eMOUSE_POS_MODE
	MOUSE_POS_WIN_RELATIVE = 0,
	MOUSE_POS_WORLD_RELATIVE
End Enum

Enum eTEXTURE_CHANNELS
    TEXTURE_CHANNELS_AUTO = 0,
	TEXTURE_CHANNELS_LUM,
	TEXTURE_CHANNELS_LUMALPHA,
	TEXTURE_CHANNELS_RGB,
	TEXTURE_CHANNELS_RGBA
End Enum

Enum eBLEND_MODE
    BLEND_NO_CHANGE = -1,
	BLEND_BLACK = 0,
	BLEND_SOLID,
	BLEND_TRANS,
	BLEND_ALPHA,
	BLEND_BLENDED,
	BLEND_GLOW
End Enum

Enum eCENTER
	CENTER_CENTER = 0,
	CENTER_ULEFT,
	CENTER_URIGHT,
	CENTER_BLEFT,
	CENTER_BRIGHT,
	CENTER_CLEFT,
	CENTER_CRIGHT,
	CENTER_CUP,
	CENTER_CBOTTOM
End Enum

Enum eSHAPE
	SHAPE_NONE = 0,
	SHAPE_POINT,
	SHAPE_CIRCLE,
	SHAPE_RECT
End Enum

Enum eALIGN
	ALIGN_LEFT = 0,
	ALIGN_CENTER,
	ALIGN_RIGHT
End Enum

Enum eSET_TYPE
	SET_TYPE_ANY = 0,
    SET_TYPE_QUAD,
    SET_TYPE_SPRITE,
    SET_TYPE_PEMITTER,
    SET_TYPE_BMPTEXT,
End Enum

Enum eSHADER_TYPE
	SHADER_VERTEX = 0,
    SHADER_FRAGMENT
End Enum

Enum eSHADER_UNIFORM_TYPE
    YAGL_GL_FLOAT = &H1406,
	YAGL_GL_FLOAT_VEC2 = &H8B50,
	YAGL_GL_FLOAT_VEC3 = &H8B51,
	YAGL_GL_FLOAT_VEC4 = &H8B52,
	YAGL_GL_INT = &H1404,
	YAGL_GL_INT_VEC2 = &H8B53,
	YAGL_GL_INT_VEC3 = &H8B54,
	YAGL_GL_INT_VEC4 = &H8B55,
	YAGL_GL_BOOL = &H8B56,
	YAGL_GL_BOOL_VEC2 = &H8B57,
	YAGL_GL_BOOL_VEC3 = &H8B58,
	YAGL_GL_BOOL_VEC4 = &H8B59,
	YAGL_GL_FLOAT_MAT2 = &H8B5A,
	YAGL_GL_FLOAT_MAT3 = &H8B5B,
	YAGL_GL_FLOAT_MAT4 = &H8B5C,
	YAGL_GL_FLOAT_MAT2x3 = &H8B65,
	YAGL_GL_FLOAT_MAT2x4 = &H8B66,
	YAGL_GL_FLOAT_MAT3x2 = &H8B67,
	YAGL_GL_FLOAT_MAT3x4 = &H8B68,
	YAGL_GL_FLOAT_MAT4x2 = &H8B69,
	YAGL_GL_FLOAT_MAT4x3 = &H8B6A,
	YAGL_GL_SAMPLER_1D = &H8B5D,
	YAGL_GL_SAMPLER_2D = &H8B5E,
	YAGL_GL_SAMPLER_3D = &H8B5F,
	YAGL_GL_SAMPLER_CUBE = &H8B60,
	YAGL_GL_SAMPLER_1D_SHADOW = &H8B61,
	YAGL_GL_SAMPLER_2D_SHADOW = &H8B62
End Enum

'/'' ---------------------------------------------------------------------- '''/
'/'' Callbacks '''/

'typedef int(*YAGLRenderProc)(float);
Type YAGLRenderProc As Function cdecl (As Single) As Integer
'typedef int(*YAGLFrameProc)(float);
Type YAGLFrameProc As Function cdecl (As Single) As Integer

'typedef int(*YAGLWinCloseProc)();
Type YAGLWinCloseProc As Function cdecl () As Integer
'typedef void(*YAGLWinSizeProc)(int,int);
Type YAGLWinSizeProc As Sub cdecl (As Integer, As Integer)
'typedef void(*YAGLWinRefreshProc)();
Type YAGLWinRefreshProc As Sub cdecl ()
'typedef void(*YAGLDebugProc)(char*,int);
Type YAGLDebugProc As Sub cdecl (As ZString, As Integer)

'typedef void(*YAGLMousePosProc)(int,int);
Type YAGLMousePosProc As Sub cdecl (As Integer, As Integer)
'typedef void(*YAGLMouseButtonProc)(int,int);
Type YAGLMouseButtonProc As Sub cdecl (As Integer, As Integer)
'typedef void(*YAGLMouseWheelProc)(int);
Type YAGLMouseWheelProc As Sub cdecl (As Integer)

'typedef void(*YAGLKeyProc)(int,int);
Type YAGLKeyProc As Sub cdecl (As Integer, As Integer)
'typedef void(*YAGLCharProc)(int,int);
Type YAGLCharProc As Sub cdecl (As Integer, As Integer)

'typedef void(*YAGLParticleSpawnProc)(void*,int,int,int);
Type YAGLParticleSpawnProc As Sub cdecl (As Any Ptr, As Integer, As Integer, As Integer)
'typedef void(*YAGLParticleDeadProc)(void*,int,int,int);
Type YAGLParticleDeadProc As Sub cdecl (As Any Ptr, As Integer, As Integer, As Integer)

'typedef int(*YAGLSpriteSetIterateProc)(void*,void*,void*);
Type YAGLSpriteSetIterateProc As Function cdecl (As Any Ptr, As Any Ptr, As Any Ptr) As Integer
'typedef int(*YAGLMultiSetIterateProc)(MultiSet* ms, void* elem, void* user_data, int elem_rank, eSET_TYPE ms_type);
Type YAGLMultiSetIterateProc As Function cdecl (As Any Ptr, As Any Ptr, As Any Ptr, As Integer, As eSET_TYPE) As Integer

'typedef void(*YAGLCollisionProc)(void*,void*);
Type YAGLCollisionProc As Sub cdecl (As Any Ptr, As Any Ptr)

'/'' ---------------------------------------------------------------------- '''/
'/'' Data Types '''/

'typedef struct Texture Texture;
Type Texture As Texture_

'typedef struct TextureMap TextureMap;
Type TextureMap As TextureMap_

'typedef struct Quad Quad;
Type Quad As Quad_

'typedef struct Sprite Sprite;
Type Sprite As Sprite_

'typedef struct SpriteSet SpriteSet;
Type SpriteSet As SpriteSet_

'typedef struct PEmitter PEmitter;
Type PEmitter As PEmitter_

'typedef struct Shader Shader;
Type Shader As Shader_

'typedef struct BmpFont BmpFont;
Type BmpFont As BmpFont_

'typedef struct BmpText BmpText;
Type BmpText As BmpText_

'typedef struct Animation Animation;
Type Animation As Animation_

'typedef struct MultiSet MultiSet;
Type MultiSet As MultiSet_

'/'' ---------------------------------------------------------------------- '''/
'/'' Functions '''/

'/' System '/
'int     YAGL_API    System_Init (eDEBUG debug_mode);
YAGL_DECLARE(Function, System_Init) (As eDEBUG) As Integer
'void    YAGL_API    System_DebugOut (const char* data, int err_lvl);
YAGL_DECLARE(Sub, System_DebugOut) (As Const ZString, As Integer)
'void	 YAGL_API	 System_SetDebugCallback (YAGLDebugProc debug_proc);
YAGL_DECLARE(Sub, System_SetDebugCallback) (As YAGLDebugProc)
'void    YAGL_API    System_Terminate ();
YAGL_DECLARE(Sub, System_Terminate) ()
'int     YAGL_API    System_GetVideoModesCount ();
YAGL_DECLARE(Function, System_GetVideoModesCount) () As Integer
'void    YAGL_API    System_GetVideoMode (int mode, int* width, int* height, int* red_bits, int* green_bits, int* blue_bits);
YAGL_DECLARE(Sub, System_GetVideoMode) (As Integer, As Integer Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr)
'void    YAGL_API    System_GetDesktopMode (int* width, int* height, int* red_bits, int* green_bits, int* blue_bits);
YAGL_DECLARE(Sub, System_GetDesktopMode) (As Integer Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr)
'void    YAGL_API    System_GetStats (int* num_textures, int* num_texture_maps, int* num_quads, int* num_sprites, int* num_sprite_sets, int* num_animations, int* num_particle_emitters, int* num_shaders, int* num_bmp_fonts, int* num_bmp_texts));
YAGL_DECLARE(Sub, System_GetStats) (As Integer Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr)
'void    YAGL_API    System_GetVersion (eVERSION flag, int* major, int* minor, int* revision);
YAGL_DECLARE(Sub, System_GetVersion) (As eVERSION, As Integer Ptr, As Integer Ptr, As Integer Ptr)

'/' Window '/
'int     YAGL_API    Window_Create (const int width, const int height, const int red_bits, const int green_bits, const int blue_bits, const int fullscreen, const char title[], int resizable, const int multisample);
YAGL_DECLARE(Function, Window_Create) (As Const Integer, As Const Integer, As Const Integer, As Const Integer, As Const Integer, As Const Integer, As Const ZString, As Integer, As Const Integer) As Integer
'int     YAGL_API    Window_CreateEx(int video_mode_id, const char title[], int multisample);
YAGL_DECLARE(Function, Window_CreateEx) (As Integer, As Const ZString, As Integer) As Integer
'void    YAGL_API    Window_Close ();
YAGL_DECLARE(Sub, Window_Close) ()
'int     YAGL_API    Window_IsOpened ();
YAGL_DECLARE(Function, Window_IsOpened) () As Integer
'void    YAGL_API    Window_Center ();
YAGL_DECLARE(Sub, Window_Center) ()
'void    YAGL_API    Window_SetPos (const int x, const int y);
YAGL_DECLARE(Sub, Window_SetPos) (As Const Integer, As Const Integer)
'void    YAGL_API    Window_SetSize (const int w, const int h);
YAGL_DECLARE(Sub, Window_SetSize) (As Const Integer, As Const Integer)
'void    YAGL_API    Window_GetSize (int* w, int* h);
YAGL_DECLARE(Sub, Window_GetSize) (As Integer Ptr, As Integer Ptr)
'void    YAGL_API    Window_SetTitle (const char title[]);
YAGL_DECLARE(Sub, Window_SetTitle) (As Const ZString)
'void    YAGL_API    Window_SetVisible (const int flag);
YAGL_DECLARE(Sub, Window_SetVisible) (As Const Integer)
'int     YAGL_API    Window_IsVisible ();
YAGL_DECLARE(Function, Window_IsVisible) () As Integer
'int     YAGL_API    Window_IsActive ();
YAGL_DECLARE(Function, Window_IsActive) () As Integer
'int     YAGL_API    Window_IsAccelerated ();
YAGL_DECLARE(Function, Window_IsAccelerated) () As Integer
'void    YAGL_API    Window_Capture (const char title[], eCAPTURE_TYPE type, int x, int y, int w, int h);
YAGL_DECLARE(Sub, Window_Capture) (As Const ZString, As eCAPTURE_TYPE, As Integer, As Integer, As Integer, As Integer)
'void    YAGL_API    Window_SetCursor (const int status);
YAGL_DECLARE(Sub, Window_SetCursor) (As Const Integer)
'void    YAGL_API    Window_SetCloseCallback (YAGLWinCloseProc proc);
YAGL_DECLARE(Sub, Window_SetCloseCallback) (As YAGLWinCloseProc)
'void    YAGL_API    Window_SetSizeCallback (YAGLWinSizeProc proc);
YAGL_DECLARE(Sub, Window_SetSizeCallback) (As YAGLWinSizeProc)
'void    YAGL_API    Window_SetRefreshCallback (YAGLWinRefreshProc proc);
YAGL_DECLARE(Sub, Window_SetRefreshCallback) (As YAGLWinRefreshProc)

'/' Render '/
'void    YAGL_API    Render_SetClearColor (const unsigned char red, const unsigned char green, const unsigned char blue);
YAGL_DECLARE(Sub, Render_SetClearColor) (As Const UByte, As Const UByte, As Const UByte)
'void    YAGL_API    Render_SetClearColorEx (YAGL_Color color);
YAGL_DECLARE(Sub, Render_SetClearColorEx) (As YAGL_COLOR)
'void    YAGL_API    Render_InitTimers ();
YAGL_DECLARE(Sub, Render_InitTimers) ()
'void    YAGL_API    Render_SetTimersMult (float tm);
YAGL_DECLARE(Sub, Render_SetTimersMult) (As Single)
'float   YAGL_API    Render_GetTimersMult ();
YAGL_DECLARE(Function, Render_GetTimersMult) () As Single
'void    YAGL_API    Render_Begin ();
YAGL_DECLARE(Sub, Render_Begin) ()
'void    YAGL_API    Render_End ();
YAGL_DECLARE(Sub, Render_End) ()
'void    YAGL_API    Render_SetCallbacks (YAGLRenderProc render_proc, YAGLFrameProc frame_proc);
YAGL_DECLARE(Sub, Render_SetCallbacks) (As YAGLRenderProc, As YAGLFrameProc)
'void    YAGL_API    Render_StartLoop (YAGLRenderProc render_proc, YAGLFrameProc frame_proc, int exit_on_win_close);
YAGL_DECLARE(Sub, Render_StartLoop) (As YAGLRenderProc, As YAGLFrameProc, As Integer)
'double  YAGL_API    Render_GetFps (const double delay);
YAGL_DECLARE(Function, Render_GetFps) (As Const Double) As Double
'double  YAGL_API    Render_GetDelta ();
YAGL_DECLARE(Function, Render_GetDelta) () As Double
'void    YAGL_API    Render_SetSwapInterval (const int interval);
YAGL_DECLARE(Sub, Render_GetSwapInterval) (As Const Integer)

'/' View '/
'void    YAGL_API    View_Move (const int x, const int y);
YAGL_DECLARE(Sub, View_Move) (As Const Integer, As Const Integer)
'void    YAGL_API    View_SetRect (const int x, const int y, const int w, const int h);
YAGL_DECLARE(Sub, View_SetRect) (As Const Integer, As Const Integer, As Const Integer, As Const Integer)
'void    YAGL_API    View_GetRect (int* x, int* y, int* w, int* h);
YAGL_DECLARE(Sub, View_GetRect) (As Integer Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr)
'void    YAGL_API    View_SetCorners (const int x1, const int y1, const int x2, const int y2);
YAGL_DECLARE(Sub, View_SetCorners) (As Const Integer, As Const Integer, As Const Integer, As Const Integer)
'void    YAGL_API    View_GetCorners (int* x1, int* y1, int* x2, int* y2);
YAGL_DECLARE(Sub, View_GetCorners) (As Integer Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr)
'void    YAGL_API    View_SetCenter (const int x, const int y);
YAGL_DECLARE(Sub, View_SetCenter) (As Const Integer, As Const Integer)
'void    YAGL_API    View_GetCenter (int* x, int* y);
YAGL_DECLARE(Sub, View_GetCenter) (As Integer Ptr, As Integer Ptr)
'void    YAGL_API    View_SetSize (const int w, const int h);
YAGL_DECLARE(Sub, View_SetSize) (As Const Integer, As Const Integer)
'void    YAGL_API    View_GetSize (int* w, int* h);
YAGL_DECLARE(Sub, View_GetSize) (As Integer Ptr, As Integer Ptr)
'void    YAGL_API    View_SetZoom (const float factor);
YAGL_DECLARE(Sub, View_SetZoom) (As Const Single)
'void    YAGL_API    View_AddZoom (float factor);
YAGL_DECLARE(Sub, View_AddZoom) (As Single)
'float   YAGL_API    View_GetZoom ();
YAGL_DECLARE(Function, View_GetZoom) () As Single
'void    YAGL_API    View_ScreenToWorld (const int scr_x, const int scr_y, int* world_x, int* world_y);
YAGL_DECLARE(Sub, View_ScreenToWorld) (As Const Integer, As Const Integer, As Integer Ptr, As Integer Ptr)
'void    YAGL_API    View_WorldToScreen (const int world_x, const int world_y, int* scr_x, int* scr_y);
YAGL_DECLARE(Sub, View_WorldToScreen) (As Const Integer, As Const Integer, As Integer Ptr, As Integer Ptr)
'int     YAGL_API    View_PointIsVisible (const int x, const int y);
YAGL_DECLARE(Function, View_PointIsVisible) (As Const Integer, As Const Integer) As Integer

'/' Events '/
'void    YAGL_API    Events_KeySetRepeat (const int status);
YAGL_DECLARE(Sub, Events_KeySetRepeat) (As Const Integer)
'int	 YAGL_API	 Events_KeyGetRepeat ();
YAGL_DECLARE(Function, Events_KeyGetRepeat) () As Integer
'int     YAGL_API    Events_KeyGet (const int key);
YAGL_DECLARE(Function, Events_KeyGet) (As Const Integer) As Integer
'void    YAGL_API    Events_MouseGetPos (int* x, int* y);
YAGL_DECLARE(Sub, Events_MouseGetPos) (As Integer Ptr, As Integer Ptr)
'int     YAGL_API    Events_MouseGetButton (const int button);
YAGL_DECLARE(Function, Events_MouseGetButton) (As Const Integer) As Integer
'int     YAGL_API    Events_MouseGetWheel ();
YAGL_DECLARE(Function, Events_MouseGetWheel) () As Integer
'void    YAGL_API    Events_MouseSetPos (int x, int y);
YAGL_DECLARE(Sub, Events_MouseSetPos) (As Integer, As Integer)
'void    YAGL_API    Events_MouseSetWheel (const int pos);
YAGL_DECLARE(Sub, Events_MouseSetWheel) (As Const Integer)
'void    YAGL_API    Events_MouseSetPosMode (eMOUSE_POS_MODE mode);
YAGL_DECLARE(Sub, Events_MouseSetPosMode) (As eMOUSE_POS_MODE)
'int	 YAGL_API	 Events_MouseGetPosMode ();
YAGL_DECLARE(Function, Events_MouseGetPosMode) () As Integer

'void    YAGL_API    Events_SetMousePosCallback (YAGLMousePosProc proc);
YAGL_DECLARE(Sub, Events_SetMousePosCallback) (As YAGLMousePosProc)
'void    YAGL_API    Events_SetMouseButtonCallback (YAGLMouseButtonProc proc);
YAGL_DECLARE(Sub, Events_SetMouseButtonCallback) (As YAGLMouseButtonProc)
'void    YAGL_API    Events_SetMouseWheelCallback (YAGLMouseWheelProc proc);
YAGL_DECLARE(Sub, Events_SetMouseWheelCallback) (As YAGLMouseWheelProc)
'void    YAGL_API    Events_SetKeyCallback (YAGLKeyProc proc);
YAGL_DECLARE(Sub, Events_SetKeyCallback) (As YAGLKeyProc)
'void    YAGL_API    Events_SetCharCallback (YAGLCharProc proc);
YAGL_DECLARE(Sub, Events_SetCharCallback) (As YAGLCharProc)

'/' Misc '/
'void        YAGL_API    Misc_Sleep (const double time);
YAGL_DECLARE(Sub, Misc_Sleep) (As Const Double)
'void        YAGL_API    Misc_TimersSetFollowMult (int follow);
YAGL_DECLARE(Sub, Misc_TimersSetFollowMult) (As Integer)
'int         YAGL_API    Misc_TimersGetFollowMult ();
YAGL_DECLARE(Function, Misc_TimersGetFollowMult) () As Integer
'double      YAGL_API    Misc_TimerInit ();
YAGL_DECLARE(Function, Misc_TimerInit) () As Double
'double      YAGL_API    Misc_TimerDiff (const double timestamp);
YAGL_DECLARE(Function, Misc_TimerDiff) (As Const Double) As Double
'int         YAGL_API    Misc_RandomI (const int min, const int max);
YAGL_DECLARE(Function, Misc_RandomI) (As Const Integer, As Const Integer) As Integer
'double      YAGL_API    Misc_RandomF (const double min, const double max);
YAGL_DECLARE(Function, Misc_RandomF) (As Const Double, As Const Double) As Double
'YAGL_Color  YAGL_API    Misc_Color (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
YAGL_DECLARE(Function, Misc_Color) (As UByte, As UByte, As UByte, As UByte) As YAGL_COLOR
'void        YAGL_API    Misc_ColorComponents (YAGL_Color color, unsigned char* red, unsigned char* green, unsigned char* blue, unsigned char* alpha);
YAGL_DECLARE(Sub, Misc_ColorComponents) (As YAGL_COLOR, As UByte Ptr, As UByte Ptr, As UByte Ptr, As UByte Ptr)

'/' Texture '/
'Texture*    YAGL_API    Texture_CreateEmpty ();
YAGL_DECLARE(Function, Texture_CreateEmpty) () As Texture Ptr
'Texture*    YAGL_API    Texture_Create (const char filepath[], eTEXTURE_CHANNELS channels);
YAGL_DECLARE(Function, Texture_Create) (As Const ZString, As eTEXTURE_CHANNELS) As Texture Ptr
'Texture*    YAGL_API    Texture_CreateFromMem (const unsigned char* data, const int buffer_size, eTEXTURE_CHANNELS channels);
YAGL_DECLARE(Function, Texture_CreateFromMem) (As Const UByte Ptr, As Const Integer, As eTEXTURE_CHANNELS) As Texture Ptr
'int   YAGL_API    Texture_IsTexture (Texture* tex);
YAGL_DECLARE(Function, Texture_IsTexture) (As Texture Ptr) As Integer
'int         YAGL_API    Texture_Load (Texture* tex, const char filepath[], eTEXTURE_CHANNELS channels);
YAGL_DECLARE(Function, Texture_Load) (As Texture Ptr, As Const ZString, As eTEXTURE_CHANNELS) As Integer
'int         YAGL_API    Texture_LoadFromMem (Texture* tex, const unsigned char* data, const int buffer_size, eTEXTURE_CHANNELS channels);
YAGL_DECLARE(Function, Texture_LoadFromMem) (As Texture Ptr, As Const UByte Ptr, As Const Integer, As eTEXTURE_CHANNELS) As Integer
'void        YAGL_API    Texture_SetParameter (Texture* tex, int flag, int value);
YAGL_DECLARE(Sub, Texture_SetParameter) (As Texture Ptr, As Integer, As Integer)
'void        YAGL_API    Texture_SetDefaultParameter (Texture* tex);
YAGL_DECLARE(Sub, Texture_SetDefaultParameter) (As Texture Ptr)
'void        YAGL_API    Texture_GetSize (Texture* tex, int* w, int* h);
YAGL_DECLARE(Sub, Texture_GetSize) (As Texture Ptr, As Integer Ptr, As Integer Ptr)
'void        YAGL_API    Texture_SetEmpty (Texture* tex);
YAGL_DECLARE(Sub, Texture_SetEmpty) (As Texture Ptr)
'int   YAGL_API    Texture_Destroy (Texture* tex);
YAGL_DECLARE(Function, Texture_Destroy) (As Texture Ptr) As Integer

'/' Texture Map '/
'TextureMap*     YAGL_API    TextureMap_Create (const char filepath[], eTEXTURE_CHANNELS channels);
YAGL_DECLARE(Function, TextureMap_Create) (As Const ZString, As eTEXTURE_CHANNELS) As TextureMap Ptr
'TextureMap*     YAGL_API    TextureMap_CreateFromTexture (Texture* tex);
YAGL_DECLARE(Function, TextureMap_CreateFromTexture) (As Texture Ptr) As TextureMap Ptr
'int       YAGL_API    TextureMap_IsTextureMap (TextureMap* tex_map);
YAGL_DECLARE(Function, TextureMap_IsTextureMap) (As TextureMap Ptr) As Integer
'int       YAGL_API    TextureMap_Destroy (TextureMap* tex_map, int free_tex);
YAGL_DECLARE(Function, TextureMap_Destroy) (As TextureMap Ptr, As Integer) As Integer

'void            YAGL_API    TextureMap_SetTexture (TextureMap* tex_map, Texture* tex);
YAGL_DECLARE(Sub, TextureMap_SetTexture) (As TextureMap Ptr, As Texture Ptr)
'Texture*        YAGL_API    TextureMap_GetTexture (TextureMap* tex_map);
YAGL_DECLARE(Function, TextureMap_GetTexture) (As TextureMap Ptr) As Texture Ptr

'void            YAGL_API    TextureMap_SetParameter (TextureMap* tex_map, int flag, int value);
YAGL_DECLARE(Sub, TextureMap_SetParameter) (As TextureMap Ptr, As Integer, As Integer)
'void            YAGL_API    TextureMap_SetDefaultParameter (TextureMap* tex_map);
YAGL_DECLARE(Sub, TextureMap_SetDefaultParameter) (As TextureMap Ptr)
'void            YAGL_API    TextureMap_GetSize (TextureMap* tex_map, int* w, int* h);
YAGL_DECLARE(Sub, TextureMap_GetSize) (As TextureMap Ptr, As Integer Ptr, As Integer Ptr)

'int             YAGL_API    TextureMap_AddRect (TextureMap* tex_map, int rect_x, int rect_y, int rect_w, int rect_h);
YAGL_DECLARE(Function, TextureMap_AddRect) (As TextureMap Ptr, As Integer, As Integer, As Integer, As Integer) As Integer
'void            YAGL_API    TextureMap_GetRect (TextureMap* tex_map, unsigned int rect_id, int* rect_x, int* rect_y, int* rect_w, int* rect_h);
YAGL_DECLARE(Sub, TextureMap_GetRect) (As TextureMap Ptr, As UInteger, As Integer Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr)
'void            YAGL_API    TextureMap_Empty (TextureMap* tex_map);
YAGL_DECLARE(Sub, TextureMap_Empty) (As TextureMap Ptr)

'int             YAGL_API    TextureMap_Count (TextureMap* tex_map);
YAGL_DECLARE(Function, TextureMap_Count) (As TextureMap Ptr) As Integer

'/' Quad '/
'Quad*       YAGL_API    Quad_Create (Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h);
YAGL_DECLARE(Function, Quad_Create) (As Texture Ptr, As Integer, As Integer, As Integer, As Integer) As Quad Ptr
'int   YAGL_API    Quad_IsQuad (Quad* qd);
YAGL_DECLARE(Function, Quad_IsQuad) (As Quad Ptr) As Integer

'void        YAGL_API    Quad_SetTexture (Quad* qd, Texture* tex);
YAGL_DECLARE(Sub, Quad_SetTexture) (As Quad Ptr, As Texture Ptr)
'void        YAGL_API    Quad_SetTextureRect (Quad* qd, int rect_x, int rect_y, int rect_w, int rect_h);
YAGL_DECLARE(Sub, Quad_SetTextureRect) (As Quad Ptr, As Integer, As Integer, As Integer, As Integer)
'void        YAGL_API    Quad_SetTextureEx (Quad* qd, Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h);
YAGL_DECLARE(Sub, Quad_SetTextureEx) (As Quad Ptr, As Texture Ptr, As Integer, As Integer, As Integer, As Integer)
'Texture*    YAGL_API    Quad_GetTexture (Quad* qd);
YAGL_DECLARE(Function, Quad_GetTexture) (As Quad Ptr) As Texture Ptr
'void        YAGL_API    Quad_GetTextureRect (Quad* qd, int* rect_x, int* rect_y, int* rect_w, int* rect_h);
YAGL_DECLARE(Sub, Quad_GetTextureRect) (As Quad Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr)
'Texture*    YAGL_API    Quad_GetTextureEx (Quad* qd, int* rect_x, int* rect_y, int* rect_w, int* rect_h);
YAGL_DECLARE(Function, Quad_GetTextureEx) (As Quad Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr) As Texture Ptr

'void        YAGL_API    Quad_SetTextureMap (Quad* qd, TextureMap* tex_map, unsigned int rect_id);
YAGL_DECLARE(Sub, Quad_SetTextureMap) (As Quad Ptr, As TextureMap Ptr, As UInteger)

'void        YAGL_API    Quad_SetCenterEx (Quad* qd, eCENTER flag);
YAGL_DECLARE(Sub, Quad_SetCenterEx) (As Quad Ptr, As eCENTER)
'void        YAGL_API    Quad_Move (Quad* qd, float x, float y);
YAGL_DECLARE(Sub, Quad_Move) (As Quad Ptr, As Single, As Single)
'void        YAGL_API    Quad_Rotate (Quad* qd, float angle);
YAGL_DECLARE(Sub, Quad_Rotate) (As Quad Ptr, As Single)
'void        YAGL_API    Quad_Scale (Quad* qd, float x, float y);
YAGL_DECLARE(Sub, Quad_Scale) (As Quad Ptr, As Single, As Single)

'void        YAGL_API    Quad_SetFlip (Quad* qd, int x, int y);
YAGL_DECLARE(Sub, Quad_SetFlip) (As Quad Ptr, As Integer, As Integer)
'void        YAGL_API    Quad_GetFlip (Quad* qd, int* x, int* y);
YAGL_DECLARE(Sub, Quad_GetFlip) (As Quad Ptr, As Integer Ptr, As Integer Ptr)

'void        YAGL_API    Quad_QuadToWorld (Quad* qd, float qd_x, float qd_y, float* world_x, float* world_y);
YAGL_DECLARE(Sub, Quad_QuadToWorld) (As Quad Ptr, As Single, As Single, As Single Ptr, As Single Ptr)
'void        YAGL_API    Quad_QuadToWorldEx (Quad* qd, float qd_x_ratio, float qd_y_ratio, float* world_x, float* world_y);
YAGL_DECLARE(Sub, Quad_QuadToWorldEx) (As Quad Ptr, As Single, As Single, As Single Ptr, As Single Ptr)

'void        YAGL_API    Quad_Draw (Quad* qd);
YAGL_DECLARE(Sub, Quad_Draw) (As Quad Ptr)

'int   YAGL_API    Quad_Destroy (Quad* qd);
YAGL_DECLARE(Function, Quad_Destroy) (As Quad Ptr) As Integer

'/' Quad Accessors '/
'void        YAGL_API    Quad_SetVisible (Quad* qd, int visible);
YAGL_DECLARE(Sub, Quad_SetVisible) (As Quad Ptr, As Integer)
'int   YAGL_API    Quad_GetVisible (Quad* qd);
YAGL_DECLARE(Function, Quad_GetVisible) (As Quad Ptr) As Integer

'void        YAGL_API    Quad_SetPos (Quad* qd, float x, float y);
YAGL_DECLARE(Sub, Quad_SetPos) (As Quad Ptr, As Single, As Single)
'void        YAGL_API    Quad_GetPos (Quad* qd, float* x, float* y);
YAGL_DECLARE(Sub, Quad_GetPos) (As Quad Ptr, As Single Ptr, As Single Ptr)

'void        YAGL_API    Quad_SetSize (Quad* qd, float w, float h);
YAGL_DECLARE(Sub, Quad_SetSize) (As Quad Ptr, As Single, As Single)
'void        YAGL_API    Quad_GetSize (Quad* qd, float* w, float* h);
YAGL_DECLARE(Sub, Quad_GetSize) (As Quad Ptr, As Single Ptr, As Single Ptr)

'void        YAGL_API    Quad_SetCenter (Quad* qd, float x, float y);
YAGL_DECLARE(Sub, Quad_SetCenter) (As Quad Ptr, As Single, As Single)
'void        YAGL_API    Quad_GetCenter (Quad* qd, float* x, float* y);
YAGL_DECLARE(Sub, Quad_GetCenter) (As Quad Ptr, As Single Ptr, As Single Ptr)

'void        YAGL_API    Quad_SetAngle (Quad* qd, float angle);
YAGL_DECLARE(Sub, Quad_SetAngle) (As Quad Ptr, As Single)
'float       YAGL_API    Quad_GetAngle (Quad* qd);
YAGL_DECLARE(Function, Quad_GetAngle) (As Quad Ptr) As Single

'void        YAGL_API    Quad_SetBlendMode (Quad* qd, eBLEND_MODE blend_mode);
YAGL_DECLARE(Sub, Quad_SetBlendMode) (As Quad Ptr, As eBLEND_MODE)
'int         YAGL_API    Quad_GetBlendMode (Quad* qd);
YAGL_DECLARE(Function, Quad_GetBlendMode) (As Quad Ptr) As Integer

'void        YAGL_API    Quad_SetColor (Quad* qd, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
YAGL_DECLARE(Sub, Quad_SetColor) (As Quad Ptr, As UByte, As UByte, As UByte, As UByte)
'void        YAGL_API    Quad_GetColor (Quad* qd, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a);
YAGL_DECLARE(Sub, Quad_GetColor) (As Quad Ptr, As UByte Ptr, As UByte Ptr, As UByte Ptr, As UByte Ptr)
'void        YAGL_API    Quad_SetColorEx (Quad* qd, YAGL_Color color);
YAGL_DECLARE(Sub, Quad_SetColorEx) (As Quad Ptr, As YAGL_COLOR)
'YAGL_Color  YAGL_API    Quad_GetColorEx (Quad* qd);
YAGL_DECLARE(Function, Quad_GetColorEx) (As Quad Ptr) As YAGL_COLOR

'void        YAGL_API    Quad_SetAttachedData (Quad* qd, void* data);
YAGL_DECLARE(Sub, Quad_SetAttachedData) (As Quad Ptr, As Any Ptr)
'void*       YAGL_API    Quad_GetAttachedData (Quad* qd);
YAGL_DECLARE(Function, Quad_GetAttachedData) (As Quad Ptr) As Any Ptr

'/' Sprite '/
'Sprite*         YAGL_API    Sprite_Create (Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h);
YAGL_DECLARE(Function, Sprite_Create) (As Texture Ptr, As Integer, As Integer, As Integer, As Integer) As Sprite Ptr
'int       YAGL_API    Sprite_IsSprite (Sprite* spr);
YAGL_DECLARE(Function, Sprite_IsSprite) (As Sprite Ptr) As Integer

'void            YAGL_API    Sprite_SetTexture (Sprite* spr, Texture* tex);
YAGL_DECLARE(Sub, Sprite_SetTexture) (As Sprite Ptr, As Texture Ptr)
'void            YAGL_API    Sprite_SetTextureRect (Sprite* spr, int rect_x, int rect_y, int rect_w, int rect_h);
YAGL_DECLARE(Sub, Sprite_SetTextureRect) (As Sprite Ptr, As Integer, As Integer, As Integer, As Integer)
'void            YAGL_API    Sprite_SetTextureEx (Sprite* spr, Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h);
YAGL_DECLARE(Sub, Sprite_SetTextureEx) (As Sprite Ptr, As Texture Ptr, As Integer, As Integer, As Integer, As Integer)
'Texture*        YAGL_API    Sprite_GetTexture (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetTexture) (As Sprite Ptr) As Texture Ptr
'void            YAGL_API    Sprite_GetTextureRect (Sprite* spr, int* rect_x, int* rect_y, int* rect_w, int* rect_h);
YAGL_DECLARE(Sub, Sprite_GetTextureRect) (As Sprite Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr)
'Texture*        YAGL_API    Sprite_GetTextureEx (Sprite* spr, int* rect_x, int* rect_y, int* rect_w, int* rect_h);
YAGL_DECLARE(Function, Sprite_GetTextureEx) (As Sprite Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr) As Texture Ptr

'void            YAGL_API    Sprite_SetTextureMap (Sprite* spr, TextureMap* tex_map, unsigned int rect_id);
YAGL_DECLARE(Sub, Sprite_SetTextureMap) (As Sprite Ptr, As TextureMap Ptr, As UInteger)

'void            YAGL_API    Sprite_SetShape (Sprite* spr, eSHAPE shape_type, float x, float y, float w, float h);
YAGL_DECLARE(Sub, Sprite_SetShape) (As Sprite Ptr, As eSHAPE, As Single, As Single, As Single, As Single)
'void            YAGL_API    Sprite_GetShape (Sprite* spr, eSHAPE* shape_type, float* x, float* y, float* w, float* h);
YAGL_DECLARE(Sub, Sprite_GetShape) (As Sprite Ptr, As eSHAPE Ptr, As Single Ptr, As Single Ptr, As Single Ptr, As Single Ptr)
'void            YAGL_API    Sprite_SetCollisionMask (Sprite* spr, int collision_mask);
YAGL_DECLARE(Sub, Sprite_SetCollisionMask) (As Sprite Ptr, As Integer)
'int             YAGL_API    Sprite_GetCollisionMask (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetCollisionMask) (As Sprite Ptr) As Integer
'void            YAGL_API    Sprite_SetCollisionGroup (Sprite* spr, int collision_group);
YAGL_DECLARE(Sub, Sprite_SetCollisionGroup) (As Sprite Ptr, As Integer)
'int             YAGL_API    Sprite_GetCollisionGroup (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetCollisionGroup) (As Sprite Ptr) As Integer

'void            YAGL_API    Sprite_AnimationSet (Sprite* spr, Animation* anim);
YAGL_DECLARE(Sub, Sprite_AnimationSet) (As Sprite Ptr, As Animation Ptr)
'Animation*      YAGL_API    Sprite_AnimationGet (Sprite* spr);
YAGL_DECLARE(Function, Sprite_AnimationGet) (As Sprite Ptr) As Animation Ptr
'void            YAGL_API    Sprite_AnimationSetFrame (Sprite* spr, unsigned int frame_id);
YAGL_DECLARE(Sub, Sprite_AnimationSetFrame) (As Sprite Ptr, As UInteger)
'void            YAGL_API    Sprite_AnimationDisplayFrame (Sprite* spr, unsigned int frame_id);
YAGL_DECLARE(Sub, Sprite_AnimationDisplayFrame) (As Sprite Ptr, As UInteger)
'unsigned int    YAGL_API    Sprite_AnimationGetFrame (Sprite* spr);
YAGL_DECLARE(Function, Sprite_AnimationGetFrame) (As Sprite Ptr) As UInteger
'void            YAGL_API    Sprite_AnimationSetStartFrame (Sprite* spr, unsigned int frame_id);
YAGL_DECLARE(Sub, Sprite_AnimationSetStartFrame) (As Sprite Ptr, As UInteger)
'unsigned int    YAGL_API    Sprite_AnimationGetStartFrame (Sprite* spr);
YAGL_DECLARE(Function, Sprite_AnimationGetStartFrame) (As Sprite Ptr) As UInteger

'void            YAGL_API    Sprite_AnimationSetTimerMult (Sprite* spr, float tm);
YAGL_DECLARE(Sub, Sprite_AnimationSetTimerMult) (As Sprite Ptr, As Single)
'float           YAGL_API    Sprite_AnimationGetTimerMult (Sprite* spr);
YAGL_DECLARE(Function, Sprite_AnimationGetTimerMult) (As Sprite Ptr) As Single

'void            YAGL_API    Sprite_AnimationGo (Sprite* spr, int loop);
YAGL_DECLARE(Sub, Sprite_AnimationGo) (As Sprite Ptr, As Integer)
'int       YAGL_API    Sprite_AnimationGetStatus (Sprite* spr);
YAGL_DECLARE(Function, Sprite_AnimationGetStatus) (As Sprite Ptr) As Integer
'int       YAGL_API    Sprite_AnimationGetLoop (Sprite* spr);
YAGL_DECLARE(Function, Sprite_AnimationGetLoop) (As Sprite Ptr) As Integer
'void            YAGL_API    Sprite_AnimationStop (Sprite* spr, unsigned int stop_frame);
YAGL_DECLARE(Sub, Sprite_AnimationStop) (As Sprite Ptr, As UInteger)

'void            YAGL_API    Sprite_SetCenterEx (Sprite* spr, eCENTER flag);
YAGL_DECLARE(Sub, Sprite_SetCenterEx) (As Sprite Ptr, As eCENTER)
'void            YAGL_API    Sprite_Move (Sprite* spr, float x, float y);
YAGL_DECLARE(Sub, Sprite_Move) (As Sprite Ptr, As Single, As Single)
'void            YAGL_API    Sprite_Rotate (Sprite* spr, float angle);
YAGL_DECLARE(Sub, Sprite_Rotate) (As Sprite Ptr, As Single)
'void            YAGL_API    Sprite_Scale (Sprite* spr, float x, float y);
YAGL_DECLARE(Sub, Sprite_Scale) (As Sprite Ptr, As Single, As Single)

'void            YAGL_API    Sprite_SetFlip (Sprite* spr, int x, int y);
YAGL_DECLARE(Sub, Sprite_SetFlip) (As Sprite Ptr, As Integer, As Integer)
'void            YAGL_API    Sprite_GetFlip (Sprite* spr, int* x, int* y);
YAGL_DECLARE(Sub, Sprite_GetFlip) (As Sprite Ptr, As Integer Ptr, As Integer Ptr)

'void            YAGL_API    Sprite_SetVelLen (Sprite* spr, float len);
YAGL_DECLARE(Sub, Sprite_SetVelLen) (As Sprite Ptr, As Single)
'void            YAGL_API    Sprite_SetVelEx (Sprite* spr, float len, float angle);
YAGL_DECLARE(Sub, Sprite_SetVelEx) (As Sprite Ptr, As Single, As Single)
'void            YAGL_API    Sprite_GetVelEx (Sprite* spr, float* len, float* angle);
YAGL_DECLARE(Sub, Sprite_GetVelEx) (As Sprite Ptr, As Single Ptr, As Single Ptr)
'void            YAGL_API    Sprite_SetVelAngle (Sprite* spr, float angle);
YAGL_DECLARE(Sub, Sprite_SetVelAngle) (As Sprite Ptr, As Single)
'void            YAGL_API    Sprite_SetAccelLen (Sprite* spr, float len);
YAGL_DECLARE(Sub, Sprite_SetAccelLen) (As Sprite Ptr, As Single)
'void            YAGL_API    Sprite_SetAccelEx (Sprite* spr, float len, float angle);
YAGL_DECLARE(Sub, Sprite_SetAccelEx) (As Sprite Ptr, As Single, As Single)
'void            YAGL_API    Sprite_GetAccelEx (Sprite* spr, float* len, float* angle);
YAGL_DECLARE(Sub, Sprite_GetAccelEx) (As Sprite Ptr, As Single Ptr, As Single Ptr)
'void            YAGL_API    Sprite_SetAccelAngle (Sprite* spr, float angle);
YAGL_DECLARE(Sub, Sprite_SetAccelAngle) (As Sprite Ptr, As Single)

'void            YAGL_API    Sprite_SpriteToWorld (Sprite* spr, float spr_x, float spr_y, float* world_x, float* world_y);
YAGL_DECLARE(Sub, Sprite_SpriteToWorld) (As Sprite Ptr, As Single, As Single, As Single Ptr, As Single Ptr)
'void            YAGL_API    Sprite_SpriteToWorldEx (Sprite* spr, float spr_x_ratio, float spr_y_ratio, float* world_x, float* world_y);
YAGL_DECLARE(Sub, Sprite_SpriteToWorldEx) (As Sprite Ptr, As Single, As Single, As Single Ptr, As Single Ptr)

'void            YAGL_API    Sprite_Draw (Sprite* spr);
YAGL_DECLARE(Sub, Sprite_Draw) (As Sprite Ptr)
'void            YAGL_API    Sprite_DrawShape (Sprite* spr);
YAGL_DECLARE(Sub, Sprite_DrawShape) (As Sprite Ptr)

'int       YAGL_API    Sprite_Destroy (Sprite* spr);
YAGL_DECLARE(Function, Sprite_Destroy) (As Sprite Ptr) As Integer

'/' Sprite Accessors '/
'void        YAGL_API    Sprite_SetVisible (Sprite* spr, int visible);
YAGL_DECLARE(Sub, Sprite_SetVisible) (As Sprite Ptr, As Integer)
'void        YAGL_API    Sprite_SetDynamic (Sprite* spr, int dynamic);
YAGL_DECLARE(Sub, Sprite_SetDynamic) (As Sprite Ptr, As Integer)
'int   YAGL_API    Sprite_GetVisible (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetVisible) (As Sprite Ptr) As Integer
'int   YAGL_API    Sprite_GetDynamic (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetDynamic) (As Sprite Ptr) As Integer

'void        YAGL_API    Sprite_SetPos (Sprite* spr, float x, float y);
YAGL_DECLARE(Sub, Sprite_SetPos) (As Sprite Ptr, As Single, As Single)
'void        YAGL_API    Sprite_GetPos (Sprite* spr, float* x, float* y);
YAGL_DECLARE(Sub, Sprite_GetPos) (As Sprite Ptr, As Single Ptr, As Single Ptr)

'void        YAGL_API    Sprite_SetSize (Sprite* spr, float w, float h);
YAGL_DECLARE(Sub, Sprite_SetSize) (As Sprite Ptr, As Single, As Single)
'void        YAGL_API    Sprite_GetSize (Sprite* spr, float* w, float* h);
YAGL_DECLARE(Sub, Sprite_GetSize) (As Sprite Ptr, As Single Ptr, As Single Ptr)

'void        YAGL_API    Sprite_SetCenter (Sprite* spr, float x, float y);
YAGL_DECLARE(Sub, Sprite_SetCenter) (As Sprite Ptr, As Single, As Single)
'void        YAGL_API    Sprite_GetCenter (Sprite* spr, float* x, float* y);
YAGL_DECLARE(Sub, Sprite_GetCenter) (As Sprite Ptr, As Single Ptr, As Single Ptr)

'void        YAGL_API    Sprite_SetAngle (Sprite* spr, float angle);
YAGL_DECLARE(Sub, Sprite_SetAngle) (As Sprite Ptr, As Single)
'float       YAGL_API    Sprite_GetAngle (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetAngle) (As Sprite Ptr) As Single

'void        YAGL_API    Sprite_SetBlendMode (Sprite* spr, eBLEND_MODE blend_mode);
YAGL_DECLARE(Sub, Sprite_SetBlendMode) (As Sprite Ptr, As eBLEND_MODE)
'int         YAGL_API    Sprite_GetBlendMode (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetBlendMode) (As Sprite Ptr) As eBLEND_MODE

'void        YAGL_API    Sprite_SetColor (Sprite* spr, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
YAGL_DECLARE(Sub, Sprite_SetColor) (As Sprite Ptr, As UByte, As UByte, As UByte, As UByte)
'void        YAGL_API    Sprite_GetColor (Sprite* spr, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a);
YAGL_DECLARE(Sub, Sprite_GetColor) (As Sprite Ptr, As UByte Ptr, As UByte Ptr, As UByte Ptr, As UByte Ptr)
'void        YAGL_API    Sprite_SetColorEx (Sprite* spr, YAGL_Color color);
YAGL_DECLARE(Sub, Sprite_SetColorEx) (As Sprite Ptr, As YAGL_COLOR)
'YAGL_Color  YAGL_API    Sprite_GetColorEx (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetColorEx) (As Sprite Ptr) As YAGL_COLOR

'void        YAGL_API    Sprite_SetVel (Sprite* spr, float x, float y);
YAGL_DECLARE(Sub, Sprite_SetVel) (As Sprite Ptr, As Single, As Single)
'void        YAGL_API    Sprite_SetVelMax (Sprite* spr, float max);
YAGL_DECLARE(Sub, Sprite_SetVelMax) (As Sprite Ptr, As Single)
'void        YAGL_API    Sprite_GetVel (Sprite* spr, float* x, float* y);
YAGL_DECLARE(Sub, Sprite_GetVel) (As Sprite Ptr, As Single Ptr, As Single Ptr)
'float       YAGL_API    Sprite_GetVelLen (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetVelLen) (As Sprite Ptr) As Single
'float       YAGL_API    Sprite_GetVelAngle (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetVelAngle) (As Sprite Ptr) As Single
'float       YAGL_API    Sprite_GetVelMax (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetVelMax) (As Sprite Ptr) As Single

'void        YAGL_API    Sprite_SetAccel (Sprite* spr, float x, float y);
YAGL_DECLARE(Sub, Sprite_SetAccel) (As Sprite Ptr, As Single, As Single)
'void        YAGL_API    Sprite_GetAccel (Sprite* spr, float* x, float* y);
YAGL_DECLARE(Sub, Sprite_GetAccel) (As Sprite Ptr, As Single Ptr, As Single Ptr)
'float       YAGL_API    Sprite_GetAccelLen (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetAccelLen) (As Sprite Ptr) As Single
'float       YAGL_API    Sprite_GetAccelAngle (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetAccelAngle) (As Sprite Ptr) As Single

'void        YAGL_API    Sprite_SetInnertia (Sprite* spr, float innertia);
YAGL_DECLARE(Sub, Sprite_SetInnertia) (As Sprite Ptr, As Single)
'float       YAGL_API    Sprite_GetInnertia (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetInnertia) (As Sprite Ptr) As Single

'void        YAGL_API    Sprite_SetAVel (Sprite* spr, float avel);
YAGL_DECLARE(Sub, Sprite_SetAVel) (As Sprite Ptr, As Single)
'void        YAGL_API    Sprite_SetAVelMax (Sprite* spr, float max);
YAGL_DECLARE(Sub, Sprite_SetAVelMax) (As Sprite Ptr, As Single)
'float       YAGL_API    Sprite_GetAVel (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetAVel) (As Sprite Ptr) As Single
'float       YAGL_API    Sprite_GetAVelMax (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetAVelMax) (As Sprite Ptr) As Single

'void        YAGL_API    Sprite_SetAAccel (Sprite* spr, float aaccel);
YAGL_DECLARE(Sub, Sprite_SetAAccel) (As Sprite Ptr, As Single)
'float       YAGL_API    Sprite_GetAAccel (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetAAccel) (As Sprite Ptr) As Single

'void        YAGL_API    Sprite_SetAInnertia (Sprite* spr, float ainnertia);
YAGL_DECLARE(Sub, Sprite_SetAInnertia) (As Sprite Ptr, As Single)
'float       YAGL_API    Sprite_GetAInnertia (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetAInnertia) (As Sprite Ptr) As Single

'void        YAGL_API    Sprite_SetParentV (Sprite* spr, Sprite* spr_parent);
YAGL_DECLARE(Sub, Sprite_SetParentV) (As Sprite Ptr, As Sprite Ptr)
'void        YAGL_API    Sprite_SetParentA (Sprite* spr, Sprite* spr_parent);
YAGL_DECLARE(Sub, Sprite_SetParentA) (As Sprite Ptr, As Sprite Ptr)
'Sprite*     YAGL_API    Sprite_GetParentV (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetParentV) (As Sprite Ptr) As Sprite Ptr
'Sprite*     YAGL_API    Sprite_GetParentA (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetParentA) (As Sprite Ptr) As Sprite Ptr

'void        YAGL_API    Sprite_SetAttachedData (Sprite* spr, void* data);
YAGL_DECLARE(Sub, Sprite_SetAttachedData) (As Sprite Ptr, As Any Ptr)
'void*       YAGL_API    Sprite_GetAttachedData (Sprite* spr);
YAGL_DECLARE(Function, Sprite_GetAttachedData) (As Sprite Ptr) As Any Ptr

'/' Sprite Set '/
'SpriteSet*  YAGL_API    SpriteSet_Create ();
YAGL_DECLARE(Function, SpriteSet_Create) () As SpriteSet Ptr
'int   YAGL_API    SpriteSet_IsSpriteSet (SpriteSet* spr_set);
YAGL_DECLARE(Function, SpriteSet_IsSpriteSet) (As SpriteSet Ptr) As Integer
'int   YAGL_API    SpriteSet_Destroy (SpriteSet* spr_set, int destroy);
YAGL_DECLARE(Function, SpriteSet_Destroy) (As SpriteSet Ptr, As Integer) As Integer

'void        YAGL_API    SpriteSet_Add (SpriteSet* spr_set, Sprite* spr);
YAGL_DECLARE(Sub, SpriteSet_Add) (As SpriteSet Ptr, As Sprite Ptr)
'int         YAGL_API    SpriteSet_Exists (SpriteSet* spr_set, Sprite* spr);
YAGL_DECLARE(Function, SpriteSet_Exists) (As SpriteSet Ptr, As Sprite Ptr) As Integer
'void        YAGL_API    SpriteSet_Del (SpriteSet* spr_set, Sprite* spr, int destroy);
YAGL_DECLARE(Sub, SpriteSet_Del) (As SpriteSet Ptr, As Sprite Ptr, As Integer)
'void        YAGL_API    SpriteSet_DelAll (SpriteSet* spr_set, int destroy);
YAGL_DECLARE(Sub, SpriteSet_DelAll) (As SpriteSet Ptr, As Integer)

'void        YAGL_API    SpriteSet_SetColor (SpriteSet* spr_set, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
YAGL_DECLARE(Sub, SpriteSet_SetColor) (As SpriteSet Ptr, As UByte, As UByte, As UByte, As UByte)
'void        YAGL_API    SpriteSet_SetColorEx (SpriteSet* spr_set, YAGL_Color color);
YAGL_DECLARE(Sub, SpriteSet_SetColorEx) (As SpriteSet Ptr, As YAGL_COLOR)
'void        YAGL_API    SpriteSet_SetBlendMode (SpriteSet* spr_set, eBLEND_MODE blend_mode);
YAGL_DECLARE(Sub, SpriteSet_SetBlendMode) (As SpriteSet Ptr, As eBLEND_MODE)
'void        YAGL_API    SpriteSet_SetVisible (SpriteSet* spr_set, int visible);
YAGL_DECLARE(Sub, SpriteSet_SetVisible) (As SpriteSet Ptr, As Integer)
'void        YAGL_API    SpriteSet_SetDynamic (SpriteSet* spr_set, int dynamic);
YAGL_DECLARE(Sub, SpriteSet_SetDynamic) (As SpriteSet Ptr, As Integer)

'int         YAGL_API    SpriteSet_Collide (SpriteSet* spr_set, Sprite* spr, int force_check, int must_touch_all);
YAGL_DECLARE(Function, SpriteSet_Collide) (As SpriteSet Ptr, As Sprite Ptr, As Integer, As Integer) As Integer

'void        YAGL_API    SpriteSet_Draw (SpriteSet* spr_set);
YAGL_DECLARE(Sub, SpriteSet_Draw) (As SpriteSet Ptr)
'void        YAGL_API    SpriteSet_DrawShapes (SpriteSet* spr_set);
YAGL_DECLARE(Sub, SpriteSet_DrawShapes) (As SpriteSet Ptr)

'int         YAGL_API    SpriteSet_Count (SpriteSet* spr_set);
YAGL_DECLARE(Function, SpriteSet_Count) (As SpriteSet Ptr) As Integer
'int         YAGL_API    SpriteSet_GetAll (SpriteSet* spr_set, Sprite* spr[], int size);
YAGL_DECLARE(Function, SpriteSet_GetAll) (As SpriteSet Ptr, As Sprite Ptr Ptr, As Integer) As Integer
'int         YAGL_API    SpriteSet_Iterate (SpriteSet* spr_set, YAGLSpriteSetIterateProc iterate_proc, void* user_data);
YAGL_DECLARE(Function, SpriteSet_Iterate) (As SpriteSet Ptr, As YAGLSpriteSetIterateProc, As Any Ptr) As Integer

'/' Animation '/
'Animation*      YAGL_API    Animation_Create (unsigned int frames_count);
YAGL_DECLARE(Function, Animation_Create) (As UInteger) As Animation Ptr
'int       YAGL_API    Animation_IsAnimation (Animation* anim);
YAGL_DECLARE(Function, Animation_IsAnimation) (As Animation Ptr) As Integer

'int             YAGL_API    Animation_AddFrameEx (Animation* anim, float duration, Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h, YAGL_Color color, eBLEND_MODE blend_mode, int change_size, float size_x, float size_y);
YAGL_DECLARE(Function, Animation_AddFrameEx) (As Animation Ptr, As Single, As Texture Ptr, As Integer, As Integer, As Integer, As Integer, As YAGL_COLOR, As eBLEND_MODE, As Integer, As Single, As Single) As Integer
'int             YAGL_API    Animation_AddFrame (Animation* anim, float duration);
YAGL_DECLARE(Function, Animation_AddFrame) (As Animation Ptr, As Single) As Integer
'void            YAGL_API    Animation_FrameSetBlank (Animation* anim, unsigned int frame_id);
YAGL_DECLARE(Sub, Animation_FrameSetBlank) (As Animation Ptr, As UInteger)
'int             YAGL_API    Animation_FrameCount (Animation* anim);
YAGL_DECLARE(Function, Animation_FrameCount) (As Animation Ptr) As Integer
'int             YAGL_API    Animation_FrameMax (Animation* anim);
YAGL_DECLARE(Function, Animation_FrameMax) (As Animation Ptr) As Integer
'void            YAGL_API    Animation_Empty (Animation* anim);
YAGL_DECLARE(Sub, Animation_Empty) (As Animation Ptr)

'void        YAGL_API    Animation_SetTimerMult (Animation* anim, float tm);
YAGL_DECLARE(Sub, Animation_SetTimerMult) (As Animation Ptr, As Single)
'float       YAGL_API    Animation_GetTimerMult (Animation* anim);
YAGL_DECLARE(Function, Animation_GetTimerMult) (As Animation Ptr) As Single

'int       YAGL_API    Animation_Destroy (Animation* anim);
YAGL_DECLARE(Function, Animation_Destroy) (As Animation Ptr) As Integer

'void            YAGL_API    Animation_FrameSetDuration (Animation* anim, unsigned int frame_id, float duration);
YAGL_DECLARE(Sub, Animation_FrameSetDuration) (As Animation Ptr, As UInteger, As Single)
'void            YAGL_API    Animation_FrameSetTexture (Animation* anim, unsigned int frame_id, Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h);
YAGL_DECLARE(Sub, Animation_FrameSetTexture) (As Animation Ptr, As UInteger, As Texture Ptr, As Integer, As Integer, As Integer, As Integer)
'void            YAGL_API    Animation_FrameSetColor (Animation* anim, unsigned int frame_id, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
YAGL_DECLARE(Sub, Animation_FrameSetColor) (As Animation Ptr, As UInteger, As UByte, As UByte, As UByte, As UByte)
'void            YAGL_API    Animation_FrameSetColorEx (Animation* anim, unsigned int frame_id, YAGL_Color color);
YAGL_DECLARE(Sub, Animation_FrameSetColorEx) (As Animation Ptr, As UInteger, As YAGL_COLOR)
'void            YAGL_API    Animation_FrameSetBlendMode (Animation* anim, unsigned int frame_id, eBLEND_MODE blend_mode);
YAGL_DECLARE(Sub, Animation_FrameSetBlendMode) (As Animation Ptr, As UInteger, As eBLEND_MODE)
'void            YAGL_API    Animation_FrameSetSize (Animation* anim, unsigned int frame_id, int change_size, float size_x, float size_y);
YAGL_DECLARE(Sub, Animation_FrameSetSize) (As Animation Ptr, As UInteger, As Integer, As Single, As Single)

'float           YAGL_API    Animation_FrameGetDuration (Animation* anim, unsigned int frame_id);
YAGL_DECLARE(Function, Animation_FrameGetDuration) (As Animation Ptr, As UInteger) As Single
'Texture*        YAGL_API    Animation_FrameGetTexture (Animation* anim, unsigned int frame_id, int* rect_x, int* rect_y, int* rect_w, int* rect_h);
YAGL_DECLARE(Function, Animation_FrameGetTexture) (As Animation Ptr, As UInteger, As Integer Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr) As Texture Ptr
'void            YAGL_API    Animation_FrameGetColor (Animation* anim, unsigned int frame_id, unsigned char* red, unsigned char* green, unsigned char* blue, unsigned char* alpha);
YAGL_DECLARE(Sub, Animation_FrameGetColor) (As Animation Ptr, As UInteger, As UByte Ptr, As UByte Ptr, As UByte Ptr, As UByte Ptr)
'YAGL_Color      YAGL_API    Animation_FrameGetColorEx (Animation* anim, unsigned int frame_id);
YAGL_DECLARE(Function, Animation_FrameGetColorEx) (As Animation Ptr, As UInteger) As YAGL_COLOR
'eBLEND_MODE     YAGL_API    Animation_FrameGetBlendMode (Animation* anim, unsigned int frame_id);
YAGL_DECLARE(Function, Animation_FrameGetBlendMode) (As Animation Ptr, As UInteger) As eBLEND_MODE
'int       YAGL_API    Animation_FrameGetSize (Animation* anim, unsigned int frame_id, float* size_x, float* size_y);
YAGL_DECLARE(Function, Animation_FrameGetSize) (As Animation Ptr, As UInteger, As Single Ptr, As Single Ptr) As Integer

'/' Collision '/
'void    YAGL_API    Collision_SetCallback (YAGLCollisionProc proc);
YAGL_DECLARE(Sub, Collision_SetCallback) (As YAGLCollisionProc)
'void    YAGL_API    Collision_Process ();
YAGL_DECLARE(Sub, Collision_Process) ()
'void    YAGL_API    Collision_SetAutoProcess(int status);
YAGL_DECLARE(Sub, Collision_SetAutoProcess) (As Integer)
'int     YAGL_API    Collision_Check (Sprite* spr1, Sprite* spr2, int force_check);
YAGL_DECLARE(Function, Collision_Check) (As Sprite Ptr, As Sprite Ptr, As Integer) As Integer

'/' Particles '/
'PEmitter*   YAGL_API    PEmitter_Create (Texture* tex, int rect_x, int rect_y, int rect_w, int rect_h);
YAGL_DECLARE(Function, PEmitter_Create) (As Texture Ptr, As Integer, As Integer, As Integer, As Integer) As PEmitter Ptr
'int   YAGL_API    PEmitter_IsPEmitter (PEmitter* emit);
YAGL_DECLARE(Function, PEmitter_IsPEmitter) (As PEmitter Ptr) As Integer
'int         YAGL_API    PEmitter_ReadCfg (PEmitter* emit, const char* file, const char* section, int load_tex_rect);
YAGL_DECLARE(Function, PEmitter_ReadCfg) (As PEmitter Ptr, As Const ZString, As Const ZString, As Integer) As Integer
'int         YAGL_API    PEmitter_WriteCfg (PEmitter* emit, const char* file, const char* section, int save_tex_rect);
YAGL_DECLARE(Function, PEmitter_WriteCfg) (As PEmitter Ptr, As Const ZString, As Const ZString, As Integer) As Integer
'int   YAGL_API    PEmitter_Copy (PEmitter* source, PEmitter* dest, int copy_texture);
YAGL_DECLARE(Function, PEmitter_Copy) (As PEmitter Ptr, As PEmitter Ptr, As Integer) As Integer
'void        YAGL_API    PEmitter_SetTexture (PEmitter* emit, Texture* tex);
YAGL_DECLARE(Sub, PEmitter_SetTexture) (As PEmitter Ptr, As Texture Ptr)
'Texture*    YAGL_API    PEmitter_GetTexture (PEmitter* emit);
YAGL_DECLARE(Function, PEmitter_GetTexture) (As PEmitter Ptr) As Texture Ptr
'void        YAGL_API    PEmitter_SetTextureRect (PEmitter* emit, int rect_x, int rect_y, int rect_w, int rect_h);
YAGL_DECLARE(Sub, PEmitter_SetTextureRect) (As PEmitter Ptr, As Integer, As Integer, As Integer, As Integer)
'void        YAGL_API    PEmitter_GetTextureRect (PEmitter* emit, int* rect_x, int* rect_y, int* rect_w, int* rect_h);
YAGL_DECLARE(Sub, PEmitter_GetTextureRect) (As PEmitter Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr, As Integer Ptr)
'void        YAGL_API    PEmitter_SetTextureMap (PEmitter* emit, TextureMap* tex_map, unsigned int rect_id);
YAGL_DECLARE(Sub, PEmitter_SetTextureMap) (As PEmitter Ptr, As TextureMap Ptr, As UInteger)
'void        YAGL_API    PEmitter_SetActive (PEmitter* emit, int status);
YAGL_DECLARE(Sub, PEmitter_SetActive) (As PEmitter Ptr, As Integer)
'int	YAGL_API	PEmitter_GetActive (PEmitter* emit);
YAGL_DECLARE(Function, PEmitter_GetActive) (As PEmitter Ptr) As Integer
'void        YAGL_API    PEmitter_Emitte (PEmitter* emit, unsigned int nbr);
YAGL_DECLARE(Sub, PEmitter_Emitte) (As PEmitter Ptr, As UInteger)
'void        YAGL_API    PEmitter_EmitteAt (PEmitter* emit, float x, float y, unsigned int nbr)
YAGL_DECLARE(Sub, PEmitter_EmitteAt) (As PEmitter Ptr, As Single, As Single, As UInteger)
'void        YAGL_API    PEmitter_Draw (PEmitter* emit);
YAGL_DECLARE(Sub, PEmitter_Draw) (As PEmitter Ptr)
'int   YAGL_API    PEmitter_Destroy (PEmitter* emit);
YAGL_DECLARE(Function, PEmitter_Destroy) (As PEmitter Ptr) As Integer

'/' Particles Emitter Accessors '/
'void            YAGL_API    PEmitter_SetVisible (PEmitter* emit, int visible);
YAGL_DECLARE(Sub, PEmitter_SetVisible) (As PEmitter Ptr, As Integer)
'int             YAGL_API    PEmitter_GetVisible (PEmitter* emit);
YAGL_DECLARE(Function, PEmitter_GetVisible) (As PEmitter Ptr) As Integer

'void            YAGL_API    PEmitter_SetPos (PEmitter* emit, float x, float y);
YAGL_DECLARE(Sub, PEmitter_SetPos) (As PEmitter Ptr, As Single, As Single)
'void            YAGL_API    PEmitter_GetPos (PEmitter* emit, float* x, float* y);
YAGL_DECLARE(Sub, PEmitter_GetPos) (As PEmitter Ptr, As Single Ptr, As Single Ptr)

'void            YAGL_API    PEmitter_SetPosVar (PEmitter* emit, float x, float y);
YAGL_DECLARE(Sub, PEmitter_SetPosVar) (As PEmitter Ptr, As Single, As Single)
'void            YAGL_API    PEmitter_GetPosVar (PEmitter* emit, float* x, float* y);
YAGL_DECLARE(Sub, PEmitter_GetPosVar) (As PEmitter Ptr, As Single Ptr, As Single Ptr)

'void            YAGL_API    PEmitter_SetVel (PEmitter* emit, float vel, float vel_var);
YAGL_DECLARE(Sub, PEmitter_SetVel) (As PEmitter Ptr, As Single, As Single)
'void            YAGL_API    PEmitter_GetVel (PEmitter* emit, float* vel, float* vel_var);
YAGL_DECLARE(Sub, PEmitter_GetVel) (As PEmitter Ptr, As Single Ptr, As Single Ptr)

'void            YAGL_API    PEmitter_SetAccel (PEmitter* emit, float accel, float accel_var);
YAGL_DECLARE(Sub, PEmitter_SetAccel) (As PEmitter Ptr, As Single, As Single)
'void            YAGL_API    PEmitter_GetAccel (PEmitter* emit, float* accel, float* accel_var);
YAGL_DECLARE(Sub, PEmitter_GetAccel) (As PEmitter Ptr, As Single Ptr, As Single Ptr)

'void            YAGL_API    PEmitter_SetAngle (PEmitter* emit, float angle, float angle_var);
YAGL_DECLARE(Sub, PEmitter_SetAngle) (As PEmitter Ptr, As Single, As Single)
'void            YAGL_API    PEmitter_GetAngle (PEmitter* emit, float* angle, float* angle_var);
YAGL_DECLARE(Sub, PEmitter_GetAngle) (As PEmitter Ptr, As Single Ptr, As Single Ptr)

'void            YAGL_API    PEmitter_SetForce (PEmitter* emit, float force, float force_var);
YAGL_DECLARE(Sub, PEmitter_SetForce) (As PEmitter Ptr, As Single, As Single)
'void            YAGL_API    PEmitter_GetForce (PEmitter* emit, float* force, float* force_var);
YAGL_DECLARE(Sub, PEmitter_GetForce) (As PEmitter Ptr, As Single Ptr, As Single Ptr)

'void            YAGL_API    PEmitter_SetForceAngle (PEmitter* emit, float f_angle, float f_angle_var);
YAGL_DECLARE(Sub, PEmitter_SetForceAngle) (As PEmitter Ptr, As Single, As Single)
'void            YAGL_API    PEmitter_GetForceAngle (PEmitter* emit, float* f_angle, float* f_angle_var);
YAGL_DECLARE(Sub, PEmitter_GetForceAngle) (As PEmitter Ptr, As Single Ptr, As Single Ptr)

'void            YAGL_API    PEmitter_SetInnertia (PEmitter* emit, float innertia, float innertia_var);
YAGL_DECLARE(Sub, PEmitter_SetInnertia) (As PEmitter Ptr, As Single, As Single)
'void            YAGL_API    PEmitter_GetInnertia (PEmitter* emit, float* innertia, float* innertia_var);
YAGL_DECLARE(Sub, PEmitter_GetInnertia) (As PEmitter Ptr, As Single Ptr, As Single Ptr)

'void            YAGL_API    PEmitter_SetParticleAngle (PEmitter* emit, float angle, float angle_var);
YAGL_DECLARE(Sub, PEmitter_SetParticleAngle) (As PEmitter Ptr, As Single, As Single)
'void            YAGL_API    PEmitter_GetParticleAngle (PEmitter* emit, float* angle, float* angle_var);
YAGL_DECLARE(Sub, PEmitter_GetParticleAngle) (As PEmitter Ptr, As Single Ptr, As Single Ptr)

'void            YAGL_API    PEmitter_SetSpin (PEmitter* emit, float spin, float spin_var, float spin_flyvar);
YAGL_DECLARE(Sub, PEmitter_SetSpin) (As PEmitter Ptr, As Single, As Single, As Single)
'void            YAGL_API    PEmitter_GetSpin (PEmitter* emit, float* spin, float* spin_var, float* spin_flyvar);
YAGL_DECLARE(Sub, PEmitter_GetSpin) (As PEmitter Ptr, As Single Ptr, As Single Ptr, As Single Ptr)

'void            YAGL_API    PEmitter_SetSize (PEmitter* emit, float size, float size_var, float size_flyvar);
YAGL_DECLARE(Sub, PEmitter_SetSize) (As PEmitter Ptr, As Single, As Single, As Single)
'void            YAGL_API    PEmitter_GetSize (PEmitter* emit, float* size, float* size_var, float* size_flyvar);
YAGL_DECLARE(Sub, PEmitter_GetSize) (As PEmitter Ptr, As Single Ptr, As Single Ptr, As Single Ptr)

'void            YAGL_API    PEmitter_SetLife (PEmitter* emit, float life, float life_var);
YAGL_DECLARE(Sub, PEmitter_SetLife) (As PEmitter Ptr, As Single, As Single)
'void            YAGL_API    PEmitter_GetLife (PEmitter* emit, float* life, float* life_var);
YAGL_DECLARE(Sub, PEmitter_GetLife) (As PEmitter Ptr, As Single Ptr, As Single Ptr)

'void            YAGL_API    PEmitter_SetEmitteRate (PEmitter* emit, unsigned int particles_per_second);
YAGL_DECLARE(Sub, PEmitter_SetEmitteRate) (As PEmitter Ptr, As UInteger)
'unsigned int    YAGL_API    PEmitter_GetEmitteRate (PEmitter* emit);
YAGL_DECLARE(Function, PEmitter_GetEmitteRate) (As PEmitter Ptr) As UInteger

'void            YAGL_API    PEmitter_SetMaxParticles (PEmitter* emit, unsigned int max);
YAGL_DECLARE(Sub, PEmitter_SetMaxParticles) (As PEmitter Ptr, As UInteger)
'unsigned int    YAGL_API    PEmitter_GetMaxParticles (PEmitter* emit);
YAGL_DECLARE(Function, PEmitter_GetMaxParticles) (As PEmitter Ptr) As UInteger

'void            YAGL_API    PEmitter_SetBlendMode (PEmitter* emit, eBLEND_MODE blend_mode);
YAGL_DECLARE(Sub, PEmitter_SetBlendMode) (As PEmitter Ptr, As eBLEND_MODE)
'int             YAGL_API    PEmitter_GetBlendMode (PEmitter* emit);
YAGL_DECLARE(Function, PEmitter_GetBlendMode) (As PEmitter Ptr) As eBLEND_MODE

'void            YAGL_API    PEmitter_SetColor (PEmitter* emit, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
YAGL_DECLARE(Sub, PEmitter_SetColor) (As PEmitter Ptr, As UByte, As UByte, As UByte, As UByte)
'void            YAGL_API    PEmitter_SetColorVar (PEmitter* emit, short r, short g, short b, short a);
YAGL_DECLARE(Sub, PEmitter_SetColorVar) (As PEmitter Ptr, As Short, As Short, As Short, As Short)
'void            YAGL_API    PEmitter_SetColorFlyVar (PEmitter* emit, short r, short g, short b, short a);
YAGL_DECLARE(Sub, PEmitter_SetColorFlyVar) (As PEmitter Ptr, As Short, As Short, As Short, As Short)
'void            YAGL_API    PEmitter_GetColor (PEmitter* emit, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a);
YAGL_DECLARE(Sub, PEmitter_GetColor) (As PEmitter Ptr, As UByte Ptr, As UByte Ptr, As UByte Ptr, As UByte Ptr)
'void            YAGL_API    PEmitter_GetColorVar (PEmitter* emit, short* r, short* g, short* b, short* a);
YAGL_DECLARE(Sub, PEmitter_GetColorVar) (As PEmitter Ptr, As Short Ptr, As Short Ptr, As Short Ptr, As Short Ptr)
'void            YAGL_API    PEmitter_GetColorFlyVar (PEmitter* emit, short* r, short* g, short* b, short* a);
YAGL_DECLARE(Sub, PEmitter_GetColorFlyVar) (As PEmitter Ptr, As Short Ptr, As Short Ptr, As Short Ptr, As Short Ptr)

'void            YAGL_API    PEmitter_SetCallbacks (PEmitter* emit, YAGLParticleSpawnProc emitte_proc, YAGLParticleDeadProc dead_proc);
YAGL_DECLARE(Sub, PEmitter_SetCallbacks) (As PEmitter Ptr, As YAGLParticleSpawnProc, As YAGLParticleDeadProc)

'unsigned int    YAGL_API    PEmitter_GetCount (PEmitter* emit);
YAGL_DECLARE(Function, PEmitter_GetCount) (As PEmitter Ptr) As UInteger

'/' Shaders '/
'int   YAGL_API    Shader_Init (const int fatal_fail);
YAGL_DECLARE(Function, Shader_Init) (As Const Integer) As Integer
'int   YAGL_API    Shader_IsInit ();
YAGL_DECLARE(Function, Shader_IsInit) () As Integer
'void        YAGL_API    Shader_SetCompileErrFatal (const int flag);
YAGL_DECLARE(Sub, Shader_SetCompileErrFatal) (As Const Integer)
'void        YAGL_API    Shader_SetLinkErrFatal (const int flag);
YAGL_DECLARE(Sub, Shader_SetLinkErrFatal) (As Const Integer)
'void        YAGL_API    Shader_SetInfoLogShow (const int flag);
YAGL_DECLARE(Sub, Shader_SetInfoLogShow) (As Const Integer)
'Shader*     YAGL_API    Shader_Create ();
YAGL_DECLARE(Function, Shader_Create) () As Shader Ptr
'int   YAGL_API    Shader_IsShader (Shader* shd);
YAGL_DECLARE(Function, Shader_IsShader) (As Shader Ptr) As Integer
'int   YAGL_API    Shader_AddSource (Shader* shd, const char* source, eSHADER_TYPE type);
YAGL_DECLARE(Function, Shader_AddSource) (As Shader Ptr, As Const ZString, As eSHADER_TYPE) As Integer
'int   YAGL_API    Shader_AddSourceFile (Shader* shd, const char* filepath, eSHADER_TYPE type);
YAGL_DECLARE(Function, Shader_AddSourceFile) (As Shader Ptr, As Const ZString, As eSHADER_TYPE) As Integer
'int   YAGL_API    Shader_Link (Shader* shd);
YAGL_DECLARE(Function, Shader_Link) (As Shader Ptr) As Integer
'int   YAGL_API    Shader_IsReady (Shader* shd);
YAGL_DECLARE(Function, Shader_IsReady) (As Shader Ptr) As Integer
'int   YAGL_API    Shader_Destroy (Shader* shd);
YAGL_DECLARE(Function, Shader_Destroy) (As Shader Ptr) As Integer
'void        YAGL_API    Shader_Use (Shader* shd);
YAGL_DECLARE(Sub, Shader_Use) (As Shader Ptr)

'int         YAGL_API    Shader_UniformGetLocation (Shader* shd, const char* name);
YAGL_DECLARE(Function, Shader_UniformGetLocation) (As Shader Ptr, As ZString) As Integer
'void        YAGL_API    Shader_UniformGetActive (Shader* shd, int id, int* lenght, int* size, eSHADER_UNIFORM_TYPE* type, char* name, unsigned int name_len);
YAGL_DECLARE(Sub, Shader_UniformGetActive) (As Shader Ptr, As Integer, As Integer Ptr, As eSHADER_UNIFORM_TYPE, As ZString, As Integer)
'void        YAGL_API    Shader_UniformGetF (Shader* shd, int id, float* data);
YAGL_DECLARE(Sub, Shader_UniformGetF) (As Shader Ptr, As Integer, As Single Ptr)
'void        YAGL_API    Shader_UniformGetI (Shader* shd, int id, int* data);
YAGL_DECLARE(Sub, Shader_UniformGetI) (As Shader Ptr, As Integer, As Integer Ptr)

'void        YAGL_API    Shader_UniformSet1F (int id, float v1);
YAGL_DECLARE(Sub, Shader_UniformSet1F) (As Integer, As Single)
'void        YAGL_API    Shader_UniformSet2F (int id, float v1, float v2);
YAGL_DECLARE(Sub, Shader_UniformSet2F) (As Integer, As Single, As Single)
'void        YAGL_API    Shader_UniformSet3F (int id, float v1, float v2, float v3);
YAGL_DECLARE(Sub, Shader_UniformSet3F) (As Integer, As Single, As Single, As Single)
'void        YAGL_API    Shader_UniformSet4F (int id, float v1, float v2, float v3, float v4);
YAGL_DECLARE(Sub, Shader_UniformSet4F) (As Integer, As Single, As Single, As Single, As Single)
'void        YAGL_API    Shader_UniformSet1I (int id, int v1);
YAGL_DECLARE(Sub, Shader_UniformSet1I) (As Integer, As Single)
'void        YAGL_API    Shader_UniformSet2I (int id, int v1, int v2);
YAGL_DECLARE(Sub, Shader_UniformSet2I) (As Integer, As Single, As Single)
'void        YAGL_API    Shader_UniformSet3I (int id, int v1, int v2, int v3);
YAGL_DECLARE(Sub, Shader_UniformSet3I) (As Integer, As Single, As Single, As Single)
'void        YAGL_API    Shader_UniformSet4I (int id, int v1, int v2, int v3, int v4);
YAGL_DECLARE(Sub, Shader_UniformSet4I) (As Integer, As Single, As Single, As Single, As Single)

'void        YAGL_API    Shader_UniformSet1Fv (int id, int count, float* v);
YAGL_DECLARE(Sub, Shader_UniformSet1Fv) (As Integer, As Integer, As Single Ptr)
'void        YAGL_API    Shader_UniformSet2Fv (int id, int count, float* v);
YAGL_DECLARE(Sub, Shader_UniformSet2Fv) (As Integer, As Integer, As Single Ptr)
'void        YAGL_API    Shader_UniformSet3Fv (int id, int count, float* v);
YAGL_DECLARE(Sub, Shader_UniformSet3Fv) (As Integer, As Integer, As Single Ptr)
'void        YAGL_API    Shader_UniformSet4Fv (int id, int count, float* v);
YAGL_DECLARE(Sub, Shader_UniformSet4Fv) (As Integer, As Integer, As Single Ptr)
'void        YAGL_API    Shader_UniformSet1Iv (int id, int count, int* v);
YAGL_DECLARE(Sub, Shader_UniformSet1Iv) (As Integer, As Integer, As Integer Ptr)
'void        YAGL_API    Shader_UniformSet2Iv (int id, int count, int* v);
YAGL_DECLARE(Sub, Shader_UniformSet2Iv) (As Integer, As Integer, As Integer Ptr)
'void        YAGL_API    Shader_UniformSet3Iv (int id, int count, int* v);
YAGL_DECLARE(Sub, Shader_UniformSet3Iv) (As Integer, As Integer, As Integer Ptr)
'void        YAGL_API    Shader_UniformSet4Iv (int id, int count, int* v);
YAGL_DECLARE(Sub, Shader_UniformSet4Iv) (As Integer, As Integer, As Integer Ptr)

'void        YAGL_API    Shader_UniformMatrixSet2Fv (int id, int count, int transpose, float* v);
YAGL_DECLARE(Sub, Shader_UniformMatrixSet2Fv) (As Integer, As Integer, As Integer, As Single Ptr)
'void        YAGL_API    Shader_UniformMatrixSet3Fv (int id, int count, int transpose, float* v);
YAGL_DECLARE(Sub, Shader_UniformMatrixSet3Fv) (As Integer, As Integer, As Integer, As Single Ptr)
'void        YAGL_API    Shader_UniformMatrixSet4Fv (int id, int count, int transpose, float* v);
YAGL_DECLARE(Sub, Shader_UniformMatrixSet4Fv) (As Integer, As Integer, As Integer, As Single Ptr)
'void        YAGL_API    Shader_UniformMatrixSet2x3Fv (int id, int count, int transpose, float* v);
YAGL_DECLARE(Sub, Shader_UniformMatrixSet2x3Fv) (As Integer, As Integer, As Integer, As Single Ptr)
'void        YAGL_API    Shader_UniformMatrixSet3x2Fv (int id, int count, int transpose, float* v);
YAGL_DECLARE(Sub, Shader_UniformMatrixSet3x2Fv) (As Integer, As Integer, As Integer, As Single Ptr)
'void        YAGL_API    Shader_UniformMatrixSet2x4Fv (int id, int count, int transpose, float* v);
YAGL_DECLARE(Sub, Shader_UniformMatrixSet2x4Fv) (As Integer, As Integer, As Integer, As Single Ptr)
'void        YAGL_API    Shader_UniformMatrixSet4x2Fv (int id, int count, int transpose, float* v);
YAGL_DECLARE(Sub, Shader_UniformMatrixSet4x2Fv) (As Integer, As Integer, As Integer, As Single Ptr)
'void        YAGL_API    Shader_UniformMatrixSet3x4Fv (int id, int count, int transpose, float* v);
YAGL_DECLARE(Sub, Shader_UniformMatrixSet3x4Fv) (As Integer, As Integer, As Integer, As Single Ptr)
'void        YAGL_API    Shader_UniformMatrixSet4x3Fv (int id, int count, int transpose, float* v);
YAGL_DECLARE(Sub, Shader_UniformMatrixSet4x3Fv) (As Integer, As Integer, As Integer, As Single Ptr)

'/' Drawing '/
'void    YAGL_API    Draw_SetParams (YAGL_Color color, eBLEND_MODE blend_mode, int size, int glow);
YAGL_DECLARE(Sub, Draw_SetParams) (As YAGL_COLOR, As eBLEND_MODE, As Integer, As Integer)
'void    YAGL_API    Draw_SetColor (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
YAGL_DECLARE(Sub, Draw_SetColor) (As UByte, As UByte, As UByte, As UByte)
'void    YAGL_API    Draw_SetColorEx (YAGL_Color color);
YAGL_DECLARE(Sub, Draw_SetColorEx) (As YAGL_COLOR)
'void    YAGL_API    Draw_SetBlendMode (eBLEND_MODE blend_mode);
YAGL_DECLARE(Sub, Draw_SetBlendMode) (As eBLEND_MODE)
'void    YAGL_API    Draw_SetGlow (int status);
YAGL_DECLARE(Sub, Draw_SetGlow) (As Integer)
'void    YAGL_API    Draw_SetSize (int size);
YAGL_DECLARE(Sub, Draw_SetSize) (As Integer)
'void    YAGL_API    Draw_Point (int x, int y);
YAGL_DECLARE(Sub, Draw_Point) (As Integer, As Integer)
'void    YAGL_API    Draw_Points (int points[], int nbr);
YAGL_DECLARE(Sub, Draw_Points) (As Integer Ptr, As Integer)
'void    YAGL_API    Draw_Line (int x1, int y1, int x2, int y2);
YAGL_DECLARE(Sub, Draw_Line) (As Integer, As Integer, As Integer, As Integer)
'void    YAGL_API    Draw_Lines (int points[], int nbr, int strip);
YAGL_DECLARE(Sub, Draw_Lines) (As Integer Ptr, As Integer, As Integer)
'void    YAGL_API    Draw_Triangle (int x1, int y1, int x2, int y2, int x3, int y3);
YAGL_DECLARE(Sub, Draw_Triangle) (As Integer, As Integer, As Integer, As Integer, As Integer, As Integer)
'void    YAGL_API    Draw_TriangleF (int x1, int y1, int x2, int y2, int x3, int y3);
YAGL_DECLARE(Sub, Draw_TriangleF) (As Integer, As Integer, As Integer, As Integer, As Integer, As Integer)
'void    YAGL_API    Draw_Rect (int x, int y, int w, int h, float angle);
YAGL_DECLARE(Sub, Draw_Rect) (As Integer, As Integer, As Integer, As Integer, As Single)
'void    YAGL_API    Draw_RectF (int x, int y, int w, int h, float angle);
YAGL_DECLARE(Sub, Draw_RectF) (As Integer, As Integer, As Integer, As Integer, As Single)
'void    YAGL_API    Draw_RectCenter (int x, int y, int w, int h, float angle);
YAGL_DECLARE(Sub, Draw_RectCenter) (As Integer, As Integer, As Integer, As Integer, As Single)
'void    YAGL_API    Draw_RectCenterF (int x, int y, int w, int h, float angle);
YAGL_DECLARE(Sub, Draw_RectCenterF) (As Integer, As Integer, As Integer, As Integer, As Single)
'void    YAGL_API    Draw_Ellipse (int x, int y, int rx, int ry, float angle, int precision);
YAGL_DECLARE(Sub, Draw_Ellipse) (As Integer, As Integer, As Integer, As Integer, As Single, As Integer)
'void    YAGL_API    Draw_EllipseF (int x, int y, int rx, int ry, float angle, int precision);
YAGL_DECLARE(Sub, Draw_EllipseF) (As Integer, As Integer, As Integer, As Integer, As Single, As Integer)
'void    YAGL_API    Draw_EllipseRect (int x, int y, int w, int h, float angle, int precision);
YAGL_DECLARE(Sub, Draw_EllipseRect) (As Integer, As Integer, As Integer, As Integer, As Single, As Integer)
'void    YAGL_API    Draw_EllipseRectF (int x, int y, int w, int h, float angle, int precision);
YAGL_DECLARE(Sub, Draw_EllipseRectF) (As Integer, As Integer, As Integer, As Integer, As Single, As Integer)

'/' Geometry '/
'float   YAGL_API    Geo_PtoP_Dist (int x1, int y1, int x2, int y2);
YAGL_DECLARE(Function, Geo_PtoP_Dist) (As Integer, As Integer, As Integer, As Integer) As Single
'float   YAGL_API    Geo_PtoP_Angle (int x1, int y1, int x2, int y2);
YAGL_DECLARE(Function, Geo_PtoP_Angle) (As Integer, As Integer, As Integer, As Integer) As Single
'void    YAGL_API    Geo_PtoP_Vect (int x1, int y1, int x2, int y2, float len, float* v_x, float* v_y);
YAGL_DECLARE(Sub, Geo_PtoP_Vect) (As Integer, As Integer, As Integer, As Integer, As Single Ptr, As Single Ptr)

'float   YAGL_API    Geo_SprtoP_Dist (Sprite* spr, int x, int y);
YAGL_DECLARE(Function, Geo_SprtoP_Dist) (As Sprite Ptr, As Integer, As Integer) As Single
'float   YAGL_API    Geo_SprtoP_Angle (Sprite* spr, int x, int y);
YAGL_DECLARE(Function, Geo_SprtoP_Angle) (As Sprite Ptr, As Integer, As Integer) As Single
'float   YAGL_API    Geo_SprtoP_AngleDiff (Sprite* spr, int x, int y);
YAGL_DECLARE(Function, Geo_SprtoP_AngleDiff) (As Sprite Ptr, As Integer, As Integer) As Single
'void    YAGL_API    Geo_SprtoP_Vect (Sprite* spr, int x, int y, float len, float* v_x, float* v_y);
YAGL_DECLARE(Sub, Geo_SprtoP_Vect) (As Sprite Ptr, As Integer, As Integer, As Single, As Single Ptr, As Single Ptr)

'float   YAGL_API    Geo_SprtoSpr_Dist (Sprite* spr1, Sprite* spr2);
YAGL_DECLARE(Function, Geo_SprtoSpr_Dist) (As Sprite Ptr, As Sprite Ptr) As Single
'float   YAGL_API    Geo_SprtoSpr_Angle (Sprite* spr1, Sprite* spr2);
YAGL_DECLARE(Function, Geo_SprtoSpr_Angle) (As Sprite Ptr, As Sprite Ptr) As Single
'float   YAGL_API    Geo_SprtoSpr_AngleDiff (Sprite* spr1, Sprite* spr2);
YAGL_DECLARE(Function, Geo_SprtoSpr_AngleDiff) (As Sprite Ptr, As Sprite Ptr) As Single
'void    YAGL_API    Geo_SprtoSpr_Vect (Sprite* spr1, Sprite* spr2, float len, float* v_x, float* v_y);
YAGL_DECLARE(Sub, Geo_SprtoSpr_Vect) (As Sprite Ptr, As Sprite Ptr, As Single, As Single Ptr, As Single Ptr)

'void    YAGL_API    Geo_PolarToCartesian (float angle, float len, float* x, float* y);
YAGL_DECLARE(Sub, Geo_PolarToCartesian) (As Single, As Single, As Single Ptr, As Single Ptr)
'void    YAGL_API    Geo_CartesianToPolar (float x, float y, float* angle, float* len);
YAGL_DECLARE(Sub, Geo_CartesianToPolar) (As Single, As Single, As Single Ptr, As Single Ptr)

'/' Bitmap font and text '/
'BmpFont*    YAGL_API    BmpFont_Create (const char fnt_file[], const char img_file[]);
YAGL_DECLARE(Function, BmpFont_Create) (As Const ZString, As Const ZString) As BmpFont Ptr
'int   YAGL_API    BmpFont_IsBmpFont (BmpFont* bfnt);
YAGL_DECLARE(Function, BmpFont_IsBmpFont) (As BmpFont Ptr) As Integer
'int   YAGL_API    BmpFont_Destroy (BmpFont* bfnt);
YAGL_DECLARE(Function, BmpFont_Destroy) (As BmpFont Ptr) As Integer
'int         YAGL_API    BmpFont_CharExists (BmpFont* bfnt, const char chr);
YAGL_DECLARE(Function, BmpFont_CharExists) (As BmpFont Ptr, As Const Byte) As Integer
'void        YAGL_API    BmpFont_Print (BmpFont* bfnt, const char text[], int x, int y, int size, eALIGN align, float angle);
YAGL_DECLARE(Sub, BmpFont_Print) (As BmpFont Ptr, As Const ZString, As Integer, As Integer, As Integer, As eALIGN, As Single)
'void        YAGL_API    BmpFont_PrintLines (BmpFont* bfnt, const char text[], int x, int y, int size, eALIGN align, float angle);
YAGL_DECLARE(Sub, BmpFont_PrintLines) (As BmpFont Ptr, As Const ZString, As Integer, As Integer, As Integer, As eALIGN, As Single)
'int         YAGL_API    BmpFont_Measure (BmpFont* bfnt, const char text[], int size);
YAGL_DECLARE(Function, BmpFont_Measure) (As BmpFont Ptr, As Const ZString, As Integer) As Integer

'/' Bitmap text '/
'BmpText*    YAGL_API    BmpText_Create (BmpFont* bfnt, const char text[], unsigned int size, int multiligne);
YAGL_DECLARE(Function, BmpText_Create) (As BmpFont Ptr, As Const ZString, As UInteger, As Integer) As BmpText Ptr
'int   YAGL_API    BmpText_IsBmpText (BmpText* btxt);
YAGL_DECLARE(Function, BmpText_IsBmpText) (As BmpText Ptr) As Integer
'int   YAGL_API    BmpText_Destroy (BmpText* btxt);
YAGL_DECLARE(Function, BmpText_Destroy) (As BmpText Ptr) As Integer
'void        YAGL_API    BmpText_SetText (BmpText* btxt, const char text[]);
YAGL_DECLARE(Sub, BmpText_SetText) (As BmpText Ptr, As Const ZString)
'int         YAGL_API    BmpText_GetLen (BmpText* btxt);
YAGL_DECLARE(Function, BmpText_GetLen) (As BmpText Ptr) As Integer
'void        YAGL_API    BmpText_Draw (BmpText* btxt);
YAGL_DECLARE(Sub, BmpText_Draw) (As BmpText Ptr)

'/' Bitmap text Accessors '/
'char*       YAGL_API    BmpText_GetText (BmpText* btxt);
YAGL_DECLARE(Function, BmpText_GetText) (As BmpText Ptr) As ZString Ptr

'void        YAGL_API    BmpText_SetFont (BmpText* btxt, BmpFont* bfnt);
YAGL_DECLARE(Sub, BmpText_SetFont) (As BmpText Ptr, As BmpFont Ptr)
'BmpFont*    YAGL_API    BmpText_GetFont (BmpText* btxt);
YAGL_DECLARE(Function, BmpText_GetFont) (As BmpText Ptr) As BmpFont Ptr

'void        YAGL_API    BmpText_SetVisible (BmpText* btxt, int visible);
YAGL_DECLARE(Sub, BmpText_SetVisible) (As BmpText Ptr, As Integer)
'int   YAGL_API    BmpText_GetVisible (BmpText* btxt);
YAGL_DECLARE(Function, BmpText_GetVisible) (As BmpText Ptr) As Integer

'void        YAGL_API    BmpText_SetMultiligne (BmpText* btxt, int multiligne);
YAGL_DECLARE(Sub, BmpText_SetMultiligne) (As BmpText Ptr, As Integer)
'int   YAGL_API    BmpText_GetMultiligne (BmpText* btxt);
YAGL_DECLARE(Function, BmpText_GetMultiligne) (As BmpText Ptr) As Integer

'void        YAGL_API    BmpText_SetPos (BmpText* btxt, int x, int y);
YAGL_DECLARE(Sub, BmpText_SetPos) (As BmpText Ptr, As Integer, As Integer)
'void        YAGL_API    BmpText_GetPos (BmpText* btxt, int* x, int* y);
YAGL_DECLARE(Sub, BmpText_GetPos) (As BmpText Ptr, As Integer Ptr, As Integer Ptr)

'void        YAGL_API    BmpText_SetSize (BmpText* btxt, int size);
YAGL_DECLARE(Sub, BmpText_SetSize) (As BmpText Ptr, As Integer)
'int         YAGL_API    BmpText_GetSize (BmpText* btxt);
YAGL_DECLARE(Function, BmpText_GetSize) (As BmpText Ptr) As Integer

'void        YAGL_API    BmpText_SetAlign (BmpText* btxt, eALIGN align);
YAGL_DECLARE(Sub, BmpText_SetAlign) (As BmpText Ptr, As eALIGN)
'int         YAGL_API    BmpText_GetAlign (BmpText* btxt);
YAGL_DECLARE(Function, BmpText_GetAlign) (As BmpText Ptr) As Integer

'void        YAGL_API    BmpText_SetAngle (BmpText* btxt, float angle);
YAGL_DECLARE(Sub, BmpText_SetAngle) (As BmpText Ptr, As Single)
'float       YAGL_API    BmpText_GetAngle (BmpText* btxt);
YAGL_DECLARE(Function, BmpText_GetAngle) (As BmpText Ptr) As Single

'void        YAGL_API    BmpText_SetBlendMode (BmpText* btxt, eBLEND_MODE blend_mode);
YAGL_DECLARE(Sub, BmpText_SetBlendMode) (As BmpText Ptr, As eBLEND_MODE)
'int         YAGL_API    BmpText_GetBlendMode (BmpText* btxt);
YAGL_DECLARE(Function, BmpText_GetBlendMode) (As BmpText Ptr) As Integer

'void        YAGL_API    BmpText_SetColor (BmpText* btxt, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
YAGL_DECLARE(Sub, BmpText_SetColor) (As BmpText Ptr, As UByte, As UByte, As UByte, As UByte)
'void        YAGL_API    BmpText_GetColor (BmpText* btxt, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a);
YAGL_DECLARE(Sub, BmpText_GetColor) (As BmpText Ptr, As UByte Ptr, As UByte Ptr, As UByte Ptr, As UByte Ptr)
'void        YAGL_API    BmpText_SetColorEx (BmpText* btxt, YAGL_Color color);
YAGL_DECLARE(Sub, BmpText_SetColorEx) (As BmpText Ptr, As YAGL_COLOR)
'YAGL_Color  YAGL_API    BmpText_GetColorEx (BmpText* btxt);
YAGL_DECLARE(Function, BmpText_GetColorEx) () As YAGL_COLOR

'/' MultiSet '/
'MultiSet*   YAGL_API    MultiSet_Create (eSET_TYPE type);
YAGL_DECLARE(Function, MultiSet_Create) (As eSET_TYPE) As MultiSet Ptr
'int         YAGL_API    MultiSet_IsMultiSet (MultiSet* ms);
YAGL_DECLARE(Function, MultiSet_IsMultiSet) (As MultiSet Ptr) As Integer
'eSET_TYPE   YAGL_API    MultiSet_GetDataType (MultiSet* ms);
YAGL_DECLARE(Function, MultiSet_GetDataType) (As MultiSet Ptr) As eSET_TYPE
'int         YAGL_API    MultiSet_Destroy (MultiSet* ms, int destroy);
YAGL_DECLARE(Function, MultiSet_Destroy) (As MultiSet Ptr, As Integer) As Integer

'void        YAGL_API    MultiSet_Add (MultiSet* ms, void* data, int rank);
YAGL_DECLARE(Sub, MultiSet_Add) (As MultiSet Ptr, As Any Ptr, As Integer)
'int         YAGL_API    MultiSet_Exists (MultiSet* ms, void* data);
YAGL_DECLARE(Function, MultiSet_Exists) (As MultiSet Ptr, As Any Ptr) As Integer
'void        YAGL_API    MultiSet_Del (MultiSet* ms, void* data, int destroy);
YAGL_DECLARE(Sub, MultiSet_Del) (As MultiSet Ptr, As Any Ptr, As Integer)
'void        YAGL_API    MultiSet_DelAll (MultiSet* ms, int destroy);
YAGL_DECLARE(Sub, MultiSet_DelAll) (As MultiSet Ptr, As Integer)

'int         YAGL_API    MultiSet_Count (MultiSet* ms);
YAGL_DECLARE(Function, MultiSet_Count) (As MultiSet Ptr) As Integer
'int         YAGL_API    MultiSet_GetAll (MultiSet* ms, void* data[], int size);
YAGL_DECLARE(Function, MultiSet_GetAll) (As MultiSet Ptr, As Any Ptr, As Integer) As Integer
'int         YAGL_API    MultiSet_Iterate (MultiSet* ms, YAGLMultiSetIterateProc enum_proc, void* user_data);
YAGL_DECLARE(Function, MultiSet_Iterate) (As MultiSet Ptr, As YAGLMultiSetIterateProc, As Any Ptr) As Integer

'/' Multi '/
'void        YAGL_API    MultiSet_Draw (MultiSet* ms); // quad, spr, pemitter, bmptext
YAGL_DECLARE(Sub, MultiSet_Draw) (As MultiSet Ptr)
'void        YAGL_API    MultiSet_SetColor (MultiSet* ms, unsigned char r, unsigned char g, unsigned char b, unsigned char a); // quad, spr, bmptext
YAGL_DECLARE(Sub, MultiSet_SetColor) (As MultiSet Ptr, As UByte, As UByte, As UByte, As UByte)
'void        YAGL_API    MultiSet_SetColorEx (MultiSet* ms, YAGL_Color color); // quad, spr, bmptext
YAGL_DECLARE(Sub, MultiSet_SetColorEx) (As MultiSet Ptr, As YAGL_COLOR)
'void        YAGL_API    MultiSet_SetBlendMode (MultiSet* ms, eBLEND_MODE blend_mode);  // quad, spr, pemitter, bmptext
YAGL_DECLARE(Sub, MultiSet_SetBlendMode) (As MultiSet Ptr, As eBLEND_MODE)
'void        YAGL_API    MultiSet_SetVisible (MultiSet* ms, int visible); // quad, spr, pemitter, bmptext
YAGL_DECLARE(Sub, MultiSet_SetVisible) (As MultiSet Ptr, As Integer)

'/' Quad specific '/
'/' Sprite specific '/
'void        YAGL_API    MultiSet_SpriteDrawShape (MultiSet* ms); // spr
YAGL_DECLARE(Sub, MultiSet_SpriteDrawShape) (As MultiSet Ptr)
'void        YAGL_API    MultiSet_SpriteSetDynamic (MultiSet* ms, int dynamic); // spr
YAGL_DECLARE(Sub, MultiSet_SpriteSetDynamic) (As MultiSet Ptr, As Integer)
'int         YAGL_API    MultiSet_SpriteCollide (MultiSet* ms, Sprite* spr, int force_check, int must_touch_all); // spr
YAGL_DECLARE(Function, MultiSet_SpriteCollide) (As MultiSet Ptr, As Sprite Ptr, As Integer, As Integer) As Integer
'void        YAGL_API    MultiSet_SpriteSetFlip (MultiSet* ms, int x, int y);
YAGL_DECLARE(Sub, MultiSet_SpriteSetFlip) (As MultiSet Ptr, As Integer, As Integer)
'void        YAGL_API    MultiSet_SpriteSetVel (MultiSet* ms, float x, float y);
YAGL_DECLARE(Sub, MultiSet_SpriteSetVel) (As MultiSet Ptr, As Single, As Single)
'void        YAGL_API    MultiSet_SpriteSetVelLen (MultiSet* ms, float len);
YAGL_DECLARE(Sub, MultiSet_SpriteSetVelLen) (As MultiSet Ptr, As Single)
'void        YAGL_API    MultiSet_SpriteSetVelAngle (MultiSet* ms, float angle);
YAGL_DECLARE(Sub, MultiSet_SpriteSetVelAngle) (As MultiSet Ptr, As Single)
'void        YAGL_API    MultiSet_SpriteSetVelEx (MultiSet* ms, float len, float angle);
YAGL_DECLARE(Sub, MultiSet_SpriteSetVelEx) (As MultiSet Ptr, As Single, As Single)
'void        YAGL_API    MultiSet_SpriteSetVelMax (MultiSet* ms, float vel_max);
YAGL_DECLARE(Sub, MultiSet_SpriteSetVelMax) (As MultiSet Ptr, As Single)
'void        YAGL_API    MultiSet_SpriteSetAccel (MultiSet* ms, float x, float y);
YAGL_DECLARE(Sub, MultiSet_SpriteSetAccel) (As MultiSet Ptr, As Single, As Single)
'void        YAGL_API    MultiSet_SpriteSetAccelLen (MultiSet* ms, float len);
YAGL_DECLARE(Sub, MultiSet_SpriteSetAccelLen) (As MultiSet Ptr, As Single)
'void        YAGL_API    MultiSet_SpriteSetAccelAngle (MultiSet* ms, float angle);
YAGL_DECLARE(Sub, MultiSet_SpriteSetAccelAngle) (As MultiSet Ptr, As Single)
'void        YAGL_API    MultiSet_SpriteSetAccelEx (MultiSet* ms, float len, float angle);
YAGL_DECLARE(Sub, MultiSet_SpriteSetAccelEx) (As MultiSet Ptr, As Single, As Single)
'void        YAGL_API    MultiSet_SpriteSetInnertia (MultiSet* ms, float innertia);
YAGL_DECLARE(Sub, MultiSet_SpriteSetInnertia) (As MultiSet Ptr, As Single)
'void        YAGL_API    MultiSet_SpriteSetAVel (MultiSet* ms, float avel);
YAGL_DECLARE(Sub, MultiSet_SpriteSetAVel) (As MultiSet Ptr, As Single)
'void        YAGL_API    MultiSet_SpriteSetAVelMax (MultiSet* ms, float avel_max);
YAGL_DECLARE(Sub, MultiSet_SpriteSetAVelMax) (As MultiSet Ptr, As Single)
'void        YAGL_API    MultiSet_SpriteSetAAccel (MultiSet* ms, float aaccel);
YAGL_DECLARE(Sub, MultiSet_SpriteSetAAccel) (As MultiSet Ptr, As Single)
'void        YAGL_API    MultiSet_SpriteSetAInnertia (MultiSet* ms, float ainnertia);
YAGL_DECLARE(Sub, MultiSet_SpriteSetAInnertia) (As MultiSet Ptr, As Single)

'/' PEmitter specific '/
'void        YAGL_API    MultiSet_PEmitterSetActive (MultiSet* ms, int active); // pemitter
YAGL_DECLARE(Sub, MultiSet_PEmitterSetActive) (As MultiSet Ptr, As Integer)
'void        YAGL_API    MultiSet_PEmitterEmitte (MultiSet* ms, unsigned int nbr); // pemitter
YAGL_DECLARE(Sub, MultiSet_PEmitterEmitte) (As MultiSet Ptr, As UInteger)
'void        YAGL_API    MultiSet_PEmitterEmitteAt (MultiSet* ms, float x, float y, unsigned int nbr); // pemitter
YAGL_DECLARE(Sub, MultiSet_PEmitterEmitteAt) (As MultiSet Ptr, As Single, As Single, As UInteger)

'/' BmpText specific '/
'void        YAGL_API    MultiSet_BmpTextSetText (MultiSet* ms, const char text[]);
YAGL_DECLARE(Sub, MultiSet_BmpTextSetText) (As MultiSet Ptr, As ZString)

'''
#endif ' __YAGL_BI__
