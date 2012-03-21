#include <iostream>
//#include "EvolException.hpp"
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

    public: 
    ZarzadcaZadan( std::string fileName ) /*throw (evol::CannotOpenFileException)*/
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
                        throw 2;
                    }
                }
            }        
        }
        else
        {
            std::cout << "FAIL?" << std::endl;
            throw 1;
            /*throw evol::CannotOpenFileException(fileName);*/
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

    int getIloscMaszyn()
    {
        return iloscMaszyn;
    }
    
    int getIloscZadan()
    {
        return iloscZadan;
    }

    void print()
    {
        std::cout << "Maszyn: " << iloscMaszyn << std::endl;
        std::cout << "Zadan:  " << iloscZadan << std::endl;
        for ( int i = 0; i < iloscMaszyn; ++i )
        {
            for ( int j = 0; j < iloscZadan; ++j )
                std::cout << czasy[ i ][ j ] << " ";
            std::cout << std::endl;
        }
    }

    time_type czasObrobki( int idMaszyny, int idZadania )
    {
        return czasy[idMaszyny][idZadania];
    }
};

int main()
{
    try{
        ZarzadcaZadan zz("zadania.dat");
        zz.print();
        std::cout << zz.czasObrobki( 2, 0 ) << std::endl ;
    }
    catch( int a )
    {
        std::cout << "O KURCZE :( " << a << std::endl;
    }
    return 0;
}
