#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include "AbstractPriorityQueue.h"
#include "PriorityQueueHeap.h"
#include "UnsortedPriorityQueue.h"
#include "SortedPriorityQueue.h"

using namespace std;

int main() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    PriorityQueueHeap<int> o1;
    UnsortedPriorityQueue<int> o2;
    SortedPriorityQueue<int> o3;

    vector<double> data;
    vector<int> inputs;

    int start_insertion_num = 10;
    for(int i = 0; i <= 100000; i+= 2500){

        auto t1 = high_resolution_clock::now();

        for (int k = 0; k < i; k++) {
            int z = rand() % 200 + 25;
            o3.pq_insert(z);
        }

        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;

        data.push_back(ms_double.count());
        inputs.push_back(i);

        cout << "iteration: " << i << endl;
    }

    ofstream outputFile("runtime_results.csv");
    if(!outputFile.is_open()){
        cerr << "Error: unable to open output file." << endl;
        return 1;
    }

    outputFile << "Input Size,Insertion Time (ms)" << endl;

    for(int i = 1; i < data.size(); i++){
        outputFile << inputs[i] << "," << data[i] << endl;
    }

    outputFile.close();

    cout << "data written to runtime_results.csv" << endl;
}
