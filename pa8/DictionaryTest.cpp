//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 8
// DictionaryTest.cpp
//-----------------------------------------------------------------------------------------------
// Credit: Please Note, there was high level pusedocode collabration with my sister tvsharma 
// (Twisha Sharma) during this assignment. The below code is also based off of Professor Tantalo's
// example code and pusedo-code provided on the class webpage.
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>
#include <assert.h>
#include "Dictionary.h"

using namespace std;

int main() {
    Dictionary D;
    Dictionary E;
    bool eq = true;
    string pink[] = {"blue", "red", "green", "purple"};
    for (int i = 0; i < 4; i++) {
        D.setValue(pink[i], i + 1);
        E.setValue(pink[i], i + 1);
    }
    eq = (E == D);
    eq = (D.size() == 4);
    eq = (D.contains("blue"));

    D.end();
    eq = (D.currentVal() == 4);
    eq = (D.currentKey() == "purple");
    D.begin();
    eq = (D.currentVal() == 1);
    eq = (D.currentKey() == "blue");
    eq = (D.getValue("blue") == 1);
    D.setValue("blue", 10);
    eq = (D.getValue("blue") == 10);
    D.remove("blue");
    eq = (D.size() == 3);

    D.clear();
    eq = (D.size() == 0);

    assert(eq == true);
}
