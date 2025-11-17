#pragma once

#include "AMateria.hpp"

class Cure: public AMateria {

public:
    Cure();
    ~Cure();
    Cure( const Cure& other );
    Cure& operator=( const Cure& other );
    void use( ICharacter& target );
    std::string const& getType() const;
    AMateria* clone( void ) const;
};
