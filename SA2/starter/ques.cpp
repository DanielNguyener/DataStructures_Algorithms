#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

#ifndef ASCENDING_PATHS
int helperFunction(Node* root, int prevData);
// You can create helper functions for count ascending paths if required here

int countAscendingPaths(Node* root){
    return helperFunction(root, root->data);
}

int helperFunction(Node* root, int prevData){
    if(root == nullptr){
        return 0;
    }

    int count = 0;

    if(root->data > prevData){

        if(root->left == nullptr && root->right == nullptr){
            return 1;
        }
    }

    count += helperFunction(root->left, root->data);
    count += helperFunction(root->right, root->data);
    return count;
}

#endif

#ifndef LEFT_LEAVES

// You can create helper functions for sum of left leaves if required here

int sumOfLeftLeaves(Node* root) {
    if(root == nullptr){
        return 0;
    }
    int sumLeft = 0;
    if(root->left != nullptr){ //if left child exists
        Node* nodeLeft = root->left;
        if(nodeLeft->left == nullptr && nodeLeft->right == nullptr){ //if left child is a leaf
            sumLeft = nodeLeft->data; //store data
        }else{
            sumLeft += sumOfLeftLeaves(nodeLeft);
        }
    }

    sumLeft += sumOfLeftLeaves(root->right);
    //root is not a leaf, so we need to check right child
    return sumLeft;
}

#endif

#ifndef TEST_MODE
int main() {
    cout << "Sample Test case 1" << endl;
    {
        Node root(3);
        Node left(4), right(5);
        Node leftLeft(7), leftRight(8), rightLeft(9), rightRight(10);
        Node leftRightLeft(3), rightLeftRight(12);

        root.left = &left, root.right = &right;
        left.left = &leftLeft, left.right = &leftRight, right.left = &rightLeft, right.right = &rightRight;
        leftRight.left = &leftRightLeft, rightLeft.right = &rightLeftRight;

        int sumReturned = sumOfLeftLeaves(&root);
        cout << "Testing sum of left leaves" << endl;
        cout << "Expected sum of left leaves: 10" << endl;
        cout << "Returned sum of left leaves: " << sumReturned << endl;

        cout << endl;

        int numAscendingPaths = countAscendingPaths(&root);
        cout << "Testing count ascending paths" << endl;
        cout << "Expected number of ascending paths: 3" << endl;
        cout << "Returned number of ascending paths: " << numAscendingPaths << endl;
    }
    cout << endl;
    cout << endl;

    cout << "Sample Test case 2" << endl;
    {
        Node root(3);
        Node right(4);
        Node rightLeft(5), rightRight(16);
        Node rightRightLeft(14);

        root.right = &right;
        right.left = &rightLeft, right.right = &rightRight;
        rightRight.left = &rightRightLeft;

        int sumReturned = sumOfLeftLeaves(&root);
        cout << "Testing sum of left leaves" << endl;
        cout << "Expected sum of left leaves: 19" << endl;
        cout << "Returned sum of left leaves: " << sumReturned << endl;

        cout << endl;

        int numAscendingPaths = countAscendingPaths(&root);
        cout << "Testing count ascending paths" << endl;
        cout << "Expected number of ascending paths: 1" << endl;
        cout << "Returned number of ascending paths: " << numAscendingPaths << endl;
    }
}
#endif