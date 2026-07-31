#include "Intern.hpp"
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include <iostream>

int main()
{
    Intern interMilan;

    std::cout << "--- Intern creates robotomy request ---" << std::endl;
    {
        AForm* rrf = interMilan.makeForm("robotomy request", "Bender");
        if (rrf) {
            Bureaucrat boss("Boss", 45);
            boss.signForm(*rrf);
            boss.executeForm(*rrf);
            delete rrf;
        }
    }

    std::cout << "\n--- Intern creates shrubbery creation ---" << std::endl;
    {
        AForm* scf = interMilan.makeForm("shrubbery creation", "home");
        if (scf) {
            Bureaucrat gardener("Gardener", 137);
            gardener.signForm(*scf);
            gardener.executeForm(*scf);
            delete scf;
        }
    }

    std::cout << "\n--- Intern creates presidential pardon ---" << std::endl;
    {
        AForm* ppf = interMilan.makeForm("presidential pardon", "Marvin");
        if (ppf) {
            Bureaucrat president("Zaphod", 5);
            president.signForm(*ppf);
            president.executeForm(*ppf);
            delete ppf;
        }
    }

    std::cout << "\n--- Intern given unknown form name ---" << std::endl;
    {
        AForm* unknown = interMilan.makeForm("form 28C", "whoever");
        if (!unknown)
            std::cout << "No form was created." << std::endl;
    }

    return 0;
}
