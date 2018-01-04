//
//  ElasticCollisionSim.hpp
//  ParticlesSim
//
//  Created by Bach Phan on 1/1/18.
//  Copyright © 2018 Bach Phan. All rights reserved.
//

#ifndef ElasticCollisionSim_hpp
#define ElasticCollisionSim_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <iostream>
#include <math.h>

constexpr float particleRadius{1.f};
constexpr int windowWidth{800}, windowHeight{600};

struct Bar{
    sf::Vertex line[2];
    sf::Color color = sf::Color::Blue;
    Bar() : line{
            sf::Vertex(sf::Vector2f(0, 10), color),
            sf::Vertex(sf::Vector2f(windowWidth, 10), color)
    } {};
    void draw(sf::RenderWindow &window);
};

struct Particle{
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

class ParticleSystem{
    
    int mapHeight;
    int mapWidth;
public:
    typedef std::uniform_real_distribution<> UniRealDist;
    typedef std::uniform_int_distribution<> UniIntDist;
    typedef std::shared_ptr<Particle> ParticlePtr;
    typedef std::vector<ParticlePtr>::iterator ParticlePtrIter;
    
    std::vector<ParticlePtr> particleSystem;
    
    ParticleSystem(sf::Vector2u canvasSize){
        mapHeight = canvasSize.y;
        mapWidth = canvasSize.x;
        //std::cout << mapWidth << ' ' << mapHeight << std::endl;
    }
    
    void spawn(int n);
    void draw(sf::RenderWindow &window);
    void collide(ParticlePtr& p1, ParticlePtr& p2);
    void resetDefaultColor();
private:
    float dotProduct(sf::Vector2f v1, sf::Vector2f v2);
};
#endif /* ElasticCollisionSim_hpp */
