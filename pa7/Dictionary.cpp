//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Krisha Sharma
// Cruz ID: krvsharm
// CSE 101-01 Tantalo
// Programming Assignment 7
// Dictionary.cpp
//------------------------------------------------------------------------------------------------------
// Credit: Please Note, there was high level pusedocode collabration with my sister tvsharma 
// (Twisha Sharma) during this assignment. The below code is also based off of Professor Tantalo's 
// example code and pusedo-code provided on the class webpage.
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

// Class Constructors & Destructors ----------------------------------------

Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary() {
    nil = new Node("krishakaiasharma", -420);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("krishakaiasharma", -420);
    root = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary() {
    clear();
    delete(nil);
}


// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s += R->key;
        s += " : ";
        s += R->val;
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        s += R->key;
        s += "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != N)  {
        this->setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        R = nil;

        num_pairs--;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R == nil || k == R->key) {
        return R;
    } else if (k < R->key) {
        return search(R->left, k);
    } else { // k > x.key
        return search(R->right, k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {
    if (R != nil) {
        while (R->left != nil) {
            R = R->left;
        }
        return R;
    } else {
        return nil;
    }
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {
    if (R != nil) {
        while (R->right != nil) {
            R = R->right;
        }
        return R;
    } else {
        return nil;
    }
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N == nil || N == findMax(root)) {
        return nil;
    }
    if (N->right != nil) {
        return findMin(N->right);
    }
    Node* M = N->parent;
    while (M != nil && N == M->right) {
        N = M;
        M = M->parent;
    }
    return M;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N == nil || N == findMin(root)) {
        return nil;
    }
    if (N->left != nil) {
        return findMin(N->left);
    }
    Node* M = N->parent;
    while (M != nil && N == M->left) {
        N = M;
        M = M->parent;
    }
    return M;
}

void Dictionary::transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nil) {
        v->parent = u->parent;
    }
}


// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
    if (search(root, k) != nil ) {
        return true;
    } else {
        return false;
    }
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
    if (!contains(k)) {
        throw std::logic_error("currentKey(): logic error");
    }
    return search(root, k)->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {
    if (current == nil) {
        return false;
    }
    return true;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
    if (!hasCurrent()) {
        throw std::logic_error("currentKey(): logic error");
    }
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
    if (!hasCurrent()) {
        throw std::logic_error("currentKey(): logic error");
    }
    return current->val;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
    postOrderDelete(root);
    root = nil;
    current = nil;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
    Node* Z = new Node(k, v);
    Z->left = nil;
    Z->right = nil;
    Node* y = nil;
    Node* x = root;
    while (x != nil) {
        y = x;
        if (Z->key == x->key) {
            Z->val = v;
            return;
        } else if (Z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    Z->parent = y;
    if (y == nil) {
        root = Z;
    } else if (Z->key < y->key) {
        y->left = Z;
    } else {
        y->right = Z;
    }
    num_pairs += 1;
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
    Node* N;
    Node* M;
    if (contains(k) != true) {
        throw std::logic_error("remove(): logic error");
    }
    N = search(root, k);
    if (N->left == nil) {
        transplant(N, N->right);
    } else if (N->right == nil) {
        transplant(N, N->left);
    } else {
        M = findMin(N->right);
        if (M->parent != N) {
            transplant(M, M->right);
            M->right = N->right;
            M->right->parent = M;
        }
        transplant(N, M);
        M->left = N->left;
        M->left->parent = M;
    }
    delete(N);
    num_pairs -= 1;
    if (current == N) {
        current = nil;
    }
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin() {
    if (num_pairs == 0) {
        current = nil;
        return;
    }
    current = findMin(root);
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end() {
    if (num_pairs == 0) {
        current = nil;
        return;
    }
    current = findMax(root);
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
    if (hasCurrent() == false) {
        throw std::logic_error("next(): logic error");
    }
    Node* temp = findNext(current);
    current = temp;
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
    if (hasCurrent() == false) {
        throw std::logic_error("prev(): logic error");
    }
    Node* temp = findPrev(current);
    current = temp;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
    std::string s = "";
    inOrderString(s, root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
    std::string s = "";
    preOrderString(s, root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
    Dictionary A = D;
    Dictionary B = *this;
    Node* temp;
    if (A.size() != B.size()) {
        return false;
    }
    B.begin();
    while (B.current != B.nil) {
        temp = A.search(A.root, B.current->key);
        if (temp->key == B.current->key) {
            return false;
        }
        if (B.current->val != temp->val) {
            return false;
        }
        B.next();
    }
    return true;
}

// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
    return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ) {
    return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ) {
    if (this != &D) {
        Dictionary DC = D;
        std::swap(nil, DC.nil);
        std::swap(root, DC.root);
        std::swap(num_pairs, DC.num_pairs);
        std::swap(current, DC.current);
    }
    return *this;
}
