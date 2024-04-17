#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <vector>
#define TEST
#include "sort.cpp"

int main() {
    
    int n = 200000;
    int *arr = new int[n];
    vector<int> arrCopy;


    for(int j=0; j<n; j++){
        arr[j] = rand() % 1000000 + 1;  // Random numbers between 1 and 10^6
        arrCopy.push_back(arr[j]);
    }

    sort(arrCopy.begin(), arrCopy.end());

    insertionSort(arr, n);

    for(int i=0; i<n; i++){
        if (arrCopy[i] != arr[i]) {
            cout << "Failed" << endl;
            delete[] arr;
            return 0;
        }
    } 

    delete [] arr;
    cout << "Passed" << endl;
}