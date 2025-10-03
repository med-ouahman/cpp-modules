#include "Point.hpp"
#include "Fixed.hpp"

/*Area(ABC)=21​*/
static Fixed triangleArea(Point A, Point B, Point C) {

    Fixed area = Fixed(.5f);

    area = area * (A.getX() * (B.getY() - C.getY())
        + B.getX() * (C.getY() - A.getY())
        + C.getX() * (A.getY() - B.getY()));
    if (area < 0)
        return area * -1;
    return area;
}

bool bsp(const Point a, const Point b, const Point c, const Point point) {

    Fixed abc = triangleArea(a, b, c);
    Fixed al = triangleArea(point, b, c) / abc;
    Fixed bet = triangleArea(point, c, a) / abc;
    Fixed gam = triangleArea(point, a, b) / abc;
    if (al >= 0 && bet >= 0 && gam >= 0 && al + bet + gam == 1)
        return true;
    return false;
}


