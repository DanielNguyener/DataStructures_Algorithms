#include <iostream>
#include "bst.h"
using namespace std;

#ifndef TEST
int main() {
    
    BST<int> bst;
    bst.root = new BST_Node<int>(1);
    bst.insert(2);

    cout << "root: " << bst.root->key << endl;
    if(bst.root->left != nullptr){
        cout << "left: " << bst.root->left->key << endl;
    }else if(bst.root->right != nullptr){
        cout << "right: " << bst.root->right->key << endl;
    }
}
#endif