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

    int currentLevel = level;
    
    while (currentLevel >= 0) {
        Node* current = header->forward[currentLevel];
        while (current != nullptr) {
            if(current->forward[currentLevel] != nullptr){ // error
                Node* next = current->forward[currentLevel]; // Keep track of the next node at the current level
                delete current; // Delete the current node
                current = next; // Move to the next node at the current level
            }
        }
        currentLevel--; // Move to the next level
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
    Node* newNode = new Node(key, level); //new node
    if(p > level){
        level = p;
    }
    
    //traverse list: find where to insert
    Node* current = header; //start at the top
    int currentLevel = level;
    
    while(currentLevel >= 0){ //while not at bottom
        while(current->forward[currentLevel] != nullptr && current->forward[currentLevel]->key < key){
            //go forward if there is nextNode and it's less
            current = current->forward[currentLevel];
        }

        //stop here if greater, or end of level.
        if(currentLevel <= p){//if can insert at this level
            newNode->forward[currentLevel] = current->forward[currentLevel]; //newNode points to current's next
            current->forward[currentLevel] = newNode; //current next points to newNode.
        }

        //go to next level down
        currentLevel--;
    }
}

void SkipList::deleteElement(int search_key) {
    Node* current = header;
    int currentLevel = level;
    
    while (currentLevel >= 0 && current != nullptr) {
        while (current->forward[currentLevel] != nullptr) {

            if (current->forward[currentLevel]->key < search_key) {
                current = current->forward[currentLevel];
            }
            else if (current->forward[currentLevel]->key == search_key) {
                Node* temp = current->forward[currentLevel];

                if(temp->forward[currentLevel] != nullptr){
                    current->forward[currentLevel] = temp->forward[currentLevel];
                }

                delete temp;
                // No need to decrement level here
            }
            else {
                // Move to the next node at the same level
                break;
            }
        }
        currentLevel--; // Decrement level after completing a level's traversal
    }
}

bool SkipList::searchElement(int key) {
    Node* current = header; //stores the pointer to the next node at maxlvl

    //traverse

    int currentLevel = level;
    while(currentLevel >= 0){ //while not at the bottom level
        if(current->forward[currentLevel] != nullptr){ //if can go forward
            if(current->forward[currentLevel]->key == key){ // the next is key, return true
                return true;
            }
            else if(current->forward[currentLevel]->key < key){ //the next is less than key, go forward
                current = current->forward[currentLevel];
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