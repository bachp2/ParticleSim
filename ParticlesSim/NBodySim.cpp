//
//  NBodySim.cpp
//  ParticlesSim
//
//  Created by Bach Phan on 1/1/18.
//  Copyright © 2018 Bach Phan. All rights reserved.
//

#include "NBodySim.hpp"

void NBody::spawn(int n){
    int radii[4] = {1, 2, 3, 5};
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
        std::random_shuffle(&radii[0], &radii[3]);
        
        ParticlePtr b( new Particle(randomPosX(gen), randomPosY(gen), (float) radii[0], r*5 ));
        sf::Vector2f velocity(randomVel(gen), randomVel(gen));
        if(velocity.x == 0.0f && velocity.y == 0.0f) {
            return;
        }
        b->velocity = velocity;
        nbodySystem.push_back(b);
        
        //init Barnes_hut tree
        float midx, midy;
        midx = windowWidth*1.0f/2;
        midy = windowHeight*1.0f/2;
        root = std::make_shared<Quadtree>(0, Boundary(midx, midy, windowWidth, windowHeight));
    }
}
void NBody::applyForce(ParticlePtr& cueball, ParticlePtr& pocketball)
{
    float EPS = 100;
    auto d = pocketball->getPosition() - cueball->getPosition();
    auto dist = pocketball->get_distance(cueball);
    float F = (G * pocketball->mass * cueball->mass) / (dist*dist + EPS);
    cueball->force.x = F * d.x / dist;
    cueball->force.y = F * d.y / dist;
}

void NBody::update_physics(){
    root->clear();
    for(auto& p : nbodySystem){
        root->insert(p);
    }
    std::vector<ParticlePtr> returnObjPtrs;
    
    for(auto j = nbodySystem.begin(); j != nbodySystem.end(); ++j){
        //std::cout << &(*j) << std::endl;
        //assert(*j != nullptr);
        (*j)->reset_force();
        returnObjPtrs.clear();
        returnObjPtrs = root->retrieve(returnObjPtrs, *j);
        auto duplicate = std::find(returnObjPtrs.begin(), returnObjPtrs.end(), *j);
        if(duplicate != returnObjPtrs.end()) returnObjPtrs.erase(duplicate);
        for(auto i = returnObjPtrs.begin(); i != returnObjPtrs.end(); i++){
            if( (*j)->contact(**i) ) {
                auto smaller_particle = return_smaller_particle(*j, *i);
                if(smaller_particle == *i){
                    (*j)->consume(*i);
                }
                else{
                    (*i)->consume(*j);
                }
            }
            else if( !(*j)->isDestroyed || !(*i)->isDestroyed ) applyForce(*j, *i);
        }
    }
    clean_up_dead_particles();
    for(const auto& p : nbodySystem){
        p->update_velocity(dt);
    }

}

void NBody::draw(sf::RenderWindow &window){
    update_physics();
    
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
