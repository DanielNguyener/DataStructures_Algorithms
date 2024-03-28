#ifndef DOUBLEHASHING_H
#define DOUBLEHASHING_H

#include "AbstractHashTable.h"
#include <vector>

// Double hashing hash table class
class DoubleHashTable : public AbstractHashTable {
    private:
    // helper functions
    int secondHash(std::string s) const;
    std::vector<HashEntry> table;
    int prevPrime;
    void resizeAndRehash();

    public: 
    DoubleHashTable();
    ~DoubleHashTable(); 
    void insert(std::string key, int val); 
    int remove(std::string key); 
    int get(std::string key) const; 
    bool contains(std::string key) const;
};


///////////////////// TODO: FILL OUT THE FUNCTIONS /////////////////////

// constructor 
DoubleHashTable::DoubleHashTable(): AbstractHashTable() {
	
}

// destructor
DoubleHashTable::~DoubleHashTable() {
	
}

// inserts the given string key
void DoubleHashTable::insert(std::string key, int val) {
	
}

// removes the given key from the hash table - if the key is not in the list, throw an error
int DoubleHashTable::remove(std::string key) {
	return -1;
}

// getter to obtain the value associated with the given key
int DoubleHashTable::get(std::string key) const {
	return -1;
}

bool DoubleHashTable::contains(std::string key) const {
	return false;
}

void DoubleHashTable::resizeAndRehash() {
	
}

// helper functions 
int DoubleHashTable::secondHash(std::string s) const {
	return -1;
}


#endif