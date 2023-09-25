
#include "yagl.bi"
#include "yagl_class.bi"

'============================================================================='
' Texture Type '
'============================================================================='
Constructor cTexture ()
	This.pTexture = Texture_CreateEmpty()
End Constructor

Constructor cTexture (pTex As Texture Ptr)
	This.pTexture = pTex
End Constructor

Constructor cTexture (path As Const ZString, channels As eTEXTURE_CHANNELS = 0)
	This.pTexture = Texture_Create(path, channels)
End Constructor

Constructor cTexture (pdata As Const UByte Ptr, buffer_size As Const Integer, channels As eTEXTURE_CHANNELS = 0)
	This.pTexture = Texture_CreateFromMem(pdata, buffer_size, channels)
End Constructor

Destructor cTexture ()
	If This.pTexture = 0 Then Return
	Texture_Destroy(This.pTexture)
End Destructor

Sub cTexture.Free ()
	If This.pTexture = 0 Then Return
	Texture_Destroy(This.pTexture)
	This.pTexture = 0
End Sub

Operator cTexture.Cast () As Texture Ptr
	Return This.pTexture
End Operator

'''

Function cTexture.Load Overload (path As Const ZString, channels As eTEXTURE_CHANNELS = 0) As Integer
	Return Texture_Load(This.pTexture, path, channels)
End Function

Function cTexture.Load Overload (pdata As Const UByte Ptr, buffer_size As Const Integer, channels As eTEXTURE_CHANNELS = 0) As Integer
	Return Texture_LoadFromMem(This.pTexture, pdata, buffer_size, channels)
End Function

'''

Sub cTexture.SetParameter (param As Integer, value As Integer)
	Texture_SetParameter(This.pTexture, param, value)
End Sub

Sub cTexture.SetDefaultParameter ()
	Texture_SetDefaultParameter(This.pTexture)
End Sub

'''

Sub cTexture.GetSize (x As Integer Ptr, y As Integer Ptr)
	Texture_GetSize(This.pTexture, x, y)
End Sub

Sub cTexture.SetEmpty ()
	Texture_SetEmpty(This.pTexture)
End Sub


'============================================================================='
' Texture Map Type '
'============================================================================='
Constructor cTextureMap ()
	This.pTextureMap = TextureMap_CreateFromTexture(0)
	This.created_from_file = 0
End Constructor

Constructor cTextureMap (filepath As Const ZString, channels As eTEXTURE_CHANNELS = 0)
	This.pTextureMap = TextureMap_Create(filepath, channels)
	This.created_from_file = 1
End Constructor

Constructor cTextureMap (pTexMap As TextureMap Ptr)
	This.pTextureMap = pTexMap
	This.created_from_file = 0
End Constructor

Constructor cTextureMap (pTex As Texture Ptr)
	This.pTextureMap = TextureMap_CreateFromTexture(pTex)
	This.created_from_file = 0
End Constructor


Destructor cTextureMap ()
	If This.pTextureMap = 0 Then Return
	TextureMap_Destroy(This.pTextureMap, created_from_file)
End Destructor

Sub cTextureMap.Free ()
	If This.pTextureMap = 0 Then Return
	TextureMap_Destroy(This.pTextureMap, created_from_file)
	This.pTextureMap = 0
End Sub

Operator cTextureMap.Cast () As TextureMap Ptr
	Return This.pTextureMap
End Operator

'''
Property cTextureMap.Tex () As Texture Ptr
	Return TextureMap_GetTexture(This.pTextureMap)
End Property

Property cTextureMap.Tex (pTex As Texture Ptr)
	TextureMap_SetTexture(This.pTextureMap, pTex)
End Property

'''
Sub cTextureMap.SetParameter (flag As Integer, value As Integer)
	TextureMap_SetParameter(This.pTextureMap, flag, value)
End Sub

Sub cTextureMap.SetDefaultParameter ()
	TextureMap_SetDefaultParameter(This.pTextureMap)
End Sub

Sub cTextureMap.GetSize (w As Integer Ptr, h As Integer Ptr)
	TextureMap_GetSize(This.pTextureMap, w, h)
End Sub

'''
Sub cTextureMap.AddRect (x As Integer, y As Integer, w As Integer, h As Integer)
	TextureMap_AddRect(This.pTextureMap, x, y, w, h)
End Sub

Sub cTextureMap.GetRect (rect_id As UInteger, x As Integer Ptr, y As Integer Ptr, w As Integer Ptr, h As Integer Ptr)
	TextureMap_GetRect(This.pTextureMap, rect_id, x, y, w, h)
End Sub

Sub cTextureMap.Empty ()
	TextureMap_Empty(This.pTextureMap)
End Sub


Property cTextureMap.Count () As Integer
	Return TextureMap_Count(This.pTextureMap)
End Property


'============================================================================='
' Quad Type '
'============================================================================='
Type _Quad_
	As Integer visible

	As Texture Ptr tex
	As Single tex_rect_1_1, tex_rect_1_2
	As Single tex_rect_2_1, tex_rect_2_2
	As Single tex_rect_3_1, tex_rect_3_2
	As Single tex_rect_4_1, tex_rect_4_2

	As YAGL_COLOR clr

	As Single pos_x, pos_y
	As Single size_x, size_y
	As Single center_x, center_y
	As eCENTER center_enum

	As Single angle
	As eBLEND_MODE blend_mode
	As Integer flip_x, flip_y

	As Any Ptr data_
End Type
#define __QUAD_PTR Cast(_Quad_ Ptr, This.pQuad)

Constructor cQuad ()
	This.pQuad = Quad_Create(0, 0, 0, 0, 0)
End Constructor

Constructor cQuad (pQd As Quad Ptr)
	This.pQuad = pQd
End Constructor

Constructor cQuad (tex As Texture Ptr, tex_x As Integer = 0, tex_y As Integer = 0, tex_w As Integer = 0, tex_h As Integer = 0)
	This.pQuad = Quad_Create(tex, tex_x, tex_y, tex_w, tex_h)
End Constructor

Destructor cQuad ()
	If This.pQuad = 0 Then Return
	Quad_Destroy(This.pQuad)
End Destructor

Sub cQuad.Free ()
	If This.pQuad = 0 Then Return
	Quad_Destroy(This.pQuad)
	This.pQuad = 0
End Sub

Operator cQuad.Cast () As Quad Ptr
	Return This.pQuad
End Operator

