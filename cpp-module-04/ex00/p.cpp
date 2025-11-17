#include <iostream>

class Animal {
public:
    virtual void makeSound() const {
        std::cout << "Generic animal sound\n";
    }

    // Always include a virtual destructor in base classes
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    void makeSound() const {
        std::cout << "Woof!\n";
    }
};

int main() {
    const Animal* a = new Dog();
    a->makeSound(); // Outputs: Woof!
    delete a;
    return 0;
}
