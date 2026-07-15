#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

static void printSeparator(const std::string& title)
{
    std::cout << "\n=== " << title << " ===" << std::endl;
}

int main()
{
    printSeparator("TEST 1: Valid form construction and operator<<");
    try {
        Form f("TaxReturn", 50, 25);
        std::cout << f << std::endl;
    }
    catch (std::exception& e) { std::cerr << "UNEXPECTED: " << e.what() << std::endl; }
    // EXPECTED:
    // Form: TaxReturn | Signed: no | Grade to sign: 50 | Grade to execute: 25

    printSeparator("TEST 2: Form grade too high (sign grade = 0)");
    try {
        Form f("BadForm", 0, 10);
        std::cout << "FAIL — should have thrown" << std::endl;
    }
    catch (Form::GradeTooHighException& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }
    // EXPECTED:
    // Caught: Form grade is too high (minimum is 1)

    printSeparator("TEST 3: Form grade too low (exec grade = 151)");
    try {
        Form f("BadForm", 10, 151);
        std::cout << "FAIL — should have thrown" << std::endl;
    }
    catch (Form::GradeTooLowException& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }
    // EXPECTED:
    // Caught: Form grade is too low (maximum is 150)

    printSeparator("TEST 4: Bureaucrat high enough to sign");
    try {
        Bureaucrat alice("Alice", 45);
        Form f("TaxReturn", 50, 25);
        alice.signForm(f);
        std::cout << f << std::endl;
    }
    catch (std::exception& e) { std::cerr << "UNEXPECTED: " << e.what() << std::endl; }
    // EXPECTED:
    // Alice signed TaxReturn
    // Form: TaxReturn | Signed: yes | Grade to sign: 50 | Grade to execute: 25

    printSeparator("TEST 5: Bureaucrat exactly at required grade (boundary)");
    try {
        Bureaucrat alice("Alice", 50);
        Form f("TaxReturn", 50, 25);
        alice.signForm(f);
        std::cout << f << std::endl;
    }
    catch (std::exception& e) { std::cerr << "UNEXPECTED: " << e.what() << std::endl; }
    // EXPECTED:
    // Alice signed TaxReturn
    // Form: TaxReturn | Signed: yes | Grade to sign: 50 | Grade to execute: 25

    printSeparator("TEST 6: Bureaucrat NOT high enough to sign");
    try {
        Bureaucrat bob("Bob", 100);
        Form f("TaxReturn", 50, 25);
        bob.signForm(f);
        std::cout << f << std::endl;
    }
    catch (std::exception& e) { std::cerr << "UNEXPECTED: " << e.what() << std::endl; }
    // EXPECTED:
    // Bob couldn't sign TaxReturn because Form grade is too low (maximum is 150)
    // Form: TaxReturn | Signed: no | Grade to sign: 50 | Grade to execute: 25

    printSeparator("TEST 7: Two bureaucrats — one signs, one cannot");
    try {
        Form f("ImportantForm", 30, 10);
        Bureaucrat weak("WeakBob", 80);
        Bureaucrat strong("StrongAlice", 10);
        weak.signForm(f);
        strong.signForm(f);
        std::cout << f << std::endl;
    }
    catch (std::exception& e) { std::cerr << "UNEXPECTED: " << e.what() << std::endl; }
    // EXPECTED:
    // WeakBob couldn't sign ImportantForm because Form grade is too low (maximum is 150)
    // StrongAlice signed ImportantForm
    // Form: ImportantForm | Signed: yes | Grade to sign: 30 | Grade to execute: 10

    printSeparator("TEST 8: beSigned throws catchable as std::exception");
    try {
        Form f("TaxReturn", 50, 25);
        Bureaucrat low("LowRank", 100);
        f.beSigned(low);
        std::cout << "FAIL — should have thrown" << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Caught via std::exception&: " << e.what() << std::endl;
    }
    // EXPECTED:
    // Caught via std::exception&: Form grade is too low (maximum is 150)

    return 0;
}
