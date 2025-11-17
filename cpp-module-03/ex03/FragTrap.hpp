#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap: virtual public ClapTrap {
private:
    
public:
    FragTrap();
    ~FragTrap();
    FragTrap( const FragTrap& copy );
    FragTrap& operator=( const FragTrap& copy );
    FragTrap( const std::string name );
    void attack( std::string& target );
    void hyFiveGuys( void );
};



#endif