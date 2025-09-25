#ifndef FIXED_HPP
#define FIXED_HPP

#include <cmath>

class Fixed {

private:
    int integer;
    const static int fr_bits = 8;
public:
    Fixed();
    Fixed(const Fixed& cpy);
    Fixed& operator=(const Fixed& cpy);
    Fixed(const int val);
    Fixed(float const flt);
    ~Fixed();
    int getRawBits(void);
    void setRawBits(int const raw);
    float toFloat(void) const;
    int toInt(void) const;
};

#endif