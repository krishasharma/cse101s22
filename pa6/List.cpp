//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 6
// List.cpp
//------------------------------------------------------------------------------------------------------
// Credit: Please Note, there was high level pusedocode collabration with my sister tvsharma·
// (Twisha Sharma) during this assignment. The below code is also based off of Professor Tantalo's·
// example code and pusedo-code provided on the class webpage.
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<cassert>
#include<stdexcept> 
#include"List.h"

#define NUM -50

// *** Private Constructor *** --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
    data = x;
    next = nullptr;
    prev = nullptr;
}


// *** Class Constructors & Destructors *** -------------------------------------------

// Creates a new List in the empty state.
List::List(){
    frontDummy = new Node(NUM);
    backDummy = new Node(NUM);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}


// Copy constructor.
List::List(const List& L) {
    // make this an empty list
    frontDummy = new Node(NUM);
    backDummy = new Node(NUM);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    num_elements = 0;
    pos_cursor = 0;
    Node *X = L.frontDummy->next;
    while (X != L.backDummy) {
        this->insertBefore(X->data);
        X = X->next;
    }
    frontDummy->prev = nullptr;
    backDummy->next = nullptr;
}

// Destructor
List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}


// *** Access functions *** --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
    if (num_elements <= 0) {
        throw std::length_error("List: Front(): length of list is less than or equal to 0");
    }
    return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
    if (num_elements <= 0) {
        throw std::length_error("List: Back(): length of list is less than or equal to 0");
    }
    return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
    if (pos_cursor >= num_elements) {
        throw std::range_error("List: peekNext(): trying to peekNext when cursor is out of list range");
    }
    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
    if (pos_cursor < 0) {
        throw std::range_error("List: peekPrev(): trying to peekPrev when cursor is out of list range");
    }
    return beforeCursor->data;
}


// *** Manipulation procedures *** -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    moveFront();
    while (num_elements > 0) {
        eraseAfter();
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
    pos_cursor = num_elements;
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext() {
    if (position() >= length()) {
        throw std::range_error("List: moveNext(): calling moveNext on a List out of range");
    }
    pos_cursor += 1;
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev() {
    if (position() <= 0) {
        throw std::range_error("List: movePrev(): calling movePrev on a List out of range");
    }
    pos_cursor -= 1;
    afterCursor = afterCursor->prev;
    beforeCursor = beforeCursor->prev;
    return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
    Node *N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    afterCursor = N;
    num_elements += 1;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
    Node *N = new Node(x);
    N->prev = beforeCursor;
    N->next = afterCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    beforeCursor = N;
    num_elements += 1;
    pos_cursor += 1;
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
    Node *N = nullptr;
    if (!(length() > position())) {
        throw std::range_error("List: eraseAfter(): calling eraseAfter on a List out of range");
    }
    N = afterCursor;
    afterCursor = afterCursor->next;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;
    num_elements -= 1;
    delete N;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
    //Node *N = new Node(x);
    Node *N = nullptr;
    if (pos_cursor <= 0) {
        throw std::range_error("List: eraseBefore(): calling eraseBefore on a List out of range");
    }
    N = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    num_elements -= 1;
    pos_cursor -= 1;
    delete N;
}


// *** Other Functions *** ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x) {
    while (afterCursor != backDummy) {
        if (afterCursor->data == x) {
            moveNext();
            return pos_cursor;
        }
        moveNext();
    }
    moveBack();
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x) {
    while (beforeCursor != frontDummy) {
        if (beforeCursor->data == x) {
            movePrev();
            return pos_cursor;
        }
        movePrev();
    }
    moveFront();
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
    // make a node to keep track of the index frontDummy->next
    // use the cursor to itterate through the rest of the list to check for duplicates
    // keep track of cursor and before and after cursor's and then call moveFront()

    if (length() <= 1) {
        return;
    }

    //int cursorCopy = pos_cursor; // pos_cursor COPY
    //Node *bfC = beforeCursor; // before cursor copy
    //Node *afC = afterCursor;
    //Node *ind = nullptr;
    //int x = 0;
    //moveFront();
    //moveNext();
    //for (ind = frontDummy->next; ind != backDummy; ind = ind->next) {
    //    while (findNext(ind->data) != -1 && position() != length()) {
    //        if (beforeCursor == bfC) {
    //            bfC = bfC->prev;
    //        }
    //        if (beforeCursor == afC) {
    //            afC = afC->prev;
    //        }
    //        eraseBefore();
    //        if (cursorCopy > pos_cursor) {
    //            cursorCopy -= 1;
    //        }
    //    }

    //    if (position() == length() && beforeCursor->data == ind->data) {
    //        if (beforeCursor == bfC) {
    //            bfC = bfC->prev;
    //        }
    //        if (beforeCursor == afC) {
    //            afC = afC->prev;
    //        }
    //        eraseBefore();
    //        if (cursorCopy > pos_cursor) {
    //            cursorCopy -= 1;
    //        }
    //    }

    //    moveFront();
    //    x += 1; // moveFront counter
    //    for (int y = 0; y <= x; y ++) {
    //        if (ind != backDummy->prev) {
    //            moveNext(); // x + 1 = how many times to call moveNext
    //        }
    //    }
    //}
    //pos_cursor = cursorCopy;
    //beforeCursor = bfC; 
    //afterCursor = afC;
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
    List J;
    Node *N = nullptr;
    Node *M = nullptr;
    for (N = this->frontDummy->next; N != this->backDummy; N = N->next) {
        J.insertBefore(N->data);
    }
    for (M = L.frontDummy->next; M != L.backDummy; M = M->next) {
        J.insertBefore(M->data);
    }
    J.moveFront();
    return J;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    std::string s = "(";
    Node *N = nullptr;
    for (N = frontDummy->next; N->next != nullptr; N = N->next) {
        //std::cout << "n->data: " << N->data << std::endl;
        s += std::to_string(N->data)+"";
        //s += ", ";
        if (N->next != backDummy) {
             s += ", ";
        }
        if (N == backDummy->prev) {
            //s += std::to_string(N->data)+" ";
            s += ")";
            break;
        }
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
    eq = (this->num_elements == R.num_elements);
    N = this->frontDummy;
    M = R.frontDummy;
    while (eq && N != nullptr) {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

// *** Overriden Operators *** -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged
bool operator==( const List& A, const List& B ) {
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
    if (this != &L) {
        List Copy = L;
        std::swap(frontDummy, Copy.frontDummy);
        std::swap(backDummy, Copy.backDummy);
        std::swap(num_elements, Copy.num_elements);
    }
    return *this;
}

