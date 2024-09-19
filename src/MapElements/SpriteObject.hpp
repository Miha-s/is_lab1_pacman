#ifndef SPRITEOBJECT_HPP
#define SPRITEOBJECT_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <vector>

#include "./MapObject.hpp"

class SpriteObject : public MapObject
{
    std::unique_ptr< const sf::Texture > m_texture;
    const std::vector< sf::IntRect > m_sprite_states;

    sf::Sprite m_sprite;

public:
    SpriteObject( std::unique_ptr< const sf::Texture > texture,
                  const std::vector< sf::IntRect >& sprite_states );
    void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
    void set_position( const sf::Vector2f& pos ) override;
    sf::FloatRect get_global_bounds( ) const override;
    bool set_state( const std::size_t state );
};

#endif
