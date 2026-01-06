#pragma once

#include <iostream>
#include "Bureaucrat.hpp"

class AForm {
private:
    std::string const name;
    bool isSigned;
    const int signGrade;
    const int executeGrade;
public:
    AForm( const AForm& form );
    ~AForm();
    AForm( std::string name, int signGrade, int executeGrade );
    AForm& operator=( const AForm& form );
    std::string const getName( void ) const;
    int getSignGrade( void ) const;
    int getExecuteGrade( void ) const;
    bool getIsSigned() const;
    void beSigned( const Bureaucrat& bur );
};


std::ostream& operator<<( const std::ostream& os, const AForm& form );