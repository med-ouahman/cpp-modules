#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form(const std::string& name, int gradeToSign, int gradeToExec)
    : _name(name),
    _signed(false),
    _gradeToSign(gradeToSign),
    _gradeToExec(gradeToExec) {

    if (_gradeToSign < 1 || _gradeToExec < 1)
        throw GradeTooHighException();
    if (_gradeToSign > 150 || _gradeToExec > 150)
        throw GradeTooLowException();
}

Form::Form(const Form& other)
    : _name(other._name),
    _signed(other._signed),
    _gradeToSign(other._gradeToSign),
    _gradeToExec(other._gradeToExec) {}

Form& Form::operator=(const Form& other) {
    if (this != &other)
        _signed = other._signed;
    return *this;
}

Form::~Form() {}

const std::string& Form::getName()        const { return _name; }
bool               Form::isSigned()       const { return _signed; }
int                Form::getGradeToSign() const { return _gradeToSign; }
int                Form::getGradeToExec() const { return _gradeToExec; }

void Form::beSigned(const Bureaucrat& b) {
    if (b.getGrade() > _gradeToSign)
        throw GradeTooLowException();
    _signed = true;
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
