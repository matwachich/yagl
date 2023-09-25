#ifndef __SET_H__
#define __SET_H__

#include <stdio.h>
#include <stdlib.h>

#ifndef SET_DATA_TYPE
	#define SET_DATA_TYPE int
#endif

/* ------------------------------------------------------------------------- */

/* Those types are internals, do not use them manualy */
typedef struct Element Element;
struct Element {
	SET_DATA_TYPE data;
	Element* next;
};

typedef struct Set Set;
struct Set {
	Element* first;
	int size;
};

typedef struct Cursor Cursor;
struct Cursor {
	Set* parent_set;
	Element* current;
};

/* ------------------------------------------------------------------------- */

Set*	Set_Create ();
void	Set_Destroy (Set* set);
int		Set_Add (Set* set, SET_DATA_TYPE data);
int		Set_GetArray (Set* set, SET_DATA_TYPE** array);
int		Set_Del (Set* set, SET_DATA_TYPE data);
void	Set_Empty (Set* set);
int		Set_Size (Set* set);

Cursor*	Cursor_Create (Set* set);
void	Cursor_Destroy (Cursor* cursor);
SET_DATA_TYPE
		Cursor_Get (Cursor* cursor);
int		Cursor_Advance (Cursor* cursor);
void	Cursor_Rewind (Cursor* cursor);

/* ------------------------------------------------------------------------- */

#endif // __SET_H__
