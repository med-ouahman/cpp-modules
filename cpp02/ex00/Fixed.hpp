#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {

private:
    int integer;
    const static int fr_bits = 8;
public:
    Fixed();
    Fixed(const Fixed& cpy);
    Fixed& operator=(const Fixed& cpy);
    ~Fixed();
    int getRawBits(void);
    void setRawBits(int const raw);
};

#endif