#pragma once

#include <iostream>
#include "WrongAnimal.hpp"

class WrongCat: public WrongAnimal {

public:
    WrongCat();
    ~WrongCat();
    WrongCat( const WrongCat& wCat );
    WrongCat& operator=( const WrongCat& wCat );
private:
    std::string type;
};
