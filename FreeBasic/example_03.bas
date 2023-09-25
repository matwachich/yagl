' Basic example
' This example shows how to setup YAGL, open a window
' and advanced sprite and texture handling (Texture rect)

#include "yagl.bi"

' First of all
System_Init(OFF)

' Create a 640x480, 24bits (8+8+8) render window
Window_Create(640, 480, 8, 8, 8, 0, "YAGL Example 03", 1, 0)

' We load a picture file into a Texture object
Dim my_tex As Texture Ptr = Texture_Create("data\logo.png", 0)

' We create a Sprite, but we want this time to draw only a part of the texture
' We can do this by specifiying a texture rect when creating our sprite (or after, using the function Sprite_SetTextureRect)
' A Texture Rect is specified by set it's upper-left corner, and it's size
' If we want to display the gamepad, we must set the upper-left corner of our texture rect to (x,y) = (317,178)
'  and the size to (w,h) = (265,205)
Dim my_spr As Sprite Ptr = Sprite_Create(my_tex, 317, 178, 265, 205)

' This time, Sprite will be sized not to the texture's size, but to the specified texture rect size (320,400)
' And it's center will always be in it's middle

' Let's position our sprite in the center of the window
Sprite_SetPos(my_spr, 320, 240)

' We loop while the window is still opened, and we didn't pressed the escape key
While Window_IsOpened() And Not Events_KeyGet(YAGL_KEY_ESC)
	' start render operations: this function clears the screen
	Render_Begin()

	' Draw sprite
	Sprite_Draw(my_spr)

	' end render operations: this function validates the draws that occured befor it, and after Render_Begin
	Render_End()
WEnd

Sprite_Destroy(my_spr)
Texture_Destroy(my_tex)

' Free all ressources
' including all objects created with AuGL (Sprites, Particle Emitters...). AuGL has a kind of garbage collector
System_Terminate()
