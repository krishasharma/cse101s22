//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 2
// Graph.c
//------------------------------------------------------------------------------------------------------
// Credit: Please Note, there was high level pusedocode collabration with my sister Twisha Sharma  
// (tvsharma) during this assignment. The below code is also based off of Professor Tantalo's 
// example code and pusedo-code provided on the class webpage.
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "List.h"

// ** structs ** ----------------------------------------------------------------------------------------------

// private Graph type
typedef struct GraphObj{
    List *neighborV;
    int *color; // array
    int *parentV; // array 
    int *distanceV; // array 
    int edges; // var that represents the size 
    int sourceV; 
    int vertex; // var that represents the order 
}GraphObj;

// ** Constructors-Destructors ** -----------------------------------------------------------------------------

// Function newGraph() returns a Graph pointing to a newly created GraphObj 
// representing a graph having n vertices and no edges.
Graph newGraph(int n) {
    Graph G = calloc(1, sizeof(GraphObj));
    if (G == NULL) {
        return NULL;
    }
    List *neighborV = (List *) calloc(n + 1, sizeof(List));
    for (int i = 1, i <= n, i++) {
        neighborV[i] = newList(L);
        G->parentV[i] = NIL; // set the parent vertex to NIL 
        G->distanceV[i] = INF; // set the distance to INF
        G->color[i] = WHITE; // set vertex to "as of yet undiscovered"
    }
    int G->vertex = n;
    int G->color = (int) calloc(n + 1, sizeof(int));
    int G->parentV = (int) calloc(n + 1), sizeof(int)); // parent vertex
    int G->distanceV = (int) calloc(n + 1, sizeof(int));
    G->edges = 0;
    G->sourceV = NIL; // BFS returns the source vertex
    return G; 
}

