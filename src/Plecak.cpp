#include "debug.h"
#include "Population.hpp"
#include "Chromosome.hpp"
#include "EvolFunctions.hpp"
#include "EvolException.hpp"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <set>
#include "Observer.hpp"
#include <fstream>

#define ptrCast(typ, nazwa) ((typ*)(&(*(nazwa))))

using namespace evol;

class Przedmiot;
class Skarbiec;


typedef std::shared_ptr< Przedmiot > PrzedmiotPtr;
typedef std::unique_ptr< Skarbiec > SkarbiecUPtr;

class Przedmiot 
{
    double waga;
    int wartosc;

    public: 
    /* prosty konsturktor */
    Przedmiot( double waga, int wartosc): waga(waga), wartosc(wartosc)
    {}

    /* gettery */
    double getWaga(){ return this->waga;    }
    int getWartosc(){ return this->wartosc; }
};

class PrzedmiotComparator
{
    public:
    bool operator()( const PrzedmiotPtr first, const PrzedmiotPtr second )
    {    
        return ( first->getWaga() < second->getWaga() ||
                 (first->getWaga() == second->getWaga() && first<second ));
    }
};


class MySet : public std::set<PrzedmiotPtr, PrzedmiotComparator >
{
    public:
    PrzedmiotPtr operator[ ]( int index )
    {
        return *(getIt(index));
    }

    std::set<PrzedmiotPtr, PrzedmiotComparator>::iterator getIt( int index )
    {
        std::set<PrzedmiotPtr, PrzedmiotComparator>::iterator it = this->begin();
        for(int i = 0; i < index; ++i, ++it )
        {}
        return it;
    }
};

class CyclesCounter : public NewGenerationObserver
{
    unsigned int cycleCounter;
    constexpr static unsigned int cyclesToBeDone = 1000;

    public:

    CyclesCounter() : cycleCounter(0) {}

    void update(Population& population)
    {
        ++cycleCounter;
        std::cout << "POKOLENIE: "<< cycleCounter << std::endl;
        if(cycleCounter == CyclesCounter::cyclesToBeDone)
        {
            // przerwij dzialanie algorytmu
            population.stopLoop();
        }
    }

    unsigned int getCycleCount()
    {
        return cycleCounter;
    }
};

class ResultPrinter : public NewGenerationObserver
{
    void update(Population& population)
    {
        std::cout << "W tym pokoleniu najlepszy wynik to "<<std::endl;
        population.getSubjects().at( population.getBestId() )->print();
        population.getCurrentBestFF()->print();
        std::cout << std::endl;
    }
};

/**
 *  Skarbiec przechowuje przedmioty do wyboru
 *  Skarbiec potrafi wylosować element do wyjęcia, który ma conajwyżej zadaną wagę.
 */
class Skarbiec
{    
    /*wektor powinien być zawsze posortowany wg. wagi przedmiotu */
    MySet przedmioty;

    public:
    #define DP(waga,wartosc) this->przedmioty.insert( PrzedmiotPtr ( new Przedmiot(waga,wartosc ) ) );
    Skarbiec()
    {
        std::vector< std::pair<double,unsigned int> > data;
        try
        {
           data = *getSafeData("dane.txt");
        }
        catch(FileException &e)
        {
            std::cout << e.what() << std::endl;
            exit(1);
        }

        for( auto& entry : data )
        {
            DP(entry.first, entry.second);
        }
        /*tworzenie domyslnego sejfu (w zasadzie zawartosc statyczna
          ale mogla by byc wczytana np. z pliku lub bazy danych) */
        this->sortuj();
    }

    /*tworzy skrarbiec na bazie wektora (np. konkretnego plecaka*/
    Skarbiec( MySet przedmioty )
    {        
        this->przedmioty = przedmioty;        
        this->sortuj();
        //std::cout << "ILE: " << this->przedmioty.size() << std::endl;
    }
        