'''
' Texture
' Set texture
Sub cQuad.SetTexture (tex As Texture Ptr)
	Quad_SetTexture(This.pQuad, tex)
End Sub

Function cQuad.GetTexture () As Texture Ptr
	Return Quad_GetTexture(This.pQuad)
End Function

' Set texture rectangle
Sub cQuad.SetTextureRect (tex_x As Integer = 0, tex_y As Integer = 0, tex_w As Integer = 0, tex_h As Integer = 0)
	Quad_SetTextureRect(This.pQuad, tex_x, tex_y, tex_w, tex_h)
End Sub

Sub cQuad.GetTextureRect (tex_x As Integer Ptr, tex_y As Integer Ptr, tex_w As Integer Ptr, tex_h As Integer Ptr)
	Quad_GetTextureRect(This.pQuad, tex_x, tex_y, tex_w, tex_h)
End Sub

' Set texture, and texture rectangle
Sub cQuad.SetTextureEx (tex As Texture Ptr, tex_x As Integer = 0, tex_y As Integer = 0, tex_w As Integer = 0, tex_h As Integer = 0)
	Quad_SetTextureEx(This.pQuad, tex, tex_x, tex_y, tex_w, tex_h)
End Sub

Function cQuad.GetTextureEx (tex_x As Integer Ptr, tex_y As Integer Ptr, tex_w As Integer Ptr, tex_h As Integer Ptr) As Texture Ptr
	Return Quad_GetTextureEx(This.pQuad, tex_x, tex_y, tex_w, tex_h)
End Function

' Set texture and texture rectangle from a TextureMap element
Sub cQuad.SetTextureMap (tex_map As TextureMap Ptr, rect_id As UInteger)
	Quad_SetTextureMap(This.pQuad, tex_map, rect_id)
End Sub

'''
' Center, Move & Scale
Sub cQuad.SetCenterEx (center_enum As eCENTER)
	Quad_SetCenterEx(This.pQuad, center_enum)
End Sub

Sub cQuad.Move (x As Single, y As Single)
	Quad_Move(This.pQuad, x, y)
End Sub

Sub cQuad.Rotate (a As Single)
	Quad_Rotate(This.pQuad, a)
End Sub

Sub cQuad.Scale (x_ratio As Single, y_ratio As Single)
	Quad_Scale(This.pQuad, x_ratio, y_ratio)
End Sub

Sub cQuad.SetFlip (x As Integer, y As Integer)
	Quad_SetFlip(This.pQuad, x, y)
End Sub

Sub cQuad.GetFlip (x As Integer Ptr, y As Integer Ptr)
	Quad_GetFlip(This.pQuad, x, y)
End Sub

'''
' Point
Sub cQuad.ToWorld (qd_x As Single, qd_y As Single, world_x As Single Ptr, world_y As Single Ptr)
	Quad_QuadToWorld(This.pQuad, qd_x, qd_y, world_x, world_y)
End Sub

Sub cQuad.ToWorldEx (qd_x_ratio As Single, qd_y_ratio As Single, world_x As Single Ptr, world_y As Single Ptr)
	Quad_QuadToWorldEx(This.pQuad, qd_x_ratio, qd_y_ratio, world_x, world_y)
End Sub

'''
' Draw
Sub cQuad.Draw ()
	Quad_Draw(This.pQuad)
End Sub

'''
' Accessors
Property cQuad.Visible () As Integer
	Return __QUAD_PTR->visible
End Property

Property cQuad.Visible (v As Integer)
	__QUAD_PTR->visible = v
End Property


Sub cQuad.SetPos (x As Single, y As Single)
	__QUAD_PTR->pos_x = x
	__QUAD_PTR->pos_y = y
End Sub

Sub cQuad.GetPos (x As Single Ptr, y As Single Ptr)
	If x <> 0 Then *x = __QUAD_PTR->pos_x
	If y <> 0 Then *y = __QUAD_PTR->pos_y
End Sub


Sub cQuad.SetSize (w As Single, h As Single)
	Quad_SetSize(This.pQuad, w, h)
End Sub

Sub cQuad.GetSize (w As Single Ptr, h As Single Ptr)
	If w <> 0 Then *w = __QUAD_PTR->size_x
	If h <> 0 Then *h = __QUAD_PTR->size_y
End Sub


Sub cQuad.SetCenter (x As Single, y As Single)
	__QUAD_PTR->center_enum = -1
	__QUAD_PTR->center_x = x
	__QUAD_PTR->center_y = y
End Sub

Sub cQuad.GetCenter (x As Single Ptr, y As Single Ptr)
	If x <> 0 Then *x = __QUAD_PTR->center_x
	If y <> 0 Then *y = __QUAD_PTR->center_y
End Sub


Property cQuad.Angle () As Single
	Return Quad_GetAngle(This.pQuad)
End Property

Property cQuad.Angle (a As Single)
	__QUAD_PTR->angle = a
End Property


Property cQuad.BlendMode () As eBLEND_MODE
	Return __QUAD_PTR->blend_mode
End Property

Property cQuad.BlendMode (blend_mode As eBLEND_MODE)
	__QUAD_PTR->blend_mode = blend_mode
End Property


Property cQuad.Color () As YAGL_COLOR
	Return __QUAD_PTR->clr
End Property

Property cQuad.Color (clr As YAGL_COLOR)
	__QUAD_PTR->clr = clr
End Property

Sub cQuad.SetColor (r As UByte, g As UByte, b As UByte, a As UByte)
	Quad_SetColor(This.pQuad, r, g, b, a)
End Sub

Sub cQuad.GetColor (r As UByte Ptr, g As UByte Ptr, b As UByte Ptr, a As UByte Ptr)
	Quad_GetColor(This.pQuad, r, g, b, a)
End Sub


Property cQuad.UserData () As Any Ptr
	Return __QUAD_PTR->data_
End Property

Property cQuad.UserData (d As Any Ptr)
	__QUAD_PTR->data_ = d
End Property


'============================================================================='
' Sprite Type '
'============================================================================='
Type _Sprite_
	As Integer visible, dynamic

	tex As Texture Ptr
	As Single tex_rect_1_1, tex_rect_1_2
	As Single tex_rect_2_1, tex_rect_2_2
	As Single tex_rect_3_1, tex_rect_3_2
	As Single tex_rect_4_1, tex_rect_4_2

	clr As YAGL_COLOR

	As Single pos_x, pos_y
	As Single size_x, size_y
	As Single center_x, center_y
	center_enum As eCENTER

	As Single angle
	blend_mode As eBLEND_MODE
	As Integer flip_x, flip_y

	As Single vel_x, vel_y
	As Single accel_x, accel_y
	As Single vel_max, innertia
	As Single a_vel, a_accel, a_vel_max, a_innertia
	As Sprite Ptr tutor_vel, tutor_avel

	shape_type As eSHAPE
	shape_pos_x As Single: shape_pos_y As Single
	shape_size_x As Single: shape_size_y As Single
	collision_mask As Single: collision_group As Single

	anim As Animation Ptr
	anim_start_frame As UInteger: anim_frame As UInteger
	anim_status As Integer: anim_loop As Integer
	anim_timer As Double

	data_ As Integer
End Type
#define __SPR_PTR Cast(_Sprite_ Ptr, This.pSprite)

Constructor cSprite ()
	This.pSprite = Sprite_Create(0, 0, 0, 0, 0)
End Constructor

Constructor cSprite (pSpr As Sprite Ptr)
	This.pSprite = pSpr
End Constructor

Constructor cSprite (tex As Texture Ptr, x As Integer = 0, y As Integer = 0, w As Integer = 0, h As Integer = 0)
	This.pSprite = Sprite_Create(tex, x, y, w, h)
End Constructor

Destructor cSprite ()
	If This.pSprite = 0 Then Return
	Sprite_Destroy(This.pSprite)
End Destructor

Sub cSprite.Free ()
	If This.pSprite = 0 Then Return
	Sprite_Destroy(This.pSprite)
	This.pSprite = 0
End Sub

Operator cSprite.Cast () As Sprite Ptr
	Return This.pSprite
End Operator

'''
' Texture
Sub cSprite.SetTexture (tex As Texture Ptr)
	Sprite_SetTexture(This.pSprite, tex)
