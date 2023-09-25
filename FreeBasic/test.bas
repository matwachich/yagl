#include once "yagl.bi"
#include once "yagl_class.bi"

Sub Custom_Debug_Proc cdecl (text As ZString, err_lvl As Integer)
	Print "> " + text
End Sub

System_Init(DEBUG_OFF)
System_SetDebugCallback(Cast(YAGLDebugProc, @Custom_Debug_Proc))

Window_Create(1024, 600, 8, 8, 8, 0, "Matwachich!", 0, 0)

Dim tex_bk As cTexture = cTexture("data\spacefield.png")
Dim tex_parts As cTexture = cTexture("data\particles.png")

Dim spr_bk As cSprite = cSprite(tex_bk)
spr_bk.SetCenterEx(CENTER_CENTER)
spr_bk.SetSize(1024, 600)
spr_bk.SetPos(1024/2, 600/2)

Dim parts_1 As cPEmitter = cPEmitter(tex_parts)
PEmitter_ReadCfg(parts_1, "data\particles.ini", "fire", 1)
parts_1.SetPos(1024/4, (600/3)*2)
parts_1.Active = 1

Dim parts_2 As cPEmitter = cPEmitter()
parts_2 = parts_1
parts_2.SetPos((1024/4)*3, (600/3)*2)
parts_2.Active = 1

While Window_IsOpened()
	Render_Begin()
	spr_bk.Draw()
	parts_1.Draw()
	parts_2.Draw()
	Render_End()
WEnd

parts_2.Free()
parts_1.Free()
spr_bk.Free()
tex_bk.Free()
tex_parts.Free()

System_Terminate()
