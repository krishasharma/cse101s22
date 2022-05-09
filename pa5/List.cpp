//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 5
// List.cpp
//------------------------------------------------------------------------------------------------------
// Credit: Please Note, there was high level pusedocode collabration with my sister tvsharma·
// (Twisha Sharma) during this assignment. The below code is also based off of Professor Tantalo's·
// example code and pusedo-code provided on the class webpage.
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

// *** Private Constructor *** --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
}


// *** Class Constructors & Destructors *** -------------------------------------------

// Creates a new List in the empty state.
List::List(){
   front = nullptr;
   back = nullptr;
   length = 0;
}

// Copy constructor.
List(const List& L) {
    
}

// Destructor
~List();


// *** Access functions *** --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
    if (length <= 0) {
        throw std::length_error("List: Length(): length of list is less than or equal to 0");
    }
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
    if (length <= 0) {
        throw std::length_error("List: Front(): length of list is less than or equal to 0");
    }
    return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
    if (length <= 0) {
        throw std::length_error("List: Back(): length of list is less than or equal to 0");
    }
    return frontDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
    if (length <= 0) {
        throw std::range_error("List: Position(): range of list is out of range");
    }
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
    if (pos_cursor > num_elements) {
        throw std::range_error("List: peekNext(): trying to peekNext when cursor is out of list range");
    }
    return afterCursor->next->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
    if (pos_cursor > num_elements) {
        throw std::range_error("List: peekPrev(): trying to peekPrev when cursor is out of list range");
    }
    return beforeCursor->prev->data;
}


// *** Manipulation procedures *** -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    if (length <= 0) {
        throw std::length_error("List: clear(): calling clear on a List that does not exist");
    } else {
        num_elements = 0;
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
    pos_cursor = 0;
    //frontDummy->next = frontDummy;
    beforeCursor = frontDummy->next;
    //return frontDummy;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
    pos_cursor = length;
    //backDummy->prev = backDummy;
    afterCursor = backDummy->prev;
    //return backDummy;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext() {
    if (pos_cursor >= num_elements) {
        throw std::range_error("List: moveNext(): calling moveLength on a List out of range");
    } else {
        pos_cursor += 1;
        beforeCursor = beforeCursor->next;
        afterCursor = afterCursor->next;
        return beforeCursor->data;
    }
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev() {
    if (pos_cursor >= num_elements) {
        throw std::range_error("List: movePrev(): calling moveLength on a List out of range");
    } else {
        pos_cursor -= 1;
        beforeCursor = beforeCursor->prev;
        afterCursor = afterCursor->perv;
        return afterCursor->data;
    }
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
    Node *N = new Node(x);
    if (num_elements <= 0 || pos_cursor < 0) {
        throw std::range_error("List: insertAfter(): calling insertAfter on a List out of range");
    } else {
        N->next = afterCursor;
        N->prev = beforeCursor;
        beforeCursor->next = N;
        afterCursor->prev = N;
        num_elements += 1;
    }
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
    Node *N = new Node(x);
    if (num_elements <= 0 || pos_cursor < 0) {
        throw std::range_error("List: insertBefore(): calling insertBefore on a List out of range");
    } else {
        N->prev = afterCursor;
        N->next = beforeCursor;
        beforeCursor->prev = N;
        afterCursor->next = N;
        num_elements += 1;
        beforeCursor = N;
    }
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
    if (pos_cursor >= num_elements) {
        throw std::range_error("List: setAfter(): calling setAfter on a List out of range");
    } else {
        afterCursor->data = x;
    }
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
    if (pos_cursor <= 0) {
        throw std::range_error("List: setBefore(): calling setBefore on a List out of range");
    } else {
        beforeCursor->data = x;
    }
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
    //Node *N = new Node(x);
    Node *N = afterCursor->next;
    if (pos_cursor >= num_elements) {
        throw std::range_error("List: eraseAfter(): calling eraseAfter on a List out of range");
    } else {
        afterCursor->data = 0; // KAI CHANGE THIS!!! (should not be set to 0)
    }
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
    //Node *N = new Node(x);
    Node *N = afterCursor
    if (pos_cursor >= num_elements) {
        throw std::range_error("List: eraseAfter(): calling eraseAfter on a List out of range");
    } else {
        beforeCursor->data = 0; // KAI CHANGE THIS!!!! (should not be set to 0)
    }
}


// *** Other Functions *** ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x) {
    /*
    // WHILE LOOP?
    // search for the first occurance of x in list linearly
    if (!x) {
        // place cursor at position length()
        int val = -1;
        return val;
    } else {
        // place cursor after the found element
        // return the final cursor position
    }
    */
    for (int i = 0; i <= num_elements; i++) {
        if (afterCursor->data == x) {
            moveNext; 
            return pos_cursor;
        }
        moveNext;
    }
    if (afterCursor->data != x) {
        moveBack;
        return -1;
    }
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x) {
    /*
    // WHILE LOOP? 
    // search for the  first occurance of x in the list linearly
    if (!x) {
        // place cursor at position 0 
        int val = -1;
        return val;
    } else {
        // place cursor before found element 
        // return the final cursor position
    }
    */
    for (int i = 0; i <= num_elements; i++) {
        if (beforeCursor->data == x) {
            moveBack;·
            return pos_cursor;
        }   
        moveBack;
    }
    if (beforeCursor->data != x) {
        moveNext;
        return -1;
    }

}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
    for (int i = 0; i <= num_elements; i++) {
        for (int e = 0; ; e++) {
            
        }
        delete afterCursor->data;
        moveNext;
    }
    
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const;

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    Node *N = nullptr; 
    std::string s = "";
    for (N = front; N != nullptr; N = N->next) {
        s += std::to_string(N->data)+" "; // what does this line do; prof'd queue.cpp
    }
    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
    bool eq = false;
    Node *N = nullptr;
    Node *M = nullptr;
    eq = (this?->length == Q.length);
    N = this
}


// *** Overriden Operators *** -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
friend std::ostream& operator<<( std::ostream& stream, const List& L );

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
friend bool operator==( const List& A, const List& B );

// operator=()
// Overwrites the state of this List with state of L.
List& operator=( const List& L );
