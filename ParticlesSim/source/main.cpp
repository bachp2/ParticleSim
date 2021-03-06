
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


// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "ElasticCollisionSim.hpp"
#include "NBodySim.hpp"
#include "ConicSections.hpp"
//#define DISPLAY_TRAIL_ON_PARTICLE

namespace test{
    void run_collision_test(){
        sf::Vector2u window_size(1000,1000);
        ParticleSystem system(window_size);
        system.spawn(100);
        system.print_particle_position(system.particleSystem);
        printf("\n");
        //system.root->clear();
        //assert(root->MAX_OBJECTS == 10);
        //assert(root->empty());
        auto midx = window_size.x*1.0f/2;
        auto midy = window_size.y*1.0f/2;
        
        system.root = std::make_shared<Quadtree>(0, Boundary(midx, midy, window_size.x, window_size.y));
        assert(system.root != nullptr);
        //insert object through pointer
        for(auto& p : system.particleSystem){
            //printf("%p", &(*p));
            system.root->insert(p);
        }
        system.print_particle_position(system.root);
        printf("\n");
        std::vector<std::shared_ptr<Particle>> returnObjPtrs;
        
        for(auto j = system.particleSystem.begin(); j != system.particleSystem.end(); j++){
            //std::cout << &(*j) << std::endl;
            returnObjPtrs.clear();
            returnObjPtrs = system.root->retrieve(returnObjPtrs, *j);
            auto duplicate = std::find(returnObjPtrs.begin(), returnObjPtrs.end(), *j);
            if(duplicate != returnObjPtrs.end()) returnObjPtrs.erase(duplicate);
            auto pos = (*j)->getPosition();
            printf("checking particle %p, x:%4.1f y:%4.1f\n", &(**j), pos.x, pos.y);
            system.print_particle_position(returnObjPtrs);
            printf("\n");
        }
    }
    
    void run_tilemaps_test(){
        sf::RenderWindow window(sf::VideoMode{windowWidth,windowHeight}, "Tilemap test", sf::Style::Titlebar | sf::Style::Close);
        sf::RectangleShape grid(sf::Vector2f(50.0f,50.0f));
        sf::RectangleShape grid1(sf::Vector2f(50.0f,50.0f));
        grid1.move(200.0f, 200.0f);
        //sf::RectangleShape grid2(sf::Vector2f(200.0f,200.0f));
        sf::Texture grid_texture;
        if ( !grid_texture.loadFromFile(resourcePath() + "grid.png") )
            return EXIT_FAILURE;
        grid.setTexture(&grid_texture);
        grid.setFillColor(sf::Color(255, 255, 255, 128));
        grid1.setTexture(&grid_texture);
        auto texture_size = grid_texture.getSize();
        texture_size.x /= 4;
        texture_size.y /= 4;
        grid.setTextureRect(sf::IntRect(texture_size.x, texture_size.y, texture_size.x, texture_size.y));
        grid1.setTextureRect(sf::IntRect(texture_size.x, texture_size.y, texture_size.x, texture_size.y));
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
            //draw entities
            window.draw(grid);
            window.draw(grid1);
            // Update the window
            window.display();
        }
        
    }
    
    void run_conic_sections_test(){
        sf::RenderWindow window(sf::VideoMode{windowWidth,windowHeight}, "Tilemap test", sf::Style::Titlebar | sf::Style::Close);
        ConicSections::init();
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
            //draw entities
            //ConicSections::draw_circle(window, 100, 100, 100);
            //ConicSections::draw_parabola(window, 100, 100, -25);
            ConicSections::draw_hyperbola(window, 100, 100, 75, 25);
            // Update the window
            window.display();
        }
    }
}

namespace sim{
    void elastic_collision(){
        // Create the main window
        sf::RenderWindow window(sf::VideoMode{windowWidth,windowHeight}, "Particles Simulation", sf::Style::Titlebar | sf::Style::Close);
        window.setFramerateLimit(120);
        
        // Set the Icon
//        sf::Image icon;
//        if (!icon.loadFromFile(resourcePath() + "icon.png")) {
//            return EXIT_FAILURE;
//        }
//        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
//
//
        ParticleSystem system(window.getSize());
        //Bar piston;
        system.spawn(1);
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
            //piston.draw(window);
            window.draw(system.tileMap);
            system.update_physics();
            window.draw(system);
            // Update the window
            window.display();
        }
    };
    
    void nbody(){
        // Create the main window
        sf::RenderWindow window(sf::VideoMode{windowWidth,windowHeight}, "Particles Simulation", sf::Style::Titlebar | sf::Style::Close);
        window.setFramerateLimit(60);
        
        NBody nbody_system(window.getSize());
        nbody_system.spawn(100);
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
            nbody_system.draw(window);
            // Update the window
            window.display();
        }
    }
}

int main(int, char const**)
{
    //test::run_test();
    //sim::elastic_collision();
    //sim::nbody();
    //test::run_tilemaps_test();
    test::run_conic_sections_test();
    return EXIT_SUCCESS;
}

