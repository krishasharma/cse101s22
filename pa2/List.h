//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 1
// List.h
//------------------------------------------------------------------------------------------------------
// Credit: Please Note, there was high level pusedocode collabration with my sister tvsharma 
// (Twisha Sharma) during this assignment. The below code is also based off of Professor Tantalo's 
// example code and pusedo-code provided on the class webpage.
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct NodeObj *Node;
typedef int ListElement;
typedef struct ListObj* List;


List newList(void);

void freeList(List *pL);    // pL is a pointer to the list

bool isEmpty(List L);

int length( List L);    // L is the list 

int index(List L);

int front(List L);

int back(List L);

int get(List L);

bool equals(List A, List B);

void dequeue(List L);

void clear(List L);

void set(List L, int x);    // L is the list, x is the val that the current element will be set too 

void moveFront(List L);

void moveBack(List L);

void movePrev(List L);

void moveNext(List L);

void prepend(List L, int x);

void append(List L, int x);

void insertBefore(List L, int x);

void insertAfter(List L, int x);

void deleteFront(List L);

void deleteBack(List L);

void delete(List L);

void printList(FILE *out, List L);

List concatList(List A, List B);

List copyList(List L);
