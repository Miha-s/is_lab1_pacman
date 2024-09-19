#ifndef DIJKSTRASEARCHALGORITHM_HPP
#define DIJKSTRASEARCHALGORITHM_HPP

#include "PathSearchAlgorithm.hpp"

class DijkstraSearchAlgorithm : public PathSearchAlgorithm
{

public:
    std::vector< MapPosition > search_path(
            MapPosition start,
            std::function< bool( const MapPosition& pos ) > is_end,
            std::function< bool( const MapPosition& pos ) > is_blocked ) const;
};

#endif // DIJKSTRASEARCHALGORITHM_HPP
