#include "ShortTest.h"
#include <assert.h>
#include "Bag.h"
#include "BagIterator.h"
#include <iostream>


void testAll() { 
	Bag b;
	assert(b.isEmpty() == true);
	assert(b.size() == 0); 
	b.add(5);
	b.add(1);
	b.add(10);
	b.add(7);
	b.add(1);
	b.add(11);
	b.add(-3);
	assert(b.size() == 7);
	assert(b.search(10) == true);
	assert(b.search(16) == false);
	assert(b.nrOccurrences(1) == 2);
	assert(b.nrOccurrences(7) == 1);
	assert(b.remove(1) == true);
	assert(b.remove(6) == false);
	assert(b.size() == 6);
	assert(b.nrOccurrences(1) == 1);
	BagIterator it = b.iterator();
	it.first();
	while (it.valid()) {
		TElem e = it.getCurrent();
		it.next();
	}
	Bag bi;
	bi.add(5);
	bi.add(1);
	bi.add(10);
	bi.add(7);
	bi.add(11);
	bi.add(-3);
	bi.add(5);
	bi.add(1);
	bi.add(10);
	bi.add(7);
	bi.add(11);
	bi.add(-3);
	assert(bi.removeElementsWIthMultipleOccurences()==12);
	assert(bi.size() == 0);
	Bag b1;
	b1.add(5);
	b1.add(1);
	b1.add(10);
	b1.add(7);
	b1.add(11);
	b1.add(-3);
	b1.add(5);
	b1.add(1);
	b1.add(10);
	assert(b1.removeElementsWIthMultipleOccurences() == 6);
	assert(b1.size() == 3);

	Bag b2;
	b2.add(4);
	b2.add(5);
	assert(b2.removeElementsWIthMultipleOccurences() == 0);
	assert(b2.size() == 2);
}
