#include "Controller.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>


Controller::Controller( sf::RenderWindow& window, const MapSize& map_size )
    : m_game_engine{ map_size, 1 }
    , m_window{ window }
{
    const std::string coins_path = "assets/textures/dots.png";

    m_map_layer.reset( new MapLayer );
    m_map_objects_layer.reset( new MapObjectsLayer{ m_game_engine.entities_controller( ) } );
    m_coins_layer.reset( new CoinsLayer{ m_game_engine.coins_controller( ), coins_path } );

    m_game_engine.set_map_instance_callback( [ this ]( MapInstanceConstPtr map_instance )
                                             { on_map_instance_changed( map_instance ); } );

    m_game_engine.launch_level( 0 );
}

void
Controller::process_event( sf::Event event )
{
    if ( event.type == sf::Event::Closed )
    {
        m_window.close( );
        return;
    }

    m_game_engine.process_event( event );
}

void
Controller::poll( const sf::Time& elapsed_time )
{
    m_game_engine.poll( elapsed_time );
}

RenderLayerPtr
Controller::map_layer( )
{
    return m_map_layer;
}

RenderLayerPtr
Controller::map_objects_layer( )
{
    return m_map_objects_layer;
}

RenderLayerPtr
Controller::coins_layer( )
{
    return m_coins_layer;
}

void
Controller::on_map_instance_changed( MapInstanceConstPtr new_map_instance )
{
    m_map_layer->update_with_map_instance( new_map_instance );
    m_coins_layer->update_with_map_instance( new_map_instance );
}
