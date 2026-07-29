#include "ScalarConverter.hpp"
#include <iostream>
#include <iomanip>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <limits>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &) {}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &) { return *this; }
ScalarConverter::~ScalarConverter() {}


static bool isCharLiteral(const std::string &s) {
	return s.length() == 3 && s[0] == '\'' && s[2] == '\'';
}

static bool isPseudoFloat(const std::string &s) {
	return s == "-inff" || s == "+inff" || s == "nanf";
}

static bool isPseudoDouble(const std::string &s) {
	return s == "-inf" || s == "+inf" || s == "nan";
}

static bool isFloat(const std::string &s) {

	if (s.empty() || s[s.size() - 1] != 'f')
		return false;
	std::string sub = s.substr(0, s.size() - 1);
	char *end;
	strtod(sub.c_str(), &end);
	return *end == '\0' && end != sub.c_str();
}

static bool isDouble(const std::string &s) {
	char *end;
	
	strtod(s.c_str(), &end);
	return *end == '\0' && end != s.c_str();
}

static bool isInt(const std::string &s) {
	char *end;
	long v = strtol(s.c_str(), &end, 10);
	return *end == '\0' && end != s.c_str()
		&& v >= static_cast<long>(INT_MIN)
		&& v <= static_cast<long>(INT_MAX);
}

static void printChar(double d) {
	if (std::isnan(d) || std::isinf(d) || d < 0 || d > 127)
		std::cout << "char: impossible" << std::endl;
	else if (!std::isprint(static_cast<int>(d)))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
}

static void printInt(double d) {
	if (std::isnan(d) || std::isinf(d)
		|| d < static_cast<double>(INT_MIN)
		|| d > static_cast<double>(INT_MAX))
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(d) << std::endl;
}

static void printFloat(double d) {
	float f = static_cast<float>(d);
	if (std::isnan(f))
		std::cout << "float: nanf" << std::endl;
	else if (std::isinf(f))
		std::cout << "float: " << (f > 0 ? "+" : "-") << "inff" << std::endl;
	else
		std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << std::endl;
}

static void printDouble(double d) {
	if (std::isnan(d))
		std::cout << "double: nan" << std::endl;
	else if (std::isinf(d))
		std::cout << "double: " << (d > 0 ? "+" : "-") << "inf" << std::endl;
	else
		std::cout << "double: " << std::fixed << std::setprecision(1) << d << std::endl;
}

void ScalarConverter::convert(const std::string &s) {
	double d;

	if (isCharLiteral(s)) {
		d = static_cast<double>(s[1]);
	} else if (isPseudoFloat(s)) {
		if (s == "nanf")       d = std::numeric_limits<double>::quiet_NaN();
		else if (s == "+inff") d = std::numeric_limits<double>::infinity();
		else                   d = -std::numeric_limits<double>::infinity();
	} else if (isPseudoDouble(s)) {
		if (s == "nan")       d = std::numeric_limits<double>::quiet_NaN();
		else if (s == "+inf") d = std::numeric_limits<double>::infinity();
		else                  d = -std::numeric_limits<double>::infinity();
	} else if (isInt(s)) {
		d = static_cast<double>(strtol(s.c_str(), NULL, 10));
	} else if (isFloat(s)) {
		std::string sub = s.substr(0, s.size() - 1);
		d = static_cast<double>(strtof(sub.c_str(), NULL));
	} else if (isDouble(s)) {
		d = strtod(s.c_str(), NULL);
	} else {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}

	printChar(d);
	printInt(d);
	printFloat(d);
	printDouble(d);
}
