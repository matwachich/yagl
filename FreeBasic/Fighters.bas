#include "yagl.bi"

' Window Size/Screen Resolution
#define dSCR_W 1024
#define dSCR_H 600
#define dVIEW_W 1024
#define dVIEW_H 600

' Max units per team
#define dMAX_UNITS_PER_TEAM 10

' Units size
#define dUNIT_SIZE_X 24
#define dUNIT_SIZE_Y 24

' Team colors
#define dTEAM_1_COLOR YAGL_RGBA(255, 128, 128, 255) ' Red
#define dTEAM_2_COLOR YAGL_RGBA(128, 255, 128, 255) ' Green

' Unit dynamics
#define dUNIT_VEL_MIN 100
#define dUNIT_VEL_MAX 200
#define dUNIT_INNERTIA 20
#define dUNIT_AVEL_MAX 180
#define dUNIT_AINNERTIA 1000
#define dUNIT_ACCEL 500
#define dUNIT_AACCEL 600

' Shot
#define dSHOT_CONE_ANGLE 5 ' degrees
#define dSHOT_DELAY 0.1 ' s => 10/sec
#define dSHOT_VEL 1000
#define dSHOT_DAMAGE 10
#define dSHOT_LIFE 0.5 ' s
Const dSHOT_MIN_RANGE = dSHOT_LIFE * dSHOT_VEL

' Collisions
#define dTEAM_1_UNIT_COLL_MASK 1 ' team 1 units collision mask, same as team 2 shots => collision
#define dTEAM_2_UNIT_COLL_MASK 2 ' team 2 units collision mask, same as team 1 shots => collision
#define dUNIT_COLL_GROUP 1 ' all units in the same coll. group => they wont collide each other ...

#define dTEAM_1_SHOT_COLL_MASK 2 ' team 1 shots collision mask
#define dTEAM_2_SHOT_COLL_MASK 1 ' team 2 shots collision mask
#define dSHOT_COLL_GROUP 2 ' all shots in the same coll. group => they wont collide each other ...
' ... units and shots have different coll. groups => they will collide

' Ressources and data paths
#define dTEX_BK			"data\fighters\spacefield.png"
#define dTEX_SHIP		"data\fighters\ship.png"
#define dTEX_SHOT		"data\fighters\shot.png"
#define dTEX_PARTS		"data\fighters\particles.png"
#define dTEX_ANIM_BOOM	"data\fighters\Explosion1spritesheet.png"
#define dFNT_TEX		"data\fighters\calibri.png"
#define dFNT_DEF		"data\fighters\calibri.fnt"

#define dPRT_FILE		"data\fighters\particles.ini"
#define dPRT_SPAWN		"spawn"
#define dPRT_HIT		"hit"
#define dPRT_BOOM_FIRE	"boom_fire"
#define dPRT_BOOM_SMOKE	"boom_smoke"
#define dPRT_ENGINE		"engine"

' Effects
#define dTIMERS_MULT 0.9
#define dKEEP_IN_SCREEN
'#define dDRAW_TARGET_LINE
'#define dDRAW_COLL_SHAPE
#define dDRAW_DEBUG_INFO
#define dPRT_EMITTE_COUNT_SPAWN 10
#define dPRT_EMITTE_COUNT_HIT 20
#define dPRT_EMITTE_COUNT_BOOM 50

' -----------------------------------------------------------------------------

' Team enumeration
Enum eTEAM
	team_1, team_2
End Enum

' -----------------------------------------------------------------------------

' Will hold all global vars
Type tGameData
	' Textures
	As Texture Ptr pTex_bk, pTex_ship, pTex_shot, pTex_parts, pTex_anim_boom
	' Background Quad
	As Quad Ptr pQd_bk
	' Font
	As BmpFont Ptr pFnt_fnt
	As BmpText Ptr pTxt_score1, pTxt_score2
	#ifdef dDRAW_DEBUG_INFO
	As BmpText Ptr pTxt_debug
	#endif
	As Integer iScore1, iScore2 = 0
	' Particles
	As PEmitter Ptr pPEmit_spawn, pPEmit_hit, pPEmit_boomFire, pPEmit_boomSmoke, pPEmit_engineDummy ' ...
	' ... Dummy because this emitter will not be used directly, it will a "configuration container" that the other engine emitter will copy
	' this is to avoid multiple disk access
	'''
	' 2 teams, 2 MultiSets for Sprites
	As MultiSet Ptr pSetSpr_team1, pSetSpr_team2
	' A MultiSet for the shots sprites
	As MultiSet Ptr pSetSpr_shots
	' A MultiSet for engines Paticles
	As MultiSet Ptr pSetEmit_engines
	' A MultiSet for explosions
	As MultiSet Ptr pSetSpr_explosions
	'''
	' Explosion animation
	As Animation Ptr pAnim_boom
