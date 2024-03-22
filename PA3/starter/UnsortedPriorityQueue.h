#ifndef UNSORTED_PRIORITY_QUEUE_H
#define UNSORTED_PRIORITY_QUEUE_H

#include "AbstractPriorityQueue.h"

template <typename Type>
class UnsortedPriorityQueue : public AbstractPriorityQueue<Type> {
    private:
        Type *arr;
        int capacity;
        int size;

    public:
        UnsortedPriorityQueue();

        ~UnsortedPriorityQueue();

        void pq_insert(Type value);

        Type pq_delete();

        Type pq_get_min();

        int pq_size();
};

template <typename Type>
UnsortedPriorityQueue<Type>::UnsortedPriorityQueue() {
    size = 0;
    capacity = 10;
    arr = new Type[capacity];
}

template <typename Type>
UnsortedPriorityQueue<Type>::~UnsortedPriorityQueue(){
    delete [] arr;
    capacity = 0;
    size = 0;
}

template <typename Type>
void UnsortedPriorityQueue<Type>::pq_insert(Type value) {
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

    arr[size] = value;
    size++;
}

template <typename Type>
Type UnsortedPriorityQueue<Type>::pq_delete(){
    if(size == 0){
        throw std::out_of_range("Unsorted Queue is empty.");
    }

    Type deleted = pq_get_min();
    for(int i = 0; i < size; i++){
        if(arr[i] == deleted){

            for(int j = i; j < size-1; j++){
                arr[j] = arr[j+1];
            }
            size--;
            i = size; //make it so that the parent for loop stops running in case there are multiple numbers with same value.
        }
        

    }

    return deleted;
}

template <typename Type>
Type UnsortedPriorityQueue<Type>::pq_get_min(){
    if(size == 0){
        throw std::out_of_range("Unsorted Queue is empty.");
    }

    Type min = arr[0];

    for(int i = 1; i < size; i++){
        if(arr[i] < min){
            min = arr[i];
        }
    }

    return min;
}

template <typename Type>
int UnsortedPriorityQueue<Type>::pq_size(){
    return size;
}

#endif