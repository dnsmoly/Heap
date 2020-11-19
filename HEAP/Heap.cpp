#include <iostream>
#include <windows.h>
#include <string.h>
#include "Heap.h"
#include"HeapNode.h"
#include <vector>
using namespace std;

template <typename T>
HeapNode<T>::HeapNode(const T& data) {
	this->data = data;
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
}

template <typename T>
Heap<T>::Heap(int capacity) {
	this->capacity = capacity;
	this->size = 0;
	this->root = nullptr;
	this->last = nullptr;
}

template <typename T>
Heap<T>::~Heap() {
	deconstruct(root);
}

template <typename T>
void Heap<T>::deconstruct(HeapNode<T>* root) {
	if (!root) return;
	deconstruct(root->left);
	deconstruct(root->right);
	delete root;
}

template <typename T>
void Heap<T>::addKey(const T& key) {
	if (this->size + 1 > this->capacity) { // if out of capacity
		throw invalid_argument("Out of capacity");
	}
	else if (this->root == nullptr) { // if no elements
		this->root = new HeapNode<T>(key);
		this->last = this->root;
	}
	else if (this->root == this->last) { // if one element
		this->root->left = new HeapNode<T>(key);
		this->root->left->parent = this->root;
		this->last = this->root->left;
		fixUp();
	}
	else if (this->last->parent->left == this->last) { // if last is left
		HeapNode<T>* tmp = new HeapNode<T>(key);
		tmp->parent = this->last->parent;
		this->last->parent->right = tmp;
		this->last = tmp;
		fixUp();
	}
	else if (this->last->parent->right == this->last) { // if last is right
		HeapNode<T>* tmp = this->last->parent;
		while (tmp->parent) {
			if (tmp->parent->right == tmp) {
				tmp = tmp->parent;
			}
			else {
				break;
			}
			
		}
		if(tmp->parent) tmp = tmp->parent->right;
		while (tmp->left) {
			tmp = tmp->left;
		}
		tmp->left = new HeapNode<T>(key);
		tmp->left->parent = tmp;
		this->last = tmp->left;
		fixUp();
	}
	this->size++;
}

template <typename T>
void Heap<T>::fixUp() {
	if (this->last->data > this->last->parent->data) {
		HeapNode<T>* tmp = this->last;
		while (tmp->data > tmp->parent->data) {
			swap(tmp, tmp->parent);
			tmp = tmp->parent;
			if (tmp == this->root) break;
		}
	}
}

template <typename T>
void Heap<T>::swap(HeapNode<T>* first, HeapNode<T>* second) {
	T a = first->data;
	first->data = second->data;
	second->data = a;
}

template <typename T>
bool Heap<T>::find(const T& key) {
	int result = search(this->root, key);
	if (result > 0) return true;
	else return false;
}

template <typename T>
int Heap<T>::search(HeapNode<T>* root, const T& key) {
	if (!root) return 0;
	if (root->data == key) return 1;
	return Heap<T>::search(root->left, key) + Heap<T>::search(root->right, key);
}

template <typename T>
void Heap<T>::print() {
	if (size > 0)
	{
		rPrint(root, 0);
	}
	else {
		throw bad_weak_ptr();
	}
}

template <typename T>
void Heap<T>::rPrint(HeapNode<T>* root, int lvl)
{
	if (root)
	{
		rPrint(root->right, lvl + 5);
		for (int i = 0; i < lvl; i++)
			cout << ' ';
		cout << "   " << root->data << endl;
		rPrint(root->left, lvl + 5);
	}
	
	
}

template <typename T>
T Heap<T>::getMax() {
	if(root) return this->root->data;
	else throw bad_weak_ptr();
}

template <typename T>
void Heap<T>::remove(const T& key) {
	if (!find(key)) {
		throw invalid_argument("No such element");
	}
	else if (this->root == this->last) {
		delete this->root;
		root = nullptr;
		last = nullptr;
		size--;
	}
	else {
		del(this->root, key);
	}
}