End Type

' Data attached to a unit
Type tShipData
	As Byte health ' current health
	As eTEAM team ' team
	As Sprite Ptr target ' target
	
	As PEmitter Ptr engine ' engine particles emitter
	
	As Double shot_timer
End Type

' Data attached to a shot
Type tShotData
	As eTEAM team ' team
	As UByte kill_me ' set to 1 when the shot has to be deleted (collision with a unit)
	
	As Double life_timer
End Type

' -----------------------------------------------------------------------------
' Functions and procedures declaration

Declare Sub Game_Init ()
Declare Sub Game_Clean ()
Declare Sub Game_Loop ()

Declare Sub Team_Fill (team As eTEAM)
Declare Function Team_MoveProc cdecl (set As MultiSet Ptr, unit As Sprite Ptr, user_data As Any Ptr, rank As Integer, set_type As eSET_TYPE) As Integer

Declare Sub Unit_Create (team As eTEAM)
Declare Function Unit_Move (unit As Sprite Ptr) As Integer
Declare Sub Unit_SetTarget (unit As Sprite Ptr)
Declare Sub Unit_Shot (unit As Sprite Ptr)
Declare Function Unit_DrawHealth cdecl (set As MultiSet Ptr, unit As Sprite Ptr, user_data As Any Ptr, rank As Integer, set_type As eSET_TYPE) As Integer
#ifdef dDRAW_TARGET_LINE
Declare Function Unit_DrawTargetLine cdecl (set As MultiSet Ptr, unit As Sprite Ptr, user_data As Any Ptr, rank As Integer, set_type As eSET_TYPE) As Integer
#endif

Declare Sub Explosion_Add (x As Single, y As Single)
Declare Function Explosion_Process cdecl (set As MultiSet Ptr, unit As Sprite Ptr, user_data As Any Ptr, rank As Integer, set_type As eSET_TYPE) As Integer

Declare Function Shots_ProcessProc cdecl (set As MultiSet Ptr, unit As Sprite Ptr, user_data As Any Ptr, rank As Integer, set_type As eSET_TYPE) As Integer

Declare Sub CollisionProc cdecl (As Sprite Ptr, As Sprite Ptr)
Declare Function SpriteCleanDataProc cdecl (set As MultiSet Ptr, unit As Sprite Ptr, user_data As Any Ptr, rank As Integer, set_type As eSET_TYPE) As Integer

Declare Sub ScoreUp (As eTEAM)
#ifdef dDRAW_DEBUG_INFO
declare sub UpdateDebug ()
#endif

' -----------------------------------------------------------------------------

' Global game data
Dim Shared _game_ As tGameData

System_Init(DEBUG_ON_STD)
Window_Create(dSCR_W, dSCR_H, 8, 8, 8, 0, "Fighters - YAGL Example", 0, 0)
View_SetRect(0, 0, dVIEW_W, dVIEW_H)

Render_SetTimersMult(dTIMERS_MULT)
Collision_SetCallback(Cast(YAGLCollisionProc, @CollisionProc))

Game_Init()
Game_Loop()
Game_Clean()

System_Terminate()

' -----------------------------------------------------------------------------

