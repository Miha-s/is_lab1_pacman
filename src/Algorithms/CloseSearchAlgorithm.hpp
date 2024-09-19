#ifndef CLOSESEARCHALGORITHM_HPP
#define CLOSESEARCHALGORITHM_HPP

#include "RandomMoveAlgorithm.hpp"
#include "PathSearchAlgorithm.hpp"

class CloseSearchAlgorithm : public RandomMoveAlgorithm
{
    PathSearchAlgorithmConstPtr m_path_searcher;
    MapObjectConstPtr m_pacman;
    const size_t m_max_distance;

public:
    CloseSearchAlgorithm( MapInstanceConstPtr map_instance,
                          PseudoRandomGeneratorConstPtr random_generator,
                          PathSearchAlgorithmConstPtr path_searcher,
                          MapObjectConstPtr pacman,
                          const size_t max_distance = 4 );

    MapPosition get_next_move( const MapPosition& current_pos ) const override;
};

#endif // CLOSESEARCHALGORITHM_HPP