End Sub

Function cSprite.GetTexture () As Texture Ptr
	Return Sprite_GetTexture(This.pSprite)
End Function


Sub cSprite.SetTextureRect (tex_x As Integer = 0, tex_y As Integer = 0, tex_w As Integer = 0, tex_h As Integer = 0)
	Sprite_SetTextureRect(This.pSprite, tex_x, tex_y, tex_w, tex_h)
End Sub

Sub cSprite.GetTextureRect (tex_x As Integer Ptr, tex_y As Integer Ptr, tex_w As Integer Ptr, tex_h As Integer Ptr)
	Sprite_GetTextureRect(This.pSprite, tex_x, tex_y, tex_w, tex_h)
End Sub


Sub cSprite.SetTextureEx (tex As Texture Ptr, tex_x As Integer = 0, tex_y As Integer = 0, tex_w As Integer = 0, tex_h As Integer = 0)
	Sprite_SetTextureEx(This.pSprite, tex, tex_x, tex_y, tex_w, tex_h)
End Sub

Function cSprite.GetTextureEx (tex_x As Integer Ptr, tex_y As Integer Ptr, tex_w As Integer Ptr, tex_h As Integer Ptr) As Texture Ptr
	Return Sprite_GetTextureEx(This.pSprite, tex_x, tex_y, tex_h, tex_w)
End Function


Sub cSprite.SetTextureMap (tex_map As TextureMap Ptr, rect_id As UInteger)
	Sprite_SetTextureMap(This.pSprite, tex_map, rect_id)
End Sub

'''
' Shape & Collision
Sub cSprite.SetShape (shape As eSHAPE, x As Single, y As Single, w As Single, h As Single)
	Sprite_SetShape(This.pSprite, shape, x, y, w, h)
End Sub

Function cSprite.GetShape (x As Single Ptr, y As Single Ptr, w As Single Ptr, h As Single Ptr) As eSHAPE
	Dim shape As Integer
	Sprite_GetShape(This.pSprite, @shape, x, y, w, h)
	Return shape
End Function

Property cSprite.CollisionMask () As Integer
	CollisionMask = Sprite_GetCollisionMask(This.pSprite)
End Property

Property cSprite.CollisionMask (mask As Integer)
	Sprite_SetCollisionMask(This.pSprite, mask)
End Property

Property cSprite.CollisionGroup () As Integer
	CollisionGroup = Sprite_GetCollisionGroup(This.pSprite)
End Property

Property cSprite.CollisionGroup (group As Integer)
	Sprite_SetCollisionGroup(This.pSprite, group)
End Property

'''
' Animation
Property cSprite.Anim () As Animation Ptr
	Return __SPR_PTR->anim
End Property

Property cSprite.Anim (a As Animation Ptr)
	Sprite_AnimationSet(This.pSprite, a)
End Property

Property cSprite.AnimCurrFrame () As UInteger
	Return __SPR_PTR->anim_frame
End Property

Property cSprite.AnimCurrFrame (frame As UInteger)
	Sprite_AnimationSetFrame(This.pSprite, frame)
End Property

Property cSprite.AnimStartFrame () As UInteger
	Return __SPR_PTR->anim_start_frame
End Property

Property cSprite.AnimStartFrame (frame As UInteger)
	Sprite_AnimationSetStartFrame(This.pSprite, frame)
End Property

Property cSprite.AnimTimerMult () As Single
	Return Sprite_AnimationGetTimerMult(This.pSprite)
End Property

Property cSprite.AnimTimerMult (timer_mult As Single)
	Sprite_AnimationSetTimerMult(This.pSprite, timer_mult)
End Property

Sub cSprite.AnimDisplayFrame (frame As Integer = -1) ' if -1, display CurrFrame
	Dim ui_frame As UInteger
	If frame = -1 Then
		ui_frame = __SPR_PTR->anim_frame
	Else
		ui_frame = frame
	End If
	Sprite_AnimationDisplayFrame(This.pSprite, ui_frame)
End Sub

Sub cSprite.AnimGo (is_loop As Integer)
	Sprite_AnimationGo(This.pSprite, is_loop)
End Sub

Sub cSprite.AnimStop (stop_frame As UInteger)
	Sprite_AnimationStop(This.pSprite, stop_frame)
End Sub

Property cSprite.AnimStatus () As Integer ' Read only
	Return __SPR_PTR->anim_status
End Property

Property cSprite.AnimLoop () As Integer ' Read only
	Return __SPR_PTR->anim_loop
End Property

'''
' Center, Move & Scale
Sub cSprite.SetCenterEx (flag As eCENTER)
	Sprite_SetCenterEx(This.pSprite, flag)
End Sub

Sub cSprite.Move (x As Single, y As Single)
	Sprite_Move(This.pSprite, x, y)
End Sub

Sub cSprite.Rotate (a As Single)
	Sprite_Rotate(This.pSprite, a)
End Sub

Sub cSprite.Scale (x As Single, y As Single)
	Sprite_Scale(This.pSprite, x, y)
End Sub

Sub cSprite.SetFlip (x As Integer, y As Integer)
	Sprite_SetFlip(This.pSprite, x, y)
End Sub

Sub cSprite.GetFlip (x As Integer Ptr, y As Integer Ptr)
	Sprite_GetFlip(This.pSprite, x, y)
End Sub

'''
' Dynamics
Sub cSprite.SetVel (x As Single, y As Single)
	__SPR_PTR->vel_x = x
	__SPR_PTR->vel_y = y
End Sub

Sub cSprite.SetVelEx (l As Single, a As Single)
	Sprite_SetVelEx(This.pSprite, l, a)
End Sub

Sub cSprite.GetVel (x As Single Ptr, y As Single Ptr)
	If x <> 0 Then *x = __SPR_PTR->vel_x
	If y <> 0 Then *y = __SPR_PTR->vel_y
End Sub

Sub cSprite.GetVelEx (l As Single Ptr, a As Single Ptr)
	Sprite_GetVelEx(This.pSprite, l, a)
End Sub

Property cSprite.VelMax () As Single
	Return __SPR_PTR->vel_max
End Property

Property cSprite.VelMax (vmax As Single)
	__SPR_PTR->vel_max = vmax
End Property

Property cSprite.VelLen () As Single
	VelLen = Sprite_GetVelLen(This.pSprite)
End Property

Property cSprite.VelLen (l As Single)
	Sprite_SetVelLen(This.pSprite, l)
