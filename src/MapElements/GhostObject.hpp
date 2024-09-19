#ifndef GHOSTOBJECT_HPP
#define GHOSTOBJECT_HPP

#include "./AnimatedObject.hpp"
#include "./MapInstance.hpp"
#include "./MovableObject.hpp"
#include "./SpriteObject.hpp"
#include "Algorithms/MoveAlgorithm.hpp"

class GhostObject : public AnimatedObject
{
    MapInstanceConstPtr m_map_instance;
    std::shared_ptr< SpriteObject > m_sprite;
    std::shared_ptr< MovableObject > m_movable;
    MoveAlgorithmConstPtr m_move_algorithm;
    const sf::Time m_speed;

public:
    GhostObject( MapInstanceConstPtr map_instance,
                 MoveAlgorithmConstPtr move_algorithm,
                 const sf::Time& speed );
    void poll( const sf::Time& elapsed_time ) override;
    bool load_texture( const std::string& path ) override;
    void set_position( const MapPosition& pos ) override;
    MapObjectConstPtr map_object( ) const override;

private:
    void move_to( const MapPosition& pos );
};

using GhostObjectPtr = std::shared_ptr< GhostObject >;

#endif // GHOSTOBJECT_HPP
