#include "Dog.hpp"

Dog::Dog() {

}

Dog::~Dog() {

}

Dog::Dog( const Dog& dog ) {
    type = dog.type;
}

Dog::Dog( std::string name ) {
    type = name;
}

Dog& Dog::operator=( const Dog& dog ) {
    type = dog.type;
    return *this;
}

std::string Dog::getType( void ) const {
    return type;
}

void Dog::makeSound( void ) const {
    std::cout << "Wof WOf\n";
}

