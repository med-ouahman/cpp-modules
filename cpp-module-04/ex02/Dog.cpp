#include "Dog.hpp"

Dog::Dog() {
    type = "some type";
    brain = new Brain();
}

Dog::~Dog() {
    delete brain;
}

Dog::Dog( const Dog& dog ) {
    type = dog.type;
brain = new Brain(*dog.brain);
}

Dog::Dog( std::string name ) {
    type = name;
}

Dog& Dog::operator=( const Dog& dog ) {
    type = dog.type;
    delete brain;
    brain = new Brain(*dog.brain);
    return *this;
}

std::string Dog::getType( void ) const {
    return type;
}

void Dog::makeSound( void ) const {
    std::cout << "Wof Wof\n";
}

