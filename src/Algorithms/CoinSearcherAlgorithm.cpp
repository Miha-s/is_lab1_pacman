#include "CoinSearcherAlgorithm.hpp"

CoinSearcherAlgorithm::CoinSearcherAlgorithm( MapInstanceConstPtr map_instance,
                                              PseudoRandomGeneratorConstPtr random_generator,
                                              PathSearchAlgorithmConstPtr path_searcher,
                                              CoinsControllerConstPtr coins_controller,
                                              MapObjectConstPtr pacman )
    : RandomMoveAlgorithm{ map_instance, random_generator }
    , m_path_searcher{ path_searcher }
    , m_coins_controller{ coins_controller }
    , m_pacman{ pacman }
{
}

MapPosition
CoinSearcherAlgorithm::get_next_move( const MapPosition& current_pos ) const
{
    auto path = m_path_searcher->search_path(
            current_pos,
            [ this ]( const MapPosition& pos ) { return pos == m_pacman->get_map_position( ); },
            [ this ]( const MapPosition& pos ) { return m_map_instance->is_wall( pos ); } );

    if ( path.size( ) <= 4 && !path.empty( ) )
    {
        return path.front( );
    }

    path = m_path_searcher->search_path(
            current_pos,
            [ this ]( const MapPosition& pos ) { return m_coins_controller->is_coin( pos ); },
            [ this ]( const MapPosition& pos ) { return m_map_instance->is_wall( pos ); } );

    if ( path.size( ) > 15 || path.empty( ) )
    {
        return RandomMoveAlgorithm::get_next_move( current_pos );
    }
    else
    {
        return path.front( );
    }
}
