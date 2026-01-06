#include "Bureaucrat.hpp"
#include "Form.hpp"

Bureaucrat::Bureaucrat(std::string name, int grade): name(name) {

    if (grade < GRADE_MAX) {
        throw Bureaucrat::GradeTooHighException();
    }
    if (grade > GRADE_MIN) {
        throw Bureaucrat::GradeTooLowException();
    }
    this->grade = grade;
}

Bureaucrat::~Bureaucrat() {

}

Bureaucrat::Bureaucrat( const Bureaucrat& other ): name(other.name), grade(other.grade) {}

Bureaucrat& Bureaucrat::operator=( const Bureaucrat& other ) {
	if (this != &other) {
		grade = other.grade;
	}
	return *this;
}

std::string const Bureaucrat::getName( void ) {
    return name;
}

int Bureaucrat::getGrade( void ) const {
    return grade;
}

void Bureaucrat::incrementGrade( void ) {
    if (grade == GRADE_MAX) {
        throw Bureaucrat::GradeTooHighException();
    }
    grade--;
}

void Bureaucrat::decrementGrade( void ) {
    if (grade == GRADE_MIN) {
        throw Bureaucrat::GradeTooLowException();
    }
    grade++;
}

std::ostream& operator<<(std::ostream& os, Bureaucrat& b) {
    os << b.getName() << ", bureaucrat grade " << b.getGrade() << '\n';
    return os;
}

void Bureaucrat::signForm( Form& form ) const {
    try {

        form.beSigned(*this);
    } catch(Bureaucrat::GradeTooLowException& e) {
        std::cout << this->name << " couldn't sign " << form.getName() << " because " << e.what() << '\n';
        return ;
    }
    std::cout << this->name << " signed " << form.getName() << '\n';

}

Bureaucrat::GradeTooLowException::GradeTooLowException() {

}

Bureaucrat::GradeTooHighException::GradeTooHighException() {
    
}

