//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 4
// MatrixTest.c
//------------------------------------------------------------------------------------------------------
// Credit: Please Note, there was high level pusedocode collabration with my sister tvsharma·
// (Twisha Sharma) during this assignment. The below code is also based off of Professor Tantalo's·
// example code and pusedo-code provided on the class webpage.
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"

int main(){
    int n=100;
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    Matrix C, D, E, F, G, H;

    printf("----------changeEntry() test----------\n");
    changeEntry(A, 1,1,1);
    changeEntry(B, 1,1,1);
    changeEntry(A, 1,2,2);
    changeEntry(B, 1,2,0);
    changeEntry(A, 1,3,3);
    changeEntry(B, 1,3,1);
    changeEntry(A, 2,1,4);
    changeEntry(B, 2,1,0);

    printf("----------printMatrix() test----------\n");
    printf("%d\n", NNZ(A));
    printMatrix(stdout, A);
    printf("\n");

    printf("%d\n", NNZ(B));
    printMatrix(stdout, B);
    printf("\n");

    printf("----------scalarMult() test----------\n");
    C = scalarMult(1.5, A);
    printf("%d\n", NNZ(C));
    printMatrix(stdout, C);
    printf("\n");

    printf("----------sum() test----------\n");
    D = sum(A, B);
    printf("%d\n", NNZ(D));
    printMatrix(stdout, D);
    printf("\n");

    printf("----------diff() test----------\n");
    E = diff(A, A);
    printf("%d\n", NNZ(E));
    printMatrix(stdout, E);
    printf("\n");

    printf("----------transpose() test----------\n");
    F = transpose(B);
    printf("%d\n", NNZ(F));
    printMatrix(stdout, F);
    printf("\n");

    printf("----------product() test----------\n");
    G = product(B, B);
    printf("%d\n", NNZ(G));
    printMatrix(stdout, G);
    printf("\n");

    printf("----------copy() test----------\n");
    H = copy(A);
    printf("%d\n", NNZ(H));
    printMatrix(stdout, H);
    printf("\n");

    printf("---------equals() test----------\n");
    printf("%s\n", equals(A, H)?"true":"false" );

    printf("----------makeZero() test----------\n");
    makeZero(A);
    printf("%d\n", NNZ(A));
    printMatrix(stdout, A);

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);

    return EXIT_SUCCESS;
}

/*
Output of this program:
9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0)
3: (1, 1.0) (2, 1.0) (3, 1.0)

9
1: (1, 1.5) (2, 3.0) (3, 4.5)
2: (1, 6.0) (2, 7.5) (3, 9.0)
3: (1, 10.5) (2, 12.0) (3, 13.5)

9
1: (1, 2.0) (2, 2.0) (3, 4.0)
2: (1, 4.0) (2, 6.0) (3, 6.0)
3: (1, 8.0) (2, 9.0) (3, 10.0)

0

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0) (3, 1.0)
3: (1, 1.0) (3, 1.0)

7
1: (1, 2.0) (2, 1.0) (3, 2.0)
2: (2, 1.0)
3: (1, 2.0) (2, 2.0) (3, 2.0)

9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

true
false
true
0
*/
