#include "Fixed.hpp"


Fixed::Fixed() {
    integer = 0;
}

Fixed::~Fixed() {
    
}

Fixed& Fixed::operator=(const Fixed& cpy) {
    integer = cpy.integer;
    return *this;
}


Fixed::Fixed(const Fixed& cpy) {
    integer = cpy.integer;
}

int Fixed::getRawBits(void) {
    return integer;
}

void Fixed::setRawBits(int const raw) {
    integer = raw;
}
