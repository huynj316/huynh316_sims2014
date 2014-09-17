/*
 *  Particle.h
 *  03_C_Homework
 *
 *  Created by Julie Huynh on 9/16/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include "ofMain.h"

class Particle{
public:
	
    Particle();
	
    
    void setInitialCondition(float px, float py, float vx, float vy);
    
	
    void addForce(float x, float y);
    void resetForce();
	
	void addRepulsionForce(Particle &p, float radius, float scale);
//	void addAttractionForce(Particle &p, float radius, float scale);
    
    void update();
	void bounceOffWalls();
    
	void draw();
	
    float damping;
    
private:
    
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f acc;
	ofVec2f frc;   // frc is also know as acceleration (newton says "f=ma")
};

