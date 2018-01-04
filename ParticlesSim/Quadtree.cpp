//
//  Quadtree.cpp
//  ParticlesSim
//
//  Created by Bach Phan on 1/3/18.
//  Copyright © 2018 Bach Phan. All rights reserved.
//

#include "Quadtree.hpp"

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
    QuadtreePtr q3(new Quadtree(level+1, Boundary(midx - subWidth/2, midy + subHeight/2, subWidth, subHeight)));//top right
    QuadtreePtr q4(new Quadtree(level+1, Boundary(midx + subWidth/2, midy - subHeight/2, subWidth, subHeight)));//bottom left
    nodes[0] = q1;
    nodes[1] = q2;
    nodes[2] = q3;
    nodes[3] = q4;
}

int Quadtree::getIndex(Particle::ParticlePtr p){
    int index = -1;
    float verticalMidpoint = bounds.midx;
    float horizontalMidpoint = bounds.midy;
    // Object can completely fit within the top quadrants
    bool topQuad = (p->y() < horizontalMidpoint && p->y() + p->radius() < horizontalMidpoint);
    bool bottomQuad = (p->y() - p->radius() >= horizontalMidpoint);
    bool leftQuad = (p->x() < verticalMidpoint && p->x() + p->radius() < verticalMidpoint);
    bool rightQuad = (p->x() + p->radius() >= verticalMidpoint);
    
    if(topQuad && leftQuad) index = 0;
    else if(topQuad && rightQuad) index = 2;
    else if(bottomQuad && rightQuad) index = 1;
    else if (bottomQuad && leftQuad) index = 3;
    return index;
}

void Quadtree::insert(Particle::ParticlePtr p){
    if (nodes[0] != nullptr) {
        int index = getIndex(p);
        if (index != -1) {
            nodes[index]->insert(p);
            return;
        }
    }
    entities.push_back(p);
    
    if (entities.size() > MAX_OBJECTS && level < MAX_LEVELS) {
        if (nodes[0] == nullptr) {
            split();
        }
        
        int i = 0;
        while (i < entities.size()) {
            int index = getIndex(entities[i]);
            if (index != -1) {
                nodes[index]->insert(entities[i]);
                entities.erase(entities.begin()+i);
            }
            else {
                i++;
            }
        }
    }
}


