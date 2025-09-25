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

Fixed::Fixed(const int val) {
    Fixed fixedVal;
    fixedVal.integer = val;
}

Fixed::Fixed(float const flt) {
    Fixed fixedVal;
    fixedVal.integer = (int)flt;
}

float Fixed::toFloat(void) const {
    return (float)this->integer;
}

int Fixed::toInt(void) const {

    return (int)roundf((float)integer);
}
