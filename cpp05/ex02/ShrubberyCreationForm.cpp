#include "ShrubberyCreationForm.hpp"
#include <fstream>


static void writeASCIITree(std::ofstream& file) {
    file << "        *        \n";
    file << "       ***       \n";
    file << "      *****      \n";
    file << "     *******     \n";
    file << "    *********    \n";
    file << "   ***********   \n";
    file << "  *************  \n";
    file << "       |||       \n";
    file << "       |||       \n";
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("ShrubberyCreationForm", 145, 137), target_(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
    : AForm(other), target_(other.target_) {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other) {
    if (this != &other) {
        AForm::operator=(other);
        target_ = other.target_;
    }
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

void ShrubberyCreationForm::executeAction() const {
    std::ofstream file((target_ + "_shrubbery").c_str());

    if (!file.is_open()) throw std::runtime_error("Could not open file for writing");
    
    writeASCIITree(file);
    file << "\n";
    writeASCIITree(file);

    file.close();
}
