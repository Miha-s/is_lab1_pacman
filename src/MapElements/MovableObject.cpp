#include "MovableObject.hpp"

MovableObject::MovableObject( MapObjectPtr object, MapInstanceConstPtr map_instance )
    : m_object{ object }
    , m_map_instance{ map_instance }
{
    reset( );
}

bool
MovableObject::is_moving( )
{
    return m_remaining_time != sf::Time::Zero;
}

void
MovableObject::move_to( const MapPosition& position, const sf::Time& moving_time )
{
    m_remaining_time = moving_time;
    m_dest_position = m_map_instance->get_object_position_at( *m_object, position );
    m_object->set_map_position( position );
}

void
MovableObject::poll( const sf::Time& elapsed_time )
{
    if ( !is_moving( ) )
    {
        return;
    }

    if ( elapsed_time > m_remaining_time )
    {
        m_object->set_position( m_dest_position );
        reset( );
        return;
    }

    auto curr_pos = m_object->get_global_bounds( ).getPosition( );
    const auto& move_x = ( m_dest_position.x - curr_pos.x ) * ( elapsed_time / m_remaining_time );
    const auto& move_y = ( m_dest_position.y - curr_pos.y ) * ( elapsed_time / m_remaining_time );

    curr_pos.x += move_x;
    curr_pos.y += move_y;

    m_object->set_position( curr_pos );

    m_remaining_time -= elapsed_time;
}

void
MovableObject::reset( )
{
    m_dest_position = sf::Vector2f{ };
    m_remaining_time = sf::Time::Zero;
}
