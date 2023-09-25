' Basic example
' This example shows how to setup YAGL, open a window
' Sprite dynamics (velocity, acceleration, innertia...) (Exactly the same as example_04)
' and SpriteSet (used to store shoots) (Exactlye the same as example_05)
' and Particle Emitters (ship engin, explosion)
'
' Use ZQSD to move around (for other keyboards than AZERTY, change the keys here (***)
' Clique to shoot

#include "yagl.bi"

Declare Sub shot (ship_spr As Sprite Ptr, tex As Texture Ptr, spr_set As SpriteSet Ptr)
Declare Function iterate cdecl (spr_set As SpriteSet Ptr, spr As Sprite Ptr) As Integer

' Let's define a data structure that will be attached to every shot projectil
Type tShotData
	As Double life_timer ' This var will contain the shot spawn timestamp, in order to calculate the moment when the shot should be killed
End Type

' First of all
System_Init(OFF)

' Create a 640x480, 24bits (8+8+8) render window
Window_Create(640, 480, 8, 8, 8, 0, "YAGL Example 06", 1, 0)

' Load the spaceship texture
Dim pTex_spaceship As Texture Ptr = Texture_Create("data\spaceship.png", 0)
' And the particles texture, from where we will get the picture for the shot
Dim pTex_particles As Texture Ptr = Texture_Create("data\particles.png", 0)

' Create the spaceship Sprite and position it in the middle of the window
Dim pSpr_spaceship As Sprite Ptr = Sprite_Create(pTex_spaceship, 0, 0, 0, 0)
Sprite_SetSize(pSpr_spaceship, 100, 50)
Sprite_SetPos(pSpr_spaceship, 320, 240)

'Sprite_SetFlip(pSpr_spaceship, 1, 0)

' We set some dynamic vars
'Sprite_SetVelMax(pSpr_spaceship, 100)
Sprite_SetInnertia(pSpr_spaceship, 50) ' speed loose when no acceleration applied = 50 pixels/s²

Sprite_SetAVelMax(pSpr_spaceship, 60) ' max rotation speed = 60°/s
Sprite_SetAInnertia(pSpr_spaceship, 180) ' rotation speed loose when no angular acceleration applied = 180°/s²

' We create a SpriteSet that will store all the shots
Dim pSprSet_shots As SpriteSet Ptr = SpriteSet_Create()

' We create a particles emitter for the shots explosions, and load it's configuration
Dim Shared pEmit_impact As PEmitter Ptr
pEmit_impact = PEmitter_Create(pTex_particles, 0, 0, 0, 0)
PEmitter_ReadCfg(pEmit_impact, "data\particles.ini", "impact", 1)

' By default, a particle emitter is not active, means it will not automatically emit particles unless told so
' either by PEmitter_Emitte or by setting it active (PEmitter_SetActive) so it will emitte without stoping
' In this example, the particles emission is done in the iterate functions (when a projectil is "dead")

' Let's create another 2 particle emitter for the ship engines
Dim Shared pEmit_engine_1 As PEmitter Ptr
Dim Shared pEmit_engine_2 As PEmitter Ptr
pEmit_engine_1 = PEmitter_Create(pTex_particles, 0, 0, 0, 0)
pEmit_engine_2 = PEmitter_Create(pTex_particles, 0, 0, 0, 0)
PEmitter_ReadCfg(pEmit_engine_1, "data\particles.ini", "engine", 1)
PEmitter_ReadCfg(pEmit_engine_2, "data\particles.ini", "engine", 1)

' We need some more vars for the shot ability
Const shots_per_sec As Single = 10.0 ' fire rate (shots/sec)
Const shot_life As Single = 1.0 ' shot life time in seconds
Const shot_speed = 300 ' projectil speed (in pixels/s)

' Do not modify, or do it if you want :p
Dim shot_delay As Double = 1 / shots_per_sec ' delay between shots
Dim shot_timer As Double = Misc_TimerInit() ' timer used to shot

' (***)
' Use Capitals
Dim asc_forward As Integer = Asc("Z")
Dim asc_backward As Integer = Asc("S")
Dim asc_left As Integer = Asc("Q")
Dim asc_right As Integer = Asc("D")


Dim As Single player_engine_x, player_engine_y

