//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 3
// FindComponents.c
//--------------------------------------------------------------------------------------------------------
// Credit: Please Note, there was high level pusedocode collabration with my sister Twisha Sharma  
// (tvsharma) during this assignment. The below code is also based off of Professor Tantalo's 
// example code and pusedo-code provided on the class webpage.
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include "List.h"
#include "Graph.h"

int main (int argc, char **argv) {
    int x;
    int y;
    int z;
    int counter = 0;
    int strong = 0;
    if (argv[1] == NULL) {
        fprintf(stderr, "MAIN ERROR: program FindComponents.c needs more input arguments");
	exit(EXIT_FAILURE);
    }
    if (argv[2] == NULL) {
        fprintf(stderr, "MAIN ERROR: program FindComponents.c was given too many arguments");  
        exit(EXIT_FAILURE);
    }
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    fscanf(in, "%d", &x);
    Graph N = newGraph(x);
    fscanf(in, "%d %d", &y, &z);
    while (y != 0 && z != 0) {
        addArc(N, y, z);
	fscanf(in, "%d %d", &y, &z);	
    }
    fprintf(out, "Adjacency list representation of G: \n");
    printGraph(out, N);
    List A = newList();
    for (int i = 1; i < getOrder(N) + 1; i++) {
        append(A, i);
    }
    DFS(N, A);
    Graph M = transpose(N);
    DFS(M, A);
    List B = newList();
    for (int i = 1; i <= getOrder(M); i++) {
        if (getParent(M, i) == NIL) {
	    strong += 1;
	}
    }
    fprintf(out,"G contains %d strongly connected components:\n", strong);
    moveBack(A);
    while (index(A) >= 0) {
        prepend(B, get(A));
	if (getParent(M, get(A)) == NIL) {
	    counter += 1;
	    fprintf(out, "Component %i: ", counter);
	    printList(out, B);
	    clear(B);
	}
	movePrev(A);
    }
} 