    /*wybiera losowy przedmiot spośród takiego podzbioru przedmiotów 
      w skarbcu, że waga każdego z nich jest mniejsza równa maksWaga*/
    PrzedmiotPtr wybierzLosowy( int maksWaga )
    {
        /* ustal zakres losowania */
        int i = -1;
        for( PrzedmiotPtr przedmiot : przedmioty )
        {
           if( przedmiot->getWaga() <= maksWaga )
                ++i;
           else 
                break;          
        }      
        if( i < 0 ) return PrzedmiotPtr();
//        std::cout << "Wybieram z: " << i << std::endl; 
        int wybor = EvolFunctions::random( 0, i );
//        std::cout << "Wypadlo na " << wybor << std::endl;
        PrzedmiotPtr rezultat = przedmioty[wybor];
        this->przedmioty.erase(this->przedmioty.getIt(wybor));
        return rezultat;
    }

    /*tworzy kopie skarbca*/
    std::unique_ptr<Skarbiec> clone() const 
    {
        return std::unique_ptr<Skarbiec>( new Skarbiec( this->przedmioty) );
    }

    private:
    std::shared_ptr< std::vector< std::pair<double,unsigned int> > > getSafeData(std::string filePath)
    {
        typedef std::vector< std::pair<double,unsigned int> > pairVector;

        pairVector *toReturn = new pairVector();
        std::shared_ptr< pairVector > ptrToReturn(toReturn);
        std::ifstream fh;
        fh.open(filePath, std::ios::in);
        if(fh.is_open())
        {
            while( fh.good() )
            {
                double waga = 0;
                unsigned int wartosc = 0;
                fh >> waga >> wartosc;
                toReturn->push_back(std::make_pair(waga,wartosc));
            }
            toReturn->pop_back(); // because ifstream.good() is true until we try to get data after last one from file, so we get one more element than is in file
            fh.close();
        }
        else
        {
            throw CannotOpenFileException(filePath);
        }
        return ptrToReturn;
    }
    void sortuj()
    {
        PrzedmiotComparator comparator;
        //std::sort( this->przedmioty.begin(), this->przedmioty.end(), comparator ); 
    }
};
Skarbiec SKARBIEC_OGOLNY;


class ZawartoscPlecaka : public Chromosome
{
    MySet przedmioty;
    constexpr static double udzwig = 431.0;

    public: 
    /* tworzy losowy plecak
       z przedmiotow ze skarbca   
     */
    ZawartoscPlecaka( const Skarbiec& skad )
    {
        std::unique_ptr<Skarbiec> SkarbPtr = skad.clone();
        PrzedmiotPtr przedmiot;
        /*TODO ugly code*/
        for( przedmiot = SkarbPtr->wybierzLosowy( this->pobierzPozostalaPojemnosc() ) ; 
             przedmiot != PrzedmiotPtr() ; 
             przedmiot = SkarbPtr->wybierzLosowy( this->pobierzPozostalaPojemnosc() )
            ) 
        {
            dodajDoPlecaka(przedmiot);
       }
    }

    /* ile przedmiotow jest aktualnie w plecaku*/
    int getIlePrzedmiotow( )
    {
        return this->przedmioty.size();
    }

    /* waga wszystkich przedmiotow w plecaku*/
    double getWagaSumaryczna( )
    {
        double waga = 0;
        for( auto przedmiot : przedmioty )
        {
            waga += przedmiot->getWaga();
        }
        return waga;
    }

    int getWartoscSumaryczna( )
    {
        int wartosc = 0;
        for( auto przedmiot : przedmioty )
        {
            wartosc += przedmiot->getWartosc();
        }
        return wartosc;
    }

    /* pobiera udzwig*/
    double getUdzwig()
    {
        return ZawartoscPlecaka::udzwig;
    }

    /*dodaje okreslony przedmiot do plecaka*/
    void dodajDoPlecaka( PrzedmiotPtr doDodania )
    {
        this->przedmioty.insert( doDodania );
        return;
    }

