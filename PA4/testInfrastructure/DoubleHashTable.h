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
	capacity = 11;
    num_elements = 0;
    maxLoadFactor = 0.7;
    table.resize(capacity);
}

// destructor
DoubleHashTable::~DoubleHashTable() {
    table.clear();

    capacity = 11;
    num_elements = 0;
    maxLoadFactor = 0.7;
}

// inserts the given string key
void DoubleHashTable::insert(std::string key, int val) {
	//search for the key
    //search through possible slots before inserting

    //stop when an empty slot is not DELETED or
    //when we find key or
    //we loop back to the original index

    //first hash


    int hashIndex = hash(key);
    int offset = secondHash(key);
    int currentIndex = hashIndex;
    int deletedIndex = -1;

        
    while(true){
        if(!table[currentIndex].isFilled || table[currentIndex].DELETED){ //not filled OR DELETED
            
            //deletedindex hasn't been changed, so it's the first free slot that is deleted.
            if(deletedIndex == -1) {
                //store the index.
                deletedIndex = currentIndex;
            }

            if(!table[currentIndex].DELETED){ //not filled & not deleted
                //insert
                table[currentIndex] = HashEntry(key, val);
                num_elements++;

                if(this->load_factor() > maxLoadFactor){
                    this->resizeAndRehash();
                }

                return; // finished inserting at first non-filled not-deleted.
            }
        }
        else if(table[currentIndex].isFilled && table[currentIndex].key == key){ //filled, and key exists.
            //update
            table[currentIndex].val = val;
            return; //finished updating
        }

        //move to next index if //filled, and not same key.
        currentIndex = (currentIndex + offset) % capacity;

        if(currentIndex == hashIndex){ //we are back to the beginning, so quit
            break;
        }
    }

    //if we haven't returned already. that means all slots are occupied or deleted.
    if(deletedIndex != -1){ //if there was a deleted slot, tje value would've changed, and will be at that real index.
        //insert at unfilled, deleted.
        table[deletedIndex] = HashEntry(key, val);
        num_elements++;

        if(this->load_factor() > maxLoadFactor){
            this->resizeAndRehash();
        }
    }

    //if there are actually no unfilled spots, or deleted slots, then increase capacity.
    else{
        resizeAndRehash();
        insert(key,val);
    }
    //find starting index based on first hash.
    
    //second is our offset,
    //first check starting index
    //then we loop, checking index + offset % capacity

    //make sure when SEARCHING to continue moving through even
    //if you see a deleted slot
    //HELP to keep track of the first deleted slot you see while proving

    //once we confirm key is not in possible slots
    //we then insert at first empty slot,
    //deleted or not
    //do normal resize checks on loadfactor


}


// removes the given key from the hash table - if the key is not in the list, throw an error
int DoubleHashTable::remove(std::string key) {
    //search through WHOLE table for key

    int hashIndex = hash(key);
    int offset = secondHash(key);
    int currentIndex = hashIndex;
    int elmChecked = 0;

    while(elmChecked < num_elements){
        if(table[currentIndex].isFilled && table[currentIndex].key == key){ //is filled and matching key

            int valRemoved = table[currentIndex].val;

            table[currentIndex].isFilled = false;
			table[currentIndex].key = "";
			table[currentIndex].val = 0;
			table[currentIndex].DELETED = true;
            
            num_elements--;
            return valRemoved;
        }


        //move to next index if //filled, and not same key.
        currentIndex = (currentIndex + offset) % capacity;
        elmChecked++;
    }

    //we get to this point, then it doesn't exist.
    throw std::out_of_range("Key doesn't exist");
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

    //prime - (key mod prime)
    //prime is a number less than table size
    //use isPrime() as a function to check if prime.
    //never evaluates to 0
    //all cells must be probed.

    int n = capacity;
    int prime;
    //find larget prime number smaller than table size
    while (n >= 2){
        if(isPrime(n)){
            prime = n;
            break;
        }
        n--;
    }
    
    //convert key to ascii
    int keyN = s.length();
    unsigned long key = 0;

    for (int i = 0; i < n; i++){
		key = key + static_cast<int>(s[i]);
	}

    //generate hash2
    int hash2 = prime - (key % prime);

    //make sure hash2 non-zero
    while(hash2 <= 0){
        hash2 += prime;
    }

    //make sure hash2 within range of table
    return hash2 % capacity;
}


#endif