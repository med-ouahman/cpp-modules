#include "Form.hpp"

Form::Form( std::string name, int signGrade, int executeGrade ): name(name), signGrade(signGrade), executeGrade(executeGrade) {
    isSigned = false;
    if (signGrade < GRADE_MAX || executeGrade < GRADE_MAX ) {
        throw Bureaucrat::GradeTooHighException();
    }
    if (signGrade > GRADE_MIN || executeGrade > GRADE_MIN ) {
        throw Bureaucrat::GradeTooLowException();
    }
}


Form::Form( const Form& form ): name(form.name), signGrade(form.signGrade), executeGrade(form.executeGrade) {
    this->isSigned = form.isSigned;
}

Form& Form::operator=( const Form& form ) {
    if (this != &form) {
        this->isSigned = form.isSigned;
    }
    return *this;
}

Form::~Form() {}

std::string const Form::getName( void ) const {
    return name;
}

int Form::getSignGrade( void ) const {
    return signGrade;
}

int Form::getExecuteGrade( void ) const{
    return executeGrade;
}

bool Form::getIsSigned( void ) const {
    return isSigned;
}

void Form::beSigned( const Bureaucrat& bur ) {

    if (bur.getGrade() > this->signGrade) {
        throw Bureaucrat::GradeTooLowException();
    }
    this->isSigned = true;
}

std::ostream& operator<<( std::ostream& os, const Form& form ) {
    os << form.getName() << form.getSignGrade() << form.getExecuteGrade() << form.getIsSigned() << std::endl;
    return os;
}
