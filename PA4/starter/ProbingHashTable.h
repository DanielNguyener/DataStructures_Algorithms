#ifndef LINEARPROBING_H
#define LINEARPROBING_H

#include "AbstractHashTable.h"
#include <vector>

// Linear probing hash table class
class ProbingHashTable : public AbstractHashTable {
    private:
    std::vector<HashEntry> table;
    void resizeAndRehash();
    
    public: 
    ProbingHashTable();
    ~ProbingHashTable(); 
    void insert(std::string key, int val); 
    int remove(std::string key); 
    int get(std::string key) const; 
    bool contains(std::string key) const;
};

///////////////////// TODO: FILL OUT THE FUNCTIONS /////////////////////

// constructor 
ProbingHashTable::ProbingHashTable(): AbstractHashTable() {
	
}

// destructor
ProbingHashTable::~ProbingHashTable() {
   
}

// inserts the given string key
void ProbingHashTable::insert(std::string key, int val) {
	
}

// removes the given key from the hash table - if the key is not in the list, throw an error
int ProbingHashTable::remove(std::string key) {
	return -1;
}

// getter to obtain the value associated with the given key
int ProbingHashTable::get(std::string key) const {
	return -1;
}

bool ProbingHashTable::contains(std::string key) const {
	return false;
}

void ProbingHashTable::resizeAndRehash() {
    
}

#endif