#ifndef PSEUDORANDOMGENERATOR_HPP
#define PSEUDORANDOMGENERATOR_HPP
#include <memory>

#include "Enumerations.hpp"

class PseudoRandomGenerator
{
public:
    PseudoRandomGenerator( const size_t seed );

    size_t rand( ) const;
    size_t rand( const size_t max ) const;
    size_t rand( const size_t min, const size_t max ) const;
    MapPosition rand( const MapSize& size ) const;
};

using PseudoRandomGeneratorConstPtr = std::shared_ptr< const PseudoRandomGenerator >;

#endif  // PSEUDORANDOMGENERATOR_HPP
