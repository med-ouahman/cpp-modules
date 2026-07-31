#include "Bureaucrat.hpp"
#include "AForm.hpp"

Bureaucrat::Bureaucrat(const std::string& name, int grade)
    : name_(name),
    grade_(grade) {
    if (grade_ < 1)
        throw GradeTooHighException();
    if (grade_ > 150)
        throw GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat& other)
    : name_(other.name_), grade_(other.grade_) {}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
    if (this != &other)
        grade_ = other.grade_;
    return *this;
}

Bureaucrat::~Bureaucrat() {}

const std::string& Bureaucrat::getName() const { return name_; }
int                Bureaucrat::getGrade() const { return grade_; }

void Bureaucrat::incrementGrade() {
    if (grade_ - 1 < 1)
        throw GradeTooHighException();
    grade_--;
}

void Bureaucrat::decrementGrade() {
    if (grade_ + 1 > 150)
        throw GradeTooLowException();
    grade_++;
}

void Bureaucrat::signForm(AForm& f) const {
    try {
        f.beSigned(*this);
        std::cout << name_ << " signed " << f.getName() << std::endl;
    }
    catch (std::exception& e) {
        std::cout << name_ << " couldn't sign " << f.getName()
                  << " because " << e.what() << std::endl;
    }
}

void Bureaucrat::executeForm(const AForm& f) const {
    try {
        f.execute(*this);
        std::cout << name_ << " executed " << f.getName() << std::endl;
    }
    catch (std::exception& e) {
        std::cout << name_ << " couldn't execute " << f.getName()
                  << " because " << e.what() << std::endl;
    }
}

const char* Bureaucrat::GradeTooHighException::what() const throw() {
    return "Grade is too high (minimum is 1)";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
    return "Grade is too low (maximum is 150)";
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b) {
    os << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
    return os;
}

