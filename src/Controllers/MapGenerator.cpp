#include "MapGenerator.hpp"

MapGenerator::MapGenerator( PseudoRandomGeneratorConstPtr random_generator )
    : m_random_generator{ random_generator }
{
}

MapInstancePtr
MapGenerator::generate_map( const MapSize& map_size, const size_t level ) const
{
    auto map_instance = std::make_shared< MapInstance >( map_size, level );
    build_outer_walls( map_instance );

    if ( level == 0 )
    {
        generate_simple_map( map_instance );
    }
    else
    {
        generate_ring_map( map_instance, level );
    }

    return map_instance;
}

void
MapGenerator::build_outer_walls( MapInstancePtr map_instance ) const
{
    const MapSize& map_size = map_instance->size( );
    for ( size_t i = 0; i < map_size.width; i++ )
    {
        map_instance->set_wall( 0, i );
        map_instance->set_wall( map_size.height - 1, i );
    }

    for ( size_t i = 0; i < map_size.height; i++ )
    {
        map_instance->set_wall( i, 0 );
        map_instance->set_wall( i, map_size.width - 1 );
    }
}

void
MapGenerator::generate_simple_map( MapInstancePtr map_instance ) const
{
}

void
MapGenerator::generate_ring_map( MapInstancePtr map_instance, const size_t level ) const
{
    const MapSize& map_size = map_instance->size( );
    MapPosition top_left = { 1, 1 };
    MapPosition bottom_right = { map_size.height - 2, map_size.width - 2 };

    for ( size_t row = 0; row <= bottom_right.row; row++ )
        for ( size_t col = 0; col <= bottom_right.col; col++ )
        {
            map_instance->set_wall( row, col );
        }

    for ( size_t i = 0; i < 12; i++ )
    {
        MapPosition pos1 = { m_random_generator->rand( top_left.row, bottom_right.row ),
                             m_random_generator->rand( top_left.col, bottom_right.col ) };

        MapPosition pos2 = { m_random_generator->rand( 1, map_size.height - 2 ),
                             m_random_generator->rand( 1, map_size.width - 2 ) };

        cut_rectangle( map_instance, pos1, pos2 );

        auto new_limits = get_top_left_bottom_right( pos1, pos2 );
        top_left = new_limits.first;
        bottom_right = new_limits.second;
    }
}

void
MapGenerator::cut_rectangle( MapInstancePtr map_instance, MapPosition pos1, MapPosition pos2 ) const
{
    auto top_left_bottom_right = get_top_left_bottom_right( pos1, pos2 );
    auto top_left = top_left_bottom_right.first;
    auto bottom_right = top_left_bottom_right.second;

    for ( size_t row = top_left.row; row <= bottom_right.row; row++ )
    {
        map_instance->remove_wall( { row, top_left.col } );
        map_instance->remove_wall( { row, bottom_right.col } );
    }

    for ( size_t col = top_left.col; col <= bottom_right.col; col++ )
    {
        map_instance->remove_wall( { top_left.row, col } );
        map_instance->remove_wall( { bottom_right.row, col } );
    }
}

std::pair< MapPosition, MapPosition >
MapGenerator::get_top_left_bottom_right( MapPosition pos1, MapPosition pos2 ) const
{
    MapPosition top_left, bottom_right;
    top_left.row = pos1.row <= pos2.row ? pos1.row : pos2.row;
    top_left.col = pos1.col <= pos2.col ? pos1.col : pos2.col;

    bottom_right.row = pos1.row >= pos2.row ? pos1.row : pos2.row;
    bottom_right.col = pos1.col >= pos2.col ? pos1.col : pos2.col;

    return { top_left, bottom_right };
}
