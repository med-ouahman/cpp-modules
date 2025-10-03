#ifndef HUMAN_A_HPP
#define HUMAN_A_HPP

#include <iostream>
#include "Weapon.hpp"

class HumanA {
private:
    Weapon& weapon;
    std::string name;
public:
    HumanA(std::string name, Weapon& weopon);
    ~HumanA();
    void attack(void);
};

#endif