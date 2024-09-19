#ifndef RECTOBJECT_HPP
#define RECTOBJECT_HPP

#include <SFML/Graphics/RectangleShape.hpp>

#include "./MapObject.hpp"

class RectObject : public MapObject
{
    sf::RectangleShape m_rect;

public:
    RectObject( const sf::Vector2f size );

    void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
    void set_position( const sf::Vector2f& pos ) override;
    sf::FloatRect get_global_bounds( ) const override;
};

#endif // RECTOBJECT_HPP
