#ifndef CLAPTRAP_HPP__
#define CLAPTRAP_HPP__

#include <iostream>

class ClapTrap {
protected:
    std::string name;
    unsigned int hitPoints;
    unsigned int energy;
    unsigned int attackDamage;
public:
    void attack( const std::string& target );
    void takeDamage( unsigned int amount );
    void beRepaired ( unsigned int amount );
    ClapTrap();
    ClapTrap(std::string name);
    ClapTrap(const ClapTrap& copy);
    ClapTrap& operator=(const ClapTrap& copy);
    ~ClapTrap();
};

#endif