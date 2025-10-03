#include "Account.hpp"
#include <iostream>
#include <ctime>
#include <stdio.h>

int accIndex = 0;

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account( int intial_deposit ) {
    Account::_nbAccounts++;
    this->_accountIndex = accIndex++;
    this->_amount = intial_deposit;
    Account::_totalAmount += this->_amount;
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";"
    << "amount:" << this->_amount << ";created" << std::endl;
}

Account::~Account(void) {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";"
    << "amount:" << this->_amount << ";closed" << std::endl;
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
    std::cout << "accounts:"
    << _nbAccounts << ";"
    << "total:" << _totalAmount << ";"
    << "deposits:" << _totalNbDeposits << ";"
    << "withdrawals:" << _totalNbWithdrawals << std::endl;
    
}

void Account::makeDeposit(int deposit) {
    int prevAmount = _amount;
    _amount += deposit;
    Account::_totalAmount += deposit;
    _nbDeposits++;
    Account::_totalNbDeposits++;
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";"
    << "p_amount:" << prevAmount << ";"
    << "deposit:" << deposit << ";"
    << "amount:" << this->_amount << ";"
    << "nb_deposits:" << _nbDeposits << std::endl;
}

bool Account::makeWithdrawal(int withdrawal) {
    int prevAmount = _amount;
    bool success = false;
    if (withdrawal <= _amount) {
        _amount -= withdrawal;
        _totalAmount -= withdrawal;
        _nbWithdrawals++;
        Account::_totalNbWithdrawals++;
        success = true;
    }
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";"
    << "p_amount:" << prevAmount << ";";
    if (!success) {
        std::cout << "withdrawal:refused" << std::endl;
    } else {
        std::cout << "withdrawal:" << withdrawal << ";"
        << "amount:" << this->_amount << ";"
        << "nb_withdrawals:" << _nbWithdrawals << std::endl;
    }
    return success;
}

int Account::checkAmount(void) const {
    
    return _amount;
}

void Account::displayStatus(void) const {

    _displayTimestamp();
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