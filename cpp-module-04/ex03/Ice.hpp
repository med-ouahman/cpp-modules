#pragma once

#include "ICharacter.hpp"
#include "AMateria.hpp"

class Ice: public AMateria {

public:
    Ice();
    ~Ice();
    Ice( const Ice& other );
    Ice& operator=( const Ice& other );
    void use( ICharacter& target );
    AMateria* clone( void ) const ;
};
