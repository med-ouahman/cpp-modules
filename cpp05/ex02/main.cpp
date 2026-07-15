#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main()
{
    std::cout << "--- ShrubberyCreationForm ---" << std::endl;
    try {
        Bureaucrat worker("Worker", 130);
        ShrubberyCreationForm shrubbery("garden");
        worker.signForm(shrubbery);
        worker.executeForm(shrubbery);
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n--- RobotomyRequestForm ---" << std::endl;
    try {
        Bureaucrat techie("Techie", 45);
        RobotomyRequestForm robotomy("Bender");
        techie.signForm(robotomy);
        techie.executeForm(robotomy);
        techie.executeForm(robotomy);
        techie.executeForm(robotomy);
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n--- PresidentialPardonForm ---" << std::endl;
    try {
        Bureaucrat president("Zaphod", 5);
        PresidentialPardonForm pardon("Arthur Dent");
        president.signForm(pardon);
        president.executeForm(pardon);
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n--- Execute unsigned form ---" << std::endl;
    try {
        Bureaucrat boss("Boss", 1);
        PresidentialPardonForm pardon("Marvin");
        boss.executeForm(pardon);
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n--- Execute with insufficient grade ---" << std::endl;
    try {
        Bureaucrat weak("Weak", 100);
        Bureaucrat strong("Strong", 5);
        PresidentialPardonForm pardon("Ford");
        strong.signForm(pardon);
        weak.executeForm(pardon);
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
