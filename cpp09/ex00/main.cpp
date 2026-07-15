#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

static std::string trimMain(const std::string& s)
{
	size_t start = s.find_first_not_of(" \t\r\n");
	if (start == std::string::npos)
		return "";
	size_t end = s.find_last_not_of(" \t\r\n");
	return s.substr(start, end - start + 1);
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}

	std::ifstream input(argv[1]);
	if (!input.is_open())
	{
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}

	BitcoinExchange exchange;
	try
	{
		exchange.loadDatabase("data.csv");
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}

	std::string line;
	bool isFirstLine = true;

	while (std::getline(input, line))
	{
		if (isFirstLine)
		{
			isFirstLine = false;
			if (line == "date | value")
				continue;
		}
		if (line.empty())
			continue;

		size_t sep = line.find('|');
		if (sep == std::string::npos)
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string datePart = trimMain(line.substr(0, sep));
		std::string valuePart = trimMain(line.substr(sep + 1));

		if (!BitcoinExchange::isValidDate(datePart))
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		float value;
		ValueStatus status = BitcoinExchange::parseValue(valuePart, value);

		if (status == VALUE_NOT_A_NUMBER)
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		if (status == VALUE_NEGATIVE)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		if (status == VALUE_TOO_LARGE)
		{
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}

		try
		{
			float rate = exchange.getRate(datePart);
			std::cout << datePart << " => " << value << " = " << (value * rate) << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
	}

	return 0;
}
