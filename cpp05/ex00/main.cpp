#include "Bureaucrat.hpp"
#include <iostream>

int main()
{
    std::cout << "--- Valid construction ---" << std::endl;
    try {
        Bureaucrat alice("Alice", 1);
        Bureaucrat bob("Bob", 150);
        std::cout << alice << std::endl;
        std::cout << bob  << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n--- Grade too high ---" << std::endl;
    try {
        Bureaucrat bad("Bad", 0);
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n--- Grade too low ---" << std::endl;
    try {
        Bureaucrat bad("Bad", 151);
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n--- Increment / decrement ---" << std::endl;
    try {
        Bureaucrat c("Charlie", 3);
        std::cout << c << std::endl;
        c.incrementGrade();
        std::cout << "After increment: " << c << std::endl;
        c.decrementGrade();
        c.decrementGrade();
        std::cout << "After 2 decrements: " << c << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n--- Overflow increment ---" << std::endl;
    try {
        Bureaucrat top("Top", 1);
        top.incrementGrade();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n--- Overflow decrement ---" << std::endl;
    try {
        Bureaucrat bot("Bot", 150);
        bot.decrementGrade();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
