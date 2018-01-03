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

struct Body : Particle
{
    float mass;
    sf::Vector2f acceleration;
    Body() : acceleration{0.0f,0.0f}, mass{1.0f}
    {
        shape.setRadius(1.0f);
    };
};

class NBody
{
    int mapHeight, mapWidth;
    typedef std::shared_ptr<Body> BodyPtr;
    typedef std::set<BodyPtr>::iterator BodyPtrIter;
    std::set<Body> nbodySystem;
    
public:
    NBody();
    NBody(sf::Vector2u canvasSize){
        mapHeight = canvasSize.y;
        mapWidth = canvasSize.x;
        //std::cout << mapWidth << ' ' << mapHeight << std::endl;
    }
    ~NBody();
    sf::Vector2f getUnitDistanceVector(BodyPtr& b1, BodyPtr& b2){
        float distance = b2->getDistance(*b1);
        return (b2->getPosition() - b1->getPosition())/distance;
    };
    void spawn(int n);
    void update();
    void draw(sf::RenderWindow &window);
    void collide(BodyPtr& b1, BodyPtr& b2);
    void applyGravAcc2System();
    
};
#endif /* NBodySim_hpp */
