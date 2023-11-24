#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <stdexcept>
using namespace std;

// Best,Average and total:Theta(1)
SMIterator::SMIterator(const SortedMap& m) : map(m) {
	this->first();
}

// Best,Average and total:Theta(1)
void SMIterator::first(){
	this->currentElement = this->map.head;
}

// Best,Average and total:Theta(1)
void SMIterator::next(){
	if (!this->valid())
		throw exception();
	this->currentElement = this->map.DLLANodes[this->currentElement].next;
}

// Best,Average and total:Theta(1)
bool SMIterator::valid() const{
	if (this->currentElement == -1)
		return false;
	return true;
}

// Best,Average and total:Theta(1)
void SMIterator::last() {
	this->currentElement = this->map.tail;
}

// Best,Average and total:Theta(1)
void SMIterator::previous() {
	if (!this->valid())
		throw exception();
	this->currentElement = this->map.DLLANodes[this->currentElement].prev;
}

// Best,Average and total:Theta(1)
TElem SMIterator::getCurrent() const{
	if (!this->valid())
		throw exception();
	return this->map.DLLANodes[this->currentElement].info;
}


