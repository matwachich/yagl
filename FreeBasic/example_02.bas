' Basic example
' This example shows how to setup YAGL, open a window, and simply display a picture file (a Texture)

#include "yagl.bi"

' First of all
System_Init(OFF)

' Create a 640x400, 24bits (8+8+8) render window
Window_Create(640, 400, 8, 8, 8, 0, "YAGL Example 02", 1, 0)

' We load a picture file into a Texture object
Dim my_tex As Texture Ptr = Texture_Create("data\logo.png", 0)

' We cannot display a texture directly, so we create a Sprite object to do so
' Since we don't select any Texture Rectagle to assign to the Sprite, the Sprite will
'  be assigned the entire texture, and it will be resized to the texture's size
Dim my_quad As Quad Ptr = Quad_Create(my_tex, 0, 0, 0, 0)

' By default, a Sprite's center is in the middle.
' So we position the sprite in the center of the screen
Quad_SetPos(my_quad, 320, 200)

' We loop while the window is still opened, and we didn't pressed the escape key
While Window_IsOpened() And Not Events_KeyGet(YAGL_KEY_ESC)
	' start render operations: this function clears the screen
	Render_Begin()

	' Let's draw our sprite
	Quad_Draw(my_quad)

	' end render operations: this function validates the draws that occured befor it, and after Render_Begin
	Render_End()
WEnd

' Event with the garbage collector, it is still a good idea to do this
Quad_Destroy(my_quad)
Texture_Destroy(my_tex)

' Free all ressources
' including all objects created with AuGL (Sprites, Particle Emitters...). AuGL has a kind of garbage collector
System_Terminate()
Sleep
