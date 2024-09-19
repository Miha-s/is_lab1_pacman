#include "MapObjectsLayer.hpp"

MapObjectsLayer::MapObjectsLayer( EntitiesControllerConstPtr ghosts_controller )
    : m_entities_controller{ ghosts_controller }
{
}

void
MapObjectsLayer::draw( sf::RenderTarget& render_target )
{
    for ( const auto& ghost : m_entities_controller->get_ghosts( ) )
    {
        render_target.draw( *ghost->map_object( ) );
    }

    render_target.draw( *m_entities_controller->pacman( )->map_object( ) );
}
