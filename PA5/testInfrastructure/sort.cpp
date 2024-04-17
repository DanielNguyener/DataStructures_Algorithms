#include <iostream>
#include <queue>

using namespace std;

void bubbleSort(int *arr, int size){
    //while not completed,
    // do passes to swap.

    int i;
    int j;

    for(int i = 0; i < size-1; i++){

        for(int j = 0; j < size-i-1; j++){
            if(arr[j] > arr[j+1]){
                //swap
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void heapSort(int *arr, int size){
    //use queue

    //min-heap
    priority_queue<int, vector<int>, greater<int>> pq;

    for(int i = 0; i < size; i++){
        pq.push(arr[i]);
    }

    for(int i = 0; i < size; i++){
        arr[i] = pq.top();
        pq.pop();
    }
}

void mergeSort(int * arr, int start, int end) {
    
}

void quickSort(int *arr, int start, int end) {
    // use median of three
}
