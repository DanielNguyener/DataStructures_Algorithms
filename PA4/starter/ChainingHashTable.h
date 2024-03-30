#ifndef CHAINING_H
#define CHAINING_H

#include "AbstractHashTable.h"
#include <vector>
#include <list>


// Chaining hash table class
class ChainingHashTable: public AbstractHashTable {
    private:
    std::vector<std::list<HashEntry>> table; //this is the map
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
    table.resize(capacity);
    cout << "constructor success" << endl;
}

// destructor
ChainingHashTable::~ChainingHashTable() {
    
    for(auto i = 0; i < table.size(); i++){
        table[i].clear();
    }
    table.clear();

    capacity = 11;
    num_elements = 0;
    maxLoadFactor = 0.7;
}

// inserts the given string key
void ChainingHashTable::insert(std::string key, int val) {
    //check if load factor exeeds maximum first
    if(this->load_factor() > maxLoadFactor){
        resizeAndRehash();
    }

	//create index and find list at index.
    int index = hash(key);
    auto &list = table[index];

    //key deosn't exist
    if(!this->contains(key)){
        
        list.push_back(HashEntry(key,val));
        cout << "inserted: " << table[index].back().key << endl;
        num_elements++;
    
    }else{
        //key exists: update the value.
        for(auto i = list.begin(); i != list.end(); i++){

            if(i->key == key){
                cout << "val before:" << i->val << endl;
                i->val = val;
                cout << "updated: " << i->key << " with :" << i->val << endl;
                return;
            }
        }
        
    }
}

// removes the given key from the hash table - if the key is not in the list, throw an error
int ChainingHashTable::remove(std::string key) {
    //search for key then remove
    //throw error if not in table

    if(!this->contains(key)){
        throw std::out_of_range("Key doesn't exist");

    }else{
        int valRemoved;
        int index = hash(key);
        auto list = table[index];
        
        for(auto i = list.begin(); i != list.end(); i++){
            if(i->key == key){
                valRemoved = i->val;
                list.erase(i);
                num_elements--;
                return valRemoved;
            }
        }
    }

}

// getter to obtain the value associated with the given key
int ChainingHashTable::get(std::string key) const {
    //search for key in hash table, similar to insert
    //throws if not found
    
    //have to find index first
    int index = hash(key);

    //at index, is there a node with the key?
    auto &list = table[index];

    //bool if found
    bool found = false;

    for(auto i = list.begin(); i != list.end(); i++){
        string nodeKey = i->key;
        if(nodeKey == key){
            found = true;
            return i->val;
        }
    }

    if(!found){
        throw std::out_of_range("Key doesn't exist2");
    }


}

bool ChainingHashTable::contains(const std::string key) const {
    //like get but returns boolean, no throw.

    //get inddex
    int index = hash(key);

    //at index, is there a node with key?
    auto list = table[index];

    for(auto i = list.begin(); i != list.end(); i++){
        string nodeKey = i->key;
        if(nodeKey == key){
            return true;
        }
    }

	return false;
}

void ChainingHashTable::resizeAndRehash() {
   //new capacity is prime

   //make new hash table
   //rehash existing elements into new hash table. (don't just copy, rehash and reinsert)

    int newCapacity = findNextPrime(capacity);
    std::vector<std::list<HashEntry>> newTable(newCapacity);

    for(auto i = 0; i < table.size(); i++){
        for(auto j = table[i].begin(); j != table[i].end(); j++){
            int newIndex = hash(j->key);

            newTable[newIndex].push_back(HashEntry(j->key, j->val));
        }
    }

    table = std::move(newTable);
    capacity = newCapacity;

}

#endif