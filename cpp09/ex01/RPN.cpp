#include "RPN.hpp"
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cctype>

RPN::RPN() {}

RPN::RPN(const RPN&) {
}

RPN& RPN::operator=(const RPN&) {
	return *this;
}

RPN::~RPN() {}

static bool isOperatorToken(const std::string& token) {
	return token == "+" || token == "-" || token == "*" || token == "/";
}

static bool isDigitToken(const std::string& token) {
	return token.size() == 1
		&& std::isdigit(static_cast<unsigned char>(token[0]));
}

static long eval(long a, long b, const std::string& op) {

	char c = op[0];
	
	switch (c) {
		case '-': return a - b;
		case '+': return a + b;
		case '*': return a * b;
		case '/': {
			if (b == 0) throw std::runtime_error("division by zero");
			return a / b;
		}
		default: break;
	}
	return 0;
}

long RPN::evaluate(const std::string& expression) const {
	std::stack<long> values;
	std::istringstream iss(expression);
	std::string token;

	while (iss >> token) {
		if (isOperatorToken(token)) {
			if (values.size() < 2) throw std::runtime_error("not enough operands");

			long b = values.top();
			values.pop();
			long a = values.top();
			values.pop();
			long result = eval(a, b, token);
			values.push(result);
		}
		else if (isDigitToken(token))
			values.push(token[0] - '0');
		else
			throw std::runtime_error("invalid token");
	}

	if (values.size() != 1)
		throw std::runtime_error("invalid expression");

	return values.top();
}
