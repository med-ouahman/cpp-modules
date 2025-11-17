#include "ClapTrap.hpp"

ClapTrap::ClapTrap() {
    std::cout << "ClapTrap default constructor called\n";
}

ClapTrap::~ClapTrap() {
    std::cout << "ClapTrap destrutcor called\n";
}

ClapTrap::ClapTrap( std::string name ) {
    std::cout << "ClapTrap name init constructor called\n";
    this->name = name;
    attackDamage = 0;
    hitPoints = 10;
    energy = 10;
}

ClapTrap& ClapTrap::operator=( const ClapTrap& other ) {
    std::cout << "ClapTrap copy assignment operator called\n";
    if (this != &other) {
        name = other.name;
        energy = other.energy;
        hitPoints = other.hitPoints;
        attackDamage = other.attackDamage;
    }
    return *this;
}

ClapTrap::ClapTrap( const ClapTrap& other ) {
    std::cout << "ClapTrap copy constructor called\n";
    name = other.name;
    energy = other.energy;
    hitPoints = other.hitPoints;
    attackDamage = other.attackDamage;
}

void ClapTrap::attack( const std::string& target ) {
    if (energy == 0 || hitPoints == 0) {
        return ;
    }
    std::cout << "ClapTrap " << name <<  " attacks " << target <<  " causing " << attackDamage <<  " points of damage!\n";
}

void ClapTrap::takeDamage( unsigned int amount ) {

    if (amount > attackDamage) {
        attackDamage = 0;
    } else {
        attackDamage -= amount;
    }
    std::cout << "ClapTrap " << name << " took " << amount << " of damage\n";
}

void ClapTrap::beRepaired( unsigned int amount ) {

    if (energy == 0) {
        return ;
    }
    hitPoints += amount;
    energy--;
    std::cout << "ClapTrap " << name << " repaired and gained " << amount << " of hit points\n";
}
