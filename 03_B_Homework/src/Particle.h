/*
 *  Particle.h
 *  03_A_Homework
 *
 *  Created by Julie Huynh on 9/16/14.
 *  Reference
 *	Particle.h
 *  SingleParticle
 *
 *  Created by Charlie Whitney on 9/23/13.
 *
 */

#pragma once

#include "ofMain.h"

class Particle {
public:
    Particle();
    
    void update();
    void draw();
    
    void setParams( float px, float py, float vx, float vy );
    void addForce( ofVec2f force );
    void addDampingForce();
    void resetForces();
    
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f frc;
    
    ofVec2f damping;  // could also be a ofVec2f

};