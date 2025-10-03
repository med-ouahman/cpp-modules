#include "Fixed.hpp"

Fixed::Fixed() {
    integer = 0;
    std::cout << "Default constructor called" << std::endl;
}

Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& cpy) {
    integer = cpy.integer;
    std::cout << "Copy assignment operator called" << std::endl;
    return *this;
}


Fixed::Fixed(const Fixed& cpy) {
    std::cout << "Copy constructor called" << std::endl;
    integer = cpy.integer;
}

int Fixed::getRawBits(void) {
    std::cout << "getRawbits member function called" << std::endl;
    return integer;
}

void Fixed::setRawBits(int const raw) {
    std::cout << "setRawbits member function called" << std::endl;
    integer = raw;
}
