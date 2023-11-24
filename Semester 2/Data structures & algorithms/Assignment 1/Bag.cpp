#include "Bag.h"
#include "BagIterator.h"


Bag::Bag() {
    capacity = 100;
    elements = new std::pair<TElem, int>[capacity];
    nr_of_elems = 0;
}

/*
Best case: 0(1) -> When the number of unique elements of the bag is not equal to the capacity,
                   the added element is already in the bag and it's the first element from the bag

Worst case:0(n) -> When the number of unique elements of the bag is equal to the capacity,
                   so a resize is needed,and the added element is on the last position.
                   The program goes from (0->n) 2 times,hence the complexity is still 0(n)

Total: 0(n)

*/
void Bag::add(TElem e) {
    if (nr_of_elems == capacity) {
        std::pair<TElem, int>* new_elements = new std::pair<TElem, int>[2 * capacity];
        for (int i = 0; i < nr_of_elems; i++) {
            new_elements[i] = elements[i];
        }
        capacity = 2 * capacity;
        delete[] elements;
        elements = new_elements;
    }
    for (int i = 0; i < nr_of_elems; i++) {
        if (elements[i].first == e) {
            elements[i].second++;
            return;
        }
    }
    elements[nr_of_elems] = std::make_pair(e, 1);
    nr_of_elems++;
}

/*
Best case: 0(1) -> When the deleted element is the first in the bag and it's not unique

Worst case:0(n^2) -> When the deleted element is unique,because in that case the program
                     goes from (i->n) while going from (0->n).

Total: 0(n^2)
*/

bool Bag::remove(TElem e) {
    for (int i = 0; i < nr_of_elems; i++) {
        if (elements[i].first == e) {
            elements[i].second--;
            if (elements[i].second == 0) {
                for (int j = i; j < nr_of_elems - 1; j++) {
                    elements[j] = elements[j + 1];
                }
                nr_of_elems--;
            }
            return true;
        }
    }
    return false;
}

/*
Best case: 0(1) -> When the searched element is the first in the bag

Worst case:0(n) -> When the searched element is the last in the bag,or it's not in the bag at all  

Total: 0(n)
*/

bool Bag::search(TElem e) const {
    for (int i = 0; i < nr_of_elems; i++) {
        if (elements[i].first == e) {
            return true;
        }
    }
    return false;
}

/*
Best case: 0(1) -> When the searched element is the first in the bag

Worst case:0(n) -> When the searched element is the last in the bag,or it's not in the bag at all

Total: 0(n)
*/

int Bag::nrOccurrences(TElem e) const {
    for (int i = 0; i < nr_of_elems; i++) {
        if (elements[i].first == e) {
            return elements[i].second;
        }
    }
    return 0;
}

/*
Best case: 0(n) -> 

Worst case:0(n) -> 

Total: 0(n)
*/

int Bag::size() const {
    int total_elems = 0;
    for (int i = 0; i < nr_of_elems; i++) {
        total_elems += elements[i].second;
    }
    return total_elems;
}

/*
Best case: 0(1) ->

Worst case:0(1) ->

Total: 0(1)
*/

BagIterator Bag::iterator() const {
    return BagIterator(*this);
}

/*
Best case: 0(1) ->

Worst case:0(1) ->

Total: 0(1)
*/

bool Bag::isEmpty() const {
    return (nr_of_elems == 0);
}

/*
Best case: 0(1) ->

Worst case:0(1) ->

Total: 0(1) ?? 
*/

Bag::~Bag() {
    delete[] elements;
}


/*
Best case: 0(n) -> When all the elements in the bag are unique

Worst case:O(n^2) -> When all the elements in the bag are not unique

Total: O(n^2)??
*/
int Bag::removeElementsWIthMultipleOccurences() {
    int result = 0;
    for(int i = 0;i<this->nr_of_elems;++i)
        if (this->elements[i].second > 1) {
            result += this->elements[i].second;
            for (int j = i; j < this->nr_of_elems - 1; ++j)
                this->elements[j] = this->elements[j + 1];
            this->nr_of_elems--;
            i--;
        }
    return result;
}