//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 1
// Lex.c
//------------------------------------------------------------------------------------------------------
// Credit: Please Note, there was high level pusedocode collabration with my sister tvsharma 
// (Twisha Sharma) during this assignment. The below code is also based off of Professor Tantalo's 
// example code and pusedo-code provided on the class webpage.
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>  
#include "List.h"


int main (int argc, char **argv) {
    if (argc != 3) {
        printf("ERROR USER INPUT: please specificy input and output file\n");
        exit(EXIT_FAILURE);
    }
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    char buf[400];
    int numlines = 0;
    while (fgets(buf, 400, in) != NULL) {
        numlines ++;
    }
    fseek(in, 0, SEEK_SET);
    char **A = (char **) malloc(numlines * sizeof(char *));
    for (int counter = 0; counter < numlines; counter ++) {
        fgets(buf, 400, in);
        A[counter] = (char *) malloc((strlen(buf) + 1) * sizeof(char));
        strncpy(A[counter], buf, (strlen(buf) + 1));
    }
    List nL = newList();
    for (int x = 0; x < numlines; x++) {
        bool flag = false;
        moveFront(nL);
        while (index(nL) >= 0) {
            int y = get(nL);
            if (strcmp(A[x], A[y]) < 0) {
                flag = true;
                insertBefore(nL, x);
                break;
            }
            moveNext(nL);
        }
        if (flag == false) {
            append(nL, x);
        }
    }
    moveFront(nL);
    while (index(nL) >= 0) {
        int z = get(nL);
        fprintf(out, "%s", A[z]);
        moveNext(nL);
    }
    for (int n = 0; n < numlines; n++) {
        free(A[n]);
        A[n] = NULL;
    }
    free(A);
    A = NULL;
    freeList(&nL);
    fclose(in);
    fclose(out);
    return 0;
}
