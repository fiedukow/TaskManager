#ifndef _REALIZACJA_HPP_
#define _REALIZACJA_HPP_

#include "Population.hpp"
#include "Chromosome.hpp"
#include "EvolFunctions.hpp"
#include "EvolException.hpp"
#include <iostream>
#include "Observer.hpp"
#include <algorithm>
#include "ZarzadcaZadan.hpp"

using namespace evol;

class Realizacja : public Subject
{
    public:
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
