#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	node* current;
	SMMIterator(const SortedMultiMap& map);

	//TODO - Representation

public:
	SMMIterator& operator=(const SMMIterator& other);
	void first();
	void next();
	bool valid() const;
	TElem getCurrent();
};

