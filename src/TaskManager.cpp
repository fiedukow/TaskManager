#include "Realizacja.hpp"
#include "CzasRealizacji.hpp"

int main()
{
    CzasRealizacji goal(8);
    SubjectPtr realizacja( (Subject*) new Realizacja() );
    realizacja->setInitialValue();
    Population populacja( ( FitnessFunction& ) goal, realizacja, 1000, 0.2, 2.0 );
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
