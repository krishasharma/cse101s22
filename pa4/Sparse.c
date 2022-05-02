//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 4
// Sparse.c
//------------------------------------------------------------------------------------------------------
// Credit: Please Note, there was high level pusedocode collabration with my sister tvsharma 
// (Twisha Sharma) during this assignment. The below code is also based off of Professor Tantalo's 
// example code and pusedo-code provided on the class webpage.
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "List.h"

int main(int argc, char *argv[]) {
    int x, y, z, a, b;
    double c; 
    Matrix C, D, E, F, G, H, I, J;

    if (argv[1] == NULL) {
        fprintf(stderr, "MAIN ERROR: program Sparse.c needs more input arguments");
        exit(EXIT_FAILURE);
    }
    if (argv[2] == NULL) {
        fprintf(stderr, "MAIN ERROR: program Sparse.c was given too many arguments");  
        exit(EXIT_FAILURE);
    }

    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    fscanf(in, "%d %d %d\n", &x, &y, &z);
    Matrix A = newMatrix(x);
    Matrix B = newMatrix(x);

    for (int i = 1; i <= y; i++) {
        fscanf(in, "%d %d %lf\n", &a, &b, &c);
        changeEntry(A, a, b, c);
    }
    for (int i = 1; i <= z; i++) {
        fscanf(in, "%d %d %lf\n", &a, &b, &c);
        changeEntry(B, a, b, c);
    }

    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");

    fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);
    fprintf(out, "\n");

    fprintf(out, "(1.5)*A =\n");
    C = scalarMult(1.5, A);
    printMatrix(out, C);
    fprintf(out, "\n");

    fprintf(out, "A+B =\n");
    D = sum(A, B);
    printMatrix(out, D);
    fprintf(out, "\n");

    fprintf(out, "A+A =\n");
    E = sum(A, A);
    printMatrix(out, E);
    fprintf(out, "\n");

    fprintf(out, "B-A =\n");
    F = diff(B, A);
    printMatrix(out, F);
    fprintf(out, "\n");

    fprintf(out, "A-A =\n");
    G = diff(A, A);
    printMatrix(out, G);
    fprintf(out, "\n");

    fprintf(out, "Transpose(A) =\n");
    H = transpose(A);
    printMatrix(out, H);
    fprintf(out, "\n");

    fprintf(out, "A*B =\n");
    I = product(A, B);
    printMatrix(out, I);
    fprintf(out, "\n");

    fprintf(out, "B*B =\n");
    J = product(B, B);
    printMatrix(out, J);
    fprintf(out, "\n");

    fclose(in);
    fclose(out);
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);
    return 0;
}
