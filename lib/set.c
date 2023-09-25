#include <stdio.h>
#include <stdlib.h>

#include "set.h"

/* ------------------------------------------------------------------------- */

// Create a Set
Set*	Set_Create ()
{
	Set* set = (Set*)malloc(sizeof(Set));
	if (set == NULL) { return NULL; }
	// ---
	set->first = NULL;
	set->size = 0;
	return set;
}

// Destroy a Set, and all contained values
void	Set_Destroy (Set* set)
{
	Set_Empty(set);
	free(set);
}

// Add a value in a Set
int		Set_Add (Set* set, SET_DATA_TYPE data)
{
	Element* elem = (Element*)malloc(sizeof(Element));
	if (elem == NULL) { return -1; }
	// ---
	Set_Del(set, data);
	// ---
	elem->data = data;
	elem->next = set->first;
	set->first = elem;
	set->size++;
	return set->size;
}

// Get all values stored in a Set
int		Set_GetArray (Set* set, SET_DATA_TYPE** array)
{
	if (set->size == 0 || set->first == 0) { return 0; }
	// ---
	if (*array == NULL) {
        *array = (SET_DATA_TYPE*)malloc(set->size * sizeof(SET_DATA_TYPE));
	} else {
        *array = (SET_DATA_TYPE*)realloc(*array, set->size * sizeof(SET_DATA_TYPE));
	}
	if (*array == NULL) { return -1; }
	// ---
	Element* current = set->first;
	int i = 0;
	do {
		(*array)[i] = current->data;
		current = current->next;
		i++;
	} while (current != NULL);
	return set->size;
}

// Delete a value from a Set
int		Set_Del (Set* set, SET_DATA_TYPE data)
{
	if (set->size == 0 || set->first == NULL) { return 0; }
	// ---
	Element* current = set->first;
	Element* befor = NULL;
	do {
		if (current->data == data) {
			if (befor == NULL) {
				set->first = current->next;
			} else {
				befor->next = current->next;
			}
			free(current);
			set->size--;
			return set->size;
		}
		// ---
		befor = current;
		current = current->next;
	} while (current != NULL);
	return -1;
}

// Delete all values from a Set
void	Set_Empty (Set* set)
{
	if (set->size == 0 || set->first == NULL) { return; }
	// ---
	Element* current = set->first;
	Element* tmp = NULL;
	do {
		tmp = current->next;
		free(current);
		current = tmp;
	} while (current != NULL);
	set->size = 0;
	set->first = NULL;
}

// Get the size (stored values count) of a Set
int		Set_Size (Set* set)
{
	return set->size;
}

/* ------------------------------------------------------------------------- */

// Create a Cursor for a Set
Cursor*	Cursor_Create (Set* set)
{
	Cursor* cursor = (Cursor*)malloc(sizeof(Cursor));
	if (cursor == NULL) { return NULL; }
	// ---
	cursor->parent_set = set;
	cursor->current = set->first;
	return cursor;
}

// Destroy a Cursor
void	Cursor_Destroy (Cursor* cursor)
{
	free(cursor);
}

// Get the actual value pointed by a Cursor
// or 0 if the Set is empty, or the en of the Set is reached by the Cursor
SET_DATA_TYPE
		Cursor_Get (Cursor* cursor)
{
	if (cursor->current == NULL) { return 0; } // Either empty set, or the cursor reached the end (must call Cursor_Rewind)
	// ---
	return cursor->current->data;
}

// Advance the cursor position by on Value
// Return 0 if the Set is empty, or the en of the Set is reached by the Cursor
int		Cursor_Advance (Cursor* cursor)
{
	if (cursor->current == NULL) { return 0; } // Either empty set, or the cursor reached the end (must call Cursor_Rewind)
	// ---
	cursor->current = cursor->current->next;
	if (cursor->current != 0) {
		return 1;
	} else {
		return 0;
	}
}

// Rewind a Cursor to the begining of a Set
// MUST call this function after every operation (Add, Del, Empty) on the Set
void	Cursor_Rewind (Cursor* cursor)
{
	cursor->current = cursor->parent_set->first;
}

/* ------------------------------------------------------------------------- */
