' Basic example
' This example shows how to setup YAGL, open a window
' Sprite dynamics (velocity, acceleration, innertia...)
'
' Use ZQSD to move around (for other keyboards than AZERTY, change the keys here (***)

#include "yagl.bi"

' First of all
System_Init(OFF)

' Create a 640x480, 24bits (8+8+8) render window
Window_Create(640, 480, 8, 8, 8, 0, "YAGL Example 04", 1, 0)

' Load the spaceship texture
Dim my_tex As Texture Ptr = Texture_Create("data\spaceship.png", 0)

' Create the spaceship Sprite and position it in the middle of the window
Dim my_spr As Sprite Ptr = Sprite_Create(my_tex, 0, 0, 0, 0)
Sprite_SetSize(my_spr, 100, 50)
Sprite_SetPos(my_spr, 320, 240)

' We set some dynamic vars
'Sprite_SetVelMax(my_spr, 100)
Sprite_SetInnertia(my_spr, 50) ' speed loose when no acceleration applied = 50 pixels/s²

Sprite_SetAVelMax(my_spr, 60) ' max rotation speed = 60°/s
Sprite_SetAInnertia(my_spr, 180) ' rotation speed loose when no angular acceleration applied = 180°/s²

' (***)
' Use Capitals
Dim asc_forward As Integer = Asc("Z")
Dim asc_backward As Integer = Asc("S")
Dim asc_left As Integer = Asc("Q")
Dim asc_right As Integer = Asc("D")

' We loop while the window is still opened, and we didn't pressed the escape key
While Window_IsOpened() And Not Events_KeyGet(YAGL_KEY_ESC)

	' Forward/Backward movements
	If Events_KeyGet(asc_forward) Then
		Sprite_SetVelMax(my_spr, 100) ' when moving forward, max speed = 100 pixels/sec
		' We set the acceleration vector lenght to 500
		Sprite_SetAccelLen(my_spr, 500)

	ElseIf Events_KeyGet(asc_backward) Then
		Sprite_SetVelMax(my_spr, 50) ' when moving backward, max speed = 50 pixels/sec
		' We set the acceleration vector lenght to -500
		Sprite_SetAccelLen(my_spr, -500)

	Else
		' No acceleration, like the engines are down, and the ship will stop slowly with it's innertia
		Sprite_SetAccelLen(my_spr, 0)
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
		Sprite_SetAAccel(my_spr, 500)

	ElseIf Events_KeyGet(asc_left) Then
		' rotate counter clock-wise
		Sprite_SetAAccel(my_spr, -500)

	Else
		Sprite_SetAAccel(my_spr, 0)
	End If

	' start render operations: this function clears the screen
	Render_Begin()
	' Draw the sprite
	Sprite_Draw(my_spr)
	' end render operations: this function validates the draws that occured befor it, and after Render_Begin
	Render_End()
WEnd

Sprite_Destroy(my_spr)
Texture_Destroy(my_tex)

' Free all ressources
' including all objects created with AuGL (Sprites, Particle Emitters...). AuGL has a kind of garbage collector
System_Terminate()
