#include "PseudoRandomGenerator.hpp"
#include <stdlib.h>

PseudoRandomGenerator::PseudoRandomGenerator( const size_t seed )
{
    std::srand( seed );
}

size_t
PseudoRandomGenerator::rand( ) const
{
    return std::rand( );
}

size_t
PseudoRandomGenerator::rand( const size_t max ) const
{
    return std::rand( ) % ( max + 1 );
}

size_t
PseudoRandomGenerator::rand( const size_t min, const size_t max ) const
{
    return min + ( std::rand( ) % ( max - min + 1 ) );
}

MapPosition
PseudoRandomGenerator::rand( const MapSize& size ) const
{
    return { rand( 0, size.height - 1 ), rand( 0, size.width - 1 ) };
}
