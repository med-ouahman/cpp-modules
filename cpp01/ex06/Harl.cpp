#include "Harl.hpp"

void Harl::debug(void) {
    std::cout << "I " << std::endl;
}

void Harl::error(void) {
    std::cout << "am " << std::endl;
}

void Harl::info(void) {
     std::cout << "har" << std::endl;
}

void Harl::warning(void) {
    std::cout << "l." << std::endl;
}

void Harl::complain(std::string level) {
    // return_type (ClassName::*pointer_name)(argument_types) = &ClassName::member_function;

    void (Harl::*msgFunc)(void);

    if (level == "DEBUG")
        msgFunc = &Harl::debug;
    if (level == "WARNING")
        msgFunc = &Harl::warning;
    if (level == "ERROR")
        msgFunc = &Harl::error;
    if (level == "INFO")
        msgFunc = &Harl::info;
    (this->*msgFunc)();
}
