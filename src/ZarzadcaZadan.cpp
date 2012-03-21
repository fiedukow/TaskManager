#include <iostream>
#include "EvolException.hpp"
#include <string>
#include <fstream>

typedef int time_type;

/**
 * Class that provides informations about time that each Machine spends doing each Task.
 * This class can read informations from file if it is needed
 **/
class ZarzadcaZadan
{
    time_type **czasy;
    int iloscMaszyn, iloscZadan;

    ZarzadcaZadan( std::string fileName ) throw (evol::CannotOpenFileException)
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
                for( int j = 0; i < iloscZadan; ++j )
                {
                    fileToRead >> czasy[i][j];
                }
            }        
        }
        else
        {
            throw evol::CannotOpenFileException(fileName);
        }  
    }

    ~ZarzadcaZadan()
    {
        for( int i = 0; i < iloscMaszyn; ++i )
        {
            delete[] czasy[i];
        }
        delete[] czasy;
    }

};
