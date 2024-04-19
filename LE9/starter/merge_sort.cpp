#include <iostream>
#include <thread>
using namespace std;

void merge(int *arr, int start, int med, int end);
void mergeSort_single(int* arr, int start, int end);

void mergeSort(int * arr, int start, int end, int level) {
    if(start >= end){
        return;
    } 

    if(start < end){

        if(level > 0){
            //multi-thread
            int med = start + (end - start) / 2;

            mergeSort(arr, start, med, level--);
            mergeSort(arr, med+1, end, level--);
            merge(arr, start, med, end);
        }
        else{
            //single-thread
            mergeSort_single(arr, start, end);
        }
    }

    
}

void mergeSort_single(int *arr, int start, int end){

    int med = start + (end - start) / 2;

    if(start >= end){
        return;
    }

    mergeSort_single(arr, start, med);
    mergeSort_single(arr, med+1, end);
    merge(arr, start, med, end);
}

void merge(int* arr, int start, int med, int end){
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
};