Sub Game_Loop ()
	While Window_IsOpened() And Not Events_KeyGet(YAGL_KEY_ESC)
		Render_Begin()
		''' Logics
		' Fill teams
		Team_Fill(team_1)
		Team_Fill(team_2)
		' Move units
		MultiSet_Iterate(_game_.pSetSpr_team1, Cast(YAGLMultiSetIterateProc, @Team_MoveProc), Cast(Any Ptr, 0))
		MultiSet_Iterate(_game_.pSetSpr_team2, Cast(YAGLMultiSetIterateProc, @Team_MoveProc), Cast(Any Ptr, 0))
		' Process shots
		MultiSet_Iterate(_game_.pSetSpr_shots, Cast(YAGLMultiSetIterateProc, @Shots_ProcessProc), Cast(Any Ptr, 0))
		' Process explosion animations
		MultiSet_Iterate(_game_.pSetSpr_explosions, Cast(YAGLMultiSetIterateProc, @Explosion_Process), Cast(Any Ptr, 0))
		'''
		' Drawings
		' Draw the background first
		Quad_Draw(_game_.pQd_bk)
		' Explosions
		PEmitter_Draw(_game_.pPEmit_boomSmoke)
		PEmitter_Draw(_game_.pPEmit_boomFire)
		MultiSet_Draw(_game_.pSetSpr_explosions)
		' Then the shots, the units and their engines
		MultiSet_Draw(_game_.pSetSpr_shots)
		MultiSet_Draw(_game_.pSetEmit_engines)
		MultiSet_Draw(_game_.pSetSpr_team1)
		MultiSet_Draw(_game_.pSetSpr_team2)
		' And finally, the effects
		PEmitter_Draw(_game_.pPEmit_spawn)
		PEmitter_Draw(_game_.pPEmit_hit)
		' Units Health bars, and target lines
		MultiSet_Iterate(_game_.pSetSpr_team1, Cast(YAGLMultiSetIterateProc, @Unit_DrawHealth), Cast(Any Ptr, 0))
		MultiSet_Iterate(_game_.pSetSpr_team2, Cast(YAGLMultiSetIterateProc, @Unit_DrawHealth), Cast(Any Ptr, 0))
		#ifdef dDRAW_TARGET_LINE
		MultiSet_Iterate(_game_.pSetSpr_team1, Cast(YAGLMultiSetIterateProc, @Unit_DrawTargetLine), Cast(Any Ptr, 0))
		MultiSet_Iterate(_game_.pSetSpr_team2, Cast(YAGLMultiSetIterateProc, @Unit_DrawTargetLine), Cast(Any Ptr, 0))
		#endif
		' Scores
		BmpText_Draw(_game_.pTxt_score1)
		BmpText_Draw(_game_.pTxt_score2)
		#ifdef dDRAW_DEBUG_INFO
		UpdateDebug()
		BmpText_Draw(_game_.pTxt_debug)
		#endif
		'''
		Render_End()
	Wend
End Sub

' -----------------------------------------------------------------------------
' Teams

' Fills a team with units
Sub Team_Fill (team As eTEAM)
	Dim As MultiSet Ptr set = 0
	Select Case team
		Case team_1
			set = _game_.pSetSpr_team1
		Case team_2
			set = _game_.pSetSpr_team2
	End Select
	' ---
	' fill only if there are less then dMAX_UNITS_PER_TEAM in the MultiSet
	For i As Integer = 1 To dMAX_UNITS_PER_TEAM - MultiSet_Count(set)
		Unit_Create(team)
	Next
End Sub

' Callback for MultiSet_Iterate: Calls Unit_Move() on every unit of the MultiSet
Function Team_MoveProc cdecl (set As MultiSet Ptr, unit As Sprite Ptr, user_data As Any Ptr, rank As Integer, set_type As eSET_TYPE) As Integer
	Return Unit_Move(unit)
End Function

' -----------------------------------------------------------------------------
' Units

' Create a unit, and add it to a team
Sub Unit_Create (team As eTEAM)
	' Sprite creation
	Dim As Sprite Ptr spr = Sprite_Create(_game_.pTex_ship, 0, 0, 0, 0)
	' Unit size
	Sprite_SetSize(spr, dUNIT_SIZE_X, dUNIT_SIZE_Y)
	'''
	' Unit pos and angle (both random)
	Dim As Single x, y
	Select Case team
		Case team_1
			x = Misc_RandomI(30, 60)
			y = Misc_RandomI(30, dVIEW_H - 30)
		Case team_2
			x = Misc_RandomI(dVIEW_W - 60, dVIEW_W - 30)
			y = Misc_RandomI(30, dVIEW_H - 30)
	End Select
	Sprite_SetPos(spr, x, y)
	Sprite_SetAngle(spr, Misc_RandomI(0, 360))
	' Spawn effect
	PEmitter_SetPos(_game_.pPEmit_spawn, x, y)
	PEmitter_Emitte(_game_.pPEmit_spawn, dPRT_EMITTE_COUNT_SPAWN)
	'''
	' Dynamics
	Sprite_SetVelMax(spr, Misc_RandomI(dUNIT_VEL_MIN, dUNIT_VEL_MAX))
	Sprite_SetAVelMax(spr, dUNIT_AVEL_MAX)
	Sprite_SetInnertia(spr, dUNIT_INNERTIA)
	Sprite_SetAInnertia(spr, dUNIT_AINNERTIA)
	'''
	' Sprite's collision parameters (coll. mask is set later ...)
	Sprite_SetShape(spr, SHAPE_CIRCLE, dUNIT_SIZE_X / 2, dUNIT_SIZE_Y / 2, dUNIT_SIZE_X / 2.5, 0)
	Sprite_SetCollisionGroup(spr, dUNIT_COLL_GROUP)
	'''
	' Allocating unit data structure, and initializing it
	Dim As tShipData Ptr unit_data = Allocate(SizeOf(tShipData))
	unit_data->health = 100
	unit_data->team = team
	unit_data->target = 0
	unit_data->shot_timer = Misc_TimerInit()
	' create a particle emitter for the unit's engine
	unit_data->engine = PEmitter_Create(_game_.pTex_parts, 0, 0, 0, 0)
	PEmitter_Copy(_game_.pPEmit_engineDummy, unit_data->engine, 1) ' copy it's configuration from the Dummy global emitter
	MultiSet_Add(_game_.pSetEmit_engines, unit_data->engine, -1) ' add the engines PEmitter to the MultiSet
	'''
	' Attach unit data to the Sprite
	Sprite_SetAttachedData(spr, unit_data)
	'''
	Select Case team ' team specific data
		Case team_1
			Sprite_SetColorEx(spr, dTEAM_1_COLOR) ' color
			Sprite_SetCollisionMask(spr, dTEAM_1_UNIT_COLL_MASK) ' ... collision mask
			MultiSet_Add(_game_.pSetSpr_team1, spr, -1) ' add the unit to the right MultiSet
		Case team_2
			Sprite_SetColorEx(spr, dTEAM_2_COLOR)
			Sprite_SetCollisionMask(spr, dTEAM_2_UNIT_COLL_MASK)
			MultiSet_Add(_game_.pSetSpr_team2, spr, -1)
	End Select
End Sub

' IA: move the unit toward it's target, and shot
Function Unit_Move (unit As Sprite Ptr) As Integer
	Dim As tShipData Ptr unit_data = Cast(tShipData Ptr, Sprite_GetAttachedData(unit))
	' ---
	' first of all, check if the unit has to be deleted (health <= 0)
	If unit_data->health <= 0 Then
		' destroy the unit
		MultiSet_Del(_game_.pSetEmit_engines, unit_data->engine, 1) ' the engine particles emitter
		Deallocate(unit_data) ' deallocate attached data
		'''
		' explosion effect
		Dim As Single x, y
		Sprite_GetPos(unit, @x, @y)
		Explosion_Add(x, y) ' add explosion animation
		'PEmitter_SetPos(_game_.pPEmit_boomFire, x, y)
		PEmitter_SetPos(_game_.pPEmit_boomSmoke, x, y)
		'PEmitter_Emitte(_game_.pPEmit_boomFire, dPRT_EMITTE_COUNT_BOOM)
		PEmitter_Emitte(_game_.pPEmit_boomSmoke, dPRT_EMITTE_COUNT_BOOM)
		'''
		' ScoreUp the other team
		Select Case unit_data->team
			Case team_1
				ScoreUp(team_2)
			Case team_2
				ScoreUp(team_1)
		End Select
		'''
		' Return 2, so that the Team_MoveProc() will return 2 and the unit will be deleted from it's MultiSet
		Return 2
	EndIf
	' ---
	Unit_SetTarget(unit)
	' ---
	' If not target, stop engines and return
	If unit_data->target = 0 Then
		Sprite_SetAccelLen(unit, 0)
		Sprite_SetAAccel(unit, 0)
		PEmitter_SetActive(unit_data->engine, 0)
		Return 0
	EndIf
	' ---
	' update particles emitter engine position
	Dim As Single x, y
	Sprite_SpriteToWorldEx(unit, 0, 0.5, @x, @y)
	PEmitter_SetPos(unit_data->engine, x, y)
	' ---
	Dim As Single dist, angle_diff
	' distance between the unit and it's target
	dist = Geo_SprtoSpr_Dist(unit, unit_data->target)
	' angle difference between the unit and it's target
	angle_diff = Geo_SprtoSpr_AngleDiff(unit, unit_data->target)
	' ---
	Select Case angle_diff ' rotation
		Case Is > 5
			Sprite_SetAAccel(unit, dUNIT_AACCEL) ' rotate counter-clockwise
		Case Is < -5
			Sprite_SetAAccel(unit, -dUNIT_AACCEL) ' rotate clockwise
		Case Else ' here, the unit is directed toward it's target
			Sprite_SetAAccel(unit, 0) ' stop rotating
			' if the target is in range, then shot
			If dist <= dSHOT_MIN_RANGE Then Unit_Shot(unit)
	End Select
	' ---
	Select Case angle_diff ' propulsion
		Case Is > 30, Is < -30
			Sprite_SetAccelLen(unit, 0) ' engines OFF
			PEmitter_SetActive(unit_data->engine, 0)
		Case Is <= 30, Is >= -30
			Sprite_SetAccelLen(unit, dUNIT_ACCEL) ' engines NO
			PEmitter_SetActive(unit_data->engine, 1)
	End Select
	' ---
	' Keep in screen
	#ifdef dKEEP_IN_SCREEN
	Sprite_GetPos(unit, @x, @y)
	If x < 0 Then x += dVIEW_W
	If x > dVIEW_W Then x -= dVIEW_W
	If y < 0 Then y += dVIEW_H
	If y > dVIEW_H Then y -= dVIEW_H
	Sprite_SetPos(unit, x, y)
	#endif
	' ---
	Return 0
