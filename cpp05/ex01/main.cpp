#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main()
{
    std::cout << "--- Valid form construction ---" << std::endl;
    try {
        Form f("TaxForm", 50, 25);
        std::cout << f << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n--- Form grade too high ---" << std::endl;
    try {
        Form bad("Bad", 0, 10);
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n--- Signing: bureaucrat high enough ---" << std::endl;
    try {
        Bureaucrat alice("Alice", 45);
        Form f("TaxForm", 50, 25);
        alice.signForm(f);
        std::cout << f << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n--- Signing: bureaucrat NOT high enough ---" << std::endl;
    try {
        Bureaucrat bob("Bob", 100);
        Form f("TaxForm", 50, 25);
        bob.signForm(f);
        std::cout << f << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
