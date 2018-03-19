//
//  ElasticCollisionSim.cpp
//  ParticlesSim
//
//  Created by Bach Phan on 1/1/18.
//  Copyright © 2018 Bach Phan. All rights reserved.
//

#include "ElasticCollisionSim.hpp"
#include <assert.h>
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
    float midx, midy;
    midx = windowWidth*1.0f/2;
    midy = windowHeight*1.0f/2;
    
    root = std::make_shared<Quadtree>(0, Boundary(midx, midy, windowWidth, windowHeight));
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
    //bruteforce();
    
    //quadtree optimization
    root->clear();
    //assert(root->MAX_OBJECTS == 10);
    //assert(root->empty());
    for(auto& p : particleSystem){
        root->insert(p);
    }

//    size_t sum = 0;
//    root->traverseTree(sum);
    std::vector<ParticlePtr> returnObjPtrs;

    for(auto j = particleSystem.begin(); j != particleSystem.end(); j++){
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
                //(*j)->setColor(sf::Color::Red);
                //(*i)->setColor(sf::Color::Red);
                //std::cout << "collision" << std::endl;
                collide(*i, *j);
                //std::cout << *i << " position: " << (*i)->shape.getRadius() << ' ' << (*i)->shape.getPosition().x << std::endl;
                while( (*j)->contact(**i) ){
                    (*j)->shape.move( (*j)->velocity );
                    (*i)->shape.move( (*i)->velocity );
                }
            }
        }
    }
    //std::cout << returnObjPtrs.size() << std::endl;
    //draw on screen
    //std::cout << &particleSystem[0] << std::endl;
    for(ParticlePtrIter it = particleSystem.begin(); it != particleSystem.end(); it++){
        auto p = *it;
        //std::cout << p << " position: " << p->shape.getPosition().y << ' ' << p->shape.getPosition().x << std::endl;
        if( p->left() < 0.0f) p->velocity.x = abs(p->velocity.x);
        else if ( p->right() > mapWidth ) p->velocity.x = -abs(p->velocity.x);

        if( p->top() < 0.0f ) p->velocity.y = abs(p->velocity.y);
        else if( p->bottom() > mapHeight ) p->velocity.y = -abs(p->velocity.y);

        p->shape.move(p->velocity);
        window.draw( p->shape );
    }
}

void ParticleSystem::testInsertion(){
    root->clear();
    //assert(root->empty());
    for(auto& p : particleSystem){
        root->insert(p);
    }
    size_t sum = 0;
    root->traverseTree(sum);
    std::cout << sum << std::endl;
}
void ParticleSystem::testInsertion1(){
    ParticlePtr p1( new Particle( 1, 12 ) );
    ParticlePtr p2( new Particle( 350, 350 ) );
    ParticlePtr p3( new Particle( 260, 350 ) );
    root->clear();
    //assert(root->empty());
    root->insert(p1);
    root->insert(p2);
    root->insert(p3);
    size_t sum = 0;
    root->traverseTree(sum);

//    ParticlePtr p4( new Particle( randomPosX(gen), randomPosY(gen) ) );
//    ParticlePtr p5( new Particle( randomPosX(gen), randomPosY(gen) ) );
//    ParticlePtr p6( new Particle( randomPosX(gen), randomPosY(gen) ) );
//    ParticlePtr p7( new Particle( randomPosX(gen), randomPosY(gen) ) );
//    ParticlePtr p8( new Particle( randomPosX(gen), randomPosY(gen) ) );
//    ParticlePtr p9( new Particle( randomPosX(gen), randomPosY(gen) ) );
//    ParticlePtr p10( new Particle( randomPosX(gen), randomPosY(gen) ) );
}
void ParticleSystem::bruteforce(){
    
    //resetDefaultColor();
    for(auto j = particleSystem.begin(); j != particleSystem.end(); j++){
        for(auto i = j+1; i != particleSystem.end(); i++){
            if( (*j)->contact(**i) ) {
                //(*j)->setColor(sf::Color::Red);
                //(*i)->setColor(sf::Color::Red);
                collide(*i, *j);
                while( (*j)->contact(**i) ){
                    (*j)->shape.move( (*j)->velocity );
                    (*i)->shape.move( (*i)->velocity );
                }
            }
        }
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
    auto v1prime = v1 - float( dotProduct(v1-v2, dr)/dist_square ) * (dr);
    auto v2prime = v2 - float( dotProduct(v2-v1, -dr)/dist_square ) * (-dr);
    p1->velocity = v1prime;
    p2->velocity = v2prime;
}

void ParticleSystem::print_particle_position(std::vector<ParticlePtr>& system){
    int i = 0;
    for(auto p : system){
        auto pos = p->getPosition();
        printf("count %d, particle %p, x:%4.1f y:%4.1f\n", i++, &(*p), pos.x, pos.y);
    }
}

void ParticleSystem::print_particle_position(std::shared_ptr<Quadtree>& root){
    //assert(root->entities.size() == 10);
    printf("%p level %d\n", &(*root), root->level);
    print_particle_position(root->entities);
    for (int i = 0; i < 4; i++) {
        if (root->nodes[i] != nullptr) {
            switch (i) {
                case 0:
                    printf("northwest\n");
                    break;
                case 1:
                    printf("southeast\n");
                    break;
                case 2:
                    printf("southwest\n");
                    break;
                case 3:
                    printf("northeast\n");
                    break;
            }
            print_particle_position(root->nodes[i]);
        }
    }
}
//void Bar::draw(sf::RenderWindow &window){
//    window.draw(line, 2, sf::Lines);
//}

