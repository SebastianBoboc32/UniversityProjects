#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	first();
	current_index = 1;
}

TComp SortedBagIterator::getCurrent() {
	if (!valid())
		throw exception();
	return current->value.first;
}

bool SortedBagIterator::valid() {
	return current != nullptr;
}

void SortedBagIterator::next() {
	if (!valid())
		throw exception();
	if (current_index == current->value.second) {
		current_index = 1;
		current = current->next;
	}
	else current_index++;
}

void SortedBagIterator::first() {
	current = bag.elems->tail;
}