End Property

Property cSprite.VelAngle () As Single
	VelAngle = Sprite_GetVelAngle(This.pSprite)
End Property

Property cSprite.VelAngle (a As Single)
	Sprite_SetVelAngle(This.pSprite, a)
End Property


Sub cSprite.SetAccel (x As Single, y As Single)
	__SPR_PTR->accel_x = x
	__SPR_PTR->accel_y = y
End Sub

Sub cSprite.SetAccelEx (l As Single, a As Single)
	Sprite_SetAccelEx(This.pSprite, l, a)
End Sub

Sub cSprite.GetAccel (x As Single Ptr, y As Single Ptr)
	If x <> 0 Then *x = __SPR_PTR->accel_x
	If y <> 0 Then *y = __SPR_PTR->accel_y
End Sub

Sub cSprite.GetAccelEx (l As Single Ptr, a As Single Ptr)
	Sprite_GetAccelEx(This.pSprite, l, a)
End Sub

Property cSprite.AccelLen () As Single
	AccelLen = Sprite_GetAccelLen(This.pSprite)
End Property

Property cSprite.AccelLen (l As Single)
	Sprite_SetAccelLen(This.pSprite, l)
End Property

Property cSprite.AccelAngle () As Single
	AccelAngle = Sprite_GetAccelAngle(This.pSprite)
End Property

Property cSprite.AccelAngle (a As Single)
	Sprite_SetAccelAngle(This.pSprite, a)
End Property


Property cSprite.Innertia () As Single
	Return __SPR_PTR->innertia
End Property

Property cSprite.Innertia (i As Single)
	__SPR_PTR->innertia = i
End Property

Property cSprite.AVel () As Single
	Return __SPR_PTR->a_vel
End Property

Property cSprite.AVel (av As Single)
	__SPR_PTR->a_vel = av
End Property

Property cSprite.AVelMax () As Single
	Return __SPR_PTR->a_vel_max
End Property

Property cSprite.AVelMax (avmax As Single)
	__SPR_PTR->a_vel_max = avmax
End Property


Property cSprite.AAccel () As Single
	Return __SPR_PTR->a_accel
End Property

Property cSprite.AAccel (aa As Single)
	__SPR_PTR->a_accel = aa
End Property


Property cSprite.AInnertia () As Single
	Return __SPR_PTR->a_innertia
End Property

Property cSprite.AInnertia (ai As Single)
	__SPR_PTR->a_innertia = ai
End Property


Property cSprite.ParentV () As Sprite Ptr
	Return __SPR_PTR->tutor_vel
End Property

Property cSprite.ParentV (p As Sprite Ptr)
	__SPR_PTR->tutor_vel = p
End Property


Property cSprite.ParentA () As Sprite Ptr
	Return __SPR_PTR->tutor_avel
End Property

Property cSprite.ParentA (p As Sprite Ptr)
	__SPR_PTR->tutor_avel = p
End Property


'''
' Point
Sub cSprite.ToWorld (x As Single, y As Single, px As Single Ptr, py As Single Ptr)
	Sprite_SpriteToWorld(This.pSprite, x, y, px, py)
End Sub

Sub cSprite.ToWorldEx (ratiox As Single, ratioy As Single, px As Single Ptr, py As Single Ptr)
	Sprite_SpriteToWorldEx(This.pSprite, ratiox, ratioy, px, py)
End Sub

'''
' Draw
Sub cSprite.Draw ()
	Sprite_Draw(This.pSprite)
End Sub

Sub cSprite.DrawShape ()
	Sprite_DrawShape(This.pSprite)
End Sub

'''
' Accessors
Property cSprite.Visible () As Integer
	Return __SPR_PTR->visible
End Property

Property cSprite.Visible (v As Integer)
	__SPR_PTR->visible = v
End Property


Property cSprite.Dynamic () As Integer
	Return __SPR_PTR->dynamic
End Property

Property cSprite.Dynamic (d As Integer)
	__SPR_PTR->dynamic = d
End Property


Sub cSprite.SetPos (x As Single, y As Single)
	__SPR_PTR->pos_x = x
	__SPR_PTR->pos_y = y
End Sub

Sub cSprite.GetPos (x As Single Ptr, y As Single Ptr)
	If x <> 0 Then *x = __SPR_PTR->pos_x
	If y <> 0 Then *y = __SPR_PTR->pos_y
End Sub


Sub cSprite.SetSize (w As Single, h As Single)
	Sprite_SetSize(This.pSprite, w, h)
End Sub

Sub cSprite.GetSize (w As Single Ptr, h As Single Ptr)
	If w <> 0 Then *w = __SPR_PTR->size_x
	If h <> 0 Then *h = __SPR_PTR->size_y
End Sub


Sub cSprite.SetCenter (x As Single, y As Single)
	__SPR_PTR->center_enum = -1
	__SPR_PTR->center_x = x
	__SPR_PTR->center_y = y
End Sub

Sub cSprite.GetCenter (x As Single Ptr, y As Single Ptr)
	If x <> 0 Then *x = __SPR_PTR->center_x
	If y <> 0 Then *y = __SPR_PTR->center_y
End Sub


Property cSprite.Angle () As Single
	Return Sprite_GetAngle(This.pSprite)
End Property

Property cSprite.Angle (a As Single)
	__SPR_PTR->angle = a
End Property


Property cSprite.BlendMode () As eBLEND_MODE
	Return __SPR_PTR->blend_mode
End Property

Property cSprite.BlendMode (bm As eBLEND_MODE)
	__SPR_PTR->blend_mode = bm
End Property


Property cSprite.Color () As YAGL_COLOR
	Return Sprite_GetColorEx(This.pSprite)
End Property

Property cSprite.Color (c As YAGL_COLOR)
	Sprite_SetColorEx(This.pSprite, c)
End Property

Sub cSprite.SetColor (r As UByte, g As UByte, b As UByte, a As UByte)
	Sprite_SetColor(This.pSprite, r, g, b, a)
End Sub

Sub cSprite.GetColor (r As UByte Ptr, g As UByte Ptr, b As UByte Ptr, a As UByte Ptr)
	Sprite_GetColor(This.pSprite, r, g, b, a)
End Sub


Property cSprite.UserData () As Any Ptr
	Return Sprite_GetAttachedData(This.pSprite)
End Property

Property cSprite.UserData (d As Any Ptr)
	Sprite_SetAttachedData(This.pSprite, d)
End Property


'============================================================================='
' SpriteSet Type '
'============================================================================='
Constructor cSpriteSet ()
	This.pSpriteSet = SpriteSet_Create()
End Constructor

Constructor cSpriteSet (pSprSet As SpriteSet Ptr)
	This.pSpriteSet = pSprSet
End Constructor

Destructor cSpriteSet ()
	If This.pSpriteSet = 0 Then Return
	SpriteSet_Destroy(This.pSpriteSet, This.DestroySprites)
End Destructor

Sub cSpriteSet.Free ()
	If This.pSpriteSet = 0 Then Return
	SpriteSet_Destroy(This.pSpriteSet, This.DestroySprites)
	This.pSpriteSet = 0
End Sub

Operator cSpriteSet.Cast() As SpriteSet Ptr
	Return This.pSpriteSet
End Operator

'''
' Methods
Sub cSpriteSet.Add (spr As Sprite Ptr)
	SpriteSet_Add(This.pSpriteSet, spr)
