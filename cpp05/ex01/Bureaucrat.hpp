#pragma once

#include <iostream>
#include <exception>
#include <string>

class Form;

class Bureaucrat {
public:
    Bureaucrat(const std::string& name, int grade);
    Bureaucrat(const Bureaucrat& other);
    Bureaucrat& operator=(const Bureaucrat& other);
    ~Bureaucrat();

    const std::string& getName() const;
    int                getGrade() const;

    void incrementGrade();
    void decrementGrade();
    void signForm(Form& f) const;

    class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw();
    };

private:
    const std::string name_;
    int               grade_;
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b);
