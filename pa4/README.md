## Programing Assignment 4: Matrix Calculator

## Short Description
    In this assignment you will create a calculator for performing matrix operations that exploits the (expected) sparseness of its matrix operands. An 𝑛 × 𝑛 square matrix is said to be sparse if the number of non-zero entries (here abbreviated NNZ) is small compared to the total number of entries 𝑛2. The result will be a C program capable of performing fast matrix operations, even on very large matrices, provided they are sparse. 

## Build 
        To build the main program manually, type "clang -Wall -Wextra -Werror -Wpedantic -o Sparse Sparse.c” into command line

## Files
        The following files have been submitted:
        Sparse.c
        Matrix.h
        Matrix.c
        MatrixTest.c
        List.c
        List.h
        ListTest.c
        Makefile
        README.md

## Errors
        This code currently has no known errors.

## Cleaning
        make clean
        To clean the program manually, type "rm -f *.o Sparse Matrix List MatrixTest ListTest" into command line. 

## Notes
        Please note that there was high level pusedocode collabration with my sister Twisha Sharma (tvsharma) during this assignment. The assignment code is also based off of Professor Tantalo's example code and pusedo-code provided on the class webpage as well as during class lecture.
