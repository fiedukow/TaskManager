#pragma once
#include "Observer.hpp"
#include "Population.hpp"
#include <iostream>


class PodgladPostepu : public evol::NewGenerationObserver
{
    void update( evol::Population& population );
}; 