End Function

' select the closest enemy unit as a target
Sub Unit_SetTarget (unit As Sprite Ptr)
	Dim As tShipData Ptr unit_data = Cast(tShipData Ptr, Sprite_GetAttachedData(unit))
	' ---
	Dim As MultiSet Ptr enemies_set = 0
	
	' select the enemies MultiSet
	Select Case unit_data->team
		Case team_1
			enemies_set = _game_.pSetSpr_team2
		Case team_2
			enemies_set = _game_.pSetSpr_team1
	End Select
	' ---
	' if there is already a target, and the target exists in the enemies MultiSet, then return
	If unit_data->target <> 0 And MultiSet_Exists(enemies_set, unit_data->target) Then
		Return
	EndIf
	' ---
	' if the enemies MultiSet is empty, then no target and return
	If MultiSet_Count(enemies_set) = 0 Then
		unit_data->target = 0
		Return
	EndIf
	' ---
	' an array of Sprite pointers to hold all the enemy units
	Dim As Sprite Ptr enemies(0 to dMAX_UNITS_PER_TEAM - 1)
	Dim As Integer enemy_id = -1, min_distance = 0, tmp_distance = 0
	
	' this loop selects the closest enemy unit, and store it's array ID in enemy_id
	For i As Integer = 0 To MultiSet_GetAll(enemies_set, @enemies(0), dMAX_UNITS_PER_TEAM) - 1
		tmp_distance = Geo_SprtoSpr_Dist(unit, enemies(i))
		If tmp_distance < min_distance Or min_distance = 0 Then
			min_distance = tmp_distance
			enemy_id = i
		EndIf
	Next
	
	' if an enemy has been selected by the loop, then set it as target
	If enemy_id <> -1 Then
		unit_data->target = enemies(enemy_id)
	Else
		unit_data->target = 0 ' no target
	End If
