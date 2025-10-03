#include "Zombie.hpp"

int main(void) {
    Zombie *horde = Zombie::zombieHorde(5, "Med");

    for (int i = 0; i < 5; i++) {
        horde[i].announce();
    }

    delete[] horde;
    return 0;
}
