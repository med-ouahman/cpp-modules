#pragma once

#include <iostream>
#include <exception>
#include <string>

class Bureaucrat;

class Form {
public:
    Form(const std::string& name, int gradeToSign, int gradeToExec);
    Form(const Form& other);
    Form& operator=(const Form& other);
    ~Form();

    const std::string& getName()        const;
    bool               isSigned()       const;
    int                getGradeToSign() const;
    int                getGradeToExec() const;

    void beSigned(const Bureaucrat& b);

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
    bool              signed_;
    const int         signGrade_;
    const int         execGrade_;
};

std::ostream& operator<<(std::ostream& os, const Form& f);