#include "Population.hpp"
#include "Chromosome.hpp"
#include "EvolFunctions.hpp"
#include "EvolException.hpp"
#include <cmath>
#include <iostream>
#include "Observer.hpp"

#define NOT_CONNECTED -1

class Zadanie;
using namespace evol;

typedef std::shared_ptr< Zadanie > ZadaniePtr;

class Zadanie : public Chromosome
{
    int idSelf;
    int maszyna;
    public:
    Zadanie ( int selfid ) : idSelf (selfid), maszyna(NOT_CONNECTED)
    {}
    Zadanie ( int selfid, int maszyna_ ) : idSelf (selfid), maszyna( maszyna_ ) 
    {}
    Zadanie ( const Zadanie* toCopy )
    {
        this->idSelf = toCopy->idSelf;
        this->maszyna = toCopy->maszyna;
    }

    virtual ChromosomePtr crossWith( ChromosomePtr toCross ) const
    {
        if( EvolFunctions::random() > 0.5 ) 
        {
            Zadanie* toCopy = EvolFunctions::ptr_cast<ChromosomePtr, Zadanie>(toCross);  
            return ZadaniePtr( new Zadanie( toCopy ) );
        }
        else
        {
            return ZadaniePtr( new Zadanie ( this ) );
        }
    }  

    int getSelfId()
    {
        return idSelf;
    }

    int getMaszyna()
    {
        return maszyna;
    }
    
    /*we cant mutate chromosome without knowing anything about whole Subject*/
    virtual void mutate( )  
    { return; }
};
