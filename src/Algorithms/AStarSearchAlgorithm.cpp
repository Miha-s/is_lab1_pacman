#include "AStarSearchAlgorithm.hpp"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <algorithm>

struct VisitedPosition
{
    MapPosition pos;
    MapPosition prev;
    size_t cost;

    bool
    operator==( const VisitedPosition& other ) const
    {
        return pos == other.pos;
    }

    struct HashFunction {
        size_t
        operator( )( const VisitedPosition& pos ) const
        {
            return MapPosition::HashFunction( )( pos.pos );
        }
    };
};


std::vector< MapPosition >
AStarSearchAlgorithm::search_path( MapPosition start,
                                   std::function< bool( const MapPosition& pos ) > is_end,
                                   std::function< bool( const MapPosition& pos ) > is_blocked ) const
{
    std::function< int( const MapPosition& pos ) > heuristic;
    auto compare = []( const VisitedPosition& lhs, const VisitedPosition& rhs )
    {
        return lhs.cost > rhs.cost;  // Min-heap based on the cost
    };

    std::priority_queue< VisitedPosition, std::vector< VisitedPosition >, decltype( compare ) >
            positions_to_check( compare );
    std::unordered_set< VisitedPosition, VisitedPosition::HashFunction > visited_positions;

    positions_to_check.push( { start, start, 0 } );

    std::unordered_map< MapPosition, size_t, MapPosition::HashFunction > g_cost;  // Cost to reach the
                                                                               // node
    g_cost[ start ] = 0;

    bool found_path = false;
    MapPosition end;

    while ( !positions_to_check.empty( ) )
    {
        auto visited_pos = positions_to_check.top( );
        positions_to_check.pop( );

        auto pos = visited_pos.pos;
        if ( is_end( pos ) )
        {
            end = pos;
            found_path = true;
            break;
        }

        if ( visited_positions.count( visited_pos ) > 0 )
        {
            continue;
        }
        visited_positions.insert( visited_pos );

        std::vector< MapPosition > next_pos{ { pos.row, pos.col + 1 },
                                             { pos.row + 1, pos.col },
                                             { pos.row, pos.col - 1 },
                                             { pos.row - 1, pos.col } };

        for ( const auto& new_pos : next_pos )
        {
            if ( is_blocked( new_pos ) || visited_positions.count( { new_pos, 0 } ) > 0 )
            {
                continue;
            }

            size_t new_g_cost = g_cost[ pos ] + 1;  // Assuming all edges have equal weight
            if ( g_cost.find( new_pos ) == g_cost.end( ) || new_g_cost < g_cost[ new_pos ] )
            {
                g_cost[ new_pos ] = new_g_cost;
                size_t f_cost = new_g_cost + heuristic( new_pos );  // g_cost + heuristic
                positions_to_check.push( { new_pos, pos, f_cost } );
            }
        }
    }

    if ( !found_path )
    {
        return { };
    }

    std::vector< MapPosition > result;
    result.push_back( end );
    while ( result.back( ) != start )
    {
        auto pos = visited_positions.find( { result.back( ), 0 } );
        if ( pos == visited_positions.end( ) )
        {
            std::cout << "Something has gone wrong" << std::endl;
            break;
        }
        result.push_back( pos->prev );
    }

    result.pop_back( );
    std::reverse( result.begin( ), result.end( ) );
    return result;
}
