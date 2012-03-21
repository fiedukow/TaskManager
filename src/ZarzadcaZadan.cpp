#include "ZarzadcaZadan.hpp"
#include "EvolException.hpp"
#include <string>
#include <fstream>

typedef int time_type;

ZarzadcaZadan& ZarzadcaZadan::getInstance()
{
    static ZarzadcaZadan instance("zadania.dat");
    return instance;
}

/**
 * Class that provides informations about time that each Machine spends doing each Task.
 * This class can read informations from file if it is needed
 **/
ZarzadcaZadan::ZarzadcaZadan( std::string fileName ) throw (evol::CannotOpenFileException)
{
    std::ifstream fileToRead;
    fileToRead.open( fileName.c_str(), std::ios::in );
    if( fileToRead.is_open() )
    {   
        fileToRead >> iloscMaszyn >> iloscZadan;
        czasy = new time_type*[ iloscMaszyn ];
        for ( int i = 0; i < iloscMaszyn; ++i )
        {                
            czasy[i] = new time_type[iloscZadan];
        }     
        for ( int i = 0; i < iloscMaszyn; ++i )
        {
            for( int j = 0; j < iloscZadan; ++j )
            {
                if( fileToRead.good() )
                {               
                    fileToRead >> czasy[i][j];
                }
                else
                {
                    throw evol::FileException( fileName ); /*TODO: it should be another exception*/
                }
            }
        }        
    }
    else
    {
        throw evol::CannotOpenFileException(fileName);
    }  
}

ZarzadcaZadan::~ZarzadcaZadan()
{
    for( int i = 0; i < iloscMaszyn; ++i )
    {
        delete[] czasy[i];
    }
    delete[] czasy;
}

int ZarzadcaZadan::getIloscMaszyn()
{
    return iloscMaszyn;
}

int ZarzadcaZadan::getIloscZadan()
{
    return iloscZadan;
}

time_type ZarzadcaZadan::czasObrobki( int idMaszyny, int idZadania )
{
    if( idMaszyny >= iloscMaszyn || idZadania >= iloscZadan )
    {
        /*TODO: out of bound exception here */ 
    }
    return czasy[idMaszyny][idZadania];
}

