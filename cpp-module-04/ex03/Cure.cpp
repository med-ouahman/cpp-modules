#include "Cure.hpp"


Cure::Cure() {
    type = "cure";
}

Cure::~Cure() {
    std::cout << "Cure Destructor called\n";
}

Cure::Cure( const Cure& other ): AMateria(other.type) {
    type = other.type;
}

Cure& Cure::operator=( const Cure& other ) {
    if (&other != this) {
        type = other.type;
    }
    return *this;
}

std::string const& Cure::getType( void ) const {
    return type;
}

void Cure::use( ICharacter& target ) {

    std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}

AMateria* Cure::clone( void ) const {
    return new Cure(*this);
}
