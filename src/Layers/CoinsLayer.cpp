#include "CoinsLayer.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <iostream>

#include "MapElements/SpriteObject.hpp"

CoinsLayer::CoinsLayer( CoinsControllerConstPtr coins_controller, const std::string& coins_path )
    : m_coins_controller{ coins_controller }
{
    auto texture = std::make_unique< sf::Texture >( );
    sf::IntRect location = { 6, 6, 2, 2 };
    if ( !texture->loadFromFile( coins_path, location ) )
    {
        std::cout << "Failed to load coin texture" << std::endl;
    }

    std::vector< sf::IntRect > sprite_states = { { 0, 0, 2, 2 } };
    m_coin_object = std::make_shared< SpriteObject >( std::move( texture ), sprite_states );
}

void
CoinsLayer::update_with_map_instance( MapInstanceConstPtr map_instance )
{
    m_map_instance = map_instance;
}

void
CoinsLayer::draw( sf::RenderTarget& render_target )
{
    auto map_size = m_map_instance->size( );
    for ( size_t row = 0; row < map_size.height; row++ )
        for ( size_t col = 0; col < map_size.width; col++ )
        {
            if ( m_coins_controller->is_coin( { row, col } ) )
            {
                m_map_instance->position_object_at( *m_coin_object, { row, col } );
                render_target.draw( *m_coin_object );
            }
        }
}
