#include <iostream>
#include <string>
using namespace std;

struct Node{
    int key;
    Node* parent;
    Node* left;
    Node* right;
    char color;
};

class RBT{
public:
    Node* root;
    Node* NIL;

    RBT();
    void inorder(Node*);
    void leftRotate(Node*);
    void rightRotate(Node*);
    Node* newNode(int);
    void insertion(int);
    void transplant(Node*, Node*);
    void deletion(Node*, int);
};

RBT::RBT(){
    NIL = new Node;
    NIL->color = 'B';
    NIL->left = NULL;
    NIL->right = NULL;
    root = NIL;
}

void RBT::inorder(Node* node){
    string color;
    if(node->color == 'R')
        color = "Red";
    else 
        color = "Black";
    if(node != NIL){
        inorder(node->left);
        if(node->parent != NULL)
            cout << "key: " << node->key << " parent: " << node->parent->key << " color: " << color << "\n";
        else
            cout << "key: " << node->key << " parent: " << "  " << " color: " << color << "\n";
        inorder(node->right);
    }
}

void RBT::leftRotate(Node* x){
    Node* y = x->right;
    x->right = y->left;

    if(y->left != NIL)
        y->left->parent = x;
    y->parent = x->parent;
    if(x->parent == NULL)
        root = y;
    else if (x == x->parent->left) // x is left child
        x->parent->left = y; // switch x with y
    else // x is right child
        x->parent->right = y; // switch x with y
    y->left = x;
    x->parent = y;
}

void RBT::rightRotate(Node* x){
    Node* y = x->left;
    x->left = y->right;
    
    if(y->right != NIL)
        y->right->parent = x;
    y->parent = x->parent;
    if(x->parent == NULL)
        root = y;
    else if(x == x->parent->right) // x is right child
        x->parent->right = y; //switch x with y
    else // x is left child
        x->parent->left = y; // switch x with y
    y->right = x;
    x->parent = y;
}

Node* RBT::newNode(int key){
    Node* node = new Node;
    node->parent = NULL;
    node->key = key;
    node->left = NIL;
    node->right = NIL;
    node->color = 'R';
    return node;
}

void RBT::insertion(int key){
    Node* node = newNode(key);
    Node* x = root;
    Node* y = NULL;

    while(x != NIL){
        y = x; // save x's parent as y
        if(key < x->key)
            x = x->left;
        else 
            x = x->right;
    }
    node->parent = y;
    if(y == NULL)
        root = node;
    else if(key < y->key)
        y->left = node;
    else
        y->right = node;

    if(node->parent == NULL){ // node is root
        node->color = 'B';
        return;
    }
    if(node->parent->parent == NULL) // node is second layer
        return;

    // fix color
    Node* u; // u is node's uncle
    while(node != root && node->parent->color == 'R'){ // if parent is red
        if(node->parent == node->parent->parent->right){ // parent is right child
            u = node->parent->parent->left; 
            if(u->color == 'R'){ // if uncle is red
                u->color = 'B'; // change uncle to black
                node->parent->color = 'B'; // change parent to black
                node->parent->parent->color = 'R'; // change grandparent to red
                node = node->parent->parent; // node = grandparent
            }
            else { // if uncle is black
                if(node == node->parent->left) {// if node is left child
                    node = node->parent; // node = parent;
                    rightRotate(node);
                }
                node->parent->color = 'B';
                node->parent->parent->color = 'R';
                leftRotate(node->parent->parent);
            }
        }
        else{ // parent is left child
            u = node->parent->parent->right;
            if(u->color == 'R'){ // if uncle is red
                u->color = 'B'; // change uncle to black
                node->parent->color = 'B'; // change parent to black
                node->parent->parent->color = 'R'; // change grandparent to red
                node = node->parent->parent; // node = grandparent
            }
            else{ // if uncle is black
                if(node == node->parent->right){ // if node is right child
                    node = node->parent; // node = parent;
                    leftRotate(node);
                }
                node->parent->color = 'B';
                node->parent->parent->color = 'R';
                rightRotate(node->parent->parent);
            }
        }
    }
    root->color = 'B'; // correct root's color
}

// utility function for deletion
void RBT::transplant(Node* u, Node* v){ // swap u and v 
    if(u->parent == NULL) // if u is root
        root = v;
    else if(u == u->parent->left) // if u is left child
        u->parent->left = v;
    else // if u is right child
        u->parent->right = v;
    v->parent = u->parent;
}

void RBT::deletion(Node* node, int key){
    Node* z = NIL;
    Node* x;
    Node* y;
    while(node != NIL){
        if(node->key == key)
            z = node;
        if(node->key < key)
            node = node->right;
        else
            node = node->left;
    }

    y = z; // remember the found node
    char y_color = y->color; // remember y's original color
    if(z->left == NIL){ // found key has no left child
        x = z->right; // remember z's child
        transplant(z, z->right);
    }
    else if(z->right == NIL) {// found key has no right child
        x = z->left; // remember z's child
        transplant(z, z->left);
    }
    else { // found key has both children
        y = z->right;
        while(y->left != NIL) // find the smallest node on the right branch
            y = y->left;

        y_color = y->color;
        x = y->right;
        if(y->parent == z) // if z is second last level
            x->parent = y;
        else{
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if(y_color == 'R') 
        return;

    // fix color
    Node* s; // s is x's sibling
    while(x != root && x->color == 'B'){
        if(x == x->parent->left){ // x is left child
            s = x->parent->right;
            if(s->color == 'R'){
                s->color = 'B';
                x->parent->color = 'R';
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if(s->left->color == 'B' && s->right->color == 'B'){ // if s's both children are black
                s->color = 'R';
                x = x->parent;
            }
            else {// any other case
                if(s->right->color == 'B'){ // if s's right child is black
                    s->left->color = 'B';
                    s->color = 'R';
                    rightRotate(s);
                    s = x->parent->right;
                }
                s->color = x->parent->color;
                x->parent->color = 'B';
                s->right->color = 'B';
                leftRotate(x->parent);
                x = root;
            }
        }

        else { // x is right child
            s = x->parent->left;
            if(s->color == 'R'){
                s->color = 'B';
                x->parent->color = 'R';
                rightRotate(x->parent);
                s = x->parent->left;
            }
            if(s->left->color == 'B' && s->right->color == 'B'){ // if s's both children are black
                s->color = 'R';
                x = x->parent;
            }
            else {// any other case
                if(s->left->color == 'B'){ // if s's right child is black
                    s->right->color = 'B';
                    s->color = 'R';
                    leftRotate(s);
                    s = x->parent->left;
                }
                s->color = x->parent->color;
                x->parent->color = 'B';
                s->right->color = 'B';
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = 'B';
}

int main(void){
    RBT rbt;
    int t;
    cin >> t;
    for(int i=0; i<t; i++){
        int op, n;
        cin >> op >> n;
        if(op == 1){ // insert
            cout << "\nInsert: ";
            for(int j=0; j<n; j++){
                int m;
                cin >> m;
                cout << m;
                if(j < n-1) 
                     cout << ", ";
                rbt.insertion(m);
            } cout << "\n";
            rbt.inorder(rbt.root);
        }
        else { // delete
            cout << "\nDelete: ";
            for(int j=0; j<n; j++){
                int m;
                cin >> m;
                cout << m;
                if (j < n-1)
                    cout << ", ";
                rbt.deletion(rbt.root, m);
            }cout << "\n";
            rbt.inorder(rbt.root);
        }
    }
    return 0;
}