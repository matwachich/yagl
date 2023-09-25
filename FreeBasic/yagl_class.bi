
#ifndef __YAGL_CLASS_BI__
#define __YAGL_CLASS_BI__

#inclib "yagl_class"

'============================================================================='
' Texture Type '
'============================================================================='
Type cTexture
	Private:
	pTexture As Texture Ptr = 0

	Public:
	' Default: creates empty texture
	Declare Constructor ()
	' Create cTexture instance from existing Texture ptr
	Declare Constructor (pTex As Texture Ptr)
	' Create texture from file
	Declare Constructor (file_path As Const ZString, channels As eTEXTURE_CHANNELS = 0)
	' Create texture from memory buffer
	Declare Constructor (buffer As Const UByte Ptr, buffer_size As Const Integer, channels As eTEXTURE_CHANNELS = 0)

	' Destructor
	Declare Destructor ()
	' You can call it to free all object's stuff. Object become unusable after that
	Declare Sub Free ()

	Declare Operator Cast() As Texture Ptr

	'''
	' Load a texture from file
	Declare Function Load Overload (file_path As Const ZString, channels As eTEXTURE_CHANNELS = 0) As Integer
	' Load a texture from memory buffer
	Declare Function Load Overload (buffer As Const UByte Ptr, buffer_size As Const Integer, channels As eTEXTURE_CHANNELS = 0) As Integer

	'''
	' Set OpenGL texture parameters (see glTexParameteri)
	Declare Sub SetParameter (flag As Integer, value As Integer)
	' Restor OpenGL texture parameters to YAGL's defaults
	Declare Sub SetDefaultParameter ()

	'''
	' Return the size of the texture (width, height)
	Declare Sub GetSize (w As Integer Ptr, h As Integer Ptr)
	' Set the texture as empty (free OpenGL texture, must use Load methode to use it again)
	Declare Sub SetEmpty ()
End Type

'============================================================================='
' Texture Map Type '
'============================================================================='
Type cTextureMap
	Private:
	pTextureMap As TextureMap Ptr = 0
	created_from_file As Integer = 0

	Public:
	Declare Constructor ()
	Declare Constructor (filepath As Const ZString, channels As eTEXTURE_CHANNELS = 0) ' Texture WILL BE destroyed at the end
	Declare Constructor (pTexMap As TextureMap Ptr) ' Texture WILL NOT be destroyed at the end
	Declare Constructor (pTex As Texture Ptr) ' Texture WILL NOT be destroyed at the end

	Declare Destructor ()
	Declare Sub Free ()

	Declare Operator Cast () As TextureMap Ptr

	'''
	Declare Property Tex () As Texture Ptr
	Declare Property Tex (As Texture Ptr)

	'''
	Declare Sub SetParameter (flag As Integer, value As Integer)
	Declare Sub SetDefaultParameter ()

	Declare Sub GetSize (w As Integer Ptr, h As Integer Ptr)

	'''
	Declare Sub AddRect (x As Integer, y As Integer, w As Integer, h As Integer)
	Declare Sub GetRect (rect_id As UInteger, x As Integer Ptr, y As Integer Ptr, w As Integer Ptr, h As Integer Ptr)
	Declare Sub Empty ()

	Declare Property Count () As Integer
End Type

