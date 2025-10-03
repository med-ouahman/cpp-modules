#ifndef HARL_H_
#define HARL_H_

#include <iostream>

typedef enum {
    DEBUG,
    INFO,
    WARNING,
    ERROR
} logLevel;

class Harl {

private:
    void debug(void);
    void warning(void);
    void info(void);
    void error(void);
public:
    void complain(std::string level);
};

#endif