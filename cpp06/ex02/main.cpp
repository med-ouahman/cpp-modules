#include "functions.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(void)
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	std::cout << "=== Random generation (10 rounds) ===" << std::endl;
	for (int i = 0; i < 10; ++i) {
		Base *obj = generate();
		std::cout << "ptr: "; identify(obj);
		std::cout << "ref: "; identify(*obj);
		delete obj;
		std::cout << "---" << std::endl;
	}

	std::cout << std::endl;
	std::cout << "=== Direct tests ===" << std::endl;

	Base *a = new A();
	Base *b = new B();
	Base *c = new C();

	std::cout << "A ptr: "; identify(a);
	std::cout << "A ref: "; identify(*a);
	std::cout << "B ptr: "; identify(b);
	std::cout << "B ref: "; identify(*b);
	std::cout << "C ptr: "; identify(c);
	std::cout << "C ref: "; identify(*c);

	delete a;
	delete b;
	delete c;
	return 0;
}
