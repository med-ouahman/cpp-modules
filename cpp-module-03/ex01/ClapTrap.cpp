#include "ClapTrap.hpp"

ClapTrap::ClapTrap() {

    std::cout << "ClapTrap Default constructor called" << std::endl;
}

ClapTrap::~ClapTrap() {
    std::cout << "ClapTrap Destrutcor called" << std::endl;
}

ClapTrap::ClapTrap( std::string name ) {
    std::cout << "ClapTrap name init constructor called" << std::endl;
    this->name = name;
    attackDamage = 0;
    hitPoints = 10;
    energy = 10;
}

ClapTrap& ClapTrap::operator=( const ClapTrap& other ) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other) {
        name = other.name;
        energy = other.energy;
        hitPoints = other.hitPoints;
        attackDamage = other.attackDamage;
    }
    return *this;
}

ClapTrap::ClapTrap( const ClapTrap& other ) {
    std::cout << "ClapTrap Copy constructor called" << std::endl;
    name = other.name;
    energy = other.energy;
    hitPoints = other.hitPoints;
    attackDamage = other.attackDamage;
}

void ClapTrap::attack( const std::string& target ) {
    if (energy == 0 || hitPoints == 0) {
        return ;
    }
    energy--;
    std::cout << "ClapTrap " << name <<  " attacks " << target <<  " causing " << attackDamage <<  " points of damage!" << std::endl;
}

void ClapTrap::takeDamage( unsigned int amount ) {

    if (amount >= attackDamage) {
        attackDamage = 0;
    } else {
        attackDamage -= amount;
    }
    std::cout << "ClapTrap " << name << " took " << amount << " of damage" << std::endl;
}

void ClapTrap::beRepaired( unsigned int amount ) {

    if (energy <= 0)
        return ;
    hitPoints += amount;
    energy--;
    std::cout << "ClapTrap " << name << " repaired and gained " << amount << " of hit points" << std::endl;
}
