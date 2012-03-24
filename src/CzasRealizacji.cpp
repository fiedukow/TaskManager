#include "Population.hpp"
#include "CzasRealizacji.hpp"
#include <iostream>

CzasRealizacji::CzasRealizacji()
{
    czas = 1;
}
CzasRealizacji::CzasRealizacji(const int czas_)
{
    czas = czas_;
}
bool CzasRealizacji::operator > ( const FitnessFunction& toCompare) const
{
    std::cout << czas << ">" << ((CzasRealizacji&)toCompare).czas << std::endl;
    return czas < ((CzasRealizacji&)toCompare).czas;
}
bool CzasRealizacji::operator == ( const FitnessFunction& toCompare) const
{
    return czas == ((CzasRealizacji&)toCompare).czas;
}
void CzasRealizacji::calculate( const Subject& toCalculate )
{
    Realizacja& doOceny = (Realizacja&) toCalculate;
    czas = doOceny.getSumarycznyCzas();
    return;
}
std::unique_ptr< FitnessFunction > CzasRealizacji::clone() const
{
    return std::unique_ptr< FitnessFunction >( new CzasRealizacji( czas ) );
}
void CzasRealizacji::print()
{
/* FIXME implement me, if you want ;) */
}
