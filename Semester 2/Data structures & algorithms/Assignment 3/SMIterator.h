#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap& mapionar);
	int currentElement;
	//TODO - Representation

public:
	void first();
	void last();
	void previous();
	void next();
	bool valid() const;
    TElem getCurrent() const;
};

