#include "MapLayer.hpp"

MapLayer::MapLayer( )
{
}

void
MapLayer::update_with_map_instance( MapInstanceConstPtr map_instance )
{
    update_walls_recrangles( map_instance );
}

void
MapLayer::draw( sf::RenderTarget& render_target )
{
    for ( const auto& wall : m_walls )
    {
        render_target.draw( wall );
    }
}

void
MapLayer::update_walls_recrangles( MapInstanceConstPtr map_instance )
{
    m_walls.clear( );
    const auto& map_size = map_instance->size( );
    for ( size_t i = 0; i < map_size.height; i++ )
    {
        for ( size_t j = 0; j < map_size.width; j++ )
        {
            if ( map_instance->is_wall( { i, j } ) )
            {
                sf::RectangleShape new_wall{ sf::Vector2f{ map_size.block_width,
                                                           map_size.block_height } };
                new_wall.setPosition( j * map_size.block_width, i * map_size.block_height );
                m_walls.push_back( new_wall );
            }
        }
    }
}
