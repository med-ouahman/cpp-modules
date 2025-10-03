#ifndef FIXED_HPP
#define FIXED_HPP

#include <cmath>
#include <iostream>

class Fixed {
private:
    int integer;
    const static int fr_bits = 8;
public:
    Fixed();
    Fixed(const Fixed& cpy);
    Fixed& operator=(const Fixed& cpy);
    Fixed(const float flt);
    Fixed(const int val);
    int toInt() const;
    float toFloat() const;
    ~Fixed();
    bool operator>(const Fixed& fixed);
    bool operator<(const Fixed& fixed);
    bool operator>=(const Fixed& fixed);
    bool operator<=(const Fixed& fixed);
    bool operator==(const Fixed& fixed);
    bool operator!=(const Fixed& fixed);
    Fixed operator+(const Fixed& fixed);
    Fixed operator-(const Fixed& fixed);
    Fixed operator/(const Fixed& fixed);
    Fixed operator*(const Fixed& fixed);
    Fixed& operator++();
    Fixed& operator--();
    Fixed operator++(int);
    Fixed operator--(int);
    static Fixed& min(Fixed& a, Fixed& b);
    const static Fixed& min(const Fixed& a, const Fixed& b);
    static Fixed& max(Fixed& a, Fixed& b);
    const static Fixed& max(const Fixed& a, const Fixed& b);
};

std::ostream& operator<<(std::ostream& os, Fixed fixed);

#endif