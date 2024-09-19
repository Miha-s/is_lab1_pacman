#ifndef PACMANOBJECT_HPP
#define PACMANOBJECT_HPP

#include "./AnimatedObject.hpp"
#include "./MapInstance.hpp"
#include "./MovableObject.hpp"
#include "./SpriteObject.hpp"
#include "Algorithms/MoveAlgorithm.hpp"

class PacmanObject : public AnimatedObject
{
    MapInstanceConstPtr m_map_instance;
    std::shared_ptr< SpriteObject > m_sprite;
    std::shared_ptr< MovableObject > m_movable;
    MoveDirection m_move_direction;
    MoveAlgorithmConstPtr m_move_algo;

public:
    PacmanObject( MapInstanceConstPtr map_instance, MoveAlgorithmConstPtr move_algo = nullptr );
    void poll( const sf::Time& elapsed_time ) override;
    bool load_texture( const std::string& path ) override;
    void set_position( const MapPosition& pos ) override;
    MapObjectConstPtr map_object( ) const override;

    void try_move( MoveDirection dir );

private:
    const MapPosition& position( ) const;
    void try_move( );
    void move_to( const MapPosition& pos );
};

using PacmanObjectPtr = std::shared_ptr< PacmanObject >;
using PacmanObjectConstPtr = std::shared_ptr< PacmanObject >;

#endif // PACMANOBJECT_HPP
