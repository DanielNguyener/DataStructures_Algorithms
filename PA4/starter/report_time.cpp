#include "AbstractHashTable.h"
#include "ChainingHashTable.h"
#include "ProbingHashTable.h"
#include "DoubleHashTable.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstdlib>
#include <unordered_set>

using namespace std;

enum OPERATION {
    INSERTION,
    DELETION
};

int main() {

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    AbstractHashTable* o1 = new ChainingHashTable();
    AbstractHashTable* o2 = new ProbingHashTable();
    AbstractHashTable* o3 = new DoubleHashTable();
    
    vector<double> data;
    vector<int> inputs;


    //generate random lowercase strings of length 5-12
     std::unordered_set<std::string> words;
     std::vector<std::string> unique_words;
    while(words.size() < 1000000){
        int length = rand() % 7 + 5;
        string word;
        for(int j = 0; j < length; j++){
            word += static_cast<char>(rand() % 26 + 97);
        }
        
        if(words.find(word) == words.end()){
            words.insert(word);
            unique_words.push_back(word);
        }
    }

<<<<<<< HEAD
    for(int i = 0; i < 10000; i+=10){
=======
    for(int i = 0; i < 100000; i+=100){
>>>>>>> d8efb80b235abf66871162baa51dcfa650700deb

        auto t1 = high_resolution_clock::now();

        for(int j = 0; j < i; j++){
            string word = unique_words[j];

            //only insert unique words
<<<<<<< HEAD
            o3->insert(word, 1);
=======
            o2->insert(word, 1);
>>>>>>> d8efb80b235abf66871162baa51dcfa650700deb
            
        }

        auto t2 = high_resolution_clock::now();

        duration<double, std::milli> ms_double = t2 - t1;
        data.push_back(ms_double.count());
        inputs.push_back(i);

        cout << i << endl;
    }

<<<<<<< HEAD
    for(int i = 10000; i < 1000000; i+=5000){
=======
    for(int i = 100000; i < 1000000; i+=5000){
>>>>>>> d8efb80b235abf66871162baa51dcfa650700deb
        auto t1 = high_resolution_clock::now();

        for(int j = 0; j < i; j++){
            string word = unique_words[j];

            //only insert unique words
<<<<<<< HEAD
            o3->insert(word, 1);
=======
            o2->insert(word, 1);
>>>>>>> d8efb80b235abf66871162baa51dcfa650700deb

        }

        auto t2 = high_resolution_clock::now();

        duration<double, std::milli> ms_double = t2 - t1;
        data.push_back(ms_double.count());
        inputs.push_back(i);

<<<<<<< HEAD
        if(ms_double.count() > 10000){
            break;
        }

        cout << i << endl;
=======
        cout << i << endl;

        if(ms_double.count() >= 20000){
            break;
        }
>>>>>>> d8efb80b235abf66871162baa51dcfa650700deb
    }



<<<<<<< HEAD
    ofstream outputFile("o3.csv");
=======
    ofstream outputFile("o2.csv");
>>>>>>> d8efb80b235abf66871162baa51dcfa650700deb
    if(!outputFile.is_open()){
        cerr << "Error: unable to open output file." << endl;
        return 1;
    }

    outputFile << "Input Size,Insertion Time (ms)" << endl;

    for(int i = 1; i < data.size(); i++){
        outputFile << inputs[i] << "," << data[i] << endl;
    }

    outputFile.close();

    cout << "data written to .csv" << endl;

}