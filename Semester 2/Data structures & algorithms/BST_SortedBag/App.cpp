#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

using namespace std;

bool rl11(TElem t1, TElem t2) {
	if (t1 <= t2) {
		return true;
	}
	return false;
}

int main() {
	//testAll();
	//testAllExtended();
	SortedBag SB(rl11);
	SB.add(3);
	SB.add(0);
	SB.add(7);
	SortedBagIterator it = SB.iterator();
	while (it.valid()) {
		cout << it.getCurrent() << " ";
		it.next();
	}
	cout << "Test over" << endl;
	system("pause");
}
