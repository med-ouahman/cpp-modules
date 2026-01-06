#include "Bureaucrat.hpp"



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

int Bureaucrat::getGrade( void ) {
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

Bureaucrat::GradeTooLowException::GradeTooLowException() {

}

const char* Bureaucrat::GradeTooLowException::what() {
    return "grade too low";
}

Bureaucrat::GradeTooHighException::GradeTooHighException() {
    
}

const char* Bureaucrat::GradeTooHighException::what() {
    return "grade too high";
}