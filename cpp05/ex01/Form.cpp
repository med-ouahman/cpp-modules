#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form(const std::string& name, int gradeToSign, int gradeToExec)
    : name_(name),
    signed_(false),
    signGrade_(gradeToSign),
    execGrade_(gradeToExec) {

    if (signGrade_ < 1 || execGrade_ < 1)
        throw GradeTooHighException();
    if (signGrade_ > 150 || execGrade_ > 150)
        throw GradeTooLowException();
}

Form::Form(const Form& other)
    : name_(other.name_),
    signed_(other.signed_),
    signGrade_(other.signGrade_),
    execGrade_(other.execGrade_) {}

Form& Form::operator=(const Form& other) {
    
    if (this != &other)
        signed_ = other.signed_;
    return *this;
}

Form::~Form() {}

const std::string& Form::getName()        const { return name_; }

bool               Form::isSigned()       const { return signed_; }

int                Form::getGradeToSign() const { return signGrade_; }

int                Form::getGradeToExec() const { return execGrade_; }

void Form::beSigned(const Bureaucrat& b) {
    if (b.getGrade() > signGrade_)
        throw GradeTooLowException();
    signed_ = true;
}

const char* Form::GradeTooHighException::what() const throw() {
    return "Form grade is too high (minimum is 1)";
}

const char* Form::GradeTooLowException::what() const throw() {
    return "Form grade is too low (maximum is 150)";
}

std::ostream& operator<<(std::ostream& os, const Form& f) {
    os << "Form: " << f.getName()
       << " | Signed: " << (f.isSigned() ? "yes" : "no")
       << " | Grade to sign: " << f.getGradeToSign()
       << " | Grade to execute: " << f.getGradeToExec();
    return os;
}
