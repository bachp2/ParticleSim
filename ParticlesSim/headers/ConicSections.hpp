//
//  ConicSections.hpp
//  ParticlesSim
//
//  Created by Bach Phan on 4/15/18.
//  Copyright © 2018 Bach Phan. All rights reserved.
//
#include <stdio.h>
#include "ResourcePath.hpp"
using namespace sf;

#ifndef ConicSections_hpp
#define ConicSections_hpp
namespace ConicSections
{
    static const int NUM_PTS = 500;
    static const int BOUND  = 100;
    static VertexArray lines;
    static double t[NUM_PTS];
    static void init(){
        lines = VertexArray(LinesStrip, NUM_PTS);
        auto dt = 2*M_PI/NUM_PTS;
        for(int i = 0; i < NUM_PTS; i++){
            t[i] = (i+1)*dt;
        }
    }
    
    static void draw_circle(RenderTarget& window, float x0, float y0, float r){
        for(int i = 0; i < NUM_PTS; i++){
            auto x = x0 + r*cos(t[i]);
            auto y = y0 + r*sin(t[i]);
            lines[i].position = Vector2f(x,y);
            lines[i].color    = Color::Magenta;
        }
        window.draw(lines);
    }
    static void draw_ellispe(RenderTarget& window, float x0, float y0, float a, float b){
        for(int i = 0; i < NUM_PTS; i++){
            auto x = x0 + a*cos(t[i]);
            auto y = y0 + b*sin(t[i]);
            lines[i].position = Vector2f(x,y);
            lines[i].color    = Color::Magenta;
        }
        window.draw(lines);
    }
    static void draw_parabola(RenderTarget& window, float fx, float fy, float fl){
        auto nlines = VertexArray(LinesStrip, 2*BOUND);
        auto d = fy - 2*fl;
        auto b2 = 2*BOUND;
        for(int i = 0; i < b2; i++){
            auto x = float(i);
            auto y = ((x-fx)*(x-fx) + fy*fy - d*d)/(2*(fy-d));
            nlines[i].position = Vector2f(x,y);
            nlines[i].color    = Color::Magenta;
        }
        window.draw(nlines);
    }
    static void draw_hyperbola(RenderTarget& window, float x0, float y0, float a, float b){
        for(int i = 0; i < NUM_PTS; i++){
            auto x = x0 + a*cosh(t[i]-M_PI);
            auto y = y0 + b*sinh(t[i]-M_PI);
            lines[i].position = Vector2f(x,y);
            lines[i].color    = Color::Magenta;
        }
        window.draw(lines);
    }
};
#endif /* ConicSections_hpp */
