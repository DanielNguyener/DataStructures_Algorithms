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
        prevPrime = 7;
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

        int hashIndex = hash(key);
        int offset = secondHash(key);
        int currentIndex = hashIndex;
        int deletedIndex = -1;
        int elm_checked = 0;
        bool found = false;


        while(true){
            if(!table[currentIndex].isFilled || table[currentIndex].DELETED){ //not filled OR DELETED
                
                //deletedindex hasn't been changed, so it's the first free slot that is deleted.
                if(table[currentIndex].DELETED && deletedIndex == -1) {
                    //store the index.
                    deletedIndex = currentIndex;
                }

                if(!table[currentIndex].DELETED && !table[currentIndex].isFilled){ //not filled & not deleted
                    //insert
                    table[currentIndex] = HashEntry(key, val);

                    num_elements++;
                    found = true;
                    break; // finished inserting at first non-filled not-deleted.
                }
            }
            else if(table[currentIndex].isFilled && table[currentIndex].key == key){ //filled, and key exists.
                //update
                table[currentIndex].val = val;
                found = true;


                break; //finished updating
            }

            //move to next index if //filled, and not same key.
            currentIndex = (currentIndex + offset) % capacity;
            elm_checked++;
            if(elm_checked >= capacity){ //we've checked all slots
                break;
            }
        }

        if(load_factor() > maxLoadFactor){
            resizeAndRehash();
        }

        if(found){
            return;
        }

        //if we haven't returned already. that means all slots are occupied or deleted.
        if(deletedIndex != -1 && !found){ //if there was a deleted slot, the value would've changed, and will be at that real index.
            //insert at unfilled, deleted.
            table[deletedIndex] = HashEntry(key, val);
            num_elements++;
            return;
        }

        //if there are actually no unfilled spots, or deleted slots, then increase capacity.
        else{
            resizeAndRehash();
            insert(key,val);
        }

    }


    // removes the given key from the hash table - if the key is not in the list, throw an error
    int DoubleHashTable::remove(std::string key) {
        //search through WHOLE table for key

        int hashIndex = hash(key);
        int offset = secondHash(key);
        int currentIndex = hashIndex;
        int elmChecked = 0;
        int valRemoved = 0;

        while(true){
            if(table[currentIndex].isFilled && table[currentIndex].key == key){ //is filled and matching key

                valRemoved = table[currentIndex].val;

                table[currentIndex].isFilled = false;
                table[currentIndex].key = "";
                table[currentIndex].val = 0;
                table[currentIndex].DELETED = true;
                
                num_elements--;
                break;
            }


            //move to next index if //filled, and not same key.
            currentIndex = (currentIndex + offset) % capacity;
            elmChecked++;

            if(elmChecked >= capacity){ //we've checked all slots
                break;
            }
        }

        if(valRemoved == 0){
            throw std::out_of_range("Key not found");
        }
        
    }

    // getter to obtain the value associated with the given key
    int DoubleHashTable::get(std::string key) const {
        
        int hashIndex = hash(key);
        int offset = secondHash(key);
        int currentIndex = hashIndex;
        int elm_checked = 0;

        while(elm_checked < capacity){
            if(table[currentIndex].key == key && table[currentIndex].isFilled){
                return table[currentIndex].val;
            }

            else{
                currentIndex = (currentIndex + offset) % capacity;
                elm_checked++;
            }
        }
        if(elm_checked >= capacity){
            throw std::out_of_range("Key not found");
        }
    }

    bool DoubleHashTable::contains(std::string key) const {

        int hashIndex = hash(key);
        int offset = secondHash(key);
        int currentIndex = hashIndex;
        int elm_checked = 0;

        while(elm_checked < capacity){
            if(table[currentIndex].key == key && table[currentIndex].isFilled){
                return true;
            }

            currentIndex = (currentIndex + offset) % capacity;
            elm_checked++;
        }

        return false;
    }

void DoubleHashTable::resizeAndRehash() {

    
    int newCapacity = findNextPrime(2 * capacity);
    prevPrime = findPrevPrime(newCapacity); // Increase capacity more gradually
    capacity = newCapacity;

    // Create a temporary table for rehashing without clearing the existing table
    std::vector<HashEntry> newTable(newCapacity);

    // Rehash existing elements into the new table
    for (const auto& entry : table) {
        if (entry.isFilled) {
            int currentIndex = hash(entry.key); // Primary hash
            int offset = secondHash(entry.key); // Secondary hash

            while(true) {
                if(!newTable[currentIndex].isFilled){
                    newTable[currentIndex] = entry;
                    break;
                }
                currentIndex = (currentIndex + offset) % newCapacity;
            }
        }
    }

    // Move the new table into the existing table, avoiding unnecessary memory reallocation
    table = std::move(newTable);
}

    // helper functions 
    int DoubleHashTable::secondHash(std::string s) const {
        
        //use a prime number close to capacity
        int prime = prevPrime;

        //hash ascii of key
        unsigned long hash = 0;
        int n = s.length();
        int c = 5;
        for (int i = 0; i < n; i++){
            hash = c * hash + static_cast<int>(s[i]);
        }

        // Calculate hash2 using the chosen prime number
        int hash2 = prime - (hash % prime);

        // Ensure hash2 is non-zero
        if (hash2 <= 0) {
            hash2 += prime;
        }

        return hash2;
    }


    #endif