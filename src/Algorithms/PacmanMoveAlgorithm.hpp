#ifndef PACMANMOVEALGORITHM_HPP
#define PACMANMOVEALGORITHM_HPP

#include "Controllers/EntitiesController.hpp"
#include "PathSearchAlgorithm.hpp"
#include "RandomMoveAlgorithm.hpp"

class PacmanMoveAlgorithm : public RandomMoveAlgorithm
{
    PathSearchAlgorithmConstPtr m_path_searcher;
    const EntitiesController& m_entities_controller;
    CoinsControllerConstPtr m_coins_controller;

public:
    PacmanMoveAlgorithm( MapInstanceConstPtr map_instance,
                         PseudoRandomGeneratorConstPtr random_generator,
                         PathSearchAlgorithmConstPtr path_searcher,
                         const EntitiesController& entities_controller,
                         CoinsControllerConstPtr coins_controller );

    MapPosition get_next_move( const MapPosition& current_pos ) const override;
};

#endif // PACMANMOVEALGORITHM_HPP
