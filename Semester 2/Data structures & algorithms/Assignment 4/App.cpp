
#include "ShortTest.h"
#include "ExtentedTest.h"
#include  "SortedMap.h"
#include "SMIterator.h"

#include <iostream>
using namespace std;


int main() {
	testAll();
	testAllExtended();

	cout << "That's all!" << endl;
	system("pause");
	return 0;
}
