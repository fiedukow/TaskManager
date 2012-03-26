#include "Realizacja.hpp"
#include "Zadanie.hpp"
#include <iostream>

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
        return;
}

unsigned int Realizacja::getSumarycznyCzas() const
{
    std::vector< ChromosomePtr >::const_iterator iter = chromosomes.begin();
    std::vector< ChromosomePtr >::const_iterator endIterator = chromosomes.end();
    ZarzadcaZadan &zarzadcaZadan = ZarzadcaZadan::getInstance();
    unsigned int czas = 0;
    for(;iter!=endIterator;++iter)
    {
        Zadanie *biezaceZadanie = EvolFunctions::ptr_cast<ChromosomePtr,Zadanie>(*iter);
        czas += zarzadcaZadan.czasObrobki(*biezaceZadanie);
//        biezaceZadanie->
//        FIXME get time of task execution and sum it up
    }
    return czas;
}
