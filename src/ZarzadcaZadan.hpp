#pragma once
#include <string>
#include "EvolException.hpp"

typedef int time_type;

class ZarzadcaZadan
{
    time_type **czasy;
    int iloscMaszyn, iloscZadan;
    
    private:
    ZarzadcaZadan( std::string fileName ) throw ( evol::CannotOpenFileException );
    public:
    ~ZarzadcaZadan();
    static ZarzadcaZadan& getInstance();
    int getIloscMaszyn();
    int getIloscZadan();
    time_type czasObrobki( int idMaszyny, int idZadania );
};

