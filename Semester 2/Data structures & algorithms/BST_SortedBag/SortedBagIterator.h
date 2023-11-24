#pragma once
#include "SortedBag.h"

class SortedBag;


class Queue {
private:
	int *elements;
	int capacity;
	int size;
public:
	Queue();
	Queue(const int&);
	int top();
	void pop();
	void push(const int&);
	void resize();
	void parse_tree(const SortedBag&,Node*);
	int sz();
	int operator[](int index);
};

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);
	Queue queue;
	//TODO - Representation

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

