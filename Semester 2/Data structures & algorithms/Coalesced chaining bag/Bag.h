#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111
#define inf 0x3f3f
typedef int TElem;
class BagIterator;

const float alpha = 0.75;

struct Node {
	int next;
	int key;
	TElem value;
};

class Bag {

private:
	//TODO - Representation
	Node** hashtable;
	int capacity;
	int sz;
	//int first_free;
	//float percentage;

	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:

	float percentage;
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	void resize();

	int first_free();

	//destructor
	~Bag();
};