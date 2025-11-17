#include "AMateria.hpp"

AMateria::~AMateria() {

}

AMateria::AMateria() {

}

AMateria::AMateria( std::string const& type ) {
    this->type = type;
}

AMateria::AMateria( const AMateria& other ) {
    this->type = other.type;
}

AMateria& AMateria::operator=( const AMateria& other ) {
    if (this != &other ) {
        type = other.type;
    }
    return *this;
}

std::string const& AMateria::getType( void ) const {
    return type;
}

void AMateria::use( ICharacter& target ) {
    std::cout << "Me\n" << target.getName();
}

