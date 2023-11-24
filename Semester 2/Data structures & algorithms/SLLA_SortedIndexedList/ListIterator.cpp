#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	first();
}

void ListIterator::first(){
	current = list.get_first_elem_index();
}

void ListIterator::next(){
	if (!valid())
		throw exception();
	current = list.next[current];
}

bool ListIterator::valid() const{
	return current != -1;
	//return false;
}

TComp ListIterator::getCurrent() const{
	if (!valid())
		throw exception();
	return list.elems[current];
}


