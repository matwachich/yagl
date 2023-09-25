' Basic example
' This example shows how to setup AuGL, open a window, close it on Escape press (or on window close)

#include "yagl.bi"

' First of all
System_Init(ON_STD)

' Create a 640x480, 24bits (8+8+8) render window
Window_Create(640, 480, 8, 8, 8, 0, "YAGL Example - Shaders", 1, 0)

' Initiate Shaders
If Shader_Init(0) = 0 Then Print "Shaders not supported"
Shader_SetInfoLogShow(1)

' Create a Shader program
Dim As Shader Ptr shd = Shader_Create()

' Add shaders source codes
'Dim vert_src As String = "void main(void){gl_Position = ftransform();gl_FrontColor = gl_Color;}"
'Dim frag_src As String = "void main(void){gl_FragColor = gl_Color;}"

Print "Vert: " + str(Shader_AddSourceFile(shd, "data/vert.txt", VERTEX))
Print "Frag: " + str(Shader_AddSourceFile(shd, "data/frag.txt", FRAGMENT))

' Link and use
If Shader_Link(shd) Then
	Print "Link OK"
Else
	Print "Link Failed"
End If

Shader_Use(shd)

Draw_SetParams(YAGL_RGBA(255, 255, 255, 255), BLEND_ALPHA, 1, 0)

' We loop while the window is still opened, and we didn't pressed the escape key
While Window_IsOpened() And Not Events_KeyGet(YAGL_KEY_ESC)
	' start render operations: this function clears the screen
	Render_Begin()

	Draw_Line(100, 100, 540, 380)

	' end render operations: this function validates the draws that occured befor it, and after Render_Begin
	Render_End()
WEnd

Shader_Destroy(shd)

' Free all ressources
' including all objects created with AuGL (Sprites, Particle Emitters...). AuGL has a kind of garbage collector
System_Terminate()
Sleep
