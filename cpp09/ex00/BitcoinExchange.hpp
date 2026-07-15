#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

enum ValueStatus
{
	VALUE_OK,
	VALUE_NOT_A_NUMBER,
	VALUE_NEGATIVE,
	VALUE_TOO_LARGE
};

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		void loadDatabase(const std::string& path);
		bool isDatabaseLoaded() const;
		float getRate(const std::string& date) const;

		static bool isValidDate(const std::string& date);
		static ValueStatus parseValue(const std::string& token, float& out);

	private:
		std::map<std::string, float> _database;
};

#endif
