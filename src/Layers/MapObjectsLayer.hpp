#ifndef MAPOBJECTSLAYER_HPP
#define MAPOBJECTSLAYER_HPP

#include "./RenderLayer.hpp"
#include "Controllers/EntitiesController.hpp"
#include "MapElements/MapObject.hpp"

class MapObjectsLayer : public RenderLayer
{
    EntitiesControllerConstPtr m_entities_controller;

public:
    MapObjectsLayer( EntitiesControllerConstPtr ghosts_controller );
    void draw( sf::RenderTarget& render_target ) override;
};

using MapObjectsLayerPtr = std::shared_ptr< MapObjectsLayer >;

#endif  // MAPOBJECTSLAYER_HPP
