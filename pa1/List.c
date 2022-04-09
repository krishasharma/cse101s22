//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 1
// List.c
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj *Node;

// private NodeObj type
typedef struct NodeObj {
    Node next;
    Node prev;
    int data; // cursor index COULD BE WRONG
} NodeObj;

// private ListObj type 
typedef struct ListObj {
    Node cursor; // cursor Node
    Node front;
    Node back;
    int index;
    int length;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

Node newNode(int data) {
    Node N = malloc(sizeof(NodeObj));
    if (N == NULL) {
        return NULL;
    }
    N->data = data; // COULD BE WRONG!!!!
    N->next = NULL; // initialize at NULL
    N->prev = NULL; // initialize at NULL
    return(N);
}

void freeNode(Node *pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

// Creates and returns a new empty List.
List newList(void) {
    List L;
    L = malloc(sizeof(ListObj));
    if (L == NULL) {
        return NULL;
    }
    L->index = -1;
    L->length = 0;
    L->cursor = NULL;
    L->front = NULL;
    L->back = NULL;
    return(L); // returns the new empty list
}

// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

// Access functions -----------------------------------------------------------


// Access functions -----------------------------------------------------------

bool isEmpty(List L) {
    if (L == NULL) {
        printf("List Error: calling isEmpty() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0) {
        return false;
    }
    return true;
}

// returns the number of elements in list L 
int length(List L) {
    if (L == NULL) {
        printf("List Error: calling length() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    return (L->length);
}

int index(List L) {
    // returns the index of the cursor element if defined, -1 otherwise 
    if (L == NULL) {
        printf("List Error: calling index() on NULL list refrence\n");
        exit(EXIT_FAILURE);
        return -1;
    }
    return (L->index);
}

// returns the front element of L, pre: length() > 0 
int front(List L) {
    if (L == NULL) {
        printf("List Error: calling front() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L)) {
        printf("List Error: calling front() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    return (L->front->data);
}

// returns the back element of L, pre: length() > 0
int back(List L) {
    if (L == NULL) {
        printf("List Error: calling front() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L)) {
        printf("List Error: calling front() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    return(L->back->data);
}

// returns the cursor element of L, pre: length() > 0, index() >= 0
int get(List L) {
    if (index(L) < 0) {
        printf("List Error: calling front() on NULL List refrence\n");
        exit(EXIT_FAILURE);
        return -1;
    }
    if (length(L) <= 0) {
        printf("List Error: calling front() on NULL List refrence\n");
        exit(EXIT_FAILURE);
        return -1;
    }
    return L->cursor->data; // returns the cursor element, might be index MIGHT BUT IDK
}

// returns true if List A and B are in the same state and returns false otherwise
bool equals(List A, List B) {
    if (A == NULL) {
        printf("List A Error: calling equals() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    if (B == NULL) {
        printf("List B Error: calling equals() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    bool eq;
    Node X;
    Node Y;
    eq = (A->length == B->length);
    X = A->front;
    Y = B->front;
    while (eq && X != NULL) {
        eq = (X->data == Y->data);
        X = X->next;
        Y = Y->next;
    }
    return eq;
}

// Manipulation procedures ----------------------------------------------------

/*
void dequeue(List L) {
    Node N = NULL;
    if (L == NULL) {
        printf("List Error: calling dequeue() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L)) {
        printf("List Error: calling dequeue on an empty List\n");
        exit(EXIT_FAILURE);
    }
    N = L->front;
    if (length(L) > 1) {
        L->front = L->front->next;
    }else{
        L->front = L->back = NULL;
    }
    L->length -= 1;
    freeNode(&N);
}
*/

// Resets L to its original empty state.
void clear(List L) {
    // is it dumb to say for clear all we need to do is make a new empty list 
    // then set the input L to that new empty list?
    // or do we have to go through and clear out every node
    /*
    Node N = NULL;
    while (L != NULL) {
        N = L->front;
        if (length(L) > 1) {
            L->front = L ->front->next;
        }else{
            L->front = L->back = NULL;
            }
            L->length -= 1;
            freeNode(&N);
    }*/
    while (length(L) > 0) {
        deleteFront(L);
    }
    return;
}
// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, int x) {
    if (length(L) <= 0 || index(L) < 0) {
        printf("List Error: calling set() while length or index preconditions are not met");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L) {
    if (L->front == NULL) {
        return;
    }
    if (!isEmpty(L)) {
        L->cursor = L->front;
        L->index = 1;
    }
}

// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L) {
    if (L->back == NULL) {
        return;
    }
    if (!isEmpty(L)) {
        L->cursor = L->back;
        L->index = length(L);
    }
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L) {
    if (L->cursor == NULL) { // if cursor is defined and not at front
        return;
    }
    if (L->cursor != NULL && L->cursor == L->front) { // if cursor is defined and at front
        L->cursor = NULL; // cursor becomes undefined
        L->index -= 1;
        return;
    }
    L->cursor = L->cursor->prev;
    L->index -= 1;
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
    /*if (L->cursor == NULL) { // if cursor is defined and not at back 
        return;
    }*/
    if (L->cursor != NULL && L->cursor != L->back) {
        L->cursor = L->cursor->next;
        L->index += 1;
        return;
    }
    if (L->cursor != NULL && L->cursor == L->back) { // if cursor is defined and at back
        L->cursor = NULL;
        L->index -= 1; // cursor becomes undefined
        return;
    }
    return;
    /*
    L->cursor = L->cursor->next;
    L->index += 1;*/
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int x) {
    /*Node N = newNode(x); // x is data of cursor element
    //if (N == NULL) {
        //printf("List Error calling prepend() on NULL List refrence \n");
        //exit(EXIT_FAILURE);
    //}
    if (isEmpty(L)) {
        L->length += 1; // increment the length
        L->front = N;
        L->back = N; // only thing in the list 
    }
    if (length(L) > 0){
        L->length += 1;
    }
    if (!L->cursor) {
        L->index += 1;
    }
    L->front->prev = N;
    N->next = L->front;
    L->front = N;
    return; */
    if (isEmpty(L)) {
        Node N = newNode(x);
        L->front = N;
        L->back = N;
    }
    else {
        Node N = newNode(x);
        L->front->prev = N;
        N->next = L->front;
        L->front = N;
    }
    L->length += 1;
    L->index += 1;
}


// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int x) {
    Node N = newNode(x);
    /*if (N == NULL) {
        printf("List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }*/
    if (isEmpty(L)) {
        L->front = L->back = N;
    }
    else{
        L->back->next = N;
        N->prev = L->back;
        L->back = N;
    }
    L->length += 1;
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x) {
    //Node N = newNode(x);
    if (length(L) <= 0 || index(L) < 0) {
        printf("List Error: calling insertBefore() on NULL list and index reference\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) == 0) {
        prepend(L, x);
        return;
    }
    /*
    if (isEmpty(L)) {
        L->index = 0;
        L->front = L->back = N;
    }
    */
    Node N = newNode(x);
    N->next = L->cursor;
    N->prev = L->cursor->prev;
    L->cursor->prev = N;
    N->prev->next = N;
    L->length ++; // increment the length 
    L->index ++; // move the index back to update to the correct value
    return;
}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
    Node N = newNode(x);
    if (length(L) <= 0 || index(L) < 0) {
        printf("List Error: calling insertAfter() on NULL list and index reference\n");
        exit(EXIT_FAILURE);
    }
    /*if (isEmpty(L)) {
        L->index = 0;
        L->front = L->back = N;
    }*/
    L->cursor->next->prev = N;
    N->next = L->cursor->next;
    N->prev = L->cursor;
    L->cursor->next = N;
    L->length ++; // increment the length 
    return;
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) {
    if (L == NULL) {
        printf("List Error: calling deleteFront() while length preconditions are unsatisfied\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: calling deleteFront() while length preconditions are unsatisfied\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 1) {
        Node X = NULL;
        X = L->front;
        if (L->cursor == L->front) {
            L->index = -1;
        }
        L->front = NULL;
        L->back = NULL;
        L->length = 0;
        freeNode(&X);
        return;
    }
    else {
        Node Y = NULL;
        Y = L->front;
        if (L->cursor == L->front) {
            L->index = -1;
            L->front = L->front->next;
            L->length -= 1;
            freeNode(&Y);
            return;
        }
        if (L->cursor != NULL) {
            L->index -= 1;
        }
        L->front = L->front->next;
        L->length -= 1;
        freeNode(&Y);
        return;
    }
}

// Delete the back element. Pre: length()>0
void deleteBack(List L) {
    if (L == NULL) {
        printf("List Error: calling deleteBack() while length preconditions are unsatisfied");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0){
        printf("List Error: calling deleteBack() while length preconditions are unsatisfied");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == L->back) {
        L->cursor = NULL;
        L->index = -1;
        freeNode(&L->back);
        return;
    }
    if (length(L) == 1) {
        freeNode(&L->back);
        L->length -= 1;
        return;
    }
    if (L->cursor != NULL) {
        L->index -= 1;
    }
    L->back = L->back->prev;
    freeNode(&L->back);
    L->length -= 1;
    return;
}

// Delete cursor element, makingc ursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
    if (length(L) <= 0 || index(L) < 0) {
        printf("List Error: calling delete() with length or index preconditions not met\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL) {
        printf("List Error: calling delete() on  NULL list refrence\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == L->front) {
        deleteFront(L);
        return;
    }
    if (L->cursor == L->back) {
        deleteBack(L);
        return;
    }
    L->cursor->prev->next = L->cursor->next;
    L->cursor->next->prev = L->cursor->prev;
    L->index = -1;
    L->length -= 1;
    freeNode(&L->cursor);
    return;
}

// Other operations -----------------------------------------------------------

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE *out, List L) {
    for (Node next = L->front; next != NULL; next = next->next) {
        fprintf(out, "%d ", next->data);
    }
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L) {
    List newList = L;
    newList->index = -1;
    return(newList);
}




