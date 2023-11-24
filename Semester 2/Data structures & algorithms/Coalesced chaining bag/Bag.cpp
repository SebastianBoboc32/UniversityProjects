#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	capacity = 100;
	percentage = 0;
	sz = 0;
	hashtable = new Node*[capacity];
	for (int i = 0; i < capacity; ++i) {
		hashtable[i] = new Node;
		hashtable[i]->key = i;
		hashtable[i]->value = NULL_TELEM;
		hashtable[i]->next = -1;
	}
}


void Bag::add(TElem elem) {
	percentage = static_cast<float>(sz) / capacity;
	if (percentage > alpha) {
		resize();
	}
	int index = elem % capacity;
	if (hashtable[index] == nullptr) {
		Node* X = new Node;
		X->key = index;
		X->value = elem;
		X->next = -1;
		hashtable[index] = X;
		sz++;
	}
	else if (hashtable[index]->value == -111111) {
		hashtable[index]->value = elem;
		sz++;
	}
	else {
		int frst_free = first_free();
		Node* X = new Node;
		X->key = frst_free;
		X->value = elem;
		X->next = -1;
		int position = hashtable[index]->next;
		if (position == -1) {
			hashtable[index]->next = frst_free;
		}
		else {
			while (hashtable[position]->next != -1) {
				position = hashtable[position]->next;
			}
			hashtable[position]->next = frst_free;
		}
		hashtable[frst_free] = X;
		sz++;
	}
}


bool Bag::remove(TElem elem) {
	if (!search(elem))
		return false;
	int index = 0;
	while (hashtable[index]->value != elem)
		index++;
	bool is_pointed = false;
	int pointer_index = -1;
	bool points_to = hashtable[index]->next != -1;
	for (int i = 0; i < capacity && !is_pointed; ++i)
		if (hashtable[i]->next == index) {
			is_pointed = true;
			pointer_index = i;
		}
	if (!is_pointed && !points_to) {
		hashtable[index]->next = -1;
		hashtable[index]->value = NULL_TELEM;
	}
	else if (is_pointed && points_to) {
		hashtable[pointer_index]->next = hashtable[index]->next;
		hashtable[index]->next = -1;
		hashtable[index]->value = NULL_TELEM;
	}
	else if (is_pointed) {
		hashtable[pointer_index]->next = -1;
		hashtable[index]->value = NULL_TELEM;
	}
	else if (points_to) {
		int position = index;
		while (hashtable[position]->next != -1) {
			hashtable[position]->value = hashtable[hashtable[position]->next]->value;
			position = hashtable[position]->next;
		}
		hashtable[position]->next = -1;
		hashtable[position]->value = NULL_TELEM;
	}
	return true;
}


bool Bag::search(TElem elem) const {
	for (int i = 0; i < capacity; ++i)
		if (hashtable[i]->value == elem)
			return true;
	return false;
}

int Bag::nrOccurrences(TElem elem) const {
	int nroc=0;
	for (int i = 0; i < capacity; ++i)
		if (hashtable[i]->value == elem)
			nroc++;
	return nroc; 
}


int Bag::size() const {
	return sz;
}


bool Bag::isEmpty() const {
	return sz == 0;
}

void Bag::resize()
{
	capacity *= 2;
	Node** temp = new Node * [capacity];
	for (int j = 0; j < capacity; ++j) {
		temp[j] = new Node;
		temp[j]->key = j;
		temp[j]->next = -1;
		temp[j]->value = NULL_TELEM;
	}
	for (int i = 0; i < capacity; ++i) {
		int index = i % (capacity / 2);
		if (hashtable[index] != nullptr && hashtable[index]->value != NULL_TELEM) {
			int elem = hashtable[index]->value;
			int newIndex = elem % capacity;
			if (temp[newIndex]->value == NULL_TELEM) {
				Node* X = new Node;
				X->key = newIndex;
				X->value = elem;
				X->next = -1;
				temp[newIndex] = X;
			}
			else {
				int frst_free = capacity - 1;
				while (temp[frst_free]->value != NULL_TELEM)
					frst_free--;
				Node* X = new Node;
				X->key = frst_free;
				X->value = elem;
				X->next = -1;
				if (temp[newIndex]->next == -1)
					temp[newIndex]->next = X->key;
				else {
					int position = temp[newIndex]->next;
					while (temp[position]->next != -1)
						position = temp[position]->next;
					temp[position]->next = X->key;
				}
				temp[frst_free] = X;
			}
		}
	}
	for (int i = 0; i < capacity / 2; ++i) {
		delete hashtable[i];
	}
	delete[] hashtable;

	hashtable = temp;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


int Bag::first_free()
{
	int result = capacity-1;
	bool found = false;
	while (result != -1 && !found) {
		if (hashtable[result]->value == -111111) {
			found = true;
		}
		else {
			result--;
		}
	}
	return result;
}

Bag::~Bag() {
	for (int i = 0; i < capacity; ++i)
		delete hashtable[i];
	delete[]hashtable;
}