    /*krzuje dwa plecaki ze soba w taki sposob ze
      1. Wez losowy procent przedmiotow ze starego plecaka
      2. Dopoki to mozliwe losuj ze skarbca drugiego plecaka przedmiotu
      3. Dopoki to mozliwe losuj ze skarbca ogolnego przedmioty
    */
    ChromosomePtr crossWith( ChromosomePtr toCross ) const
    {
        double randomFactor = EvolFunctions::random();
        std::shared_ptr< ZawartoscPlecaka > nowaZawartoscPlecaka( new ZawartoscPlecaka() );

        {
                SkarbiecUPtr biezacySkarbiec ( new Skarbiec(this->przedmioty) );
                // wez wylosowana ilosc przedmiotow ze starego plecaka
                for(unsigned int i = 0;i<randomFactor*przedmioty.size();++i)
                {
                    PrzedmiotPtr wybranyPrzedmiot;
                    int pojemnosc = nowaZawartoscPlecaka->pobierzPozostalaPojemnosc();
                    wybranyPrzedmiot = biezacySkarbiec->wybierzLosowy( pojemnosc );
                                        
                    if(wybranyPrzedmiot == NULL)
                        break;
                    else
                        ptrCast(ZawartoscPlecaka,nowaZawartoscPlecaka)->dodajDoPlecaka(wybranyPrzedmiot);
                }
        }

        // dopoki to mozliwe, losuj ze skarbca drugiego plecaka przedmiotu
        {
                std::unique_ptr<Skarbiec> drugiePrzedmiotyPtr( new Skarbiec(ptrCast(ZawartoscPlecaka,toCross)->przedmioty) );
                PrzedmiotPtr przedmiot;
                while( (przedmiot = drugiePrzedmiotyPtr->wybierzLosowy( ptrCast(ZawartoscPlecaka,nowaZawartoscPlecaka)->pobierzPozostalaPojemnosc() )) != NULL )
                {
                    ptrCast(ZawartoscPlecaka,nowaZawartoscPlecaka)->dodajDoPlecaka(przedmiot);
                }
        }
        {
            std::unique_ptr<Skarbiec> cloneOfSkarbiec = SKARBIEC_OGOLNY.clone();
            PrzedmiotPtr przedmiot;
            while( (przedmiot = cloneOfSkarbiec->wybierzLosowy( ptrCast(ZawartoscPlecaka,nowaZawartoscPlecaka)->pobierzPozostalaPojemnosc() ) ) != NULL)
            {
                ptrCast(ZawartoscPlecaka,nowaZawartoscPlecaka)->dodajDoPlecaka(przedmiot);
            }
        }
        return ChromosomePtr(nowaZawartoscPlecaka);

    }
    
    /* mutuje plecak w taki sposob ze
       1. Zabierz z plecaka jeden losowy przedmiot
       2. Dopoki to mozliwie losuj ze skarbca ogolnego nowe przedmioty   
     */
    void mutate( )
    {
        if(this->przedmioty.size() == 0)
            return;
        /* usuwamy podana ilosc przedmiotow - zmien dla zwiekszenia stopnia mutacji */
        for(unsigned int i = 0; i<1; ++i)
        {
            unsigned int randomIndex = EvolFunctions::random()*(this->przedmioty.size()-1);
            this->przedmioty.erase(this->przedmioty.getIt(randomIndex));
        }
        /* dodajemy tyle przedmiotow ze skarbca glownego ile sie da na miejsce usunietych */
        std::unique_ptr<Skarbiec> cloneOfSkarbiec = SKARBIEC_OGOLNY.clone();
        PrzedmiotPtr przedmiot;

        while( (przedmiot = cloneOfSkarbiec->wybierzLosowy( this->pobierzPozostalaPojemnosc() )) != NULL )
        {
            this->dodajDoPlecaka(przedmiot);
        } 
    }

    /*wykonuje kopie chromosomu*/ 
    ChromosomePtr clone( ) const
    {
        ChromosomePtr toReturn( new ZawartoscPlecaka() );
        for( auto entry : this->przedmioty )
        {
            EvolFunctions::ptr_cast<ChromosomePtr, ZawartoscPlecaka>(toReturn)->dodajDoPlecaka( entry );
        }

        return toReturn;
    }

