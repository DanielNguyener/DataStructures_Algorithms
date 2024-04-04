#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>

using namespace std;

template <typename Type>
class PriorityQueueHeap : public AbstractPriorityQueue<Type> {
private:
    Type *arr;
    int capacity;
    int size;
    
    void minHeapify(int i);
    void bubbleUp(int i);
    int pq_parent(int i);

public:
    PriorityQueueHeap();

    ~PriorityQueueHeap();

    int pq_size();
    
    Type pq_get_min();

    void pq_insert(Type value);

    Type pq_delete();
};

// Your implementation here

template <typename Type>
PriorityQueueHeap<Type>::PriorityQueueHeap(){
    capacity = 10;
    size = 0;
    arr = new Type[capacity];
}

template <typename Type>
PriorityQueueHeap<Type>::~PriorityQueueHeap(){
    delete[] arr;
    capacity = 0;
    size = 0;
}

template <typename Type>
int PriorityQueueHeap<Type>::pq_size() {
    return size;
}

template <typename Type>
int PriorityQueueHeap<Type>::pq_parent(int i){
    if(i % 2 == 0){
        return (i - 2) / 2;
    }else{
        return (i - 1) / 2;
    }
}

template <typename Type>
Type PriorityQueueHeap<Type>::pq_get_min(){
    if(size == 0){
        throw std::out_of_range("Priority Queue is Empty.");

    }
    return arr[0];
}

template <typename Type>
void PriorityQueueHeap<Type>::pq_insert(Type x) {
    if(size == capacity){
        
        //increase capacity, perform resizing
        //double
        int newCapacity = capacity * 2;
        //new array
        Type *newArr = new Type[newCapacity];
        //copy over elements
        for(int i = 0; i < size; i++){
            newArr[i] = arr[i];
        }
        //delete old array
        delete[] arr;
        //assign array as the new one.
        arr = newArr;
        //update capacity
        capacity = newCapacity;
    }

    //proceed to insertion.
    size++;
    arr[size - 1] = x;
    //perform bubbleup to fix
    if(size > 1){
        bubbleUp(size - 1);
    }
}


template <typename Type>
void PriorityQueueHeap<Type>::bubbleUp(int i){
    //min heap.
    //while parent node is greater
    while(i > 0 && (arr[pq_parent(i)] > arr[i])){
        //swap if compare is true

        int temp = arr[pq_parent(i)];
        arr[pq_parent(i)] = arr[i];
        arr[i] = temp;

        i = pq_parent(i); //new index
    }
}

template <typename Type>
Type PriorityQueueHeap<Type>::pq_delete(){
    if(size == 0){
        throw std::out_of_range("Priority Queue is Empty.");
    }

    Type root = arr[0];
    arr[0] = arr[size - 1]; //new root will be the last node.
    size--;

    //now fix heap.
    minHeapify(0);

    //return removed node.
    return root;
}

template <typename Type>
void PriorityQueueHeap<Type>::minHeapify(int i){
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int min_max = i;
    int temp;

    //left then right...
    // max-heap : root node is greater than children, left child is greater than right child
    // min-heap : root node is less than children, left child is less than right child

    //compare will be true if a > b (min heap) or a < b (max heap) 
    // min-heap: if left is greater. swap
    // max-heap: if left is less. swap
    // make sure still in bounds...

    
    if(left < size && (arr[left] < arr[min_max])){
        min_max = left;
        //new min_max is now the left -> to be swapped
    }

    if(right < size && (arr[right] < arr[min_max])){
        min_max = right;
    }

    //if one of the children needs to be swapped with current
    //then current will not be min_max
    //swap and recursively call with the new current node
    if(min_max != i){
        //swap
        // int temp = arr[i];
        // arr[i] = min_max;
        // arr[min_max] = temp;

        int temp = arr[min_max];
        arr[min_max] = arr[i];
        arr[i] = temp;

        //recursively call
        minHeapify(min_max);
    }
}

#endif