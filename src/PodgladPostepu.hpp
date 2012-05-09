#pragma once
#include <boost/optional.hpp>
#include "Observer.hpp"
#include "Population.hpp"
#include <iostream>

class PodgladPostepu : public evol::NewGenerationObserver
{
    private:
    boost::optional<unsigned int> bestTime;
    unsigned int populationCounter;
    public:
    PodgladPostepu();
    void update( evol::Population& population );
}; 

