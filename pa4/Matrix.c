//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 4
// Matrix.c
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

// ** structs ** --------------------------------------------------------------------------------------------
// private EntryObj type
typedef struct EntryObj *Entry;

typedef struct EntryObj{
    double data;
    int cols;
} EntryObj;

// private MatrixObj type
typedef struct MatrixObj{
    List *array; 
    int size; 
    int NNZ; 
} MatrixObj;

// ** Constructors-Destructors ** ---------------------------------------------------------------------------
// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
    Matrix M = calloc(1, sizeof(MatrixObj));
    M->array = calloc(n + 1, sizeof(List));
    M->size = n;
    M->NNZ = 0; // initialize at 0! 
    for (int i = 1; i<= n; i++) {
        M->array[i] = newList();
    }
    return M;
}

Entry newEntry(double data, int cols) {
    Entry Obj = calloc(1, sizeof(EntryObj));
    Obj->cols = cols;
    Obj->data = data;
    return Obj;
}

void freeEntry(Entry* pE) {
    if ((*pE) != NULL && pE != NULL) {
        free((*pE));
        (*pE) = NULL;
    }
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
    if ((*pM) != NULL && pM != NULL) {
        makeZero(*pM);
        for (int i = 1; i <= size(*pM); i++) {
            freeList(&(*pM)->array[i]);
        }
        free((*pM)->array); // free whats inside
        (*pM)->array = NULL;
        free((*pM)); // free the array 
        (*pM) = NULL;
    }
}

// ** Access functions ** ----------------------------------------------------------------------------------
// size()
// Return the size of square Matrix M.
int size(Matrix M) {
    return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
    return M->NNZ;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        return 0;
    }
    if (A->NNZ != B->NNZ) {
        return 0;
    }
    if (A == B) { // if the mem address are the same (meaning that the matrices are identical) 
        return 1;
    }
    for (int i = 1; i <= size(A); i++){
        if (length(A->array[i]) != length(B->array[i])) {
            return 0;
        }
        moveFront(A->array[i]);
        moveFront(B->array[i]);
        while (index(A->array[i]) >= 0 && index(B->array[i]) >= 0) {
            Entry C = (Entry) get(A->array[i]);
            Entry D = (Entry) get(B->array[i]);
            if (C->cols != D->cols || C->data != D->data) {
                return 0;
            }
            moveNext(A->array[i]);
            moveNext(B->array[i]);
        }
    }
    return 1;
}

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
    for (int i = 1; i <= size(M); i++) {
        moveFront(M->array[i]);
        while (index(M->array[i]) >= 0) {
            Entry N = (Entry) get(M->array[i]);
            freeEntry(&N);
            moveNext(M->array[i]);
        }
        clear(M->array[i]);
    }
    M->NNZ = 0;
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
    if (i > size(M) || 1 > i || j > size(M) || 1 > i) {
        printf("ENTRY ERROR: calling changeEntry() on an entry outside the given range\n.");
        exit(EXIT_FAILURE);
    }
    if (length(M->array[i]) <= 0 && x == 0) {
        return;
    }
    moveFront(M->array[i]);
    while (index(M->array[i]) >= 0) {
        Entry X = (Entry) get(M->array[i]); 
        if (X->cols == j && x == 0) {
            freeEntry(&X);
            delete(M->array[i]);
            M->NNZ --;
            return;
        }
        if (X->cols > j) {
            Entry E = newEntry(x, j);
            insertBefore(M->array[i], E);
            M->NNZ ++;
            return;
        }
        if (x != 0 && X->cols == j) {
            X->data = x;
            return;
        }
        moveNext(M->array[i]);
    }
    if (x != 0) {
    Entry E = newEntry(x, j);
    append(M->array[i], E);
    M->NNZ ++;
    return;
    }
}

