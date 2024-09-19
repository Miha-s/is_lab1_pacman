#ifndef MAPOBJECT_HPP
#define MAPOBJECT_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>

#include "Enumerations.hpp"

class MapObject : public sf::Drawable
{
    MapPosition m_map_position;
public:
    virtual sf::FloatRect get_global_bounds( ) const = 0;
    virtual void set_position( const sf::Vector2f& pos ) = 0;
    void set_map_position( const MapPosition map_position );
    const MapPosition& get_map_position( ) const;
    bool intersects( const MapObject& other ) const;

    virtual ~MapObject( )
    {
    }
};

using MapObjectPtr = std::shared_ptr< MapObject >;
using MapObjectConstPtr = std::shared_ptr< const MapObject >;

#endif // MAPOBJECT_HPP
