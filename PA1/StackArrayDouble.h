#ifndef STACK_DOUBLE_ARRAY_H
#define STACK_DOUBLE_ARRAY_H
#include "AbstractStack.h"

template <typename T>
class StackArrayDouble : public AbstractStack<T> {
private:
    T* data;
    int length;
    int topIndex;

public:
    StackArrayDouble();

    ~StackArrayDouble();

    StackArrayDouble(const StackArrayDouble& other);

    StackArrayDouble& operator=(const StackArrayDouble& other);

    bool isEmpty();

    int size();

    T& top();

    T pop();

    void push(const T& e);

};

// Your implementation here

template <typename T>
StackArrayDouble<T>::StackArrayDouble(){
    //constructor
    data = new T[1];
    length = 1;
    topIndex = -1;
    
}

template <typename T>
StackArrayDouble<T>::~StackArrayDouble(){
    // deconstructor

    delete [] data;
    data = nullptr;
    length = 0;
    topIndex = -1;

}

template <typename T>
StackArrayDouble<T>::StackArrayDouble(const StackArrayDouble& other) {
    // copy constructor iterates through current stack
    //create another stack

    topIndex = other.topIndex; //update public variables
    length = other.length;
    data = new T[length];

    if(topIndex >= 0){
        for (int i = 0; i <= topIndex; i++){
        data[i] = other.data[i];
        }
    }

}

template <typename T>
StackArrayDouble<T>& StackArrayDouble<T>::operator=(const StackArrayDouble& other) {
    //copy assignment operator

    if(this != &other){ //check if current stack isn't the same as other
        delete [] data; // then empty current stack
    
    
        topIndex = other.topIndex; // update public variables
        length = other.length;
        data = new T[length]; // create new stack

        // populate stack
        if(topIndex >= 0){
            for (int i = 0; i <= topIndex; i++){
                data[i] = other.data[i];
            }  
        }
    }
    
    return *this;
}

template <typename T>
bool StackArrayDouble<T>::isEmpty(){

    // if index indicates empty return true
    if(topIndex == -1){
        return true;
    }
    else{
        return false;
    }
}

template <typename T>
int StackArrayDouble<T>::size(){
    
    // size is based off of the index since length is based off
    // of allocated memory
    
    //check empty
    if(topIndex == -1){
        return 0;
    }
    else{
        return (topIndex + 1);
    }
}

template <typename T>
T& StackArrayDouble<T>::top(){ // return element stored at the index

    //check if empty
    if(topIndex >= 0){
        return data[topIndex];
    }
    else {
        throw std::out_of_range("stack is empty...");
    }

}

template <typename T>
T StackArrayDouble<T>::pop(){ //remove element stored at index

    //check if empty
    if(topIndex >= 0){
        T element_popped = data[topIndex]; 
        topIndex--; // return element from the top and decrement index.
        return element_popped;
    }
    else{
        throw std::out_of_range("stack is empty...");
    }


}

template <typename T>
void StackArrayDouble<T>::push(const T& e){ //add new element, and resize if needed
    int newlength;

    //check if empty
    if(topIndex >= -1){

        //check if resizing is needed
        if(topIndex + 1 == length){
            //double the length
            newlength = length * 2;
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