#include "Intern.hpp"
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include <iostream>

static void printSeparator(const std::string& title)
{
    std::cout << "\n=== " << title << " ===" << std::endl;
}

static void runForm(Intern& intern,
                    const std::string& formName,
                    const std::string& target,
                    int signerGrade)
{
    AForm* f = intern.makeForm(formName, target);
    if (!f)
        return;
    Bureaucrat b("TestBureaucrat", signerGrade);
    b.signForm(*f);
    b.executeForm(*f);
    delete f;
}

int main()
{
    Intern anyIntern;

    printSeparator("TEST 1: makeForm(\"shrubbery creation\", \"garden\")");
    runForm(anyIntern, "shrubbery creation", "garden", 137);
    // EXPECTED:
    // Intern creates shrubbery creation
    // TestBureaucrat signed ShrubberyCreationForm
    // TestBureaucrat executed ShrubberyCreationForm
    // (file garden_shrubbery is created with ASCII trees)

    printSeparator("TEST 2: makeForm(\"robotomy request\", \"Bender\")");
    runForm(anyIntern, "robotomy request", "Bender", 45);
    // EXPECTED:
    // Intern creates robotomy request
    // TestBureaucrat signed RobotomyRequestForm
    // Bzzzzzt... DRRRRRR... *drilling noises*
    // Bender has been robotomized successfully!  <-- or "robotomy failed." (random)
    // TestBureaucrat executed RobotomyRequestForm

    printSeparator("TEST 3: makeForm(\"presidential pardon\", \"Arthur Dent\")");
    runForm(anyIntern, "presidential pardon", "Arthur Dent", 5);
    // EXPECTED:
    // Intern creates presidential pardon
    // TestBureaucrat signed PresidentialPardonForm
    // Arthur Dent has been pardoned by Zaphod Beeblebrox.
    // TestBureaucrat executed PresidentialPardonForm

    printSeparator("TEST 4: Unknown form name returns NULL with error message");
    {
        AForm* f = anyIntern.makeForm("form 28C", "whoever");
        if (f) {
            std::cout << "FAIL — should have returned NULL" << std::endl;
            delete f;
        }
        else {
            std::cout << "Correctly returned NULL." << std::endl;
        }
    }
    // EXPECTED:
    // Intern error: unknown form name "form 28C"
    // Correctly returned NULL.

    printSeparator("TEST 5: Empty string form name");
    {
        AForm* f = anyIntern.makeForm("", "nobody");
        if (!f)
            std::cout << "Correctly returned NULL for empty name." << std::endl;
        else
            delete f;
    }
    // EXPECTED:
    // Intern error: unknown form name ""
    // Correctly returned NULL for empty name.

    printSeparator("TEST 6: Case sensitivity — \"Robotomy Request\" is not recognised");
    {
        AForm* f = anyIntern.makeForm("Robotomy Request", "Bender");
        if (!f)
            std::cout << "Correctly returned NULL (names are case-sensitive)." << std::endl;
        else
            delete f;
    }
    // EXPECTED:
    // Intern error: unknown form name "Robotomy Request"
    // Correctly returned NULL (names are case-sensitive).

    printSeparator("TEST 7: Multiple interns, same form name — each creates independently");
    {
        Intern intern1;
        Intern intern2;
        AForm* f1 = intern1.makeForm("presidential pardon", "Ford");
        AForm* f2 = intern2.makeForm("presidential pardon", "Trillian");
        if (f1 && f2) {
            Bureaucrat boss("Zaphod", 5);
            boss.signForm(*f1);
            boss.executeForm(*f1);
            boss.signForm(*f2);
            boss.executeForm(*f2);
        }
        delete f1;
        delete f2;
    }
    // EXPECTED:
    // Intern creates presidential pardon
    // Intern creates presidential pardon
    // Zaphod signed PresidentialPardonForm
    // Ford has been pardoned by Zaphod Beeblebrox.
    // Zaphod executed PresidentialPardonForm
    // Zaphod signed PresidentialPardonForm
    // Trillian has been pardoned by Zaphod Beeblebrox.
    // Zaphod executed PresidentialPardonForm

    printSeparator("TEST 8: Form returned is heap-allocated (delete does not crash)");
    {
        AForm* f = anyIntern.makeForm("shrubbery creation", "test");
        std::cout << "Pointer is: " << (f ? "non-null" : "null") << std::endl;
        delete f;
        std::cout << "delete succeeded — no crash." << std::endl;
    }
    // EXPECTED:
    // Intern creates shrubbery creation
    // Pointer is: non-null
    // delete succeeded — no crash.

    return 0;
}
