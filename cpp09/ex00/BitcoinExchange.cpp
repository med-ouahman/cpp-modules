#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <cctype>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	_database = other._database;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_database = other._database;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

static std::string trimStr(const std::string& s)
{
	size_t start = s.find_first_not_of(" \t\r\n");
	if (start == std::string::npos)
		return "";
	size_t end = s.find_last_not_of(" \t\r\n");
	return s.substr(start, end - start + 1);
}

void BitcoinExchange::loadDatabase(const std::string& path)
{
	std::ifstream file(path.c_str());
	if (!file.is_open())
		throw std::runtime_error("could not open database.");

	std::string line;
	bool isFirstLine = true;

	while (std::getline(file, line))
	{
		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}
		if (line.empty())
			continue;

		size_t sep = line.find(',');
		if (sep == std::string::npos)
			continue;

		std::string datePart = trimStr(line.substr(0, sep));
		std::string ratePart = trimStr(line.substr(sep + 1));

		if (!isValidDate(datePart))
			continue;

		float rate;
		ValueStatus status = parseValue(ratePart, rate);
		if (status != VALUE_OK && status != VALUE_TOO_LARGE)
			continue;

		_database[datePart] = rate;
	}

	if (_database.empty())
		throw std::runtime_error("database is empty.");
}

bool BitcoinExchange::isDatabaseLoaded() const
{
	return !_database.empty();
}

float BitcoinExchange::getRate(const std::string& date) const
{
	std::map<std::string, float>::const_iterator it = _database.lower_bound(date);

	if (it != _database.end() && it->first == date)
		return it->second;
	if (it == _database.begin())
		throw std::runtime_error("no database entry at or before this date.");
	--it;
	return it->second;
}

bool BitcoinExchange::isValidDate(const std::string& date)
{
	if (date.size() != 10)
		return false;

	for (size_t i = 0; i < date.size(); ++i)
	{
		if (i == 4 || i == 7)
		{
			if (date[i] != '-')
				return false;
		}
		else if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return false;
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12)
		return false;

	int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
	int maxDay = daysInMonth[month - 1];
	if (month == 2 && isLeap)
		maxDay = 29;

	if (day < 1 || day > maxDay)
		return false;

	return true;
}

ValueStatus BitcoinExchange::parseValue(const std::string& token, float& out)
{
	if (token.empty())
		return VALUE_NOT_A_NUMBER;

	std::istringstream iss(token);
	float value;
	iss >> value;
	if (iss.fail())
		return VALUE_NOT_A_NUMBER;

	std::string leftover;
	if (iss >> leftover)
		return VALUE_NOT_A_NUMBER;

	if (value < 0)
		return VALUE_NEGATIVE;
	if (value > 1000)
		return VALUE_TOO_LARGE;

	out = value;
	return VALUE_OK;
}
