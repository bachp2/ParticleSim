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
    sf::Vector2f force;
    float mass;
    
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
    
    Particle(float x, float y, float r, float m){
        isDestroyed = false;
        shape.setPosition(x, y);
        shape.setRadius(r);
        shape.setFillColor(sf::Color::Blue);
        shape.setOrigin(particleRadius, particleRadius);
        mass = m;
        force = sf::Vector2f(0,0);
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
    
    void set_radius(float r){
        this->shape.setRadius(r);
    }
    void consume(ParticlePtr p){
        this->set_radius( p->radius() + this->radius() );
        this->mass += p->mass;
    }
    void reset_force(){
        force.x = 0; force.y = 0;
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
    
    void update_velocity(float dt){
        velocity += dt * force / mass;
    }
    
    bool contact(Particle& p){
        sf::Vector2f dxdy = this->getPosition() - p.getPosition();
        return pow(dxdy.x,2) + pow(dxdy.y,2) < pow(this->shape.getRadius() + p.shape.getRadius(), 2);
    }
    //square distance from a point
    float get_square_distance(float ox , float oy){
        auto particle_pos = shape.getPosition();
        return pow(particle_pos.x - ox,2) + pow(particle_pos.y - oy,2);
    }
    
    float get_square_distance(ParticlePtr& p){
        auto particle1_pos = this->getPosition();
        auto particle2_pos = p->getPosition();
        return pow(particle1_pos.x - particle2_pos.x,2) + pow(particle1_pos.y - particle2_pos.y,2);
    }
    
    float get_distance(ParticlePtr& p){
        return sqrt(get_square_distance(p));
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
