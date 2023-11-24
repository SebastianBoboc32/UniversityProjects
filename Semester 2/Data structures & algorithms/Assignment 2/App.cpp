#include <iostream>
#include <assert.h>
#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedMultiMap.h"

bool relation9(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void test_keyset() {
	SortedMultiMap M = SortedMultiMap(relation9);
	M.add(1, 2);
	M.add(1, 4);
	M.add(2, 4);
	vector<TKey> values = M.keySet();
	assert(values.size() == 2);
	assert(values[0] == 1);
}

int main(){
	test_keyset();
    testAll();
	testAllExtended();
    std::cout<<"Finished SMM Tests!"<<std::endl;
	system("pause");
}
