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

        if(load_factor() > maxLoadFactor){
            resizeAndRehash();
        }

        int hashIndex = hash(key);
        int offset = secondHash(key);
        int currentIndex = hashIndex;
        int deletedIndex = -1;
        int elm_checked = 0;
        bool found = false;

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
        
        currentIndex = (currentIndex + offset) % capacity;
        

    }while(currentIndex != hashIndex);

}


    // removes the given key from the hash table - if the key is not in the list, throw an error
    int DoubleHashTable::remove(std::string key) {
	int valRemoved = 0;
    int hashIndex = hash(key);
    int currentIndex = hashIndex;
    int offset = secondHash(key);

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

        currentIndex = (currentIndex + offset) % capacity;

    }while(currentIndex != hashIndex);
}

    // getter to obtain the value associated with the given key
    int DoubleHashTable::get(std::string key) const {
	int hashIndex = hash(key);
    int currentIndex = hashIndex;
    int offset = secondHash(key);

    do{
        if(table[currentIndex].key == key && !table[currentIndex].DELETED){
            return table[currentIndex].val;
        }else if(!table[currentIndex].isFilled && !table[currentIndex].DELETED){
            throw std::out_of_range("Key not found");
        }

        currentIndex = (currentIndex + offset) % capacity;
    }while(currentIndex != hashIndex);

    
}

    bool DoubleHashTable::contains(std::string key) const {
	int hashIndex = hash(key);
    int currentIndex = hashIndex;
    int offset = secondHash(key);

    do{
        if(!table[currentIndex].isFilled && !table[currentIndex].DELETED){
            return false;

        }else if(table[currentIndex].key == key && !table[currentIndex].DELETED){
            return true;
        }

        currentIndex = (currentIndex + offset) % capacity;
    }while(currentIndex != hashIndex);
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