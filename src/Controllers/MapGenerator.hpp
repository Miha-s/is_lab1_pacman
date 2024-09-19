#ifndef MAPGENERATOR_HPP
#define MAPGENERATOR_HPP

#include "./PseudoRandomGenerator.hpp"
#include "MapElements/MapInstance.hpp"

class MapGenerator
{
    PseudoRandomGeneratorConstPtr m_random_generator;

public:
    MapGenerator( PseudoRandomGeneratorConstPtr random_generator );

    MapInstancePtr generate_map( const MapSize& map_size, const size_t level ) const;
private:
    void build_outer_walls( MapInstancePtr map_instance ) const;
    void generate_simple_map( MapInstancePtr map_instance ) const;
    void generate_ring_map( MapInstancePtr map_instance, const size_t level ) const;
    void generate_maze_map( MapInstancePtr map_instance, const size_t level ) const;
    void add_difficulty_maze_map( MapInstancePtr map_instance, const size_t level ) const;
    void remove_wall_in_between( MapInstancePtr map_instance,
                                 MapPosition pos1,
                                 MapPosition pos2 ) const;
    void cut_rectangle( MapInstancePtr map_instance, MapPosition pos1, MapPosition pos2 ) const;
    std::pair< MapPosition, MapPosition > get_top_left_bottom_right( MapPosition pos1,
                                                                     MapPosition pos2 ) const;
};

#endif  // MAPGENERATOR_HPP
