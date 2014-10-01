#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSeedRandom();
    Particle car1;
    
    dest1 = ofPoint( ofRandomWidth(), ofRandomHeight() );
    dest2 = ofPoint( ofRandomWidth(), ofRandomHeight() );
    
	for (int i= 0; i < 10; i++){
    car1.setInit( ofGetWindowSize() / 2, ofPoint(10, -5) );
    car2.setInit( ofGetWindowSize() / 2, ofPoint(10, 5) );
    
    car1.color = ofColor(0,255,0);
    car2.color = ofColor(0,0,255);
		
	car1Particles.push_back(car1);
    }
		
    ofBackground(255);
    
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::update(){
	
	for (int i=0; i < car1Particles.size(); i++) {	
    // apply steering force
    car1Particles[i].seek( dest1 );
    car2.seek( dest2 );
    
    // apply repelling force
    float area = 200;
    if( car1Particles[i].getPosition().distance( car2.getPosition() ) < area ){
        car1Particles[i].color = ofColor(255,0,0);
        car2.color = ofColor(255,0,0);
        
        car1Particles[i].addRepulsionForce( car2.getPosition(), area,  0.1 );
        car2.addRepulsionForce( car1Particles[i].getPosition(), area, 0.1 );
    }else{
        car1Particles[i].color = ofColor(0,255,0);
        car2.color = ofColor(0,0,255);
    }
    
    // update physics
    car1Particles[i].update();
    car2.update();
    
    if( car1Particles[i].getPosition().distance(dest1) < 5){
        dest1 = ofPoint( ofRandomWidth(), ofRandomHeight() );
    }
    
    if( car2.getPosition().distance(dest2) < 5){
        dest2 = ofPoint( ofRandomWidth(), ofRandomHeight() );
    }
	}
	for (int i = 0; i < car1Particles.size(); i++) {
		car1Particles[i].update();
	}
}


//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    
	for (int i = 0; i < car1Particles.size(); i++){
    ofSetColor( car1Particles[i].color );
    ofCircle( dest1, 4 );
    car1Particles[i].draw();
	}
    
    ofSetColor( car2.color );
    ofCircle( dest2, 4 );
    car2.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
	
}
