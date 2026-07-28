#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

Intern::Intern() {}

Intern::Intern(const Intern&) {}

Intern& Intern::operator=(const Intern&) { return *this; }

Intern::~Intern() {}

static AForm* makeShrubbery(const std::string& target) {
    return new ShrubberyCreationForm(target);
}

static AForm* makeRobotomy(const std::string& target) {
    return new RobotomyRequestForm(target);
}

static AForm* makePardon(const std::string& target) {
    return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) const {
    typedef AForm* (*FormFactory)(const std::string&);

    static const std::string names[3] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };
    static const FormFactory factories[3] = {
        makeShrubbery,
        makeRobotomy,
        makePardon
    };

    for (int i = 0; i < 3; i++) {
        if (formName == names[i]) {
            std::cout << "Intern creates " << formName << std::endl;
            return factories[i](target);
        }
    }

    std::cerr << "Intern error: unknown form name \"" << formName << "\"" << std::endl;
    return NULL;
}
