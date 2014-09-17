#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(255);
	
	//    for (int i = 0; i < 1000; i++){
	//        addParticle();
	//    }
    
    ofSetBackgroundAuto(false);

}

//--------------------------------------------------------------
void testApp::update(){
	
    // on every frame
	// we reset the forces
	// add in any forces on the particle
	// perfom damping and
	// then update
	
	for (int i=0; i < particleList.size(); i++){
		particleList[i].resetForces();
		//		particleList[i].addForce( ofVec2f(0,0.04));  // gravity
		particleList[i].addDampingForce();
		particleList[i].update();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
    
    
    ofFill();
    
    ofSetColor(0, 0, 0, 2);
    ofRect( ofGetWindowRect() );
    
    ofSetColor(ofRandom(0,255),ofRandom(0,155),ofRandom(0,155));
    for (int i=0; i < particleList.size(); i++){
        particleList[i].draw();
    }
	
    ofNoFill();
	
	ofBeginShape();
	for (int i = 0; i < particleList.size(); i++){
		ofVertex(particleList[i].pos.x, particleList[i].pos.y);
	}
	ofEndShape();
}

void testApp::addParticle() {
    Particle myParticle;
	
    float vx = ofRandom(-4,4);
    float vy = ofRandom(-4,4);
    myParticle.setParams(300,300,vx, vy);
	
    particleList.push_back(myParticle);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	

	
    ofPoint difference = ofPoint(x,y) - lastMousePos;
	float radius = cos(3);
	float angle = sin(30);

	x = x + radius * cos(angle);
	y = y + radius * sin(angle);
	
    Particle myParticle;
	
	//    float vx = ofRandom(-4,4);
	//    float vy = ofRandom(-4,4);
    myParticle.setParams(x, y, difference.x, difference.y);
	
    particleList.push_back(myParticle);
	
	
    lastMousePos.set(x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    particleList.clear();
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
