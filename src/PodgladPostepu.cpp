#include "PodgladPostepu.hpp"

void PodgladPostepu::update( evol::Population& population )
{
    std::cout << "HERE IS THE BEST" << std::endl;
    population.getSubjects().at( population.getBestId() )->print();
}
