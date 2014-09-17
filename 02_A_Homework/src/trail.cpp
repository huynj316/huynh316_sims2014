/*
 *  trail.cpp
 *  02_A_HW
 *
 *  Created by Julie Huynh on 9/10/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#include "trail.h"


//------------------------------------------------------------------
trail::trail(){
	catchUpSpeed = 0.04f;
}

//------------------------------------------------------------------
void trail::draw() {
	//	ofFill();
	//	ofSetRectMode(OF_RECTMODE_CENTER); // center around the position
	//    ofSetColor(ofColor::green);
	//	for (int i = 0; i<10; i++) {
	//		ofSetColor(i+200, i*9, i*9);
	//	}
	ofSetCircleResolution(60);
	ofSetColor(255 * (pos.y / ofGetHeight() ), 255 * (pos.y / ofGetHeight() ), 0 );
    ofCircle(pos.x, pos.y, 40);
}

//------------------------------------------------------------------
void trail::xenoToPoint(float catchX, float catchY){
	
	pos.x = catchUpSpeed * catchX + (1-catchUpSpeed) * pos.x; 
	pos.y = catchUpSpeed * catchY + (1-catchUpSpeed) * pos.y;
	
}
