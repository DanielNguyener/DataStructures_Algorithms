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
    maxLoadFactor = 1.0;
    table.resize(capacity);
}

// destructor
ChainingHashTable::~ChainingHashTable() {
    
    for(auto i = 0; i < table.size(); i++){
        table[i].clear();
    }
    table.clear();

    capacity = 11;
    num_elements = 0;
    maxLoadFactor = 1.0;
}

// inserts the given string key
void ChainingHashTable::insert(std::string key, int val) {

    //check if load factor exeeds maximum first
    if(this->load_factor() > maxLoadFactor){
        this->resizeAndRehash();
    }

	//create index and find list at index.
    int index = hash(key);
    auto &list = table[index];


    //key deosn't exist
    if(!this->contains(key)){

        list.push_back(HashEntry(key,val));
        //cout << "inserted: " << table[index].front().key << endl;
        num_elements++;

    }else{
        //key exists: update the value.
        for(auto i = list.begin(); i != list.end(); i++){

            if(i->key == key){
                i->val = val;
                //cout << "value updated" << endl;
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
        auto &list = table[index];

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
    const auto list = table[index];

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
        throw std::out_of_range("Key doesn't exist");
    }


}

bool ChainingHashTable::contains(const std::string key) const {
    //like get but returns boolean, no throw.

    //get inddex
    int index = hash(key);
    //at index, is there a node with key?
    const auto &list = table[index];

    for(auto i = list.begin(); i != list.end(); i++){
        if(i->key == key){
            //cout << "contains:true" << endl;
            return true;
        }
    }

	return false;
}

void ChainingHashTable::resizeAndRehash() {
   //new capacity is prime

   //make new hash table
   //rehash existing elements into new hash table. (don't just copy, rehash and reinsert)


    int newCapacity = findNextPrime(2 * num_elements);
    std::vector<std::list<HashEntry>> newTable(newCapacity);

    capacity = newCapacity;
    
    for(auto& list: table){ //for each existing index in table
        if(!list.empty()){
            for(auto& entry: list){ //for each item in index list

                //generate new index, by hashing the key, with new capacity.
                int newIndex = hash(entry.key);
            
                newTable[newIndex].push_back(std::move(entry));
            }
        }
        
    }

    table = std::move(newTable);
}

#endif