#include <iostream>


class Zombie {

private:
    std::string name;
public:
    void announce(void);
    Zombie();
    Zombie(std:: string name);
    ~Zombie();
    static Zombie *zombieHorde(int N, std::string name);

};