    void print()
    {
        std::cout << "W plecaku znajduje sie " << this->przedmioty.size() << ": " << std::endl;
        for( PrzedmiotPtr entry : this->przedmioty )
            std::cout << entry << ": " << entry->getWaga() << "kg. " << entry->getWartosc() << "$" << std::endl ;
        std::cout << "Suma wag " << this->getWagaSumaryczna() << "\t";
        std::cout << "Suma wartosci " << this->getWartoscSumaryczna() <<std::endl;
    }

    private:
    ZawartoscPlecaka()
    {}

    int pobierzPozostalaPojemnosc()
    {
        return ZawartoscPlecaka::udzwig - this->getWagaSumaryczna();
    }

};



class Plecak : public Subject
{
    public:
    
    /*tworzy plecak wypelniony losowa choc dopuszczalna zawartoscia*/
    void setInitialValue()
    {
        this->clearChromosomes();
        ChromosomePtr zawartosc = ChromosomePtr(new ZawartoscPlecaka( SKARBIEC_OGOLNY ));
        this->addChromosome( zawartosc );       
    }

    /*wykonuje kopie plecaka*/
    SubjectPtr clone() const 
    {
        SubjectPtr nowyPlecak = SubjectPtr(new Plecak()); 
        nowyPlecak->addChromosome( ptrCast( ZawartoscPlecaka, this->chromosomes[0])->clone()  );

        return nowyPlecak;
    }

    int getWartoscSumaryczna()
    {
        return ptrCast( ZawartoscPlecaka, this->chromosomes[0] )->getWartoscSumaryczna();
    }

    void print() const     
    {
        ptrCast( ZawartoscPlecaka, this->chromosomes[0] )->print();
    }    
};



class WartoscPlecaka : FitnessFunction
{
    int wartosc;

    public:

    /* tworzy prototypowa wartosc do ktorej bedziemy dazyc*/
    WartoscPlecaka()
    {
        this->wartosc = 7150 ;
    }

    WartoscPlecaka( int wartosc ) : wartosc(wartosc)
    {}
    
    bool operator > ( const FitnessFunction& toCompare ) const
    {
        return this->wartosc > ((WartoscPlecaka&)toCompare).wartosc;
    }
    
    bool operator == ( const FitnessFunction& toCompare ) const
    {
        return this->wartosc == ((WartoscPlecaka&)toCompare).wartosc;
    }

    /*policz wartosc funkcji celu:
      1. Wez kolejne przedmiotu z plecaka i dodaj ich wartosci
      2. Zapisz uzyskana liczbe jako wartosc
    */
    void calculate( const Subject& toCalculate )
    {
        Plecak& doOceny = (Plecak&) toCalculate;
        this->wartosc = doOceny.getWartoscSumaryczna();
    }
    
    /*tworzy kopie funckji celu*/
    std::unique_ptr < FitnessFunction > clone() const
    {
        return std::unique_ptr< FitnessFunction >( new WartoscPlecaka( this->wartosc ) );  
    }

    void print()
    {
        /*@FIXME if u need me :-) */
    }
};

int main()
{
    WartoscPlecaka goal;
    SubjectPtr plecak( (Subject*) new Plecak() );
    plecak->setInitialValue();
    Population populacja( ( FitnessFunction& ) goal, plecak, 1000, 0.1, 1.5 );
    CyclesCounter *populationCyclesCounter = new CyclesCounter();
    populacja.registerObserver( NObserverPtr(populationCyclesCounter) );
    ResultPrinter *rp = new ResultPrinter();
    populacja.registerObserver( NObserverPtr(rp) );
    Plecak *wynik;
    try
    {
        wynik = EvolFunctions::ptr_cast< SubjectPtr , Plecak >(populacja.start( ));
    }
    catch ( OutOfBoundException &e )
    {
        std::cerr << e.what() << std::endl ;
    }
    std::cout << "\n\nNajlepszy wynik " <<std::endl;
    wynik->print();
    return 0;
}
