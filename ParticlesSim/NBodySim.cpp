//
//  NBodySim.cpp
//  ParticlesSim
//
//  Created by Bach Phan on 1/1/18.
//  Copyright © 2018 Bach Phan. All rights reserved.
//

#include "NBodySim.hpp"

void NBody::spawn(int n){
    for(int i = 0; i < n; ++i){
        std::random_device rd;
        std::mt19937 gen(rd());
        //set velocity limit boundary
        UniRealDist randomVel(-3.0f, 3.0f);
        UniRealDist randomRad( 1.0f, 10.0f );
        UniRealDist randomMass( 1.0f, 10.0f );
        float r = randomRad(gen);
        UniRealDist randomPosX( r, mapWidth - r );
        UniRealDist randomPosY( r, mapHeight - r );
        
        BodyPtr b( new Body(randomPosX(gen), randomPosY(gen), r, randomMass(gen)) );
        sf::Vector2f velocity(randomVel(gen), randomVel(gen));
        if(velocity.x == 0.0f && velocity.y == 0.0f) {
            return;
        }
        b->velocity = velocity;
        nbodySystem.push_back(b);
    }
}
void NBody::applyGravAcc2System()
{
}
