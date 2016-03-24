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

	testTimeA.setYear(1989);
	testTimeA.setMonth(3);
	testTimeA.setDayOfMonth(14);
	testTimeA.setHour(15);
	testTimeA.setMinutes(43);
	testTimeA.setSeconds(53);

	std::cout << testTimeA.time() << ", " << testTimeA.display() << std::endl;


	return 0;
}