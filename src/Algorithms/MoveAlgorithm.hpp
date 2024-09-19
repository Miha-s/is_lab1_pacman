#ifndef MOVEALGORITHM_HPP
#define MOVEALGORITHM_HPP

#include <memory>

#include "Enumerations.hpp"

/*
 *  In theory the same algorithm object can be used by different instances, so this must be
 * independent of when or how many times it is called
 */
class MoveAlgorithm
{
public:
    virtual MapPosition get_next_move( const MapPosition& current_pos ) const = 0;

    virtual ~MoveAlgorithm( )
    {
    }
};

using MoveAlgorithmConstPtr = std::shared_ptr< const MoveAlgorithm >;

#endif // MOVEALGORITHM_HPP
