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

}

template <typename Type>
PriorityQueueHeap<Type>::~PriorityQueueHeap(){
   
}

template <typename Type>
int PriorityQueueHeap<Type>::pq_size() {
    return -1;
}

template <typename Type>
int PriorityQueueHeap<Type>::pq_parent(int i){
    return -1;
}

template <typename Type>
Type PriorityQueueHeap<Type>::pq_get_min(){
    return Type();
}

template <typename Type>
void PriorityQueueHeap<Type>::pq_insert(Type x) {
    
}


template <typename Type>
void PriorityQueueHeap<Type>::bubbleUp(int i){
    
}

template <typename Type>
Type PriorityQueueHeap<Type>::pq_delete(){
    return Type();
}

template <typename Type>
void PriorityQueueHeap<Type>::minHeapify(int i){
    
}

#endif