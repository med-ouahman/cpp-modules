#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() {
    type = "Some type of animal";
}


WrongAnimal::~WrongAnimal() {

}

WrongAnimal::WrongAnimal( const WrongAnimal& wAnimal ) {

    type = wAnimal.type;
}

WrongAnimal& WrongAnimal::operator=( const WrongAnimal& wAnimal ) {

    type = wAnimal.type;
    return *this;
}
