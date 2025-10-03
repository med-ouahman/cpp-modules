#ifndef WEAPON_H_
#define WEAPON_H_

#include <iostream>

class Weapon {
private:
    std::string type;
public:
    Weapon();
    Weapon(std::string type);
    ~Weapon();

    std::string getType( void );

    void setType(std::string newType);
};

#endif