#include <iostream>

char toupper(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A');
    }
    return c;
}

void printUpper(char *string) {
     
    for (int i = 0; string[i]; ++i) {
        std::cout << toupper(string[i]);
    }
}

int main(int ac, char **av) {
 
    if (ac == 1) {
        printUpper((char *)" * loud and unbearable feedback noise! *\n");
        return 0;
    }
    for (int i = 1; i < ac; i++) {
        printUpper(av[i]);
    }
    std::cout << std::endl;
    return 0;
}