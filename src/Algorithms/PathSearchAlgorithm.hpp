#ifndef PATHSEARCHALGORITHM_HPP
#define PATHSEARCHALGORITHM_HPP
#include <functional>
#include <memory>
#include <vector>

#include "Enumerations.hpp"

class PathSearchAlgorithm
{
public:
    virtual std::vector< MapPosition > search_path(
            MapPosition start,
            std::function< bool( const MapPosition& pos ) > is_end,
            std::function< bool( const MapPosition& pos ) > is_blocked ) const = 0;
};


using PathSearchAlgorithmConstPtr = std::shared_ptr< const PathSearchAlgorithm >;
#endif  // PATHSEARCHALGORITHM_HPP
