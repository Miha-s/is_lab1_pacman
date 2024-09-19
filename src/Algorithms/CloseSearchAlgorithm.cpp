#include "CloseSearchAlgorithm.hpp"

CloseSearchAlgorithm::CloseSearchAlgorithm( MapInstanceConstPtr map_instance,
                                            PseudoRandomGeneratorConstPtr random_generator,
                                            PathSearchAlgorithmConstPtr path_searcher,
                                            MapObjectConstPtr pacman,
                                            const size_t max_distance )
    : RandomMoveAlgorithm{ map_instance, random_generator }
    , m_path_searcher{ path_searcher }
    , m_pacman{ pacman }
    , m_max_distance{ max_distance }
{
}

MapPosition
CloseSearchAlgorithm::get_next_move( const MapPosition& current_pos ) const
{
    auto path = m_path_searcher->search_path(
            current_pos,
            [ this ]( const MapPosition& pos ) { return m_pacman->get_map_position( ) == pos; },
            [ this ]( const MapPosition& pos ) { return m_map_instance->is_wall( pos ); } );

    if ( path.size( ) > m_max_distance || path.empty( ) )
    {
        return RandomMoveAlgorithm::get_next_move( current_pos );
    }
    else
    {
        return path[ 0 ];
    }
}