End Sub

Function cSpriteSet.Exists (spr As Sprite Ptr) As Integer
	Return SpriteSet_Exists(This.pSpriteSet, spr)
End Function


Sub cSpriteSet.Del (spr As Sprite Ptr)
	SpriteSet_Del(This.pSpriteSet, spr, This.DestroySprites)
End Sub

Sub cSpriteSet.DelAll ()
	SpriteSet_DelAll(This.pSpriteSet, This.DestroySprites)
End Sub


Function cSpriteSet.GetAll (spr_array As Sprite Ptr Ptr, size As Integer) As Integer
	Return SpriteSet_GetAll(This.pSpriteSet, spr_array, size)
End Function

Function cSpriteSet.Iterate (iterate_proc As YAGLSpriteSetIterateProc, user_data As Any Ptr) As Integer
	Return SpriteSet_Iterate(This.pSpriteSet, iterate_proc, user_data)
End Function


Sub cSpriteSet.SetColor (r As UByte, g As UByte, b As UByte, a As UByte)
	SpriteSet_SetColor(This.pSpriteSet, r, g, b, a)
End Sub

Sub cSpriteSet.SetColorEx (clr As YAGL_COLOR)
	SpriteSet_SetColorEx(This.pSpriteSet, clr)
End Sub

Sub cSpriteSet.SetBlendMode (blend_mode As eBLEND_MODE)
	SpriteSet_SetBlendMode(This.pSpriteSet, blend_mode)
End Sub

Sub cSpriteSet.SetVisible (visible As Integer)
	SpriteSet_SetVisible(This.pSpriteSet, visible)
End Sub

Sub cSpriteSet.SetDynamic (d As Integer)
	SpriteSet_SetDynamic(This.pSpriteSet, d)
End Sub


Function cSpriteSet.Collide (spr As Sprite Ptr, force_check As Integer, must_touch_all As Integer) As Integer
	Return SpriteSet_Collide(This.pSpriteSet, spr, force_check, must_touch_all)
End Function


Sub cSpriteSet.Draw ()
	SpriteSet_Draw(This.pSpriteSet)
End Sub

Sub cSpriteSet.DrawShapes ()
	SpriteSet_DrawShapes(This.pSpriteSet)
End Sub


Property cSpriteSet.Count () As Integer
	Return SpriteSet_Count(This.pSpriteSet)
End Property

'============================================================================='
' Animation Type '
'============================================================================='
Constructor cAnimation (n As UInteger)
	This.pAnimation = Animation_Create(n)
End Constructor

Constructor cAnimation (pAnim As Animation Ptr)
	This.pAnimation = pAnim
End Constructor

Destructor cAnimation ()
	If This.pAnimation = 0 Then Return
	Animation_Destroy(This.pAnimation)
End Destructor

Sub cAnimation.Free ()
	If This.pAnimation = 0 Then Return
	Animation_Destroy(This.pAnimation)
	This.pAnimation = 0
End Sub

Operator cAnimation.Cast () As Animation Ptr
	Return This.pAnimation
End Operator

Sub cAnimation.Resize (n As UInteger)
	This.Free()
	This.pAnimation = Animation_Create(n)
End Sub

'''
' Frames
Function cAnimation.AddFrame (duration As Single, tex As Texture Ptr = 0, tex_x As Integer = 0, tex_y As Integer = 0, tex_w As Integer = 0, tex_h As Integer = 0, clr As YAGL_COLOR = &hFFFFFFFF, bm As eBLEND_MODE = BLEND_TRANS, size_change As Integer = 0, size_w As Single = 0, size_h As Single = 0) As Integer
	Return Animation_AddFrameEx(This.pAnimation, duration, tex, tex_x, tex_y, tex_w, tex_h, clr, bm, size_change, size_w, size_h)
End Function

Sub cAnimation.FrameSetBlank (frame_id As UInteger)
	Animation_FrameSetBlank(This.pAnimation, frame_id)
End Sub


Property cAnimation.FrameMax () As Integer
	FrameMax = Animation_FrameMax(This.pAnimation)
End Property

Property cAnimation.FrameCount () As Integer
	FrameCount = Animation_FrameCount(This.pAnimation)
End Property

Sub cAnimation.Empty ()
	Animation_Empty(This.pAnimation)
End Sub

'''
Property cAnimation.TimerMult () As Single
	Return Animation_GetTimerMult(This.pAnimation)
End Property

Property cAnimation.TimerMult (timer_mult As Single)
	Animation_SetTimerMult(This.pAnimation, timer_mult)
End Property

