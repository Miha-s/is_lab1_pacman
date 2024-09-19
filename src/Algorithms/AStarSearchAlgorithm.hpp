#ifndef ASTARSEARCHALGORITHM_HPP
#define ASTARSEARCHALGORITHM_HPP
#include "PathSearchAlgorithm.hpp"

class AStarSearchAlgorithm : public PathSearchAlgorithm
{
public:
    std::vector< MapPosition > search_path(
            MapPosition start,
            std::function< bool( const MapPosition& pos ) > is_end,
            std::function< bool( const MapPosition& pos ) > is_blocked ) const;
};

#endif // ASTARSEARCHALGORITHM_HPP
