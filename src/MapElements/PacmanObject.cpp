#include "PacmanObject.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <unordered_map>

#include "Enumerations.hpp"

const std::unordered_map< MoveDirection, float > MOVE_DIRECTION_TO_SPRITE_STATE = {
    { MoveDirection::RIGHT, 0 },
    { MoveDirection::DOWN, 3 },
    { MoveDirection::LEFT, 1 },
    { MoveDirection::UP, 2 }
};

PacmanObject::PacmanObject( MapInstanceConstPtr map_instance, MoveAlgorithmConstPtr move_algo )
    : m_map_instance{ map_instance }
    , m_move_direction{ MoveDirection::UNDEFINED }
    , m_move_algo{ move_algo }
{
}

void
PacmanObject::poll( const sf::Time& elapsed_time )
{
    if ( m_movable->is_moving( ) )
    {
        m_movable->poll( elapsed_time );
        return;
    }

    if ( m_move_algo )
    {
        if ( m_move_direction != MoveDirection::UNDEFINED )
        {
            try_move( );
            m_move_direction = MoveDirection::UNDEFINED;
        }
        else
        {
            move_to( m_move_algo->get_next_move( position( ) ) );
        }
    }
    else if ( m_move_direction != MoveDirection::UNDEFINED )
    {
        try_move( );
    }
}

void
PacmanObject::try_move( MoveDirection dir )
{
    const auto pos =
            m_map_instance->get_position_in_direction( m_sprite->get_map_position( ), dir );

    if ( m_map_instance->is_wall( pos ) )
    {
        std::cout << "In that direction stays wall" << pos.row << " " << pos.col << std::endl;
        return;
    }

    m_move_direction = dir;
}


bool
PacmanObject::load_texture( const std::string& path )
{
    auto texture = std::make_unique< sf::Texture >( );
    sf::IntRect location = { 0, 0, 30, 120 };
    if ( !texture->loadFromFile( path, location ) )
    {
        return false;
    }

    std::vector< sf::IntRect > sprite_states = { { 0, 0, 30, 30 },
                                                 { 0, 32, 30, 30 },
                                                 { 0, 64, 30, 30 },
                                                 { 0, 96, 30, 30 } };
    m_sprite.reset( new SpriteObject{ std::move( texture ), sprite_states } );
    m_movable.reset( new MovableObject{ m_sprite, m_map_instance } );

    return true;
}

void
PacmanObject::set_position( const MapPosition& pos )
{
    m_map_instance->position_object_at( *m_sprite, pos );
}

MapObjectConstPtr
PacmanObject::map_object( ) const
{
    return m_sprite;
}

const MapPosition&
PacmanObject::position( ) const
{
    return m_sprite->get_map_position( );
}


void
PacmanObject::try_move( )
{
    if ( m_movable->is_moving( ) || m_move_direction == MoveDirection::UNDEFINED )
    {
        std::cout << "Is already moving" << std::endl;
        return;
    }

    const auto pos = m_map_instance->get_position_in_direction( position( ), m_move_direction );

    if ( m_map_instance->is_wall( pos ) )
    {
        return;
    }

    move_to( pos );
}

void
PacmanObject::move_to( const MapPosition& pos )
{
    auto dir = m_map_instance->get_move_direction_to_position( position( ), pos );
    m_movable->move_to( pos, PLAYER_SPEED );
    m_sprite->set_state( MOVE_DIRECTION_TO_SPRITE_STATE.at( dir ) );
}
