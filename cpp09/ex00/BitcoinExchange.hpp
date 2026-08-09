#pragma once

#include <map>
#include <string>

enum ValueStatus {
	OK,
	NaN,
	Negative,
	TooLarge,
	BadInput,
};

enum Error {
	None,
	FileError,
	DbEmpty,
};

class BitcoinExchange {
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	bool isDatabaseLoaded() const;
	float getRate(const std::string& date) const;

	static bool isValidDate(const std::string& date);
	static ValueStatus parseValue(const std::string& token, float& out);

	Error evaluate(std::ifstream& inputDB);

private:
	std::map<std::string, float> database_;
	Error 		loadDatabase(const std::string& path);
	ValueStatus parseLine(const std::string& line, float& out);
};

std::string trimStr(const std::string& s);