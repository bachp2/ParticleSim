
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
namespace sim{
    void elastic_collision(){
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
        //Bar piston;
        system.spawn(1000);
        //system.testInsertion1();
        //system.testInsertion();
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
            system.draw(window);
            // Update the window
            window.display();
        }
    };
    
    void nbody_sim(){
        
    }
}

int main(int, char const**)
{
    sim::elastic_collision();

    return EXIT_SUCCESS;
}
 
//test main
/*
int main(int, char const**){
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
    
    return 0;
}
 */
