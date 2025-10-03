#include "Point.hpp"

Point::~Point() {

}

Point& Point::operator=(Point const &point) {
    (void)point;
    return *this;
}

Fixed Point::getX(void) const {

    return this->x;
}

Fixed Point::getY(void) const {

    return this->y;
}