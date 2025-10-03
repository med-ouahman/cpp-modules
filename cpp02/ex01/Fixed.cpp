#include "Fixed.hpp"

int get_fraction(int fr_bits) {

    int fraction = 1;
    while (fr_bits) {
        fraction *= 2;
        fr_bits--;
    }
    return fraction;
}

Fixed::Fixed() {
    std::cout << "Default constructor called" << std::endl;
    integer = 0;
}

Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& cpy) {
    std::cout << "Copy assignment operator called" << std::endl;
    integer = cpy.integer;
    return *this;
}

Fixed::Fixed(const Fixed& cpy) {
    integer = cpy.integer;
}

int Fixed::getRawBits(void) {
    std::cout << "getRawBits member function called" << std::endl;
    return integer;
}

void Fixed::setRawBits(int const raw) {
    integer = raw;
}

Fixed::Fixed(const int val) {
    std::cout << "Int constructor called" << std::endl;
    integer = val * get_fraction(Fixed::fr_bits); // get_fraction(Fixed::fr_bits) == 2^8;
}

Fixed::Fixed(float const flt) {
    std::cout << "Float constructor called" << std::endl;
    integer = flt * float(get_fraction(Fixed::fr_bits));
}

float Fixed::toFloat(void) const {
    float flt = float(integer) / float(get_fraction(Fixed::fr_bits));
    return flt;
}

int Fixed::toInt(void) const {
    return integer / get_fraction(Fixed::fr_bits);
}

std::ostream& operator<<(std::ostream& os, Fixed fixed) {

    os << fixed.toFloat();
    return os;
}
