//
//  ElasticCollisionSim.hpp
//  ParticlesSim
//
//  Created by Bach Phan on 1/1/18.
//  Copyright © 2018 Bach Phan. All rights reserved.
//

#ifndef ElasticCollisionSim_hpp
#define ElasticCollisionSim_hpp

#include <stdio.h>
#include "ResourcePath.hpp"
#include "Particle.hpp"
#include "Quadtree.hpp"

constexpr int windowWidth{800}, windowHeight{600};

//struct Bar{
//    sf::Vertex line[2];
//    sf::Color color = sf::Color::Blue;
//    Bar() : line{
//            sf::Vertex(sf::Vector2f(0, 10), color),
//            sf::Vertex(sf::Vector2f(windowWidth, 10), color)
//    } {};
//    void draw(sf::RenderWindow &window);
//};

namespace boundary_handle{
    inline void fixed_walls(Particle::ParticlePtr& p, int mapWidth, int mapHeight){
        if( p->left() < 0.0f) {
            p->velocity.x = abs(p->velocity.x);
        }
        else if ( p->right() > mapWidth ) {
            p->velocity.x = -abs(p->velocity.x);
        }
        if( p->top() < 0.0f ) {
            p->velocity.y = abs(p->velocity.y);
        }
        else if( p->bottom() > mapHeight ) {
            p->velocity.y = -abs(p->velocity.y);
        }
        p->shape.move(p->velocity);
        p->trail.update_shape(p->getPosition(), false);
    }
    
    inline void through_walls(Particle::ParticlePtr& p, int mapWidth, int mapHeight){
        float LP = 5.f;
        bool is_teleported = false;
        if( p->right() < 0.0f - LP) {
            p->setPosition(sf::Vector2f( mapWidth + abs(p->getPosition().x) , p->getPosition().y));
            is_teleported = true;
        }
        else if ( p->left() > mapWidth + LP ){
            p->setPosition(sf::Vector2f( mapWidth - abs(p->getPosition().x) , p->getPosition().y));
            is_teleported = true;
        }
        
        if( p->bottom() < 0.0f - LP){
            p->setPosition(sf::Vector2f( p->getPosition().x , mapHeight + abs(p->getPosition().y) ));
            is_teleported = true;
        }
        else if( p->top() > mapHeight + LP) {
            p->setPosition(sf::Vector2f( p->getPosition().x , mapHeight - abs(p->getPosition().y) ));
            is_teleported = true;
        }
        p->shape.move(p->velocity);
        p->trail.update_shape(p->getPosition(), is_teleported);
    }
};

class ParticleSystem{
    int mapHeight;
    int mapWidth;
public:
    std::shared_ptr<Quadtree> root;
    typedef std::uniform_real_distribution<> UniRealDist;
    typedef std::uniform_int_distribution<> UniIntDist;
    typedef std::shared_ptr<Particle> ParticlePtr;
    typedef std::vector<ParticlePtr>::iterator ParticlePtrIter;
    
    std::vector<ParticlePtr> particleSystem;
    
    ParticleSystem(sf::Vector2u canvasSize){
        mapHeight = canvasSize.y;
        mapWidth = canvasSize.x;
        //std::cout << mapWidth << ' ' << mapHeight << std::endl;
    }
    
    void spawn(int n);
    void draw(sf::RenderWindow &window);
    void collide(ParticlePtr& p1, ParticlePtr& p2);
    void resetDefaultColor();
    void print_particle_position(std::vector<ParticlePtr>& system);
    void print_particle_position(std::shared_ptr<Quadtree>& root);
private:
    float dotProduct(sf::Vector2f v1, sf::Vector2f v2);
    void bruteforce();
};
#endif /* ElasticCollisionSim_hpp */
