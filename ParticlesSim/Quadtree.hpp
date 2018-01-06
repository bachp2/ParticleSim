//
//  Quadtree.hpp
//  ParticlesSim
//
//  Created by Bach Phan on 1/3/18.
//  Copyright © 2018 Bach Phan. All rights reserved.
//

#ifndef Quadtree_hpp
#define Quadtree_hpp

#include <stdio.h>
#include "ResourcePath.hpp"
#include "Particle.hpp"
struct Boundary{
    float midx, midy, width, height;
    Boundary() : midx(0), midy(0), width(0), height(0) {};
    Boundary(float mx, float my, float w, float h){
        midx = mx;
        midy = my;
        width = w;
        height = h;
    }
};

class Quadtree{
    typedef std::shared_ptr<Particle> ParticlePtr;
    typedef std::vector<ParticlePtr>::iterator ParticlePtrIter;
    typedef std::shared_ptr<Quadtree> QuadtreePtr;
    const int MAX_OBJECTS = 10;
    const int MAX_LEVELS = 5;
    int level;
    std::vector<ParticlePtr> entities;
    Boundary bounds;
    QuadtreePtr nodes[4];
public:
    Quadtree() : bounds{0,0,0,0} {};
    Quadtree(int pLevel, Boundary b){
        level = pLevel;
        bounds = b;
    };
    void insert(Particle::ParticlePtr& p);
    std::vector<ParticlePtr>& retrieve(std::vector<ParticlePtr>& returnObjPtrs, ParticlePtr& p);
    void clear();
    void split();
    int getIndex(ParticlePtr p);
    bool empty(){
        return nodes[0] == nullptr;
    }
    void traverseTree(size_t& sum);
};
#endif /* Quadtree_hpp */
