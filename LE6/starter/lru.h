//Least Recently Used Cache Implementation
// The size of the Cache is limited to maxSize. If the cache is full and we want to insert a new item, we remove the least recently used item from the cache.
// Implement with O(1) time complexity the following functions:
    // 1. insertKeyValue(string key, int value) - insert a key value pair into the cache. If the key already exists, update the value of the key.
    // 2. getValue(string key) - return the value of the key if it exists, otherwise return NULL.
    // 3. mostRecentKey() - return the key of the most recently used value.

#ifndef LRU_H
#define LRU_H

#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

//Node to store the data (Linked List)
class Node {
public:
	string key;
	int value;
	Node (string key,int value) {
		this->key = key;
		this->value = value;
	}
};


//LRU Cache Data Structure
class LRUCache{
private: 
	int maxSize;
	list<Node> l;
	unordered_map<string,list<Node>::iterator > m;

public:
	LRUCache(int maxSize);
	void insertKeyValue(string key,int value);
	int* getValue(string key);
	string mostRecentKey();

};

LRUCache::LRUCache(int maxSize){
	this->maxSize = maxSize > 1 ? maxSize : 1;
}

void LRUCache::insertKeyValue(string key,int value){

	//the key exists -> replace
	if(m.find(key) != m.end()){
		//update the value
		m[key]->value = value;

		//it is now the most RU.
		//shift all keys
		
		//store the iterator corresponding to key, points to Node
		list<Node>::iterator nodeIt = m[key];
		//copy the Node at the position indicated by NodeIt
		Node moveNode = *nodeIt;

		//delete the Node at key from node list
		l.erase(nodeIt);

		//put the copied node at the end.
		l.push_back(moveNode);

		//update the map, the key is now the last node.
		m[key] = prev(l.end());
		return;
	}

	//the key doesn't exist
	else{
		//the cache is full
		if(l.size() >= maxSize){
			//remove the LEAST (front) used key from map
			m.erase(l.front().key);
			//remove the corresponding node from list
			l.pop_front();
		}
		//proceed

		//insert new node at end
		l.push_back(Node(key,value));
		//update the iterator with the key, with the last node.
		m[key] = prev(l.end());
	
	}

}

int* LRUCache::getValue(string key){
    // Your implementation here

	//doesn't exist
	if(m.find(key) == m.end()){
		return nullptr;
	}else{
		//key exists, so store a pointer to the Node
		list<Node>::iterator it = m[key]; 
		//dereference the node pointer's value
		int* nodeValue = &it->value;
		
		//upate most recently used key.
		//this algorithm is defined and used in insertion.
		list<Node>::iterator nodeIt = m[key];
		Node moveNode = *nodeIt;
		l.erase(nodeIt);
		l.push_back(moveNode);
		m[key] = prev(l.end());

		//return dereferenced value.
		return nodeValue;
	}

}

string LRUCache::mostRecentKey(){
	//empty
	if(m.empty()){
		return "";
	}else{
		//not empty, store last Node
		list<Node>::iterator lastNode = prev(l.end());
		//store last node's key
		string recentKey = lastNode->key;

		//return key
		return recentKey;
	}
}

#endif