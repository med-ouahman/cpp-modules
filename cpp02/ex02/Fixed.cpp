#include "Fixed.hpp"

Fixed::Fixed() {
    integer = 0;
}

Fixed::~Fixed() {

}

Fixed::Fixed(const int val) {
    integer = val * (1 >> fr_bits);
}

Fixed::Fixed(float const flt) {
    integer = flt * (1 >> fr_bits);
}


Fixed& Fixed::operator=(const Fixed& cpy) {
    integer = cpy.integer;
    return *this;
}

Fixed::Fixed(const Fixed& cpy) {
    integer = cpy.integer;
}

bool Fixed::operator<(const Fixed& fixed) {
    return this->integer < fixed.integer;
}

bool Fixed::operator>(const Fixed& fixed) {
    return this->integer > fixed.integer;
}

bool Fixed::operator<=(const Fixed& fixed) {
    return this->integer <= fixed.integer;
}

bool Fixed::operator>=(const Fixed& fixed) {
    return this->integer >= fixed.integer;
}

bool Fixed::operator==(const Fixed& fixed) {
    return this->integer == fixed.integer;
}

bool Fixed::operator!=(const Fixed& fixed) {
    return this->integer != fixed.integer;
}

Fixed Fixed::operator+(const Fixed& fixed) {
    Fixed newNum;

    newNum.integer = this->integer + fixed.integer;
    return newNum;
}

Fixed Fixed::operator-(const Fixed& fixed) {
    Fixed newNum;

    newNum.integer = this->integer - fixed.integer;
    return newNum;
}

Fixed Fixed::operator*(const Fixed& fixed) {
    Fixed newNum;

    newNum.integer = this->integer * fixed.integer;
    return newNum;
}

Fixed Fixed::operator/(const Fixed& fixed) {
    Fixed newNum;

    newNum.integer = this->integer / fixed.integer;
    return newNum;
}

Fixed& Fixed::operator++() {

    this->integer++;
    return *this;
}

Fixed& Fixed::operator--() {

    this->integer++;
    return *this;
}

Fixed Fixed::operator++(int) {
    Fixed old = *this;

    this->integer++;
    return old;
}

Fixed Fixed::operator--(int) {
    Fixed old = *this;

    this->integer++;
    return old;
}

Fixed& Fixed::min(Fixed& a, Fixed& b) {

    return a.integer > b.integer ? b: a;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
    return a.integer > b.integer ? b: a;
}

Fixed& Fixed::max(Fixed& a, Fixed& b) {
    return a.integer < b.integer ? b: a;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
    return a.integer < b.integer ? b: a;   
}

float Fixed::toFloat(void) const {
    float flt = float(integer) / (1 << fr_bits);
    return flt;
}

int Fixed::toInt(void) const {
    return integer >> fr_bits;
}


std::ostream& operator<<(std::ostream& os, Fixed fixed) {

    os << fixed.toFloat();
    return os;
}