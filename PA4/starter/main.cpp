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

    for (int i = 0; i < words.size(); i++) {
        std::string word = words[i];

        if(i == 302){
            //cout << "here" << endl;
        }

        if (!cht->contains(word)) { //if word not present in hashtble, insert it with a val of 1.
            
            cht->insert(word, 1);
            
        } else {
            int curVal = cht->get(word);
            
            cht->insert(word, curVal + 1); //if word is alr present, increment it's val by 1 and reinsert
    
        }


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

        cout << i << endl;
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
            return 0;
        } 
        if (cht->getSize() != actualMap.size()) {
            return 0;
        }
    }

    cout << "remove passed" << endl;

}