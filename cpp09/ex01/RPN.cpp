#include "RPN.hpp"
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cctype>

RPN::RPN() {}

RPN::RPN(const RPN& other)
{
	(void)other;
}

RPN& RPN::operator=(const RPN& other)
{
	(void)other;
	return *this;
}

RPN::~RPN() {}

static bool isOperatorToken(const std::string& token)
{
	return token == "+" || token == "-" || token == "*" || token == "/";
}

long RPN::evaluate(const std::string& expression) const
{
	std::stack<long> values;
	std::istringstream iss(expression);
	std::string token;

	while (iss >> token)
	{
		if (isOperatorToken(token))
		{
			if (values.size() < 2)
				throw std::runtime_error("not enough operands");

			long b = values.top();
			values.pop();
			long a = values.top();
			values.pop();
			long result = 0;

			if (token == "+")
				result = a + b;
			else if (token == "-")
				result = a - b;
			else if (token == "*")
				result = a * b;
			else
			{
				if (b == 0)
					throw std::runtime_error("division by zero");
				result = a / b;
			}
			values.push(result);
		}
		else if (token.size() == 1 && std::isdigit(static_cast<unsigned char>(token[0])))
		{
			values.push(token[0] - '0');
		}
		else
		{
			throw std::runtime_error("invalid token");
		}
	}

	if (values.size() != 1)
		throw std::runtime_error("invalid expression");

	return values.top();
}
