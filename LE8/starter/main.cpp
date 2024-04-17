#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <vector>
#define TEST
#include "sort.cpp"

int main() {
    
    int n = 100;
    int *arr = new int[n];
    vector<int> arrCopy;


    for(int j=0; j<n; j++){
        arr[j] = rand() % 100 + 1;  // Random numbers between 1 and 10^6
        arrCopy.push_back(arr[j]);
    }

    sort(arrCopy.begin(), arrCopy.end());

    radixSort(arr, n);

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