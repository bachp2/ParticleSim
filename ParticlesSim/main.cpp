
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <iostream>
#include <math.h>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "ElasticCollisionSim.hpp"
int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode{windowWidth,windowHeight}, "Particles Simulation", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(120);
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    ParticleSystem system(window.getSize());
    Bar piston;
    system.spawn(100);
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        // Clear screen
        window.clear(sf::Color::White);
        //draw particles
        piston.draw(window);
        system.draw(window);
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
