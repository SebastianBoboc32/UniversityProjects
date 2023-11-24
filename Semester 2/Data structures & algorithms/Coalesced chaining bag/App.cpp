#include "Bag.h"
#include "BagIterator.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>

using namespace std;

int main() {

	Bag bg;
	for (int i = 0; i < 100; ++i) {
		bg.add(i * 71);
	}
	BagIterator it = bg.iterator();
	while (it.valid()) {
		TElem y = it.getCurrent();
		if(y != -111111)
		cout <<y << " ";
		if (y % 4 == 0)
			bg.remove(y);
		it.next();
	}
	it.first();
	cout << "\n";
	while (it.valid()) {
		if (it.getCurrent() != -111111)
		cout << it.getCurrent() << " ";
		it.next();
	}
	cin.ignore();
	return 0;
}