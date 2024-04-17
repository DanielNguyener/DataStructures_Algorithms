#include <iostream>
#include "SortedPriorityQueue.h"
#include <vector>

using namespace std;

int getMax(int *arr, int n);
void countSort(int *arr, int n, int exp);


void radixSort(int *arr, int n) {

    int max = getMax(arr, n); // get max number, tells us how many digits.

    //do sort for each digit
    //pass exponent to get current digit number
    for(int exp = 1; max/exp > 0; exp *= 10){
        countSort(arr, n, exp);
    }

}

//get the max number (to determine digits)
int getMax(int *arr, int n){
    
    int max = arr[0];

    for(int i = 1; i < n; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }

    return max;
}

// sort arr, according to count of digits at exponent
void countSort(int *arr, int n, int exp){
    //array to return
    int out[n];

    //array to store count of each digit
    int count[10];
    for(int i = 0; i < 10; i++){
        count[i] = 0;
    }
    

    // for every element of array, count occurances of digit_val.
    for(int i = 0; i < n; i++){
        int digit_val = (arr[i] / exp) % 10; //extract digit value at exponent
        count[digit_val]++; //increment count for that digit
    }

    //for digit vals 1-9, add the count of previous digit.
    for(int i = 1; i < 10; i++){
        count[i] += count[i-1];

        //this ensures stable sort, maintains relative order of elements with same digit value.
    }

    for(int i = n-1; i >= 0; i--){ //from end of array

        int digit_val = (arr[i] / exp) % 10; //extract digit value at exponent

        //determine new position for element, given by the count of current digit_val.
        int new_pos = count[digit_val] - 1;
        //store current element at new position
        out[new_pos] = arr[i];

        count[digit_val]--; //decrement count for that digit
    }

    //copy out to arr
    for(int i = 0; i < n; i++){
        arr[i] = out[i];
    }

}

void insertionSort(int *arr, int n) {
    SortedPriorityQueue<int> data;

    for(int i = 0; i < n; i++){
        data.pq_insert(arr[i]);
    }

    for(int i = 0; i < n; i++){
        arr[i] = data.pq_delete();
    }
}
