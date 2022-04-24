//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 3
// Graph.c
//--------------------------------------------------------------------------------------------------------
// Credit: Please Note, there was high level pusedocode collabration with my sister Twisha Sharma  
// (tvsharma) during this assignment. The below code is also based off of Professor Tantalo's 
// example code and pusedo-code provided on the class webpage.
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "List.h"

// ** structs ** ----------------------------------------------------------------------------------------------
// private Graph type
typedef struct GraphObj{
    List *neighborV;
    int *distanceV;
    int *discover;
    int *finish;
    int *color; // array
    int *parentV; // array  
    int edges; // var that represents the size 
    int check; // DFS check var
    int vertex; // var that represents the order
    int time; 
} GraphObj;

// ** Constructors-Destructors ** -----------------------------------------------------------------------------
// Function newGraph() returns a Graph pointing to a newly created GraphObj 
// representing a graph having n vertices and no edges.
Graph newGraph(int n) {
    Graph G = calloc(1, sizeof(GraphObj));
    G->neighborV = (List *) calloc(n + 1, sizeof(List));
    G->vertex = n;
    G->distanceV = calloc(n + 1, sizeof(int));
    G->discover = calloc(n + 1, sizeof(int));
    G->finish = calloc(n + 1, sizeof(int));
    G->color = calloc(n + 1, sizeof(int));
    G->parentV = calloc(n + 1, sizeof(int)); // parent vertex
    G->edges = 0;
    G->check = 0;
    for (int i = 1; i < n + 1; i++) {
        G->neighborV[i] = newList();
        G->parentV[i] = NIL; // set the parent vertex to NIL 
        G->distanceV[i] = UNDEF; // set the distance to INF
        G->color[i] = WHITE; // set vertex to "as of yet undiscovered"
	G->discover[i] = 0;
    }
    return G;
}

// Function freeGraph() frees all heap memory associated with the Graph *pG, 
// then sets the handle *pG to NULL.
void freeGraph(Graph* pG) {
    if ((*pG) != NULL && pG != NULL) {
        for (int i = 1; i <= getOrder(*pG); i++) {
            freeList(&((*pG)->neighborV[i]));
        }
    free((*pG)->neighborV);
    free((*pG)->color);
    free((*pG)->parentV);
    free((*pG)->distanceV);
    free((*pG)->discover);
    free((*pG)->finish);
    (*pG)->neighborV = NULL;
    (*pG)->color = NULL;
    (*pG)->parentV = NULL;
    (*pG)->distanceV = NULL;
    (*pG)->discover = NULL;
    (*pG)->finish = NULL;
    free(*pG);
    *pG = NULL;
    }
}

// ** Access functions ** -------------------------------------------------------------------------------------
// Function getOrder() returns the corresponding field values, order = number of vertex 
int getOrder(Graph G) {
    if (!G) {
        printf("GRAPH ERROR: calling getOrder() on a NULL graph refrence\n.");
        exit(EXIT_FAILURE);
    }
    return G->vertex;
}

// Function getSize() return the corresponding field values, size = number of edges  
int getSize(Graph G) {
    if (!G) {
        printf("GRAPH ERROR: calling getSize() on a NULL graph refrence\n.");
        exit(EXIT_FAILURE);
    }
    return G->edges;
}

// Function getParent() will return the parent of vertex u in the BFS tree created by BFS(), 
// or NIL if BFS() has not yet been called. 
int getParent(Graph G, int u) {
    if (u > getOrder(G) || u < 1) { // if the vertex is not in the range 
        printf("GRAPH ERROR: calling getParent() on an vertex outside the given range\n.");
        exit(EXIT_FAILURE);
    }
    if (G->check == 0) { // if BFS() has not been called yet 
        return NIL;
    }
    return G->parentV[u];
}

// Function getDiscover() preconditions: 1 <= u <= n=getOrder(G)
int getDiscover(Graph G, int u) { 
    if (u < 1 || u > getOrder(G)) { // if vertex is not in range
	printf("Graph Error: calling getPath() on a vertex out of range\n");
        exit(EXIT_FAILURE);
    }
    if (G->check == 0) {
        return UNDEF;
    }
    return G->discover[u];
}

// Function getFinish() preconditions: 1 <= u <= n = getOrder(G)
int getFinish(Graph G, int u) { 
    if (u < 1 || u > getOrder(G)) { // if vertex is not in range
        printf("Graph Error: calling getPath() on vertex out of range\n");
        exit(EXIT_FAILURE);
    }
    if (G->check == 0) {
        return UNDEF;
    }
    return G->finish[u];
}

