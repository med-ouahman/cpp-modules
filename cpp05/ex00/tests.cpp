#include "Bureaucrat.hpp"
#include <iostream>

static void printSeparator(const std::string& title)
{
    std::cout << "\n=== " << title << " ===" << std::endl;
}

int main()
{
    printSeparator("TEST 1: Valid construction at boundaries");
    try {
        Bureaucrat top("TopDog", 1);
        Bureaucrat bot("BottomDog", 150);
        std::cout << top << std::endl;
        std::cout << bot  << std::endl;
    }
    catch (std::exception& e) { std::cerr << "UNEXPECTED: " << e.what() << std::endl; }
    // EXPECTED:
    // TopDog, bureaucrat grade 1.
    // BottomDog, bureaucrat grade 150.

    printSeparator("TEST 2: Grade too high (0)");
    try {
        Bureaucrat bad("GodMode", 0);
        std::cout << "FAIL — should have thrown" << std::endl;
    }
    catch (Bureaucrat::GradeTooHighException& e) {
        std::cout << "Caught GradeTooHighException: " << e.what() << std::endl;
    }
    // EXPECTED:
    // Caught GradeTooHighException: Grade is too high (minimum is 1)

    printSeparator("TEST 3: Grade too low (151)");
    try {
        Bureaucrat bad("Nobody", 151);
        std::cout << "FAIL — should have thrown" << std::endl;
    }
    catch (Bureaucrat::GradeTooLowException& e) {
        std::cout << "Caught GradeTooLowException: " << e.what() << std::endl;
    }
    // EXPECTED:
    // Caught GradeTooLowException: Grade is too low (maximum is 150)

    printSeparator("TEST 4: incrementGrade — grade goes from 3 to 2");
    try {
        Bureaucrat b("Alice", 3);
        std::cout << "Before: " << b << std::endl;
        b.incrementGrade();
        std::cout << "After:  " << b << std::endl;
    }
    catch (std::exception& e) { std::cerr << "UNEXPECTED: " << e.what() << std::endl; }
    // EXPECTED:
    // Before: Alice, bureaucrat grade 3.
    // After:  Alice, bureaucrat grade 2.

    printSeparator("TEST 5: incrementGrade at grade 1 throws");
    try {
        Bureaucrat b("MaxRank", 1);
        b.incrementGrade();
        std::cout << "FAIL — should have thrown" << std::endl;
    }
    catch (Bureaucrat::GradeTooHighException& e) {
        std::cout << "Caught GradeTooHighException: " << e.what() << std::endl;
    }
    // EXPECTED:
    // Caught GradeTooHighException: Grade is too high (minimum is 1)

    printSeparator("TEST 6: decrementGrade — grade goes from 148 to 149");
    try {
        Bureaucrat b("Bob", 148);
        std::cout << "Before: " << b << std::endl;
        b.decrementGrade();
        std::cout << "After:  " << b << std::endl;
    }
    catch (std::exception& e) { std::cerr << "UNEXPECTED: " << e.what() << std::endl; }
    // EXPECTED:
    // Before: Bob, bureaucrat grade 148.
    // After:  Bob, bureaucrat grade 149.

    printSeparator("TEST 7: decrementGrade at grade 150 throws");
    try {
        Bureaucrat b("MinRank", 150);
        b.decrementGrade();
        std::cout << "FAIL — should have thrown" << std::endl;
    }
    catch (Bureaucrat::GradeTooLowException& e) {
        std::cout << "Caught GradeTooLowException: " << e.what() << std::endl;
    }
    // EXPECTED:
    // Caught GradeTooLowException: Grade is too low (maximum is 150)

    printSeparator("TEST 8: Copy constructor — independent copies");
    try {
        Bureaucrat original("Original", 50);
        Bureaucrat copy(original);
        copy.incrementGrade();
        std::cout << "Original: " << original << std::endl;
        std::cout << "Copy:     " << copy     << std::endl;
    }
    catch (std::exception& e) { std::cerr << "UNEXPECTED: " << e.what() << std::endl; }
    // EXPECTED:
    // Original: Original, bureaucrat grade 50.
    // Copy:     Original, bureaucrat grade 49.

    printSeparator("TEST 9: catch as std::exception (polymorphic catch)");
    try {
        Bureaucrat bad("Bad", 0);
    }
    catch (std::exception& e) {
        std::cout << "Caught via std::exception&: " << e.what() << std::endl;
    }
    // EXPECTED:
    // Caught via std::exception&: Grade is too high (minimum is 1)

    return 0;
}
