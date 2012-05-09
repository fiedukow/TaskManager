#include "PodgladPostepu.hpp"
#include "Realizacja.hpp"
#include "Observer.hpp"
#include "CzasRealizacji.hpp"

int main( int argc, char* argv[] )
{
    if( argc < 2 )
    {
        std::cout << "Usage: " << argv[0] << " fileWithTasks" << std::endl;
        return -1;
    }

    CzasRealizacji goal(8);
    SubjectPtr realizacja( (Subject*) new Realizacja(argv[1]) );
    realizacja->setInitialValue();
    Population populacja( ( FitnessFunction& ) goal, realizacja, 1000, 0.2, 2.0 );
    populacja.registerObserver( NObserverPtr( new PodgladPostepu() ) );

    Realizacja *wynik;
    try
    {
        wynik = EvolFunctions::ptr_cast< SubjectPtr, Realizacja >(populacja.start( ));
    }
    catch ( OutOfBoundException &e )
    {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "\n\nNajlepszy wynik " << std::endl;
    wynik->print();
    return 0;
}
