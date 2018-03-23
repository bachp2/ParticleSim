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

const int MAX_RADIUS = 7;

using namespace sf;
struct tPoint{
    Vector2f position;
    bool is_teleported;
    tPoint(Vector2f p){
        position = p;
    }
};
struct Trail{
    static const int MAX_RESOLUTION = 50;
    std::deque<tPoint> trail;
    void update_shape(Vector2f last_particle_position, bool is_teleported){
        if(trail.size() == MAX_RESOLUTION) trail.pop_front();
        auto tmp = tPoint(last_particle_position);
        tmp.is_teleported = is_teleported;
        trail.push_back(tmp);
    }
    void draw(RenderWindow &window){
        //if(trail.size() == 1) return;
        VertexArray lines(LinesStrip, trail.size());
        int i = 0;
        int disjoint = 0;
        for(auto& point : trail){
            if(point.is_teleported) disjoint = i;
            lines[i].position = point.position;
            lines[i].color = Color::Magenta;
            i++;
        }
        
        if(disjoint){
            VertexArray segment1(LinesStrip, disjoint);
            VertexArray segment2(LinesStrip, trail.size() - disjoint);
            for(int i = 0; i < disjoint; i++){
                segment1[i].position = lines[i].position;
                segment1[i].color = lines[i].color;
            }
            for(int i = 0; i < trail.size() - disjoint; i++){
                segment2[i].position = lines[disjoint + i].position;
                segment2[i].color = lines[disjoint + i].color;
            }
            window.draw(segment1);
            window.draw(segment2);
        }
        else window.draw(lines);
    }
};

struct Particle{
    static const std::size_t DEFAULT_POINT_COUNT = 10;
    typedef std::uniform_real_distribution<> UniRealDist;
    typedef std::uniform_int_distribution<> UniIntDist;
    typedef std::shared_ptr<Particle> ParticlePtr;
    typedef std::vector<ParticlePtr>::iterator ParticlePtrIter;
    CircleShape shape;
    bool isDestroyed;
    Vector2f velocity;
    Vector2f force;
    float mass;
    Trail trail;
    //sf::Vector2f acceleration;
    Particle() : isDestroyed{false} {};
    Particle(float x, float y){
        isDestroyed = false;
        shape.setPosition(x, y);
        shape.setRadius(particleRadius);
        //shape.setFillColor(sf::Color(169,169,169));
        shape.setFillColor(sf::Color::Blue);
        shape.setPointCount(10);
        shape.setOrigin(particleRadius, particleRadius);
    }
    ~Particle(){
        
    }
    Particle(float x, float y, float r, float m){
        isDestroyed = false;
        shape.setPosition(x, y);
        shape.setRadius(r);
        shape.setFillColor(sf::Color::Blue);
        shape.setOrigin(r, r);
        shape.setPointCount(10);
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
    //i have to think more about the momentum of particle on impact with consumed particle
    //TODO: refine this subrotine to be physically correct
    void consume(ParticlePtr& p){
        auto new_r = p->radius() + this->radius();
        if(new_r < MAX_RADIUS){
            this->set_radius( new_r );
            shape.setOrigin(new_r, new_r);
        }
        else shape.setFillColor(sf::Color::Black);
        
        auto old_mass = this->mass;
        this->mass += p->mass;
        auto momentum_before_impact = old_mass * this->velocity + p->mass * p->velocity;
        this->velocity = momentum_before_impact/this->mass;
        p->isDestroyed = true;
    }
   
    void reset_force(){
        force.x = 0; force.y = 0;
    }
    void setPosition(sf::Vector2f newPos){
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
        Vector2f dxdy = this->getPosition() - p.getPosition();
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
