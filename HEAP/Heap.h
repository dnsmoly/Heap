#pragma once
#include "HeapNode.h"
#include <string.h>
#include <iostream>
template <typename T>
class Heap {
	
	int capacity; // max number of elements

public:
	//Constructor
	Heap(int capacity = 10);
	//Destructor
	~Heap();

	int size; // current size of heap

	void addKey(const T& key);
	bool find(const T& key);
	void remove(const T& key);
	void print();
	int getSize();
	T getMax();


private:

	HeapNode<T>* root;
	HeapNode<T>* last;

	HeapNode<T>* penult();
	void deconstruct(HeapNode<T>* root);
	void del(HeapNode<T>* root, const T& key);
	void rPrint(HeapNode<T>* root, int lvl);
	int search(HeapNode<T>* root, const T& key);
	void swap(HeapNode<T>* first, HeapNode<T>* second);
	void fixUp();
	void fixDown(HeapNode<T>* node);

};