'============================================================================='
' Quad Type '
'============================================================================='
Type cQuad
	Private:
	pQuad As Quad Ptr = 0

	Public:
	Declare Constructor ()
	Declare Constructor (pQd As Quad Ptr)
	Declare Constructor (tex As Texture Ptr, tex_x As Integer = 0, tex_y As Integer = 0, tex_w As Integer = 0, tex_h As Integer = 0)

	Declare Destructor ()
	Declare Sub Free ()

	Declare Operator Cast () As Quad Ptr

	'''
	' Texture
	' Set texture
	Declare Sub SetTexture (tex As Texture Ptr)
	Declare Function GetTexture () As Texture Ptr

	' Set texture rectangle
	Declare Sub SetTextureRect (tex_x As Integer = 0, tex_y As Integer = 0, tex_w As Integer = 0, tex_h As Integer = 0)
	Declare Sub GetTextureRect (tex_x As Integer Ptr, tex_y As Integer Ptr, tex_w As Integer Ptr, tex_h As Integer Ptr)

	' Set texture, and texture rectangle
	Declare Sub SetTextureEx (tex As Texture Ptr, tex_x As Integer = 0, tex_y As Integer = 0, tex_w As Integer = 0, tex_h As Integer = 0)
	Declare Function GetTextureEx (tex_x As Integer Ptr, tex_y As Integer Ptr, tex_w As Integer Ptr, tex_h As Integer Ptr) As Texture Ptr

	' Set texture and texture rectangle from a TextureMap element
	Declare Sub SetTextureMap (tex_map As TextureMap Ptr, rect_id As UInteger)

	'''
	' Center, Move & Scale
	Declare Sub SetCenterEx (center_enum As eCENTER)
	Declare Sub Move (x As Single, y As Single)
	Declare Sub Rotate (a As Single)
	Declare Sub Scale (x_ratio As Single, y_ratio As Single)
	Declare Sub SetFlip (x As Integer, y As Integer)
	Declare Sub GetFlip (x As Integer Ptr, y As Integer Ptr)

	'''
	' Point
	Declare Sub ToWorld (qd_x As Single, qd_y As Single, world_x As Single Ptr, world_y As Single Ptr)
	Declare Sub ToWorldEx (qd_x_ratio As Single, qd_y_ratio As Single, world_x As Single Ptr, world_y As Single Ptr)

	'''
	' Draw
	Declare Sub Draw ()

	'''
	' Accessors
	Declare Property Visible () As Integer
	Declare Property Visible (visible As Integer)

	Declare Sub SetPos (x As Single, y As Single)
	Declare Sub GetPos (x As Single Ptr, y As Single Ptr)

	Declare Sub SetSize (w As Single, h As Single)
	Declare Sub GetSize (w As Single Ptr, h As Single Ptr)

	Declare Sub SetCenter (x As Single, y As Single)
	Declare Sub GetCenter (x As Single Ptr, y As Single Ptr)

	Declare Property Angle () As Single
	Declare Property Angle (angle As Single)

	Declare Property BlendMode () As eBLEND_MODE
	Declare Property BlendMode (blend_mode As eBLEND_MODE)

	Declare Property Color () As YAGL_COLOR
	Declare Property Color (clr As YAGL_COLOR)
	Declare Sub SetColor (r As UByte, g As UByte, b As UByte, a As UByte)
	Declare Sub GetColor (r As UByte Ptr, g As UByte Ptr, b As UByte Ptr, a As UByte Ptr)

	Declare Property UserData () As Any Ptr
	Declare Property UserData (As Any Ptr)
End Type

'============================================================================='
' Sprite Type '
'============================================================================='
Type cSprite
	Private:
	pSprite As Sprite Ptr = 0

	Public:
	Declare Constructor ()
	Declare Constructor (pSpr As Sprite Ptr)
	' Create a Sprite, assigne it a texture. And optionally select a texture rectangle to display
	Declare Constructor (tex As Texture Ptr, tex_x As Integer = 0, tex_y As Integer = 0, tex_w As Integer = 0, tex_h As Integer = 0)

	Declare Destructor ()
	Declare Sub Free ()

	Declare Operator Cast() As Sprite Ptr

	'''
	' Texture
	' Set texture
	Declare Sub SetTexture (tex As Texture Ptr)
	Declare Function GetTexture () As Texture Ptr

	' Set texture rectangle
	Declare Sub SetTextureRect (tex_x As Integer = 0, tex_y As Integer = 0, tex_w As Integer = 0, tex_h As Integer = 0)
	Declare Sub GetTextureRect (tex_x As Integer Ptr, tex_y As Integer Ptr, tex_w As Integer Ptr, tex_h As Integer Ptr)

	' Set texture, and texture rectangle
	Declare Sub SetTextureEx (tex As Texture Ptr, tex_x As Integer = 0, tex_y As Integer = 0, tex_w As Integer = 0, tex_h As Integer = 0)
	Declare Function GetTextureEx (tex_x As Integer Ptr, tex_y As Integer Ptr, tex_w As Integer Ptr, tex_h As Integer Ptr) As Texture Ptr

	' Set texture and texture rectangle from a TextureMap element
	Declare Sub SetTextureMap (tex_map As TextureMap Ptr, rect_id As UInteger)

	'''
	' Shape & Collision
	Declare Sub SetShape (shp As eSHAPE, x As Single, y As Single, w As Single, h As Single)
	Declare Function GetShape (x As Single Ptr, y As Single Ptr, w As Single Ptr, h As Single Ptr) As eSHAPE
	' Sprite with mask = 0 WILL collide with all other sprites. Only sprites with BitAND equal masks will collide, otherwise.
	Declare Property CollisionMask () As Integer
	Declare Property CollisionMask (mask As Integer)
	' All sprites in the same group will NOT collide. 0 is a "no group", a sprite with no group will collide with ALL others
	Declare Property CollisionGroup () As Integer
	Declare Property CollisionGroup (group As Integer)

	'''
	' Animation
	Declare Property Anim () As Animation Ptr
	Declare Property Anim (anim As Animation Ptr)
	Declare Property AnimCurrFrame () As UInteger
	Declare Property AnimCurrFrame (frame_id As UInteger)
	Declare Property AnimStartFrame () As UInteger
	Declare Property AnimStartFrame (frame_id As UInteger)
	Declare Property AnimTimerMult () As Single
	Declare Property AnimTimerMult (As Single)
	Declare Sub AnimDisplayFrame (frame_id As Integer = -1) ' if -1, display CurrFrame
	Declare Sub AnimGo (loop As Integer)
	Declare Sub AnimStop (stop_frame_id As UInteger)
	Declare Property AnimStatus () As Integer ' Read only
	Declare Property AnimLoop () As Integer ' Read only

	'''
	' Center, Move & Scale
	Declare Sub SetCenterEx (center_enum As eCENTER)
	Declare Sub Move (x As Single, y As Single)
	Declare Sub Rotate (a As Single)
	Declare Sub Scale (x_ratio As Single, y_ratio As Single)
	Declare Sub SetFlip (x As Integer, y As Integer)
	Declare Sub GetFlip (x As Integer Ptr, y As Integer Ptr)

	'''
	' Dynamics
	Declare Sub SetVel (x As Single, y As Single)
	Declare Sub SetVelEx (lenght As Single, angle As Single)
	Declare Sub GetVel (x As Single Ptr, y As Single Ptr)
	Declare Sub GetVelEx (lenght As Single Ptr, angle As Single Ptr)
	Declare Property VelMax () As Single
	Declare Property VelMax (vel_max As Single)
	Declare Property VelLen () As Single
	Declare Property VelLen (vel_len As Single)
	Declare Property VelAngle () As Single
	Declare Property VelAngle (vel_angle As Single)

	Declare Sub SetAccel (x As Single, y As Single)
	Declare Sub SetAccelEx (lenght As Single, angle As Single)
	Declare Sub GetAccel (x As Single Ptr, y As Single Ptr)
	Declare Sub GetAccelEx (lenght As Single Ptr, angle As Single Ptr)
	Declare Property AccelLen () As Single
	Declare Property AccelLen (accel_len As Single)
	Declare Property AccelAngle () As Single
	Declare Property AccelAngle (accel_angle As Single)

	Declare Property Innertia () As Single
	Declare Property Innertia (innertia As Single)

	Declare Property AVel () As Single
	Declare Property AVel (a_vel As Single)
	Declare Property AVelMax () As Single
	Declare Property AVelMax (a_vel_max As Single)

	Declare Property AAccel () As Single
	Declare Property AAccel (a_accel As Single)

	Declare Property AInnertia () As Single
	Declare Property AInnertia (a_innertia As Single)

	Declare Property ParentV () As Sprite Ptr
	Declare Property ParentV (As Sprite Ptr)

	Declare Property ParentA () As Sprite Ptr
	Declare Property ParentA (As Sprite Ptr)

	'''
	' Point
	Declare Sub ToWorld (spr_x As Single, spr_y As Single, world_x As Single Ptr, world_y As Single Ptr)
	Declare Sub ToWorldEx (spr_x_ratio As Single, spr_y_ratio As Single, world_x As Single Ptr, world_y As Single Ptr)
	Declare Sub FromWorld (world_x As Single, world_y As Single, spr_x As Single Ptr, spr_y As Single Ptr, follow_spr_angle As Integer = 0)

	'''
	' Draw
	Declare Sub Draw ()
	Declare Sub DrawShape ()

	'''
	' Accessors
	Declare Property Visible () As Integer
	Declare Property Visible (visible As Integer)

	Declare Property Dynamic () As Integer
	Declare Property Dynamic (dynamic As Integer)

	Declare Sub SetPos (x As Single, y As Single)
	Declare Sub GetPos (x As Single Ptr, y As Single Ptr)

	Declare Sub SetSize (w As Single, h As Single)
	Declare Sub GetSize (w As Single Ptr, h As Single Ptr)

	Declare Sub SetCenter (x As Single, y As Single)
	Declare Sub GetCenter (x As Single Ptr, y As Single Ptr)

	Declare Property Angle () As Single
	Declare Property Angle (angle As Single)

	Declare Property BlendMode () As eBLEND_MODE
	Declare Property BlendMode (blend_mode As eBLEND_MODE)

	Declare Property Color () As YAGL_COLOR
	Declare Property Color (clr As YAGL_COLOR)
	Declare Sub SetColor (r As UByte, g As UByte, b As UByte, a As UByte)
	Declare Sub GetColor (r As UByte Ptr, g As UByte Ptr, b As UByte Ptr, a As UByte Ptr)

	Declare Property UserData () As Any Ptr
	Declare Property UserData (As Any Ptr)

End Type

'============================================================================='
' SpriteSet Type '
'============================================================================='
Type cSpriteSet
	Private:
	pSpriteSet As SpriteSet Ptr = 0

	Public:
	DestroySprites As Integer = 1

	Declare Constructor ()
	Declare Constructor (pSprSet As SpriteSet Ptr)

	Declare Destructor ()
	Declare Sub Free ()

	Declare Operator Cast() As SpriteSet Ptr

	'''
	' Methods
	Declare Sub Add (spr As Sprite Ptr)
	Declare Function Exists (spr As Sprite Ptr) As Integer

	Declare Sub Del (spr As Sprite Ptr)
	Declare Sub DelAll ()

	Declare Function GetAll (spr_array As Sprite Ptr Ptr, array_size As Integer) As Integer
	Declare Function Iterate (iterate_proc As YAGLSpriteSetIterateProc, user_data As Any Ptr) As Integer

	Declare Sub SetColor (r As UByte, g As UByte, b As UByte, a As UByte)
	Declare Sub SetColorEx (clr As YAGL_COLOR)
	Declare Sub SetBlendMode (blend_mode As eBLEND_MODE)
	Declare Sub SetVisible (visible As Integer)
	Declare Sub SetDynamic (dynamic As Integer)

	Declare Function Collide (spr As Sprite Ptr, force_check As Integer, must_touch_all As Integer) As Integer

	Declare Sub Draw ()
	Declare Sub DrawShapes ()

	Declare Property Count () As Integer
