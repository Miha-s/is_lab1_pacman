#ifndef MAPINSTANCE_HPP
#define MAPINSTANCE_HPP

#include <memory>
#include <vector>

#include "./MapObject.hpp"
#include "Enumerations.hpp"

enum class MoveDirection
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UNDEFINED
};

class MapInstance
{
    const MapSize m_map_size;
    std::vector< std::vector< bool > > m_map_represantation;
    const size_t m_level;

public:
    MapInstance( const MapSize& map_size, const size_t level );

    void position_object_at( MapObject& object, const MapPosition& position ) const;
    sf::Vector2f get_object_position_at( MapObject& object, const MapPosition& position ) const;

    MapPosition get_position_in_direction( const MapPosition& position, MoveDirection dir ) const;
    MoveDirection get_move_direction_to_position( const MapPosition& start,
                                                  const MapPosition& end ) const;

    const MapSize& size( ) const;
    size_t level( ) const;
    bool is_wall( const MapPosition& position ) const;
    void set_wall( const size_t row, const size_t col );
    void remove_wall( const MapPosition& position );
};

using MapInstancePtr = std::shared_ptr< MapInstance >;
using MapInstanceConstPtr = std::shared_ptr< const MapInstance >;

#endif
