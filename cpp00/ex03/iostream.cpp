#include <iostream>

#include <stdarg.h>

class Player {

public:
    static int playerCount;
    
    int x, y;
    int speed;

    void displayData() {
        std::cout << this->x << " " << this->y << " " << this->speed << std::endl;
    }

    int changeCoordinates(int newX, int newY) {
        x = newX;
        y = newY;
        return 0;
    }

    Player() {
        Player::playerCount++;
    }

    Player(int defX, int defY) {
        x = defX;
        y = defY;
    }
    
    static int getPlayerCount() {
        return Player::playerCount;
    }
};

int Player::playerCount = 0;
void free(void *__ptr);
int main() {
    Player *player = new Player();
    player->x = 0;
    player->y = 0;
    player->speed = 1.0;
    player->changeCoordinates(10, 104);
    player->displayData();
    std::cout << Player::getPlayerCount() << std::endl;
    delete player;
    player = new Player(1, 5);
    free(player);
    return 0;
}

