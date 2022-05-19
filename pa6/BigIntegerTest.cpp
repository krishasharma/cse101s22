//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 6
// BigInteger.cpp
//-------------------------------------------------------------------------------------------
// Credit: Please Note, there was high level pusedocode collabration with my sister tvsharma·
// (Twisha Sharma) during this assignment. The below code is also based off of Professor Tanta        lo's·
// example code and pusedo-code provided on the class webpage.
//-------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstddef>
#include "List.h"
#include "BigInteger.h"

using namespace std;

int main() {
    BigInteger b = BigInteger("12345");
    BigInteger a = BigInteger("54321");
    int c = b.compare(a);
    return c;
}