End Sub

' create a shot Sprite and attach it to the shots MultiSet
Sub Unit_Shot (unit As Sprite Ptr)
	Dim As tShipData Ptr unit_data = Cast(tShipData Ptr, Sprite_GetAttachedData(unit))
	' ---
	' shot only if the delay has passed
	If Misc_TimerDiff(unit_data->shot_timer) < dSHOT_DELAY Then Return
	unit_data->shot_timer = Misc_TimerInit()
	' ---
	' get unit properties (position and angle)
	Dim As Single x, y, angle = 0
	Sprite_GetPos(unit, @x, @y)
	angle = Sprite_GetAngle(unit)
	' ---
	' create the shot Sprite
	Dim As Sprite Ptr spr = Sprite_Create(_game_.pTex_shot, 0, 0, 0, 0)
	Sprite_SetPos(spr, x, y)
	Sprite_SetAngle(spr, Misc_RandomF(angle - (dSHOT_CONE_ANGLE/2), angle + (dSHOT_CONE_ANGLE/2)))
	' ---
	' shot speed
	Sprite_SetVelLen(spr, dSHOT_VEL)
	' ---
	' shot collision data
	Sprite_SetShape(spr, SHAPE_POINT, 24, 4, 0, 0)
	Sprite_SetCollisionGroup(spr, dSHOT_COLL_GROUP)
	' ---
	' create the attached shot data structure
	Dim As tShotData Ptr shot_data = Allocate(SizeOf(tShotData))
	shot_data->team = unit_data->team
	shot_data->kill_me = 0
	shot_data->life_timer = Misc_TimerInit()
	' ---
	Select Case shot_data->team ' team specific properties
		Case team_1
			Sprite_SetColorEx(spr, dTEAM_1_COLOR) ' color
			Sprite_SetCollisionMask(spr, dTEAM_1_SHOT_COLL_MASK) ' collision mask
		Case team_2
			Sprite_SetColorEx(spr, dTEAM_2_COLOR)
			Sprite_SetCollisionMask(spr, dTEAM_2_SHOT_COLL_MASK)
	End Select
	' ---
	' attach shot_data and add to shots MultiSet
	Sprite_SetAttachedData(spr, shot_data)
	MultiSet_Add(_game_.pSetSpr_shots, spr, -1)
End Sub

