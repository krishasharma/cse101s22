//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 8
// Order.cpp
//-----------------------------------------------------------------------------------------------
// Credit: Please Note, there was high level pusedocode collabration with my sister tvsharma
// (Twisha Sharma) during this assignment. The below code is also based off of Professor Tantalo's
// example code and pusedo-code provided on the class webpage.
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<fstream>
#include"Dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {
    ifstream input;
    ofstream output;
    string readLine;
    int numOfLines = 1;
    Dictionary D;
    if (argc != 3) {
        cerr << "ERROR: incorrect usage" << endl;
        return EXIT_FAILURE;
    }
    input.open(argv[1]);
    if (!input.is_open()) {
        cerr << "ERROR: cannot open file" << endl;
        return EXIT_FAILURE;
    }
    output.open(argv[2]);
    if (!output.is_open()) {
        cerr << "ERROR: cannot open file" << endl;
        return EXIT_FAILURE;
    }
    while (getline(input, readLine)) {
        D.setValue(readLine, numOfLines);
        numOfLines += 1;
    }
    output << D << endl << endl;
    output << D.pre_string() << endl;
    input.close();
    output.close();
    return EXIT_SUCCESS;
}
