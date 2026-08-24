#include "PmergeMe.hpp"
#include <iostream>
#include <sys/time.h>

static double nowMicroseconds() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return static_cast<double>(tv.tv_sec) * 1000000.0 + static_cast<double>(tv.tv_usec);
}

int main(int argc, char** argv) {

	while (true) {
		break;
		size_t n;
		std::cout << "N: ";

		std::cin >> n;
		PmergeMe x(n);
	}

	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	std::vector<int> original;
	try {
		PmergeMe::parseArguments(original, const_cast<const char**>(argv + 1), argc - 1);

	} catch (const std::exception&) {
		std::cerr << "Error" << std::endl;
		return 1;
	}

	std::vector<int> vecData(original.begin(), original.end());
	std::deque<int> dequeData(original.begin(), original.end());

	std::cout << "Before:";
	for (size_t i = 0; i < original.size(); ++i)
		std::cout << " " << original[i];
	std::cout << std::endl;

	PmergeMe pm(original.size());

	double vecStart = nowMicroseconds();
	pm.sortVector(vecData);
	double vecEnd = nowMicroseconds();

	double dequeStart = nowMicroseconds();
	pm.sortDeque(dequeData);
	double dequeEnd = nowMicroseconds();

	std::cout << "After:";
	for ( size_t i = 0; i < vecData.size(); ++i )
		std::cout << " " << vecData[i];
	std::cout << std::endl;

	std::cout.setf(std::ios::fixed);
	std::cout.precision(2);

	std::cout << "Time to process a range of " << original.size()
		<< " elements with std::vector : " << (vecEnd - vecStart) << " us" << std::endl;
	std::cout << "Time to process a range of " << original.size()
		<< " elements with std::deque : " << (dequeEnd - dequeStart) << " us" << std::endl;

	return 0;
}