' Draws a health bar over every unit
Function Unit_DrawHealth cdecl (set As MultiSet Ptr, unit As Sprite Ptr, user_data As Any Ptr, rank As Integer, set_type As eSET_TYPE) As Integer
	Dim As tShipData Ptr unit_data = Cast(tShipData Ptr, Sprite_GetAttachedData(unit))
	' ---
	' get unit's position
	Dim As Single x, y
	Sprite_GetPos(unit, @x, @y)
	' ---
	' set drawing parameters
	Draw_SetGlow(0)
	Draw_SetSize(1)
	Select Case unit_data->health
		Case Is >= 60
			Draw_SetColorEx(YAGL_COLOR_GREEN)
		Case Is >= 30
			Draw_SetColorEx(YAGL_COLOR_YELLOW)
		Case Else
			Draw_SetColorEx(YAGL_COLOR_RED)
	End Select
	' ---
	' draw the health bar (filled rectangle)
	Draw_RectCenterF(x, y - 20, (unit_data->health / 100) * 32, 4, 0)
	' ---
	Return 0
End Function

#ifdef dDRAW_TARGET_LINE
Function Unit_DrawTargetLine cdecl (set As MultiSet Ptr, unit As Sprite Ptr, user_data As Any Ptr, rank As Integer, set_type As eSET_TYPE) As Integer
	Dim As tShipData Ptr unit_data = Cast(tShipData Ptr, Sprite_GetAttachedData(unit))
	' ---
	If unit_data->target = 0 Or Sprite_IsSprite(unit_data->target) = 0 Then Return 0
	' ---
	Dim As Single ux, uy, tx, ty
	Sprite_GetPos(unit, @ux, @uy)
	Sprite_GetPos(unit_data->target, @tx, @ty)
	' ---
	Draw_SetGlow(1)
	Draw_SetSize(5)
	Draw_SetColorEx(YAGL_COLOR_WHITE)
	Draw_Line(ux, uy, tx, ty)
End Function
#endif

Sub Explosion_Add (x As Single, y As Single)
	Dim As Sprite Ptr spr = Sprite_Create(0, 0, 0, 0, 0)
	'
	Sprite_SetPos(spr, x, y)
	Dim As Integer rnd_size = Misc_RandomI(96, 128)
	Sprite_SetSize(spr, rnd_size, rnd_size)
	Sprite_SetAngle(spr, Misc_RandomI(0, 360))
	'
	Sprite_AnimationSet(spr, _game_.pAnim_boom)
	Sprite_AnimationGo(spr, 0)
	'
	MultiSet_Add(_game_.pSetSpr_explosions, spr, -1)
End Sub

Function Explosion_Process cdecl (set As MultiSet Ptr, unit As Sprite Ptr, user_data As Any Ptr, rank As Integer, set_type As eSET_TYPE) As Integer
	If Sprite_AnimationGetStatus(unit) = 0 Then
		Return 2
	EndIf
	Return 0
End Function

' -----------------------------------------------------------------------------

Function Shots_ProcessProc cdecl (set As MultiSet Ptr, unit As Sprite Ptr, user_data As Any Ptr, rank As Integer, set_type As eSET_TYPE) As Integer
	Dim As tShotData Ptr shot_data = Cast(tShotData Ptr, Sprite_GetAttachedData(unit))
	' ---
	If shot_data->kill_me = 1 Or Misc_TimerDiff(shot_data->life_timer)>= dSHOT_LIFE Then
		Deallocate(shot_data)
		Return 2 ' destroy the shot
	EndIf
	Return 0
End Function

' -----------------------------------------------------------------------------

