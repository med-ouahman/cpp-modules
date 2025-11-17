#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : virtual public ClapTrap {

public:
    ScavTrap();
    ScavTrap(const ScavTrap& copy);
    ScavTrap& operator=(const ScavTrap& copy);
    ScavTrap(const std::string name);
    ~ScavTrap();
    void attack( std::string& target );
    void guardGate( void );
};

#endif