#ifndef HARL_H_
#define HARL_H_

#include <iostream>
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