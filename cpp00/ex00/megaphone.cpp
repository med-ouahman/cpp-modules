#include <iostream>
#include <cstring>

void printUpper(std::string str) {
    char c;

    for (int i = 0; str[i]; ++i) {
        c = toupper(str[i]);
        std::cout << c;
    }
}

int main(int ac, char **av) {
 
    if (ac == 1) {
        printUpper((char *)" * loud and unbearable feedback noise! *\n");
        return 0;
    }
    for (int i = 1; i < ac; i++) {
        printUpper(av[i]);
        if (i < ac - 1)
            std::cout << " ";
    }
    std::cout << std::endl;
    return 0;
}