#include "PodgladPostepu.hpp"
#include "EvolFunctions.hpp"
#include "Subject.hpp"
#include "Realizacja.hpp"

void PodgladPostepu::update( evol::Population& population )
{
    Realizacja* best = evol::EvolFunctions::ptr_cast<SubjectPtr, Realizacja>(
            population.getSubjects().at( population.getBestId() )
    );
    unsigned int current = best->getSumarycznyCzas();
    if( current < bestTime )
    {
        bestTime = current;
        std::cout << "Poprawil sie wynik najlepszego osobnika."<< std::endl;
        std::cout << "Obecny wynik to: " << std::endl;
        best->print();
        std::cout << std::endl;
    }
}
