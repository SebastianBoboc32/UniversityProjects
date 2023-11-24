#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
	next = new int[CAP];
	elems = new TComp[CAP];
	rel = r;
	sz = 0;
	cap = CAP;
	for (int i = 0; i < CAP - 1; ++i) {
		next[i] = i + 1;
		elems[i] = 0;
	}
	next[CAP - 1] = -1;
	elems[CAP - 1] = 0;
}

int SortedIndexedList::size() const {
	return sz;
}

bool SortedIndexedList::isEmpty() const {
	return sz == 0;
}

TComp SortedIndexedList::getElement(int i) const{
	if (i >= sz || i < 0 || sz == 0)
		throw exception();
	int index = 0;
	while (index != i && index != -1)
		index = next[index];
	return elems[index];
}

TComp SortedIndexedList::remove(int i) {
	if (sz == 0 || i < 0 || i >= sz)
		throw exception();
		int deleted = elems[i];
		for (int j = i; j < sz - 1; ++j) {
			elems[j] = elems[j + 1];
			if (next[j] > next[i])
				next[j]--;
			if (next[j] == i)
				next[j] = next[i];
		}
		sz--;
		return deleted;
}

int SortedIndexedList::search(TComp e) const {
	if (sz == 0)
		return -1;
	int index = 0;
	while (elems[index] != e && index != -1)
		index = next[index];
	return index;
}

void SortedIndexedList::add(TComp e) {

	if (sz == cap-1)
		resize();
	if (sz == 0) {
		elems[sz] = e;
		next[sz] = -1;
	}
	else {
		elems[sz] = e;
		int index = 0;
		int prev = index;
		while (index != -1 && rel(elems[index], e)) {
			index = next[index];
			prev = index;
		}
		next[prev] = sz;
		next[sz] = index;
	}
	sz++;
}

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
	delete[] elems;
	delete[] next;
}

void SortedIndexedList::resize() {
	cap *= 2;
	int *temp_next = new int[cap];
	TComp* temp_elems = new TComp[cap];
	for (int i = 0; i < cap; ++i) {
		if (i < sz) {
			temp_next[i] = next[i];
			temp_elems[i] = elems[i];
		}
		else {
			temp_next[i] = i + 1;
			temp_elems[i] = 0;
		}
	}
	delete[] next;
	delete[] elems;
	next = temp_next;
	elems = temp_elems;
}

int SortedIndexedList::get_first_elem_index() const {
	if (sz == 1)
		return 0;
	int index = 0;
	TComp min_TElem = 0;
	while (index != -1) {
		index = next[index];
		min_TElem = max(min_TElem,elems[index]);
	}
	for(int i = 0;i<sz;++i)
		if (rel(elems[i], min_TElem)) {
			index = i;
			min_TElem = elems[i];
		}
	return index;
}
