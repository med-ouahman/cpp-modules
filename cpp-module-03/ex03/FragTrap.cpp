#include "FragTrap.hpp"

FragTrap::FragTrap() {
    std::cout << "FragTrap Default constructor called" << std::endl;
}

FragTrap::~FragTrap() {
    std::cout << "FragTrap destructor called" << std::endl;
}

FragTrap::FragTrap( const FragTrap& other ) {
    std::cout << "FragTrap copy constructor called" << std::endl;
    name = other.name;
    hitPoints = other.hitPoints;
    energy = other.energy;
    attackDamage = other.attackDamage;
}

FragTrap& FragTrap::operator=( const FragTrap& other ) {
    std::cout << "FragTrap copy assignment operator called" << std::endl;
    if (this != &other) {    
        name = other.name;
        hitPoints = other.hitPoints;
        energy = other.energy;
        attackDamage = other.attackDamage;
    }
    return *this;
}

FragTrap::FragTrap( const std::string name ) {
    std::cout << "FragTrap name constructor called" << std::endl;
    this->name = name;
    hitPoints = 100;
    energy = 100;
    attackDamage = 30;
}

void FragTrap::hyFiveGuys( void ) {
    std::cout << "FragTrap " << name << ": High Five Guys!" << std::endl;
}

void FragTrap::attack( std::string& target ) {
    if (energy == 0 || hitPoints == 0) {
        return ;
    }
    energy -= 1;
    std::cout << "FragTrap " << name << " attacks " << target << " causing " << attackDamage << " of damage" << std::endl;
}
