#include "Realizacja.hpp"
#include "Zadanie.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

void Realizacja::mutate()
{
        std::vector< ChromosomePtr >::iterator iter = chromosomes.begin();
        std::vector< ChromosomePtr >::const_iterator endIterator = chromosomes.end();
        for(;iter != endIterator;++iter)
        {
            /*
             * We don't want to swap with ourself, so we have to random 
             * range one lower than we have chromosomes.
             * If we get chromosome at position higher or equal our position, we have to add 1
             */
            unsigned int chromosomeToSwap = EvolFunctions::random(0,chromosomes.size()-2);
            if(chromosomeToSwap>=(endIterator-iter-1))
            {
                ++chromosomeToSwap;
            }
            std::swap(*iter,chromosomes.at(chromosomeToSwap));
        }       
}

void Realizacja::setInitialValue()
{
        clearChromosomes();
        ZarzadcaZadan &zarzadcaZadan = ZarzadcaZadan::getInstance();
        unsigned int iloscMaszyn = zarzadcaZadan.getIloscMaszyn();
        unsigned int iloscZadan = zarzadcaZadan.getIloscZadan();
        for(unsigned int i = 0;i<iloscZadan;++i)
        {        
                addChromosome( ChromosomePtr(new Zadanie(i,EvolFunctions::random(0,iloscMaszyn-1))) );
        }
}

SubjectPtr Realizacja::clone() const
{
        SubjectPtr nowaRealizacja = SubjectPtr(new Realizacja());
        for( auto iter : chromosomes )
        {
            Zadanie *biezaceZadanie = EvolFunctions::ptr_cast<ChromosomePtr,Zadanie>( iter );
            ChromosomePtr zadanie = ChromosomePtr( new Zadanie( biezaceZadanie ) );
            nowaRealizacja->addChromosome(zadanie);
        }
        return nowaRealizacja;
}
/*
 * Does nothing for now.
 * TODO if we need it - implement this.
 */
void Realizacja::print() const
{
    std::cout << "Przydzial zadan do maszyn:" << std::endl ;
    std::cout << "==================================" << std::endl;
    std::cout << "==    ZADANIE   ==    MASZYNA   ==" << std::endl;
    std::cout << "==================================" << std::endl;

    for( auto iter : chromosomes )
    {
        Zadanie *przydzial = EvolFunctions::ptr_cast<ChromosomePtr, Zadanie>(iter);
        std::cout << "==\t" << przydzial->getSelfId() << "\t==\t" << przydzial->getMaszyna();
        std::cout << "\t==" << std::endl;    
    }     

    std::cout << "==================================" << std::endl;
    std::cout << "CZAS WYKONANIA: " << getSumarycznyCzas() << std::endl << std::endl;

    return;
}

unsigned int Realizacja::getSumarycznyCzas() const
{
    ZarzadcaZadan &zarzadcaZadan = ZarzadcaZadan::getInstance();
    std::vector<unsigned int> czasy(zarzadcaZadan.getIloscMaszyn(), 0);

    Zadanie* biezaceZadanie;
    for(auto biezacyChromosom : chromosomes )
    {
        biezaceZadanie = EvolFunctions::ptr_cast<ChromosomePtr,Zadanie>(biezacyChromosom);
        czasy[biezaceZadanie->getMaszyna()] += zarzadcaZadan.czasObrobki(*biezaceZadanie);
    }
    return *std::max_element(czasy.begin(), czasy.end());
}
