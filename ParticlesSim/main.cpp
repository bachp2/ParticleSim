
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
/*
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

    return EXIT_SUCCESS;
}
*/

//test main
int main(int, char const**){
    sf::Vector2u window_size(1000,1000);
    ParticleSystem system(window_size);
    system.spawn(10);
    system.print_particle_position(system.particleSystem);
    printf("\n");
    //system.root->clear();
    //assert(root->MAX_OBJECTS == 10);
    //assert(root->empty());
    auto midx = window_size.x*1.0f/2;
    auto midy = window_size.y*1.0f/2;
    
    auto root = std::make_shared<Quadtree>(0, Boundary(midx, midy, window_size.x, window_size.y));
    assert(root != nullptr);
    //insert object through pointer
    for(auto& p : system.particleSystem){
        //printf("%p", &(*p));
        root->insert(p);
    }
    system.print_particle_position(root);

//    //    size_t sum = 0;
//    //    root->traverseTree(sum);
//    std::vector<std::shared_ptr<Particle>> returnObjPtrs;
//
//    for(auto j = system.particleSystem.begin(); j != system.particleSystem.end(); j++){
//        //std::cout << &(*j) << std::endl;
//        returnObjPtrs.clear();
//        //assert(!returnObjPtrs.empty());
//        system.root->retrieve(returnObjPtrs, *j);
//        //assert(!returnObjPtrs.empty());
//        //assert(returnObjPtrs.size() != 1000);
//        //std::cout << *j << " position: " << (*j)->shape.getRadius() << ' ' << (*j)->shape.getPosition().x << std::endl;
//        for(auto i = returnObjPtrs.begin(); i != returnObjPtrs.end(); i++){
//            if( (*j)->contact(**i) ) {
//                //(*j)->setColor(sf::Color::Red);
//                //(*i)->setColor(sf::Color::Red);
//                //std::cout << "collision" << std::endl;
//                //collide(*i, *j);
//                std::cout << *i << " position: " << (*i)->shape.getRadius() << ' ' << (*i)->shape.getPosition().x << std::endl;
//                while( (*j)->contact(**i) ){
//                    (*j)->shape.move( (*j)->velocity );
//                    (*i)->shape.move( (*i)->velocity );
//                }
//            }
//        }
    return 0;
}

