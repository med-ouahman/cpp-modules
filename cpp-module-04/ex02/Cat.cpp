#include "Cat.hpp"

Cat::Cat() {
    std::cout << "Default constructor called\n";
    type = "some type";
    brain = new Brain();
}

Cat::~Cat() {
    std::cout << "Cat destructor called\n";
    delete brain;
}

Cat::Cat( const Cat& cat ) {
    type = cat.type;
    brain = new Brain(*cat.brain);

}

Cat& Cat::operator=( const Cat& cat ) {
    type = cat.type;
    delete brain;
    brain = new Brain(*cat.brain);
    return *this;
}

Cat::Cat( std::string name ) {
    type = name;
}

std::string Cat::getType( void ) const {
    return type;
}

void Cat::makeSound( void ) const {
    std::cout << "Meow Meow\n";
}