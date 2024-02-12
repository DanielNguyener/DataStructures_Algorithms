#ifndef STACK_LINEAR_ARRAY_H
#define STACK_LINEAR_ARRAY_H
#include "AbstractStack.h"

template <typename T>
class StackArrayLinear : public AbstractStack<T> {
private:
    T* data;
    int length;
    int topIndex;

public:
    StackArrayLinear();

    ~StackArrayLinear();

    StackArrayLinear(const StackArrayLinear& other);

    StackArrayLinear& operator=(const StackArrayLinear& other);

    bool isEmpty();

    int size();

    T& top();

    T pop();

    void push(const T& e);

};

// Your implementation here
template <typename T>
StackArrayLinear<T>::StackArrayLinear(){
        //constructor

    const int start_capacity = 1; //initialize to size 1
    data = new T[start_capacity];
    length = start_capacity; // update length
    topIndex = -1; // empty stack
}

template <typename T>
StackArrayLinear<T>::~StackArrayLinear(){
    // deconstructor

    delete [] data;
    data = nullptr;
    topIndex = -1;
    length = 0;    
}

template <typename T>
StackArrayLinear<T>::StackArrayLinear(const StackArrayLinear& other) {
    // copy constructor iterates through current stack
    //create another stack

    topIndex = other.topIndex; //update public variables
    length = other.length;
    data = new T[length];

    for (int i = 0; i <= topIndex; i++){
        data[i] = other.data[i];
    }
}

template <typename T>
StackArrayLinear<T>& StackArrayLinear<T>::operator=(const StackArrayLinear& other) {
    //copy assignment operator

    if(this != &other){ //check if current stack isn't the same as other
        delete [] data; // then empty current stack
    
    
        topIndex = other.topIndex; // update public variables
        length = other.length;
        data = new T[length]; // create new stack

        // populate stack
        for (int i = 0; i <= topIndex; i++){
            data[i] = other.data[i];
        }
    }
    return *this;
}

template <typename T>
bool StackArrayLinear<T>::isEmpty(){

    // if index indicates empty return true
    if(topIndex = -1){
        return true;
    }
    else{
        return false;
    }
}

template <typename T>
int StackArrayLinear<T>::size(){
    
    // size is based off of the index since length is based off
    // of allocated memory
    return topIndex + 1 ;
}

template <typename T>
T& StackArrayLinear<T>::top(){ // return element stored at the index

    //check if empty
    if(topIndex >= 0){
        return data[topIndex];
    }
    else {
        throw std::out_of_range("stack is empty...");
    }

}

template <typename T>
T StackArrayLinear<T>::pop(){ //remove element stored at index
    return -1;

    //check if empty
    if(topIndex >= 0){
        T element_popped = data[topIndex]; 
        topIndex--; // return element from the top and decrement index.
    }
    else{
        throw std::out_of_range("stack is empty...");
    }


    return -1;
}

template <typename T>
void StackArrayLinear<T>::push(const T& e){ //add new element, and resize if needed
    int newlength;
    //check if empty
    if(topIndex >= 0){

        //check if resizing is needed
        if(topIndex + 1 == length){
            //increase length by 10
            newlength = length + 10;
            //make new stack with new length
            T* newStack = new T[newlength];

            //copy elements to new stack
            for (int i = 0; i < length; i++){
                newStack[i] = data[i];
            }

            //update private variables
            length = newlength;
            //delete old stack
            delete [] data;
            // update data pointer to new stack
            data = newStack;
        }

        //increment the index
        topIndex++;
        // add the new element to top of stack.
        data[topIndex] = e;
    }
    else{
        throw std::out_of_range("stack is empty..");
    }


}

#endif