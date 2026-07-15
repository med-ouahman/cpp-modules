#include "Array.hpp"
#include <iostream>
#include <string>

template <typename T>
void printArray(Array<T> const &arr)
{
	for (unsigned int i = 0; i < arr.size(); ++i)
		std::cout << "[" << i << "] = " << arr[i] << std::endl;
}

int main(void)
{
	std::cout << "--- default constructor (empty) ---" << std::endl;
	Array<int> empty;
	std::cout << "size = " << empty.size() << std::endl;

	std::cout << "--- size constructor ---" << std::endl;
	Array<int> ints(5);
	std::cout << "size = " << ints.size() << std::endl;
	for (unsigned int i = 0; i < ints.size(); ++i)
		std::cout << "ints[" << i << "] default = " << ints[i] << std::endl;

	std::cout << "--- fill and print ---" << std::endl;
	for (unsigned int i = 0; i < ints.size(); ++i)
		ints[i] = static_cast<int>(i * 10);
	printArray(ints);

	std::cout << "--- copy constructor (deep copy) ---" << std::endl;
	Array<int> copy(ints);
	copy[0] = 999;
	std::cout << "original ints[0] = " << ints[0] << " (must stay 0)" << std::endl;
	std::cout << "copy[0] = " << copy[0] << " (must be 999)" << std::endl;

	std::cout << "--- assignment operator (deep copy) ---" << std::endl;
	Array<int> assigned;
	assigned = ints;
	assigned[1] = 888;
	std::cout << "original ints[1] = " << ints[1] << " (must stay 10)" << std::endl;
	std::cout << "assigned[1] = " << assigned[1] << " (must be 888)" << std::endl;

	std::cout << "--- self-assignment ---" << std::endl;
	ints = ints;
	std::cout << "ints[0] = " << ints[0] << " (must stay 0)" << std::endl;

	std::cout << "--- string array ---" << std::endl;
	Array<std::string> strs(3);
	strs[0] = "hello";
	strs[1] = "world";
	strs[2] = "cpp";
	printArray(strs);

	std::cout << "--- out of bounds on non-empty array ---" << std::endl;
	try {
		int x = ints[100];
		(void)x;
		std::cout << "FAIL: no exception thrown" << std::endl;
	} catch (std::exception const &e) {
		std::cout << "PASS: caught exception: " << e.what() << std::endl;
	}

	std::cout << "--- out of bounds on empty array ---" << std::endl;
	try {
		int x = empty[0];
		(void)x;
		std::cout << "FAIL: no exception thrown" << std::endl;
	} catch (std::exception const &e) {
		std::cout << "PASS: caught exception: " << e.what() << std::endl;
	}

	std::cout << "--- const array access ---" << std::endl;
	Array<int> const constArr(ints);
	std::cout << "constArr[0] = " << constArr[0] << std::endl;
	try {
		int x = constArr[999];
		(void)x;
		std::cout << "FAIL: no exception thrown" << std::endl;
	} catch (std::exception const &e) {
		std::cout << "PASS: const out-of-bounds: " << e.what() << std::endl;
	}

	std::cout << "--- value initialisation (all zeros) ---" << std::endl;
	Array<int> zeroed(4);
	bool allZero = true;
	for (unsigned int i = 0; i < zeroed.size(); ++i)
		if (zeroed[i] != 0) allZero = false;
	std::cout << (allZero ? "PASS: all zero" : "FAIL: not zero") << std::endl;

	return 0;
}
