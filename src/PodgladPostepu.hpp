#pragma once
#include "Observer.hpp"
#include "Population.hpp"
#include <iostream>


class PodgladPostepu : public evol::NewGenerationObserver
{
    private:
    unsigned int bestTime;
    unsigned int populationCounter;
    public:
    PodgladPostepu();
    void update( evol::Population& population );
}; 

