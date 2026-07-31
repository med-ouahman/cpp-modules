#include "RobotomyRequestForm.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
    : AForm("RobotomyRequestForm", 72, 45),
    target_(target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other)
    : AForm(other),
    target_(other.target_) {}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other) {
    if (this != &other) {
        AForm::operator=(other);
        target_ = other.target_;
    }
    return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {}

void RobotomyRequestForm::executeAction() const {
    std::cout << "Bzzzzzt... DRRRRRR... *drilling noises*" << std::endl;
    std::srand(static_cast<unsigned int>(std::time(0)));
    if (std::rand() % 2)
        std::cout << target_ << " has been robotomized successfully!" << std::endl;
    else
        std::cout << target_ << ": robotomy failed." << std::endl;
}
