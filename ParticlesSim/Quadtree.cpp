//
//  Quadtree.cpp
//  ParticlesSim
//
//  Created by Bach Phan on 1/3/18.
//  Copyright © 2018 Bach Phan. All rights reserved.
//

#include "Quadtree.hpp"
#include <assert.h>
void Quadtree::clear(){
    entities.clear();
    for (int i = 0; i < 4; i++) {
        if (nodes[i] != nullptr) {
            nodes[i]->clear();
            nodes[i] = nullptr;
        }
    }
}
void Quadtree::split(){
    float subWidth = bounds.width/2;
    float subHeight = bounds.height/2;
    float midx = bounds.midx;
    float midy = bounds.midy;
    QuadtreePtr q1(new Quadtree(level+1, Boundary(midx - subWidth/2, midy - subHeight/2, subWidth, subHeight)));//top left
    QuadtreePtr q2(new Quadtree(level+1, Boundary(midx + subWidth/2, midy + subHeight/2, subWidth, subHeight)));//bottom right
    QuadtreePtr q3(new Quadtree(level+1, Boundary(midx - subWidth/2, midy + subHeight/2, subWidth, subHeight)));//bottom left
    QuadtreePtr q4(new Quadtree(level+1, Boundary(midx + subWidth/2, midy - subHeight/2, subWidth, subHeight)));//top right
    nodes[0] = q1;
    nodes[1] = q2;
    nodes[2] = q3;
    nodes[3] = q4;
    //assert(empty());
}

int Quadtree::getIndex(Particle::ParticlePtr p){
    int index = -1;
    float verticalMidpoint = bounds.midx;
    float horizontalMidpoint = bounds.midy;
    // Object can completely fit within the top quadrants
    bool topQuad = (p->y() + p->radius() < horizontalMidpoint);
    // Object can completely fit within the bottom quadrants
    bool bottomQuad = (p->y() - p->radius() > horizontalMidpoint);
    // Object can completely fit within the left quadrants
    bool leftQuad = (p->x() + p->radius() < verticalMidpoint);
    // Object can completely fit within the right quadrants
    bool rightQuad = (p->x() + p->radius() > verticalMidpoint);
    
    if(topQuad && leftQuad) index = 0;
    else if(topQuad && rightQuad) index = 3;
    else if(bottomQuad && rightQuad) index = 1;
    else if (bottomQuad && leftQuad) index = 2;
    return index;
}

void Quadtree::insert(Particle::ParticlePtr& p){
    if (nodes[0] != nullptr) {
        int index = getIndex(p);
        if (index != -1) {
            nodes[index]->insert(p);
            return;
        }
    }
    entities.push_back(p);
    
    if (entities.size() > MAX_OBJECTS && level < MAX_LEVELS) {
        if (nodes[0] == nullptr) split();
        
        int i = 0;
        while (i < entities.size()) {
            int index = getIndex(entities[i]);
            //std::cout << index << std::endl;
            if (index != -1) {
                nodes[index]->insert(entities[i]);
                entities.erase(entities.begin()+i);
            }
            else i++;
        }
    }
}

std::vector<Particle::ParticlePtr>& Quadtree::retrieve(std::vector<Particle::ParticlePtr>& returnObjPtrs, Particle::ParticlePtr& p){
    int index = getIndex(p);
    if (index != -1 && nodes[0] != nullptr) {
        nodes[index]->retrieve(returnObjPtrs, p);
    }
    returnObjPtrs.insert(returnObjPtrs.end(), this->entities.begin(), this->entities.end());
    return returnObjPtrs;
}
void Quadtree::traverseTree(size_t& sum){
    std::cout << this->entities.size() << " level: " << this->level << " boundary " << this->bounds.midx - bounds.width/2 << "->" << this->bounds.midx + bounds.width/2 << ',' << this->bounds.midy - bounds.height/2 << "->" << this->bounds.midy + bounds.height/2 << std::endl;
    sum += this->entities.size();
    for (int i = 0; i < 4; i++){
        if (nodes[i] != nullptr) {
            nodes[i]->traverseTree(sum);
        }
    }
}
