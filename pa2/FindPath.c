//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 2
// FindPath.c
//------------------------------------------------------------------------------------------------------
// Credit: Please Note, there was high level pusedocode collabration with my sister Twisha Sharma  
// (tvsharma) during this assignment. The below code is also based off of Professor Tantalo's 
// example code and pusedo-code provided on the class webpage.
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

#define MAX_LENGTH 400

int main(int argc, char* argv[]){
    int size; // initialize
    int count;
    FILE *in;
    FILE *out;
    char line[MAX_LENGTH];
    if (argc != 3) { // if the number of arguments is not 3
        printf("FindPath: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    in = fopen(argv[1], "r"); // set in to readable 
    out = fopen(argv[2], "w"); // set out to writeable 
    if (in == NULL) { // if in is NULL 
        printf("File %s could not be openedfor reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if (out == NULL) { // if out is NULL
        printf("File %s could not be opened for writing\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    fgets(line, MAX_LENGTH, in); // read in line 
    size = 0; // set size to 0 
    sscanf(line, "%d", &size);
    Graph G = newGraph(size); // create a new graph of size 0
    while (fgets(line, MAX_LENGTH, in) != NULL) { // while you can read the file
        int x = 0;
        int y = 0;
        sscanf(line, "%d %d", &x, &y); // read the formatted output
        if (x == 0 && y == 0) { // if x and y are 0 
            break;
        }
        addEdge(G, x, y);
    }
    printGraph(out, G);
    count = 0; // set count to 0 
    while (fgets(line, MAX_LENGTH, in) != NULL) { // while you can read the file
        int x = 0;
        int y = 0;
        sscanf(line, "%d %d", &x, &y);
        if(x == 0 && y == 0) { // if x and y are 0 
            break;
        }
        if(count++ != 0) { // if the incremented count does not equal 0
            fprintf(out, "\n"); // print to outfile
        }
        fprintf(out, "\n"); // print to outfile 
        BFS(G, x); // call BFS()
        int z = getDist(G, z); // set z to the distance
        fprintf(out, "The distance from %d to %d is ", x, y); // print out the distance
        if(z == INF) { // 
            fprintf(out, "infinity\n");
        }
        else {
            fprintf(out, "%d\n", z);
        }
        List N = newList(); // create a new list
        getPath(N, G, y); // get the path 
        if(front(N) == NIL) {
            fprintf(out, "The %d-%d path does not exist", x, y);
        }else {
            fprintf(out, "The shortest %d-%d path is: ", x, y);
            printList(out, N);
        }
        freeList(&N); // free the list 
    }
    fprintf(out, "\n"); // print to outfile 
    freeGraph(&G); // free the graph 
    fclose(in);
    fclose(out);
    return(0);
}
