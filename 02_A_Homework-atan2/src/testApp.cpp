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
	
	//atan2
	center.set(250,250);
//    ofSetWindowShape(1024, 540);
    
    angleT   = 0.0f;
    radiusT  = 140.0f;
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
	
	//atan2
	if ( bPlay ){
        //  If it's playing recursively add 
        //
        angleT += 1.0/ofGetFrameRate();
        
        //  Just for making it clear angle could be more than the 2PI
        //
        if (angleT > PI*2)
            angleT = 0.0f;
    }
    
    //  Get the cartesian 
    //
    dotPos.x = cos(angleT) * radiusT;
    dotPos.y = sin(angleT) * radiusT;
    
    //  Store the Y (sin) position
    //
    sinHistory.push_back(dotPos.y);
    if (sinHistory.size() > 400){
        sinHistory.erase(sinHistory.begin());
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
	
	//atan2
	ofDrawBitmapString("Press a key or drag with your mouse", 15,15);
    
    ofPushMatrix();
    ofTranslate(center);
    
    //  Draw Cartesian
    //
    float lenghtOfAxis = 200;
    ofSetColor(100);
    
    ofLine(ofPoint(-lenghtOfAxis,0),
           ofPoint(lenghtOfAxis,0));
    ofDrawBitmapString("-X", -lenghtOfAxis - 25, 5);
    ofDrawBitmapString("X", lenghtOfAxis + 5, 5);
    ofLine(ofPoint(0,-lenghtOfAxis),
           ofPoint(0,lenghtOfAxis));
    ofDrawBitmapString("-Y", -11, -lenghtOfAxis - 5);
    ofDrawBitmapString("Y", -3, lenghtOfAxis + 15);
	
    //  Draw Vector
    //
    ofSetColor(255);
    ofLine(0,0, dotPos.x, dotPos.y);
    
    //  Draw Vector projections on axis
    //
    ofSetColor(255);
    ofLine(0,0,dotPos.x,0); // X
    ofLine(0,0,0,dotPos.y); // Y
    ofSetColor(255,50);
    ofLine(dotPos.x,dotPos.y,dotPos.x,0); // X
    ofLine(dotPos.x,dotPos.y,0,dotPos.y); // Y
    
    //  Draw Dot
    //
    drawDot( dotPos );
    
    //  Draw angle References
    //
    ofPolyline  angleLine;
    angleLine.arc(0, 0, radiusT*0.3, radiusT*0.3, 0, ofRadToDeg(angleT));
    ofNoFill();
    ofSetColor(255,180);
    angleLine.draw();
    ofDrawBitmapString("a = " + ofToString(angleT,2) + " (" + ofToString((int)(ofRadToDeg(angleT))) + " deg)", radiusT*0.3 + 5, 15);
    
    //  Draw sin and cos projected dots
    //
    ofSetColor(255,100);
    ofLine(-radiusT, lenghtOfAxis + 30, radiusT, lenghtOfAxis + 30);
    ofDrawBitmapString("-1", -radiusT - 15, lenghtOfAxis + 30 + 5);
    ofDrawBitmapString("1", radiusT + 5, lenghtOfAxis + 30 + 5);
    ofPoint cosPos = ofPoint(dotPos.x,  lenghtOfAxis + 30);
    ofDrawBitmapString("cos(a).r = " + ofToString( cos(angleT),2) , cosPos + ofPoint(-3,15));
    drawDot(cosPos);
    ofLine(lenghtOfAxis + 30,-radiusT, lenghtOfAxis + 30,radiusT);
    ofDrawBitmapString("-1", lenghtOfAxis + 30 - 12,-radiusT -5);
    ofDrawBitmapString("1", lenghtOfAxis + 30 - 3, radiusT + 15 );
    ofPoint sinPos = ofPoint(lenghtOfAxis + 30, dotPos.y);
    ofDrawBitmapString("sin(a).r = " + ofToString( sin(angleT),2) , sinPos + ofPoint(15,3));
    drawDot(sinPos);
    
    //  Draw the history of sin throught time
    //
    ofMesh lineMesh;
    lineMesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    
    for (int i = sinHistory.size() -1 ; i > 0 ; i--){
        float alpha = ofMap(i+1, 1,sinHistory.size(), 0.0,1.0);
        
        lineMesh.addColor( ofFloatColor(1.0, alpha) );
        lineMesh.addVertex( ofPoint(lenghtOfAxis + 30 + (sinHistory.size()-i), sinHistory[i]) );
    }
    
    ofSetColor(255);
    lineMesh.draw();
    
    
    ofPopMatrix();
	//end of atan2
	
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
void testApp::drawDot(ofPoint _pos){
	//atan2
    ofPushStyle();
    
    ofFill();
    ofSetColor(255, 0,0);
    ofCircle(_pos, 5);
    
    ofPopStyle();
	
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
	//atan2
	bPlay = !bPlay;

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
