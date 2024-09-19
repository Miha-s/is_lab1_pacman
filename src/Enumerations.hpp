#ifndef ENUMERATIONS_HPP
#define ENUMERATIONS_HPP
#include <SFML/System/Time.hpp>
#include <cstddef>
#include <unordered_set>

using size_t = std::size_t;

struct MapSize
{
    size_t width;
    size_t height;
    float block_width;
    float block_height;
};

struct MapPosition
{
    size_t row;
    size_t col;

    bool
    operator==( const MapPosition& other ) const
    {
        return row == other.row && col == other.col;
    }

    bool
    operator!=( const MapPosition& other ) const
    {
        return !( *this == other );
    }

    struct HashFunction
    {
        size_t
        operator( )( const MapPosition& pos ) const
        {
            size_t xHash = std::hash< size_t >( )( pos.row );
            size_t yHash = std::hash< size_t >( )( pos.col ) << 1;
            return xHash ^ yHash;
        }
    };
};

namespace std
{
template <>
struct hash< MapPosition >
{
    size_t
    operator( )( const MapPosition& pos ) const
    {
        return MapPosition::HashFunction( )( pos );
    }
};
}  // namespace std

const sf::Time PLAYER_SPEED = sf::seconds( 0.15 );  // seconds per cell
const sf::Time GHOST_SPEED = sf::seconds( 0.2 );

#endif // ENUMERATIONS_HPP
