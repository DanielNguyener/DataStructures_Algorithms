#ifndef DEQUE_H
#define DEQUE_H

#include "node.h"
using namespace std;

template <class Type>
class Deque {
private:
	int s;
	Node<Type>* firstNode;
	Node<Type>* lastNode;

public:
	Deque();
	Deque(const Deque& other); 
	Deque& operator=(const Deque& other); 
	~Deque();
	bool isEmpty() const;
	int size();
	Type first();
	Type last();
	void insertFirst(Type o);
	void insertLast(Type o);
	Type removeFirst();
	Type removeLast();
};

// Your implementation here 
// Deque whose size can
// grow as elements are inserted into the deque. Specifically, you will
// implement a deque using a doubly linked list.

template <class Type>
Deque<Type>::Deque() { // constructor
	//inititate header
	firstNode = nullptr;
	//initiate tail
	lastNode = nullptr;
	//initiate size
	s = 0;
}

template <class Type>
Deque<Type>::~Deque() { // deconstructor
	Node<Type>* current = firstNode;
	Node<Type>* next;

	if(!isEmpty()){
		while(current != nullptr){
			next = current->getNext();
			delete current;
			current = next;
		}
	}

	firstNode = nullptr;
	lastNode = nullptr;
	s = 0;

}

template <class Type>
Deque<Type>::Deque(const Deque& other) { //copy constructor

	firstNode = nullptr;
	lastNode = nullptr;
	s = 0;

	// make sure this isn't self-assignemnt
	if(this != &other){

		//we want to preserve the order, so we're going to iterate 

		//ensure the other queue isn't empty
		if(!other.isEmpty()){

			// current Node to iterate with
			Node<Type>* current = other.firstNode; // start at head

			while(current != nullptr){ // iterate through into reach tail (which points to nullptr)

				insertLast(current->getData());
				current = current->getNext();

			}
		}


	}


}

template <class Type>
Deque<Type>& Deque<Type>::operator=(const Deque& other) { //copy assignment

	if(this != &other){
		while(!isEmpty()){
			//clear current queue
			removeLast();
		}
	}

	firstNode = nullptr;
	lastNode = nullptr;
	s = 0;

	if(!other.isEmpty()){
		// current Node to iterate with
		Node<Type>* current = other.firstNode; // start at head

		while(current != nullptr){ // iterate through into reach tail (which points to nullptr)

			insertLast(current->getData());
			current = current->getNext();

		}	
	}

	return *this;


}

template <class Type>
bool Deque<Type>::isEmpty() const{ // empty boolean
	
	if(s > 0){
		return false;
	}else{
		return true;
	}
}

template <class Type>
int Deque<Type>::size() {
	return s;
}

template <class Type>
Type Deque<Type>::first() {

	if(!isEmpty()){
		return firstNode->getData();
	}else{
		return Type();
	}
}

template <class Type>
Type Deque<Type>::last() {
	
	if(!isEmpty()){
		return lastNode->getData();
	}else{
		return Type();
	}
}

template <class Type>
void Deque<Type>::insertFirst(Type o) {

	//initialize new node, data, and point next to firstNode.
	Node<Type>* newNode = new Node<Type>(o, firstNode, nullptr);

	if(!isEmpty()){

		//point header Node previous to newNode
		firstNode->setPrev(newNode);

	}else{
		//list is empty, so lastNode will be the same as firstNode
		lastNode = newNode;
	}

	firstNode = newNode;
	s++;

}

template <class Type>
void Deque<Type>::insertLast(Type o) {
	
	//initialize new node, and data
	Node<Type>* newNode = new Node<Type>(o, nullptr, lastNode);

	if(!isEmpty()){
		
		//point tail to new Node
		lastNode->setNext(newNode);
		
	}else{
		firstNode = newNode;
	}
	
	// tail is now newNode.
	lastNode = newNode;
	s++;
	
}

template <class Type>
Type Deque<Type>::removeFirst() { //remove first node, and return the elment

	if(!isEmpty()){
		
		//store popped data
		Type poppedElem = firstNode->getData();

		Node<Type>* old_head = firstNode;

		firstNode = old_head->getNext();

		delete old_head;

		s--;

		return poppedElem;

	}
	else{
		return Type();
	}

}

template <class Type>
Type Deque<Type>::removeLast() {

	if(!isEmpty()){

		Type poppedElem = lastNode->getData();

		Node<Type>* old_tail = lastNode;

		lastNode = lastNode->getPrev();

		delete old_tail;

		s--;

		return poppedElem;

	}
	else{
		return Type();
	}
	
}

#endif
