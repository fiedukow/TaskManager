#pragma once
#include <string>
#include "EvolException.hpp"

typedef int time_type;

class ZarzadcaZadan
{
    time_type **czasy;
    int iloscMaszyn, iloscZadan;
    
    public:
    ZarzadcaZadan( std::string fileName ) throw ( evol::CannotOpenFileException );
    ~ZarzadcaZadan();
    int getIloscMaszyn();
    int getIloscZadan();
    time_type czasObrobki( int idMaszyny, int idZadania );
};

