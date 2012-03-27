#include "PodgladPostepu.hpp"

void PodgladPostepu::update( evol::Population& population )
{
    population.getSubjects().at( population.getBestId() )->print();
}
