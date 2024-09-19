#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "GameEngine.hpp"
#include "Layers/CoinsLayer.hpp"
#include "Layers/MapLayer.hpp"
#include "Layers/MapObjectsLayer.hpp"

class Controller
{
    GameEngine m_game_engine;
    sf::RenderWindow& m_window;

    MapLayerPtr m_map_layer;
    MapObjectsLayerPtr m_map_objects_layer;
    CoinsLayerPtr m_coins_layer;

public:
    Controller( sf::RenderWindow& window, const MapSize& map_size );

    void process_event( sf::Event event );
    void poll( const sf::Time& elapsed_time );

    RenderLayerPtr map_layer( );
    RenderLayerPtr map_objects_layer( );
    RenderLayerPtr coins_layer( );
private:
    void on_map_instance_changed( MapInstanceConstPtr new_map_instance );
};

#endif // CONTROLLER_HPP
