#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

/*
Best case: 0(1) ->

Worst case:0(1) ->

Total: 0(1)
*/
BagIterator::BagIterator(const Bag& c) : bag(c)
{
    this->currentPosition = 0;
    this->currentFrequency = 0;
}

/*
Best case: 0(1) ->

Worst case:0(1) ->

Total: 0(1)
*/
void BagIterator::first() {
    this->currentPosition = 0;
    this->currentFrequency = 0;
}

/*
Best case: 0(1) ->

Worst case:0(1) ->

Total: 0(1)
*/
void BagIterator::next() {
    if (this->valid()) {
        if (this->currentFrequency < this->bag.nrOccurrences(this->bag.elements[this->currentPosition].first) - 1) {
            this->currentFrequency++;
        }
        else {
            this->currentPosition++;
            this->currentFrequency = 0;
        }
    }
    else {
        throw std::exception();
    }
}

/*
Best case: 0(1) ->

Worst case:0(1) ->

Total: 0(1)
*/
bool BagIterator::valid() const {
    return this->currentPosition < this->bag.nr_of_elems;
}

/*
Best case: 0(1) ->

Worst case:0(1) ->

Total: 0(1)
*/
TElem BagIterator::getCurrent() const
{
    if (this->valid()) {
        return this->bag.elements[this->currentPosition].first;
    }
    else {
        throw std::exception();
    }
}