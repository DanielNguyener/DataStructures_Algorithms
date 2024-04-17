#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

class Node {
public:
    int key;
    std::vector<Node*> forward;

    Node(int key, int level) : key(key), forward(level + 1, nullptr) {}
};

class SkipList {
private: 
    double P;
    int MAXLVL;
    Node* header;
    int level;

public:
    SkipList(int max_lvl, double p);
    ~SkipList();
    int randomLevel();
    void insertElement(int key);
    void deleteElement(int search_key);
    bool searchElement(int key);
    void displayList();
};


SkipList::SkipList(int max_lvl, double p) : MAXLVL(max_lvl), P(p), level(0) {
    header = new Node(-1, MAXLVL);
}

SkipList::~SkipList() {
    //traverse

    // Node current = *header;
    // while(current.forward[0] != nullptr){

    //     Node* next = current.forward[0];

    //     delete &current;

    //     current = *next;
    // }

    if (header->forward[0] == nullptr) {
        delete header; // Simply delete the header node
        return;
    }

    Node* current = header->forward[0]; // Start from the first element after the header

    while (current != nullptr) {
        Node* next = current->forward[0]; // Store the pointer to the next node
        delete current; // Delete the current node
        current = next; // Move to the next node
    }

    delete header; // Delete the header node

}

int SkipList::randomLevel() {
    int level = 0;
    double result;
    while(level < MAXLVL){
        result = static_cast<double>(rand()) / RAND_MAX;
        if(result < P){
            level++;
        }else{
            return level;
        }
    }
}

void SkipList::insertElement(int key) {
    //check if key exists
    if(searchElement(key)){
        return;
    }

    int p = randomLevel(); //doesn't exist, determine level at which to insert
    if(p > level){ //if level determined is greater than highest level-> update
        level = p;
    }

    Node* newNode = new Node(key, p); //new node
    
    //traverse list: find where to insert
    Node* current = header; //start at the top
    int currentLevel = level;
    
    while(currentLevel >= 0){ // While not at bottom
        if(current->forward[currentLevel] == nullptr || current->forward[currentLevel]->key >= key) { 
            // If we're at end of list, or next is greater then insert.

            if(currentLevel <= p) { // Check if we can insert at correct level
                newNode->forward[currentLevel] = current->forward[currentLevel]; // newNode points to current's next !works even if next is null.
                current->forward[currentLevel] = newNode; // current next points to newNode.
            } 
            // Go to next level down
            currentLevel--;
        } else { 
            // Keep traversing if next is less
            current = current->forward[currentLevel];
        }
    }
}

void SkipList::deleteElement(int search_key) {
    Node* current = header;
    Node* update[MAXLVL + 1]; // Array to store pointers to the nodes whose forward pointers need to be updated

    // Initialize update array
    for (int i = 0; i <= level; i++) {
        update[i] = header; // Initialize update array with header nodes at all levels
    }

    // Traverse the list to find the node to delete and update the update array
    for (int i = level; i >= 0; i--) {
        while (current->forward[i] != nullptr && current->forward[i]->key < search_key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    // Move to the next node at the bottom level
    current = current->forward[0];

    // If current node has the search_key, update pointers and delete the node
    if (current != nullptr && current->key == search_key) {
        for (int i = 0; i <= level; i++) {
            // If the forward pointer at this level points to the node to be deleted, update it
            if (update[i]->forward[i] == current) {
                update[i]->forward[i] = current->forward[i];
            }
        }

        // Remove levels from the skip list where the node to be deleted exists
        while (level > 0 && header->forward[level] == nullptr) {
            level--;
        }

        // Delete the node
        delete current;

    } else {
        std::cout << "Element with key " << search_key << " not found." << std::endl;
    }
    
    
}

bool SkipList::searchElement(int key) {

    Node* current = header; //stores the pointer to the next node at maxlvl
    int currentLevel = level;

    while(currentLevel >= 0){ //while not at the bottom level

        if(current->forward[currentLevel] != nullptr){ //if can go forward

            if(current->forward[currentLevel]->key < key){ //the next is less than key, go forward
                current = current->forward[currentLevel];
            }
            else if(current->forward[currentLevel]->key == key){ // the next is key, return true
                return true;
            }
            else{ //the next is greater, and you're not at the right key yet, so go down.
                currentLevel--;
            }
        }
        else{ //go down if you've reached the end of the list.
            currentLevel--;
        }
    }

    return false; //not found.
}

void SkipList::displayList() {
    std::cout << "\n*****Skip List******" << std::endl;
    Node* head = header;
    for (int lvl = 0; lvl <= level; lvl++) {
        std::cout << "Level " << lvl << ": ";
        Node* node = head->forward[lvl];
        while (node != nullptr) {
            std::cout << node->key << " ";
            node = node->forward[lvl];
        }
        std::cout << std::endl;
    }
}

#endif