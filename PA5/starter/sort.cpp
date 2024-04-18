#include <iostream>
#include <queue>

using namespace std;

void merge(int *arr, int start, int med, int end);
int partition(int *arr, int start, int end);

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

    if(start >= end){
        return;
    }

    //determine the median (pivot)
    int med = start + (end - start) / 2;

    mergeSort(arr, start, med); //mergesort (recursion arr1)
    mergeSort(arr, med+1, end); //mergesort (recursion arr2)
    merge(arr, start, med, end); //merge (arr1 and arr2, into arr)

}

void merge(int *arr, int start, int med, int end){
    
    //determine sizes for partitions
    int size1 = med - start + 1;
    int size2 = end - med;

    //crete temp partitions
    auto arr1 = new int[size1];
    auto arr2 = new int[size2];

    //copy data to temp partitions
    for(int i = 0; i < size1; i++){
        arr1[i] = arr[start + i];
    }
    for(int i = 0; i < size2; i++){
        arr2[i] = arr[med + 1 + i];
    }

    //merge temp partitions back into arr
    int i = 0;
    int j = 0;
    int k = start;
    while(i < size1 && j < size2){
        if(arr1[i] <= arr2[j]){
            arr[k] = arr1[i];
            i++; 
        }

        else{
            arr[k] = arr2[j];
            j++;
        }

        k++;
    }

    //copy remaining elements of left partition
    while(i < size1){
        arr[k] = arr1[i];
        i++;
        k++;
    }

    //copy remaining elements of right partition
    while(j < size2){
        arr[k] = arr2[j];
        j++;
        k++;
    }

    //delete temp partitions
    delete [] arr1;
    delete [] arr2;
}

void quickSort(int *arr, int start, int end) {
    

    if(start >= end){
        return;
    }

    //create pivot index, and one iteration of swapping elements
    int pivot = partition(arr, start, end);

    //recursively sort partitions -> divide + conqeuer
    quickSort(arr, start, pivot - 1);
    quickSort(arr, pivot + 1, end);
}

int partition(int *arr, int start, int end){
    //return a pivot index using median

    //initialize at start
    int pivotVal = arr[start];

    int countLess = 0;

    //iterate through the array, skipping first element
    for(int i = start + 1; i <= end; i++){
        if(arr[i] <= pivotVal){ //count how many elements less than the pivot.
            countLess++;
        }
    }

    int pivotIndex = start + countLess; //the pivot index, is after #elements less than pivotVal
    //swap pivotVal with the pivotIndex's val, to makesure the pivotIndex reflects actual pivotVal
    int temp = arr[start];
    arr[start] = arr[pivotIndex];
    arr[pivotIndex] = temp;

    //sort the array
    int i = start;
    int j = end;

    while(i < pivotIndex && j > pivotIndex){ //while i and j are not at pivotIndex yet,

        //if i value is less than pivotVal, move toward pivot
        while(arr[i] <= pivotVal){
            i++;
        }

        //if j value is greater than pivotVal, move toward pivot
        while(arr[j] > pivotVal){
            j--;
        }

        //once we've gone through while loops, we know that i and j are at the wrong side of the pivot

        if(i < pivotIndex && j > pivotIndex){ //if i and j are not at pivotIndex yet, but at the wrong side of the pivot
            //swap the elements
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            //move i and j toward pivot
            i++;
            j--;
        }

        //this if statement continues for all values at the wrong side of the pivot
    }

    return pivotIndex;

}   