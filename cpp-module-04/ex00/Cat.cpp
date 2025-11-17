#include "Cat.hpp"

Cat::Cat() {

}

Cat::~Cat() {

}

Cat::Cat( const Cat& cat ) {
    type = cat.type;
}

Cat& Cat::operator=( const Cat& cat ) {
    type = cat.type;
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