// ** Manipulation Procedures ** ------------------------------------------------------------------------------
// This function is a helper sort function.
// The function inserts and element and then sorts the list 
bool listSort(List L, int x) {
    moveFront(L);
    while (index(L) >= 0) { 
        int cursorValue = get(L);
        if (x == cursorValue) {
            return false;
        }
        if (x < cursorValue) {
            insertBefore(L, x);
            return true;
        }
        moveNext(L);
    }
    append(L, x);
    return true;
}

// Function addEdge() inserts a new edge joining u to v, 
// i.e. u is added to the adjacency List of v, and v to the adjacency List of u. 
// Your program is required to maintain these lists in sorted order by increasing labels. 
// *see addArc for precond*
void addEdge(Graph G, int u, int v) {
    if (u > getOrder(G) || u < 1) { // if the vertex u is not in the range
        printf("GRAPH ERROR: calling addEdge() on an vertex outside the given range\n.");
        exit(EXIT_FAILURE);
    }
    if (v > getOrder(G) || v < 1) { // if the vertex v is not in the range 
        printf("GRAPH ERROR: calling addEdge() on an vertex outside the given range\n.");
        exit(EXIT_FAILURE);
    }
    if (listSort(G->neighborV[v], u) == true && listSort(G->neighborV[u], v) == true) {
	G->edges += 1;
    }
    return;
}

// Function addArc() inserts a new directed edge from u to v, 
// i.e. v is added to the adjacency List of u (but not u to the adjacency List of v). 
// Both addEdge() and addArc() have the precondition that the two int arguments must lie in range 1 to getOrder(G). 
void addArc(Graph G, int u, int v) {
    if (u > getOrder(G) || u < 1) { // if the vertex u is not in the range
        printf("GRAPH ERROR: calling addEdge() on an vertex outside the given range\n.");
        exit(EXIT_FAILURE);
    }
    if (v > getOrder(G) || v < 1) { // if the vertex v is not in the range 
        printf("GRAPH ERROR: calling addEdge() on an vertex outside the given range\n.");
        exit(EXIT_FAILURE);
    }
    if (listSort(G->neighborV[u], v) == true) {
        G->edges++;
    }
    return;
}

// CREDIT: Professor Tantalo's provided Visit() psuedocode in python and during class lecture
// he explained how to use the list as a stack and queue which is implemented below
int Visit(Graph G, int x, int time, List S) {
    G->discover[x] = (++time); // the discover time at x, ++time increments time and then assigns the value
    G->color[x] = GRAY;
    moveFront(G->neighborV[x]);
    while (index(G->neighborV[x]) >= 0) {
        if (G->color[get(G->neighborV[x])] == WHITE) {
            G->parentV[get(G->neighborV[x])] = x;
            time = Visit(G, get(G->neighborV[x]), time, S);
        }
	moveNext(G->neighborV[x]);
    }
    G->color[x] = BLACK;
    G->finish[x] = (++time); // finish time of x
    insertAfter(S, x);
    return time;
}

// credit: Professor Tantalo, DFS psuedocode in python
//pre: length(S)==getOrder(G)
void DFS(Graph G, List S) { 
    G->check = 1; 
    if (length(S) != getOrder(G)) { // if the length of S is not equal to the size of the graph
        printf("Graph Error: calling DFS() while the preconditions are not met\n");
        exit(EXIT_FAILURE);
    }
    for (int x = 1; x <= getOrder(G); x++) {
        G->color[x] = WHITE;
        G->parentV[x] = NIL;
    }
    int time = 0;
    moveBack(S);
    while (index(S) >= 0) {
        if (G->color[front(S)] == WHITE) {
            time = Visit(G, front(S), time, S);
        }
	deleteFront(S);
    }
}

// ** Helper operations ** ------------------------------------------------------------------------------------
// Function transpose() preconditions: Graph exists 
Graph transpose(Graph G) { 
    /*int n = getOrder(G);
    Graph transpose = newGraph(n);
    int x = 1; // was 1
    moveFront(G->neighborV[x]);
    while (index(G->neighborV[x]) >= 0) { // while -1 will still run 
        for (int x = 1; x < getOrder(G); x ++) {
            int y = get(G->neighborV[x]); // get the adj vertex
            addArc(transpose, y, x);
            moveNext(G->neighborV[x]);
        }
    }*/
    return G;
}

// Function copyGraph() preconditions: Graph exists
Graph copyGraph(Graph G) { 
    /*int x = getOrder(G);
    Graph newG = newGraph(x);
    for (int i = 1; i <= x; i++) {
        newG->neighborV[i] = G->neighborV[i];
    }*/
    return G;
}

// Finally, function printGraph() prints the adjacency list representation of G to the file pointed to by out. 
// The format of this representation should match the above examples, 
// so all that is required by the client is a single call to printGraph().
void printGraph(FILE* out, Graph G) {
    for (int x = 1; x < getOrder(G); x++) {
        printList(out, G->neighborV[x]);
    }
}


