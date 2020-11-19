#pragma once
template <typename T>
class HeapNode {

public:
	//Constructor
	HeapNode(const T& data);

	T data;

	HeapNode* left;
	HeapNode* right;
	HeapNode* parent;
};