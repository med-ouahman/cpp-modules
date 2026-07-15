#include "Serializer.hpp"
#include <iostream>

int main(void)
{
	Data original;
	original.id    = 42;
	original.name  = "hello";
	original.value = 3.14;

	std::cout << "Original pointer : " << &original << std::endl;

	uintptr_t raw = Serializer::serialize(&original);
	std::cout << "Serialized (int) : " << raw << std::endl;

	Data *recovered = Serializer::deserialize(raw);
	std::cout << "Recovered pointer: " << recovered << std::endl;
	std::cout << "Pointers match   : " << (recovered == &original ? "YES" : "NO") << std::endl;
	std::cout << "id    : " << recovered->id    << std::endl;
	std::cout << "name  : " << recovered->name  << std::endl;
	std::cout << "value : " << recovered->value << std::endl;

	return 0;
}
