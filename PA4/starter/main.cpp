#include "AbstractHashTable.h"
#include "ChainingHashTable.h"
#include "ProbingHashTable.h"
#include "DoubleHashTable.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

enum OPERATION {
    INSERTION,
    DELETION
};

int main() {

    std::string filename = "dictionary.txt";
    std::ifstream file(filename);
    std::srand(time(NULL));
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 0;
    }

    vector<string> words;
    std::string word;
    while (file >> word) {
        words.push_back(word);
    }

    cout << "Double Hash Table" << endl;
    AbstractHashTable* cht = new DoubleHashTable();
    std::unordered_map<string, int> actualMap;

    int count = 0;
    cout << words.size() << endl;

    for (int i = 0; i < 100000; i++) {
        std::string word = words[i];

        if (!cht->contains(word)) { //if word not present in hashtble, insert it with a val of 1.
            
            cht->insert(word, 1);
            
        } else {
            int curVal = cht->get(word);
            
            cht->insert(word, curVal + 1); //if word is alr present, increment it's val by 1 and reinsert
    
        }

        cout << i << endl;

        if (actualMap.find(word) != actualMap.end()) { 
            // If the word is found in the actualMap
            actualMap[word] += 1;  // Increment the count associated with the word
            
        } else {
            // If the word is not found in the actualMap
            actualMap[word] = 1; // Add the word to the map with a count of 1
        }

        if(cht->get(word) != actualMap[word]) {
            cout << "actual: " << actualMap[word] << " hash: " << cht->get(word) << endl;
            cout << i <<endl;
        }

        
    }
    //cout << "insertion complete" << endl;
    //after inserting all words, compare the counts of each word in hash and actual map
    for (auto it = actualMap.cbegin(); it != actualMap.cend(); it++) {
       if (actualMap[it->first] != cht->get(it->first)) {
           
            cout <<"doesnt match" << endl;
            cout << "actual: " << actualMap[it->first] << " hash: " << cht->get(it->first) << endl;
            return 0;
       }
    }

    return 0;

    if (actualMap.size() != cht->getSize()) {

        cout << "unique word count dont match" << endl;
        return 0;
    }

    cout << "hash table isnert passed" << endl;

    if (actualMap.size() == 0) {
        cout << "You have not passed insert yet" << endl;
        return 0;
    }


    for (auto it = actualMap.cbegin(), next_it = it; it != actualMap.cend(); it = next_it) {
        ++next_it;
        string word = it->first;
        actualMap.erase(it);
        cht->remove(word);
        if (cht->contains(word)) {
            cout << "remove didn't work" << endl;
            return 0;
        } 
        if (cht->getSize() != actualMap.size()) {
            cout << "size doesn't match" << endl;
            return 0;
        }
    }

    cout << "remove passed" << endl;

    
    std::unordered_map<string, int> tempMap;
    for (int i = 0; i < 10000 / 2; i++) {
        int rand_idx = rand() % 10000;
        int insert_or_delete = rand() % 2;
        if (insert_or_delete == OPERATION::INSERTION) {
            if (tempMap.find(words[rand_idx]) != tempMap.end()) {
                tempMap[words[rand_idx]] += 1;
            } else {
                tempMap[words[rand_idx]] = 1;
            }
            if (cht->contains(words[rand_idx])) {
                int curValue = cht->get(words[rand_idx]);
                cht->insert(words[rand_idx], curValue + 1);
            } else {
                cht->insert(words[rand_idx], 1);
            }
        }
        else if (insert_or_delete == OPERATION::DELETION) {
            if (tempMap.find(words[rand_idx]) != tempMap.end()) {
                tempMap.erase(tempMap.find(words[rand_idx]));
            } 
            if (cht->contains(words[rand_idx])) {
                cht->remove(words[rand_idx]);
            } else {
                try {
                    cht->remove(words[rand_idx]);
                } catch (std::out_of_range& e) {
                    continue;
                }
            }
        }
    }

    for (auto it = tempMap.cbegin(); it != tempMap.cend(); it++) {
       if (tempMap[it->first] != cht->get(it->first)) {
            return 0;
       }
    }

    if (tempMap.size() != cht->getSize()) {
        return 0;
    }

    cout << "insert + removed passed" << endl;

}