'''
' Frames modification
Sub cAnimation.FrameSetDuration (frame_id As UInteger, duration As Single)
	Animation_FrameSetDuration(This.pAnimation, frame_id, duration)
End Sub

Sub cAnimation.FrameSetTexture (frame_id As UInteger, tex As Texture Ptr, tex_x As Integer, tex_y As Integer, tex_w As Integer, tex_h As Integer)
	Animation_FrameSetTexture(This.pAnimation, frame_id, tex, tex_x, tex_y, tex_w, tex_h)
End Sub

Sub cAnimation.FrameSetColor (frame_id As UInteger, r As UByte, g As UByte, b As UByte, a As UByte)
	Animation_FrameSetColor(This.pAnimation, frame_id, r, g, b, a)
End Sub

Sub cAnimation.FrameSetColorEx (frame_id As UInteger, clr As YAGL_COLOR)
	Animation_FrameSetColorEx(This.pAnimation, frame_id, clr)
End Sub

Sub cAnimation.FrameSetBlendMode (frame_id As UInteger, bm As eBLEND_MODE)
	Animation_FrameSetBlendMode(This.pAnimation, frame_id, bm)
End Sub

Sub cAnimation.FrameSetSize (frame_id As UInteger, size_change As Integer, size_w As Single, size_h As Single)
	Animation_FrameSetSize(This.pAnimation, frame_id, size_change, size_w, size_h)
End Sub


Function cAnimation.FrameGetDuration (frame_id As UInteger) As Single
	Return Animation_FrameGetDuration(This.pAnimation, frame_id)
End Function

Function cAnimation.FrameGetTexture (frame_id As UInteger, tex_x As Integer Ptr, tex_y As Integer Ptr, tex_w As Integer Ptr, tex_h As Integer Ptr) As Texture Ptr
	Return Animation_FrameGetTexture(This.pAnimation, frame_id, tex_x, tex_y, tex_w, tex_h)
End Function

Sub cAnimation.FrameGetColor (frame_id As UInteger, r As UByte Ptr, g As UByte Ptr, b As UByte Ptr, a As UByte Ptr)
	Animation_FrameGetColor(This.pAnimation, frame_id, r, g, b, a)
End Sub

Function cAnimation.FrameGetColorEx (frame_id As UInteger) As YAGL_COLOR
	Return Animation_FrameGetColorEx(This.pAnimation, frame_id)
End Function

Function cAnimation.FrameGetBlendMode (frame_id As UInteger) As eBLEND_MODE
	Return Animation_FrameGetBlendMode(This.pAnimation, frame_id)
End Function

Function cAnimation.FrameGetSize (frame_id As UInteger, size_w As Single Ptr, size_h As Single Ptr) As Integer
	Return Animation_FrameGetSize(This.pAnimation, frame_id, size_w, size_h)
End Function

'============================================================================='
' Particles Emitter Type '
'============================================================================='
Type _PEmitter_
	visible As Integer
	active As Integer ' Emitter active

	' Texture
	tex As Texture Ptr
	As Single tex_rect_1_1, tex_rect_1_2
	As Single tex_rect_2_1, tex_rect_2_2
	As Single tex_rect_3_1, tex_rect_3_2
	As Single tex_rect_4_1, tex_rect_4_2

	' Dynamics
	As Single pos_x, pos_y
	As Single pos_var_x, pos_var_y
	As Single vel, vel_var
	As Single accel, accel_var
	As Single angle, angle_var

	As Single force, force_var
	As Single force_angle, force_angle_var

	As Single p_innertia, p_innertia_var
    As Single p_angle, p_angle_var
	As Single spin, spin_var, spin_flyvar

	' Size
	As Single size, size_var, size_flyvar

	' Life time
	As Single life, life_var

	' Emitte Speed
	As UInteger p_per_sec

	' Maximum particles number
	As UInteger max_particles

	' Blend Mode
	As eBLEND_MODE blend_mode

	' Color
	As UByte col_r, col_g, col_b, col_a
	As Short col_r_var, col_g_var, col_b_var, col_a_var
	As Short col_r_flyvar, col_g_flyvar, col_b_flyvar, col_a_flyvar

	' Callbacks
	As YAGLParticleSpawnProc p_emitte_proc
	As YAGLParticleDeadProc p_dead_proc

	' WARNING: Internal use only
	As Double emitte_timer
	As Any Ptr first
	As UInteger count ' You can acces it, but avoid modification
End Type
#define __EMIT_PTR Cast(_PEmitter_ Ptr, This.pPEmitter)

Constructor cPEmitter ()
	This.pPEmitter = PEmitter_Create(0, 0, 0, 0, 0)
End Constructor

Constructor cPEmitter (pPEmit As PEmitter Ptr)
	This.pPEmitter = pPEmit
End Constructor

Constructor cPEmitter (tex_ As Texture Ptr, tex_x As Integer = 0, tex_y As Integer = 0, tex_w As Integer = 0, tex_h As Integer = 0)
	This.pPEmitter = PEmitter_Create(tex_, tex_x, tex_y, tex_w, tex_h)
End Constructor

Constructor cPEmitter (ByRef source_emit As cPEmitter)
	This.pPEmitter = PEmitter_Create(source_emit.Tex, 0, 0, 0, 0)
	PEmitter_Copy(source_emit, This.pPEmitter, 1)
End Constructor

Destructor cPEmitter ()
	If This.pPEmitter = 0 Then Return
	PEmitter_Destroy(This.pPEmitter)
End Destructor

Sub cPEmitter.Free ()
	If This.pPEmitter = 0 Then Return
	PEmitter_Destroy(This.pPEmitter)
	This.pPEmitter = 0
End Sub

Operator cPEmitter.Cast () As PEmitter Ptr
	Return This.pPEmitter
End Operator

Operator cPEmitter.Let (source_emit As PEmitter Ptr)
	PEmitter_Copy(source_emit, This.pPEmitter, 1)
	This.Tex = PEmitter_GetTexture(source_emit)
End Operator
Operator cPEmitter.Let (ByRef source_emit As cPEmitter)
	PEmitter_Copy(source_emit, This.pPEmitter, 1)
	This.Tex = source_emit.Tex
End Operator

'''
Property cPEmitter.Tex (tex_ As Texture Ptr)
	PEmitter_SetTexture(This.pPEmitter, tex_)
End Property

Property cPEmitter.Tex () As Texture Ptr
	Return PEmitter_GetTexture(This.pPEmitter)
End Property


Sub cPEmitter.SetTextureRect (tex_x As Integer, tex_y As Integer, tex_w As Integer, tex_h As Integer)
	PEmitter_SetTextureRect(This.pPEmitter, tex_x, tex_y, tex_w, tex_h)
End Sub

Sub cPEmitter.GetTextureRect (tex_x As Integer Ptr, tex_y As Integer Ptr, tex_w As Integer Ptr, tex_h As Integer Ptr)
	PEmitter_GetTextureRect(This.pPEmitter, tex_x, tex_y, tex_w, tex_h)
End Sub


Sub cPEmitter.SetTextureMap (tex_map As TextureMap Ptr, rect_id As UInteger)
	PEmitter_SetTextureMap(This.pPEmitter, tex_map, rect_id)
End Sub


Sub cPEmitter.SetCallbacks (spawn_proc As YAGLParticleSpawnProc, dead_proc As YAGLParticleDeadProc)
	PEmitter_SetCallbacks(This.pPEmitter, spawn_proc, dead_proc)
End Sub


'''
Property cPEmitter.Active (act As Integer)
	PEmitter_SetActive(This.pPEmitter, act)
End Property

Property cPEmitter.Active () As Integer
	Return PEmitter_GetActive(This.pPEmitter)
End Property


Sub cPEmitter.Emitte (num As UInteger)
	PEmitter_Emitte(This.pPEmitter, num)
End Sub

Sub cPEmitter.EmitteAt (x As Single, y As Single, num As UInteger)
	PEmitter_EmitteAt(This.pPEmitter, x, y, num)
End Sub


Sub cPEmitter.Draw ()
	PEmitter_Draw(This.pPEmitter)
End Sub


Property cPEmitter.Count () As UInteger
	Return PEmitter_GetCount(This.pPEmitter)
End Property


'''
' Accessors
'	Position

Property cPEmitter.Visible (v As Integer)
	__EMIT_PTR->visible = v
End Property

Property cPEmitter.Visible () As Integer
	Return __EMIT_PTR->visible
End Property


Sub cPEmitter.SetPos (x As Single, y As Single)
	PEmitter_SetPos(This.pPEmitter, x, y)
End Sub

Sub cPEmitter.GetPos (x As Single Ptr, y As Single Ptr)
	PEmitter_GetPos(This.pPEmitter, x, y)
End Sub


Sub cPEmitter.SetPosVar (x As Single, y As Single)
	PEmitter_SetPosVar(This.pPEmitter, x, y)
End Sub

Sub cPEmitter.GetPosVar (x As Single Ptr, y As Single Ptr)
	PEmitter_GetPosVar(This.pPEmitter, x, y)
End Sub


