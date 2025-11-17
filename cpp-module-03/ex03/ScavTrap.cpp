#include "ScavTrap.hpp"

ScavTrap::ScavTrap() {
    std::cout << "ScavTrap Default constructor called\n";
}

ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap Destructor called\n";
}

ScavTrap& ScavTrap::operator=( const ScavTrap& other ) {
    std::cout << "ScavTrap copy assignment operator called\n";
    if (this != &other) {
        this->name = other.name;
        hitPoints = other.hitPoints;
        energy = other.energy;
        attackDamage = other.attackDamage;
    }
    return *this;
}

ScavTrap::ScavTrap( const ScavTrap& other ): ClapTrap(other) {
    std::cout << "ScavTrap copy constructor called\n";
    this->name = other.name;
    hitPoints = other.hitPoints;
    energy = other.energy;
    attackDamage = other.attackDamage;
}

ScavTrap::ScavTrap( const std::string name ) {
    std::cout << "ScavTrap name init constructor called\n";
    this->name = name;
    hitPoints = 100;
    energy = 50;
    attackDamage = 20;
}

void ScavTrap::attack( std::string& target ) {
    if (energy == 0 || hitPoints == 0) {
        return ;
    }
    energy--;
    std::cout << "ScavTrap " << name << " attacks " << target << " causing " << attackDamage << " of damage\n"; 
}

void ScavTrap::guardGate( void ) {
    std::cout << "ScavTrap " << name << " is now guarding the gate\n";
}
