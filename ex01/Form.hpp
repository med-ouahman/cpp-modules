#pragma once

#include <iostream>
#include "Bureaucrat.hpp"

class Form {
private:
    std::string const name;
    bool isSigned;
    const int signGrade;
    const int executeGrade;
public:
    Form( const Form& form );
    ~Form();
    Form( std::string name, int signGrade, int executeGrade );
    Form& operator=( const Form& form );
    std::string const getName( void ) const;
    int getSignGrade( void ) const;
    int getExecuteGrade( void ) const;
    bool getIsSigned() const;
    void beSigned( const Bureaucrat& bur );
};


std::ostream& operator<<( const std::ostream& os, const Form& form );