#include "testApp.h"
#include "ofMain.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetVerticalSync(true);
	
	ofBackground(ofColor::black);
	
	ofEnableAlphaBlending();
	
	
	//set pos of circle
	for (int i=0; i<30; i++) {
		circle myCircle;
		circList.push_back( myCircle );
	}
	
	
	//set a and b positions of rectangle
	for (int i = 0; i<10; i++) {
		myRectangles[i].posb.x = 0;
		myRectangles[i].posb.y = i*20;
		myRectangles[i].posa.x = ofGetWidth();
		myRectangles[i].posa.y = ofGetHeight() - i*20;
		myRectangles[i].shaper = 0.4 + 0.2 * i;
		myRectangles[i].interpolateByPct(0);	//start at 0 pct

		myRectangles[i].radiusa = 30;
		myRectangles[i].radiusb = 200;
	}
		pct = 0;							//a variable we can alter
		

}

//--------------------------------------------------------------
void testApp::update(){
	pct += 0.02f;				//inc by a certain amt
	if (pct > 1) pct = 0;		//just btwn 0 and 1 (0% - 100%)
	for (int i = 0; i < 10; i++){
		myRectangles[i].interpolateByPct(pct);
	}
	for (int i = 0; i <circList.size(); i++) {
		if (i==0) {
			circList[i].xenoToPoint(mouseX,mouseY);
		}else {
			circList[i].xenoToPoint(circList[i-1].pos.x, circList[i-1].pos.y);
		}
									

	}
	

}

//--------------------------------------------------------------
void testApp::draw(){
	for (int i = 0; i < 10; i++) {
		ofSetColor(ofColor::aqua);
		//if (i == 3) ofSetColor(255, 0, 0);
		myRectangles[i].draw();
	}
//	ofSetColor(ofColor::gray);
//	for (int i = 0; i < 10; i++) {
//		ofLine(0, i*20, ofGetWidth(), i*20);
//	}
	
	for (int i = 0; i < circList.size(); i++) {
		
		circList[i].draw();
	}

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == ' ') {
		ofToggleFullscreen();
	}
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
	//click to get new position
	//myRectangle.pos.x = ofRandom(0,ofGetWidth());
	//myRectangle.pos.y = ofRandom(0,ofGetHeight());
	pct += 0.01f;				//inc by a certain amt
	if (pct < 1) pct = 0;		//just btwn 0 and 1 (0% - 100%)
		
	for (int i = 0; i < 10; i++) {
		myRectangles[i].interpolateByPct(pct);	
	}

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
