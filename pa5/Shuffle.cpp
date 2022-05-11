//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 5
// Shuffle.cpp
//------------------------------------------------------------------------------------------------------
// Credit: Please Note, there was high level pusedocode collabration with my sister tvsharma·
// (Twisha Sharma) during this assignment. The below code is also based off of Professor Tantalo's·
// example code and pusedo-code provided on the class webpage.
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<cassert>
#include<fstream>
#include"List.h"

using namespace std;

void shuffleList(List& L) {
    List X;
    List Y;
    List ListCopy;
    int len = L.length();
    int half = (len / 2);
    L.moveFront();

    for (int i = 0; i < half; i++) {
        X.insertBefore(L.peekNext());
        L.moveNext();
    }
    for (int i = half; i < len; i++) {
        Y.insertBefore(L.peekNext());
        L.moveNext();
    }
    X.moveFront();
    Y.moveFront();

    while (ListCopy.length() != L.length()) {
        if (Y.position() != Y.length()) {
            ListCopy.insertBefore(Y.peekNext());
            Y.moveNext();
        }
        if (X.position() != X.length()) {
            ListCopy.insertBefore(X.peekNext());
            X.moveNext();
        }
    }
    L = ListCopy;
}

int main(int argc, char * argv[]){
    if(argc != 2){
        std::cerr << "Usage: " << argv[0] << "  <number>" << std::endl;
        return(EXIT_FAILURE);
    }
    int n = atoi(argv[1]);
    std::cout << "deck size       shuffle count" << std::endl;
    std::cout << "------------------------------" << std::endl;
    List X, Y;
    int iter;
    for (int i = 0; i < n; i++){
        int count = i + 1;
        iter = 0;
        for (int e = 0; e < count ; e++){
            X.insertBefore(e);
            Y.insertBefore(e);
        }
        shuffleList(X);
        iter++;
        while(!(X == Y)){
            shuffleList(X);
            iter ++;
        }
        printf("%d               %d\n", i + 1, iter);
        X.clear();
        Y.clear();
    }
    return (EXIT_SUCCESS);
}
