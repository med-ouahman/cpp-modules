#pragma once

#include "IMateriaSource.hpp"

class MateriaSource: public IMateriaSource {
private:
    AMateria* materias[4];
public:
    MateriaSource();
    ~MateriaSource();
    MateriaSource( const MateriaSource& other );
    MateriaSource& operator=( const MateriaSource& other );
    void learnMateria(AMateria* m);
    AMateria* createMateria( std::string const& type );
};