// ** Arithemetic functions ** ---------------------------------------------------------------------------
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
    Matrix B = newMatrix(size(A));
    for (int i = 1; i <= size(A); i++) {
        moveFront(A->array[i]);
        while (index(A->array[i]) >= 0) {
            Entry N = (Entry) get(A->array[i]);
            changeEntry(B, i, N->cols, N->data);
            moveNext(A->array[i]);
        }
    }
    return B;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
    Matrix B = newMatrix(size(A));
    for (int i = 1; i <= size(A); i++) {
        moveFront(A->array[i]);
        while (index(A->array[i]) >= 0) {
            Entry N = (Entry) get(A->array[i]);
            changeEntry(B, N->cols, i, N->data); // flip rows and cols 
            moveNext(A->array[i]);
        }
    }
    return B;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
    Matrix B = newMatrix(size(A));
    if (x == 0) {
        return B;
    }
    for (int i = 1; i <= size(A); i++) {
        moveFront(A->array[i]);
        while (index(A->array[i]) >= 0) {
            Entry N = (Entry) get(A->array[i]);
            changeEntry(B, i, N->cols, N->data * x); // scalar 
            moveNext(A->array[i]);
        }
    }
    return B;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
    if (A == B) {
        Matrix M = scalarMult(2, A);
        return M;
    }
    Matrix N = newMatrix(size(A));
    for (int i = 1; i <= size(A); i++) {
        moveFront(A->array[i]);
        moveFront(B->array[i]);
        while (index(A->array[i]) >= 0 && index(B->array[i]) >= 0) {
            Entry AE = (Entry) get(A->array[i]);
            Entry BE = (Entry) get(B->array[i]);
            if (AE->cols > BE->cols) {
                changeEntry(N, i, BE->cols, BE->data);
                moveNext(B->array[i]);
            }
            if (AE->cols < BE->cols) {
                changeEntry(N, i, AE->cols, AE->data);
                moveNext(A->array[i]);
            }
            if (AE->cols == BE->cols) {
                double temp = AE->data + BE->data;
                changeEntry(N, i, AE->cols, temp);
                moveNext(A->array[i]);
                moveNext(B->array[i]);
            }
        }
        while (index(A->array[i]) >= 0 && index(B->array[i]) < 0) {
            Entry AE = (Entry) get(A->array[i]);
            changeEntry(N, i, AE->cols, AE->data);
            moveNext(A->array[i]);
        }
        while (index(A->array[i]) < 0 && index(B->array[i]) >= 0) {
            Entry BE = (Entry) get(B->array[i]);
            changeEntry(N, i, BE->cols, BE->data);
            moveNext(B->array[i]);
        }
    }
    return N;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        fprintf(stderr, "error\n"); // finish this
        exit(EXIT_FAILURE);
    }

    Matrix N = newMatrix(size(A));
    for (int i = 1; i <= size(A); i++) {
        moveFront(A->array[i]);
        moveFront(B->array[i]);
        while (index(A->array[i]) >= 0 && index(B->array[i]) >= 0) {
            Entry AE = (Entry) get(A->array[i]);
            Entry BE = (Entry) get(B->array[i]);
            if (AE->cols > BE->cols) {
                changeEntry(N, i, BE->cols, -BE->data);
                moveNext(B->array[i]);
            }
            else if (AE->cols < BE->cols) {
                changeEntry(N, i, AE->cols, AE->data);
                moveNext(A->array[i]);
            } else {
                double temp = AE->data - BE->data;
                if (temp != 0) {
                    changeEntry(N, i, AE->cols, temp);
                }
                moveNext(A->array[i]);
                moveNext(B->array[i]);
            }
        }
        while (index(A->array[i]) >= 0 && index(B->array[i]) < 0) {
            Entry AE = (Entry) get(A->array[i]);
            changeEntry(N, i, AE->cols, AE->data);
            moveNext(A->array[i]);
        }
        while (index(A->array[i]) < 0 && index(B->array[i]) >= 0) {
            Entry BE = (Entry) get(B->array[i]);
            changeEntry(N, i, BE->cols, -BE->data);
            moveNext(B->array[i]);
        }
    }
    return N;
}

double dotProduct(List A, List B) {
    moveFront(A);
    moveFront(B);
    double val = 0;
    while (index(A) >= 0 && index(B) >= 0) {
        Entry AE = (Entry) get(A);
        Entry BE = (Entry) get(B);
        if (AE->cols > BE->cols) {
            moveNext(B);
            continue;
        }
        if (AE->cols < BE->cols) {
            moveNext(A);
            continue;
        }
        if (AE->cols == BE->cols) {
            val += AE->data * BE->data;
            moveNext(A);
            moveNext(B);
        }
    }
    return val;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        printf("PRODUCT ERROR: calling product() when size is not the same\n.");
        exit(EXIT_FAILURE);
    }
    double temp = 0;
    Matrix N = newMatrix(size(A));
    Matrix BT = transpose(B);
    for (int i = 1; i <= size(A); i++) {
        if (length(A->array[i]) > 0) {
            for (int e = 1; e <= size(BT); e++) {
                if (length(BT->array[e]) > 0) {
                    temp = dotProduct(A->array[i], BT->array[e]);
                    if (temp != 0) {
                        changeEntry(N, i, e, temp);
                    }
                }
            }
        }
    }
    return N;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
    for (int i = 1; i <= size(M); i++) {
        moveFront(M->array[i]);
        if(length(M->array[i]) <= 0) {
            continue;
        }
        fprintf(out, "%d: ", i);
        while (index(M->array[i]) >= 0) {
            Entry N = get(M->array[i]);
            fprintf(out, "(%d, %.1f) ", N->cols, N->data);
            moveNext(M->array[i]);
        }
        fprintf(out, "\n");
    }
}
