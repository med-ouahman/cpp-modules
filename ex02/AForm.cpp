#include "AForm.hpp"

AForm::AForm( std::string name, int signGrade, int executeGrade ): name(name), signGrade(signGrade), executeGrade(executeGrade) {
    isSigned = false;
    if (signGrade < GRADE_MAX || executeGrade < GRADE_MAX ) {
        throw Bureaucrat::GradeTooHighException();
    }
    if (signGrade > GRADE_MIN || executeGrade > GRADE_MIN ) {
        throw Bureaucrat::GradeTooLowException();
    }
}


AForm::AForm( const AForm& form ): name(form.name), signGrade(form.signGrade), executeGrade(form.executeGrade) {
    this->isSigned = form.isSigned;
}

AForm& AForm::operator=( const AForm& AForm ) {
    if (this != &AForm) {
        this->isSigned = AForm.isSigned;
    }
    return *this;
}

AForm::~AForm() {}

std::string const AForm::getName( void ) const {
    return name;
}

int AForm::getSignGrade( void ) const {
    return signGrade;
}

int AForm::getExecuteGrade( void ) const{
    return executeGrade;
}

bool AForm::getIsSigned( void ) const {
    return isSigned;
}

void AForm::beSigned( const Bureaucrat& bur ) {

    if (bur.getGrade() > this->signGrade) {
        throw Bureaucrat::GradeTooLowException();
    }
    this->isSigned = true;
}

std::ostream& operator<<( std::ostream& os, const AForm& form ) {
    os << form.getName() << form.getSignGrade() << form.getExecuteGrade() << form.getIsSigned() << std::endl;
    return os;
}
