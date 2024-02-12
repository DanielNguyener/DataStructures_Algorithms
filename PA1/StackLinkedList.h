#ifndef STACK_LinkedList_H
#define STACK_LinkedList_H
#include "AbstractStack.h"

template <typename T>
class Node {
public:

    T data;
    Node<T>* next;
};

template <typename T>
class StackLinkedList : public AbstractStack<T>{
private:
    Node<T>* head;
    int length;
public:
    StackLinkedList();

    ~StackLinkedList();

    StackLinkedList(const StackLinkedList& other);

    StackLinkedList& operator=(const StackLinkedList& other);

    bool isEmpty();

    int size();

    T& top();

    T pop();

    void push(const T& e);

};

// Your implementation here
template <typename T>
StackLinkedList<T>::StackLinkedList(){
    // constructor

    //initialize head and next to null
    head = nullptr;
    length = 0;

}

template <typename T>
StackLinkedList<T>::~StackLinkedList(){
    // deconstructor

    while(!isEmpty()){
        pop();
    }


}

template <typename T>
StackLinkedList<T>::StackLinkedList(const StackLinkedList& other) {
    // copy constructor
    head = nullptr;
    length = 0;

    //make sure isn't self assignment
    if(this != &other){

        //make sure the other linked list isn't empty
        if(other.head != nullptr){
            
            // temporary linked list
            StackLinkedList<T> temp;
            // temporary node
            Node<T>* tempNode = other.head;

            //while iterating through other list
            while(tempNode != nullptr){
                
                // we push the head of other into our tempoary
                temp.push(tempNode->data);
                tempNode = tempNode->next;
                
                // temp list will be reversed of other list
            }
            
            // we rest temp node to be the head of temp list
            tempNode = temp.head;

            //iterate through temp list
            while(tempNode != nullptr){
                
                // we push temp list data
                push(tempNode->data);
                tempNode = tempNode->next;
            }
            
            // now our list will be the reversed of temp list (which is reversed of other), and being equivalent to other list.
        }

    }
}

template <typename T>
StackLinkedList<T>& StackLinkedList<T>::operator=(const StackLinkedList& other) {
    //copy assignment operator

    //make sure isn't self assignment
    if(this != &other){

        //iterate, clear current list
        while(!isEmpty()){
            pop();
        }

        head = nullptr;
        length = 0;

        //make sure the new list isn't empty
        if(other.head != nullptr){

            // temporary linked list
            StackLinkedList<T> temp;
            // temporary node
            Node<T>* tempNode = other.head;

            //while iterating through other list
            while(tempNode != nullptr){
                
                // we push the head of other into our tempoary
                temp.push(tempNode->data);
                tempNode = tempNode->next;
                
                // temp list will be reversed of other list
            }
            
            // we rest temp node to be the head of temp list
            tempNode = temp.head;

            //iterate through temp list
            while(tempNode != nullptr){
                
                // we push temp list data
                push(tempNode->data);
                tempNode = tempNode->next;
            }
            
            // now our list will be the reversed of temp list (which is reversed of other), and being equivalent to other list.
        }
    }

    return *this;
}

template <typename T>
bool StackLinkedList<T>::isEmpty(){
    if(length == 0){
        return true;
    }
    else{
        return false;
    }
}

template <typename T>
int StackLinkedList<T>::size(){
    //should be the same as length?
    return length;
}

template <typename T>
T& StackLinkedList<T>::top(){
    
    //check if list is empty
    if(!this->isEmpty()){
        return head->data;
    }
    else{
        throw std::out_of_range("stack is empty");
    }
}

template <typename T>
T StackLinkedList<T>::pop(){
    //remove head element

    //check if list is empty
    if(isEmpty()){
        throw std::out_of_range("stack is empty");
    }
    else{
        
        //store the data from current head to return later
        T popElement = head->data;

        //store the head that will be deleted
        Node<T>* deleteHead = head;

        //set new head
        head = head->next;
        length--;

        //delete old head
        delete deleteHead;

        return popElement;

    }
}

template <typename T>
void StackLinkedList<T>::push(const T& e){

    //initialize a new node
    Node<T>* newNode = new Node<T>();
    newNode->data = e;
    newNode->next = head;
    head = newNode;
    length++;

}


#endif