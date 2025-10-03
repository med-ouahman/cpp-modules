#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

class Point {

private:
    Fixed const x;
    Fixed const y;
public:
    Point() : x(0), y(0) {};
    Point(const float x, const float y): x(x), y(y) {};
    Point(const Point& point): x(point.x), y(point.y) {};
    Point& operator=(const Point& point);
    ~Point();
    Fixed getX(void) const;
    Fixed getY(void) const;
};

#endif