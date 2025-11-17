#pragma once

#include <iostream>

class Animal {

public:
    Animal();
    virtual ~Animal();
    Animal( const Animal& animal );
    Animal& operator=( const Animal& animal );
    virtual void makeSound( void ) const = 0;
    virtual std::string getType( void ) const;
protected:
    std::string type;
};
