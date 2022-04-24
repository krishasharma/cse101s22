//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 3
// GraphTest.c
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

int main(void) {
    Graph G = newGraph();
    if (G != NULL) {
        printf("The graph was made\n");
    }
    else{
        printf("The graph was not made\n");
    }
    addArc(G, 2,5);
    addArc(G, 2,6);
    addArc(G, 3,2);
    addArc(G, 3,4);
    addArc(G, 3,6);
    addArc(G, 3,7);
    addArc(G, 3,8);
    addEdge(G, 6,5);
    addEdge(G, 6,7);
    addEdge(G, 8,4);
    addEdge(G, 8,7);

    printf("Graph G: ");
    printGraph(stdout, G);
    printf("order : %d\n", getOrder(G));
    printf("size : %d\n", getSize(G));
    printf("parent: %d\n", getParent(G));
    int u = 13;
    printf("discover time: %d\n", getDiscover(G, u));
    printf("finish time: %d\n", getFinish(G, u));
    printf("Graph G: ");
    printGraph(stdout, G);
    Graph T = transpose(G);
    printf("Graph Transpose: ");
    printGraph(stdout, T);
    printf("Graph G: ");
    printGraph(stdout, G);
    Graph C = copyGraph(G);
    printf("Graph Copy: ");
    printGraph(stdout, C);

    return 0;
}