// Function freeGraph() frees all heap memory associated with the Graph *pG, 
// then sets the handle *pG to NULL.
void freeGraph(Graph* pG) {
    if ((*pG) != NULL && pg != NULL) {
        for (int i = 1; i <= getOrder(*pG); i++) {
            freeList(&((*pG)->neighborV[i]));
        }
    free((*pG)->neighborV); 
    free((*pG)->color);
    free((*pG)->parentV);
    free((pG*)->distanceV);
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

// Function getSource() return the corresponding field values, source vertex most recently used
int getSource(Graph G) {
    if (!G) {
        printf("GRAPH ERROR: calling getSource() on a NULL graph refrence\n.");
        exit(EXIT_FAILURE);
    }
    if (!BFS(G)) {
        return NIL;
    }else{
        return G->sourceV; // return source vertex 
    }
}

// Function getParent() will return the parent of vertex u in the BFS tree created by BFS(), 
// or NIL if BFS() has not yet been called. 
int getParent(Graph G, int u) {
    if (u > getOrder(G) || u < 1) { // if the vertex is not in the range 
        printf("GRAPH ERROR: calling getParent() on an vertex outside the given range\n.");
        exit(EXIT_FAILURE);
    }
    if (!G->sourceV) { // if BFS() has not been called yet 
        return NIL;
    }
    if (G->sourceV) { // if BFS() has been called
        return G->parentV[u];
    }
}

// Function getDist() returns the distance from the most recent BFS source to vertex u, 
// or INF if BFS() has not yet been called. 
int getDist(Graph G, int u) {
    if (u > getOrder(G) || u < 1) { // if the vertex is not in the range
        printf("GRAPH ERROR: calling getDist() on an vertex outside the given range\n.");
        exit(EXIT_FAILURE);
    }
    if (!G->sourceV) {
        return INF;
    }
    if (G->sourceV) {
        return G->distanceV[u];
    }
}

// Function getPath() appends to the List L the vertices of a shortest path in G from source to u, 
// or appends to L the value NIL if no such path exists. getPath() has the precondition getSource(G)!=NIL, 
// so BFS() must be called before getPath() is called.
void getPath(List L, Graph G, int u) {
    if (u > getOrder(G) || u < 1) { // if the vertex is not in the range
        printf("GRAPH ERROR: calling getPath() on an vertex outside the given range\n.");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) == NIL) { // if the source vertex is NIL
        printf("GRAPH ERROR: calling getParent() while source vertex is unknown\n.");
        return NIL;
    }
    if (getParent(G, u) == NIL) { // if the parent vertex is NIL and no path exists
        append(L, NIL); // append NIL to the back of the list 
    } else if (u == getSource(G)) { // if u is the source vertex
        append(L, u); // append u to the back of the list 
    } else { // otherwise 
        prepend(L, u); // add u to the front of the list
        int head = getParent(G, u); // set u to a temp var 
        while ((head != getSource(G) && (head != NIL))) { // while head is not the source vertex and head is not NIL
            prepend(L, head); // add head to the front of the list 
            head = getParent(G, head); // set head to the parent vertex
        }
        prepend(L, head); // add head to the front of the list 
    }
}

// ** Manipulation Procedures ** ------------------------------------------------------------------------------

// Function makeNull() deletes all edges of G, restoring it to its 5 original (no edge) state. 
// (This is called a null graph in graph theory literature). 
void makeNull(Graph G) {
    for (int i = 1, i <= getOrder(G), i++) { // if the graph exists 
        clear(G->neighborV[i]); // clear the neighbor verticies
        G->parentV[i] = NIL; // set the parent vertex to NIL 
        G->distanceV[i] = INF; // set the distance to INF
        G->color[i] = WHITE; // set the vertex to "as of yet undiscovered"
    }
    G->sourceV = NIL; // set the source vertex to NIL 
    G->edges = 0; // set the edges to O 
}

// Function addEdge() inserts a new edge joining u to v, 
// i.e. u is added to the adjacency List of v, and v to the adjacency List of u. 
// Your program is required to maintain these lists in sorted order by increasing labels. 
//*see addArc for precond*
void addEdge(Graph G, int u, int v) {
    if (u > getOrder(G) || u < 1) { // if the vertex u is not in the range
        printf("GRAPH ERROR: calling addEdge() on an vertex outside the given range\n.");
        exit(EXIT_FAILURE);
    }
    if (v > getOrder(g) || v < 1) { // if the vertex v is not in the range 
        printf("GRAPH ERROR: calling addEdge() on an vertex outside the given range\n.");
        exit(EXIT_FAILURE);
    }
    /*int now = -1; // initialize var at -1 
    set(G->neighborV[u], 0); // set the cursor of list at the neighbor index u to 0 
    if (index(G->neighborV[u]) != -1) { // if the index of the cursor of the list at the neighbor index u does not equal -1 
        now = get(G->neighborV[u]); // set now equal to the cursor element of the list at neighbor index u
    }
    while (now < v && index(G->neighborV[u]) != -1) { // while now is less than v and the index of the cursor is defined 
        moveNext(G->neighborV[u]); // move the cursor at the list neighbor index u back one 
        if (index(G->neighborV[u]) != -1) { // if the cursor element of the neighbor list at index u is defined 
            now = get(G->neighborV[u]); // set now equal to the cursor element of the neighbor list at index u 
        }
    }
    if (index(G->neighborV[u] != -1)) { // if the cursor element of the neighbor list at index u is defined 
        insertBefore(G->neighborV[u], v); // insert vertex v before the cursor element of the neighbor list at index u
    }else{
        append(G->neighborV[u], v); // append vertex v to the back of the neighbor list at index u
    }
    set(G->neighborV[v], 0); // set the cursor element of the neighbor list at index v to 0
    if (index(G->neighborV[v]) != -1) { // if the index of the cursor element of the neighbor list at index v is defined 
        now = get(G->neighborV[v]); // set now equal to the cursor element of the neighbor list at index v 
    }
    while (now < u && index(G->neighborV[v]) != -1) { // while now is less than u and the index of the cursor is defined 
        moveNext(G->neighborV[v]); // move the cursor at the neighbor list index v back one 
        if (index(G->neighborV[v]) != -1) { // if the index of the cursor element of the neighbor list at index v is defined 
            now = get(G->neighborV[v]); // set now equal to the cursor element of the neighbor list at index v
        }
    }
    if (index(G->neighborV[v]) != -1) { // if the index of the cursor element of the neighbor list at index v is defined 
        insertBefore(G->neighborV[v], u); // insert vertex u before the cursor element of the neighbor list at index v 
    }else{
        append(G->neighbor[v], u); // append vertev u to the back of the neighbor list at index v 
    }
    G->edges++; // add edge by one */
    addArc(G, u, v);
    addArc(G, u, v);
    G->edges -= 1;
}

// Function addArc() inserts a new directed edge from u to v, 
// i.e. v is added to the adjacency List of u (but not u to the adjacency List of v). 
// Both addEdge() and addArc() have the precondition that the two int arguments must lie in range 1 to getOrder(G). 
void addArc(Graph G, int u, int v) { 
    if (u > getOrder(G) || u < 1) { // if the vertex u is not in the range
        printf("GRAPH ERROR: calling addEdge() on an vertex outside the given range\n.");
        exit(EXIT_FAILURE);
    }
    if (v > getOrder(g) || v < 1) { // if the vertex v is not in the range 
        printf("GRAPH ERROR: calling addEdge() on an vertex outside the given range\n.");
        exit(EXIT_FAILURE);
    }
    int now = -1; // initialize var at -1 
    set(G->neighborV[u], 0); // set the cursor of list at the neighbor index u to 0 
    if (index(G->neighborV[u]) != -1) { // if the index of the cursor element of the neighbor list at u is defined
        now = get(G->neighbor[u]); // set now equal to the cursor element of the neighbor list at index u
    }
    while (now < v && index(G->neighborV[u]) != -1) { // while now is less than v and the index of the cursor is defined 
        moveNext(G->neighborV[u]); // move the cursor at the list neighbor index u back one 
        if (index(G->neighborV[u]) != -1) { // if the cursor element of the neighbor list at index u is defined 
            now = get(G->neighborV[u]); // set now equal to the cursor element of the neighbor list at index u 
        }
    }
    if (index(G->neighborV[u] != -1)) { // if the cursor element of the neighbor list at index u is defined 
        insertBefore(G->neighborV[u], v); // insert vertex v before the cursor element of the neighbor list at index u
    }else{
        append(G->neighborV[u], v); // append vertex v to the back of the neighbor list at index u
    }
    G->edges ++; // increment edge by one

}

// Function BFS() runs the BFS algorithm on the Graph G with source s, 
// setting the color, distance, parent, and source fields of G accordingly. 
void BFS(Graph G, int s) {}
    if (s > getOrder(G) || s < 1) { // if the source vertex is not in the range 
        printf("GRAPH ERROR: calling BFS() on an source vertex outside the given range\n.");
        exit(EXIT_FAILURE);
    }
    G->sourceV = s; // set s as the source vertex 
    for (int i = 1; i <= getOrder(G); i++) { // reset the graph to be like a new graph
        G->parentV[i] = NIL; // set the parent vertex to NIL 
        G->distanceV[i] = INF; // set the distance to INF
        G->color[i] = WHITE; // set the vertex to "as of yet undiscovered"
    }
    int x;
    int y;
    G->parentV[s] = NIL;
    G->distanceV[s] = 0;
    G->color[s] = GRAY // set the source vertex color to "vertecies discovered, but neighbors not"
    List A = newList;
    append(A, s);
    while (length(A) > 0) { // while the length of the list is greater than 0
        x = front(A); // set temp var to the front of list
        deleteFront(A); // delete the front of the list 
        set(G->neighborV[x]); // set the list at index of the neighbor x to 0 
        while (index(G->neighborV[x] != -1)) { // while the cursor is defined 
            y = get(G->neighborV[x]); // set y to the cursor pointing to the list at the index
            if (G->color[y] == WHITE) { // if the vertex is "as of yet undiscovered"
                G->color[y] = GRAY; // discover the vertex but not the neighbor 
                G->distanceV[y] = getDist(G, x) + 1; // set the distance to y equal to the distance to x + 1 
                G->parentV[y] = x; // set the parent vertex at index y to x  
                append(Q, y); // append the parent vertex to the front of the list
            }
            moveNext(G->neighborV[x]); // move to the next 
        }
        G->color[x] = BLACK; // set color to "finished"
    }
    freeList(&A); // free the list
}

// ** Helper operations ** ------------------------------------------------------------------------------------

// Finally, function printGraph() prints the adjacency list representation of G to the file pointed to by out. 
// The format of this representation should match the above examples, 
// so all that is required by the client is a single call to printGraph().
void printGraph(FILE* out, Graph G) {
    if (getSource(G) == NIL) {
        return NIL;
    }
    for (int i = 0; i < G->neighbors[i]; i++) {
        if (i == G->sourceV) {
            printf("%i\n", G->sourceV);
        }
        else if (G->parentV[i] == NIL) {
            printf("%i, is not reachable from %i\n", i, G->sourceV)
        }
        else {
            printPath(G, G->sourceV, G->parentV[i]);
            printf("%i\n", x);
        }
    }
}