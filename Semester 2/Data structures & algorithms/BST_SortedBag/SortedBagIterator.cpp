#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b),queue(100){
	first();
}

TComp SortedBagIterator::getCurrent() {
	if (!valid())
		throw exception();
	return queue.top();
}

bool SortedBagIterator::valid() {
	
	return queue.sz() != 0;
}

void SortedBagIterator::next() {
	if (!valid())
		throw exception();
	queue.pop();
}

void SortedBagIterator::first() {
	queue.parse_tree(bag, bag.binary_search_tree->root);
}

Queue::Queue()
{
	size = 0;
	capacity = 100;
	elements = new int[capacity];
}

Queue::Queue(const int&sz)
{
	size = 0;
	capacity = sz;
	elements = new int[capacity];

}

int Queue::top()
{
	return elements[0];
}

void Queue::pop()
{
	size--;
	for (int i = 0; i < size; ++i)
		elements[i] = elements[i + 1];
}

void Queue::push(const int& X)
{
	elements[size++] = X;
}

void Queue::resize()
{
	int* temp = new int[2 * capacity];
	for (int i = 0; i < size; ++i)
		temp[i] = elements[i];
	capacity *= 2;
	delete[]elements;
	elements = temp;
}

void Queue::parse_tree(const SortedBag&b, Node*root)
{
	if (root != nullptr) {
		parse_tree(b, root->left);
		push(root->data);
		parse_tree(b, root->right);
	}
}

int Queue::sz()
{
	return size;
}

int Queue::operator[](int index)
{
	if (index <0 || index > size)
		throw exception();
	return elements[index];
}
