#include "Realizacja.hpp"
#include "Observer.hpp"
#include "PodgladPostepu.hpp"
#include "CzasRealizacji.hpp"

int main()
{
    CzasRealizacji goal(8);
    SubjectPtr realizacja( (Subject*) new Realizacja() );
    realizacja->setInitialValue();
    Population populacja( ( FitnessFunction& ) goal, realizacja, 5000, 0.3, 3.0 );
    PodgladPostepu postep;
    populacja.registerObserver( NObserverPtr( &postep ) );

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
