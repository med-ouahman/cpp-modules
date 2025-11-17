#pragma once

#include <iostream>
#include "Animal.hpp"

class Dog: public Animal {

public:
    Dog();
    ~Dog();
    Dog( const Dog& Dog );
    Dog& operator=( const Dog& Dog );
    Dog( std::string name );
    std::string getType( void ) const;
    void makeSound( void ) const;
private:
    std::string type;
};
