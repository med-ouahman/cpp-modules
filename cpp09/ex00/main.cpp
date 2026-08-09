#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}

	std::ifstream inputDB(argv[1]);
	if (!inputDB.is_open()) {
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}

	try {
		BitcoinExchange exchange;
		exchange.evaluate(inputDB);
	} catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}
