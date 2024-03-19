#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>

using namespace std;

template <typename Type>
class BST_Node {
public:
    Type key;
    BST_Node* left;
    BST_Node* right;

    BST_Node(Type key) {
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
    }
};

template <typename Type>
class BST {
private: 
    // helper function for copy constructor
    BST_Node<Type>* copyTree(BST_Node<Type>* originalNode);
    // helper function for deallocating all nodes recursively
    void clearTree(BST_Node<Type>* node);
    // insertRecursive is helper function for insert
    void insertRecursive(BST_Node<Type>* &node, Type key);
    // deleteRecursive is helper function for deleteNode
    BST_Node<Type>* deleteRecursive(BST_Node<Type>* node, Type key);
    // Helper method to find the minimum value in the subtree rooted at node (as well as the node itself)
    Type minValue(BST_Node<Type>* node);
    // Helper function for recursively searching for a key
    bool findHelper(BST_Node<Type>* node, Type lkpkey);
    // Helper function for recursively adding the in-order output key values to a string s
    void printTreeInOrderHelper(BST_Node<Type>* node, string& s);
public:
    BST_Node<Type>* root;  
    // Constructor
    BST();
    
    // Copy Constructor
    BST(const BST& other);
    
    // Copy Assignment Operator - uses helper functions copyTree and clearTree
    BST& operator=(const BST& other);

    // Destructor
    ~BST();

    // Insert method to insert node with key
    void insert(Type key);

    // deleteNode method to delete a node with a particular key
    void deleteNode(Type key);

    // Find method to search for a key; returns true if it exists in the tree and false if it does not
    bool find(Type lkpkey);

    // Creates and returns a string that contains the tree in-order
    string printTreeInOrder();
};

template <typename Type>
BST<Type>::BST(){
    this->root = nullptr;
}

template <typename Type>
BST_Node<Type>* BST<Type>::copyTree(BST_Node<Type>* originalNode) {
    // This function is recursive

    // given root of other, make tree.
    if(originalNode == nullptr){
        return nullptr;
    }

    BST_Node<Type>* newNode = new BST_Node<Type>(originalNode->key);
    newNode->left = copyTree(originalNode->left);
    newNode->right = copyTree(originalNode->right);

    return newNode;
}

template <typename Type>
BST<Type>::BST(const BST<Type>& other){ //copy constructor
    // use copy tree

    if(other.root == nullptr){
        this->root = nullptr;
    }else{
        this->root = copyTree(other.root);
    }

}

template <typename Type>
BST<Type>& BST<Type>::operator=(const BST& other) { //copy assignment
    
    //not self-assignment
    if(this->root != other.root){
        clearTree(this->root); //clear current tree
    }

    //initialize
    this->root = nullptr;

    //other tree isn't empty
    if(other.root != nullptr){
        this->root = copyTree(other.root); //copy other tree
    }


    return *this;
}

template <typename Type>
void BST<Type>::clearTree(BST_Node<Type>* node){
    // recursively delete
     
    if(node != nullptr){
        //if not leaf,

        clearTree(node->left); //delete left subtree
        clearTree(node->right); //delete right subtree

        delete node; //now delete current node.
    }else{
        //if leaf
        delete node; //delete self.
    }

}

template <typename Type>
BST<Type>::~BST(){ //destructor

    clearTree(this->root);
    this->root = nullptr;
    
}

template <typename Type>
void BST<Type>::insertRecursive(BST_Node<Type>*& node, Type key) {

    
    //if current node is free
    if(node != nullptr){
        if(key < node->key){
            // go right
            insertRecursive(node->left, key);

        }else if(key > node->key){
            // go left
            insertRecursive(node->right, key);

        }else{
            cout << "node already exists, key: " << key << endl;
        }
    }else if(node == nullptr){
        node = new BST_Node<Type>(key);

    }   
}   

template <typename Type>
void BST<Type>::insert(Type key) {
    if (this->root == nullptr) {
        this->root = new BST_Node<Type>(key);
    } else {
        insertRecursive(this->root, key);
    }
}

template <typename Type>
BST_Node<Type>* BST<Type>::deleteRecursive(BST_Node<Type>* node, Type key) {

   // base case, tree is empty, or key not present.
   if(node == nullptr){
    return node;
   }
    //recursively find node.
   if(key < node->key){
    // go left
    node->left = deleteRecursive(node->left, key); // will replace the deleted node with replacement
   }else if(key > node->key){
    // go right
    node->right = deleteRecursive(node->right, key);
   }
   
   else{ // node.key == key, delete current node
    // case 1: 1 or 0 children
    if(node->left == nullptr){
        //left is empty, so store child as temp -> delete node -> return the temp, to replace node.
        BST_Node<Type>* Temp = node->right;
        delete node;
        return Temp;
        

    }else if(node->right == nullptr){
        //right is empty, store child as temp -> delete node -> return temp to replace node.
        BST_Node<Type>* Temp = node->left;
        delete node;
        return Temp;
    }

    //case2: 2 children, find min of right subtree
    /*
      2. find in-order-successor
        2a. minvalue of the right subtree
    3. overwrite current value
    4. delete minvalue from right subtree
    5. return a node that is now going to be the new child
    */
    int successor = minValue(node->right);

    node->key = successor; //overwrite current value with successor value

    node->right = deleteRecursive(node->right, successor); //delete the min-value node from right subtree.
   }

   return node;
}

template <typename Type>
void BST<Type>::deleteNode(Type key) {
    if (this->root == nullptr) {
        return;
    }
    this->root = deleteRecursive(this->root, key);
}

// Helper method to find the minimum value in the subtree rooted at a particular node (including the node itself)
template <typename Type>
Type BST<Type>::minValue(BST_Node<Type>* node) {

    while(node->left != nullptr){
        node = node->left;
    }

    return node->key;
}

template <typename Type>
bool BST<Type>::findHelper(BST_Node<Type>* node, Type lkpkey) {

    //inorder search. 
    if(node == nullptr){
        return false;
    }
    else if(node->key < lkpkey){
        findHelper(node->right, lkpkey);

    }else if(node->key > lkpkey){
        findHelper(node->left, lkpkey);

    }else{
    return true;
    }
}


template <typename Type>
bool BST<Type>::find(Type lpkey) {
    if (this->root == nullptr) {
        return false;
    }
    return findHelper(this->root, lpkey);
}

template <typename Type>
void BST<Type>::printTreeInOrderHelper(BST_Node<Type>* node, string& s) {

    // in order search... 

    //if current has children
    if(node != nullptr){

        //traverse to the left first
        if(node->left != nullptr){
            printTreeInOrderHelper(node->left, s);
        }

        s += to_string(node->key) += " ";

        if(node->right != nullptr){
            printTreeInOrderHelper(node->right, s);
        }
        
    }
}

template <typename Type>
string BST<Type>::printTreeInOrder() {
    if (this->root == nullptr) {
        return "";
    }
    string s = "";
    printTreeInOrderHelper(this->root, s);
    return s;
}

#endif


