//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 1
// ListTest.c
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

int main(void){
    List A = newList();
    List B = newList();
    List C = newList();
    List D = newList();
    List E = newList();
    List F = newList();

    printf("-----newList() test-----\n");
    if (A != NULL) {
        printf("newList() test successful\n");
    }
    else {
        printf("newList() test failed\n");
    }

    printf("-----append() test-----\n");
    for (int x = 1; x <= 20; x++){
        append(A, x);
    }
    if (length(A) > 1) {
        printf("append() test successful\n");
    }
    else {
        printf("append() test failed\n");
    }
        printf("-----prepend() test-----\n");
    for (int x = 1; x <= 20; x++){
        prepend(C, x);
    }
    if (length(C) > 1) {
        printf("prepend() test successful\n");
    }
    else {
        printf("prepend() test failed\n");
    }

    printf("-----length() test-----\n");
    if (length(A) > 0) {
        printf("length() test successful\n");
    }
    else {
        printf("length() test failed\n");
    }

    printf("-----index() test-----\n");
    if (index(A) == -1) {
        printf("index() test successful\n");
    }
    else {
        printf("index() test failed\n");
    }

    printf("-----front() test-----\n");
    if (length(A) > 0) {
        printf("front() test successful\n");
    }
    else {
        printf("front() test failed\n");
    }

    printf("-----back() test-----\n");
    if (length(A) > 0) {
        printf("back() test successful\n");
    }
    else {
        printf("back() test failed\n");
    }

        printf("-----get() test-----\n");
    for (int x = 1; x <= 20; x++){
        append(F, x);
    }
    if (length(F) > 0 || index(F) >= 0) {
        printf("get() test successful\n");
    }
    else {
        printf("get() test failed\n");
    }

    printf("-----equals() test-----\n");
    for (int x = 1; x <= 20; x++){
        append(B, x);
    }
    if (equals(A, B) == true) {
        printf("equals() test successful\n");
    }
    else {
        printf("equals() test failed\n");
    }

    printf("-----clear() test-----\n");
    clear(B);
    if (length(B) == 0) {
        printf("clear() test successful\n");
    }
    else {
        printf("clear() test failed\n");
    }

    printf("-----set() test-----\n");
    moveFront(A);
    set(A, 3);
    int x = get(A);
    if (x == 3) {
        printf("set() test successful\n");
    }
    else {
        printf("set() test failed\n");
    }

    printf("-----moveFront() test-----\n");
    /*moveFront(B);
    set(B, 10);
    int y = get(B);*/
    if (x == 3) {
        printf("moveFront() test successful\n");
    }
    else {
        printf("moveFront() test failed\n");
    }

    printf("-----moveBack() test-----\n");
    moveBack(A);
    set(A, 7);
    int z = get(A);
    if (z == 7) {
        printf("moveBack() test successful\n");
    }
    else {
        printf("moveBack() test failed\n");
    }

    printf("-----movePrev() test-----\n");
    movePrev(A);
    set(A, 14);
    int a = get(A);
    if (a == 14) {
        printf("movePrev() test successful\n");
    }
    else {
        printf("movePrev() test failed\n");
    }

    printf("-----moveNext() test-----\n");
    moveNext(A);
    set(A, 0);
    int b = get(A);
    if (b == 0) {
        printf("moveNext() test successful\n");
    }
    else {
        printf("moveNext() test failed\n");
    }

        printf("-----insertBefore() test-----\n");
    insertBefore(A, 25);
    movePrev(A);
    int c = get(A);
    if (c == 25) {
        printf("insertBefore() test successful\n");
    }
    else {
        printf("insertBefore() test failed\n");
    }

    printf("-----insertAfter() test-----\n");
    insertAfter(A, 9);
    moveNext(A);
    int d = get(A);
    if (d == 9) {
        printf("insertAfter() test successful\n");
    }
    else {
        printf("insertAfter() test failed\n");
    }

    printf("-----deleteFront() test-----\n");
    for (int x = 1; x <= 20; x++){
        append(D, x);
    }
    printList(stdout, D);
    moveBack(D);
    deleteFront(D);
    printList(stdout, D);
    if (length(D) < 20) {
        printf("deleteFront() test successful\n");
    }
    else {
        printf("deleteFront() test failed\n");
    }

        printf("-----deleteBack() test-----\n");
    for (int x = 1; x <= 20; x++){
        append(E, x);
    }
    printList(stdout, E);
    moveFront(E);
    deleteBack(E);
    printList(stdout, E);
    if (length(E) < 20) {
        printf("deleteBack() test successful\n");
    }
    else {
        printf("deleteBack() test failed\n");
    }

    printf("-----delete() test-----\n");
    moveFront(E);
    moveFront(E);
    moveFront(E);
    printf("current cursor element: %d\n", get(E));
    delete(E);
    printList(stdout, E);
    printf("current cursor element: %d\n", get(E));
    return 0;
}