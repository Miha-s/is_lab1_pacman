#ifndef COINSLAYER_HPP
#define COINSLAYER_HPP

#include "./RenderLayer.hpp"
#include "Controllers/CoinsController.hpp"
#include "MapElements/MapInstance.hpp"

class CoinsLayer : public RenderLayer
{
    MapInstanceConstPtr m_map_instance;
    CoinsControllerConstPtr m_coins_controller;
    MapObjectPtr m_coin_object;

public:
    CoinsLayer( CoinsControllerConstPtr coins_controller, const std::string& coins_path );

    void update_with_map_instance( MapInstanceConstPtr map_instance );

    void draw( sf::RenderTarget& render_target ) override;
};

using CoinsLayerPtr = std::shared_ptr< CoinsLayer >;

#endif // COINSLAYER_HPP
