#include "Zombie.hpp"

int main(void) {
    Zombie *zombie = newZombie("med");
    zombie->announce();
    randomChump("med");
    delete zombie;
    return 0;
}