template <typename T>
void Heap<T>::del(HeapNode<T>* root, const T& key) {
	if (!root) return;
	if (root->data == key) {
		swap(root, this->last);
		HeapNode<T>* tmp = penult();
		if (last->parent || last->left || last->right) {
			if (last == last->parent->left) last->parent->left = nullptr;
			else last->parent->right = nullptr;
			if (root != last) {
				delete last;
				last = tmp;
				fixDown(root);
				this->size--;
				del(root, key);
			}
			else {
				delete root;
				root = nullptr;
				last = tmp;
				this->size--;
			}
		}
		else {
			delete root;
			this->root = nullptr;
			root = nullptr;
			last = nullptr;
			this->size--;
		}
	}
	if (root && size > 0) {
		del(root->left, key);
		del(root->right, key);
	}
	
	
}

template <typename T>
HeapNode<T>* Heap<T>::penult() { // return penultimate
	if (this->root == nullptr) { // if no elements
		throw bad_weak_ptr();
	}
	else if (this->last == this->root) return this->root;
	else if (this->last->parent->right == this->last) { // if last is left
		return this->last->parent->left;
	}
	else if (this->last->parent->left == this->last) { // if last is right
		HeapNode<T>* tmp = this->last->parent;
		while (tmp->parent) {
			if (tmp->parent->left == tmp) {
				tmp = tmp->parent;
			}
			else {
				break;
			}

		}
		if (tmp->parent) tmp = tmp->parent->left;
		while (tmp->right) {
			tmp = tmp->right;
		}
		return tmp;
	}
}

template <typename T>
void Heap<T>::fixDown(HeapNode<T>* node) {
	
	while (node->left && node->right) {
		if (node->data < node->left->data || node->data < node->right->data) {
			if (node->left->data < node->right->data) {
				swap(node, node->right);
				node = node->right;
			}
			else {
				swap(node, node->left);
				node = node->left;
			}
		}
		else {
			break;
		}
	}
	if (node->left && node->left->data > node->data) {
		swap(node, node->left);
	}
	
}

template <typename T>
int Heap<T>::getSize() {
	return size;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char action = '1';
	/*Heap<int> heap = Heap<int>(14);
	heap.addKey(123);
	heap.addKey(42);
	heap.addKey(1);
	heap.addKey(43);
	heap.addKey(2);
	heap.addKey(43);
	heap.addKey(43);
	heap.print();
	heap.remove(43);
	heap.print();*/
	
	while (action != '7') {
		cout << "Sorting tree programm" << endl;
		cout << "Введите размер" << endl;
		int size;
		cin >> size;
		Heap<int> heap = Heap<int>(size);
		vector<int> v(size);
		cout << "Commands:\n1. Добавить элемент\n2. Найти элемент\n3. удалить элемент (и все его копии)\n4. Визуализировать дерево" << endl;
		cout << "5. Получить размер дерева\n6. Получить максимальный элемент\n7. Остановить программу\n8. Создать новое дерево" << endl;
		int num;
		do {
			cout << "Выберите команду" << endl;
			cin >> action;
			switch (action) {
			case '1':
				cout << "Введите число" << endl;
				cin >> num;
				try {
					heap.addKey(num);
				}
				catch (invalid_argument a) {
					cout << a.what() << endl;
				}
				break;
			case '2':
				cout << "Введите число" << endl;
				cin >> num;
				if (heap.find(num)) {
					cout << "Есть" << endl;
				}
				else {
					cout << "Нет" << endl;
				}
				break;
			case '3':
				cout << "Введите число" << endl;
				cin >> num;
				try {
					heap.remove(num);
				}
				catch (invalid_argument a) {
					cout << a.what() << endl;
				}
				break;
			case '4':
				try {
					cout << "______________" << endl << endl;
					heap.print();
					cout << "______________" << endl;
				}
				catch (bad_weak_ptr a) {
					cout << a.what() << endl;
				}
				cout << endl;
				break;
			case '5':
				cout << heap.getSize() << endl;
				break;
			case '6':
				try {
					cout << heap.getMax() << endl;
				}
				catch (bad_weak_ptr a) {
					cout << a.what() << endl;
				}
				break;
			case '7':
				break;
			case '8':
				break;
			}
		} while (action != '7' && action != '8');
	}
	
	
}