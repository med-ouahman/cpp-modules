#include "Weapon.hpp"

Weapon::Weapon() {
    type = "";
}

Weapon::Weapon(std::string newType) {
    type = newType;
}

Weapon::~Weapon() {

}

std::string Weapon::getType( void ) {
    return type;
}

void Weapon::setType(std::string newType) {
    type = newType;
}