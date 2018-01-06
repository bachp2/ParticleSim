//
//  Particle.cpp
//  ParticlesSim
//
//  Created by Bach Phan on 1/3/18.
//  Copyright © 2018 Bach Phan. All rights reserved.
//

#include <stdio.h>
#include "ResourcePath.hpp"

#ifndef Particle_hpp
#define Particle_hpp

struct Particle{
    typedef std::uniform_real_distribution<> UniRealDist;
    typedef std::uniform_int_distribution<> UniIntDist;
    typedef std::shared_ptr<Particle> ParticlePtr;
    typedef std::vector<ParticlePtr>::iterator ParticlePtrIter;
    
    sf::CircleShape shape;
    bool isDestroyed;
    sf::Vector2f velocity;
    //sf::Vector2f acceleration;
    Particle() : isDestroyed{false} {};
    Particle(float x, float y){
        isDestroyed = false;
        shape.setPosition(x, y);
        shape.setRadius(particleRadius);
        //shape.setFillColor(sf::Color(169,169,169));
        shape.setFillColor(sf::Color::Blue);
        shape.setOrigin(particleRadius, particleRadius);
    }
    float x() const {
        return this->shape.getPosition().x;
    }
    float y() const {
        return this->shape.getPosition().y;
    }
    sf::Vector2f getPosition() const {
        return this->shape.getPosition();
    }
    float radius() const {
        return this->shape.getRadius();
    }
    void setPosition(sf::Vector2f& newPos){
        shape.setPosition(newPos);
    }
    
    float left() const {
        return x() - shape.getRadius();
    }
    
    float right() const {
        return x() + shape.getRadius();
    }
    
    float top() const {
        return y() - shape.getRadius();
    }
    
    float bottom() const {
        return y() + shape.getRadius();
    }
    
    float getDistance(Particle& p) const {
        return sqrt( pow( p.x()-this->x(), 2) + pow( p.y()-this->y(), 2) );
    }
    
    bool contact(Particle& p){
        sf::Vector2f dxdy = this->getPosition() - p.getPosition();
        return pow(dxdy.x,2) + pow(dxdy.y,2) < pow(this->shape.getRadius() + p.shape.getRadius(), 2);
    }
    
    void setColor(sf::Color c){
        shape.setFillColor(c);
    }
    
    Particle(const Particle& p){
        isDestroyed = false;
        shape.setPosition(p.x(), p.y());
        shape.setRadius(particleRadius);
        shape.setFillColor(sf::Color::Blue);
        shape.setOrigin(particleRadius, particleRadius);
    }
};
#endif  
