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

//class NBody: ParticleSystem<Body>
//{
//    sf::Vector2f getUnitDistanceVector(Body& b1, Body& b2){
//        float distance = b2.getDistance(b1);
//        return (b2.getPosition() - b1.getPosition())/distance;
//    };
//    sf::Vector2f getNBodyGravitationalAcc(){
//        float sum = 0;
//    };
//};
#endif /* NBodySim_hpp */