' We loop while the window is still opened, and we didn't pressed the escape key
While Window_IsOpened() And Not Events_KeyGet(YAGL_KEY_ESC)

	' Forward/Backward movements
	If Events_KeyGet(asc_forward) Then
		Sprite_SetVelMax(pSpr_spaceship, 100) ' when moving forward, max speed = 100 pixels/sec
		' We set the acceleration vector lenght to 500
		Sprite_SetAccelLen(pSpr_spaceship, 500)

		' position the engines particle emitters at the back of the sprite, and activate them
		Sprite_SpriteToWorldEx(pSpr_spaceship, 0, 0.344, @player_engine_x, @player_engine_y)
		PEmitter_SetPos(pEmit_engine_1, player_engine_x, player_engine_y)
		PEmitter_SetActive(pEmit_engine_1, 1)

		Sprite_SpriteToWorldEx(pSpr_spaceship, 0, 0.647, @player_engine_x, @player_engine_y)
		PEmitter_SetPos(pEmit_engine_2, player_engine_x, player_engine_y)
		PEmitter_SetActive(pEmit_engine_2, 1)

	ElseIf Events_KeyGet(asc_backward) Then
		Sprite_SetVelMax(pSpr_spaceship, 50) ' when moving backward, max speed = 50 pixels/sec
		' We set the acceleration vector lenght to -500
		Sprite_SetAccelLen(pSpr_spaceship, -500)

	Else
		' No acceleration, like the engines are down, and the ship will stop slowly with it's innertia
		Sprite_SetAccelLen(pSpr_spaceship, 0)

		' Deactivate the engines particles emitter
		PEmitter_SetActive(pEmit_engine_1, 0)
		PEmitter_SetActive(pEmit_engine_2, 0)
	End If

	' Note:
	' Remember that you can set Velocity and Acceleration in several ways
	'	- By setting the vector's cartesian coordinates: Sprite_Set[Vel/Accel] (sprite, vect_x, vect_y)
	'	- By setting the vector's polar coordinates: Sprite_Set[Vel/Accel]Ex (sprite, len, angle)
	'	- By setting vector's lenght, without changin it's angle: Sprite_Set[Vel/Accel]Len (sprite, len)
	'	- By setting vector's angle, without changin it's lenght: Sprite_Set[Vel/Accel]Angle (sprite, angle)
	' Each of these functions have alse getters (Sprite_Get[Vel/Accel], Sprite_Get[Vel/Accel]Ex ...)

	' Rotation movements. It's the same than above, just remember that you go clock-wise with positive values
	If Events_KeyGet(asc_right) Then
		' rotate clock-wise
		Sprite_SetAAccel(pSpr_spaceship, 500)

	ElseIf Events_KeyGet(asc_left) Then
		' rotate counter clock-wise
		Sprite_SetAAccel(pSpr_spaceship, -500)

	Else
		Sprite_SetAAccel(pSpr_spaceship, 0)
	End If

	' Shot detection
	If Events_MouseGetButton(YAGL_MOUSE_BUTTON_LEFT) And Misc_TimerDiff(shot_timer) >= shot_delay Then
		shot(pSpr_spaceship, pTex_particles, pSprSet_shots)
		shot_timer = Misc_TimerInit()
	End If

	' We now iterate through every sprite in the shots SpriteSet to check every shot if it should be deleted
	SpriteSet_Iterate(pSprSet_shots, Cast(YAGLSpriteSetIterateProc, @iterate))

	' start render operations: this function clears the screen
	Render_Begin()
	' Draw the shots befor the ship's sprite
	SpriteSet_Draw(pSprSet_shots)
	Sprite_Draw(pSpr_spaceship)
	' Draw the 2 Particles Emitters
	PEmitter_Draw(pEmit_engine_1)
	PEmitter_Draw(pEmit_engine_2)
	PEmitter_Draw(pEmit_impact)
	' end render operations: this function validates the draws that occured befor it, and after Render_Begin
	Render_End()
WEnd

PEmitter_Destroy(pEmit_impact)
PEmitter_Destroy(pEmit_engine_1)
PEmitter_Destroy(pEmit_engine_2)
SpriteSet_Destroy(pSprSet_shots, 1)
Sprite_Destroy(pSpr_spaceship)
Texture_Destroy(pTex_spaceship)

' Free all ressources
' including all objects created with AuGL (Sprites, Particle Emitters...). AuGL has a kind of garbage collector
System_Terminate()

' This procedure will create a projectil, place it, and add it to the sprite set
Sub shot (ship_spr As Sprite Ptr, tex As Texture Ptr, spr_set As SpriteSet Ptr)
	' We create the shot sprite
	Dim shot_spr As Sprite Ptr = Sprite_Create(tex, 96, 0, 32, 32)

	' We position the shot
	Dim As Single x, y
	Sprite_GetPos(ship_spr, @x, @y)
	Sprite_SetPos(shot_spr, x, y)

	' We set shot's velocity
	Dim As Single angle
	angle = Sprite_GetAngle(ship_spr)
	Sprite_SetVelEx(shot_spr, shot_speed, angle)

	' Add some rotation to the shot
	Sprite_SetAVel(shot_spr, Misc_RandomF(-500.0, 500.0))

	' Attache some data to the sprite
	Dim data_ As tShotData Ptr = Allocate(SizeOf(tShotData))
	data_->life_timer = Misc_TimerInit() ' the creation timestamp
	Sprite_SetAttachedData(shot_spr, data_)

	' Add it to the SpriteSet
	SpriteSet_Add(spr_set, shot_spr)
End Sub

' This function is called by the SpriteSet_Iterate function for every sprite (spr) contained in the sprite set (spr_set)
Function iterate cdecl (spr_set As SpriteSet Ptr, spr As Sprite Ptr) As Integer
	' We get the data structure attached to the sprite
	Dim data_ As tShotData Ptr = Cast(tShotData Ptr, Sprite_GetAttachedData(spr))

	' We check the life_timer of the sprite
	If Misc_TimerDiff(data_->life_timer) > shot_life Then
		' If the sprite should be deleted, we don't forget to Deallicate the data structure attached to it
		Deallocate(data_)
		' Position the impact particle emitter at the position of the projectil, and emit 10 particles
		Dim As Single x, y
		Sprite_GetPos(spr, @x, @y)
		PEmitter_SetPos(pEmit_impact, x, y)
		PEmitter_Emitte(pEmit_impact, 10)
		' Means: Delete the sprite from the SpriteSet, and Destroy it (Sprite_Destroy will be called on it)
		Return 2
	Else
		Return 0 ' Means: Do nothing (0 or any other value than 1 or 2)
	End If
	' PS: you can also return 1 to delete the sprite from the sprite set without destroying it
End Function
