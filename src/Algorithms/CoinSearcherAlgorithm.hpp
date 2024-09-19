#ifndef COINSEARCHERALGORITHM_HPP
#define COINSEARCHERALGORITHM_HPP
#include "RandomMoveAlgorithm.hpp"
#include "PathSearchAlgorithm.hpp"
#include "Controllers/CoinsController.hpp"

class CoinSearcherAlgorithm : public RandomMoveAlgorithm
{
    PathSearchAlgorithmConstPtr m_path_searcher;
    CoinsControllerConstPtr m_coins_controller;
    MapObjectConstPtr m_pacman;

public:
    CoinSearcherAlgorithm( MapInstanceConstPtr map_instance,
                           PseudoRandomGeneratorConstPtr random_generator,
                           PathSearchAlgorithmConstPtr path_searcher,
                           CoinsControllerConstPtr coins_controller,
                           MapObjectConstPtr pacman );

    MapPosition get_next_move( const MapPosition& current_pos ) const override;
};

#endif // COINSEARCHERALGORITHM_HPP
