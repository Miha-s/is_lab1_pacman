#include "EntitiesController.hpp"

#include "Algorithms/CloseSearchAlgorithm.hpp"
#include "Algorithms/CoinSearcherAlgorithm.hpp"
#include "Algorithms/DijkstraSearchAlgorithm.hpp"
#include "Algorithms/PacmanMoveAlgorithm.hpp"
#include "Algorithms/RandomMoveAlgorithm.hpp"

EntitiesController::EntitiesController( const std::string& sprites_path,
                                        PseudoRandomGeneratorConstPtr random_generator,
                                        CoinsControllerConstPtr coins_controller )
    : m_sprites_path{ sprites_path }
    , m_random_generator{ random_generator }
    , m_coins_controller{ coins_controller }
{
}

void
EntitiesController::poll( const sf::Time& elapsed_time )
{
    if ( m_ghost_ate_pacman )
    {
        return;
    }

    m_pacman->poll( elapsed_time );

    for ( auto& ghost : m_ghosts )
    {
        ghost->poll( elapsed_time );
        if ( ghost->map_object( )->intersects( *m_pacman->map_object( ) ) )
        {
            m_ghost_ate_pacman = true;
        }
    }
}

void
EntitiesController::reset( MapInstanceConstPtr map_instance )
{
    m_map_instance = map_instance;
    reset( );
}

PacmanObjectConstPtr
EntitiesController::pacman( ) const
{
    return m_pacman;
}

void
EntitiesController::move_requested( const MoveDirection dir )
{
    m_pacman->try_move( dir );
}

bool
EntitiesController::is_near_ghost( const MapPosition& pos, const size_t dist ) const
{
    for ( const auto& ghost : m_ghosts )
    {
        auto gpos = ghost->map_object( )->get_map_position( );
        if ( ( pos.row <= gpos.row + dist ) && ( pos.row >= gpos.row - dist )
             && ( pos.col <= gpos.col + dist ) && ( pos.col >= gpos.col - dist ) )
        {
            return true;
        }
    }

    return false;
}

bool
EntitiesController::ghost_ate_pacman( ) const
{
    return m_ghost_ate_pacman;
}

const std::vector< GhostObjectPtr >&
EntitiesController::get_ghosts( ) const
{
    return m_ghosts;
}

void
EntitiesController::reset( )
{
    auto path_searcher = std::make_shared< DijkstraSearchAlgorithm >( );

    auto pacman_algo = std::make_shared< PacmanMoveAlgorithm >( m_map_instance,
                                                                m_random_generator,
                                                                path_searcher,
                                                                *this,
                                                                m_coins_controller );
    m_pacman.reset( new PacmanObject{ m_map_instance, pacman_algo } );
    m_pacman->load_texture( m_sprites_path );
    m_pacman->set_position( rand_pos( ) );

    m_ghosts.clear( );

    add_ghost( std::make_shared< RandomMoveAlgorithm >( m_map_instance, m_random_generator ) );

    if ( m_map_instance->level( ) >= 3 )
    {
        add_ghost( std::make_shared< CloseSearchAlgorithm >( m_map_instance,
                                                             m_random_generator,
                                                             path_searcher,
                                                             m_pacman->map_object( ) ) );
    }

    if ( m_map_instance->level( ) >= 5 )
    {
        add_ghost( std::make_shared< CoinSearcherAlgorithm >( m_map_instance,
                                                              m_random_generator,
                                                              path_searcher,
                                                              m_coins_controller,
                                                              m_pacman->map_object( ) ) );
    }

    if ( m_map_instance->level( ) >= 7 )
    {
        add_ghost( std::make_shared< CloseSearchAlgorithm >( m_map_instance,
                                                             m_random_generator,
                                                             path_searcher,
                                                             m_pacman->map_object( ),
                                                             25 ) );
    }

    m_ghost_ate_pacman = false;
}

MapPosition
EntitiesController::rand_pos( )
{
    MapPosition pos = m_random_generator->rand( m_map_instance->size( ) );
    while ( m_map_instance->is_wall( pos ) )
    {
        pos = m_random_generator->rand( m_map_instance->size( ) );
    }

    return pos;
}

void
EntitiesController::add_ghost( MoveAlgorithmConstPtr move_algorithm )
{
    auto ghost = std::make_shared< GhostObject >( m_map_instance, move_algorithm, ghost_speed( ) );

    ghost->load_texture( m_sprites_path );
    ghost->set_position( rand_pos( ) );
    m_ghosts.push_back( ghost );
}

const sf::Time
EntitiesController::ghost_speed( ) const
{
    return GHOST_SPEED
           - ( GHOST_SPEED - PLAYER_SPEED ) * ( 1 - 1.f / ( m_map_instance->level( ) + 1 ) );
}
