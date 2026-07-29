#include "whatever.hpp"
#include <iostream>
#include <string>

int main(void) {
	int a = 2;
	int b = 3;

	::swap(a, b);
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
	std::cout << "max(a, b) = " << ::max(a, b) << std::endl;

	std::string c = "chaine1";
	std::string d = "chaine2";

	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min(c, d) = " << ::min(c, d) << std::endl;
	std::cout << "max(c, d) = " << ::max(c, d) << std::endl;

	int x = 5;
	int y = 5;
	std::cout << "min(5, 5) = " << ::min(x, y) << " (expect second = 5)" << std::endl;
	std::cout << "max(5, 5) = " << ::max(x, y) << " (expect second = 5)" << std::endl;

	double p = 1.1;
	double q = 2.2;
	::swap(p, q);
	std::cout << "swap doubles: p=" << p << " q=" << q << std::endl;
	std::cout << "min(p, q) = " << ::min(p, q) << std::endl;
	std::cout << "max(p, q) = " << ::max(p, q) << std::endl;

	return 0;
}
