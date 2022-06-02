//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 8
// WordFrequency.cpp
//-----------------------------------------------------------------------------------------------
// Credit: Please Note, there was high level pusedocode collabration with my sister tvsharma·
// (Twisha Sharma) during this assignment. The below code is also based off of Professor Tantalo's
// example code and pusedo-code provided on the class webpage.
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<fstream>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {
    ifstream infile;
    ofstream outfile;
    Dictionary D;
    size_t begin = 0;
    size_t end = 0;
    size_t len = 0;
    int val = 0;
    string line = "";
    string token = "";
    string delim = " \t\"',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    if (argc != 3) {
        cerr << "ERROR: incorrect usage" << endl;
        return EXIT_FAILURE;
    }
    infile.open(argv[1]);
    if (!infile.is_open()) {
        cerr << "ERROR: cannot open file" << endl;
        return EXIT_FAILURE;
    }
    outfile.open(argv[2]);
    if (!outfile.is_open()) {
        cerr << "ERROR: cannot open file" << endl;
        return EXIT_FAILURE;
    }
    while (getline(infile, line)) {
        len = line.length();
        begin = min(line.find_first_not_of(delim, 0), len);
        end = min(line.find_first_of(delim, begin), len);
        token = line.substr(begin, end-begin);
        while (token != "") {
            // lowercase the token
            for (size_t i = 0; i < token.length(); i++) {
                token[i] = tolower(token[i]);
            }
            if (D.contains(token) == true) {
                // do something;
                val = D.getValue(token); // grab the value of the string
                val += 1; // increment the value
                D.setValue(token, val); // set the value
            } else {
                // do something;
                D.setValue(token, 1);
            }
            begin = min(line.find_first_not_of(delim, end + 1),len);
            end = min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, end-begin);
        }
    }
    outfile << D << endl << endl;
    infile.close();
    outfile.close();
    return EXIT_SUCCESS;
}