End Type

'============================================================================='
' Animation Type '
'============================================================================='
Type cAnimation
	Private:
	pAnimation As Animation Ptr = 0

	Public:
	Declare Constructor (frame_count As UInteger)
	Declare Constructor (pAnim As Animation Ptr)

	Declare Destructor ()
	Declare Sub Free ()

	Declare Operator Cast () As Animation Ptr

	Declare Sub Resize (frame_count As UInteger)

	'''
	' Frames
	Declare Function AddFrame (frame_duration As Single, tex As Texture Ptr = 0, tex_x As Integer = 0, tex_y As Integer = 0, tex_w As Integer = 0, tex_h As Integer = 0, clr As YAGL_COLOR = &hFFFFFFFF, blend_mode As eBLEND_MODE = BLEND_TRANS, change_size As Integer = 0, size_w As Single = 0, size_h As Single = 0) As Integer
	Declare Sub FrameSetBlank (frame_id As UInteger)

	Declare Property FrameMax () As Integer
	Declare Property FrameCount () As Integer

	Declare Sub Empty ()
	
	'''
	Declare Property TimerMult () As Single
	Declare Property TimerMult (As Single)

	'''
	' Frames modification
	Declare Sub FrameSetDuration (frame_id As UInteger, frame_duration As Single)
	Declare Sub FrameSetTexture (frame_id As UInteger, tex As Texture Ptr, tex_x As Integer, tex_y As Integer, tex_w As Integer, tex_h As Integer)
	Declare Sub FrameSetColor (frame_id As UInteger, r As UByte, g As UByte, b As UByte, a As UByte)
	Declare Sub FrameSetColorEx (frame_id As UInteger, clr As YAGL_COLOR)
	Declare Sub FrameSetBlendMode (frame_id As UInteger, blend_mode As eBLEND_MODE)
	Declare Sub FrameSetSize (frame_id As UInteger, change_size As Integer, size_w As Single, size_h As Single)

	Declare Function FrameGetDuration (frame_id As UInteger) As Single
	Declare Function FrameGetTexture (frame_id As UInteger, tex_x As Integer Ptr, tex_y As Integer Ptr, tex_w As Integer Ptr, tex_h As Integer Ptr) As Texture Ptr
	Declare Sub FrameGetColor (frame_id As UInteger, r As UByte Ptr, g As UByte Ptr, b As UByte Ptr, a As UByte Ptr)
	Declare Function FrameGetColorEx (frame_id As UInteger) As YAGL_COLOR
	Declare Function FrameGetBlendMode (frame_id As UInteger) As eBLEND_MODE
	Declare Function FrameGetSize (frame_id As UInteger, size_w As Single Ptr, size_h As Single Ptr) As Integer
End Type

'============================================================================='
' Particles Emitter Type '
'============================================================================='
Type cPEmitter
	Private:
	pPEmitter As PEmitter Ptr = 0

	Public:
	Declare Constructor ()
	Declare Constructor (pPEmit As PEmitter Ptr)
	Declare Constructor (tex As Texture Ptr, tex_x As Integer = 0, tex_y As Integer = 0, tex_w As Integer = 0, tex_h As Integer = 0)

	Declare Constructor (ByRef As cPEmitter)

	Declare Destructor ()
	Declare Sub Free ()

	Declare Operator Cast () As PEmitter Ptr
	Declare Operator Let (As PEmitter Ptr)
	Declare Operator Let (ByRef As cPEmitter)

	Declare Sub ReadCfg (ini_file As Const ZString, ini_section As Const ZString)

	'''
	Declare Property Tex (tex As Texture Ptr)
	Declare Property Tex () As Texture Ptr

	Declare Sub SetTextureRect (tex_x As Integer, tex_y As Integer, tex_w As Integer, tex_h As Integer)
	Declare Sub GetTextureRect (tex_x As Integer Ptr, tex_y As Integer Ptr, tex_w As Integer Ptr, tex_h As Integer Ptr)

	Declare Sub SetTextureMap (tex_map As TextureMap Ptr, rect_id As UInteger)

	Declare Sub SetCallbacks (spawn_proc As YAGLParticleSpawnProc, dead_proc As YAGLParticleDeadProc)

	'''
	Declare Property Active (active As Integer)
	Declare Property Active () As Integer

	Declare Sub Emitte (num_particles As UInteger)
	Declare Sub EmitteAt (x As Single, y As Single, num_particles As UInteger)

	Declare Sub Draw ()

	Declare Property Count () As UInteger

	'''
	' Accessors
	'	Position
	Declare Property Visible (As Integer)
	Declare Property Visible () As Integer
	
	Declare Sub SetPos (x As Single,y  As Single)
	Declare Sub GetPos (x As Single Ptr, y As Single Ptr)

	Declare Sub SetPosVar (x As Single, y As Single)
	Declare Sub GetPosVar (x As Single Ptr, y As Single Ptr)

	'	Velocity
	Declare Property Vel (As Single)
	Declare Property Vel () As Single

	Declare Property VelVar (As Single)
	Declare Property VelVar () As Single

	'	Acceleration
	Declare Property Accel (As Single)
	Declare Property Accel () As Single

	Declare Property AccelVar (As Single)
	Declare Property AccelVar () As Single

	'	Emitte angle
	Declare Property Angle (As Single)
	Declare Property Angle () As Single

	Declare Property AngleVar (As Single)
	Declare Property AngleVar () As Single

	'	Force
	Declare Property Force (As Single)
	Declare Property Force () As Single

	Declare Property ForceVar (As Single)
	Declare Property ForceVar () As Single

	'	Force angle
	Declare Property ForceAngle (As Single)
	Declare Property ForceAngle () As Single

	Declare Property ForceAngleVar (As Single)
	Declare Property ForceAngleVar () As Single

	'	Particle innertia
	Declare Property ParticleInnertia (As Single)
	Declare Property ParticleInnertia () As Single

	'	Particle angle
	Declare Property ParticleAngle (As Single)
	Declare Property ParticleAngle () As Single

	Declare Property ParticleAngleVar (As Single)
	Declare Property ParticleAngleVar () As Single

	'	Particle spin
	Declare Property Spin (As Single)
	Declare Property Spin () As Single

	Declare Property SpinVar (As Single)
	Declare Property SpinVar () As Single

	Declare Property SpinFlyVar (As Single)
	Declare Property SpinFlyVar () As Single

	'	Particle size
	Declare Property Size (As Single)
	Declare Property Size () As Single

	Declare Property SizeVar (As Single)
	Declare Property SizeVar () As Single

	Declare Property SizeFlyVar (As Single)
	Declare Property SizeFlyVar () As Single

	'	Particle life time
	Declare Property Life (As Single)
	Declare Property Life () As Single

	Declare Property LifeVar (As Single)
	Declare Property LifeVar () As Single

	'	Emitte rate
	Declare Property EmitteRate (As UInteger)
	Declare Property EmitteRate () As UInteger

	'	Max particles
	Declare Property MaxParticles (As UInteger)
	Declare Property MaxParticles () As UInteger

	'	Blend mode
	Declare Property BlendMode (As eBLEND_MODE)
	Declare Property BlendMode () As eBLEND_MODE

	'	Color
	Declare Sub SetColor (r As UByte, g As UByte, b As UByte, a As UByte)
	Declare Sub SetColorVar (r As Short, g As Short, b As Short, a As Short)
	Declare Sub SetColorFlyVar (r As Short, g As Short, b As Short, a As Short)

	Declare Sub GetColor (r As UByte Ptr, g As UByte Ptr, b As UByte Ptr, a As UByte Ptr)
	Declare Sub GetColorVar (r As Short Ptr, g As Short Ptr, b As Short Ptr, a As Short Ptr)
	Declare Sub GetColorFlyVar (r As Short Ptr, g As Short Ptr, b As Short Ptr, a As Short Ptr)
