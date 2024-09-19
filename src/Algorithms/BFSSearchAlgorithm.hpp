#ifndef BFSSEARCHALGORITHM_HPP
#define BFSSEARCHALGORITHM_HPP
#include "PathSearchAlgorithm.hpp"

class BFSSearchAlgorithm: public PathSearchAlgorithm
{
public:
    std::vector< MapPosition > search_path(
        MapPosition start,
        std::function< bool( const MapPosition& pos ) > is_end,
        std::function< bool( const MapPosition& pos ) > is_blocked ) const;
};

#endif // BFSSEARCHALGORITHM_HPP
