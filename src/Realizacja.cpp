#include "Population.hpp"
#include "Chromosome.hpp"
#include "EvolFunctions.hpp"
#include "EvolException.hpp"
#include <cmath>
#include <iostream>
#include "Observer.hpp"
#include <algorithm>
#include "Zadanie.hpp"
#include "ZarzadcaZadan.hpp"

using namespace evol;

class Realizacja : public Subject
{
    protected:
    double randomMutationFactor;
    public:
    virtual void mutate()
    {
        std::vector< ChromosomePtr >::iterator iter = chromosomes.begin();
        std::vector< ChromosomePtr >::const_iterator endIterator = chromosomes.end();
        for(;iter != endIterator;++iter)
        {
            /*
             * if random tells us to swap - then swap
             */
            if(EvolFunctions::random() < randomMutationFactor)
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
    }
    virtual void setInitialValue()
    {
        ZarzadcaZadan &zarzadcaZadan = ZarzadcaZadan::getInstance();
        unsigned int iloscMaszyn = zarzadcaZadan.getIloscMaszyn();
        unsigned int iloscZadan = zarzadcaZadan.getIloscZadan();
        for(unsigned int i = 0;i<iloscMaszyn;++i)
        {
            addChromosome( ChromosomePtr(new Zadanie(EvolFunctions::random(0,iloscZadan-1),i)) );
        }
    }
    virtual SubjectPtr clone() const
    {
        SubjectPtr nowaRealizacja = SubjectPtr(new Realizacja());
        std::vector< ChromosomePtr >::const_iterator iter = chromosomes.begin();
        std::vector< ChromosomePtr >::const_iterator endIterator = chromosomes.end();
        for(;iter != endIterator;++iter)
        {
            Zadanie *biezaceZadanie = EvolFunctions::ptr_cast<ChromosomePtr,Zadanie>(*iter);
            ChromosomePtr zadanie = ChromosomePtr( new Zadanie( biezaceZadanie ) );
            nowaRealizacja->addChromosome(zadanie);
        }
        return nowaRealizacja;
    }
    /*
     * Does nothing for now.
     * FIXME if we need it - implement this.
     */
    virtual void print() const
    {
        return;
    }
};
