#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
#include <iostream>

using namespace std;

template <typename Type, typename Compare = std::greater<Type>> //min heap
class PriorityQueueHeap {
private:
    Compare compare; //function object
    Type *arr;
    int capacity;
    int size;

    void heapify(int i);
    void bubbleUp(int i);
    int pq_parent(int i);

public:
    PriorityQueueHeap(); //constructor

    PriorityQueueHeap(const PriorityQueueHeap& other); //copy constructor

    PriorityQueueHeap(const Compare& comp); //constructor using comparison function

    PriorityQueueHeap& operator=(const PriorityQueueHeap& other); //copy assignment

    ~PriorityQueueHeap(); //destructor

    int pq_size();

    bool is_pq_empty();
    
    Type pq_top();

    void pq_insert(Type x);

    Type pq_delete();
};

// Your implementation here

template <typename Type, typename Compare>
PriorityQueueHeap<Type, Compare>::PriorityQueueHeap() : compare() {
    // default constructor
    // given size and capacity
    capacity = 10;
    size = 0;
    arr = new Type[capacity];

}

template <typename Type, typename Compare>
PriorityQueueHeap<Type, Compare>::~PriorityQueueHeap(){
    // destructor
    delete[] arr;
    capacity = 0;
    size = 0;
    
}

template <typename Type, typename Compare>
PriorityQueueHeap<Type, Compare>::PriorityQueueHeap(const Compare& _comp) {  // constructor using comparison function
   //compare is function object that tells you it's greater.
   compare = _comp;
   capacity = 10;
   size = 0;
   arr = new Type[capacity];
}

template <typename Type, typename Compare>
PriorityQueueHeap<Type, Compare>::PriorityQueueHeap(const PriorityQueueHeap& other) { //copy constructor
   capacity = other.capacity;
   size = other.size;
   compare = other.compare;

   arr = new Type[capacity];
   for(int i = 0; i < size; i++){
    arr[i] = other.arr[i];
   }

}

template <typename Type, typename Compare>
PriorityQueueHeap<Type, Compare>& PriorityQueueHeap<Type, Compare>::operator=(const PriorityQueueHeap& other) { //copy assignment
    if(this != &other){

        delete[] arr;

        compare = other.compare;
        capacity = other.capacity;
        size = other.size;

        arr = new Type[capacity];
        
        for(int i = 0; i < size; i++){
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

template <typename Type, typename Compare>
int PriorityQueueHeap<Type, Compare>::pq_size() {
    return size;
}

template <typename Type, typename Compare>
bool PriorityQueueHeap<Type, Compare>::is_pq_empty(){
    if(size < 1){
        return true;
    }else{
        return false;
    }
}

template <typename Type, typename Compare>
int PriorityQueueHeap<Type, Compare>::pq_parent(int i){
    //helper function for insert, returns index at 1/2 
    if(i % 2 == 0){
        return (i - 2) / 2;
    }else{
        return (i - 1) / 2;
    }
}

template <typename Type, typename Compare>
Type PriorityQueueHeap<Type, Compare>::pq_top(){
    // returns either the minimum (min heap)
    // or maximum (max heap)

    if(is_pq_empty()){
        throw std::out_of_range("Priority Queue is Empty.");

    }
   return arr[0];
}

template <typename Type, typename Compare>
void PriorityQueueHeap<Type, Compare>::pq_insert(Type x) {

    //check size
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


template <typename Type, typename Compare>
void PriorityQueueHeap<Type, Compare>::bubbleUp(int i){
    //helper function for insert
    //compare will return true to make node on left side whether or not min or max heap.

    //while index is not 0, starting at last node
    //if current is greater/less than the parent.. 
    while(i > 0 && compare(arr[pq_parent(i)], arr[i])){
        //swap if compare is true

        int temp = arr[pq_parent(i)];
        arr[pq_parent(i)] = arr[i];
        arr[i] = temp;

        i = pq_parent(i); //new index
    }

}

template <typename Type, typename Compare>
Type PriorityQueueHeap<Type, Compare>::pq_delete(){
    if(is_pq_empty()){
        throw std::out_of_range("Priority Queue is Empty.");
    }

    Type root = arr[0];
    arr[0] = arr[size - 1]; //new root will be the last node.
    size--;

    //now fix heap.
    heapify(0);

    //return removed node.
    return root;
}

template <typename Type, typename Compare>
void PriorityQueueHeap<Type, Compare>::heapify(int i){
   // helper function for delete
   //starts at index 0.

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
    if(left < size && compare(arr[min_max], arr[left])){
        min_max = left;
        //new min_max is now the left -> to be swapped
    }

    if(right < size && compare(arr[min_max], arr[right])){
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
        heapify(min_max);
    }


    
}

#endif