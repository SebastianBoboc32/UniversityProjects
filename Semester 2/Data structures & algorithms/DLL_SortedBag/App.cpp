#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

using namespace std;

bool rel1(TComp e1, TComp e2) {
	if (e1 <= e2)
		return true;
	return false;
}

int main() {
	testAll();
	testAllExtended();
	/*
	SortedBag Sb(rel1);
	Sb.add(5);
	Sb.add(6);
	Sb.add(0);
	Sb.add(5);
	Sb.add(10);
	Sb.add(8);
	Sb.add(2);
	SortedBagIterator it(Sb);
	while (it.valid()) {
		cout << it.getCurrent() << " ";
		it.next();
	}
	cout << "\n";
	Sb.remove(6);
	it.first();
	while (it.valid()) {
		cout << it.getCurrent() << " ";
		it.next();
	}
	*/
	cout << "Test over" << endl;
	system("pause");
}
