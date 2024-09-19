#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <SFML/Window/Event.hpp>
#include <functional>

#include "./CoinsController.hpp"
#include "./EntitiesController.hpp"
#include "Enumerations.hpp"
#include "MapGenerator.hpp"
#include "PseudoRandomGenerator.hpp"

class GameEngine
{
    using MapInstanceCallback = std::function< void( MapInstanceConstPtr ) >;
    const MapSize m_map_size;
    size_t m_current_level;

    PseudoRandomGeneratorConstPtr m_random_generator_for_map;
    PseudoRandomGeneratorConstPtr m_random_generator_for_entities;
    MapGenerator m_map_generator;
    MapInstancePtr m_map_instance;
    CoinsControllerPtr m_coins_controller;
    EntitiesControllerPtr m_entities_controller;

    MapInstanceCallback m_map_instance_callback;

public:
    GameEngine( const MapSize& map_size, const size_t seed );

    void launch_level( const size_t level );
    void reload_level( );

    void process_event( sf::Event event );
    void poll( const sf::Time& elapsed_time );

    void set_map_instance_callback( MapInstanceCallback callback );

    MapInstanceConstPtr map_instance( );
    CoinsControllerConstPtr coins_controller( );
    EntitiesControllerConstPtr entities_controller( );

};

#endif // GAMEENGINE_HPP
