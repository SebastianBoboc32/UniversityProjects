#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	first();
}

void BagIterator::first() {
	current = 0;
}


void BagIterator::next() {
	if (!valid())
		throw exception();
	current++;
}


bool BagIterator::valid() const {
	return current < bag.capacity;
}



TElem BagIterator::getCurrent() const
{
	if (!valid())
		throw exception();
	return bag.hashtable[current]->value;
}
