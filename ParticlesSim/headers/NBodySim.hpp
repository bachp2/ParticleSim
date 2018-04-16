//
//  NBodySim.hpp
//  ParticlesSim
//
//  Created by Bach Phan on 1/1/18.
//  Copyright © 2018 Bach Phan. All rights reserved.
//

#ifndef NBodySim_hpp
#define NBodySim_hpp

#include <stdio.h>
#include "ElasticCollisionSim.hpp"
#include "ResourcePath.hpp"
#include "Particle.hpp"

class NBody
{
    TileMap tiles;
    const float dt = 1.0f/200.0f;
    const float G = 10.f;
    int mapHeight, mapWidth;
    std::shared_ptr<Quadtree> root;
    typedef std::uniform_real_distribution<> UniRealDist;
    typedef std::uniform_int_distribution<> UniIntDist;
    typedef std::shared_ptr<Particle> ParticlePtr;
    typedef std::vector<ParticlePtr>::iterator ParticlePtrIter;
    std::vector<ParticlePtr> nbodySystem;
public:
    NBody(sf::Vector2u canvasSize){
        mapHeight = canvasSize.y;
        mapWidth = canvasSize.x;
        tiles.init("grid.png", mapWidth, mapHeight, 50);
    };
    
    void spawn(int n);
    void update_physics();
    void draw(sf::RenderWindow &window);
    void applyForce(ParticlePtr& cueball, ParticlePtr& pocketball);
    void clean_up_dead_particles(){
        nbodySystem.erase(
                     std::remove_if(nbodySystem.begin(), nbodySystem.end(),
                                    [](const ParticlePtr & o) { return o->isDestroyed; }),
                     nbodySystem.end());
    }
    ParticlePtr& return_smaller_particle(ParticlePtr& p1, ParticlePtr& p2){
        if(p1->mass >= p2->mass) return p2;
        else return p1;
    };
};
#endif /* NBodySim_hpp */
