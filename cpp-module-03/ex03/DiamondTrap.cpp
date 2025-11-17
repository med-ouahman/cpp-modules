#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() {

}

DiamondTrap::~DiamondTrap() {

}

DiamondTrap::DiamondTrap( std::string name ): ScavTrap(name), FragTrap(name) {
    this->name = name;
    ClapTrap::name = name + "_clap_name";
    hitPoints = FragTrap::hitPoints;
    energy = ScavTrap::energy;
    attackDamage = FragTrap::attackDamage;
}

DiamondTrap::DiamondTrap( const DiamondTrap& other ) {
    name = other.name;
    energy = other.energy;
    hitPoints = other.hitPoints;
    attackDamage = other.attackDamage;
}

DiamondTrap& DiamondTrap::operator=( const DiamondTrap& other ) {
    if (this != &other) {
        name = other.name;
        hitPoints = other.hitPoints;
        energy = other.energy;
    }
    return *this;
}

void DiamondTrap::attack( std::string& target ) {
    ScavTrap::attack(target);
}

void DiamondTrap::whoAmI( void ) {
    std::cout << name << std::endl << ClapTrap::name << std::endl;
}
