#pragma once

#include <iostream>
#include "Animal.hpp"

class Cat: public Animal {

public:
    Cat();
    ~Cat();
    Cat( const Cat& Cat );
    Cat& operator=( const Cat& Cat );
    Cat( std::string name );
    std::string getType( void ) const;
    void makeSound( void ) const;
private:
    std::string type;
};