End Type

'============================================================================='
' Shaders Type '
'============================================================================='
Type cShader
	Private:
	pShader As Shader Ptr

	Public:
	Declare Constructor ()

	Declare Destructor ()
	Declare Sub Free ()

	'''
	Declare Static Sub Init (fatal_fail As Const Integer)
	Declare Static Function IsInit () As Integer
	Declare Static Sub SetCompileErrFatal (As Const Integer)
	Declare Static Sub SetLinkErrFatal (As Const Integer)
	Declare Static Sub SetInfoLogShow (As Const Integer)
	Declare Static Sub UnUse ()

	'''
	Declare Function AddSource (src As Const ZString, shader_type As eSHADER_TYPE) As Integer
	Declare Function AddSourceFile (file As Const ZString, shader_type As eSHADER_TYPE) As Integer
	Declare Function Link () As Integer
	Declare Sub Use ()

	Declare Property Ready () As Integer
End Type

'============================================================================='
' Bitmap Font Type '
'============================================================================='
Type cBmpFont
	Private:
	pBmpFont As BmpFont Ptr = 0

	Public:
	Declare Constructor (fnt_file As Const ZString, texture_file As Const ZString)
	Declare Constructor (pBFnt As BmpFont Ptr)

	Declare Destructor ()
	Declare Sub Free ()

	Declare Operator Cast () As BmpFont Ptr

	'''
	Declare Function CharExists (char As Byte) As Integer
	Declare Function Measure (text As Const ZString, size As Integer) As Integer

	Declare Sub Print (text As Const ZString, x As Integer, y As Integer, size As Integer, align As eALIGN, angle As Single)
	Declare Sub PrintLines (text As Const ZString, x As Integer, y As Integer, size As Integer, align As eALIGN, angle As Single)
End Type

'============================================================================='
' Bitmap Text Type '
'============================================================================='
Type cBmpText
	Private:
	pBmpText As BmpText Ptr = 0

	Public:
	Declare Constructor ()
	Declare Constructor (pBTxt As BmpText Ptr)
	Declare Constructor (bmp_font As BmpFont Ptr = 0, text As Const ZString = "", size As UInteger = 16, multiline As Integer = 0)

	Declare Destructor ()
	Declare Sub Free ()

	Declare Sub Draw ()

	'''
	Declare Property Font (As BmpFont Ptr)
	Declare Property Font () As BmpFont Ptr

	Declare Property Text (As Const ZString)
	Declare Property Text () As ZString Ptr

	Declare Property Len () As Integer

	Declare Property Visible (As Integer)
	Declare Property Visible () As Integer

	Declare Property Multiline (As Integer)
	Declare Property Multiline () As Integer

	Declare Sub SetPos (x As Integer, y As Integer)
	Declare Sub GetPos (x As Integer Ptr, y As Integer Ptr)

	Declare Property Size (As Integer)
	Declare Property Size () As Integer

	Declare Property Align (As eALIGN)
	Declare Property Align () As eALIGN

	Declare Property Angle (As Single)
	Declare Property Angle () As Single

	Declare Property BlendMode (As eBLEND_MODE)
	Declare Property BlendMode () As eBLEND_MODE

	Declare Property Color (As YAGL_COLOR)
	Declare Property Color () As YAGL_COLOR

	Declare Sub SetColor (r As UByte, g As UByte, b As UByte, a As UByte)
	Declare Sub GetColor (r As UByte Ptr, g As UByte Ptr, b As UByte Ptr, a As UByte Ptr)
End Type

#endif ' __YAGL_CLASS_BI__
