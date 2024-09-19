#include "GhostObject.hpp"

#include "SFML/Graphics/Texture.hpp"

GhostObject::GhostObject( MapInstanceConstPtr map_instance,
                          MoveAlgorithmConstPtr move_algorithm,
                          const sf::Time& speed )
    : m_map_instance{ map_instance }
    , m_move_algorithm{ move_algorithm }
    , m_speed{ speed }
{
}

void
GhostObject::poll( const sf::Time& elapsed_time )
{
    if ( m_movable->is_moving( ) )
    {
        m_movable->poll( elapsed_time );
        return;
    }

    auto new_pos = m_move_algorithm->get_next_move( m_sprite->get_map_position( ) );
    move_to( new_pos );
}

bool
GhostObject::load_texture( const std::string& path )
{
    auto texture = std::make_unique< sf::Texture >( );
    sf::IntRect location = { 0, 128, 32, 32 };
    if ( !texture->loadFromFile( path, location ) )
    {
        return false;
    }

    std::vector< sf::IntRect > sprite_states = { { 0, 0, 32, 32 } };
    m_sprite.reset( new SpriteObject{ std::move( texture ), sprite_states } );
    m_movable.reset( new MovableObject{ m_sprite, m_map_instance } );

    return true;
}

void
GhostObject::set_position( const MapPosition& pos )
{
    m_map_instance->position_object_at( *m_sprite, pos );
}

MapObjectConstPtr
GhostObject::map_object( ) const
{
    return m_sprite;
}

void
GhostObject::move_to( const MapPosition& pos )
{
    m_movable->move_to( pos, m_speed );
}
