#include <iostream>

#include <stdarg.h>


class Log {

    public:
        const int LogLevelInfo = 0;
        const int LogLevelWarninig = 1;
        const int LogLevelError = 2;
    private:
        int m_logLevel;
    public:
        void warn(char *msg) {
            std::cout << "Warning: " << msg << std::endl;
        }
        void error(void *errMsg) {
            std::cerr<<  "Error: " << errMsg << std::endl;

        }
};

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
    
    static int getPlayerCount() {
        return Player::playerCount;
    }
};

int Player::playerCount = 0;

int main() {
    Player *player = new Player();
    player->x = 0;
    player->y = 0;
    player->speed = 1.0;
    player->changeCoordinates(10, 104);
    player->displayData();
    std::cout << Player::getPlayerCount();
    delete player;
    return 0;
}

