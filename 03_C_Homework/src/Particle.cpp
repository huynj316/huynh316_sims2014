/*
 *  Particle.cpp
 *  03_C_Homework
 *
 *  Created by Julie Huynh on 9/16/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#include "Particle.h"


//------------------------------------------------------------
Particle::Particle(){
	setInitialCondition(0,0,0,0);
	damping = 0.01f;
}

//------------------------------------------------------------
void Particle::setInitialCondition(float px, float py, float vx, float vy){
    pos.set(px,py);
	vel.set(vx,vy);
}

//------------------------------------------------------------
void Particle::addForce(float x, float y){
    // add in a force in X and Y for this frame.
    acc.x = acc.x + x;
    acc.y = acc.y + y;
}

//------------------------------------------------------------
void Particle::update(){	
	vel = vel + acc;
    vel = vel * (1.0-damping);
	pos = pos + vel;
    acc *= 0.0;
}

//------------------------------------------------------------
void Particle::draw(){
    ofCircle(pos, 5);
}

//------------------------------------------------------------
void Particle::bounceOffWalls(){
	
	// sometimes it makes sense to damped, when we hit... for now, we don't
	bool bDampedOnCollision = false;
	bool bDidICollide = false;
	
	// what are the walls
	float minx = 0;
	float miny = 0;
	float maxx = ofGetWidth();
	float maxy = ofGetHeight();
	
	if (pos.x > maxx){
		pos.x = maxx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	} else if (pos.x < minx){
		pos.x = minx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	}
	
	if (pos.y > maxy){
		pos.y = maxy; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	} else if (pos.y < miny){
		pos.y = miny; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	}
	
	if (bDidICollide == true && bDampedOnCollision == true){
		vel *= 0.9;
	}
	
}
//------------------------------------------------------------
void Particle::addRepulsionForce(Particle &p, float radius, float scale){
	
	// ----------- (1) make a vector of where this Particle p is: 
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
		p.frc.x = p.frc.x - diff.x * scale * pct;
        p.frc.y = p.frc.y - diff.y * scale * pct;
    }
}

//------------------------------------------------------------
//void Particle::addAttractionForce(Particle & p, float radius, float scale){
//	
//	// ----------- (1) make a vector of where this Particle p is: 
//	ofVec2f posOfForce;
//	posOfForce.set(p.pos.x,p.pos.y);
//	
//	// ----------- (2) calculate the difference & length 
//	
//	ofVec2f diff	= pos - posOfForce;
//	float length	= diff.length();
//	
//	// ----------- (3) check close enough
//	
//	bool bAmCloseEnough = true;
//    if (radius > 0){
//        if (length > radius){
//            bAmCloseEnough = false;
//        }
//    }
//	
//	// ----------- (4) if so, update force
//    
//	if (bAmCloseEnough == true){
//		float pct = 1 - (length / radius);  // stronger on the inside
//		diff.normalize();
//		frc.x = frc.x - diff.x * scale * pct;
//        frc.y = frc.y - diff.y * scale * pct;
//		p.frc.x = p.frc.x + diff.x * scale * pct;
//        p.frc.y = p.frc.y + diff.y * scale * pct;
//    }
//	
//}
//
