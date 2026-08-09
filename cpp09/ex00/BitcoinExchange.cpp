#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <cctype>
#include <iostream>

BitcoinExchange::BitcoinExchange() {
	loadDatabase("data.csv");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
: database_(other.database_) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) database_ = other.database_;

	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

std::string trimStr(const std::string& s) {
	size_t start = s.find_first_not_of(" \t\r\n");
	if (start == std::string::npos)
		return "";
	size_t end = s.find_last_not_of(" \t\r\n");
	return s.substr(start, end - start + 1);
}

Error BitcoinExchange::loadDatabase(const std::string& path) {
	std::ifstream file(path.c_str());

	if (!file.is_open()) throw std::runtime_error("Failed to open database file");

	std::string line;
	bool header = false;
	while (std::getline(file, line)) {
		
		if (!header) {
			header = true;
			continue;
		}

		if (line.empty()) continue;

		size_t sep = line.find(',');
		if (sep == std::string::npos)
			continue;

		std::string date = trimStr(line.substr(0, sep));
		std::string ratePart = trimStr(line.substr(sep + 1));

		if (!isValidDate(date)) continue;

		float rate;
		ValueStatus status = parseValue(ratePart, rate);
		if (status != OK)
			continue;

		database_[date] = rate;
	}

	if (database_.empty()) throw std::runtime_error("Failed to load database");

	return None;
}

bool BitcoinExchange::isDatabaseLoaded() const {
	return !database_.empty();
}

float BitcoinExchange::getRate(const std::string& date) const {
	std::map<std::string, float>::const_iterator it = database_.lower_bound(date);

	if (it != database_.end() && it->first == date)
		return it->second;
	if (it == database_.begin())
		throw std::runtime_error("no database entry at or before this date.");
	--it;
	return it->second;
}

bool BitcoinExchange::isValidDate(const std::string& date) {
	if (date.size() != 10)
		return false;

	for ( size_t i = 0; i < date.size(); ++i ) {
		if (i == 4 || i == 7) {
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

ValueStatus BitcoinExchange::parseValue(const std::string& token, float& out) {
	if (token.empty())
		return NaN;

	std::istringstream iss(token);
	float value;
	iss >> value;
	if (iss.fail())
		return NaN;

	std::string leftover;
	if (iss >> leftover)
		return NaN;

	if (value < 0)
		return Negative;
	if (value > 1000)
		return TooLarge;

	out = value;
	return OK;
}

ValueStatus BitcoinExchange::parseLine(const std::string& line, float& out) {
	
	size_t sep = line.find("|");

	if (sep == std::string::npos || !isValidDate(line.substr(0, sep))) return BadInput;
	
	return parseValue(line.substr(sep + 1), out);
}

Error BitcoinExchange::evaluate(std::ifstream& inputDB) {

	bool header = false;

	for ( std::string line; std::getline(inputDB, line); ) {
		if (line.empty())  continue;

		if (!header) {
			header = true;
			continue;
		}
		
		float value;

		size_t sep = line.find("|");
		std::string date = line.substr(0, sep);

		ValueStatus status = OK;

		if (sep == std::string::npos || !isValidDate(date)) status = BadInput;
		if (status == OK) status = parseValue(line.substr(sep + 1), value);

		switch (status) {
			case OK: break;
			case NaN: case BadInput:
				std::cout << "Error: bad input => " << line << "\n"; break;
			case Negative:
				std::cout << "Error: not a positive number" << "\n"; break;
			case TooLarge:
				std::cout << "Error: number too large" << "\n"; break;
			default: break;
		}

		try {
			std::cout << date << " => " << value << " = " << (value * getRate(date)) << "\n";
		} catch (const std::exception& error) { std::cout << "Error: " << error.what() << "\n"; }
	}

	return None;
}