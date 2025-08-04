#include "Account.hpp"
#include <iostream>
#include <format>
#include <ctime>
#include <stdio.h>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account( int intial_deposit ) {
    Account::_nbAccounts++;
    this->_accountIndex++;
    this->_amount = intial_deposit;
    Account::_totalAmount += this->_amount;
}

Account::~Account(void) {

}

int Account::getNbAccounts(void) {

    return Account::_nbAccounts;
}

int Account::getTotalAmount(void) {

    return Account::_totalAmount;
}


int Account::getNbDeposits(void) {

    return Account::_totalNbDeposits;
}

int Account::getNbWithdrawals(void) {


    return Account::_totalNbWithdrawals;
}

void Account::displayAccountsInfos(void) {
    
    _displayTimestamp();
    
}

void Account::makeDeposit(int deposit) {
    _amount += deposit;
    Account::_totalAmount += deposit;
    _nbDeposits++;
    Account::_totalNbDeposits++;
}

bool Account::makeWithdrawal(int withdrawal) {

    if (withdrawal <= _amount) {
        _amount -= withdrawal;
        _totalAmount -= withdrawal;
        return true;
    }
    std::cout << "refused";
    return false;
}

int Account::checkAmount(void) const {
    
    return _amount;
}

void Account::displayStatus(void) const {

    std::cout << "index:" << this->_accountIndex << ";" << "amount:" << this->_amount
    << ";" << "deposits:" << this->_nbDeposits << ";" << "withdrawals:" << this->_nbWithdrawals << std::endl;
}

void Account::_displayTimestamp(void) {
    time_t now = time(NULL);
    tm *ltime;
    ltime = localtime(&now);
    int year, month, day, hour, minute, second;

    year = ltime->tm_year + 1900;
    month = ltime->tm_mon + 1;
    day = ltime->tm_mday;
    hour = ltime->tm_hour;
    minute = ltime->tm_min;
    second = ltime->tm_sec;



    std::cout << "["
    << year
    << (month < 10 ? "0" : "") << month
    << (day < 10 ? "0" : "") << day
    << "-"
    << (hour < 10 ? "0" : "") << hour
    << (minute < 10 ? "0" : "") << minute
    << (second < 10 ? "0" : "") << second << "] ";
}