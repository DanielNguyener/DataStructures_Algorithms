#ifndef CHAINING_H
#define CHAINING_H

#include "AbstractHashTable.h"
#include <vector>
#include <list>


// Chaining hash table class
class ChainingHashTable: public AbstractHashTable {
    private:
    std::vector<std::list<HashEntry>> table;
    void resizeAndRehash();

    public: 
    ChainingHashTable();
    ~ChainingHashTable(); 
    void insert(std::string key, const int val); 
    int remove(std::string key); 
    int get(std::string key) const;
    bool contains(std::string key) const;
};


///////////////////// TODO: FILL OUT THE FUNCTIONS /////////////////////

// constructor
ChainingHashTable::ChainingHashTable(): AbstractHashTable() {
	capacity = 11;
    num_elements = 0;
    maxLoadFactor = 0.7;
}

// destructor
ChainingHashTable::~ChainingHashTable() {
   
}

// inserts the given string key
void ChainingHashTable::insert(std::string key, int val) {
	
}

// removes the given key from the hash table - if the key is not in the list, throw an error
int ChainingHashTable::remove(std::string key) {
	return -1;
}

// getter to obtain the value associated with the given key
int ChainingHashTable::get(std::string key) const {
	return -1;
}

bool ChainingHashTable::contains(const std::string key) const {
	return false;
}

void ChainingHashTable::resizeAndRehash() {
   
}

#endif