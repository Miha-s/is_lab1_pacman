#include "SpriteObject.hpp"

#include <SFML/Graphics/Texture.hpp>

SpriteObject::SpriteObject( std::unique_ptr< const sf::Texture > texture,
                            const std::vector< sf::IntRect >& sprite_states )
    : m_texture{ std::move( texture ) }
    , m_sprite_states{ sprite_states }
{
    m_sprite.setTexture( *m_texture );
    set_state( 0 );
}

void
SpriteObject::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    target.draw( m_sprite );
}

void
SpriteObject::set_position( const sf::Vector2f& pos )
{
    m_sprite.setPosition( pos );
}

sf::FloatRect
SpriteObject::get_global_bounds( ) const
{
    return m_sprite.getGlobalBounds( );
}

bool
SpriteObject::set_state( const std::size_t state )
{
    if ( state > m_sprite_states.size( ) )
    {
        return false;
    }

    m_sprite.setTextureRect( m_sprite_states[ state ] );

    return true;
}
