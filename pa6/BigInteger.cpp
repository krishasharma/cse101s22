//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 6
// BigInteger.cpp
//-------------------------------------------------------------------------------------------------
// Credit: Please Note, there was high level pusedocode collabration with my sister tvsharma·
// (Twisha Sharma) during this assignment. The below code is also based off of Professor Tantalo's·
// example code and pusedo-code provided on the class webpage.
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"
#include "BigInteger.h"

#define power 9
#define base 1000000000

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
    signum = 0;
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
    if (s == "") {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }else{
        std::size_t find = s.find_first_not_of("+-0123456789"); // searches for the first instance
        if (find != std::string::npos) {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
        if (s[0] == '-') { // set the signum value based on sign 
            signum = -1;
        }
        if (s[0] == 0) {
            signum = 0;
            return;
        }
        else {
            signum = 1;
        }
        std::string empty = "";
        size_t rem = s.length() % power; // remainder of mod of len and power
        for (size_t i = 0; i < s.length(); i = i) { // iterate through the string
            if (digits.length() == 0) {
                empty = s.substr(i, rem);
                long convert = std::stol(empty);
                digits.insertBefore(convert);
                i += rem;
            }
            empty = s.substr(i, power);
            long convert = std::stol(empty); // convert each index to a long
            digits.insertBefore(convert);
            // std::s.length(); // returns lenght of string
            i += power;
        }
        //std::cout << digits << std::endl;
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
    digits = N.digits;
    signum = N.signum;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const {
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
    //int greaterThan = 1;
    //int lessThan = -1;
    //int equalTo = 0;
    if (signum != N.signum) { // if the signs arent the same 
        if (signum > N.signum) { // if the BI sig is pos 
            return 1; // BI is greater than N 
        }
        if (signum < N.signum) { // if the N sig is pos 
            return -1; // BI is less than N 
        }
    }
    if (digits.length() != N.digits.length()) { // if the length's are not the same
        if (digits.length() > N.digits.length()) { // if BI length is bigger than N 
            if (signum == -1) { // if BI is negative but longer 
                return -1; // BI is less than N
            } else {
                return 1; // BI is greater than N
            }
        }
        if (digits.length() < N.digits.length()) { // if BI length is less than N
            if (N.signum == -1) { // if BI is negative but longer·
                return 1; // BI is greater than N
            } else {
                return -1; // BI is less than N
            }
        }
    }
    for (int x = 0; x <= digits.length(); x++) {
        for (int y = 0; y <= N.digits.length(); y++) {
            if (x > y) {
                return 1;
            }
            else if (x < y) {
                return -1;
            }
        }
    }
    return 0;
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    digits.moveFront(); // go to the front 
    digits.moveNext(); // move to next element
    digits.eraseBefore(); // erase the front 
    for (int i = 0; i < digits.length(); i++) { // iterate through the List
        digits.moveNext(); // move to next List element 
        digits.eraseAfter(); // erase the one that was passed over 
    }
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
    if (signum != 0) { // if int is not 0 
        if (signum == 1) { // if sign is positive
            signum = -1; // change to negative
        }
        if (signum == -1) { // if sign is negative
            signum = 1; // change to positive
        }
    }
    return;
}


// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& res, List A, List B, int sgn) {
    A.moveBack();
    B.moveBack();
    ListElement x;
    ListElement y;
    ListElement z;
    while (A.position() > 0 || B.position() > 0) { // parse through the longest list
        if (sgn == 1) {
            if (A.position() == 0) {
                z = B.movePrev();
            }
            else if (B.position() == 0) {
                z = A.movePrev();
            }
            else {
                x = A.movePrev();
                y = B.movePrev();
                z = x + y;
            }
            res.insertAfter(z);
        }
        else if (sgn == -1) {
            if (A.position() == 0) {
                z = B.movePrev();
                z = -z;
            }
            else if (B.position() == 0) {
                z = A.movePrev();
            }
            else {
                x = A.movePrev();
                y = B.movePrev();
                z = x - y;
            }
            res.insertAfter(z);
        }
    }
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
void normalizeList(List& L) {
    int x = 0;
    int y = 0;
    bool carryOver = false;
    List newList;
    L.moveBack();
    for (int i = L.length(); i != ((L.length() - 1) % power); i--) {
        x = L.movePrev();
        if (carryOver == true) {
            y = x / base;
            x += y;
            carryOver = false;
        }
        if (x > base) {
            x = x % base;
            carryOver = true;
        }
        newList.insertAfter(x);
    }
    if (y > 0) {
        newList.insertAfter(y);
    }
}

// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger M;
    BigInteger C = *this;
    BigInteger NC = N;
    bool check = false;
    bool Ncheck = false;
    C.digits = this->digits;
    NC.digits = N.digits;
    C.signum = this->signum;
    NC.signum = N.signum;
    if (NC.signum == C.signum) {
        M.signum = C.signum;
    }
    else {
        if (C.signum < NC.signum) { 
            C.negate();
            check = true;
        }
        else if (C.signum > NC.signum) {
            NC.negate();
            Ncheck = true;
        }
        if (C < NC) {
            M.signum = NC.signum;
        }
        else if (C > NC) {
            M.signum = C.signum;
        }
        else {
            M.signum = 0;
            return M;
        }
        if (check == true) {
            C.negate();
            check = false;
        }
        else if (Ncheck == true) {
            NC.negate();
            Ncheck = false;
        }
    }
    List sum;
    sumList(sum, C.digits, NC.digits, 1);
    normalizeList(sum);
    M.digits = sum;
    return M;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
    return N;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
    return N;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
    std::string s;
    std::string holder = "";
    std::string zero = "";
    std::string holder2 = "";
    digits.moveFront();
    if (signum == -1) {
        s += '-';
    }
    for (int i = 1; i <= power; i++) {
        zero += "0";
    }
    while (digits.position() != digits.length()) {
        ListElement pass = digits.moveNext();
        if (pass == 0 && digits.position() != 1) {
            s += zero;
            continue;
        }
        holder = std::to_string(pass); // converts from long to string 
        if (holder.length() < power && digits.position() != 1) {
            for (size_t i = 0; i < power - holder.length(); i++) {
                holder2 += "0";
            }
            s += holder2;
        }
        //ListElement num = digits.moveNext();
        s += std::to_string(pass);
    }
    return s;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 0) {
        return true;
    }
    return false;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == -1) {
        return true;
    }
    return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == -1 || A.compare(B) == 0) {
        return true;
    }
    return false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 1) {
        return true;
    }
    return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 1 || A.compare(B) == 0) {
        return true;
    }
    return false;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    A = A.mult(B);
    return A;
}
