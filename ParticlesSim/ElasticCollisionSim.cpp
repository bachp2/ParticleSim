//
//  ElasticCollisionSim.cpp
//  ParticlesSim
//
//  Created by Bach Phan on 1/1/18.
//  Copyright © 2018 Bach Phan. All rights reserved.
//

#include "ElasticCollisionSim.hpp"
typedef std::uniform_real_distribution<> UniRealDist;
typedef std::uniform_int_distribution<> UniIntDist;
typedef std::shared_ptr<Particle> ParticlePtr;
typedef std::vector<ParticlePtr>::iterator ParticleIter;

float ParticleSystem::dotProduct(sf::Vector2f v1, sf::Vector2f v2){
    return v1.x * v2.x + v2.y * v1.y;
}

void ParticleSystem::resetDefaultColor(){
    for(auto it = particleSystem.begin(); it != particleSystem.end(); ++it){
        (*it)->setColor(sf::Color::Blue);
    }
}


void ParticleSystem::spawn(int n){
    for(int i = 0; i < n; ++i){
        /* Randomizer initialization */
        std::random_device rd;
        std::mt19937 gen(rd());
        //set velocity limit boundary
        UniRealDist randomVel(-3.0f, 3.0f);
        UniRealDist randomPosX( particleRadius, mapWidth - particleRadius );
        UniRealDist randomPosY( particleRadius, mapHeight - particleRadius );
        ParticlePtr particle( new Particle( randomPosX(gen), randomPosY(gen) ) );
        sf::Vector2f velocity(randomVel(gen), randomVel(gen));
        if(velocity.x == 0.0f && velocity.y == 0.0f) {
            return;
        }
        particle->velocity = velocity;
        particleSystem.push_back(particle);
        //particle.reset();
    }
}
void ParticleSystem::draw(sf::RenderWindow &window){
    
    //resetDefaultColor();
    for(auto j = particleSystem.begin(); j != particleSystem.end(); j++){
        for(auto i = j+1; i != particleSystem.end(); i++){
            if( (*j)->contact(**i) ) {
                //(*j)->setColor(sf::Color::Red);
                //(*i)->setColor(sf::Color::Red);
                collide(*i, *j);
            }
            while( (*j)->contact(**i) ){
                (*j)->shape.move( (*j)->velocity );
                (*i)->shape.move( (*i)->velocity );
            }
        }
    }
    for(ParticlePtrIter it = particleSystem.begin(); it != particleSystem.end(); it++){
        auto p = *it;
        
        if( p->left() < 0.0f) p->velocity.x = abs(p->velocity.x);
        else if ( p->right() > mapWidth ) p->velocity.x = -abs(p->velocity.x);
        
        if( p->top() < 0.0f ) p->velocity.y = abs(p->velocity.y);
        else if( p->bottom() > mapHeight ) p->velocity.y = -abs(p->velocity.y);
        
        p->shape.move(p->velocity);
        
        window.draw( p->shape );
    }
}

void ParticleSystem::collide(ParticlePtr& p1, ParticlePtr& p2){
    auto v1 = p1->velocity;
    auto v2 = p2->velocity;
    auto r1 = p1->getPosition();
    auto r2 = p2->getPosition();
    auto dr = r1-r2;
    float dist_square = pow(dr.x,2) + pow(dr.y,2);
    //auto p12u = (r1-r2)/dist;
    //auto dv = float( dotProduct(v1-v2, r1-r2)/pow(dist,2) ) * (r1-r2);
    auto v1prime = v1 - float( dotProduct(v1-v2, r1-r2)/dist_square ) * (dr);
    auto v2prime = v2 - float( dotProduct(v2-v1, r2-r1)/dist_square ) * (-dr);
    p1->velocity = v1prime;
    p2->velocity = v2prime;
}

void Bar::draw(sf::RenderWindow &window){
    window.draw(line, 2, sf::Lines);
}

