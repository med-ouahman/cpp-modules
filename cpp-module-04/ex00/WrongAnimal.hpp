#pragma once

#include <iostream>

class WrongAnimal {

public:
    WrongAnimal();
    ~WrongAnimal();
    WrongAnimal( const WrongAnimal& wAnimal );
    WrongAnimal& operator=( const WrongAnimal& wAnimal );
protected:
    std::string type;
};
