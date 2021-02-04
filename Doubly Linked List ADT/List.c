//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj
{
   LIST_ELEMENT data;
   struct NodeObj *next;
   struct NodeObj *prev;
} NodeObj;

// private Node type
typedef NodeObj *Node;

// private ListObj type
typedef struct ListObj
{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(LIST_ELEMENT data)
{
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return (N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node *pN)
{
   if (pN != NULL && *pN != NULL)
   {

      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList()
{
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = NULL;
   L->cursor = NULL;
   L->length = 0;
   L->index = UNDEFINED;
   return (L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List *pL)
{
   if (pL != NULL && *pL != NULL)
   {
      while (!isEmpty(*pL))
      {
         deleteFront(*pL);
      }

      free(*pL);
      *pL = NULL;
   }
}

// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L)
{
   if (L == NULL)
   {
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return (L->length);
}
// index()
// Returns the current cursor position in L.
int index(List L)
{
   if (L->cursor == NULL || L->index == UNDEFINED)
   {
      return UNDEFINED;
   }
   return L->index;
}

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L)
{
   if (L == NULL)
   {
      printf("List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (isEmpty(L))
   {
      printf("List Error: calling front() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return (L->front->data);
}

// back()
// Returns the value at the back of L.
// Pre: !isEmpty(L)
int back(List L)
{
   if (L == NULL)
   {
      printf("List Error: calling back() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (isEmpty(L))
   {
      printf("List Error: calling back() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return (L->back->data);
}

// get()
// Returns cursor element
int get(List L)
{
   if (L == NULL)
   {
      printf("List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (isEmpty(L))
   {
      printf("List Error: calling get() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if (L->cursor == NULL || L->index == UNDEFINED)
   {
      printf("List Error: calling get() on Undefined cursor\n");
      exit(EXIT_FAILURE);
   }

   return (L->cursor->data);
}

// equals()
// Returns true (1) if A is same int sequence as B, false (0) otherwise.
int listequals(List A, List B)
{
   int eq = 0;
   Node N = NULL;
   Node M = NULL;

   if (A == NULL || B == NULL)
   {
      printf("List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   eq = (A->length == B->length);
   N = A->front;
   M = B->front;
   while (eq && N != NULL)
   {
      eq = (N->data == M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}

// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L)
{
   if (L == NULL)
   {
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return (L->length == 0);
}

// Manipulation procedures ----------------------------------------------------

// Resets list to empty state
void clear(List L)
{
   while (L->length > 0)
   {
      deleteFront(L);
   }
}

// Moves the cursor to the front of the list
void moveFront(List L)
{
   if (L == NULL)
   {
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (!isEmpty(L))
   {
      L->cursor = L->front;
      L->index = 0;
   }
}

// Moves the cursor to the back of the list
void moveBack(List L)
{
   if (L == NULL)
   {
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (!isEmpty(L))
   {
      L->cursor = L->back;
      L->index = L->length - 1;
   }
}

// Moves the cursor to the previous position
void movePrev(List L)
{
   if (L->index != UNDEFINED && L->cursor->prev != NULL)
   {
      L->cursor = L->cursor->prev;
      L->index--;
   }
   else if (L->index != UNDEFINED && L->cursor->prev == NULL)
   {
      L->cursor = NULL;
      L->index = UNDEFINED;
   }
}

// Moves the cursor to the next position
void moveNext(List L)
{
   if (L->index != UNDEFINED && L->cursor->next != NULL)
   {
      L->cursor = L->cursor->next;
      L->index++;
   }
   else if (L->index != UNDEFINED && L->cursor->next == NULL)
   {
      L->cursor = NULL;
      L->index = UNDEFINED;
   }
}

// append()
// Places new data at the back of L.
void append(List L, LIST_ELEMENT data)
{

   Node N = newNode(data);
   if (L == NULL)
   {
      printf("List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (isEmpty(L))
   {
      L->front = L->back = N;
   }
   else
   {
      L->back->next = N;
      N->prev = L->back;
      L->back = N;
   }
   L->length++;
}

// prepend()
// Places new data at the beginning of the list
void prepend(List L, LIST_ELEMENT data)
{
   Node N = newNode(data);

   if (L == NULL)
   {
      printf("List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (isEmpty(L))
   {
      L->front = L->back = N;
   }
   else
   {
      N->next = L->front;
      L->front->prev = N;
      L->front = N;
   }
   if (L->index != UNDEFINED)
   {
      L->index++;
   }
   L->length++;
}

// insertBefore()
// Places new data before the cursor
void insertBefore(List L, LIST_ELEMENT data)
{
   Node N = newNode(data);

   if (L == NULL)
   {
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (isEmpty(L))
   {
      printf("List Error: calling insertBefore() on empty List reference\n");
      exit(EXIT_FAILURE);
   }
   if (L->cursor == NULL || L->index == UNDEFINED)
   {
      printf("List Error: calling insertBefore() on Undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   else if (L->length == 1 || L->index == 0)
   {
      freeNode(&N);
      prepend(L, data);
   }
   else
   {
      N->next = L->cursor;
      N->prev = L->cursor->prev;
      L->cursor->prev->next = N;
      L->cursor->prev = N;
      L->length++;
      L->index++;
   }
}

// insertAfter()
// Places new data after the cursor
void insertAfter(List L, LIST_ELEMENT data)
{
   Node N = newNode(data);

   if (L == NULL)
   {
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (isEmpty(L))
   {
      printf("List Error: calling insertAfter() on empty List reference\n");
      exit(EXIT_FAILURE);
   }
   if (L->cursor == NULL || L->index == UNDEFINED)
   {
      printf("List Error: calling insertAfter() on Undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   if (L->length == 1 || L->index == L->length - 1)
   {
      freeNode(&N);
      append(L, data);
   }
   else
   {
      N->prev = L->cursor;
      N->next = L->cursor->next;
      L->cursor->next->prev = N;
      L->cursor->next = N;
      L->length++;
   }
}
// deleteFront()
// Deletes data at front of L.
// Pre: !isEmpty(L)
void deleteFront(List L)
{
   Node N = NULL;

   if (L == NULL)
   {
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (isEmpty(L))
   {
      printf("List Error: calling deleteFront() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   N = L->front;
   if (length(L) > 1)
   {
      L->front = L->front->next;
   }
   else
   {
      L->front = L->back = NULL;
   }
   if (L->index != UNDEFINED)
   {
      if (L->index == 0)
      {
         L->index = UNDEFINED;
         L->cursor = NULL;
      }
      else
      {
         L->index--;
      }
   }

   L->length--;
   freeNode(&N);
}

// deleteBack()
// Deletes data at back of L.
// Pre: !isEmpty(L)
void deleteBack(List L)
{
   Node N = NULL;

   if (L == NULL)
   {
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (isEmpty(L))
   {
      printf("List Error: calling deleteBack() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   N = L->back;
   if (length(L) > 1)
   {
      L->back = L->back->prev;
   }
   else
   {
      L->back = L->front = NULL;
   }
   if (L->index == L->length - 1)
   {
      L->index = UNDEFINED;
      L->cursor = NULL;
   }
   L->length--;
   freeNode(&N);
}

// delete()
// Deletes list element at cursor if cursor is defined
void delete (List L)
{
   Node N = NULL;
   if (L == NULL)
   {
      printf("List Error: calling delete() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (isEmpty(L))
   {
      printf("List Error: calling delete() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if (L->index == UNDEFINED || L->cursor == NULL)
   {
      printf("List Error: calling delete() on an undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   N = L->cursor;

   if (L->index == 0)
   {
      deleteFront(L);
   }
   else if (L->index == L->length - 1)
   {
      deleteBack(L);
   }
   else
   {
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
      L->length--;
      freeNode(&N);
   }
}

// set()
// Overwrites the cursor element with x. Pre: length()>0, index()>=0
void set(List L, LIST_ELEMENT x)
{
   if (L == NULL)
   {
      printf("List Error: calling set() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (isEmpty(L))
   {
      printf("List Error: calling set() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if (L->index == UNDEFINED || L->cursor == NULL)
   {
      printf("List Error: calling set() on an undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   L->cursor->data = x;
}

// Other Functions ------------------------------------------------------------

// printList()
// Prints a string representation of L consisting of a space separated list
// of ints to stdout.
void printList(FILE *out, List L)
{
   Node N = NULL;
   int temp = length(L);
   if (L == NULL)
   {
      printf("List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   for (N = L->front; N != NULL; N = N->next)
   {
      printf("%l", N->data);
      temp--;
      if (temp == 0)
      {
         break;
      }
   }
   printf("\n");
}

// Returns a new list that is a copy of the parameter list passed
List copyList(List L)
{
   Node N = L->cursor;
   int temp_index = L->index;
   List copy = newList();
   int i;
   moveFront(L);
   for (i = 0; i < L->length; i++)
   {
      append(copy, L->cursor->data);
      moveNext(L);
   }
   L->index = temp_index;
   L->cursor = N;
   freeNode(&N);
   return copy;
}