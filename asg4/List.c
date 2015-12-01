//Antony Robbins
//androbbi@ucsc.edu
//Assignment 2
#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------
// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// newList()
// Returns reference to new empty List object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}


// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}


// freeList()
// Frees all heap memory associated with List *pQ, and sets *pQ to NULL.S
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
	  if( length(*pL) > 0)
         clear(*pL);
      free(*pL);
      *pL = NULL;
   }
}
 
// Access functions -----------------------------------------------------------

// getFront()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L){
   if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   if( length(L) <= 0 ){
      printf("List Error: calling front() on an empty List\n");
      exit(1);
   }
   return(L->front->data);
}

// getLength()
// Returns the length of Q.
int length(List L){
   if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
   }
   return(L->length);
}
/*
// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L){
   if( L==NULL ){
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(1);
   }
   return(L->length==0);
}*/

// Manipulation procedures ----------------------------------------------------

// append()
// Places new data element at the end of L
void append(List L, int data)
{
   Node tmp = newNode(data);
   if( L==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }
   if( length(L) <= 0 ) { L->front = L->back = tmp; }
   else { tmp->prev = L->back; L->back->next = tmp; L->back = tmp; }
   L->length++;
}

// Returns the index of the cursor element in this list, or 
// returns -1 if the cursor element is undefined.
int getIndex(List L){
   if(L->cursor != NULL){
	  return L->index;
   }
   else
	  return -1;
}
   
// Returns back element in this List. Pre: length()>0
int back(List L){
   if(length(L) <0){
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   return L->back->data; 
}
   
// Returns cursor element in this list. 
// Pre: length()>0, getIndex()>=0
int getElement(List L) {
   if(length(L) <= 0 || getIndex(L) < 0){
      printf("List Error: calling getElement() on NULL List reference, or an index with -1\n");
      exit(1);
   }
   return L->cursor->data;
}

// Inserts new element before front element in this List. Index does increment
void prepend(List L, int data) {
   Node tmp = newNode(data);
   if(length(L) == 0){
      L->front = tmp;
      L->back= L->front;
   }
   else{
	  tmp->next = L->front;
      L->front->prev = tmp;
      L->front = tmp;
      if(L->cursor!= NULL) {L->index++;}
   }
	L->length++;
} 

// Pre: !this.isEmpty()
// Deletes the front element in this List. Pre: length()>0
void deleteFront(List L){
   Node tmp = NULL;
   if( L==NULL ){
      printf("List Error: calling deleteFront on NULL List reference\n");
      exit(1);
   }
   if( length(L) <= 0 ){
      printf("List Error: calling deleteFront on an empty List\n");
      exit(1);
   }
   if( length(L) == 1) {
      tmp = L->front;
      L->front = L->back = NULL;
	  freeNode(&tmp);
   }
   if( length(L)>1 ) {
      tmp = L->front;
      L->front = L->front->next;
	  L->front->prev = NULL;
	  freeNode(&tmp);
   }

   if (L->index == 0) {
      L->cursor = NULL;
	  L->index = -1;
   }
   if(L->cursor!=NULL) {L->index--;}
   L->length--;
}
   
// If 0<=i<=length()-1, moves the cursor to the element 
// at index i, otherwise the cursor becomes undefined.   
void moveTo(List L, int i) {
   Node tmp = NULL;
   if (i >= 0 && i <= length(L)-1) {
      tmp = L->front;
      for(int j = 0; j < i; j++) {
	     tmp = tmp->next;
	  }
      L->cursor = tmp;
      L->index = i;
   }
   else{
	  L->cursor = NULL;
	  L->index = -1;
   }		 
}
   
// If 0<getIndex()<=length()-1, moves the cursor one step toward the
// front of the list. If getIndex()==0, cursor becomes undefined. 
// If getIndex()==-1, cursor remains undefined. This operation is
// equivalent to moveTo(getIndex()-1).
void movePrev(List L) {
   if(0 < getIndex(L) && getIndex(L) <= length(L) -1) {
	  moveTo(L, getIndex(L)-1);
   }	 
   else if (getIndex(L) == 0 || getIndex(L) == -1){
      L->cursor = NULL;
	  L->index = -1;
   }
}

// If 0<=getIndex()<length()-1, moves the cursor one step toward the
// back of the list. If getIndex()==length()-1, cursor becomes
// undefined. If index==-1, cursor remains undefined. This
// operation is equivalent to moveTo(getIndex()+1).
void moveNext(List L) {
   if(0 <= getIndex(L) && getIndex(L) <= length(L) -1) {
	  moveTo(L, getIndex(L)+1);		 
   }	 
   else if (getIndex(L) == length(L)-1 || getIndex(L) == -1){
	  L->cursor = NULL;
	  L->index = -1;
   }
}  
   
// Inserts new element before cursor element in this
// List. Pre: length()>0, getIndex()>=0
void insertBefore(List L, int data) {
   if(length(L)>0 && getIndex(L) >= 0) {
	  Node in = newNode(data);
	  Node tmp = NULL;
      tmp = L->cursor->prev;
      tmp->next = in;
      L->cursor->prev = in;
      in->prev = tmp;
      in->next = L->cursor;
      L->index++;
      L->length++; 
   }
}
   
// Inserts new element after cursor element in this 
// List. Pre: length()>0, getIndex()>=0
void insertAfter(List L, int data) {
   if(length(L)>0 && getIndex(L) >= 0) {
	  Node in = newNode(data);
	  Node tmp = NULL;
      tmp = L->cursor->next;
      tmp->prev = in;
      L->cursor->next = in;
      in->prev = L->cursor;
      in->next = tmp;
      L->length++;
   }
}
   
// Re-sets this List to the empty state.
void clear(List L) {
   Node tmp = NULL;
   while(L->front != NULL){
	  tmp = L->front;
      L->front = L->front->next;
      freeNode(&tmp);
   }
   freeNode(&tmp);
   L->length = 0;
   L->index = -1;
}
   
// Deletes the back element in this List. Pre: length()>0
void deleteBack(List L) {
   if(length(L) > 0){
      Node tmp = NULL;
	  tmp = L->back;
	  L->back = L->back->prev;
	  L->length--;
	  freeNode(&tmp);
	  if(L->index == length(L) -1) {L->cursor = NULL; L->index = -1;}
   }
}

// Deletes cursor element in this List. Cursor is undefined after this 
// operation. Pre: length()>0, getIndex()>=0
void delete(List L) {
   if(length(L) > 0 && getIndex(L)>=0){
      Node tmp = NULL;
	  Node left = NULL;
	  Node right = NULL;
      tmp = L->cursor;
      left = tmp->prev;
      right = tmp->next;
      left->next = right;
      right->prev = left;
      L->cursor = NULL;
	  freeNode(&tmp);
      L->index = -1;
	  L->length--;
   }
   //else 
	 // throw new RuntimeException("List Error: delete() when cursor is null");
}

// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L){
   Node curr = NULL;

   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }
   for(curr = L->front; curr != NULL; curr = curr->next){
      fprintf(out, "%d ", curr->data);
   }
   //printf("\n");
}

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B){
   int flag = 1;
   Node N = NULL;
   Node M = NULL;

   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }
   N = A->front;
   M = B->front;
   if( A->length != B->length ) { return 0; }
   while( flag && N!=NULL){
      flag = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return flag;
}

// copy(): returns a new List identical to this one.
// Returns a new list representing the same integer sequence as this
// list. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
   List copyList(List L){
      List M = newList();
      Node N = L->front;

      while( N!=NULL ){
         append(M, N->data);
         N = N->next;
      }
      return M;
   }
