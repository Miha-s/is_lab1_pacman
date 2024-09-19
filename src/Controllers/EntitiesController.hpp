#ifndef ENTITIESCONTROLLER_HPP
#define ENTITIESCONTROLLER_HPP

#include "CoinsController.hpp"
#include "MapElements/GhostObject.hpp"
#include "MapElements/MapInstance.hpp"
#include "MapElements/PacmanObject.hpp"
#include "PseudoRandomGenerator.hpp"

class EntitiesController
{
    const std::string m_sprites_path;
    bool m_ghost_ate_pacman;

    PseudoRandomGeneratorConstPtr m_random_generator;
    MapInstanceConstPtr m_map_instance;
    std::vector< GhostObjectPtr > m_ghosts;
    PacmanObjectPtr m_pacman;
    CoinsControllerConstPtr m_coins_controller;

public:
    EntitiesController( const std::string& sprites_path,
                        PseudoRandomGeneratorConstPtr random_generator,
                        CoinsControllerConstPtr coins_controller );
    void poll( const sf::Time& elapsed_time );

    void reset( MapInstanceConstPtr map_instance );
    PacmanObjectConstPtr pacman( ) const;
    void move_requested( const MoveDirection dir );
    bool is_near_ghost( const MapPosition& pos, const size_t dist = 1 ) const;
    bool ghost_ate_pacman( ) const;

    const std::vector< GhostObjectPtr >& get_ghosts( ) const;
private:
    void reset( );
    MapPosition rand_pos( );
    void add_ghost( MoveAlgorithmConstPtr move_algorithm );
    const sf::Time ghost_speed( ) const;
};

using EntitiesControllerConstPtr = std::shared_ptr< const EntitiesController >;
using EntitiesControllerPtr = std::shared_ptr< EntitiesController >;

#endif // ENTITIESCONTROLLER_HPP
