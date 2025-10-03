#include "Point.h"
#include "Fixed.h"
#include <stdio.h>

int main( void ) {
    Point a(0, 0);
    Point b(4, 0);
    Point c(0, 4);
    Point p(1, 1);
    bool i = bsp(a, b, c, p);
    printf("Point is %s\n", i ? "inside": "outside");
    return 0;
}