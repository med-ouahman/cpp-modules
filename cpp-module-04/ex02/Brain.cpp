#include "Brain.hpp"

Brain::Brain() {
    std::cout << "Default constructor called\n";
    for ( int i = 0; i < NUM_IDEAS; i++ ) {
        ideas[i] = "Some idea";
    }
}

Brain::~Brain() {
    std::cout << "Brain destructor called\n";
}

Brain::Brain( const Brain& brain ) {
    for ( int i = 0; i < NUM_IDEAS; i++ ) {
        ideas[i] = brain.ideas[i];
    }
}

Brain& Brain::operator=( const Brain& brain ) {
    if (this != &brain) {
        for ( int i = 0; i < NUM_IDEAS; i++ ) {
            ideas[i] = brain.ideas[i];
        }
    }
    return *this;
}
