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

    if(load_factor() > maxLoadFactor){
        resizeAndRehash();
    }

	int hashIndex = hash(key);
    int currentIndex = hashIndex;
    int deletedIndex = -1;

    do{

        if(!table[currentIndex].isFilled && !table[currentIndex].DELETED){ //not filled, and not deleted

            if(deletedIndex != -1){
                table[deletedIndex] = HashEntry(key,val);
                num_elements++;
                return;
            }

            else{
                table[currentIndex] = HashEntry(key,val);
                num_elements++;
                return;
            }
        }
        
        else if(table[currentIndex].isFilled && table[currentIndex].key == key){ //filled and matching key
            table[currentIndex].val = val;
            return;
        }

        else if(table[currentIndex].DELETED && deletedIndex == -1){ //deleted, and first deleted not yet stored. -> store
            deletedIndex = currentIndex;
        }
        
        currentIndex = (currentIndex + 1) % capacity;
        

    }while(currentIndex != hashIndex);

}

// removes the given key from the hash table - if the key is not in the list, throw an error
int ProbingHashTable::remove(std::string key) {
	int valRemoved = 0;
    int hashIndex = hash(key);
    int currentIndex = hashIndex;

    do{
        if(table[currentIndex].key == key && !table[currentIndex].DELETED){
            valRemoved = table[currentIndex].val;

            table[currentIndex].isFilled = false;
            table[currentIndex].DELETED = true;
            table[currentIndex].key = "";
            table[currentIndex].val = 0;

            num_elements--;
            break;
        }

        else if(!table[currentIndex].isFilled && !table[currentIndex].DELETED){
            throw std::out_of_range("Key not found");
        }

        currentIndex = (currentIndex + 1) % capacity;

    }while(currentIndex != hashIndex);
}


// getter to obtain the value associated with the given key
int ProbingHashTable::get(std::string key) const {
	int hashIndex = hash(key);
    int currentIndex = hashIndex;

    do{
        if(table[currentIndex].key == key && !table[currentIndex].DELETED){
            return table[currentIndex].val;
        }else if(!table[currentIndex].isFilled && !table[currentIndex].DELETED){
            throw std::out_of_range("Key not found");
        }

        currentIndex = (currentIndex + 1) % capacity;
    }while(currentIndex != hashIndex);

    
}

bool ProbingHashTable::contains(std::string key) const {
	int hashIndex = hash(key);
    int currentIndex = hashIndex;

    do{
        if(!table[currentIndex].isFilled && !table[currentIndex].DELETED){
            return false;

        }else if(table[currentIndex].key == key && !table[currentIndex].DELETED){
            return true;
        }

        currentIndex = (currentIndex + 1) % capacity;
    }while(currentIndex != hashIndex);
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