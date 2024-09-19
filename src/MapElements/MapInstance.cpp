#include "./MapInstance.hpp"

MapInstance::MapInstance( const MapSize& map_size, const size_t level )
    : m_map_size{ map_size }
    , m_level{ level }
{
    m_map_represantation.resize( map_size.height );
    for ( auto& row : m_map_represantation )
    {
        row.resize( map_size.width, false );
    }
}

void
MapInstance::position_object_at( MapObject& object, const MapPosition& position ) const
{
    object.set_map_position( position );
    object.set_position( get_object_position_at( object, position ) );
}

sf::Vector2f
MapInstance::get_object_position_at( MapObject& object, const MapPosition& position ) const
{
    const auto& object_size = object.get_global_bounds( ).getSize( );

    sf::Vector2f cell_position{ position.col * m_map_size.block_width,
                                position.row * m_map_size.block_height };

    cell_position.x += ( m_map_size.block_width - object_size.x ) / 2;   // centering horizontally
    cell_position.y += ( m_map_size.block_height - object_size.y ) / 2;  // centering vertically

    return cell_position;
}

MapPosition
MapInstance::get_position_in_direction( const MapPosition& position, MoveDirection dir ) const
{
    auto pos = position;
    switch ( dir )
    {
    case MoveDirection::RIGHT:
        pos.col++;
        break;
    case MoveDirection::LEFT:
        pos.col--;
        break;
    case MoveDirection::UP:
        pos.row--;
        break;
    case MoveDirection::DOWN:
        pos.row++;
        break;
    default:
        break;
    }

    return pos;
}

MoveDirection
MapInstance::get_move_direction_to_position( const MapPosition& start,
                                             const MapPosition& end ) const
{
    if ( end.col > start.col )
    {
        return MoveDirection::RIGHT;
    }
    else if ( end.col < start.col )
    {
        return MoveDirection::LEFT;
    }
    else if ( end.row > start.row )
    {
        return MoveDirection::DOWN;
    }
    else if ( end.row < start.row )
    {
        return MoveDirection::UP;
    }

    return MoveDirection::UNDEFINED;
}

const MapSize&
MapInstance::size( ) const
{
    return m_map_size;
}

size_t
MapInstance::level( ) const
{
    return m_level;
}

bool
MapInstance::is_wall( const MapPosition& position ) const
{
    return m_map_represantation[ position.row ][ position.col ];
}

void
MapInstance::set_wall( const size_t row, const size_t col )
{
    m_map_represantation[ row ][ col ] = true;
}

void
MapInstance::remove_wall( const MapPosition& position )
{
    m_map_represantation[ position.row ][ position.col ] = false;
}
