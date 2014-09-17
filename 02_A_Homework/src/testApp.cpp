#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	
	ofSetCircleResolution(100);
	
	ofEnableAlphaBlending();
	
	//draw # of circles for trail
	for (int i=0; i<30; i++) {
		trail myTrail;
		trailList.push_back( myTrail );
	}
	
	//orbit
	ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    amplitudeX = ofGetWindowWidth() / 2.0f;
    amplitudeY = ofGetHeight() / 2.0f;
    period = 5000.0;
	
	//circle path
	radiusC = 50;
}

//--------------------------------------------------------------
void testApp::update(){
	//circle trail
	for (int i = 0; i <trailList.size(); i++) {
		if (i==0) {
			trailList[i].xenoToPoint(mouseX,mouseY);
		}else {
			trailList[i].xenoToPoint(trailList[i-1].pos.x, trailList[i-1].pos.y);
		}
		
	//circle path
	radiusC = radiusC + 0.1f;
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	// bg color change
	float sinOfTime				= sin( ofGetElapsedTimef() );
	float sinOfTimeMapped		= ofMap( sinOfTime, -1, 1, 0, 255);
	
	ofBackground((sinOfTimeMapped/2), sinOfTimeMapped, sinOfTimeMapped);
	
	//circle trail
	for (int i = 0; i < trailList.size(); i++) {
		
		trailList[i].draw();
	}
	
	//resizing of center circle
	float sinOfTime1 = sin( ofGetElapsedTimef() * 2 );
	float sinOfTimeMapped1 = ofMap( sinOfTime1, -1, 1, 50, 180);
	
	//center circle color change
	float sinOfTime2			= sin( ofGetElapsedTimef() + PI);
	float sinOfTimeMapped2		= ofMap( sinOfTime2, -1, 1, 0, 255);

	ofFill();
	ofSetColor((sinOfTimeMapped2/2), sinOfTimeMapped2, sinOfTimeMapped2);
	ofCircle((ofGetWidth()/2),(ofGetHeight()/2), sinOfTimeMapped1);
	
	//orbit
	ofPoint p;
    
    p.x = amplitudeX * sin( (ofGetElapsedTimeMillis() / period ) * TWO_PI );
    p.y = amplitudeY * cos( (ofGetElapsedTimeMillis() / period ) * TWO_PI );;
    
    ofPushMatrix();{
        ofTranslate( ofGetWindowSize() / 2.0 );
        ofCircle( p, 20);
		
    }ofPopMatrix();
	
	//ancy rects
	float modulator = ofMap( sin(ofGetElapsedTimef()*12.7), -1, 1, 0, 1);
	
	float xpos		= ofMap( sin(ofGetElapsedTimef()*3) * modulator, -1, 1, 0, ofGetWidth());
	
	
	ofSetColor(255,255,255);
	
	ofRect(xpos, 100, 20,20);
	
	float modulator2 = ofMap( sin(ofGetElapsedTimef()*12.7), -1, 1, 0, 1);
	
	float xpos2		= ofMap( sin(ofGetElapsedTimef()*3) * modulator2, -1, 1, 0, ofGetWidth());
	
	
	ofSetColor(255,255,255);
	
	ofRect(xpos2, 678, 20,20);

//	//pencil tool
//	ofSetColor(0, 0, 0);
//	
//	ofBeginShape();
//	for (int i = 0; i < points.size(); i++){
//		ofVertex(points[i].x, points[i].y);
//	}
//	ofEndShape();
	
	//circle spiral path
	float xorig = ofGetWidth()/2;
	float yorig = ofGetHeight()/2;
	
	for (int i = 0; i < 20; i++){
		
		float radius = 50 + i * 20;
		float angle = ofGetElapsedTimef() * (1 + i / 10.0);
		float x = xorig + radius * cos(angle);
		float y = yorig + radius * -sin(angle);
		
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofSetColor(255,255,255);
		ofFill();
		ofCircle(x,y,10,10);
		
	}	
	
	//circle path
	float xorigC = ofGetWidth()/2;
	float yorigC = ofGetHeight()/2;
	float angle = ((ofGetElapsedTimef()*-360)/2);
	
	float x = xorigC + radiusC * cos(angle);
	float y = yorigC + radiusC * -sin(angle);
	
	ofPoint temp;
	temp.x = x;
	temp.y = y;
	points.push_back(temp);
	if (points.size() > 100){
		points.erase(points.begin());
	}
	
	
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofSetColor(255,0,127);
	ofFill();
	ofCircle(x,y,10);
	
	ofSetColor(255,255,255);
	
	ofNoFill();
	ofBeginShape();
	for (int i = 0; i < points.size(); i++){
		ofVertex(points[i].x, points[i].y);
	}
	ofEndShape();


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