Sub Game_Init ()
	' Textures
	_game_.pTex_bk = Texture_Create(dTEX_BK, 0)
	_game_.pTex_ship = Texture_Create(dTEX_SHIP, 0)
	_game_.pTex_shot = Texture_Create(dTEX_SHOT, 0)
	_game_.pTex_parts = Texture_Create(dTEX_PARTS, 0)
	_game_.pTex_anim_boom = Texture_Create(dTEX_ANIM_BOOM, 0)
	' BK Quad
	_game_.pQd_bk = Quad_Create(_game_.pTex_bk, 0, 0, 0, 0)
	Quad_SetSize(_game_.pQd_bk, dVIEW_W, dVIEW_H)
	Quad_SetCenter(_game_.pQd_bk, 0, 0)
	' Font
	_game_.pFnt_fnt = BmpFont_Create(dFNT_DEF, dFNT_TEX)
	' Score texts
	_game_.pTxt_score1 = BmpText_Create(_game_.pFnt_fnt, "0", 32, 0)
	BmpText_SetPos(_game_.pTxt_score1, 5, 24)
	BmpText_SetColorEx(_game_.pTxt_score1, dTEAM_1_COLOR)
	_game_.pTxt_score2 = BmpText_Create(_game_.pFnt_fnt, "0", 32, 0)
	BmpText_SetPos(_game_.pTxt_score2, dVIEW_W - 5, 24)
	BmpText_SetColorEx(_game_.pTxt_score2, dTEAM_2_COLOR)
	BmpText_SetAlign(_game_.pTxt_score2, ALIGN_RIGHT)
	_game_.iScore1 = 0
	_game_.iScore2 = 0
	' Debug text
	#ifdef dDRAW_DEBUG_INFO
	_game_.pTxt_debug = BmpText_Create(_game_.pFnt_fnt, "", 16, 1)
	BmpText_SetPos(_game_.pTxt_debug, 5, 48)
	#endif
	' Particles
	_game_.pPEmit_spawn = PEmitter_Create(_game_.pTex_parts, 0, 0, 0, 0)
		PEmitter_ReadCfg(_game_.pPEmit_spawn, dPRT_FILE, dPRT_SPAWN, 1)

	_game_.pPEmit_hit = PEmitter_Create(_game_.pTex_parts, 0, 0, 0, 0)
		PEmitter_ReadCfg(_game_.pPEmit_hit, dPRT_FILE, dPRT_HIT, 1)

	_game_.pPEmit_boomFire = PEmitter_Create(_game_.pTex_parts, 0, 0, 0, 0)
		PEmitter_ReadCfg(_game_.pPEmit_boomFire, dPRT_FILE, dPRT_BOOM_FIRE, 1)

	_game_.pPEmit_boomSmoke = PEmitter_Create(_game_.pTex_parts, 0, 0, 0, 0)
		PEmitter_ReadCfg(_game_.pPEmit_boomSmoke, dPRT_FILE, dPRT_BOOM_SMOKE, 1)

	_game_.pPEmit_engineDummy = PEmitter_Create(_game_.pTex_parts, 0, 0, 0, 0)
		PEmitter_ReadCfg(_game_.pPEmit_engineDummy, dPRT_FILE, dPRT_ENGINE, 1)
	'''
	' MultiSets
	_game_.pSetSpr_team1 = MultiSet_Create(SET_TYPE_SPRITE)
	_game_.pSetSpr_team2 = MultiSet_Create(SET_TYPE_SPRITE)
	' shots
	_game_.pSetSpr_shots = MultiSet_Create(SET_TYPE_SPRITE)
	' engines
	_game_.pSetEmit_engines = MultiSet_Create(SET_TYPE_PEMITTER)
	' explosions
	_game_.pSetSpr_explosions = MultiSet_Create(SET_TYPE_SPRITE)
	'''
	' Explosion animation
	_game_.pAnim_boom = Animation_Create(48)
	For y As UByte = 0 To 5
		For x As UByte = 0 To 7
			Animation_AddFrameEx(_game_.pAnim_boom, 0.015, _game_.pTex_anim_boom, x * 128, y * 128, 128, 128, YAGL_COLOR_WHITE, BLEND_ALPHA, 0, 128, 128)
		Next
	Next
End Sub

