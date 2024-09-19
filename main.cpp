#include <Controllers/Controller.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Renderer.hpp"

int
main( )
{
    // create the window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;

    const MapSize map_size{ 49, 25, 35, 35 };

    sf::RenderWindow window( sf::VideoMode( map_size.width * map_size.block_width,
                                            map_size.height * map_size.block_height ),
                             "Pacman",
                             sf::Style::Default,
                             settings );

    window.setFramerateLimit( 60 );
    Controller controller( window, map_size );

    Renderer renderer;
    renderer.add_layer( controller.map_layer( ) );
    renderer.add_layer( controller.coins_layer( ) );
    renderer.add_layer( controller.map_objects_layer( ) );

    sf::Clock clock;

    // run the program as long as the window is open
    while ( window.isOpen( ) )
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while ( window.pollEvent( event ) )
        {
            controller.process_event( event );
        }

        controller.poll( clock.restart( ) );

        renderer.render( window );
    }

    return 0;
}
