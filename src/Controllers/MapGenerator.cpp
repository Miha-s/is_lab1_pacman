#include "MapGenerator.hpp"
#include <stack>
#include <unordered_set>

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
        generate_maze_map( map_instance, level );
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

std::vector< MapPosition >
get_unvisited_neighbors(
        MapInstancePtr map_instance,
        MapPosition cell,
        const std::unordered_set< MapPosition, MapPosition::HashFunction >& visited_positions )
{
    const MapSize& map_size = map_instance->size( );

    std::vector< MapPosition > neighbors;
    std::vector< std::pair< long, long > > directions = { { -2, 0 },
                                                          { 2, 0 },
                                                          { 0, -2 },
                                                          { 0, 2 } };

    for ( const auto& d : directions )
    {
        long nx = d.first + long( cell.col );
        long ny = d.second + long( cell.row );
        if ( nx < 0 || ny < 0 || nx >= map_size.width || ny >= map_size.height )
        {
            continue;
        }
        MapPosition new_mp{ size_t( ny ), size_t( nx ) };
        if ( visited_positions.count( new_mp ) )
        {
            continue;
        }
        neighbors.push_back( new_mp );
    }

    return neighbors;
}



void
MapGenerator::generate_maze_map( MapInstancePtr map_instance, const size_t level ) const
{
    const MapSize& map_size = map_instance->size( );

    for ( size_t row = 0; row < map_size.height; row++ )
        for ( size_t col = 0; col < map_size.width; col++ )
        {
            if ( row % 2 == 1 && col % 2 == 1 )
            {
                continue;
            }
            map_instance->set_wall( row, col );
        }

    std::unordered_set< MapPosition, MapPosition::HashFunction > visited_positions;

    std::stack< MapPosition > stack;
    stack.push( { 1, 1 } );

    while ( stack.size( ) )
    {
        auto current = stack.top( );
        visited_positions.insert( current );

        auto neighbors = get_unvisited_neighbors( map_instance, current, visited_positions );

        if ( neighbors.empty( ) )
        {
            stack.pop( );
            continue;
        }

        auto selected_dir = m_random_generator->rand( neighbors.size( ) - 1 );
        remove_wall_in_between( map_instance, current, neighbors[ selected_dir ] );
        stack.push( neighbors[ selected_dir ] );
    }

    add_difficulty_maze_map( map_instance, level );
}

void
MapGenerator::add_difficulty_maze_map( MapInstancePtr map_instance, const size_t level ) const
{
    auto map_size = map_instance->size( );
    auto extra_paths = 0;
    if ( level <= 3 )
    {
        extra_paths = map_size.height * 5;
    }
    else if ( level <= 5 )
    {
        extra_paths = map_size.height * 3;
    }
    else
    {
        extra_paths = map_size.height * 2;
    }

    auto inserted_paths = 0;
    while ( inserted_paths < extra_paths )
    {
        auto row = m_random_generator->rand( 1, map_size.height - 2 );
        auto col = m_random_generator->rand( 1, map_size.width - 2 );
        MapPosition pos{ row, col };
        if ( map_instance->is_wall( pos ) )
        {
            map_instance->remove_wall( pos );
            inserted_paths++;
        }
    }
}

void
MapGenerator::remove_wall_in_between( MapInstancePtr map_instance,
                                      MapPosition pos1,
                                      MapPosition pos2 ) const
{
    size_t x1, x2, y1, y2;
    x1 = pos1.col;
    y1 = pos1.row;
    x2 = pos2.col;
    y2 = pos2.row;

    map_instance->remove_wall( { ( y1 + y2 ) / 2, ( x1 + x2 ) / 2 } );
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
