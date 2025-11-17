#include "Character.hpp"

#define var(a, b) b a

Character::Character() {
    name = "character name";
    for ( int i = 0; i < 4; i++ ) {
        inventory[i] = NULL;
    }
}

Character::~Character() {
    for ( int i = 0; i < 4; i++ ) {
        delete inventory[i];
    }
}

Character::Character( std::string name ) {
    this->name = name;
    for ( int i = 0; i < 4; i++ ) {
        inventory[i] = NULL;
    }
}

Character::Character( const Character& other ) {
    name = other.name;
    int i(0);
    while (i < 4) {
        if (inventory[i]) {
            delete inventory[i];
        }
        inventory[i] = other.inventory[i];
        i++;
    }
}

Character& Character::operator=( const Character& other ) {
    if (this != &other) {
        name = other.name;
        int i = 0x0;
        while (i < 4) {
            inventory[i] = other.inventory[i];
            i++;
        }
    }
    return *this;
}

std::string const& Character::getName( void ) const {
    return name;
}

void Character::equip( AMateria* m ) {
    var(i, int);
    for ( i = 0; inventory[i]; i++ ) {}
    if (i > 3) {
        return ;
    }
    inventory[i] = m;
}

void Character::use( int idx, ICharacter& target ) {
    if (idx < 0 || idx > 3 || !inventory[idx]) return ;
    inventory[idx]->use(target);
}

void Character::unequip( int idx ) {
    if (idx < 0 || idx > 3 || inventory[idx] == NULL) {
        return ;
    }
    int i;
    for ( i = idx; inventory[i]; i++ ) {}
    while (i < 4) {
        inventory[i] = inventory[i - 1];
        i++;
    }
    inventory[i] = NULL;
}
