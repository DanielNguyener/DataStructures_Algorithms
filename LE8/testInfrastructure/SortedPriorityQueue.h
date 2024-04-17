#ifndef SORTED_PRIORITY_QUEUE_H
#define SORTED_PRIORITY_QUEUE_H
#include <iostream>
using namespace std;

template <typename Type>
class SortedPriorityQueue {
    private:
        Type *arr;
        int capacity;
        int startIndex;
        int size;

    public:
        SortedPriorityQueue();

        ~SortedPriorityQueue();

        void pq_insert(Type value);

        Type pq_delete();

        Type pq_get_min();

        int pq_size();
};

template <typename Type>
SortedPriorityQueue<Type>::SortedPriorityQueue() {
    size = 0;
    capacity = 10;
    arr = new Type[capacity];
}

template <typename Type>
SortedPriorityQueue<Type>::~SortedPriorityQueue(){
   delete[] arr;
    size = 0;
    capacity = 0;
    startIndex = 0;
}

template <typename Type>
void SortedPriorityQueue<Type>::pq_insert(Type value) {
    //must retain sorted structure at all times.
    if(size == capacity){
        int newCapacity = capacity * 2;
        Type *newArr = new Type[newCapacity];

        for(int i = 0; i < size; i++){
            newArr[i] = arr[i];
        }

        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
    }

    if(size == 0){
        arr[0] = value;
        size++;
    }

    else if(value >= arr[size-1]){
        arr[size] = value;
        size++;
    }

    else{
        int index = 0;
        while(index < size && arr[index] <= value){
            index++;
        }

        for(int i = size; i > index; i--){
            arr[i] = arr[i-1];
        }

        arr[index] = value;
        size++;

    }
}

template <typename Type>
Type SortedPriorityQueue<Type>::pq_delete(){
    if(size == 0){
            throw std::out_of_range("Sorted Queue is empty.");
    }


    Type deleted = arr[startIndex];
    
    if(startIndex < size){
        startIndex++;
    }
    
    return deleted;
}

template <typename Type>
int SortedPriorityQueue<Type>::pq_size(){
    return size;
}
#endif