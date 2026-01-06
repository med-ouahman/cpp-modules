#pragma once

#include <iostream>
#include <exception>

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
            const char* what( void );
    };
    class GradeTooHighException: public std::exception {
        public:
            GradeTooHighException();
            const char* what( void );
    };
    ~Bureaucrat();
    Bureaucrat( const Bureaucrat& other );
    Bureaucrat& operator=( const Bureaucrat& other );
    Bureaucrat( std::string name, int grade );
    std::string const getName( void );
    int getGrade( void );
    void incrementGrade( void );
    void decrementGrade( void );
};

std::ostream& operator<<(std::ostream& s, Bureaucrat& b);