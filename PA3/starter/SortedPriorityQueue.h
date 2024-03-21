#ifndef SORTED_PRIORITY_QUEUE_H
#define SORTED_PRIORITY_QUEUE_H

#include "AbstractPriorityQueue.h"

template <typename Type>
class SortedPriorityQueue : public AbstractPriorityQueue<Type> {
    private:
        Type *arr;
        int capacity;
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
 
}

template <typename Type>
SortedPriorityQueue<Type>::~SortedPriorityQueue(){
   
}

template <typename Type>
void SortedPriorityQueue<Type>::pq_insert(Type value) {
    
}

template <typename Type>
Type SortedPriorityQueue<Type>::pq_delete(){
    return Type();
}

template <typename Type>
Type SortedPriorityQueue<Type>::pq_get_min(){
    return Type();
}

template <typename Type>
int SortedPriorityQueue<Type>::pq_size(){
    return -1;
}

#endif