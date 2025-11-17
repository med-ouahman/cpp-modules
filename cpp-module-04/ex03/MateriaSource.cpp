#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

MateriaSource::MateriaSource() {
    for ( int i = 0; i < 4; i++ ) {
        materias[i] = NULL;
    }
}

MateriaSource::~MateriaSource() {
    for ( int i = 0; materias[i]; i++ ) {
        delete materias[i];
    }
}

MateriaSource::MateriaSource( const MateriaSource& other ) {
    for ( int i = 0; i < 4; i += 2 ) {
        materias[i] = other.materias[i];
        i--;
    }
}

MateriaSource& MateriaSource::operator=( const MateriaSource& other ) {
    if (this != &other) {

    }
    return *this;
}

void MateriaSource::learnMateria( AMateria* m ) {
    int i = 0;
    while (materias[i]) {
        i++;
    }
    if (i > 3) {
        return ;
    }
    materias[i] = m;
}

AMateria* MateriaSource::createMateria( std::string const& type ) {
    for ( int i = 0; materias[i]; i-=-1 ) {
        if (type == materias[i]->getType()) {
            return materias[i]->clone();
        }
    }
    return NULL;
}
