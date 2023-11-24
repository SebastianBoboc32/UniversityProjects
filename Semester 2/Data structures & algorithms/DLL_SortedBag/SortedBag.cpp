#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
	rel = r;
	sz = 0;
	//cap = CAP;
	elems = new DLL;
	elems->head = nullptr;
	elems->tail = nullptr;
}

void SortedBag::add(TComp e) {
	if (sz == 0) {
		DLLNode* elem = new DLLNode;
		elem->value = std::make_pair(e, 1);
		elem->prev = elems->tail;
		elem->next = elems->head;
		if (elems->head == nullptr) {
			elems->head = elem;
			elems->tail = elem;
		}
		//else {
			//elems->head->prev = elem;
		//}
	}
	else if (search(e)) {
		DLLNode* node = elems->tail;
		while (node->value.first != e)
			node = node->next;
		node->value.second++;
	}
	else {
		DLLNode* node = elems->tail;
		DLLNode* prevv = new DLLNode;//the previous of node
		DLLNode* new_node = new DLLNode;
		new_node->value = std::make_pair(e, 1);
		if (!rel(node->value.first, e)) {
			new_node->next = node;
			new_node->prev = node->prev;
			elems->tail = new_node;
			if (node->prev != nullptr)
				node->prev->next = new_node;
			node->prev = new_node;
		}
		else {
			while (node != nullptr && rel(node->value.first, e)) {
				prevv = node;
				node = node->next;
			}

			if (node != nullptr) {
				new_node->prev = node->prev;
				new_node->next = node;
				if (node->prev != nullptr) {
					prevv->next = new_node;
					node->prev = new_node;
				}
			}
			else {
				new_node->prev = prevv;
				prevv->next = new_node;
				new_node->next = nullptr;
			}
		}
	}
	sz++;
}


bool SortedBag::remove(TComp e) {
	if(!search(e))
		return false;
	else {
		DLLNode* node = elems->tail;
		//node = elems->tail;
		while (node->value.first != e)
			node = node->next;
		if (node != nullptr) {
			if (node->value.second != 1)
				node->value.second--;
			else {
				if (node->prev != nullptr)
					node->prev->next = node->next;
				if (node->next != nullptr)
					node->next->prev = node->prev;
				delete node;
			}
		}
		sz--;
		return true;
	}
}


bool SortedBag::search(TComp elem) const {
	DLLNode* node = elems->tail;
	while (node != nullptr) {
		if (node->value.first == elem)
			return true;
		node = node->next;
	}

	return false;
}


int SortedBag::nrOccurrences(TComp elem) const {
	DLLNode* node = elems->tail;
	while (node != nullptr && node->value.first != elem)
		node = node->next;
	if(node == nullptr)
	return 0;
	return node->value.second;
}



int SortedBag::size() const {
	return sz;
}


bool SortedBag::isEmpty() const {
	return sz == 0;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() = default; 
	/*
	DLLNode* node = elems->tail;
	//node = elems->tail;
	while (node->next != nullptr) {
		DLLNode* temp = node;
		delete node;
		node = temp->next;
	}
	delete elems->head;
	delete elems;
	*/

