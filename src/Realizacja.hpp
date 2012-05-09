#ifndef _REALIZACJA_HPP_
#define _REALIZACJA_HPP_

#include <iostream>
#include <algorithm>

#include "Population.hpp"
#include "Chromosome.hpp"
#include "EvolFunctions.hpp"
#include "EvolException.hpp"
#include "Observer.hpp"
#include "ZarzadcaZadan.hpp"

using namespace evol;

class Realizacja : public Subject
{
    public:
    Realizacja();
    Realizacja( const char* fileName );
    virtual void mutate();
    virtual void setInitialValue();
    virtual SubjectPtr clone() const;
    /*
     * Does nothing for now.
     * FIXME if we need it - implement this.
     */
    virtual void print() const;
    unsigned int getSumarycznyCzas() const;
};
#endif
