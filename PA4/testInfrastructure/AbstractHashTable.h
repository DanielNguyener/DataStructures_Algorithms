#ifndef HASH_H
#define HASH_H

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cmath>

using namespace std;

class AbstractHashTable {
	protected:
		struct HashEntry {
			string key;
			int val;
			bool isFilled;
			bool DELETED;

			HashEntry() {
				isFilled = false;
				key = "";
				val = 0;
				DELETED = false;
			};

			HashEntry(std::string word, int value) {
				key = word;
				val = value;
				isFilled = true;
				DELETED = false;
			}
		};
		int capacity;
		int num_elements;
		float maxLoadFactor;
		// helper functions
		int hash(std::string s) const; 
		int findNextPrime(int n) const;
		bool isPrime(int n) const;
		float load_factor() const;
		virtual void resizeAndRehash() = 0;
		
	public: 
		AbstractHashTable();
		virtual ~AbstractHashTable() {}; 
		virtual void insert(std::string key, int val) = 0; 
		virtual int remove(std::string key) = 0; 
		virtual int get(std::string key) const = 0; 
		virtual bool contains(std::string key) const = 0;
		int getSize() const;
};


///////////////////// TODO: FILL OUT THE FUNCTIONS /////////////////////

AbstractHashTable::AbstractHashTable() {
	capacity = 11;
	num_elements = 0;
	maxLoadFactor = 11;

}

// hash function to determine index where string key goes, as mentioned in the instructions
int AbstractHashTable::hash(std::string s) const {
	//takes string

	unsigned long hash = 0;
	int n = s.length();
	int c = 5; //constant chosen

	//for the length of given string, hash = constant times ascii of each character
	for (int i = 0; i < n; i++){
		hash = c * hash + static_cast<int>(s[i]);
	}

	//index will be hash modulo capacity
	int index = hash % capacity;
	
	return index;
}

int AbstractHashTable::getSize() const {
	return num_elements;
}

float AbstractHashTable::load_factor() const {
	return (static_cast<double>(num_elements)/capacity); 
}

int AbstractHashTable::findNextPrime(int n) const {
	//use isPrime to check next prime number > n

	n++;
	while(!isPrime(n)){
		n++;
	}
	
	return n;
}

// Function to check if a number is prime
bool AbstractHashTable::isPrime(int n) const {
	if(n <= 1){ //check if it's 1
		return false;
	}

	if(n <= 3){ //check 2 and 3
		return true;
	}

	//check multiples of 2 and 3
	if(n % 2 == 0 || n % 3 == 0){ 
		return false;
	}

	//check if divisible, from 5 to floor(n)/2.
	for(int i = 5; i < floor(n)/2; i+=2){
		if(n % i == 0){
			return false;
		}
	}

    return true;
}

#endif