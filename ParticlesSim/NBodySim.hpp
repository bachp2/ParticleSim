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

struct Body : Particle
{
    float mass;
    sf::Vector2f acceleration;
    Body(float x, float y, float r) : acceleration{0.0f,0.0f}, mass{1.0f}
    {
        isDestroyed = false;
        shape.setPosition(x, y);
        shape.setRadius(r);
        shape.setFillColor(sf::Color(169,169,169));
        shape.setOrigin(r, r);
    };
    Body(float x, float y, float r, float m) : acceleration{0.0f,0.0f}
    {
        mass = m;
        isDestroyed = false;
        shape.setPosition(x, y);
        shape.setRadius(r);
        shape.setFillColor(sf::Color(169,169,169));
        shape.setOrigin(r, r);
    };
};

class NBody
{
    int mapHeight, mapWidth;
    typedef std::uniform_real_distribution<> UniRealDist;
    typedef std::uniform_int_distribution<> UniIntDist;
    typedef std::shared_ptr<Body> BodyPtr;
    typedef std::vector<BodyPtr>::iterator BodyPtrIter;
    
    std::vector<BodyPtr> nbodySystem;
public:
    NBody(sf::Vector2u canvasSize){
        mapHeight = canvasSize.y;
        mapWidth = canvasSize.x;
        //std::cout << mapWidth << ' ' << mapHeight << std::endl;
    };
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