Sub Game_Clean ()
	' Animation
	Animation_Destroy(_game_.pAnim_boom)
	' MultiSets
	MultiSet_Iterate(_game_.pSetSpr_team1, Cast(YAGLMultiSetIterateProc, @SpriteCleanDataProc), Cast(Any Ptr, 1))
	MultiSet_Iterate(_game_.pSetSpr_team2, Cast(YAGLMultiSetIterateProc, @SpriteCleanDataProc), Cast(Any Ptr, 1))
	MultiSet_Iterate(_game_.pSetSpr_shots, Cast(YAGLMultiSetIterateProc, @SpriteCleanDataProc), Cast(Any Ptr, 0))
	
	MultiSet_Destroy(_game_.pSetSpr_team1, 1)
	MultiSet_Destroy(_game_.pSetSpr_team2, 1)
	MultiSet_Destroy(_game_.pSetSpr_shots, 1)
	MultiSet_Destroy(_game_.pSetEmit_engines, 1)
	MultiSet_Destroy(_game_.pSetSpr_explosions, 1)
	'''
	' Particles
	PEmitter_Destroy(_game_.pPEmit_spawn)
	PEmitter_Destroy(_game_.pPEmit_hit)
	PEmitter_Destroy(_game_.pPEmit_boomFire)
	PEmitter_Destroy(_game_.pPEmit_boomSmoke)
	PEmitter_Destroy(_game_.pPEmit_engineDummy)
	' Font
	BmpText_Destroy(_game_.pTxt_score1)
	BmpText_Destroy(_game_.pTxt_score2)
	BmpFont_Destroy(_game_.pFnt_fnt)
	' BK Quad
	Quad_Destroy(_game_.pQd_bk)
	' Textures
	Texture_Destroy(_game_.pTex_bk)
	Texture_Destroy(_game_.pTex_ship)
	Texture_Destroy(_game_.pTex_shot)
	Texture_Destroy(_game_.pTex_parts)
	Texture_Destroy(_game_.pTex_anim_boom)
End Sub

' -----------------------------------------------------------------------------

Sub CollisionProc cdecl (spr1 As Sprite Ptr, spr2 As Sprite Ptr)
	Dim As tShipData Ptr unit_data = 0
	Dim As tShotData Ptr shot_data = 0
	Dim As Single x, y
	' ---
	If MultiSet_Exists(_game_.pSetSpr_shots, spr1) Then ' if spr1 is a shot
		' decrease unit's health
		unit_data = Cast(tShipData Ptr, Sprite_GetAttachedData(spr2))
		unit_data->health = unit_data->health - dSHOT_DAMAGE
		' ---
		' impact effect
		Sprite_GetPos(spr1, @x, @y)
		PEmitter_SetPos(_game_.pPEmit_hit, x, y)
		PEmitter_Emitte(_game_.pPEmit_hit, dPRT_EMITTE_COUNT_HIT)
		' ---
		' set the shot to be killed
		shot_data = Cast(tShotData Ptr, Sprite_GetAttachedData(spr1))
		shot_data->kill_me = 1
		' ---
		' draw unit shape
		#ifdef dDRAW_COLL_SHAPE
		Sprite_DrawShape(spr2)
		#endif
	EndIf
	If MultiSet_Exists(_game_.pSetSpr_shots, spr2) Then ' if spr2 is a shot
		' decrease unit's health
		unit_data = Cast(tShipData Ptr, Sprite_GetAttachedData(spr1))
		unit_data->health = unit_data->health - dSHOT_DAMAGE
		' ---
		' impact effect
		Sprite_GetPos(spr2, @x, @y)
		PEmitter_SetPos(_game_.pPEmit_hit, x, y)
		PEmitter_Emitte(_game_.pPEmit_hit, dPRT_EMITTE_COUNT_HIT)
		' ---
		' set the shot to be killed
		shot_data = Cast(tShotData Ptr, Sprite_GetAttachedData(spr2))
		shot_data->kill_me = 1
		' ---
		' draw unit shape
		#ifdef dDRAW_COLL_SHAPE
		Sprite_DrawShape(spr1)
		#endif
	EndIf
End Sub

' function to deallocate Sprite's attached data structures
Function SpriteCleanDataProc cdecl (set As MultiSet Ptr, unit As Sprite Ptr, user_data As Any Ptr, rank As Integer, set_type As eSET_TYPE) As Integer
	Dim As Any Ptr attached_data = Sprite_GetAttachedData(unit)
	' No longer needed, engines will be cleaned in Game_Clean::MultiSet_Destroy(_game_.pSetEmit_engines, 1)
	'If user_data = 1 Then ' if it's a ship, then destroy the engines particles emitter (this is set in the clean function)
	'	PEmitter_Destroy(Cast(tShipData Ptr, attached_data)->engine)
	'EndIf
	Deallocate(attached_data) ' deallocate attached data, no matter if it's a unit or a shot
	Return 0
End Function

' Add score to a team
Sub ScoreUp (team As eTEAM)
	Select Case team
		Case team_1
			_game_.iScore1 += 1
			BmpText_SetText(_game_.pTxt_score1, Str(_game_.iScore1))
		Case team_2
			_game_.iScore2 += 1
			BmpText_SetText(_game_.pTxt_score2, Str(_game_.iScore2))
	End Select
End sub

#ifdef dDRAW_DEBUG_INFO
Sub UpdateDebug ()
	Dim As Integer total_spr, total_pemit, total_shots, total_explosions
	System_GetStats(0, 0, 0, @total_spr, 0, 0, @total_pemit, 0, 0, 0)
	total_shots = MultiSet_Count(_game_.pSetSpr_shots)
	total_shots = MultiSet_Count(_game_.pSetSpr_explosions)
	
	BmpText_SetText(_game_.pTxt_debug, "Spr: " + str(total_spr) + chr(10,13) + "PEmit: " + str(total_pemit) + chr(10,13) + "Shots: " + str(total_shots) + chr(10,13) + "Explo: " + str(total_explosions))
end Sub
#endif
