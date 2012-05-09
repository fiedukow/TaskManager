#pragma once
#include "Population.hpp"
#include "Realizacja.hpp"

using namespace evol;

class CzasRealizacji : public FitnessFunction
{
    unsigned int czas;

    public:
    CzasRealizacji();
    CzasRealizacji(const int czas_);
    bool operator > ( const FitnessFunction& toCompare) const;
    bool operator == ( const FitnessFunction& toCompare) const;
    void calculate( const Subject& toCalculate );
    std::unique_ptr< FitnessFunction > clone() const;
    void print();
};
