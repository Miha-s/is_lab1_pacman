#include "DijkstraSearchAlgorithm.hpp"

#include <queue>
#include <unordered_set>
#include <iostream>
#include <algorithm>


struct VisitedPosition
{
    MapPosition pos;
    MapPosition prev;

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
DijkstraSearchAlgorithm::search_path(
        MapPosition start,
        std::function< bool( const MapPosition& pos ) > is_end,
        std::function< bool( const MapPosition& pos ) > is_blocked ) const
{
    std::unordered_set< VisitedPosition, VisitedPosition::HashFunction > visited_positions;
    std::unordered_set< VisitedPosition, VisitedPosition::HashFunction > positions_to_check_set;
    std::queue< VisitedPosition > positions_to_check;
    bool found_path = false;
    MapPosition end;

    positions_to_check.push( { start, start } );
    while ( !positions_to_check.empty( ) )
    {
        auto visited_pos = positions_to_check.front( );
        positions_to_check_set.erase( visited_pos );
        positions_to_check.pop( );
        visited_positions.insert( visited_pos );

        auto pos = visited_pos.pos;
        if ( is_end( pos ) )
        {
            end = pos;
            found_path = true;
            break;
        }

        std::vector< MapPosition > next_pos{ { pos.row, pos.col + 1 },
                                             { pos.row + 1, pos.col },
                                             { pos.row, pos.col - 1 },
                                             { pos.row - 1, pos.col } };

        for ( const auto& new_pos : next_pos )
        {
            if ( is_blocked( new_pos ) )
            {
                continue;
            }

            if ( visited_positions.count( { new_pos, 0 } ) > 0 )
            {
                continue;
            }

            if ( positions_to_check_set.count( { new_pos, 0 } ) > 0 )
            {
                continue;
            }

            positions_to_check.push( { new_pos, pos } );
            positions_to_check_set.insert( { new_pos, pos } );
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
