#include "yagl.bi"

Function iterate cdecl (ms As MultiSet Ptr, t As eSET_TYPE, elem As Any Ptr, rank As Integer, user_data As Any Ptr) As Integer
	Print "Type: "+ Str(t) +" - Elem: "+ Str(elem) +" - Rank: "+ Str(rank)
	Return 0
End Function

System_Init(DEBUG_OFF)

Dim As MultiSet Ptr ms = MultiSet_Create(SET_TYPE_ANY, 0)

MultiSet_Add(ms, 1, 10)
MultiSet_Add(ms, 2, 9)
MultiSet_Add(ms, 3, 8)
MultiSet_Add(ms, 4, 7)
MultiSet_Add(ms, 5, 6)
MultiSet_Add(ms, 6, 5)
MultiSet_Add(ms, 7, 4)
MultiSet_Add(ms, 8, 3)
MultiSet_Add(ms, 9, 2)
MultiSet_Add(ms, 10, 1)

Dim As Integer array(0 to 9)
MultiSet_GetAll(ms, @array(0), 5)
For i As Byte = 0 To 9
	Print array(i)
Next

MultiSet_Destroy(ms, 0)

System_Terminate()
Sleep
