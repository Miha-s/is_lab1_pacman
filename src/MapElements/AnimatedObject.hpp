#ifndef ANIMATEDOBJECT_HPP
#define ANIMATEDOBJECT_HPP

#include <SFML/System/Time.hpp>
#include <string>

#include "./MapObject.hpp"
#include "Enumerations.hpp"

class AnimatedObject
{
public:
    virtual void poll( const sf::Time& elapsed_time ) = 0;
    virtual bool load_texture( const std::string& path ) = 0;
    virtual void set_position( const MapPosition& pos ) = 0;

    virtual MapObjectConstPtr map_object( ) const = 0;

    ~AnimatedObject( )
    {
    }
};

using AnimatedObjectPtr = std::shared_ptr< AnimatedObject >;

#endif // ANIMATEDOBJECT_HPP
