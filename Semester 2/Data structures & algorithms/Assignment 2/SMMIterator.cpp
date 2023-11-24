#include "SMMIterator.h"
#include "SortedMultiMap.h"

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	 this->current = nullptr;
}

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
void SMMIterator::first(){
	this->current = map.tail->next;
}

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
void SMMIterator::next(){
	if (map.isEmpty())
		throw exception();
	if (this->current == nullptr)
	{
		this->first();
		return;
	}
	if (this->current == map.head)
		throw exception();
	this->current = this->current->next;
}

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
bool SMMIterator::valid() const{
	return (map.size() && this->current != map.tail && this->current != map.head);
}

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
TElem SMMIterator::getCurrent() {
	if (map.isEmpty())
		throw exception();
	if (this->current == nullptr)
	{
		this->first();
		return this->current->telem;
	}
	if (map.isEmpty() || this->current == map.head)
		throw exception();
	return this->current->telem;
}
// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
SMMIterator& SMMIterator::operator=(const SMMIterator& other)
{
	this->current = other.current;
	return *this;
}


