#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	DLLNode* current;
	int current_index;

public:
	SortedBagIterator(const SortedBag& b);
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

