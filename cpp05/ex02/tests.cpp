#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
#include <fstream>

static void printSeparator(const std::string& title)
{
    std::cout << "\n=== " << title << " ===" << std::endl;
}

static void printFile(const std::string& filename)
{
    std::ifstream f(filename.c_str());
    if (!f.is_open()) {
        std::cerr << "Could not open: " << filename << std::endl;
        return;
    }
    std::cout << "--- Contents of " << filename << " ---" << std::endl;
    std::cout << f.rdbuf();
}

int main()
{
    printSeparator("TEST 1: ShrubberyCreationForm — sign and execute");
    try {
        Bureaucrat worker("Gardener", 137);
        ShrubberyCreationForm f("yard");
        worker.signForm(f);
        worker.executeForm(f);
        printFile("yard_shrubbery");
    }
    catch (std::exception& e) { std::cerr << "UNEXPECTED: " << e.what() << std::endl; }
    // EXPECTED:
    // Gardener signed ShrubberyCreationForm
    // Gardener executed ShrubberyCreationForm
    // --- Contents of yard_shrubbery ---
    // (ASCII tree art)

    printSeparator("TEST 2: ShrubberyCreationForm — grade too low to sign");
    try {
        Bureaucrat weak("WeakWorker", 146);
        ShrubberyCreationForm f("park");
        weak.signForm(f);
    }
    catch (std::exception& e) { std::cerr << "UNEXPECTED: " << e.what() << std::endl; }
    // EXPECTED:
    // WeakWorker couldn't sign ShrubberyCreationForm because Form grade is too low (maximum is 150)

    printSeparator("TEST 3: Execute unsigned form throws FormNotSignedException");
    try {
        Bureaucrat boss("Boss", 1);
        PresidentialPardonForm f("Someone");
        boss.executeForm(f);
    }
    catch (std::exception& e) { std::cerr << "UNEXPECTED: " << e.what() << std::endl; }
    // EXPECTED:
    // Boss couldn't execute PresidentialPardonForm because Form is not signed

    printSeparator("TEST 4: Execute with grade too low throws GradeTooLowException");
    try {
        Bureaucrat signer("Signer", 5);
        Bureaucrat runner("Runner", 100);
        PresidentialPardonForm f("Arthur Dent");
        signer.signForm(f);
        runner.executeForm(f);
    }
    catch (std::exception& e) { std::cerr << "UNEXPECTED: " << e.what() << std::endl; }
    // EXPECTED:
    // Signer signed PresidentialPardonForm
    // Runner couldn't execute PresidentialPardonForm because Form grade is too low (maximum is 150)

    printSeparator("TEST 5: RobotomyRequestForm — 3 attempts (randomised output)");
    try {
        Bureaucrat techie("Techie", 45);
        RobotomyRequestForm f("Bender");
        techie.signForm(f);
        techie.executeForm(f);
        techie.executeForm(f);
        techie.executeForm(f);
    }
    catch (std::exception& e) { std::cerr << "UNEXPECTED: " << e.what() << std::endl; }
    // EXPECTED:
    // Techie signed RobotomyRequestForm
    // Bzzzzzt... DRRRRRR... *drilling noises*
    // Bender has been robotomized successfully!  <-- or "robotomy failed." (random)
    // Techie executed RobotomyRequestForm
    // (repeats twice more)

    printSeparator("TEST 6: PresidentialPardonForm — full happy path");
    try {
        Bureaucrat president("Zaphod", 5);
        PresidentialPardonForm f("Ford Prefect");
        president.signForm(f);
        president.executeForm(f);
    }
    catch (std::exception& e) { std::cerr << "UNEXPECTED: " << e.what() << std::endl; }
    // EXPECTED:
    // Zaphod signed PresidentialPardonForm
    // Ford Prefect has been pardoned by Zaphod Beeblebrox.
    // Zaphod executed PresidentialPardonForm

    printSeparator("TEST 7: Polymorphism — AForm pointer to concrete type");
    try {
        AForm* f = new PresidentialPardonForm("Marvin");
        Bureaucrat b("Zaphod", 5);
        b.signForm(*f);
        b.executeForm(*f);
        delete f;
    }
    catch (std::exception& e) { std::cerr << "UNEXPECTED: " << e.what() << std::endl; }
    // EXPECTED:
    // Zaphod signed PresidentialPardonForm
    // Marvin has been pardoned by Zaphod Beeblebrox.
    // Zaphod executed PresidentialPardonForm

    printSeparator("TEST 8: Grade exactly at exec boundary (grade 5, exec 5)");
    try {
        Bureaucrat b("Boundary", 5);
        PresidentialPardonForm f("Test");
        b.signForm(f);
        b.executeForm(f);
    }
    catch (std::exception& e) { std::cerr << "UNEXPECTED: " << e.what() << std::endl; }
    // EXPECTED:
    // Boundary signed PresidentialPardonForm
    // Test has been pardoned by Zaphod Beeblebrox.
    // Boundary executed PresidentialPardonForm

    return 0;
}
