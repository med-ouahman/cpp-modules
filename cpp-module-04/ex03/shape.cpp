
#include <iostream>

class Shape {
protected:
std::string name;
public:
    virtual ~Shape() {}
   virtual void draw() {
        std::cout << "Drawing shape\n";
    }
};

class Circle: public Shape {

public:
    Circle(std::string n) {
        name = n;
    }
    ~Circle() {}
    void draw() {
        std::cout << "Drawing circle\n";
    }
};

class Square: public Shape {

public:
    Square(std::string n) {
        name = n;
    }
    ~Square() {}
    void draw() {
        std::cout << "Drawing square\n";
    }
};


int main( void ) {
    Shape* a = new Circle("fc");
    a->draw();
    delete a;
    return 0;
}