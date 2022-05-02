//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 4
// List.c
//------------------------------------------------------------------------------------------------------
// Credit: Please Note, there was high level pusedocode collabration with my sister tvsharma 
// (Twisha Sharma) during this assignment. The below code is also based off of Professor Tantalo's 
// example code and pusedo-code provided on the class webpage.
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

// structs **************************************************************************************************

// private Node type
typedef struct NodeObj *Node;

// private NodeObj type
typedef struct NodeObj{
    Node next;
    Node prev;
    pointer data;
} NodeObj;

// private ListObj type
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int ind;
} ListObj;

// Constructors-Destructors *********************************************************************************

Node newNode(pointer data) {
    Node N = malloc(sizeof(NodeObj));
    if (N == NULL) {
        free(N);
        return NULL;
    }
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return N;
}

void freeNode(Node *pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

List newList(void) { // Creates and returns a new empty List.
    List L;
    L = malloc(sizeof(ListObj));
    if (L == NULL) {
        return NULL;
    }
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->ind = -1;
    L->length = 0;
    return L; // return the new empty list
}

void freeList(List *pL) { // Frees all heap memory associated with *pL, and sets *pL to NULL.
    if (pL != NULL && *pL != NULL) {
        clear(*pL);
        free(*pL);
        *pL = NULL; // set *pL to NULL
    }
}

// Access functions *****************************************************************************************

bool isEmpty(List L) { // checks if the list is empty
    //if (L == NULL) {
    //    printf("List Error: calling isEmpty on a NULL list refrence\n");
    //    exit(EXIT_FAILURE);
    //}
    if (length(L) > 0) {
        return false;
    }
    return true;
}

int length(List L) { // returns the number of elements in list L 
    if (L == NULL) {
        printf("List Error: calling length() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    return (L->length);
}

int index(List L) { // returns the index of the cursor element if defined, -1 otherwise 
    if (L->cursor == NULL) {
        L->ind = -1;
    }
    return (L->ind);
}

pointer front(List L) { // returns the front element of L, pre: length() > 0
    if (L == NULL) {
        printf("List Error: calling front() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: calling front() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return (L->front->data);
}

pointer back(List L) { // returns the back element of L, pre: length() > 0
    if (L == NULL) {
        printf("List Error: calling back() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: calling back() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return (L->back->data);
}

pointer get(List L) { // returns the cursor element of L, pre: length() > 0, index() >= 0
    if (L == NULL) {
        printf("List Error: calling get() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: calling get() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return (L->cursor->data);
}


// Manipulation Procedures ******************************************************************************************** 

void clear(List L) { // Resets L to its original empty state.
    while (length(L) > 0) {
        deleteFront(L);
    }
    return;
}

void set(List L, pointer x) { // Overwrites the cursor element’s data with x.
    if (length(L) <= 0 || index(L) < 0) { // Pre: length()>0, index()>=0
        printf("List Error: calling set() with length or index preconditions not met\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}


/*void moveTo(List L, pointer i) { // helper function
    if (L == NULL) {
        printf("List Error: calling moveTo() with length or index preconditions not met\n");
        exit(EXIT_FAILURE);
    }
    if (i >= 0 && i <= (length(L)-1)) {
        Node current = L->front;
        for(int x = 0; x < i; x++) {
            current = current->next;
        }
        L->cursor = current;
        L->ind = i;
    } else {
        L->cursor = NULL;
        L->ind = -1;
    }
}*/

void moveFront(List L) { // If L is non-empty, sets cursor under the front element,
    if (length(L) > 0) { // otherwise does nothing.
        L->cursor = L->front;
        L->ind = 0;
    }
}

void moveBack(List L) { // If L is non-empty, sets cursor under the back element,
    if (length(L) <= 0) { // otherwise does nothing.
        return;
    }
    if (L->back == NULL) {
        return;
    }
    if (length(L) > 0) {
        L->cursor = L->back;
        L->ind = length(L) - 1;
    }
}

void movePrev(List L) {
    if (L->cursor == NULL) { // If cursor is defined and not at front, move cursor one
        return;
    }
    if (L->cursor != NULL && L->cursor == L->front) { // step toward the front of L; if cursor is defined and at front,
        L->cursor = NULL; // cursor becomes undefined; if cursor is undefined
        L->ind -= 1;
        return; // do nothing
    }
    L->cursor = L->cursor->prev;
    L->ind -= 1;
}

void moveNext(List L) {
    if (L->cursor != NULL && L->cursor != L->back) { // If cursor is defined and not at back, 
        L->cursor = L->cursor->next; // move cursor one step toward the back of L;
        L->ind += 1;
        return;
    }
    if (L->cursor != NULL && L->cursor == L->back) { // if cursor is defined and at back, 
        L->cursor = NULL; // cursor becomes undefined;
        L->ind =- 1;
        return;
    }
    return; // if cursor is undefined, do nothing
}

void prepend(List L, pointer x) { // Insert new element into L. 
    if (length(L) == 0) { // If L is non-empty, insertion takes place before front element.
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
    L->ind += 1;
}

void append(List L, pointer x) { // Insert new element into L.
    Node N = newNode(x);
    if (L == NULL) {
        printf("List Error: calling append() with NULL list refrence\n");
    }
    if (length(L) == 0) { // If L is non-empty, insertion takes place after back element.
        L->front = L->back = N;
    }
    else {
        L->back->next = N;
        N->prev = L->back;
        L->back = N;
    }
    L->length ++;
}

void insertBefore(List L, pointer x) { // Insert new element before cursor.
    if (length(L) <= 0 || index(L) < 0) { // Pre: length()>0, index()>=0
        printf("List Error: calling insertBefore() on NULL list and index reference\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) == 0) {
        prepend(L, x);
        return;
    }
    Node N = newNode(x);
    N->next = L->cursor;
    N->prev = L->cursor->prev;
    L->cursor->prev = N;
    N->prev->next = N;
    L->length ++;
    L->ind ++;
    return;
}

void insertAfter(List L, pointer x) { // Insert new element after cursor.
    Node N = newNode(x);
    if (length(L) <= 0 || index(L) < 0) { // Pre: length()>0, index()>=0
        printf("List Error: calling insertAfter() with length or index preconditions not met\n");
        exit(EXIT_FAILURE);
    }
    if (L->back == L->cursor) {
        N->prev = L->cursor;
        N->next = NULL;
        L->cursor->next = N;
        L->back = N;
        L->length ++;
        return;
    }
    L->cursor->next->prev = N;
    N->next = L->cursor->next;
    N->prev = L->cursor;
    L->cursor->next = N;
    L->length ++; // increment the length
    return;
}

void deleteFront(List L) { // Delete the front element.
    if (L == NULL) { // Pre: length()>0
        printf("List Error: calling deleteFront() with length preconditions not met\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: calling deleteFront() with length preconditions not met\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 1) {
        Node F = NULL;
        F = L->front;
        if (L->cursor == L->front) {
            L->ind = -1;
        }
        L->front = NULL;
        L->back = NULL;
        freeNode(&F);
        L->length = 0;
        return;
    }
    else {
        Node N = NULL;
        N =  L->front;
        if (L->cursor == L->front) {
            L->ind = -1;
            L->front = L->front->next;
            freeNode(&N);
            L->length --;
            return;
        }
        if (L->cursor != NULL) {
            L->ind --;
        }
        L->front = L->front->next;
        freeNode(&N);
        L->length --;
        return;
    }
}

void deleteBack(List L) { // Delete the back element.
    Node N = NULL;
    N = L->back;
    if (L == NULL) { // Pre: length()>0
        printf("List Error: calling deleteBack() with length preconditions not met\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0){
       printf("List Error: calling deleteBack() with lengthpreconditions not met\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 1) {
        if (L->cursor != NULL) {
            L->cursor = NULL;
            L->ind --;
        }
        freeNode(&L->back);
        L->length = 0;
        return;
    }
    else {
        if (L->cursor == L->back) {
            L->cursor = NULL;
            L->ind --;
        }
        L->back = L->back->prev;
        freeNode(&N);
        L->length --;
        return;
    }
}

void delete(List L) { // Delete cursor element, making cursor undefined.
    if (L->cursor == NULL) {
        printf("List Error : calling delete() on NULL List cursor refrence\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0 || index(L) < 0) { // Pre: length()>0, index()>=0
        printf("List Error: calling delete() with length or index preconditions not met\n");
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
    freeNode(&L->cursor);
    L->ind = -1;
    L->length --;
    return;
}

// Helper operations ***************************************************************************************
