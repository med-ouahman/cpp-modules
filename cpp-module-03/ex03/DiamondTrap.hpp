#ifndef DIAMONDTRAP_HPP
#define DIOMANDTRAPP_HPP

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

class DiamondTrap: public ScavTrap, public FragTrap {
private:
    std::string name;
public:
    DiamondTrap();
    DiamondTrap( const DiamondTrap& other );
    DiamondTrap& operator=( const DiamondTrap& other );
    DiamondTrap( std::string name );
    void attack( std::string& target );
    void whoAmI( void );
    ~DiamondTrap();
};


#endif