#include "Ice.hpp"

Ice::Ice() {
    type = "ice";
}

Ice::~Ice() {
    std::cout << "Ice Destructor called\n";
}

Ice::Ice( const Ice& other ): AMateria(other.type) {
    type = other.type;
}

Ice& Ice::operator=( const Ice& other ) {
    if (&other != this) {
        type = other.type;
    }
    return *this;
}

void Ice::use( ICharacter& target ) {
    std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}

AMateria* Ice::clone( void ) const {
    return new Ice(*this);
}
