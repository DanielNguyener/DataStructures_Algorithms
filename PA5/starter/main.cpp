#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <vector>
#include <fstream>
#define TEST
#include "sort.cpp"

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;

enum SORT_TYPE {
    BUBBLE_SORT,
    HEAP_SORT,
    MERGE_SORT,
    QUICK_SORT
};

double testSort(SORT_TYPE sort_type, int n) {

    int *arr = new int[n];

    for(int j=0; j<n; j++){
        arr[j] = rand() % 1000000 + 1;  // Random numbers between 1 and 10^6
    }

    auto start = std::chrono::high_resolution_clock::now();

    if (sort_type == SORT_TYPE::BUBBLE_SORT) {
       bubbleSort(arr, n);
    } else if (sort_type == SORT_TYPE::HEAP_SORT) {
       heapSort(arr, n);
    } else if (sort_type == SORT_TYPE::MERGE_SORT) {
        mergeSort(arr, 0, n - 1);
    } else if (sort_type == SORT_TYPE::QUICK_SORT) {
        quickSort(arr, 0, n - 1);
    }

    auto end = std::chrono::high_resolution_clock::now();

    duration<double> elapsed = end - start;
    
    return elapsed.count();

};

int main() {
    
    vector<int> inputs1;
    vector<double> data1;
    cout << "Testing Bubble Sort:" << endl;
    for(int i = 0; i < 100000; i+=5000){
        cout << "bubble: " << i << endl;
        data1.push_back(testSort(SORT_TYPE::BUBBLE_SORT, i));
        inputs1.push_back(i);
    }

    ofstream outputFile1("BubbleSort.csv");
    outputFile1 << "Input Size,Insertion Time (s)" << endl;

    for(int i = 1; i < data1.size(); i++){
        outputFile1 << inputs1[i] << "," << data1[i] << endl;
    }
    outputFile1.close();


    vector<double> data2;
    vector<int> inputs2;
    cout << "Testing Heap Sort:" << endl;
    for(int i = 0; i < 1000000; i+=5000){
        cout << "heap: " << i << endl;
        data2.push_back(testSort(SORT_TYPE::HEAP_SORT, i));
        inputs2.push_back(i);
    }
    ofstream outputFile2("HeapSort.csv");
    outputFile2 << "Input Size,Insertion Time (s)" << endl;

    for(int i = 1; i < data2.size(); i++){
        outputFile2 << inputs2[i] << "," << data2[i] << endl;
    }
    outputFile2.close();
    
    vector<double> data3;
    vector<int> inputs3;
    cout << "Testing Merge Sort:" << endl;
    for(int i = 0; i < 1000000; i+=5000){
        cout << "merge: " << i << endl;
        data3.push_back(testSort(SORT_TYPE::MERGE_SORT, i));
        inputs3.push_back(i);
    }
    ofstream outputFile3("MergeSort.csv");
    outputFile3 << "Input Size,Insertion Time (s)" << endl;

    for(int i = 1; i < data3.size(); i++){
        outputFile3 << inputs3[i] << "," << data3[i] << endl;
    }
    outputFile3.close();
    
    vector<double> data4;
    vector<int> inputs4;
    cout << "Testing Quick Sort:" << endl;
    for(int i = 0; i < 1000000; i+=5000){
        cout << "quick: " << i << endl;
        data4.push_back(testSort(SORT_TYPE::QUICK_SORT, i));
        inputs4.push_back(i);
    }
    ofstream outputFile4("QuickSort.csv");
    outputFile4 << "Input Size,Insertion Time (s)" << endl;

    for(int i = 1; i < data4.size(); i++){
        outputFile4 << inputs4[i] << "," << data4[i] << endl;
    }
    outputFile4.close();

}