#include "Animal.hpp"

Animal::Animal() {
    type = "some type of animal";
}

Animal::~Animal() {

}

Animal::Animal( const Animal& animal ) {
    type = animal.type;
}

Animal& Animal::operator=( const Animal& animal ) {
    type = animal.type;
    return *this;
}

void Animal::makeSound( void ) const {
    std::cout << "Animal sound\n";
}

std::string Animal::getType( void ) const {
    return type;
}
