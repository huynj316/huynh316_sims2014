#include "testApp.h"
//--------------------------------------------------------------
void testApp::setup(){	
	
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofBackground(255);
	
	
	for (int i = 0; i < 500; i++){
		Particle myParticle;
		float vx = cos(4); // change this to sin/cos
		float vy = sin(4);
		myParticle.setInitialCondition(300,300, ofRandom(-10,10),ofRandom(-10,10));
		// more interesting with diversity :)
		// uncomment this: 
		myParticle.damping = ofRandom(0.01, 0.03);
		particles.push_back(myParticle);
	}
	ofSetBackgroundAuto(false);
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	// on every frame
	// add in any forces on the particle
	// then update
	
	
	
	for (int i = 0; i < particles.size(); i++){

		particles[i].addForce(0.0, 0.48);
		//particles[i].addAttractionForce(mouseX, mouseY, 1000, 0.07f);

		particles[i].bounceOffWalls();
		
		//for (int j = 0; j < i; j++){
			particles[i].addRepulsionForce(particles[i], 200, 0.005);
			//particles[i].addCounterClockwiseForce(particles[j], 80, 0.09);
		//}
		
		
	}
		for (int i = 0; i < particles.size(); i++){
			particles[i].update();
		}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	//transparent bg
    ofFill();
    
    ofSetColor(0, 0, 0, 2);
    ofRect( ofGetWindowRect() );
	
	
	//particles
	ofSetColor(200,0,100,ofRandom(2,3));
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].draw();
	}
	
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	for (int i = 0; i < particles.size(); i++){
//		Particle myParticle;
		float vx = cos(4);;
		float vy = sin(4);;
		particles[i].setInitialCondition(mouseX,mouseY,ofRandom(-10,10),ofRandom(-10,10));
//		myParticle.damping = ofRandom(0.01, 0.03);
//		particles.push_back(myParticle);
		
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}
