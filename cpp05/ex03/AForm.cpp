#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(const std::string& name, int gradeToSign, int gradeToExec)
    : name_(name),
    signed_(false),
    signGrade_(gradeToSign),
    execGrade_(gradeToExec) {
    if (signGrade_ < 1 || execGrade_ < 1)
        throw GradeTooHighException();
    if (signGrade_ > 150 || execGrade_ > 150)
        throw GradeTooLowException();
}

AForm::AForm(const AForm& other)
    : name_(other.name_), signed_(other.signed_),
      signGrade_(other.signGrade_), execGrade_(other.execGrade_) {}

AForm& AForm::operator=(const AForm& other) {
    if (this != &other)
        signed_ = other.signed_;
    return *this;
}

AForm::~AForm() {}

const std::string& AForm::getName()        const { return name_; }
bool               AForm::isSigned()       const { return signed_; }
int                AForm::getGradeToSign() const { return signGrade_; }
int                AForm::getGradeToExec() const { return execGrade_; }

void AForm::beSigned(const Bureaucrat& b) {
    if (b.getGrade() > signGrade_)
        throw GradeTooLowException();
    signed_ = true;
}

void AForm::execute(const Bureaucrat& executor) const {
    if (!signed_)
        throw FormNotSignedException();
    if (executor.getGrade() > execGrade_)
        throw GradeTooLowException();
    executeAction();
}

const char* AForm::GradeTooHighException::what() const throw() {
    return "Form grade is too high (minimum is 1)";
}

const char* AForm::GradeTooLowException::what() const throw() {
    return "Form grade is too low (maximum is 150)";
}

const char* AForm::FormNotSignedException::what() const throw() {
    return "Form is not signed";
}

std::ostream& operator<<(std::ostream& os, const AForm& f) {
    os << "Form: " << f.getName()
       << " | Signed: " << (f.isSigned() ? "yes" : "no")
       << " | Grade to sign: " << f.getGradeToSign()
       << " | Grade to execute: " << f.getGradeToExec();
    return os;
}
