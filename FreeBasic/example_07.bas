' Basic example
' This example shows how to setup YAGL, open a window, close it on Escape press (or on window close)
'
' How to handle collisions

#include "yagl.bi"

' First of all
System_Init(OFF)

' Create a 640x480, 24bits (8+8+8) render window
Window_Create(640, 480, 8, 8, 8, 0, "YAGL Example 07", 1, 0)

' We loop while the window is still opened, and we didn't pressed the escape key
While Window_IsOpened() And Not Events_GetKey(YAGL_KEY_ESC)
	' start render operations: this function clears the screen
	Render_Begin()

	' end render operations: this function validates the draws that occured befor it, and after Render_Begin
	Render_End()
WEnd

' Free all ressources
' including all objects created with AuGL (Sprites, Particle Emitters...). AuGL has a kind of garbage collector
System_Terminate()
