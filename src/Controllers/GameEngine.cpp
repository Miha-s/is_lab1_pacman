#include "GameEngine.hpp"

#include <string>
#include <unordered_map>
#include "Algorithms/DijkstraSearchAlgorithm.hpp"

const std::unordered_map< sf::Keyboard::Key, MoveDirection > ArrowMoveDirection = {
    { sf::Keyboard::Right, MoveDirection::RIGHT },
    { sf::Keyboard::Left, MoveDirection::LEFT },
    { sf::Keyboard::Up, MoveDirection::UP },
    { sf::Keyboard::Down, MoveDirection::DOWN }
};

const std::unordered_map< sf::Keyboard::Key, size_t > NumKeyNumber = {
    { sf::Keyboard::Num0, 0 }, { sf::Keyboard::Num1, 1 }, { sf::Keyboard::Num2, 2 },
    { sf::Keyboard::Num3, 3 }, { sf::Keyboard::Num4, 4 }, { sf::Keyboard::Num5, 5 },
    { sf::Keyboard::Num6, 6 }, { sf::Keyboard::Num7, 7 }, { sf::Keyboard::Num8, 8 },
    { sf::Keyboard::Num9, 9 }
};

GameEngine::GameEngine( const MapSize& map_size, const size_t seed )
    : m_map_size{ map_size }
    , m_random_generator_for_map{ std::make_shared< PseudoRandomGenerator >( seed ) }
    , m_random_generator_for_entities{ std::make_shared< PseudoRandomGenerator >( seed ) }
    , m_map_generator{ m_random_generator_for_map }

{
    const std::string sprites_path = "assets/textures/sprites.png";

    m_coins_controller.reset( new CoinsController );
    m_entities_controller.reset( new EntitiesController{ sprites_path,
                                                         m_random_generator_for_entities,
                                                         m_coins_controller } );
}

void
GameEngine::launch_level( const size_t level )
{
    m_current_level = level;
    reload_level( );
}

void
GameEngine::reload_level( )
{
    m_map_instance = m_map_generator.generate_map( m_map_size, m_current_level );
    m_entities_controller->reset( m_map_instance );
    m_coins_controller->reset( m_map_instance );
    m_coins_controller->set_collidable( m_entities_controller->pacman( )->map_object( ) );

    if ( m_map_instance_callback )
    {
        m_map_instance_callback( m_map_instance );
    }
}

void
GameEngine::process_event( sf::Event event )
{
    if ( event.type == sf::Event::KeyPressed )
    {
        auto event_code = event.key.code;
        if ( event_code == sf::Keyboard::Enter )
        {
            reload_level( );
        }
        if ( ArrowMoveDirection.find( event_code ) != ArrowMoveDirection.end( ) )
        {
            m_entities_controller->move_requested( ArrowMoveDirection.at( event_code ) );
        }
        if ( NumKeyNumber.find( event_code ) != NumKeyNumber.end( ) )
        {
            launch_level( NumKeyNumber.at( event_code ) );
        }
    }
}

void
GameEngine::poll( const sf::Time& elapsed_time )
{
    if ( m_entities_controller->ghost_ate_pacman( ) || m_coins_controller->all_coins_collected( ) )
    {
        return;
    }

    m_coins_controller->poll( );
    m_entities_controller->poll( elapsed_time );
}

void
GameEngine::set_map_instance_callback( MapInstanceCallback callback )
{
    m_map_instance_callback = callback;
}

MapInstanceConstPtr
GameEngine::map_instance( )
{
    return m_map_instance;
}

CoinsControllerConstPtr
GameEngine::coins_controller( )
{
    return m_coins_controller;
}

EntitiesControllerConstPtr
GameEngine::entities_controller( )
{
    return m_entities_controller;
}
