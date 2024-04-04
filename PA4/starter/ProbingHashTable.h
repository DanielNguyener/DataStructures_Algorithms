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
	capacity = 11;
    num_elements = 0;
    maxLoadFactor = 0.7;;
    table.resize(capacity);
}

// destructor
ProbingHashTable::~ProbingHashTable() {
    table.clear();

   capacity = 11;
   num_elements = 0;
   maxLoadFactor = 0.7;
   
}

// inserts the given string key
void ProbingHashTable::insert(std::string key, int val) {
	int hashIndex = hash(key);
    int currentIndex = hashIndex;
    int deletedIndex = -1;
    int elm_checked = 0;
    bool found = false;

    bool contain = contains(key); //if contain, 

    while(true){

        if(table[currentIndex].DELETED && deletedIndex == -1){ //deleted, and first deleted not yet stored. -> store
            deletedIndex = currentIndex;
        }

        if(!table[currentIndex].isFilled && !table[currentIndex].DELETED){ //not filled, and not deleted

            table[currentIndex] = HashEntry(key,val);
            num_elements++;
            found = true;
            break;
        }

        else if(table[currentIndex].isFilled && table[currentIndex].key == key){ //filled and matching key
            table[currentIndex].val = val;
            found = true;
            break;
        }

        currentIndex = (currentIndex + 1) % capacity;
        elm_checked++;

        if(elm_checked >= capacity){
            break;
        }
    }

    if(load_factor() > maxLoadFactor){
        resizeAndRehash();
    }

    if(found){
        return;
    }

    if(deletedIndex != -1 && !found){ //first deleted idx stored, and not found. insert there.
        table[deletedIndex] = HashEntry(key,val);
        num_elements++;
        return;
    }

    else{
        resizeAndRehash();
        insert(key,val);
    }
}

// removes the given key from the hash table - if the key is not in the list, throw an error
int ProbingHashTable::remove(std::string key) {
	int valRemoved = 0;
    int hashIndex = hash(key);
    int elm_checked = 0;
    int currentIndex = hashIndex;

    while(true){
        if(table[currentIndex].isFilled && table[currentIndex].key == key){
            valRemoved = table[currentIndex].val;

            table[currentIndex].isFilled = false;
            table[currentIndex].DELETED = true;
            table[currentIndex].key = "";
            table[currentIndex].val = 0;

            num_elements--;
            break;
        }

        currentIndex = (currentIndex + 1) % capacity;
        elm_checked++;

        if(elm_checked >= capacity){
            break;
        }
    }

    if(valRemoved == 0){
        throw std::out_of_range("Key not found");
    }
}

// getter to obtain the value associated with the given key
int ProbingHashTable::get(std::string key) const {
	int hashIndex = hash(key);
    int currentIndex = hashIndex;
    int elm_checked = 0;

    while(elm_checked < capacity){
        if(table[currentIndex].key == key && table[currentIndex].isFilled){
            return table[currentIndex].val;
        }

        currentIndex = (currentIndex + 1) % capacity;
        elm_checked++;
    }

    if(elm_checked >= capacity){
        throw std::out_of_range("Key not found");
    }
    
}

bool ProbingHashTable::contains(std::string key) const {
	int hashIndex = hash(key);
    int currentIndex = hashIndex;
    int elm_checked = 0;

    while(elm_checked < capacity){
        if(table[currentIndex].key == key && table[currentIndex].isFilled){
            return true;
        }

        currentIndex = (currentIndex + 1) % capacity;
        elm_checked++;
    }

    return false;
}

void ProbingHashTable::resizeAndRehash() {
    int newCapacity = findNextPrime(2 * capacity);
    capacity = newCapacity;

    std::vector<HashEntry> newTable(newCapacity);

    for(const auto& entry: table){
        if(entry.isFilled){
            int currentIndex = hash(entry.key);

            while(true){
                if(!newTable[currentIndex].isFilled){
                    newTable[currentIndex] = entry;
                    break;
                }

                currentIndex = (currentIndex + 1) % newCapacity;
            }
            
        }
    }

    table = std::move(newTable);
}

#endif