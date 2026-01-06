#include "Bureaucrat.hpp"


int main( void ) {
    
    try {
        Bureaucrat b("med", -400);
    } catch(Bureaucrat::GradeTooHighException& e) {
       std::cout << e.what() << std::endl;
    } catch(Bureaucrat::GradeTooLowException& e) {

        std::cout << e.what() << std::endl;
    }
    return 0;
}
