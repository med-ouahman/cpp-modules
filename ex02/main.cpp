#include "Bureaucrat.hpp"

#include "Form.hpp"

int main( void ) {
    
    try {
        Bureaucrat b("med", 20);
        Form f("Fd-form-895Db", 100, 50);
        b.signForm(f);
    } catch(Bureaucrat::GradeTooHighException& s) {
        std::cout << "Grade too high\n";
    } catch(Bureaucrat::GradeTooLowException& s) {

        std::cout << "Grade too low\n";
    }

    return 0;
}
