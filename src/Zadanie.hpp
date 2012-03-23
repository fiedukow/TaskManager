#ifndef _ZADANIE_HPP_
#define _ZADANIE_HPP_

#include "Population.hpp"
#include "Chromosome.hpp"
#include "EvolFunctions.hpp"
#include "EvolException.hpp"
#include <cmath>
#include <iostream>
#include "Observer.hpp"

#define NOT_CONNECTED -1

using namespace evol;

class Zadanie;
typedef std::shared_ptr< Zadanie > ZadaniePtr;
class Zadanie : public Chromosome
{
    int idSelf;
    int maszyna;
    public:
    Zadanie ( int selfid );
    Zadanie ( int selfid, int maszyna_ );
    Zadanie ( const Zadanie* toCopy );
    
    int getSelfId();
    int getMaszyna();
    virtual ChromosomePtr crossWith( ChromosomePtr toCross ) const;
    virtual void mutate( );
};
#endif
