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

    cout << "Chaining Hash Table" << endl;
    AbstractHashTable* cht = new ChainingHashTable();
    std::unordered_map<string, int> actualMap;

    int count = 0;
    cout << words.size() << endl;

    for (int i = 0; i < words.size(); i++) {
        std::string word = words[i];

        if (!cht->contains(word)) { //if word not present in hashtble, insert it with a val of 1.
            cht->insert(word, 1);
        } else {
            int curVal = cht->get(word);
            cht->insert(word, curVal + 1); //if word is alr present, increment it's val by 1 and reinsert
        }

        if (actualMap.find(word) != actualMap.end()) { //if word is present in actual map, increment by 1.
            actualMap[word] += 1;
        } else {
            actualMap[word] = 1; //this runs //not present, insert it with a count of 1.
        }
        cout << i << endl;
    }
    cout << "insertion complete" << endl;
    //after inserting all words, compare the counts of each word in hash and actual map
    for (auto it = actualMap.cbegin(); it != actualMap.cend(); it++) {
       if (actualMap[it->first] != cht->get(it->first)) {
            return 0; //doesnt match
       }
    }

    if (actualMap.size() != cht->getSize()) {
        return 0; //unique word count dont match
    }

    return 5;
}