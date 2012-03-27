#pragma once
#include "Observer.hpp"
#include "Population.hpp"
#include <iostream>


class PodgladPostepu : public evol::NewGenerationObserver
{
    private:
    unsigned int bestTime;
    public:
    void update( evol::Population& population );
}; 

