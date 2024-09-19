#include "MapObject.hpp"

void
MapObject::set_map_position( const MapPosition map_position )
{
    m_map_position = map_position;
}

const MapPosition&
MapObject::get_map_position( ) const
{
    return m_map_position;
}

bool
MapObject::intersects( const MapObject& other ) const
{
    const auto& this_bounds = get_global_bounds();
    const auto& other_bounds = other.get_global_bounds( );

    if ( this_bounds.intersects( other_bounds ) )
    {
        return true;
    }

    return false;
}

