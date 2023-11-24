#include "ExtendedTest.h"
#include "ShortTest.h"
#include <assert.h>
#include "SortedMap.h"


#include <iostream>
#include "SMIterator.h"
using namespace std;


bool testing_relation(TKey key1, TKey key2) {
	if (key1 <= key2)
		return true;
	return false;
}


void test_backwards_iterator() {
	SortedMap sm_test(testing_relation);
	sm_test.add(4, 6);
	sm_test.add(1, 5);
	sm_test.add(3, 3);
	assert(sm_test.size() == 3);
	
	SMIterator it = sm_test.iterator();
	it.last();
	assert(it.getCurrent().first == 4);
	it.previous();
	assert(it.getCurrent().first == 3);
	it.previous();
	assert(it.getCurrent().first == 1);
	SMIterator itt = sm_test.iterator();
	itt.first();
	assert(itt.getCurrent().first == 1);
	itt.next();
	assert(itt.getCurrent().first == 3);
	itt.next();
	assert(itt.getCurrent().first == 4);
	
}

int main() {
	test_backwards_iterator();
	testAll();
	testAllExtended();

	cout << "That's all!" << endl;
	system("pause");
	return 0;
}


