#include <iostream>

#include "atime.h"

int main(int argc, char *argv[]) {
	atime testTimeA;
	//atime testTimeB;

	testTimeA.now();
	//testTimeB.now();
	//testTimeB += testTimeA;

	std::cout << testTimeA.time() << ", " << testTimeA.display() << std::endl;
	//std::cout << testTimeB.time() << ", " << testTimeB.display()  << std::endl;

	return 0;
}