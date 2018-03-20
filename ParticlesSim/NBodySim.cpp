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
        //UniRealDist randomMass( 1.0f, 10.0f );
        float r = randomRad(gen);
        UniRealDist randomPosX( r, mapWidth - r );
        UniRealDist randomPosY( r, mapHeight - r );
        
        ParticlePtr b( new Particle(randomPosX(gen), randomPosY(gen), r, r*100 ));
        sf::Vector2f velocity(randomVel(gen), randomVel(gen));
        if(velocity.x == 0.0f && velocity.y == 0.0f) {
            return;
        }
        b->velocity = velocity;
        nbodySystem.push_back(b);
        std::shared_ptr<Quadtree> root;
    }
}
void NBody::applyForce(ParticlePtr& p, std::vector<ParticlePtr>& particles_in_range)
{
    float EPS = 15;
    p->force.x=0 ; p->force.y=0;
    for(auto o : particles_in_range){
        auto d = o->getPosition() - p->getPosition();
        auto dist = p->get_distance(o);
        float F = (G * p->mass * o->mass) / (dist*dist + EPS);
        p->force.x = F * d.x / dist;
        p->force.y = F * d.y / dist;
    }
}
void NBody::update(){
    root->clear();
    for(auto& p : nbodySystem){
        root->insert(p);
    }
    
    //    size_t sum = 0;
    //    root->traverseTree(sum);
    std::vector<ParticlePtr> returnObjPtrs;
    
    for(auto j = nbodySystem.begin(); j != nbodySystem.end(); j++){
        //std::cout << &(*j) << std::endl;
        returnObjPtrs.clear();
        //assert(!returnObjPtrs.empty());
        returnObjPtrs = root->retrieve(returnObjPtrs, *j);
        auto duplicate = std::find(returnObjPtrs.begin(), returnObjPtrs.end(), *j);
        if(duplicate != returnObjPtrs.end()) returnObjPtrs.erase(duplicate);
        //assert(!returnObjPtrs.empty());
        //assert(returnObjPtrs.size() != 1000);
        //std::cout << *j << " position: " << (*j)->shape.getRadius() << ' ' << (*j)->shape.getPosition().x << std::endl;
        for(auto i = returnObjPtrs.begin(); i != returnObjPtrs.end(); i++){
            
            if( (*j)->contact(**i) ) {
                auto smaller_particle = return_smaller_particle(*j, *i);
                if(smaller_particle == *i){
                    (*j)->mass += smaller_particle->mass;
                }
                else{
                    (*i)->mass += smaller_particle->mass;
                }
                auto consumed_particle = std::find(nbodySystem.begin(), nbodySystem.end(), smaller_particle);
                if(consumed_particle != returnObjPtrs.end()) nbodySystem.erase(consumed_particle);
            }
        }
    }
}

void NBody::draw(sf::RenderWindow &window){
    for(ParticlePtrIter it = nbodySystem.begin(); it != nbodySystem.end(); it++){
        auto p = *it;
        if( p->left() < 0.0f) p->velocity.x = abs(p->velocity.x);
        else if ( p->right() > mapWidth ) p->velocity.x = -abs(p->velocity.x);
        
        if( p->top() < 0.0f ) p->velocity.y = abs(p->velocity.y);
        else if( p->bottom() > mapHeight ) p->velocity.y = -abs(p->velocity.y);
        
        p->shape.move(p->velocity);
        window.draw( p->shape );
    }
    
}
