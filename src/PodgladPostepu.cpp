#include "PodgladPostepu.hpp"
#include "EvolFunctions.hpp"
#include "Subject.hpp"
#include "Realizacja.hpp"


PodgladPostepu::PodgladPostepu() : populationCounter(0)
{}

void PodgladPostepu::update( evol::Population& population )
{
    Realizacja* best = evol::EvolFunctions::ptr_cast<SubjectPtr, Realizacja>(
            population.getSubjects().at( population.getBestId() )
    );
    ++populationCounter;
    unsigned int current = best->getSumarycznyCzas();
    if( !bestTime || current < bestTime )
    {
        bestTime = current;
        std::cout << "Poprawil sie wynik najlepszego osobnika."<< std::endl;
        std::cout << "Obecny wynik (pokolenie nr. " << populationCounter << ") to: " << std::endl;
        best->print();
        std::cout << std::endl;
    }
    else if( populationCounter%100 == 0 )
    {
        std::cout << "Pokolenie nr. "<< populationCounter << std::endl << std::endl; 
    }
}
