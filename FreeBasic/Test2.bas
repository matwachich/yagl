#include "yagl.bi"
#include "yagl_class.bi"

' From 1 to 16
Dim As Integer num
Input "Particle number (1 to 16)"; num
If num <> Int(num) Or num > 16 Or num < 1 Then End -1

System_Init(DEBUG_ON_STD)

Window_Create(640, 480, 8, 8, 8, 0, "Test", 0, 0)

Dim tex_map As cTextureMap = cTextureMap("data\particles.png")
For i As Integer = 0 To 3
	For j As Integer = 0 To 3
		tex_map.AddRect(j * 32, i * 32, 32, 32)
	Next j
Next i

Dim spr As cSprite = cSprite()
spr.SetTextureMap(tex_map, num)

spr.SetPos(320, 240)

While Window_IsOpened() And Not Events_KeyGet(YAGL_KEY_ESC)
	Render_Begin()
	spr.Draw()
	Draw_Line(0, 0, 320, 240)
	Render_End()
WEnd

spr.Free()
tex_map.Free()

System_Terminate()
