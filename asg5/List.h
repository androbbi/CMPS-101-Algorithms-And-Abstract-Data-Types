//Antony Robbins
//androbbi@ucsc.edu
//Assignment 5
//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_


// Exported type --------------------------------------------------------------
typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object. 
List newList(void);

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL);


// Access functions -----------------------------------------------------------

// getFront()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L);

// getLength()
// Returns the length of L.
int length(List L);

// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L);


// Manipulation procedures ----------------------------------------------------

// append()
// Places new data element at the end of L
void append(List L, int data);

// deleteFront(List L)
// Deletes element at front of L
// Pre: !isEmpty(L)
void deleteFront(List L);

// Returns the index of the cursor element in this list, or 
// returns -1 if the cursor element is undefined.
int getIndex(List L);

// Returns back element in this List. Pre: length()>0
int back(List L);

// Returns cursor element in this list. 
// Pre: length()>0, getIndex()>=0
int getElement(List L);

// Inserts new element before front element in this List. Index does increment
void prepend(List L, int data);

// Pre: !this.isEmpty()
// Deletes the front element in this List. Pre: length()>0
void deleteFront(List L);

// If 0<=i<=length()-1, moves the cursor to the element 
// at index i, otherwise the cursor becomes undefined.   
void moveTo(List L, int i);

// If 0<getIndex()<=length()-1, moves the cursor one step toward the
// front of the list. If getIndex()==0, cursor becomes undefined. 
// If getIndex()==-1, cursor remains undefined. This operation is
// equivalent to moveTo(getIndex()-1).
void movePrev(List L);

// If 0<=getIndex()<length()-1, moves the cursor one step toward the
// back of the list. If getIndex()==length()-1, cursor becomes
// undefined. If index==-1, cursor remains undefined. This
// operation is equivalent to moveTo(getIndex()+1).
void moveNext(List L);

// Inserts new element before cursor element in this
// List. Pre: length()>0, getIndex()>=0
void insertBefore(List L, int data);

// Inserts new element after cursor element in this 
// List. Pre: length()>0, getIndex()>=0
void insertAfter(List L, int data);

// Re-sets this List to the empty state.
void clear(List L);

// Deletes the back element in this List. Pre: length()>0
void deleteBack(List L);

// Deletes cursor element in this List. Cursor is undefined after this 
// operation. Pre: length()>0, getIndex()>=0
void delete(List L);

// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L);

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B);

// copy(): returns a new List identical to this one.
// Returns a new list representing the same integer sequence as this
// list. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L);

#endif