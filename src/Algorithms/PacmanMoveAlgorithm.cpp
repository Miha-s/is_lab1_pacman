#include "PacmanMoveAlgorithm.hpp"

PacmanMoveAlgorithm::PacmanMoveAlgorithm( MapInstanceConstPtr map_instance,
                                          PseudoRandomGeneratorConstPtr random_generator,
                                          PathSearchAlgorithmConstPtr path_searcher,
                                          const EntitiesController& entities_controller,
                                          CoinsControllerConstPtr coins_controller )
    : RandomMoveAlgorithm{ map_instance, random_generator }
    , m_path_searcher{ path_searcher }
    , m_entities_controller{ entities_controller }
    , m_coins_controller{ coins_controller }
{
}

MapPosition
PacmanMoveAlgorithm::get_next_move( const MapPosition& current_pos ) const
{
    const auto coin_checker = [ this ]( const MapPosition& pos )
    { return m_coins_controller->is_coin( pos ); };
    const auto wall_ghost_checker = [ this ]( const size_t dist )
    {
        return [ this, dist ]( const MapPosition& pos ) {
            return m_map_instance->is_wall( pos )
                   || m_entities_controller.is_near_ghost( pos, dist );
        };
    };
    const auto far_from_ghost_position_checker = [ this ]( const MapPosition& pos )
    { return !m_entities_controller.is_near_ghost( pos, 2 ); };

    auto path = m_path_searcher->search_path( current_pos, coin_checker, wall_ghost_checker( 2 ) );

    if ( path.empty( ) )
    {
        path = m_path_searcher->search_path( current_pos,
                                             far_from_ghost_position_checker,
                                             wall_ghost_checker( 1 ) );
    }

    if ( path.empty( ) )
    {
        path = m_path_searcher->search_path( current_pos,
                                             far_from_ghost_position_checker,
                                             wall_ghost_checker( 0 ) );
    }

    if ( path.empty( ) )
    {
        return RandomMoveAlgorithm::get_next_move( current_pos );
    }
    else
    {
        return path.front( );
    }
}
