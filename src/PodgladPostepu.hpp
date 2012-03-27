#pragma once
#include "Observer.hpp"
#include "Population.hpp"
#include <vector>


class PodgladPostepu : public evol::NewGenerationObserver
{
    void update( evol::Population& population );
}; 

