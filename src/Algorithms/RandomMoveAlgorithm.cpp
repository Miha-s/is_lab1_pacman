#include "RandomMoveAlgorithm.hpp"

#include <stdlib.h>
#include <time.h>

size_t RandomMoveAlgorithm::counter = 1;

RandomMoveAlgorithm::RandomMoveAlgorithm( MapInstanceConstPtr map_instance,
                                          PseudoRandomGeneratorConstPtr random_generator )
    : m_map_instance{ map_instance }
    , m_random_generator{ random_generator }
{
}

MapPosition
RandomMoveAlgorithm::get_next_move( const MapPosition& current_pos ) const
{
    srand( counter++ );
    MapPosition new_pos;
    do
    {
        MoveDirection dir = static_cast< MoveDirection >( m_random_generator->rand( 3 ) );
        new_pos = m_map_instance->get_position_in_direction( current_pos, dir );
    } while ( m_map_instance->is_wall( new_pos ) );

    return new_pos;
}
