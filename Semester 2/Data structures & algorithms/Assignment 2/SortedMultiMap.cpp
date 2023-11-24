#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
SortedMultiMap::SortedMultiMap(Relation r) {
	this->relation = r;
	this->head = new node;
	this->tail = new node;
	this->len = 0;
}
// Best Case: Theta(1), Worst Case: Theta(n), Average Case: Theta(n)
void SortedMultiMap::add(TKey c, TValue v) {
	if (this->relation(this->head->telem.first,c)){
		node* newNode = new node;
		newNode->telem = TElem(c, v);
		if (this->head->prev == nullptr)
		{
			this->head->prev = newNode;
			newNode->next = this->head;
			newNode->prev = this->tail;
			this->tail->next = newNode;
		}
		else
		{
			node* current = this->head->prev;
			while (current != this->tail && this->relation(c, current->telem.first))
				current = current->prev;
			current->next->prev = newNode;
			newNode->next = current->next;
			current->next = newNode;
			newNode->prev = current;
		}
	}
	else {
		node* newNode = new node;
		newNode->telem = TElem(c, v);
		if (this->tail->next == nullptr)
		{
			this->tail->next = newNode;
			newNode->prev = this->tail;
			newNode->next = this->head;
			this->head->prev = newNode;
		}
		else
		{
			node* current = this->tail->next, * previous = this->tail;
			while (current != nullptr && this->relation(current->telem.first, c))
			{
				previous = current;
				current = current->next;
			}
			if (current == nullptr)
			{
				current = previous;
				current->next = newNode;
				newNode->prev = current;
				this->head->prev = newNode;
			}
			else
			{
				newNode->next = current;
				newNode->prev = current->prev;
				current->prev->next = newNode;
				current->prev = newNode;
			}
		}	
	}
	this->len++;
}
// Best Case: Theta(1), Worst Case: Theta(n), Average Case: Theta(n)
vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> values;
	node* current = this->tail->next;
	while (current != nullptr && this->relation(current->telem.first, c))
	{
		if (current->telem.first == c)
			values.push_back(current->telem.second);
		current = current->next;
	}
	return values;
}

// Best Case: Theta(1), Worst Case: Theta(n), Average Case: Theta(n)
bool SortedMultiMap::remove(TKey c, TValue v) {
	node* current = this->tail->next;
	while (current != this->head && this->relation(current->telem.first, c))
	{
		if (current->telem.first == c && current->telem.second == v)
		{
			node* previous = current->prev, * next = current->next;
			previous->next = next;
			next->prev = previous;
			--this->len;
			return true;
		}
		current = current->next;
	}
	return false;
}

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
int SortedMultiMap::size() const {
	return this->len;
	
}
// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
bool SortedMultiMap::isEmpty() const {
	return this->len == 0;
}
// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}
// Best Case: Theta(1), Worst Case: Theta(n), Average Case: Theta(n)

SortedMultiMap::~SortedMultiMap() {
	node* current = this->tail->next;
	while (current != nullptr)
	{
		node* next = current->next;
		delete current;
		current = next;
	}
	if (this->tail != nullptr)
		delete this->tail;
}

//Best Case: Theta(n), Worst Case: Theta(n^2), Average Case: Theta(n^2)
vector<TKey> SortedMultiMap::keySet()const {
	vector<TKey>values;
	node* current = this->tail->next;
	while (current != this->head) {
		TKey temp = current->telem.first;
		auto it = find_if(values.begin(), values.end(), [&](TKey X) {return X == temp; });
		if (it == values.end())
			values.push_back(temp);
		current = current->next;
	}
	return values;
}
