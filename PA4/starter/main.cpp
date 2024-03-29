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

    for (int i = 0; i < words.size(); i++) {
        std::string word = words[i];
        if (!cht->contains(word)) {
            cht->insert(word, 1);
        } else {
            int curVal = cht->get(word);
            cht->insert(word, curVal + 1);
        }

        if (actualMap.find(word) != actualMap.end()) {
            actualMap[word] += 1;
        } else {
            actualMap[word] = 1;
        }
    }

    for (auto it = actualMap.cbegin(); it != actualMap.cend(); it++) {
       if (actualMap[it->first] != cht->get(it->first)) {
            cout << "fail test 1" << endl;
       }
    }

    if (actualMap.size() != cht->getSize()) {
        cout << "fail test 2" << endl;
    }

    return 0;
}