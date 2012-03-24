#include "Population.hpp"
#include "Chromosome.hpp"
#include "EvolFunctions.hpp"
#include "EvolException.hpp"
#include <cmath>
#include <iostream>
#include "Observer.hpp"
#include "Zadanie.hpp"

#define NOT_CONNECTED -1

using namespace evol;

Zadanie::Zadanie ( int selfid ) : idSelf (selfid), maszyna(NOT_CONNECTED)
{}
Zadanie::Zadanie ( int selfid, int maszyna_ ) : idSelf (selfid), maszyna( maszyna_ ) 
{}
Zadanie::Zadanie ( const Zadanie* toCopy )
{
        this->idSelf = toCopy->idSelf;
        this->maszyna = toCopy->maszyna;
}

ChromosomePtr Zadanie::crossWith( ChromosomePtr toCross ) const
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

int Zadanie::getSelfId() const
{
        return idSelf;
}

int Zadanie::getMaszyna() const
{
        return maszyna;
}

/*we cant mutate chromosome without knowing anything about whole Subject*/
void Zadanie::mutate( )  
{ return; }
