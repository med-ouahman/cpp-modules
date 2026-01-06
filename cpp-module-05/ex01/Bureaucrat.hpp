#pragma once

#include <iostream>
#include <exception>

class Form;

#define GRADE_MAX 1
#define GRADE_MIN 150

class Bureaucrat {

private:
    std::string const name;
    int grade;
public:
    class GradeTooLowException: public std::exception {
        public:
            GradeTooLowException();
    };
    class GradeTooHighException: public std::exception {
        public:
            GradeTooHighException();
    };
    ~Bureaucrat();
     Bureaucrat( const Bureaucrat& other );
     Bureaucrat& operator=( const Bureaucrat& other );
    Bureaucrat( std::string name, int grade );
    std::string const getName( void );
    int getGrade( void ) const;
    void incrementGrade( void );
    void decrementGrade( void );
    void signForm( Form& form ) const;
};

std::ostream& operator<<(std::ostream& s, Bureaucrat& b);
