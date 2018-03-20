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
    const float G = 45.7f;
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
        //std::cout << mapWidth << ' ' << mapHeight << std::endl;
    };
    
    void spawn(int n);
    void update();
    void draw(sf::RenderWindow &window);
    void applyForce(ParticlePtr& particle, std::vector<ParticlePtr>& particles_in_range);
    
    ParticlePtr& return_smaller_particle(ParticlePtr& p1, ParticlePtr& p2){
        if(p1->mass >= p2->mass) return p2;
        else return p1;
    };
};
#endif /* NBodySim_hpp */
