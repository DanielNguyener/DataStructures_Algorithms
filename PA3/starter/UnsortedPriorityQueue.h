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
    
}

template <typename Type>
UnsortedPriorityQueue<Type>::~UnsortedPriorityQueue(){
    
}

template <typename Type>
void UnsortedPriorityQueue<Type>::pq_insert(Type value) {
    
}

template <typename Type>
Type UnsortedPriorityQueue<Type>::pq_delete(){
    return Type();
}

template <typename Type>
Type UnsortedPriorityQueue<Type>::pq_get_min(){
    return Type();
}

template <typename Type>
int UnsortedPriorityQueue<Type>::pq_size(){
    return -1;
}

#endif