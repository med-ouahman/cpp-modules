#pragma once

#include <iostream>

# define NUM_IDEAS 100

class Brain {

public:
    Brain();
    ~Brain();
    Brain( const Brain& brain );
    Brain& operator=( const Brain& brain );
private:
    std::string ideas[NUM_IDEAS];
};
