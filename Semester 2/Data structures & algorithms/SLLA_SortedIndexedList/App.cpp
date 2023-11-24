#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"
#include "ListIterator.h"
#include "SortedIndexedList.h"

bool ascending(TComp c1, TComp c2) {
	if (c1 <= c2) {
		return true;
	}
	else {
		return false;
	}
}

int main(){
    //testAll();
    //testAllExtended();
	SortedIndexedList SIL(ascending);
	ListIterator it = SIL.iterator();
	SIL.add(11);
	SIL.add(1);
	SIL.add(31);
	SIL.add(44);
	SIL.add(200);
	SIL.add(16);
	SIL.add(119);
	SIL.add(2);
	SIL.add(22);
	SIL.add(34);
	SIL.add(1);
	SIL.add(0);
	SIL.add(-7);
	while (it.valid()) {
		std::cout << it.getCurrent() << " ";
		it.next();
	}
    std::cout<<"Finished IL Tests!"<<std::endl;
	system("pause");
}