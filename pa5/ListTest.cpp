//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 5
// ListTest.cpp
//------------------------------------------------------------------------------------------------------
// Credit: Please Note, there was high level pusedocode collabration with my sister tvsharma·
// (Twisha Sharma) during this assignment. The below code is also based off of Professor Tantalo's·
// example code and pusedo-code provided on the class webpage.
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<stdexcept>
#include<cassert>
#include"List.h"

using namespace std;

int main(){
    int i;
    int n = 10;
    List A;
    List B;
    List C;
    List D;
    List X;

    for(i = 1; i <= n; i++){
       A.insertAfter(i); // insertAfter check 
       B.insertAfter(11-i);
       C.insertBefore(i); // insertBefore check
       D.insertBefore(11-i);
    }

    assert(A.front() == 10); // front check 

    assert(A.back() == 0); // back check

    assert(B.position() == 0); // position check 

    A.moveFront(); // moveFront check

    assert(A.position() == 0);

    A.moveBack(); // moveBack check

    assert(A.position() == A.length()); // length check

    A.setAfter(2); // setAfter check 

    assert(A.peekNext() == 2); // peekNext check

    A.eraseAfter(); // eraseAfter check

    assert(A.peekNext() != 2);

    B.moveNext();

    B.moveNext();

    B.setBefore(3); // setBefore check 

    assert(B.peekPrev() == 3); // peekPrev check

    B.eraseBefore(); // eraseBefore check

    assert(B.peekPrev() != 3);

    A.cleanup(); // cleanup check

    List F = A.concat(B); // concat check

    assert(F.length() == (A.length() + B.length()));

    A.to_string(); // to_string check

    assert(C.equals(D)); // equals check 

    X.moveFront();

    X.peekPrev();

    X.movePrev();

    X.setBefore(5);

    X.eraseBefore();

    X.moveBack();

    X.peekNext();

    X.moveNext();

    X.setAfter(5);

    X.eraseAfter();

    X.clear();

    X.front();

    X.back();

    return(EXIT_SUCCESS);
}