'	Velocity
Property cPEmitter.Vel (v As Single)
	__EMIT_PTR->vel = v
End Property

Property cPEmitter.Vel () As Single
	Return __EMIT_PTR->vel
End Property


Property cPEmitter.VelVar (v As Single)
	__EMIT_PTR->vel_var = v
End Property

Property cPEmitter.VelVar () As Single
	Return __EMIT_PTR->vel_var
End Property


'	Acceleration
Property cPEmitter.Accel (a As Single)
	__EMIT_PTR->accel = a
End Property

Property cPEmitter.Accel () As Single
	Return __EMIT_PTR->accel
End Property


Property cPEmitter.AccelVar (a As Single)
	__EMIT_PTR->accel_var = a
End Property

Property cPEmitter.AccelVar () As Single
	Return __EMIT_PTR->accel_var
End Property


'	Emitte angle
Property cPEmitter.Angle (a As Single)
	__EMIT_PTR->angle = a
End Property

Property cPEmitter.Angle () As Single
	Return __EMIT_PTR->angle
End Property


Property cPEmitter.AngleVar (a As Single)
	__EMIT_PTR->angle_var = a
End Property

Property cPEmitter.AngleVar () As Single
	Return __EMIT_PTR->angle_var
End Property


'	Force
Property cPEmitter.Force (f As Single)
	__EMIT_PTR->force = f
End Property

Property cPEmitter.Force () As Single
	Return __EMIT_PTR->force
End Property


Property cPEmitter.ForceVar (f As Single)
	__EMIT_PTR->force_var = f
End Property

Property cPEmitter.ForceVar () As Single
	Return __EMIT_PTR->force_var
End Property


'	Force angle
Property cPEmitter.ForceAngle (a As Single)
	__EMIT_PTR->force_angle = a
End Property

Property cPEmitter.ForceAngle () As Single
	Return __EMIT_PTR->force_angle
End Property


Property cPEmitter.ForceAngleVar (a As Single)
	__EMIT_PTR->force_angle_var = a
End Property

Property cPEmitter.ForceAngleVar () As Single
	Return __EMIT_PTR->force_angle_var
End Property


'	Particle innertia
Property cPEmitter.ParticleInnertia (i As Single)
	__EMIT_PTR->p_innertia = i
End Property

Property cPEmitter.ParticleInnertia () As Single
	Return __EMIT_PTR->p_innertia
End Property


'	Particle angle
Property cPEmitter.ParticleAngle (a As Single)
	__EMIT_PTR->p_angle = a
End Property

Property cPEmitter.ParticleAngle () As Single
	Return __EMIT_PTR->p_angle
End Property


Property cPEmitter.ParticleAngleVar (a As Single)
	__EMIT_PTR->p_angle_var = a
End Property

Property cPEmitter.ParticleAngleVar () As Single
	Return __EMIT_PTR->p_angle_var
End Property


'	Particle spin
Property cPEmitter.Spin (s As Single)
	__EMIT_PTR->spin = s
End Property

Property cPEmitter.Spin () As Single
	Return __EMIT_PTR->spin
End Property


Property cPEmitter.SpinVar (s As Single)
	__EMIT_PTR->spin_var = s
End Property

Property cPEmitter.SpinVar () As Single
	Return __EMIT_PTR->spin_var
End Property


Property cPEmitter.SpinFlyVar (s As Single)
	__EMIT_PTR->spin_flyvar = s
End Property

Property cPEmitter.SpinFlyVar () As Single
	Return __EMIT_PTR->spin_flyvar
End Property


'	Particle size
Property cPEmitter.Size (s As Single)
	__EMIT_PTR->size = s
End Property

Property cPEmitter.Size () As Single
	Return __EMIT_PTR->size
End Property


Property cPEmitter.SizeVar (s As Single)
	__EMIT_PTR->size_var = s
End Property

Property cPEmitter.SizeVar () As Single
	Return __EMIT_PTR->size_var
End Property


Property cPEmitter.SizeFlyVar (s As Single)
	__EMIT_PTR->size_flyvar = s
End Property

Property cPEmitter.SizeFlyVar () As Single
	Return __EMIT_PTR->size_flyvar
End Property


'	Particle life time
Property cPEmitter.Life (l As Single)
	__EMIT_PTR->life = l
End Property

Property cPEmitter.Life () As Single
	Return __EMIT_PTR->life
End Property


Property cPEmitter.LifeVar (l As Single)
	__EMIT_PTR->life_var = l
End Property

Property cPEmitter.LifeVar () As Single
	Return __EMIT_PTR->life_var
End Property


'	Emitte rate
Property cPEmitter.EmitteRate (r As UInteger)
	__EMIT_PTR->p_per_sec = r
End Property

Property cPEmitter.EmitteRate () As UInteger
	Return __EMIT_PTR->p_per_sec
End Property


'	Max particles
Property cPEmitter.MaxParticles (m As UInteger)
	__EMIT_PTR->max_particles = m
End Property

Property cPEmitter.MaxParticles () As UInteger
	Return __EMIT_PTR->max_particles
End Property


'	Blend mode
Property cPEmitter.BlendMode (bm As eBLEND_MODE)
	__EMIT_PTR->blend_mode = bm
End Property

Property cPEmitter.BlendMode () As eBLEND_MODE
	Return __EMIT_PTR->blend_mode
End Property


'	Color
Sub cPEmitter.SetColor (r As UByte, g As UByte, b As UByte, a As UByte)
	PEmitter_SetColor(This.pPEmitter, r, g, b, a)
End Sub

Sub cPEmitter.SetColorVar (r As Short, g As Short, b As Short, a As Short)
	PEmitter_SetColorVar(This.pPEmitter, r, g, b, a)
End Sub

Sub cPEmitter.SetColorFlyVar (r As Short, g As Short, b As Short, a As Short)
	PEmitter_SetColorFlyVar(This.pPEmitter, r, g, b, a)
End Sub


Sub cPEmitter.GetColor (r As UByte Ptr, g As UByte Ptr, b As UByte Ptr, a As UByte Ptr)
	PEmitter_GetColor(This.pPEmitter, r, g, b, a)
End Sub

Sub cPEmitter.GetColorVar (r As Short Ptr, g As Short Ptr, b As Short Ptr, a As Short Ptr)
	PEmitter_GetColorVar(This.pPEmitter, r, g, b, a)
End Sub

Sub cPEmitter.GetColorFlyVar (r As Short Ptr, g As Short Ptr, b As Short Ptr, a As Short Ptr)
	PEmitter_GetColorFlyVar(This.pPEmitter, r, g, b, a)
End Sub


'============================================================================='
' Shader Type '
'============================================================================='
Constructor cShader ()
	Shader_Init(0)
	This.pShader = Shader_Create()
End Constructor

Destructor cShader ()
	If This.pShader = 0 Then Return
	Shader_Destroy(This.pShader)
End Destructor

Sub cShader.Free ()
	If This.pShader = 0 Then Return
	Shader_Destroy(This.pShader)
	This.pShader = 0
End Sub

