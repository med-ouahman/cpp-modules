#include "iter.hpp"
#include <iostream>
#include <string>

template <typename T>
void printElem(T const &elem)
{
	std::cout << elem << std::endl;
}

template <typename T>
void increment(T &elem)
{
	++elem;
}

void printUpper(std::string const &s)
{
	for (std::size_t i = 0; i < s.size(); ++i)
		std::cout << static_cast<char>(s[i] >= 'a' && s[i] <= 'z' ? s[i] - 32 : s[i]);
	std::cout << std::endl;
}

int main(void)
{
	std::cout << "--- int array (print) ---" << std::endl;
	int ints[] = {1, 2, 3, 4, 5};
	iter(ints, 5, printElem<int>);

	std::cout << "--- int array (increment then print) ---" << std::endl;
	iter(ints, 5, increment<int>);
	iter(ints, 5, printElem<int>);

	std::cout << "--- string array (print) ---" << std::endl;
	std::string strs[] = {"hello", "world", "cpp"};
	iter(strs, 3, printElem<std::string>);

	std::cout << "--- string array (printUpper) ---" << std::endl;
	iter(strs, 3, printUpper);

	std::cout << "--- const int array ---" << std::endl;
	int const consts[] = {10, 20, 30};
	iter(consts, 3, printElem<int>);

	std::cout << "--- double array ---" << std::endl;
	double dbls[] = {1.1, 2.2, 3.3};
	iter(dbls, 3, printElem<double>);

	std::cout << "--- empty array (no output expected) ---" << std::endl;
	iter(ints, 0, printElem<int>);
	std::cout << "(done)" << std::endl;

	return 0;
}
