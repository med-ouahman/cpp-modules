#include "Harl.hpp"

static int getLeveL(std::string level) {
    if (level == "DEBUG")
        return DEBUG;
    if (level == "INFO")
        return INFO;
    if (level == "WARNING")
        return WARNING;
    if (level == "ERROR")
        return ERROR;
    return -1;
}

int main(int ac, char **av) {
    int level = ac != 2 ?  -1 : getLeveL(av[1]);
    if (level < 0) {
        std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
        return 0;
    }
    Harl harl;
    switch (level) {
        case DEBUG:
            std::cout << "[ DEBUG ]" << std::endl;
            harl.complain("DEBUG");
        case INFO:
            std::cout << "[ INFO ]" << std::endl;
            harl.complain("INFO");
        case WARNING:
            std::cout << "[ WARNING ]" << std::endl;
            harl.complain("WARNING");
        case ERROR:
            std::cout << "[ ERROR ]" << std::endl;
            harl.complain("ERROR");
        default:
            break;
    }
    return 0;
}
