#pragma once
#include <string>
#include "Zadanie.hpp"
#include "EvolException.hpp"

typedef int time_type;

class ZarzadcaZadan
{
    time_type **czasy;
    int iloscMaszyn, iloscZadan;
    
    private:
    ZarzadcaZadan();
    ZarzadcaZadan( std::string fileName ) throw ( evol::CannotOpenFileException );
    ZarzadcaZadan(ZarzadcaZadan const&);
    void operator=(ZarzadcaZadan const&);
    public:
    ~ZarzadcaZadan();
    static ZarzadcaZadan& getInstance( const std::string& fileName = "zadania.dat");
    int getIloscMaszyn();
    int getIloscZadan();
    time_type czasObrobki( int idMaszyny, int idZadania );
    time_type czasObrobki( const Zadanie& zadanie);
};

