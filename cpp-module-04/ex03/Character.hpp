#pragma once

#include "ICharacter.hpp"
#include "AMateria.hpp"
#include <iostream>

class Character: public ICharacter {
private:
    std::string name;
    AMateria* inventory[4];
public:
    Character();
    ~Character();
    Character( std::string name );
    Character( const Character& other );
    Character& operator=( const Character& other );
    std::string const& getName( void ) const;
    void equip( AMateria* m );
    void unequip( int idx );
    void use( int idx, ICharacter& target );
};
