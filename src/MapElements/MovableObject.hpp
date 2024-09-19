#ifndef MOVABLEOBJECT_HPP
#define MOVABLEOBJECT_HPP

#include <SFML/System/Time.hpp>

#include "./MapInstance.hpp"
#include "./MapObject.hpp"

class MovableObject
{
    MapObjectPtr m_object;
    MapInstanceConstPtr m_map_instance;
    sf::Time m_remaining_time;
    sf::Vector2f m_dest_position;

public:
    MovableObject( MapObjectPtr object, MapInstanceConstPtr map_instance );
    bool is_moving( );
    void move_to( const MapPosition& position, const sf::Time& moving_time );
    void poll( const sf::Time& elapsed_time );
private:
    void reset( );
};

#endif // MOVABLEOBJECT_HPP
