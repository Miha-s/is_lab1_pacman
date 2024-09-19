#ifndef MAPLAYER_HPP
#define MAPLAYER_HPP
#include <SFML/Graphics/RectangleShape.hpp>

#include "./RenderLayer.hpp"
#include "MapElements/MapInstance.hpp"

class MapLayer : public RenderLayer
{
    std::vector< sf::RectangleShape > m_walls;

public:
    MapLayer( );

    void update_with_map_instance( MapInstanceConstPtr map_instance );

    void draw( sf::RenderTarget& render_target ) override;
private:
    void update_walls_recrangles( MapInstanceConstPtr map_instance );
};

using MapLayerPtr = std::shared_ptr< MapLayer >;

#endif  // MAPLAYER_HPP