'''
Static Sub cShader.Init (fatal_fail As Const Integer)
	Shader_Init(fatal_fail)
End Sub

Static Function cShader.IsInit () As Integer
	Return Shader_IsInit()
End Function

Static Sub cShader.SetCompileErrFatal (flag As Const Integer)
	Shader_SetCompileErrFatal(flag)
End Sub

Static Sub cShader.SetLinkErrFatal (flag As Const Integer)
	Shader_SetLinkErrFatal(flag)
End Sub

Static Sub cShader.SetInfoLogShow (flag As Const Integer)
	Shader_SetInfoLogShow(flag)
End Sub

Static Sub cShader.UnUse ()
	Shader_Use(0)
End Sub

'''
Function cShader.AddSource (src As Const ZString, shader_type As eSHADER_TYPE) As Integer
	Return Shader_AddSource(This.pShader, src, shader_type)
End Function

Function cShader.AddSourceFile (file As Const ZString, shader_type As eSHADER_TYPE) As Integer
	Return Shader_AddSourceFile(This.pShader, file, shader_type)
End Function

Function cShader.Link () As Integer
	Return Shader_Link(This.pShader)
End Function

Sub cShader.Use ()
	Shader_Use(This.pShader)
End Sub

Property cShader.Ready () As Integer
	Return Shader_IsReady(This.pShader)
End Property


'============================================================================='
' Bitmap Font Type '
'============================================================================='
Constructor cBmpFont (fnt As Const ZString, tex As Const ZString)
	This.pBmpFont = BmpFont_Create(fnt, tex)
End Constructor

Constructor cBmpFont (pBFnt As BmpFont Ptr)
	This.pBmpFont = pBFnt
End Constructor

Destructor cBmpFont ()
	If This.pBmpFont = 0 Then Return
	BmpFont_Destroy(This.pBmpFont)
End Destructor

Sub cBmpFont.Free ()
	If This.pBmpFont = 0 Then Return
	BmpFont_Destroy(This.pBmpFont)
	This.pBmpFont = 0
End Sub

Operator cBmpFont.Cast () As BmpFont Ptr
	Return This.pBmpFont
End Operator

'''
Function cBmpFont.CharExists (ch As Byte) As Integer
	Return BmpFOnt_CharExists(This.pBmpFont, ch)
End Function

Function cBmpFont.Measure (text As Const ZString, size As Integer) As Integer
	Return BmpFont_Measure(This.pBmpFont, text, size)
End Function

Sub cBmpFont.Print (text As Const ZString, x As Integer, y As Integer, size As Integer, align As eALIGN, angle As Single)
	BmpFont_Print(This.pBmpFont, text, x, y, size, align, angle)
End Sub

Sub cBmpFont.PrintLines (text As Const ZString, x As Integer, y As Integer, size As Integer, align As eALIGN, angle As Single)
	BmpFont_PrintLines(This.pBmpFont, text, x, y, size, align, angle)
End Sub

'============================================================================='
' Bitmap Text Type '
'============================================================================='
Type _BmpText_
	As Integer visible
	As Any Ptr text
	As BmpFont Ptr font
	As Integer size
	As Integer multiligne
	As Single pos_x, pos_y
	As Integer align
	As Single angle
	As YAGL_COLOR clr
	As eBLEND_MODE blend_mode
End Type
#define __BTXT_PTR Cast(_BmpText_ Ptr, This.pBmpText)

Constructor cBmpText ()
	This.pBmpText = BmpText_Create(0, "", 0, 0)
End Constructor

Constructor cBmpText (pBTxt As BmpText Ptr)
	This.pBmpText = pBTxt
End Constructor

Constructor cBmpText (bfnt As BmpFont Ptr = 0, txt As Const ZString = "", s As UInteger = 16, ml As Integer = 0)
	This.pBmpText = BmpText_Create(bfnt, txt, s, ml)
End Constructor

Destructor cBmpText ()
	If This.pBmpText = 0 Then Return
	BmpText_Destroy(This.pBmpText)
End Destructor

Sub cBmpText.Free ()
	If This.pBmpText = 0 Then Return
	BmpText_Destroy(This.pBmpText)
	This.pBmpText = 0
End Sub

Sub cBmpText.Draw ()
	BmpText_Draw(This.pBmpText)
End Sub

'''
Property cBmpText.Font (bfnt As BmpFont Ptr)
	__BTXT_PTR->font = bfnt
End Property

Property cBmpText.Font () As BmpFont Ptr
	Return __BTXT_PTR->font
End Property


Property cBmpText.Text (txt As Const ZString)
	BmpText_SetText(This.pBmpText, txt)
End Property

Property cBmpText.Text () As ZString Ptr
	Return BmpText_GetText(This.pBmpText)
End Property


Property cBmpText.Len () As Integer
	Return BmpText_GetLen(This.pBmpText)
End Property


Property cBmpText.Visible (v As Integer)
	__BTXT_PTR->visible = v
End Property

Property cBmpText.Visible () As Integer
	Return __BTXT_PTR->visible
End Property


Property cBmpText.Multiline (ml As Integer)
	__BTXT_PTR->multiligne = ml
End Property

Property cBmpText.Multiline () As Integer
	Return __BTXT_PTR->multiligne
End Property


Sub cBmpText.SetPos (x As Integer, y As Integer)
	__BTXT_PTR->pos_x = x
	__BTXT_PTR->pos_y = y
End Sub

Sub cBmpText.GetPos (x As Integer Ptr, y As Integer Ptr)
	If x <> 0 Then *x = __BTXT_PTR->pos_x
	If y <> 0 Then *y = __BTXT_PTR->pos_y
End Sub


Property cBmpText.Size (s As Integer)
	__BTXT_PTR->size = s
End Property

Property cBmpText.Size () As Integer
	Return __BTXT_PTR->size
End Property


Property cBmpText.Align (a As eALIGN)
	__BTXT_PTR->align = a
End Property

Property cBmpText.Align () As eALIGN
	Return __BTXT_PTR->align
End Property


Property cBmpText.Angle (a As Single)
	__BTXT_PTR->angle = a
End Property

Property cBmpText.Angle () As Single
	Return __BTXT_PTR->angle
End Property


Property cBmpText.BlendMode (bm As eBLEND_MODE)
	__BTXT_PTR->blend_mode = bm
End Property

Property cBmpText.BlendMode () As eBLEND_MODE
	Return __BTXT_PTR->blend_mode
End Property


Property cBmpText.Color (clr As YAGL_COLOR)
	__BTXT_PTR->clr = clr
End Property

Property cBmpText.Color () As YAGL_COLOR
	Return __BTXT_PTR->clr
End Property


Sub cBmpText.SetColor (r As UByte, g As UByte, b As UByte, a As UByte)
	BmpText_SetColor(This.pBmpText, r, g, b, a)
End Sub

Sub cBmpText.GetColor (r As UByte Ptr, g As UByte Ptr, b As UByte Ptr, a As UByte Ptr)
	BmpText_GetColor(This.pBmpText, r, g, b, a)
End Sub
